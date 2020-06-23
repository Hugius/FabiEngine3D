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
		previous = current;
		lag += elapsedMS;

		// Update 144 times per second
		while (lag >= Config::getInst().getUpdateMsPerFrame())
		{
			_inputHandler.f_checkInput();
			_updateApplication();
			lag -= Config::getInst().getUpdateMsPerFrame();
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
	// Display engine intro
	GuiEntity logo;
	logo.load("logo");
	logo.addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true));
	logo.setDiffuseMap(_texLoader.getTexture("Engine\\Textures\\logo.png", true, true));
	
	// Get intro resolution
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = float(DM.w);
	float height = float(DM.h);
	ivec2 introResolution = ivec2(int(width * 0.4f), int(height * 0.3f));

	// Window properties & rendering
	vec3 keyingColor = vec3(0.01f);
	glClearColor(keyingColor.r, keyingColor.g, keyingColor.b, 0.0f);
	_windowManager.makeColorOpaque(keyingColor);
	_windowManager.setSize(introResolution);
	_windowManager.showWindow();
	_renderEngine.renderEngineIntro(&logo, introResolution);
	_windowManager.swapBackBuffer();
	
	// Show logo for at least 1 second
	auto start = std::chrono::high_resolution_clock::now();
	while (std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - start).count() * 1000.0f < 2000.0f) {}

	// Vignettte
	vec2 pos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(Config::getInst().getVpPos()));
	vec2 size = 2.0f * (vec2(Config::getInst().getVpSize()) / vec2(Config::getInst().getWindowSize())) + vec2(0.0f, 0.005f);
	_fe3d.guiEntity_add("@vignette", "Engine\\Textures\\vignette.png", pos, 0.0f, size, false);

	// Initialize engine controller
	_fe3d.FE3D_CONTROLLER_INIT();

	// Set new window properties
	_windowManager.setSize(Config::getInst().getWindowSize());
	_windowManager.showWindow();
	_windowManager.showBorder();
	_windowManager.setOpacity(1.0f);
}

void CoreEngine::_updateApplication()
{
	// Exit application
	if (_inputHandler.getKeyDown(Input::WINDOW_X_BUTTON))
	{
		_stop();
	}

	// User updates
	_fe3d.FE3D_CONTROLLER_UPDATE();

	// Camera updates
	_cameraManager.update(_windowManager);

	// Physics updates
	vec2 offset = vec2(Config::getInst().getVpPos().x, Config::getInst().getWindowSize().y - (Config::getInst().getVpPos().y + Config::getInst().getVpSize().y));
	vec2 mousePos = vec2(_windowManager.getMousePos()) - offset;
	mousePos = (mousePos / vec2(Config::getInst().getVpSize())) * vec2(Config::getInst().getWindowSize()); // Convert fullscreen coords to viewport coords
	_mousePicker.update(mousePos, _terrainEntityManager);
	_collisionResolver.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _cameraManager);

	// 3D entity updates
	_skyEntityManager.update();
	_waterEntityManager.update();
	_gameEntityManager.update();
	_billboardEntityManager.update();
	_aabbEntityManager.update(_gameEntityManager.getEntities());

	// 2D entity updates
	_guiEntityManager.update();
	_textEntityManager.update();

	// Miscellaneous updates
	_shadowManager.update(_shaderBus);
	_cameraManager.updateMatrices();
	_audioPlayer.update(_cameraManager, _audioManager.getChunks(), _audioManager.getMusic());

	// Performance profiling updates
	_updatePerformanceProfiler();
}

void CoreEngine::_renderApplication()
{
	EntityBus entityBus
	(
		_skyEntityManager.getSelectedSky(), _terrainEntityManager.getSelectedTerrain(), _waterEntityManager.getSelectedWater(),
		_gameEntityManager.getEntities(), _billboardEntityManager.getEntities(), _aabbEntityManager.getEntities(),
		_lightEntityManager.getEntities(), _guiEntityManager.getEntities(), _textEntityManager.getEntities()
	);

	// Render entities
	_renderEngine.renderScene(&entityBus, _cameraManager, _windowManager.getMousePos());

	// Swap GPU buffer
	_windowManager.swapBackBuffer();
}