#include "core_engine.hpp"

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

CoreEngine::CoreEngine(FabiEngine3D& fe3d)
	:
	_fe3d(fe3d),
	_window(_libraryLoader),
	_audioManager(_audioLoader),
	_shadowGenerator(_renderBus),
	_textureLoader(_renderBus),
	_camera(_renderBus, _window),
	_masterRenderer(_renderBus, _timer, _textureLoader, _camera, _shadowGenerator),
	_skyEntityManager(_meshLoader, _textureLoader, _renderBus),
	_terrainEntityManager(_meshLoader, _textureLoader, _renderBus),
	_waterEntityManager(_meshLoader, _textureLoader, _renderBus),
	_modelEntityManager(_meshLoader, _textureLoader, _renderBus, _timer),
	_billboardEntityManager(_meshLoader, _textureLoader, _renderBus, _camera),
	_aabbEntityManager(_meshLoader, _textureLoader, _renderBus),
	_pointlightEntityManager(_meshLoader, _textureLoader, _renderBus),
	_spotlightEntityManager(_meshLoader, _textureLoader, _renderBus),
	_reflectionEntityManager(_meshLoader, _textureLoader, _renderBus),
	_imageEntityManager(_meshLoader, _textureLoader, _renderBus),
	_textEntityManager(_meshLoader, _textureLoader, _renderBus),
	_raycaster(_renderBus, _terrainEntityManager)
{

}

void CoreEngine::_start()
{
	// Error
	if(_isRunning)
	{
		Logger::throwError("Tried to start engine: already running!");
	}

	// Start running
	_isRunning = true;

	// Prepare application
	_prepareApplication();

	// Variables
	float renderLag = 0.0f;

	// Main game-loop
	while(_isRunning)
	{
		// Start measuring time
		auto previousTime = high_resolution_clock::now();

		if(_fe3d.server_isRunning()) // Process application at full speed
		{
			// Retrieve user input if not exported
			if(!Config::getInst().isApplicationExported())
			{
				_inputHandler.update();
			}

			// Update application
			_updateApplication();
			_timer.increasePassedFrameCount();

			// Render application if not exported
			if(!Config::getInst().isApplicationExported())
			{
				_renderApplication();
			}
		}
		else // Process application at fixed speed
		{
			// Update render lag
			renderLag += _deltaTimeMS;

			// Check if render lag is getting too much
			if(renderLag > (Config::MS_PER_UPDATE * 10.0f))
			{
				renderLag = Config::MS_PER_UPDATE;
			}

			// Process (roughly) 144 times per second
			while(renderLag >= Config::MS_PER_UPDATE)
			{
				// Retrieve user input
				_inputHandler.update();

				// Update application
				_updateApplication();

				// Update render lag
				renderLag -= Config::MS_PER_UPDATE;
				renderLag = std::max(renderLag, 0.0f);
				_timer.increasePassedFrameCount();
			}

			// Render application
			_renderApplication();
		}

		// Calculate delta time
		auto currentTime = high_resolution_clock::now();
		auto timeDifference = duration_cast<nanoseconds>(currentTime - previousTime);
		_deltaTimeMS = static_cast<float>(timeDifference.count()) / 1000000.0f;
	}

	// Finish engine controller
	_fe3d.FE3D_CONTROLLER_TERMINATE();
}

void CoreEngine::_pause()
{
	if(_isPaused)
	{
		Logger::throwError("Tried to resume engine: already paused!");
	}

	_isPaused = true;
}

void CoreEngine::_resume()
{
	if(!_isPaused)
	{
		Logger::throwError("Tried to resume engine: not paused!");
	}

	_isPaused = false;
}

void CoreEngine::_stop()
{
	if(!_isRunning)
	{
		Logger::throwError("Tried to stop engine: not running!");
	}

	_isRunning = false;
}

void CoreEngine::_updateApplication()
{
	// Temporary values
	static ivec2 lastCursorPosition = _window.getCursorPosition();

	// Exit application
	if(_inputHandler.isKeyDown(InputType::WINDOW_X_BUTTON))
	{
		_stop();
		return;
	}

	// User updates
	_timer.startDeltaPart("coreUpdate");
	_fe3d._isRaycastUpdated = false;
	_fe3d._hoveredAabbID = "";
	_fe3d.FE3D_CONTROLLER_UPDATE();
	_timer.stopDeltaPart();

	// An exported server application does not have engine updates
	if(!(Config::getInst().isApplicationExported() && _fe3d.server_isRunning()))
	{
		// Only update 3D if engine not paused
		if(!_isPaused)
		{
			// Physics updates
			_timer.startDeltaPart("physicsUpdate");
			_camera.update(lastCursorPosition);
			_raycaster.update(_fe3d.misc_getCursorPositionRelativeToViewport());
			_cameraCollisionHandler.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _camera);
			_camera.updateMatrices();
			_timer.stopDeltaPart();

			// 3D entity updates
			_timer.startDeltaPart("skyEntityUpdate");
			_skyEntityManager.update();
			_timer.stopDeltaPart();
			_timer.startDeltaPart("waterEntityUpdate");
			_waterEntityManager.update();
			_timer.stopDeltaPart();
			_timer.startDeltaPart("modelEntityUpdate");
			_modelEntityManager.update(_reflectionEntityManager.getEntities());
			_timer.stopDeltaPart();
			_timer.startDeltaPart("billboardEntityUpdate");
			_billboardEntityManager.update();
			_timer.stopDeltaPart();
			_timer.startDeltaPart("aabbEntityUpdate");
			_aabbEntityManager.update(_modelEntityManager.getEntities(), _billboardEntityManager.getEntities());
			_timer.stopDeltaPart();
			_timer.startDeltaPart("lightEntityUpdate");
			_pointlightEntityManager.update();
			_spotlightEntityManager.update();
			_timer.stopDeltaPart();
			_timer.startDeltaPart("reflectionEntityUpdate");
			_reflectionEntityManager.update();
			_timer.stopDeltaPart();

			// Shadow updates
			_timer.startDeltaPart("shadowUpdate");
			_shadowGenerator.update();
			_timer.stopDeltaPart();

			// Audio updates
			_timer.startDeltaPart("audioUpdate");
			_audioManager.update();
			_audioPlayer.update(_camera, _audioManager.getAllSound2d(), _audioManager.getAllSound3d());
			_timer.stopDeltaPart();
		}

		// Always update 2D entity logic, because of engine GUI interaction
		_timer.startDeltaPart("guiEntityUpdate");
		_imageEntityManager.update();
		_textEntityManager.update();
		_timer.stopDeltaPart();
	}

	// Always update networking
	_timer.startDeltaPart("networkUpdate");
	_networkingServer.update();
	_networkingClient.update();
	_timer.stopDeltaPart();

	// Always update master renderer
	_masterRenderer.update();

	// Miscellaneous
	_updateWindowFading();

	// Save last cursor position
	lastCursorPosition = _window.getCursorPosition();
}

void CoreEngine::_updateWindowFading()
{
	// Only if in engine preview
	if(!Config::getInst().isApplicationExported())
	{
		static float opacity = 0.0f;

		if(opacity < 1.0f) // Stop if window is 100% visible
		{
			_window.setOpacity(opacity);
			opacity += 0.01f;
		}
		if(opacity >= 1.0f) // Opacity must be exactly 100% after fading
		{
			opacity = 1.0f;
			_window.setOpacity(opacity);
		}
	}
}