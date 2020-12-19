#include "engine_controller.hpp"

EngineController::EngineController() :
	_gui(*this),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_topViewportController(*this, _gui, _leftViewportController.getEnvironmentEditor(), _leftViewportController.getModelEditor(),
		_leftViewportController.getBillboardEditor(), _leftViewportController.getSceneEditor(), _leftViewportController.getAnimationEditor(),
		_leftViewportController.getScriptEditor(), _leftViewportController.getAudioEditor()),
	_bottomViewportController(*this, _gui, _topViewportController, _leftViewportController.getScriptEditor())
{

}

EngineController::~EngineController()
{
	if (_promptOnExit)
	{
		std::cout << std::endl << "Type something to continue...";
		auto temp = _getch();
	}
}

void EngineController::FE3D_CONTROLLER_INIT()
{
	if (engine_getSelectedGame().empty()) // Engine preview
	{
		_initializeMiscellaneous();
		_rightViewportController.initialize();
		_bottomViewportController.initialize();
		_topViewportController.initialize();
		_leftViewportController.initialize();
	}
	else // Game preview
	{
		// Import settings
		_leftViewportController.getSettingsEditor().load();

		// Permanent graphical effects
		misc_setMainRenderingColor(Vec3(1.0f, 0.0f, 0.0f));
		gfx_enableMSAA();
		gfx_enableBloom(1.0f, 0.0f, 10);

		// Default camera
		camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f), 0, 0);
		camera_center();

		// Set name of game (project) to run
		_leftViewportController.getSceneEditor().setCurrentProjectName(engine_getSelectedGame());
		_leftViewportController.getModelEditor().setCurrentProjectName(engine_getSelectedGame());
		_leftViewportController.getAnimationEditor().setCurrentProjectName(engine_getSelectedGame());
		_leftViewportController.getScriptEditor().setCurrentProjectName(engine_getSelectedGame());

		// Initialize script execution
		_leftViewportController.getScriptEditor().getScriptExecutor(false).load();
	}
}

void EngineController::FE3D_CONTROLLER_UPDATE()
{
	if (engine_getSelectedGame().empty()) // Engine preview
	{
		_updateMiscellaneous();
		_gui.update();
		_topViewportController.update();
		_leftViewportController.update();
		_rightViewportController.update();
		_bottomViewportController.update();
	}
	else // Game preview
	{
		if (_leftViewportController.getScriptEditor().getScriptExecutor(false).isRunning()) // Still running
		{
			// Update animation system
			_leftViewportController.getAnimationEditor().update();

			// Update script execution
			_leftViewportController.getScriptEditor().getScriptExecutor(false).update();
		}
		else // Error has been thrown
		{
			_promptOnExit = true;
			engine_stop();
		}
	}
}

void EngineController::FE3D_CONTROLLER_DESTROY()
{

}

void EngineController::_initializeMiscellaneous()
{
	// Permanent graphical effects
	misc_setMainRenderingColor(Vec3(0.0f));
	gfx_enableMSAA();
	gfx_enableBloom(1.0f, 0.0f, 10);

	// Default camera
	camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f));

	// Default engine background
	string textureFolderPath = "engine\\textures\\";
	skyEntity_add("@@engineBackground");
	skyEntity_setDiffuseMaps("@@engineBackground", {
		textureFolderPath + "default_right.png",
		textureFolderPath + "default_left.png",
		textureFolderPath + "default_top.png",
		textureFolderPath + "default_bottom.png",
		textureFolderPath + "default_front.png",
		textureFolderPath + "default_back.png" });
	skyEntity_select("@@engineBackground");
	skyEntity_setLightness("@@engineBackground", 0.6f);
	skyEntity_setRotationSpeed("@@engineBackground", 0.005f, true);

	// Custom cursor texture
	guiEntity_add("@@cursor", "engine\\textures\\cursor_default.png", Vec2(0.0f), 0.0f, Vec2(0.075f, 0.075f * misc_getAspectRatio()), true);
	misc_setCustomCursor("@@cursor");
	misc_hideCursor();
}

void EngineController::_updateMiscellaneous()
{
	// Initialize main menu again if came from different screen
	static string lastScreen = "";
	string activeScreen = _gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID();
	if (activeScreen == "main" && lastScreen != "main")
	{
		float lastYaw = camera_getYaw();
		float lastPitch = camera_getPitch();
		camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f), lastYaw, lastPitch);
		skyEntity_select("@@engineBackground");
	}
	lastScreen = activeScreen;

	// Update custom cursor
	guiEntity_setPosition("@@cursor", misc_convertToNDC(misc_convertFromScreenCoords(misc_getCursorPosition())));
	guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_default.png");
	misc_isCursorInsideWindow() ? guiEntity_show("@@cursor") : guiEntity_hide("@@cursor");
}