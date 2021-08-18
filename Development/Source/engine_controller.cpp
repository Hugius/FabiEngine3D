#include "engine_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"

EngineController::EngineController()
	:
	FabiEngine3D(),
	_gui(*this),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_topViewportController(*this, _gui, _leftViewportController.getSkyEditor(), _leftViewportController.getTerrainEditor(), _leftViewportController.getWaterEditor(), _leftViewportController.getModelEditor(), _leftViewportController.getAnimationEditor(), _leftViewportController.getBillboardEditor(), _leftViewportController.getAudioEditor(), _leftViewportController.getSceneEditor(), _leftViewportController.getScriptEditor(), _leftViewportController.getSettingsEditor()),
	_bottomViewportController(*this, _gui, _topViewportController, _leftViewportController.getScriptEditor())
{

}

void EngineController::FE3D_CONTROLLER_INIT()
{
	if (application_isExported()) // Application preview
	{
		// Validate project files & directories
		if (_topViewportController.isProjectCorrupted(misc_getRootDirectory()))
		{
			Logger::throwWarning("Cannot load application: corrupted files/directories!");
			application_stop();
			_promptOnExit = true;
			return;
		}

		// Set title of application to run
		_leftViewportController.getSkyEditor().setCurrentProjectID(application_getTitle());
		_leftViewportController.getTerrainEditor().setCurrentProjectID(application_getTitle());
		_leftViewportController.getWaterEditor().setCurrentProjectID(application_getTitle());
		_leftViewportController.getModelEditor().setCurrentProjectID(application_getTitle());
		_leftViewportController.getAnimationEditor().setCurrentProjectID(application_getTitle());
		_leftViewportController.getBillboardEditor().setCurrentProjectID(application_getTitle());
		_leftViewportController.getAudioEditor().setCurrentProjectID(application_getTitle());
		_leftViewportController.getScriptEditor().setCurrentProjectID(application_getTitle());
		_leftViewportController.getSceneEditor().setCurrentProjectID(application_getTitle());
		_leftViewportController.getSettingsEditor().setCurrentProjectID(application_getTitle());

		// Default rendering color
		misc_setMainRenderingColor(Vec3(0.0f));

		// Load application settings
		_leftViewportController.getSettingsEditor().loadSettingsFromFile();

		// Camera
		camera_reset();

		// Initialize script execution
		_leftViewportController.getScriptEditor().loadScriptFiles();
		_leftViewportController.getScriptEditor().getScriptExecutor().load();

		// Scripting error has been thrown
		if (!_leftViewportController.getScriptEditor().getScriptExecutor().isRunning())
		{
			application_stop();
			_promptOnExit = true;
		}
	}
	else // Engine preview
	{
		// Temporary values
		const string meshDirectoryPath = "engine_assets\\meshes\\";
		const string textureDirectoryPath = "engine_assets\\textures\\";

		// Pre-load engine meshes
		vector<string> meshPaths;
		vector<string> temp;
		meshPaths.push_back(meshDirectoryPath + "cube.obj");
		meshPaths.push_back(meshDirectoryPath + "lamp.obj");
		meshPaths.push_back(meshDirectoryPath + "plane.obj");
		meshPaths.push_back(meshDirectoryPath + "speaker.obj");
		misc_cacheMeshesMultiThreaded(meshPaths, temp);

		// Pre-load 2D engine textures
		vector<string> texturePaths2D;
		texturePaths2D.push_back(textureDirectoryPath + "a.png");
		texturePaths2D.push_back(textureDirectoryPath + "b.png");
		texturePaths2D.push_back(textureDirectoryPath + "backspace.png");
		texturePaths2D.push_back(textureDirectoryPath + "c.png");
		texturePaths2D.push_back(textureDirectoryPath + "color.png");
		texturePaths2D.push_back(textureDirectoryPath + "ctrl.png");
		texturePaths2D.push_back(textureDirectoryPath + "cube.png");
		texturePaths2D.push_back(textureDirectoryPath + "cursor_default.png");
		texturePaths2D.push_back(textureDirectoryPath + "cursor_pointing.png");
		texturePaths2D.push_back(textureDirectoryPath + "cursor_text.png");
		texturePaths2D.push_back(textureDirectoryPath + "d.png");
		texturePaths2D.push_back(textureDirectoryPath + "debug.png");
		texturePaths2D.push_back(textureDirectoryPath + "down.png");
		texturePaths2D.push_back(textureDirectoryPath + "enter.png");
		texturePaths2D.push_back(textureDirectoryPath + "esc.png");
		texturePaths2D.push_back(textureDirectoryPath + "f.png");
		texturePaths2D.push_back(textureDirectoryPath + "grid.png");
		texturePaths2D.push_back(textureDirectoryPath + "h.png");
		texturePaths2D.push_back(textureDirectoryPath + "left.png");
		texturePaths2D.push_back(textureDirectoryPath + "light_source.png");
		texturePaths2D.push_back(textureDirectoryPath + "logo.png");
		texturePaths2D.push_back(textureDirectoryPath + "minus.png");
		texturePaths2D.push_back(textureDirectoryPath + "mouse.png");
		texturePaths2D.push_back(textureDirectoryPath + "mouse_left.png");
		texturePaths2D.push_back(textureDirectoryPath + "mouse_middle.png");
		texturePaths2D.push_back(textureDirectoryPath + "mouse_right.png");
		texturePaths2D.push_back(textureDirectoryPath + "p.png");
		texturePaths2D.push_back(textureDirectoryPath + "pause.png");
		texturePaths2D.push_back(textureDirectoryPath + "play.png");
		texturePaths2D.push_back(textureDirectoryPath + "plus.png");
		texturePaths2D.push_back(textureDirectoryPath + "position.png");
		texturePaths2D.push_back(textureDirectoryPath + "r.png");
		texturePaths2D.push_back(textureDirectoryPath + "radius.png");
		texturePaths2D.push_back(textureDirectoryPath + "restart.png");
		texturePaths2D.push_back(textureDirectoryPath + "right.png");
		texturePaths2D.push_back(textureDirectoryPath + "rotation.png");
		texturePaths2D.push_back(textureDirectoryPath + "s.png");
		texturePaths2D.push_back(textureDirectoryPath + "settings.png");
		texturePaths2D.push_back(textureDirectoryPath + "shape_circle.png");
		texturePaths2D.push_back(textureDirectoryPath + "shape_square.png");
		texturePaths2D.push_back(textureDirectoryPath + "shift.png");
		texturePaths2D.push_back(textureDirectoryPath + "size.png");
		texturePaths2D.push_back(textureDirectoryPath + "space.png");
		texturePaths2D.push_back(textureDirectoryPath + "stop.png");
		texturePaths2D.push_back(textureDirectoryPath + "up.png");
		texturePaths2D.push_back(textureDirectoryPath + "v.png");
		texturePaths2D.push_back(textureDirectoryPath + "w.png");
		misc_cacheTexturesMultiThreaded2D(texturePaths2D);

		// Pre-load 3D engine textures
		array<string, 6> texturePaths3D;
		texturePaths3D[0] = string(textureDirectoryPath + "background_right.png");
		texturePaths3D[1] = string(textureDirectoryPath + "background_left.png");
		texturePaths3D[2] = string(textureDirectoryPath + "background_top.png");
		texturePaths3D[3] = string(textureDirectoryPath + "background_bottom.png");
		texturePaths3D[4] = string(textureDirectoryPath + "background_back.png");
		texturePaths3D[5] = string(textureDirectoryPath + "background_front.png");
		misc_cacheTexturesMultiThreaded3D({ texturePaths3D });

		// Enable vsync
		misc_enableVsync();
		
		// Default rendering color
		misc_setMainRenderingColor(Vec3(0.0f));

		// Camera
		camera_reset();

		// Default engine background
		skyEntity_create("@@engineBackground");
		skyEntity_setDiffuseMaps("@@engineBackground", texturePaths3D);
		skyEntity_setRotationSpeed("@@engineBackground", 0.002f);

		// Custom cursor texture
		imageEntity_create("@@cursor", true);
		imageEntity_setSize("@@cursor", Vec2(0.075f, 0.075f * misc_getAspectRatio()));
		imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_default.png");
		misc_setCustomCursor("@@cursor");
		misc_setCursorVisible(false);

		// Initialize viewport controllers
		_rightViewportController.initialize();
		_bottomViewportController.initialize();
		_topViewportController.initialize();
		_leftViewportController.initialize();
	}
}

