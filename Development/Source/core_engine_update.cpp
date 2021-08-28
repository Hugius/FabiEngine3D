#include "core_engine.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

void CoreEngine::_updateApplication()
{
	// Temporary values
	static Ivec2 lastCursorPosition = _window.getCursorPosition();

	// Exit application
	if (_inputHandler.isKeyDown(InputType::WINDOW_X_BUTTON))
	{
		_stop();
	}

	// User updates
	_timer.startDeltaPart("coreUpdate");
	_fe3d._isRaycastUpdated = false;
	_fe3d._hoveredAabbID = "";
	_fe3d.FE3D_CONTROLLER_UPDATE();
	_timer.stopDeltaPart();

	// An exported server application does not have engine updates
	if (!(_fe3d.application_isExported() && _fe3d.networkServer_isRunning()))
	{
		// Only update 3D if engine not paused
		if (!_isPaused)
		{
			// Camera updates
			_timer.startDeltaPart("cameraUpdate");
			_camera.update(lastCursorPosition);
			_timer.stopDeltaPart();

			// Raycast updates
			_timer.startDeltaPart("raycastUpdate");
			_rayCaster.update(_fe3d.misc_getCursorPositionRelativeToViewport());
			_timer.stopDeltaPart();

			// Collision updates
			_timer.startDeltaPart("collisionUpdate");
			_collisionResolver.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _camera, _collisionDetector);
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

			// Shadow updates
			_timer.startDeltaPart("shadowUpdate");
			_shadowGenerator.update(_renderBus);
			_timer.stopDeltaPart();

			// Audio updates
			_timer.startDeltaPart("audioUpdate");
			_audioPlayer.update(_camera, _audioManager.getSounds(), _audioManager.getMusic());
			_timer.stopDeltaPart();
		}

		// Always update 2D logic (except for sprite animations), because of engine GUI interaction
		_timer.startDeltaPart("guiEntityUpdate");
		(!_isPaused) ? _imageEntityManager.updateSpriteAnimations() : void();
		_imageEntityManager.update();
		_textEntityManager.update();
		_timer.stopDeltaPart();
	}

	// Always update networking
	_timer.startDeltaPart("networkUpdate");
	_networkServerAPI.update();
	_networkClientAPI.update();
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
	if (!Config::getInst().isApplicationExported())
	{
		static float opacity = 0.0f;

		if (opacity < 1.0f) // Stop if window is 100% visible
		{
			_window.setOpacity(opacity);
			opacity += 0.01f;
		}
		if (opacity >= 1.0f) // Opacity must be exactly 100% after fading
		{
			opacity = 1.0f;
			_window.setOpacity(opacity);
		}
	}
}

void CoreEngine::_renderApplication()
{
	// Reset triangle count
	_renderBus.resetTriangleCount();

	// Create bus with all entities
	const auto mainSky = _skyEntityManager.getSelectedMainSky();
	const auto mixSky = _skyEntityManager.getSelectedMixSky();
	const auto terrain = _terrainEntityManager.getSelectedTerrain();
	const auto water = _waterEntityManager.getSelectedWater();
	const auto models = _modelEntityManager.getEntities();
	const auto billboards = _billboardEntityManager.getEntities();
	const auto AABBs = _aabbEntityManager.getEntities();
	const auto lights = _lightEntityManager.getEntities();
	const auto reflections = _reflectionEntityManager.getEntities();
	const auto images = _imageEntityManager.getEntities();
	const auto texts = _textEntityManager.getEntities();
	EntityBus entityBus(mainSky, mixSky, terrain, water, models, billboards, AABBs, lights, reflections, images, texts);

	// Render entities
	_masterRenderer.renderScene(&entityBus);

	// Swap GPU buffer
	_timer.startDeltaPart("bufferSwap");
	_window.swapBackBuffer();
	_timer.stopDeltaPart();
}