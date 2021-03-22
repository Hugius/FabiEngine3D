#include "engine_controller.hpp"

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
	if (engine_isGameExported()) // Game preview
	{
		// Set name of game (project) to run
		_leftViewportController.getEnvironmentEditor().setCurrentProjectID(engine_getGameTitle());
		_leftViewportController.getModelEditor().setCurrentProjectID(engine_getGameTitle());
		_leftViewportController.getAnimationEditor().setCurrentProjectID(engine_getGameTitle());
		_leftViewportController.getBillboardEditor().setCurrentProjectID(engine_getGameTitle());
		_leftViewportController.getAudioEditor().setCurrentProjectID(engine_getGameTitle());
		_leftViewportController.getScriptEditor().setCurrentProjectID(engine_getGameTitle());
		_leftViewportController.getSceneEditor().setCurrentProjectID(engine_getGameTitle());
		_leftViewportController.getSettingsEditor().setCurrentProjectID(engine_getGameTitle());

		// Import settings
		_leftViewportController.getSettingsEditor().loadSettings();

		// Permanent graphical effects
		gfx_enableMSAA();
		gfx_enableBloom(1.0f, 0.0f, 10);

		// Default camera
		camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f), 0, 0);
		camera_center();

		// Initialize script execution
		_leftViewportController.getScriptEditor().getScriptExecutor(false).load();
	}
	else // Engine preview
	{
		_initializeMiscellaneous();
		_rightViewportController.initialize();
		_bottomViewportController.initialize();
		_topViewportController.initialize();
		_leftViewportController.initialize();
	}
}

void EngineController::FE3D_CONTROLLER_UPDATE()
{
	if (engine_isGameExported()) // Game preview
	{
		if (_leftViewportController.getScriptEditor().getScriptExecutor(false).isRunning()) // Still running
		{
			// Update animation system
			_leftViewportController.getAnimationEditor().update();

			// Update script execution
			_leftViewportController.getScriptEditor().getScriptExecutor(false).update(false);
		}
		else // Error has been thrown
		{
			engine_stop();
			_promptOnExit = true;
		}
	}
	else // Engine preview
	{
		_updateMiscellaneous();
		_gui.update();
		_topViewportController.update();
		_leftViewportController.update();
		_rightViewportController.update();
		_bottomViewportController.update();
	}
}

void EngineController::FE3D_CONTROLLER_DESTROY()
{
	// Game preview
	if (engine_isGameExported())
	{
		// Check if script was running
		if (_leftViewportController.getScriptEditor().getScriptExecutor(false).isRunning())
		{
			_leftViewportController.getScriptEditor().getScriptExecutor(false).unload();
		}
	}
}

void EngineController::_initializeMiscellaneous()
{
	// Enable vsync
	misc_setVsync(true);

	// Permanent graphical effects
	misc_setMainRenderingColor(Vec3(0.0f));
	gfx_setMsaaQuality(16);
	gfx_enableMSAA();
	gfx_enableBloom(1.0f, 0.0f, 10);

	// Default camera
	camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f));

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
	skyEntity_select("@@engineBackground");
	skyEntity_setRotationSpeed("@@engineBackground", 0.002f);

	// Custom cursor texture
	guiEntity_add("@@cursor", "engine_assets\\textures\\cursor_default.png", Vec2(0.0f), 0.0f, Vec2(0.075f, 0.075f * misc_getAspectRatio()), true);
	misc_setCustomCursor("@@cursor");
	misc_hideCursor();
}

void EngineController::_updateMiscellaneous()
{
	// Initialize main menu again if user came from another menu
	static string lastScreen = "";
	string activeScreen = _gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID();
	if (activeScreen == "main" && lastScreen != "main")
	{
		float lastYaw = camera_getYaw();
		float lastPitch = camera_getPitch();
		camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f), lastYaw, lastPitch);
		skyEntity_select("@@engineBackground");
		skyEntity_setLightness("@@engineBackground", 0.6f);
		misc_setVsync(true);
	}
	lastScreen = activeScreen;

	// Update custom cursor
	guiEntity_setPosition("@@cursor", misc_convertToNDC(misc_convertFromScreenCoords(misc_getCursorPosition())));
	guiEntity_changeTexture("@@cursor", "engine_assets\\textures\\cursor_default.png");
	misc_isCursorInsideWindow() ? guiEntity_show("@@cursor") : guiEntity_hide("@@cursor");
}

bool EngineController::mustPromptOnExit()
{
	return _promptOnExit;
}