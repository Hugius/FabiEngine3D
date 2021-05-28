#include "core_engine.hpp"
#include "configuration.hpp"

#include <ctime>
#include <ratio>
#include <chrono>

CoreEngine::CoreEngine(FabiEngine3D& fe3d) :
	_fe3d(fe3d),
	_libraryLoader(),
	_window(_libraryLoader),
	_meshLoader(),
	_textureLoader(),
	_audioLoader(),
	_inputHandler(),
	_renderBus(),
	_camera(_renderBus, _window),
	_masterRenderer(_renderBus, _timer, _textureLoader),
	_skyEntityManager(_meshLoader, _textureLoader, _renderBus),
	_terrainEntityManager(_meshLoader, _textureLoader, _renderBus),
	_waterEntityManager(_meshLoader, _textureLoader, _renderBus),
	_modelEntityManager(_meshLoader, _textureLoader, _renderBus),
	_billboardEntityManager(_meshLoader, _textureLoader, _renderBus, _camera),
	_aabbEntityManager(_meshLoader, _textureLoader, _renderBus),
	_lightEntityManager(_meshLoader, _textureLoader, _renderBus),
	_imageEntityManager(_meshLoader, _textureLoader, _renderBus),
	_textEntityManager(_meshLoader, _textureLoader, _renderBus),
	_shadowGenerator(),
	_rayCaster(_renderBus, _terrainEntityManager),
	_collisionDetector(),
	_collisionResolver(_collisionDetector),
	_timer(),
	_audioManager(_audioLoader),
	_audioPlayer(),
	_networkServerTCP(),
	_networkClientTCP()
{

}

void CoreEngine::_start()
{
	// Error
	if (_isRunning)
	{
		Logger::throwWarning("Trying to start engine: already running!");
		return;
	}

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

void CoreEngine::_pause()
{
	if (_isPaused)
	{
		Logger::throwWarning("Trying to resume engine: already paused!");
		return;
	}

	_isPaused = true;
}

void CoreEngine::_resume()
{
	if (!_isPaused)
	{
		Logger::throwWarning("Trying to resume engine: not paused!");
		return;
	}

	_isPaused = false;
}

void CoreEngine::_stop()
{
	if (!_isRunning)
	{
		Logger::throwWarning("Trying to stop engine: not running!");
		return;
	}

	_isRunning = false;
}

void CoreEngine::_setupApplication()
{
	// Create engine logo
	shared_ptr<ImageEntity> logo = make_shared<ImageEntity>("logo");
	logo->addRenderBuffer(new RenderBuffer(0.0f, 0.0f, 2.0f, 2.0f, true, false));
	logo->setTexture(_textureLoader.getTexture2D("engine_assets\\textures\\logo.png", false, false, false));

	// Calculate logo resolution
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = static_cast<float>(DM.w);
	float height = static_cast<float>(DM.h);
	Ivec2 logoResolution = Ivec2(static_cast<int>(width * 0.4f), static_cast<int>(height * 0.2f));

	// Render logo
	Vec3 keyingColor = Vec3(0.2f);
	if (Config::getInst().isGameExported())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		glClearColor(keyingColor.r, keyingColor.g, keyingColor.b, 0.0f);
		_window.enableColorKeying(keyingColor);
		_window.setSize(logoResolution);
		_window.showWindow();
		_masterRenderer.renderEngineLogo(logo, nullptr, logoResolution);
		_window.swapBackBuffer();
	}

	// Initialize engine controller
	_fe3d.FE3D_CONTROLLER_INIT();

	// Hide logo
	if (!Config::getInst().isGameExported())
	{
		_window.disableColorKeying(keyingColor);
	}

	// Set window properties
	_window.setSize(Config::getInst().getWindowSize());
	Config::getInst().isWindowFullscreen() ? _window.enableFullscreen() : void();
	!Config::getInst().isWindowBorderless() ? _window.showBorder() : void();
	Config::getInst().isGameExported() ? _window.setTitle(Config::getInst().getWindowTitle()) : void();
	_window.showWindow();

	// Only if in engine preview
	if (Config::getInst().isGameExported())
	{
		// No fade in
		_window.setOpacity(1.0f);
	}
	else
	{
		// Start smooth window fade in
		_window.setOpacity(0.0f);
	}
}

void CoreEngine::_updateWindowFading()
{
	// Only if in engine preview
	if (!Config::getInst().isGameExported())
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