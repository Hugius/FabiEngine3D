#include "engine_controller.hpp"

EngineController::EngineController() :
	_gui(make_shared<EngineGuiManager>(*this)),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_topViewportController(*this, _gui, _leftViewportController.getModelEditor(), _leftViewportController.getWorldEditor(), 
		_leftViewportController.getBillboardEditor(), _leftViewportController.getSceneEditor(), _leftViewportController.getScriptEditor()),
	_bottomViewportController(*this, _gui)
{

}

void EngineController::FE3D_CONTROLLER_INIT()
{
	_initializeMiscellaneous();
	_rightViewportController.initialize();
	_bottomViewportController.initialize();
	_topViewportController.initialize();
	_leftViewportController.initialize();
}

void EngineController::FE3D_CONTROLLER_UPDATE()
{
	_updateMiscellaneous();
	_gui->update();
	_topViewportController.update();
	_leftViewportController.update();
	_rightViewportController.update();
	_bottomViewportController.update();
}

void EngineController::FE3D_CONTROLLER_DESTROY()
{

}

void EngineController::_initializeMiscellaneous()
{
	// Permanent graphical effects
	misc_setMainRenderingColor(vec3(0.0f));
	gfx_enableMSAA();
	gfx_enableBloom(1.0f, 0.0f, 10);

	// Default camera
	camera_load(90.0f, 0.1f, 100.0f, vec3(0.0f));

	// Default cube map
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
	skyEntity_setLightness("@@engineBackground", 0.65f);

	// Custom cursor texture
	guiEntity_add("@@cursor", "engine\\textures\\cursor_default.png", vec2(0.0f), 0.0f, vec2(0.075f, 0.075f * misc_getAspectRatio()), true);
	misc_setCustomCursor("@@cursor");
	misc_hideCursor();
}

void EngineController::_updateMiscellaneous()
{
	// Initialize main menu again if came from different screen
	static string lastScreen = "";
	string activeScreen = _gui->getViewport("left")->getWindow("main")->getActiveScreen()->getID();
	if (activeScreen == "main" && lastScreen != "main")
	{
		camera_load(90.0f, 0.1f, 100.0f, vec3(0.0f));
		skyEntity_select("@@engineBackground");
	}
	lastScreen = activeScreen;

	// Update custom cursor
	guiEntity_setPosition("@@cursor", misc_convertToNDC(misc_convertFromScreenCoords(misc_getMousePos())));
	guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_default.png");
	misc_isMouseInsideWindow() ? guiEntity_show("@@cursor") : guiEntity_hide("@@cursor");
}