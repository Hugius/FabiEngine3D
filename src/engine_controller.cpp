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
						   _leftViewportController.getSettingsEditor(),
						   _leftViewportController.getSkyEditor(),
						   _leftViewportController.getTerrainEditor(),
						   _leftViewportController.getWaterEditor(),
						   _leftViewportController.getModelEditor(),
						   _leftViewportController.getBillboardEditor(),
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
	// Temporary values
	const string meshDirectoryPath = "engine\\assets\\mesh\\";
	const string textureDirectoryPath = "engine\\assets\\texture\\";
	const string fontDirectoryPath = "engine\\assets\\font\\";

	if(Config::getInst().isApplicationExported()) // Application preview
	{
		// Validate project files & directories
		if(_topViewportController.isProjectCorrupted(Tools::getRootDirectoryPath()))
		{
			Logger::throwFatalWarning("Cannot load application: missing files/directories!");
		}

		// Render color
		Tools::setRenderColor(RENDER_COLOR);

		// Load application settings
		_leftViewportController.getSettingsEditor().loadSettingsFromFile();

		// Initialize script execution
		_leftViewportController.getScriptEditor().loadScriptFiles(true);
		_leftViewportController.getScriptEditor().getScriptExecutor().load();

		// Scripting error has been thrown
		if(!_leftViewportController.getScriptEditor().getScriptExecutor().isRunning())
		{
			application_stop();
			_mustPromptOnExit = true;
		}
	}
	else // Engine preview
	{
		// Cache engine meshes
		vector<string> meshPaths;
		meshPaths.push_back(meshDirectoryPath + "camera.obj");
		meshPaths.push_back(meshDirectoryPath + "box.obj");
		meshPaths.push_back(meshDirectoryPath + "lamp.obj");
		meshPaths.push_back(meshDirectoryPath + "plane.obj");
		meshPaths.push_back(meshDirectoryPath + "speaker.obj");
		meshPaths.push_back(meshDirectoryPath + "torch.obj");
		misc_cacheMeshes(meshPaths);

		// Cache 2D engine textures
		vector<string> texturePaths2D;
		texturePaths2D.push_back(textureDirectoryPath + "box.png");
		texturePaths2D.push_back(textureDirectoryPath + "color.png");
		texturePaths2D.push_back(textureDirectoryPath + "cursor_default.png");
		texturePaths2D.push_back(textureDirectoryPath + "cursor_pointing.png");
		texturePaths2D.push_back(textureDirectoryPath + "cursor_text.png");
		texturePaths2D.push_back(textureDirectoryPath + "debug.png");
		texturePaths2D.push_back(textureDirectoryPath + "grid.png");
		texturePaths2D.push_back(textureDirectoryPath + "light_source.png");
		texturePaths2D.push_back(textureDirectoryPath + "logo.png");
		texturePaths2D.push_back(textureDirectoryPath + "minus.png");
		texturePaths2D.push_back(textureDirectoryPath + "pause.png");
		texturePaths2D.push_back(textureDirectoryPath + "plus.png");
		texturePaths2D.push_back(textureDirectoryPath + "position.png");
		texturePaths2D.push_back(textureDirectoryPath + "radius.png");
		texturePaths2D.push_back(textureDirectoryPath + "restart.png");
		texturePaths2D.push_back(textureDirectoryPath + "rotation.png");
		texturePaths2D.push_back(textureDirectoryPath + "settings.png");
		texturePaths2D.push_back(textureDirectoryPath + "shape_circle.png");
		texturePaths2D.push_back(textureDirectoryPath + "shape_square.png");
		texturePaths2D.push_back(textureDirectoryPath + "size.png");
		texturePaths2D.push_back(textureDirectoryPath + "start.png");
		texturePaths2D.push_back(textureDirectoryPath + "stop.png");
		misc_cache2dTextures(texturePaths2D);

		// Cache 3D engine textures
		array<string, 6> texturePaths3D;
		texturePaths3D[0] = string(textureDirectoryPath + "background_right.png");
		texturePaths3D[1] = string(textureDirectoryPath + "background_left.png");
		texturePaths3D[2] = string(textureDirectoryPath + "background_top.png");
		texturePaths3D[3] = string(textureDirectoryPath + "background_bottom.png");
		texturePaths3D[4] = string(textureDirectoryPath + "background_back.png");
		texturePaths3D[5] = string(textureDirectoryPath + "background_front.png");
		misc_cache3dTextures({texturePaths3D});

		// Cache engine fonts
		vector<string> fontPaths;
		fontPaths.push_back(fontDirectoryPath + "font.ttf");
		misc_cacheFonts(fontPaths);

		// Render color
		Tools::setRenderColor(RENDER_COLOR);

		// Default background
		sky_create("@@background");
		sky_setCubeMaps("@@background", texturePaths3D);

		// Custom cursor texture
		image_create("@@cursor", true);
		image_setSize("@@cursor", fvec2(CURSOR_IMAGE_SIZE, (CURSOR_IMAGE_SIZE * Tools::getWindowAspectRatio())));
		image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_default.png");
		misc_setCursorEntityID("@@cursor");
		misc_setCursorVisible(false);

		// Initialize viewport controllers
		_rightViewportController.initialize();
		_bottomViewportController.initialize();
		_topViewportController.initialize();
		_leftViewportController.initialize();

		// Enable Vsync
		misc_enableVsync();
	}
}

void EngineController::FE3D_CONTROLLER_UPDATE()
{
	if(Config::getInst().isApplicationExported()) // Application preview
	{
		if(_leftViewportController.getScriptEditor().getScriptExecutor().isRunning()) // Still running
		{
			// Update animation system
			_leftViewportController.getAnimation2dEditor().update();
			_leftViewportController.getAnimation3dEditor().update();

			// Update script execution
			_leftViewportController.getScriptEditor().getScriptExecutor().update(false);
		}
		else // Scripting error has been thrown
		{
			application_stop();
			_mustPromptOnExit = true;
		}
	}
	else // Engine preview
	{
		// Initialize main menu again if user came from another menu
		static string lastScreen = "";
		string activeScreen = _gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID();
		if(activeScreen == "main" && lastScreen != "main")
		{
			// Restore camera
			camera_reset();

			// Restore background
			sky_selectMainSky("@@background");
		}
		lastScreen = activeScreen;

		// Update background
		sky_setRotation("@@background", sky_getRotation("@@background") + 0.0025f);

		// Update custom cursor
		image_setPosition("@@cursor", Math::convertToNDC(Tools::convertFromScreenCoords(misc_getCursorPosition())));
		image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_default.png");
		image_setVisible("@@cursor", misc_isCursorInsideWindow());

		// Update GUI manager
		_gui.update();

		// Update viewport controllers
		_topViewportController.update();
		_leftViewportController.update();
		_rightViewportController.update();
		_bottomViewportController.update();
	}
}

void EngineController::FE3D_CONTROLLER_TERMINATE()
{
	if(Config::getInst().isApplicationExported()) // Application preview
	{
		// Check if script was running
		if(_leftViewportController.getScriptEditor().getScriptExecutor().isRunning())
		{
			_leftViewportController.getScriptEditor().getScriptExecutor().unload();
		}
	}
	else // Engine preview
	{

	}
}

const bool EngineController::mustPromptOnExit() const
{
	return _mustPromptOnExit;
}