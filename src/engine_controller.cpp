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
	const string meshDirectoryPath = "engine\\assets\\mesh\\";
	const string cubeMapDirectoryPath = "engine\\assets\\image\\cube_map\\";
	const string diffuseMapDirectoryPath = "engine\\assets\\image\\diffuse_map\\";
	const string fontMapDirectoryPath = "engine\\assets\\image\\font_map\\";

	if(Config::getInst().isApplicationExported())
	{
		if(_topViewportController.isProjectCorrupted(Tools::getRootDirectoryPath()))
		{
			Logger::throwFatalWarning("Cannot load application: missing files/directories!");
		}

		Tools::setRenderColor(RENDER_COLOR);

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

		vector<string> texturePaths2D;
		texturePaths2D.push_back(diffuseMapDirectoryPath + "box.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "color.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "cursor_default.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "cursor_pointing.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "cursor_text.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "debug.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "grid.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "light_source.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "logo.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "minus.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "pause.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "plus.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "position.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "radius.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "restart.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "rotation.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "settings.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "shape_circle.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "shape_square.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "size.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "start.png");
		texturePaths2D.push_back(diffuseMapDirectoryPath + "stop.png");
		texturePaths2D.push_back(fontMapDirectoryPath + "font.png");
		misc_cache2dTextures(texturePaths2D);

		array<string, 6> texturePaths3D;
		texturePaths3D[0] = string(cubeMapDirectoryPath + "background_right.png");
		texturePaths3D[1] = string(cubeMapDirectoryPath + "background_left.png");
		texturePaths3D[2] = string(cubeMapDirectoryPath + "background_top.png");
		texturePaths3D[3] = string(cubeMapDirectoryPath + "background_bottom.png");
		texturePaths3D[4] = string(cubeMapDirectoryPath + "background_back.png");
		texturePaths3D[5] = string(cubeMapDirectoryPath + "background_front.png");
		misc_cache3dTextures({texturePaths3D});

		Tools::setRenderColor(RENDER_COLOR);

		sky_create("@@background");
		sky_setCubeMaps("@@background", texturePaths3D);

		quad_create("@@cursor", true);
		quad_setSize("@@cursor", fvec2(CURSOR_QUAD_SIZE, (CURSOR_QUAD_SIZE * Tools::getWindowAspectRatio())));
		quad_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_default.png");
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
			Tools::setRenderColor(RENDER_COLOR);

			sky_selectMainSky("@@background");

			camera_reset();
		}
		lastScreen = activeScreen;

		sky_setRotation("@@background", sky_getRotation("@@background") + 0.0025f);

		quad_setPosition("@@cursor", Math::convertToNDC(Tools::convertFromScreenCoords(misc_getCursorPosition())));
		quad_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_default.png");
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