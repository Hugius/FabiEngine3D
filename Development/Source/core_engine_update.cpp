#include "core_engine.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

void CoreEngine::_updateApplication()
{
	// Temporary values
	static Ivec2 lastCursorPosition = _window.getCursorPos();

	// Exit application
	if (_inputHandler.getKeyDown(InputType::WINDOW_X_BUTTON))
	{
		_stop();
	}

	// User updates
	_timer.startDeltaPart("coreUpdate");
	_fe3d._isRaycastUpdated = false;
	_fe3d._hoveredAabbID = "";
	_fe3d.FE3D_CONTROLLER_UPDATE();
	_timer.stopDeltaPart();

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
		_collisionResolver.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _camera);
		_timer.stopDeltaPart();

		// 3D entity updates
		_timer.startDeltaPart("skyEntityUpdate");
		_skyEntityManager.update();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("waterEntityUpdate");
		_waterEntityManager.update();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("modelEntityUpdate");
		_modelEntityManager.update();
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
		_camera.updateMatrices();
		_timer.stopDeltaPart();

		// Audio updates
		_timer.startDeltaPart("guiEntityUpdate");
		_audioPlayer.update(_camera, _audioManager.getSounds(), _audioManager.getMusic());
		_timer.stopDeltaPart();
	}

	// Always update 2D logic (except for sprite animations)
	_timer.startDeltaPart("imageTextUpdate");
	(!_isPaused) ? _imageEntityManager.updateSpriteAnimations() : void();
	_imageEntityManager.update();
	_textEntityManager.update();
	_timer.stopDeltaPart();

	// Always update networking
	_timer.startDeltaPart("networkUpdate");
	_networkServer.update();
	_networkClient.update();
	_timer.stopDeltaPart();

	// Miscellaneous
	_updateWindowFading();

	// Save last cursor position
	lastCursorPosition = _window.getCursorPos();
}

void CoreEngine::_renderApplication()
{
	// Reset triangle count
	_renderBus.resetTriangleCount();

	// Create bus with all entities
	EntityBus entityBus
	(
		_skyEntityManager.getSelectedMainSky(), _skyEntityManager.getSelectedMixSky(), _terrainEntityManager.getSelectedTerrain(),
		_waterEntityManager.getSelectedWater(), _modelEntityManager.getEntities(), _billboardEntityManager.getEntities(),
		_aabbEntityManager.getEntities(), _lightEntityManager.getEntities(), _imageEntityManager.getEntities(), _textEntityManager.getEntities()
	);

	// Render entities
	_masterRenderer.renderScene(&entityBus, _camera);

	// Swap GPU buffer
	_timer.startDeltaPart("bufferSwap");
	_window.swapBackBuffer();
	_timer.stopDeltaPart();
}