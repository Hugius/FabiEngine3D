#include "engine_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

EngineController::EngineController()
	:
	FabiEngine3D(),
	_gui(*this),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_topViewportController(*this, _gui,
						   _leftViewportController.getSkyEditor(),
						   _leftViewportController.getTerrainEditor(),
						   _leftViewportController.getWaterEditor(),
						   _leftViewportController.getModelEditor(),
						   _leftViewportController.getBillboardEditor(),
						   _leftViewportController.getQuadEditor(),
						   _leftViewportController.getAnimation2dEditor(),
						   _leftViewportController.getAnimation3dEditor(),
						   _leftViewportController.getSoundEditor(),
						   _leftViewportController.getWorldEditor(),
						   _leftViewportController.getScriptEditor()),
	_bottomViewportController(*this, _gui, _topViewportController, _leftViewportController.getScriptEditor())
{

}

void EngineController::FE3D_CONTROLLER_INIT()
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const string meshDirectoryPath = "engine\\assets\\mesh\\";
	const string cubeMapDirectoryPath = "engine\\assets\\image\\cube_map\\";
	const string diffuseMapDirectoryPath = "engine\\assets\\image\\diffuse_map\\";
	const string fontMapDirectoryPath = "engine\\assets\\image\\font_map\\";

	if(Config::getInst().isApplicationExported())
	{
		if(_topViewportController.isProjectCorrupted(rootPath))
		{
			Logger::throwFatalWarning("Cannot load application: missing files/directories!");
		}

		misc_setBackgroundColor(RENDER_COLOR);

		_leftViewportController.getScriptEditor().loadScriptFiles(true);
		_leftViewportController.getScriptEditor().getScriptExecutor().load();

		if(!_leftViewportController.getScriptEditor().getScriptExecutor().isRunning())
		{
			application_stop();
			_mustPromptOnExit = true;
		}
	}
	else
	{
		vector<string> meshPaths;
		meshPaths.push_back(meshDirectoryPath + "camera.obj");
		meshPaths.push_back(meshDirectoryPath + "box.obj");
		meshPaths.push_back(meshDirectoryPath + "lamp.obj");
		meshPaths.push_back(meshDirectoryPath + "plane.obj");
		meshPaths.push_back(meshDirectoryPath + "speaker.obj");
		meshPaths.push_back(meshDirectoryPath + "torch.obj");
		misc_cacheMeshes(meshPaths);

		vector<string> imagePaths;
		imagePaths.push_back(cubeMapDirectoryPath + "background_right.tga");
		imagePaths.push_back(cubeMapDirectoryPath + "background_left.tga");
		imagePaths.push_back(cubeMapDirectoryPath + "background_top.tga");
		imagePaths.push_back(cubeMapDirectoryPath + "background_bottom.tga");
		imagePaths.push_back(cubeMapDirectoryPath + "background_back.tga");
		imagePaths.push_back(cubeMapDirectoryPath + "background_front.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "box.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "color.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_default.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_pointing.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_text.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "debug.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "grid.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "light_source.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "logo.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "minus.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "pause.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "plus.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "position.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "radius.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "restart.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "rotation.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "settings.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "shape_circle.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "shape_square.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "size.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "start.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "stop.tga");
		imagePaths.push_back(fontMapDirectoryPath + "font.tga");
		misc_cacheImages(imagePaths);

		misc_setBackgroundColor(RENDER_COLOR);

		sky_create("@@background");
		sky_setCubeMaps("@@background",
						{
							string(cubeMapDirectoryPath + "background_right.tga"),
							string(cubeMapDirectoryPath + "background_left.tga"),
							string(cubeMapDirectoryPath + "background_top.tga"),
							string(cubeMapDirectoryPath + "background_bottom.tga"),
							string(cubeMapDirectoryPath + "background_back.tga"),
							string(cubeMapDirectoryPath + "background_front.tga")
						});

		quad_create("@@cursor", true);
		quad_setSize("@@cursor", fvec2(CURSOR_QUAD_SIZE, (CURSOR_QUAD_SIZE * Tools::getWindowAspectRatio())));
		quad_setDiffuseMap("@@cursor", diffuseMapDirectoryPath + "cursor_default.tga");
		misc_setCursorEntityID("@@cursor");
		misc_setCursorVisible(false);

		_rightViewportController.initialize();
		_bottomViewportController.initialize();
		_topViewportController.initialize();
		_leftViewportController.initialize();

		misc_enableVsync();
	}
}

void EngineController::FE3D_CONTROLLER_UPDATE()
{
	if(Config::getInst().isApplicationExported())
	{
		if(_leftViewportController.getScriptEditor().getScriptExecutor().isRunning())
		{
			_leftViewportController.getAnimation2dEditor().update();
			_leftViewportController.getAnimation3dEditor().update();

			_leftViewportController.getScriptEditor().getScriptExecutor().update(false);
		}
		else
		{
			application_stop();
			_mustPromptOnExit = true;
		}
	}
	else
	{
		static string lastScreen = "";
		string activeScreen = _gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID();
		if(activeScreen == "main" && lastScreen != "main")
		{
			misc_setBackgroundColor(RENDER_COLOR);

			sky_selectMainSky("@@background");

			camera_reset();
		}
		lastScreen = activeScreen;

		sky_setRotation("@@background", sky_getRotation("@@background") + 0.0025f);

		quad_setPosition("@@cursor", Math::convertToNdc(Tools::convertFromScreenCoords(misc_getCursorPosition())));
		quad_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_default.tga");
		quad_setVisible("@@cursor", misc_isCursorInsideWindow());

		_gui.update();

		_topViewportController.update();
		_leftViewportController.update();
		_rightViewportController.update();
		_bottomViewportController.update();
	}
}

void EngineController::FE3D_CONTROLLER_TERMINATE()
{
	if(Config::getInst().isApplicationExported())
	{
		if(_leftViewportController.getScriptEditor().getScriptExecutor().isRunning())
		{
			_leftViewportController.getScriptEditor().getScriptExecutor().unload();
		}
	}
	else
	{

	}
}

const bool EngineController::mustPromptOnExit() const
{
	return _mustPromptOnExit;
}