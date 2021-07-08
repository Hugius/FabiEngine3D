#include "engine_controller.hpp"
#include "configuration.hpp"

EngineController::EngineController() :
	FabiEngine3D(),
	_gui(*this),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_topViewportController(*this, _gui, _leftViewportController.getEnvironmentEditor(), _leftViewportController.getModelEditor(),
		_leftViewportController.getBillboardEditor(), _leftViewportController.getSceneEditor(), _leftViewportController.getAnimationEditor(),
		_leftViewportController.getScriptEditor(), _leftViewportController.getAudioEditor(), _leftViewportController.getSettingsEditor()),
	_bottomViewportController(*this, _gui, _topViewportController, _leftViewportController.getScriptEditor())
{

}

void EngineController::FE3D_CONTROLLER_INIT()
{
	if (application_isExported()) // Application preview
	{
		// Set name of application to run
		_leftViewportController.getEnvironmentEditor().setCurrentProjectID(application_getTitle());
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

		// Default camera
		camera_load(Config::DEFAULT_CAMERA_FOV, Config::DEFAULT_CAMERA_NEAR, Config::DEFAULT_CAMERA_FAR, Vec3(0.0f), 0.0f, 0.0f);

		// Initialize script execution
		_leftViewportController.getScriptEditor().loadScriptFiles(true);
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
		// Enable vsync
		misc_enableVsync();
		
		// Default rendering color
		misc_setMainRenderingColor(Vec3(0.0f));

		// Default camera
		camera_load(Config::DEFAULT_CAMERA_FOV, Config::DEFAULT_CAMERA_NEAR, Config::DEFAULT_CAMERA_FAR, Vec3(0.0f), 0.0f, 0.0f);

		// Default engine background
		string textureFolderPath = "engine_assets\\textures\\";
		skyEntity_add("@@engineBackground");
		skyEntity_setDiffuseMaps("@@engineBackground", {
			textureFolderPath + "background_right.png",
			textureFolderPath + "background_left.png",
			textureFolderPath + "background_top.png",
			textureFolderPath + "background_bottom.png",
			textureFolderPath + "background_back.png",
			textureFolderPath + "background_front.png" });
		skyEntity_setRotationSpeed("@@engineBackground", 0.002f);

		// Custom cursor texture
		imageEntity_add("@@cursor", "engine_assets\\textures\\cursor_default.png", Vec2(0.0f), 0.0f, Vec2(0.075f, 0.075f * misc_getAspectRatio()), true);
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
			float lastYaw = camera_getYaw();
			float lastPitch = camera_getPitch();
			camera_load(Config::DEFAULT_CAMERA_FOV, Config::DEFAULT_CAMERA_NEAR, Config::DEFAULT_CAMERA_FAR, Vec3(0.0f), lastYaw, lastPitch);

			// Restore background
			skyEntity_select("@@engineBackground");
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
		imageEntity_changeTexture("@@cursor", "engine_assets\\textures\\cursor_default.png");
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