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
	std::chrono::high_resolution_clock::time_point previous = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	// Main game-loop
	while (_isRunning)
	{
		// Calculate timing values
		std::chrono::high_resolution_clock::time_point current = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> timeDifference = std::chrono::duration_cast<std::chrono::duration<double>>(current - previous);
		float elapsedMS = static_cast<float>(timeDifference.count()) * 1000.0f;
		_deltaTime = elapsedMS;
		
		previous = current;
		lag += elapsedMS;

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
	}

	// Finish engine controller
	_fe3d.FE3D_CONTROLLER_DESTROY();
}

void CoreEngine::_stop()
{
	_isRunning = false;
}

void CoreEngine::_setupApplication()
{
	// Create engine logo
	shared_ptr<GuiEntity> logo = make_shared<GuiEntity>("logo");
	logo->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true, false));
	logo->setDiffuseMap(_texLoader.getTexture("engine\\textures\\logo.png", true, true));
	
	// Get logo resolution
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = float();
	float height = float(DM.h);
	Ivec2 logoResolution = Ivec2(int(width * 0.4f), int(height * 0.2f));

	// Window properties & rendering
	Vec3 keyingColor = Vec3(0.2f);
	glClearColor(keyingColor.r, keyingColor.g, keyingColor.b, 0.0f);
	_windowManager.makeColorOpaque(keyingColor);
	_windowManager.setSize(logoResolution);
	_windowManager.showWindow();
	_renderEngine.renderEngineLogo(logo, logoResolution);
	_windowManager.swapBackBuffer();
	
	// Show logo for at least 1 second
	auto start = std::chrono::high_resolution_clock::now();
	while (std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - start).count() * 1000.0f < 1000.0f) {}

	// Vignettte
	Vec2 pos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(Config::getInst().getVpPos()));
	Vec2 size = ((Vec2(Config::getInst().getVpSize()) / Vec2(Config::getInst().getWindowSize())) * 2.0f) + Vec2(0.0f, 0.005f);
	_fe3d.guiEntity_add("@vignette", "engine\\textures\\vignette.png", pos, 0.0f, size, false);

	// Initialize engine controller
	_fe3d.FE3D_CONTROLLER_INIT();

	// Set new window properties
	_windowManager.setSize(Config::getInst().getWindowSize());
	_windowManager.showWindow();
	_windowManager.showBorder();
	_windowManager.setOpacity(0.0f);
}

void CoreEngine::_updateApplication()
{
	// Exit application
	if (_inputHandler.getKeyDown(InputType::WINDOW_X_BUTTON))
	{
		_stop();
	}

	// User updates
	_fe3d.FE3D_CONTROLLER_UPDATE();

	// Camera updates
	_cameraManager.update(_windowManager);

	// Calculate viewport position Y offset, because GUI borders are not all of the same size
	Ivec2 offset = Ivec2(Config::getInst().getVpPos().x, Config::getInst().getWindowSize().y - (Config::getInst().getVpPos().y + Config::getInst().getVpSize().y));
	
	// Apply Y offset to mouse position
	Vec2 mousePos = Vec2(_windowManager.getMousePos()) - Vec2(offset);

	// Convert fullscreen coords to viewport coords
	mousePos = (mousePos / Vec2(Config::getInst().getVpSize())) * Vec2(Config::getInst().getWindowSize());
	
	// Update physics
	_mousePicker.update(Ivec2(mousePos), _terrainEntityManager);
	_collisionResolver.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _cameraManager);

	// 3D entity updates
	_skyEntityManager.update();
	_waterEntityManager.update();
	_gameEntityManager.update();
	_billboardEntityManager.update();
	_aabbEntityManager.update(_gameEntityManager.getEntities(), _billboardEntityManager.getEntities());

	// 2D entity updates
	_guiEntityManager.update();
	_textEntityManager.update();

	// Miscellaneous updates
	_shadowManager.update(_renderBus);
	_cameraManager.updateMatrices();
	_audioPlayer.update(_cameraManager, _audioManager.getChunks(), _audioManager.getMusic());

	// Miscellaneous updates
	_updateWindowFading();
}

void CoreEngine::_renderApplication()
{
	// Reset triangle count
	_renderBus.resetTriangleCount();

	// Create bus with all entities
	EntityBus entityBus
	(
		_skyEntityManager.getSelectedSky(), _terrainEntityManager.getSelectedTerrain(), _waterEntityManager.getSelectedWater(),
		_gameEntityManager.getEntities(), _billboardEntityManager.getEntities(), _aabbEntityManager.getEntities(),
		_lightEntityManager.getEntities(), _guiEntityManager.getEntities(), _textEntityManager.getEntities()
	);

	// Render entities
	_renderEngine.renderScene(&entityBus, _cameraManager);

	// Swap GPU buffer
	_timer.start("bufferSwap");
	_windowManager.swapBackBuffer();
	_timer.stop();
}