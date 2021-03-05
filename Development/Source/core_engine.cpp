#include "core_engine.hpp"
#include "configuration.hpp"

#include <ctime>
#include <ratio>
#include <chrono>

void CoreEngine::_start()
{
	// Setup
	_setupApplication();
	_isRunning = true;

	// Variables
	auto previous = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	// Main game-loop
	while (_isRunning)
	{
		// Start measuring time
		auto current = std::chrono::high_resolution_clock::now();

		// Check if the delay is getting too much
		if (lag > (Config::MS_PER_UPDATE * 10.0f))
		{
			lag = Config::MS_PER_UPDATE;
		}

		// Update 144 times per second
		while (lag >= Config::MS_PER_UPDATE)
		{
			_inputHandler.f_checkInput();
			_updateApplication();
			lag -= Config::MS_PER_UPDATE;
			_timer.increasePassedFrameCount();
		}

		// Render at full speed
		_renderApplication();

		// Calculate timing values
		auto timeDifference = std::chrono::duration_cast<std::chrono::nanoseconds>(current - previous);
		_deltaTimeMS = timeDifference.count() / 1000000.0f;
		previous = current;
		lag += _deltaTimeMS;
	}

	// Finish engine controller
	_fe3d.FE3D_CONTROLLER_DESTROY();
}

void CoreEngine::_setupApplication()
{
	// Create engine logo
	shared_ptr<GuiEntity> logo = make_shared<GuiEntity>("logo");
	logo->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true, false));
	logo->setTexture(_textureLoader.getTexture2D("engine_assets\\textures\\logo.png", false, false, false));

	// Calculate logo resolution
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = float(DM.w);
	float height = float(DM.h);
	Ivec2 logoResolution = Ivec2(static_cast<int>(width * 0.4f), static_cast<int>(height * 0.2f));

	// Render logo
	Vec3 keyingColor = Vec3(0.2f);
	glClearColor(keyingColor.r, keyingColor.g, keyingColor.b, 0.0f);
	_windowManager.enableColorKeying(keyingColor);
	_windowManager.setSize(logoResolution);
	_windowManager.showWindow();
	_renderEngine.renderEngineLogo(logo, nullptr, logoResolution);
	_windowManager.swapBackBuffer();

	// Create vignettte effect
	Vec2 pos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(Config::getInst().getVpPos()));
	Vec2 size = ((Vec2(Config::getInst().getVpSize()) / Vec2(Config::getInst().getWindowSize())) * 2.0f) + Vec2(0.0f, 0.005f);
	_fe3d.guiEntity_add("@vignette", "engine_assets\\textures\\vignette.png", pos, 0.0f, size, false);

	// Initialize engine controller
	_fe3d.FE3D_CONTROLLER_INIT();

	// Hide logo
	_windowManager.disableColorKeying(keyingColor);

	// Set window properties
	_windowManager.setSize(Config::getInst().getWindowSize());
	if (Config::getInst().isWindowFullscreen())
	{
		_windowManager.enableFullscreen();
	}
	if (!Config::getInst().isWindowBorderless())
	{
		_windowManager.showBorder();
	}
	if (Config::getInst().isGameExported())
	{
		_windowManager.setTitle(Config::getInst().getWindowTitle());
	}

	// Only if in engine preview
	if (Config::getInst().isGameExported())
	{
		// No fade in
		_windowManager.setOpacity(1.0f);
	}
	else
	{
		// Start smooth window fade in
		_windowManager.setOpacity(0.0f);
	}
}

void CoreEngine::_updateApplication()
{
	// Temporary values
	static Ivec2 lastCursorPosition = _windowManager.getCursorPos();

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
		_cameraManager.update(lastCursorPosition);
		_timer.stopDeltaPart();

		// Raycast updates
		_timer.startDeltaPart("raycastUpdate");
		_rayCaster.update(_fe3d.misc_getCursorPositionRelativeToViewport());
		_timer.stopDeltaPart();

		// Collision updates
		_timer.startDeltaPart("collisionUpdate");
		_collisionResolver.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _cameraManager);
		_timer.stopDeltaPart();

		// 3D entity updates
		_timer.startDeltaPart("skyEntityUpdate");
		_skyEntityManager.update();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("waterEntityUpdate");
		_waterEntityManager.update();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("gameEntityUpdate");
		_gameEntityManager.update();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("billboardEntityUpdate");
		_billboardEntityManager.update();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("aabbEntityUpdate");
		_aabbEntityManager.update(_gameEntityManager.getEntities(), _billboardEntityManager.getEntities());
		_timer.stopDeltaPart();

		// Shadow updates
		_timer.startDeltaPart("shadowUpdate");
		_shadowManager.update(_renderBus);
		_cameraManager.updateMatrices();
		_timer.stopDeltaPart();

		// Audio updates
		_timer.startDeltaPart("audioUpdate");
		_audioPlayer.update(_cameraManager, _audioManager.getChunks(), _audioManager.getMusic());
		_timer.stopDeltaPart();
	}

	// Always update 2D logic
	_timer.startDeltaPart("guiUpdate");
	_guiEntityManager.update();
	_textEntityManager.update();
	_timer.stopDeltaPart();

	// Updates miscellaneous
	_timer.startDeltaPart("miscUpdate");
	_updateWindowFading();
	_timer.stopDeltaPart();

	// Save last cursor position
	lastCursorPosition = _windowManager.getCursorPos();
}

void CoreEngine::_renderApplication()
{
	// Reset triangle count
	_renderBus.resetTriangleCount();

	// Create bus with all entities
	EntityBus entityBus
	(
		_skyEntityManager.getSelectedMainSky(), _skyEntityManager.getSelectedMixSky(), _terrainEntityManager.getSelectedTerrain(),
		_waterEntityManager.getSelectedWater(), _gameEntityManager.getEntities(), _billboardEntityManager.getEntities(), 
		_aabbEntityManager.getEntities(), _lightEntityManager.getEntities(), _guiEntityManager.getEntities(), _textEntityManager.getEntities()
	);

	// Render entities
	_renderEngine.renderScene(&entityBus, _cameraManager);

	// Swap GPU buffer
	_timer.startDeltaPart("bufferSwap");
	_windowManager.swapBackBuffer();
	_timer.stopDeltaPart();
}