void EngineController::FE3D_CONTROLLER_UPDATE()
{
	if (application_isExported()) // Application preview
	{
		if (_leftViewportController.getScriptEditor().getScriptExecutor().isRunning()) // Still running
		{
			// Update animation system
			_leftViewportController.getAnimationEditor().update();

			// Update script execution
			_leftViewportController.getScriptEditor().getScriptExecutor().update(false);
		}
		else // Scripting error has been thrown
		{
			application_stop();
			_promptOnExit = true;
		}
	}
	else // Engine preview
	{
		// Initialize main menu again if user came from another menu
		static string lastScreen = "";
		string activeScreen = _gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID();
		if (activeScreen == "main" && lastScreen != "main")
		{
			// Restore camera
			camera_reset();

			// Restore background
			skyEntity_selectMainSky("@@engineBackground");
			skyEntity_setMixValue(0.0f);
			skyEntity_setLightness("@@engineBackground", 1.0f);
			
			// Restore Vsync
			if (!misc_isVsyncEnabled())
			{
				misc_enableVsync();
			}
		}
		lastScreen = activeScreen;

		// Update custom cursor
		imageEntity_setPosition("@@cursor", misc_convertToNDC(misc_convertFromScreenCoords(misc_getCursorPosition())));
		imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_default.png");
		imageEntity_setVisible("@@cursor", misc_isCursorInsideWindow());

		// Update GUI manager
		_gui.update();

		// Update viewport controllers
		_topViewportController.update();
		_leftViewportController.update();
		_rightViewportController.update();
		_bottomViewportController.update();
	}
}

void EngineController::FE3D_CONTROLLER_DESTROY()
{
	// Application preview
	if (application_isExported())
	{
		// Check if script was running
		if (_leftViewportController.getScriptEditor().getScriptExecutor().isRunning())
		{
			_leftViewportController.getScriptEditor().getScriptExecutor().unload();
		}
	}
}

bool EngineController::mustPromptOnExit()
{
	return _promptOnExit;
}