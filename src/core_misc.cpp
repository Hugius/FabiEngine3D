#include "core.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"
#include "tools.hpp"

void Core::_render()
{
	_renderBus->resetTriangleCount();

	_masterRenderer->renderApplication();

	_timer->startDeltaPart("bufferSwap");
	_renderWindow->swapBackBuffer();
	_timer->stopDeltaPart();
}

void Core::_prepare()
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const string meshDirectoryPath = "engine\\assets\\mesh\\";
	const string cubeMapDirectoryPath = "engine\\assets\\image\\cube_map\\";
	const string fontMapDirectoryPath = "engine\\assets\\image\\font_map\\";
	const string diffuseMapDirectoryPath = "engine\\assets\\image\\diffuse_map\\";

	if
		(
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "camera.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "box.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "lamp.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "plane.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "speaker.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "torch.obj") ||
		!Tools::isFileExisting(rootPath + cubeMapDirectoryPath + "background_back.bmp") ||
		!Tools::isFileExisting(rootPath + cubeMapDirectoryPath + "background_bottom.bmp") ||
		!Tools::isFileExisting(rootPath + cubeMapDirectoryPath + "background_front.bmp") ||
		!Tools::isFileExisting(rootPath + cubeMapDirectoryPath + "background_left.bmp") ||
		!Tools::isFileExisting(rootPath + cubeMapDirectoryPath + "background_right.bmp") ||
		!Tools::isFileExisting(rootPath + cubeMapDirectoryPath + "background_top.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "box.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "color.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "cursor_default.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "cursor_pointing.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "cursor_text.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "debug.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "grid.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "light_source.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "logo.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "minus.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "pause.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "plus.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "position.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "radius.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "restart.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "rotation.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "settings.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "shape_circle.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "shape_square.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "size.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "start.bmp") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "stop.bmp") ||
		!Tools::isFileExisting(rootPath + fontMapDirectoryPath + "font.bmp")
		)
	{
		Logger::throwFatalWarning("Directory `engine\\` is missing or corrupted!");
	}

	shared_ptr<QuadEntity> logo = make_shared<QuadEntity>("logo");
	logo->setMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	logo->setDiffuseMap(make_shared<TextureBuffer>(_imageLoader->loadImage("engine\\assets\\image\\diffuse_map\\logo.bmp"), false, false));
	logo->setCentered(true);

	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = static_cast<float>(DM.w);
	float height = static_cast<float>(DM.h);
	ivec2 logoResolution = ivec2(static_cast<int>(width * 0.4f), static_cast<int>(height * 0.2f));

	fvec3 keyingColor = fvec3(0.2f);
	if(Config::getInst().isApplicationExported())
	{
		_masterRenderer->setBackgroundColor(fvec4(0.0f));
	}
	else
	{
		_masterRenderer->setBackgroundColor(fvec4(keyingColor.r, keyingColor.g, keyingColor.b, 0.0f));
		_renderWindow->enableColorKeying(keyingColor);
		_renderWindow->setSize(logoResolution);
		_renderWindow->showWindow();
		_masterRenderer->renderLogo(logo, logoResolution);
		_renderWindow->swapBackBuffer();
	}

	_fe3d->FE3D_CONTROLLER_INIT();

	if(_isRunning)
	{
		if(!Config::getInst().isApplicationExported())
		{
			_renderWindow->disableColorKeying(keyingColor);
		}

		if(!Config::getInst().isApplicationExported() || (Config::getInst().isApplicationExported() && !_fe3d->server_isRunning()))
		{
			_renderWindow->showWindow();
			_renderWindow->setSize(Config::getInst().getWindowSize());
			if(Config::getInst().isWindowFullscreen())
			{
				_renderWindow->enableFullscreen();
			}
			if(!Config::getInst().isWindowBorderless())
			{
				_renderWindow->showBorder();
			}
			if(Config::getInst().isApplicationExported())
			{
				_renderWindow->setTitle(Config::getInst().getWindowTitle());
			}

			if(Config::getInst().isApplicationExported())
			{
				_renderWindow->setOpacity(1.0f);
			}
			else
			{
				_renderWindow->setOpacity(0.0f);
			}
		}
	}
}