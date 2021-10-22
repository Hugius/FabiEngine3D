#include "core_engine.hpp"
#include "configuration.hpp"

#include <ctime>
#include <ratio>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

CoreEngine::CoreEngine(FabiEngine3D& fe3d)
	:
	_fe3d(fe3d),
	_libraryLoader(),
	_meshLoader(),
	_audioLoader(),
	_renderBus(),
	_collisionDetector(),
	_collisionResolver(),
	_timer(),
	_audioPlayer(),
	_inputHandler(),
	_networkServerAPI(),
	_networkClientAPI(),
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
	_rayCaster(_renderBus, _terrainEntityManager)
{

}

void CoreEngine::_start()
{
	// Error
	if (_isRunning)
	{
		Logger::throwError("Tried to start engine: already running!");
	}

	// Start running
	_isRunning = true;

	// Prepare application
	_prepareApplication();

	// Variables
	auto previous = high_resolution_clock::now();
	float lag = 0.0f;

	// Main game-loop
	while (_isRunning)
	{
		// Start measuring time
		auto current = high_resolution_clock::now();

		if (_fe3d.networkServer_isRunning()) // Process application at full speed
		{
			// Retrieve user input if not exported
			if (!Config::getInst().isApplicationExported())
			{
				_inputHandler.update();
			}

			// Update application
			_updateApplication();
			_timer.increasePassedFrameCount();

			// Render application if not exported
			if (!Config::getInst().isApplicationExported())
			{
				_renderApplication();
			}
		}
		else // Process application at fixed speed
		{
			// Calculate time delay
			lag += _deltaTimeMS;

			// Check if time delay is getting too much
			if (lag > (Config::MS_PER_UPDATE * 10.0f))
			{
				lag = Config::MS_PER_UPDATE;
			}

			// Update (roughly) 144 times per second
			while (lag >= Config::MS_PER_UPDATE)
			{
				_inputHandler.update();
				_updateApplication();
				lag -= Config::MS_PER_UPDATE;
				_timer.increasePassedFrameCount();
			}

			// Render application at full speed
			_renderApplication();
		}

		// Calculate delta time
		auto timeDifference = duration_cast<nanoseconds>(current - previous);
		_deltaTimeMS = static_cast<float>(timeDifference.count()) / 1000000.0f;
		previous = current;
	}

	// Finish engine controller
	_fe3d.FE3D_CONTROLLER_DESTROY();
}

void CoreEngine::_pause()
{
	if (_isPaused)
	{
		Logger::throwError("Tried to resume engine: already paused!");
	}

	_isPaused = true;
}

void CoreEngine::_resume()
{
	if (!_isPaused)
	{
		Logger::throwError("Tried to resume engine: not paused!");
	}

	_isPaused = false;
}

void CoreEngine::_stop()
{
	if (!_isRunning)
	{
		Logger::throwError("Tried to stop engine: not running!");
	}

	_isRunning = false;
}

void CoreEngine::_prepareApplication()
{
	// Temporary values
	const string meshDirectoryPath = "engine_assets\\meshes\\";
	const string textureDirectoryPath = "engine_assets\\textures\\";
	const string fontDirectoryPath = "engine_assets\\fonts\\";

	// Validate engine assets directory
	if
		(
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + meshDirectoryPath + "camera.obj")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + meshDirectoryPath + "cube.obj")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + meshDirectoryPath + "lamp.obj")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + meshDirectoryPath + "speaker.obj")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "a.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "b.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "backspace.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "c.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "color.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "ctrl.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "cube.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "cursor_default.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "cursor_pointing.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "cursor_text.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "d.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "debug.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "down.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "enter.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "esc.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "f.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "grid.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "h.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "left.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "light_source.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "logo.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "minus.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "mouse.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "mouse_left.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "mouse_middle.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "mouse_right.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "p.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "pause.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "play.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "plus.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "position.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "r.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "radius.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "restart.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "right.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "rotation.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "s.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "settings.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "shape_circle.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "shape_square.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "shift.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "size.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "space.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "stop.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "up.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "v.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "background_right.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "background_left.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "background_top.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "background_bottom.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "background_back.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + textureDirectoryPath + "background_front.png")) ||
			!_fe3d.misc_isFileExisting(string(_fe3d.misc_getRootDirectory() + fontDirectoryPath + "font.ttf"))
			)
	{
		Logger::throwFatalWarning("Directory `engine_assets\\` is missing or corrupted!");
	}

	// Create engine logo
	shared_ptr<ImageEntity> logo = make_shared<ImageEntity>("logo");
	logo->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	logo->setDiffuseMap(_textureLoader.getTexture2D("engine_assets\\textures\\logo.png", false, false));

	// Calculate logo resolution
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = static_cast<float>(DM.w);
	float height = static_cast<float>(DM.h);
	Ivec2 logoResolution = Ivec2(static_cast<int>(width * 0.4f), static_cast<int>(height * 0.2f));

	// Render logo
	Vec3 keyingColor = Vec3(0.2f);
	if (Config::getInst().isApplicationExported())
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

	// Check if engine is still running
	if (_isRunning)
	{
		// Hide logo
		if (!Config::getInst().isApplicationExported())
		{
			_window.disableColorKeying(keyingColor);
		}

		// Create window if necessary
		if (!Config::getInst().isApplicationExported() || (Config::getInst().isApplicationExported() && !_fe3d.networkServer_isRunning()))
		{
			// Set window properties
			_window.setSize(Config::getInst().getWindowSize());
			Config::getInst().isWindowFullscreen() ? _window.enableFullscreen() : void();
			!Config::getInst().isWindowBorderless() ? _window.showBorder() : void();
			Config::getInst().isApplicationExported() ? _window.setTitle(Config::getInst().getWindowTitle()) : void();
			_window.showWindow();

			// Only if in engine preview
			if (Config::getInst().isApplicationExported())
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
	}
}