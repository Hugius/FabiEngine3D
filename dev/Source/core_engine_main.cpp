#include "core_engine.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <ctime>
#include <ratio>
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

		if(_fe3d.networkServer_isRunning()) // Process application at full speed
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
	_fe3d.FE3D_CONTROLLER_DESTROY();
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

void CoreEngine::_prepareApplication()
{
	// Temporary values
	const string meshDirectoryPath = "engine_assets\\meshes\\";
	const string textureDirectoryPath = "engine_assets\\textures\\";
	const string fontDirectoryPath = "engine_assets\\fonts\\";

	// Validate engine assets directory
	if
		(
		!Tools::isFileExisting(string(Tools::getRootDirectory() + meshDirectoryPath + "camera.obj")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + meshDirectoryPath + "cube.obj")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + meshDirectoryPath + "lamp.obj")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + meshDirectoryPath + "plane.obj")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + meshDirectoryPath + "speaker.obj")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + meshDirectoryPath + "torch.obj")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "a.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "b.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "backspace.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "c.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "color.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "ctrl.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "cube.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "cursor_default.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "cursor_pointing.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "cursor_text.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "d.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "debug.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "down.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "enter.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "esc.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "f.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "grid.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "h.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "left.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "light_source.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "logo.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "minus.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "mouse.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "mouse_left.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "mouse_middle.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "mouse_right.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "p.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "pause.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "play.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "plus.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "position.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "r.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "radius.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "restart.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "right.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "rotation.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "s.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "settings.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "shape_circle.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "shape_square.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "shift.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "size.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "space.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "stop.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "up.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "v.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "background_right.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "background_left.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "background_top.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "background_bottom.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "background_back.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + textureDirectoryPath + "background_front.png")) ||
		!Tools::isFileExisting(string(Tools::getRootDirectory() + fontDirectoryPath + "font.ttf"))
		)
	{
		Logger::throwFatalWarning("Directory `engine_assets\\` is missing or corrupted!");
	}

	// Create engine logo
	shared_ptr<ImageEntity> logo = make_shared<ImageEntity>("logo");
	logo->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	logo->setDiffuseMap(_textureLoader.loadTexture2D("engine_assets\\textures\\logo.png", false, false));

	// Calculate logo resolution
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = static_cast<float>(DM.w);
	float height = static_cast<float>(DM.h);
	Ivec2 logoResolution = Ivec2(static_cast<int>(width * 0.4f), static_cast<int>(height * 0.2f));

	// Render logo
	Vec3 keyingColor = Vec3(0.2f);
	if(Config::getInst().isApplicationExported())
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
	if(_isRunning)
	{
		// Hide logo
		if(!Config::getInst().isApplicationExported())
		{
			_window.disableColorKeying(keyingColor);
		}

		// Create window if necessary
		if(!Config::getInst().isApplicationExported() || (Config::getInst().isApplicationExported() && !_fe3d.networkServer_isRunning()))
		{
			// Set window properties
			_window.setSize(Config::getInst().getWindowSize());
			Config::getInst().isWindowFullscreen() ? _window.enableFullscreen() : void();
			!Config::getInst().isWindowBorderless() ? _window.showBorder() : void();
			Config::getInst().isApplicationExported() ? _window.setTitle(Config::getInst().getWindowTitle()) : void();
			_window.showWindow();

			// Only if in engine preview
			if(Config::getInst().isApplicationExported())
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