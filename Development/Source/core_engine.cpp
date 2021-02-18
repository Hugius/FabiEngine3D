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
		if (lag > (Config::getInst().getUpdateMsPerFrame() * 10.0f))
		{
			lag = Config::getInst().getUpdateMsPerFrame();
		}

		// Update 144 times per second
		while (lag >= Config::getInst().getUpdateMsPerFrame())
		{
			_inputHandler.f_checkInput();
			_updateApplication();
			lag -= Config::getInst().getUpdateMsPerFrame();
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
	// Only if in engine preview
	if (Config::getInst().getSelectedGame().empty())
	{
		// Create engine logo
		shared_ptr<GuiEntity> logo = make_shared<GuiEntity>("logo");
		logo->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true, false));
		logo->setTexture(_textureLoader.getTexture2D("engine\\textures\\logo.png", false, false, false));

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

		// Initialize engine controller
		_fe3d.FE3D_CONTROLLER_INIT();

		// Show logo for at least 1 second
		auto start = std::chrono::high_resolution_clock::now();
		while (std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - start).count() * 1000.0f < 1000.0f) {}
		_windowManager.disableColorKeying(keyingColor);

		// Set window properties
		_windowManager.setSize(Config::getInst().getWindowSize());
		_windowManager.setOpacity(0.0f);
		if (Config::getInst().isWindowFullscreen())
		{
			_windowManager.enableFullscreen();
		}
		if (Config::getInst().isWindowBorderless())
		{
			_windowManager.hideBorder();
		}
		else
		{
			_windowManager.showBorder();
		}
	}
	else // Game preview
	{
		// Set window properties
		_windowManager.showWindow();
		_windowManager.setSize(Config::getInst().getWindowSize());
		if (Config::getInst().isWindowFullscreen())
		{
			_windowManager.enableFullscreen();
		}
		if (Config::getInst().isWindowBorderless())
		{
			_windowManager.hideBorder();
		}
		else
		{
			_windowManager.showBorder();
		}

		// Create logo
		shared_ptr<GuiEntity> logo = make_shared<GuiEntity>("logo");
		logo->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 1.0f, 0.75f, true, false));
		logo->setTexture(_textureLoader.getTexture2D("engine\\textures\\logo.png", false, false, false));

		// Create text
		shared_ptr<TextEntity> text = make_shared<TextEntity>("text");
		text->addOglBuffer(new OpenGLBuffer(-0.6f, 0.5f, 0.3f, 0.075f, true, true));
		text->setTexture(_textureLoader.getText("Created with", "engine\\fonts\\font.ttf"));

		// Play intro sound effect
		_audioManager.add2D("intro", "engine\\audio\\intro.wav");
		_audioPlayer.allocateChannels(1);
		_audioPlayer.playChunk(_audioManager.getChunk("intro"), 0, 100, false, 0);

		// Render logo (intro fade in)
		_windowManager.enableVsync();
		for (float opaqueness = 0.0f; opaqueness < 1.0f; opaqueness += 0.01f)
		{
			logo->setColor(Vec3(opaqueness));
			text->setColor(Vec3(opaqueness));
			_inputHandler.f_checkInput();
			_renderEngine.renderEngineLogo(logo, text, Config::getInst().getWindowSize());
			_windowManager.swapBackBuffer();
		}

		// Initialize engine controller
		_fe3d.FE3D_CONTROLLER_INIT();

		// Disable vsync
		_windowManager.disableVsync();
	}

	// Add vignettte
	Vec2 pos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(Config::getInst().getVpPos()));
	Vec2 size = ((Vec2(Config::getInst().getVpSize()) / Vec2(Config::getInst().getWindowSize())) * 2.0f) + Vec2(0.0f, 0.005f);
	_fe3d.guiEntity_add("@vignette", "engine\\textures\\vignette.png", pos, 0.0f, size, false);
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
	_timer.start("coreUpdate");
	_fe3d._isRaycastUpdated = false;
	_fe3d._hoveredAabbID = "";
	_fe3d.FE3D_CONTROLLER_UPDATE();
	_timer.stop();

	// Only update 3D if engine not paused
	if (!_isPaused)
	{
		// Calculate viewport position Y offset, because GUI borders are not all of the same size
		_timer.start("cameraUpdate");
		Ivec2 offset = Ivec2(Config::getInst().getVpPos().x, Config::getInst().getWindowSize().y - (Config::getInst().getVpPos().y + Config::getInst().getVpSize().y));

		// Apply Y offset to cursor position
		Vec2 relativeCursorPosition = Vec2(_windowManager.getCursorPos()) - Vec2(offset);

		// Convert fullscreen coords to viewport coords
		relativeCursorPosition = (relativeCursorPosition / Vec2(Config::getInst().getVpSize())) * Vec2(Config::getInst().getWindowSize());

		// Camera updates
		_cameraManager.update(lastCursorPosition);
		_timer.stop();

		// Raycast updates
		_timer.start("raycastUpdate");
		_rayCaster.update(Ivec2(relativeCursorPosition));
		_timer.stop();

		// Collision updates
		_timer.start("collisionUpdate");
		_collisionResolver.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _cameraManager);
		_timer.stop();

		// 3D entity updates
		_timer.start("skyEntityUpdate");
		_skyEntityManager.update();
		_timer.stop();
		_timer.start("waterEntityUpdate");
		_waterEntityManager.update();
		_timer.stop();
		_timer.start("gameEntityUpdate");
		_gameEntityManager.update();
		_timer.stop();
		_timer.start("billboardEntityUpdate");
		_billboardEntityManager.update();
		_timer.stop();
		_timer.start("aabbEntityUpdate");
		_aabbEntityManager.update(_gameEntityManager.getEntities(), _billboardEntityManager.getEntities());
		_timer.stop();

		// Shadow updates
		_timer.start("shadowUpdate");
		_shadowManager.update(_renderBus);
		_cameraManager.updateMatrices();
		_timer.stop();

		// Audio updates
		_timer.start("audioUpdate");
		_audioPlayer.update(_cameraManager, _audioManager.getChunks(), _audioManager.getMusic());
		_timer.stop();
	}

	// Always update 2D logic
	_timer.start("guiUpdate");
	_guiEntityManager.update();
	_textEntityManager.update();
	_timer.stop();

	// Updates miscellaneous
	_timer.start("miscUpdate");
	_updateWindowFading();
	_timer.stop();

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
	_timer.start("bufferSwap");
	_windowManager.swapBackBuffer();
	_timer.stop();
}