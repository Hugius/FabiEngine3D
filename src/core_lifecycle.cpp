#include "core.hpp"

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;

Core::Core(FabiEngine3D& fe3d)
	:
	_fe3d(fe3d),
	_window(_libraryLoader),
	_sound2dManager(_audioLoader),
	_sound3dManager(_audioLoader),
	_shadowGenerator(_renderBus),
	_camera(_renderBus, _window),
	_skyEntityManager(_renderBus),
	_terrainEntityManager(_imageLoader),
	_modelEntityManager(_meshLoader, _renderBus, _timer),
	_billboardEntityManager(_renderBus, _camera),
	_quadEntityManager(_renderBus),
	_textEntityManager(_renderBus),
	_raycaster(_renderBus, _terrainEntityManager),
	_masterRenderer(_renderBus, _timer, _camera, _shadowGenerator)
{

}

void Core::_start()
{
	if(_isRunning)
	{
		Logger::throwError("Tried to start engine: already running!");
	}

	_isRunning = true;

	_prepare();

	float renderLag = 0.0f;

	while(_isRunning)
	{
		auto previousTime = high_resolution_clock::now();

		if(_fe3d.server_isRunning())
		{
			if(!Config::getInst().isApplicationExported())
			{
				_inputHandler.update();
			}

			_update();
			_timer.increasePassedFrameCount();

			if(!Config::getInst().isApplicationExported())
			{
				_render();
			}
		}
		else
		{
			renderLag += _deltaTimeMS;

			if(renderLag > (Config::MS_PER_UPDATE * 10.0f))
			{
				renderLag = Config::MS_PER_UPDATE;
			}

			while(renderLag >= Config::MS_PER_UPDATE)
			{
				_inputHandler.update();

				_update();

				renderLag -= Config::MS_PER_UPDATE;
				renderLag = max(renderLag, 0.0f);
				_timer.increasePassedFrameCount();
			}

			_render();
		}

		auto currentTime = high_resolution_clock::now();
		auto timeDifference = duration_cast<nanoseconds>(currentTime - previousTime);
		_deltaTimeMS = static_cast<float>(timeDifference.count()) / 1000000.0f;
	}

	_fe3d.FE3D_CONTROLLER_TERMINATE();
}

void Core::_pause()
{
	if(_isPaused)
	{
		Logger::throwError("Tried to resume engine: already paused!");
	}

	_isPaused = true;
}

void Core::_resume()
{
	if(!_isPaused)
	{
		Logger::throwError("Tried to resume engine: not paused!");
	}

	_isPaused = false;
}

void Core::_stop()
{
	if(!_isRunning)
	{
		Logger::throwError("Tried to stop engine: not running!");
	}

	_isRunning = false;
}

void Core::_update()
{
	static ivec2 lastCursorPosition = _window.getCursorPosition();

	if(_inputHandler.isKeyDown(InputType::WINDOW_X_BUTTON))
	{
		_stop();
		return;
	}

	_timer.startDeltaPart("coreUpdate");
	_fe3d._isRaycastUpdated = false;
	_fe3d._hoveredAabbID = "";
	_fe3d.FE3D_CONTROLLER_UPDATE();
	_timer.stopDeltaPart();

	if(!(Config::getInst().isApplicationExported() && _fe3d.server_isRunning()))
	{
		if(!_isPaused)
		{
			_timer.startDeltaPart("physicsUpdate");
			_camera.update(lastCursorPosition);
			_raycaster.update(_fe3d.misc_getCursorPositionRelativeToViewport());
			_cameraCollisionHandler.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _camera);
			_camera.updateMatrices();
			_timer.stopDeltaPart();

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

			_timer.startDeltaPart("shadowUpdate");
			_shadowGenerator.update();
			_timer.stopDeltaPart();

			_timer.startDeltaPart("soundUpdate");
			_sound2dManager.update();
			_sound3dManager.update();
			_sound2dPlayer.update(_sound2dManager.getSounds());
			_sound3dPlayer.update(_sound3dManager.getSounds(), _camera);
			_timer.stopDeltaPart();
		}

		_timer.startDeltaPart("guiEntityUpdate");
		_quadEntityManager.update();
		_textEntityManager.update();
		_timer.stopDeltaPart();
	}

	_timer.startDeltaPart("networkUpdate");
	_networkingServer.update();
	_networkingClient.update();
	_timer.stopDeltaPart();

	_masterRenderer.update();

	if(!Config::getInst().isApplicationExported())
	{
		static float opacity = 0.0f;
		if(opacity < 1.0f)
		{
			_window.setOpacity(opacity);
			opacity += 0.01f;
		}
		if(opacity > 1.0f)
		{
			opacity = 1.0f;
			_window.setOpacity(opacity);
		}
	}

	lastCursorPosition = _window.getCursorPosition();
}