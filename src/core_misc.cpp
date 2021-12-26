#include "core.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"
#include "tools.hpp"

void Core::_render()
{
	_renderBus.resetTriangleCount();

	const auto mainSky = _skyEntityManager.getSelectedMainSky();
	const auto mixSky = _skyEntityManager.getSelectedMixSky();
	const auto terrain = _terrainEntityManager.getSelectedTerrain();
	const auto water = _waterEntityManager.getSelectedWater();
	const auto models = _modelEntityManager.getEntities();
	const auto billboards = _billboardEntityManager.getEntities();
	const auto AABBs = _aabbEntityManager.getEntities();
	const auto pointlights = _pointlightEntityManager.getEntities();
	const auto spotlights = _spotlightEntityManager.getEntities();
	const auto reflections = _reflectionEntityManager.getEntities();
	const auto images = _imageEntityManager.getEntities();
	const auto texts = _textEntityManager.getEntities();
	EntityBus entityBus(mainSky, mixSky, terrain, water, models, billboards, AABBs, pointlights, spotlights, reflections, images, texts);

	_masterRenderer.renderWorld(&entityBus);

	_timer.startDeltaPart("bufferSwap");
	_window.swapBackBuffer();
	_timer.stopDeltaPart();
}

void Core::_prepare()
{
	const string meshDirectoryPath = "engine\\assets\\mesh\\";
	const string textureDirectoryPath = "engine\\assets\\texture\\";
	const string fontDirectoryPath = "engine\\assets\\font\\";

	if
		(
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "camera.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "box.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "lamp.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "plane.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "speaker.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "torch.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "background_back.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "background_bottom.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "background_front.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "background_left.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "background_right.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "background_top.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "box.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "color.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "cursor_default.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "cursor_pointing.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "cursor_text.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "debug.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "grid.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "light_source.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "logo.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "minus.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "pause.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "plus.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "position.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "radius.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "restart.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "rotation.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "settings.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "shape_circle.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "shape_square.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "size.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "start.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + textureDirectoryPath + "stop.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + fontDirectoryPath + "font.ttf")
		)
	{
		Logger::throwFatalWarning("Directory `engine\\` is missing or corrupted!");
	}

	shared_ptr<ImageEntity> logo = make_shared<ImageEntity>("logo", true, make_shared<RenderBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	logo->setDiffuseMap(_textureLoader.load2dTexture("engine\\assets\\texture\\logo.png", false, false));

	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = static_cast<float>(DM.w);
	float height = static_cast<float>(DM.h);
	ivec2 logoResolution = ivec2(static_cast<int>(width * 0.4f), static_cast<int>(height * 0.2f));

	fvec3 keyingColor = fvec3(0.2f);
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

	_fe3d.FE3D_CONTROLLER_INIT();

	if(_isRunning)
	{
		if(!Config::getInst().isApplicationExported())
		{
			_window.disableColorKeying(keyingColor);
		}

		if(!Config::getInst().isApplicationExported() || (Config::getInst().isApplicationExported() && !_fe3d.server_isRunning()))
		{
			_window.showWindow();
			_window.setSize(Config::getInst().getWindowSize());
			if(Config::getInst().isWindowFullscreen())
			{
				_window.enableFullscreen();
			}
			if(!Config::getInst().isWindowBorderless())
			{
				_window.showBorder();
			}
			if(Config::getInst().isApplicationExported())
			{
				_window.setTitle(Config::getInst().getWindowTitle());
			}

			if(Config::getInst().isApplicationExported())
			{
				_window.setOpacity(1.0f);
			}
			else
			{
				_window.setOpacity(0.0f);
			}
		}
	}
}