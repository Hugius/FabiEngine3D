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

	_masterRenderer.render(&entityBus);

	_timer.startDeltaPart("bufferSwap");
	_window.swapBackBuffer();
	_timer.stopDeltaPart();
}

void Core::_prepare()
{
	const string meshDirectoryPath = "engine\\assets\\mesh\\";
	const string cubeMapDirectoryPath = "engine\\assets\\image\\cube_map\\";
	const string fontMapDirectoryPath = "engine\\assets\\image\\font_map\\";
	const string diffuseMapDirectoryPath = "engine\\assets\\image\\diffuse_map\\";

	if
		(
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "camera.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "box.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "lamp.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "plane.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "speaker.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + meshDirectoryPath + "torch.obj") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + cubeMapDirectoryPath + "background_back.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + cubeMapDirectoryPath + "background_bottom.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + cubeMapDirectoryPath + "background_front.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + cubeMapDirectoryPath + "background_left.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + cubeMapDirectoryPath + "background_right.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + cubeMapDirectoryPath + "background_top.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "box.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "color.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "cursor_default.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "cursor_pointing.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "cursor_text.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "debug.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "grid.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "light_source.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "logo.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "minus.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "pause.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "plus.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "position.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "radius.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "restart.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "rotation.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "settings.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "shape_circle.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "shape_square.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "size.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "start.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + diffuseMapDirectoryPath + "stop.png") ||
		!Tools::isFileExisting(Tools::getRootDirectoryPath() + fontMapDirectoryPath + "font.png")
		)
	{
		Logger::throwFatalWarning("Directory `engine\\` is missing or corrupted!");
	}

	shared_ptr<ImageEntity> logo = make_shared<ImageEntity>("logo");
	logo->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	logo->setDiffuseMap(_textureLoader.load2dTexture("engine\\assets\\image\\diffuse_map\\logo.png", false, false));
	logo->setCentered(true);

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
		_masterRenderer.render(logo, logoResolution);
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