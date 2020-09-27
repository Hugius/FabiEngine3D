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

	// Default cube map
	string textureFolderPath = "engine\\textures\\";
	skyEntity_add("@@defaultSky");
	skyEntity_setDiffuseMaps("@@defaultSky", { 
		textureFolderPath + "default_right.png", 
		textureFolderPath + "default_left.png", 
		textureFolderPath + "default_top.png", 
		textureFolderPath + "default_bottom.png", 
		textureFolderPath + "default_front.png", 
		textureFolderPath + "default_back.png" });
	skyEntity_select("@@defaultSky");
	skyEntity_setLightness("@@defaultSky", 0.65f);
	skyEntity_setRotationSpeed("@@defaultSky", 0.25f);

	// Editor cube map
	skyEntity_add("@@editorSky");
	skyEntity_setDiffuseMaps("@@editorSky", {
		textureFolderPath + "editor_right.png",
		textureFolderPath + "editor_left.png",
		textureFolderPath + "editor_top.png",
		textureFolderPath + "editor_bottom.png",
		textureFolderPath + "editor_front.png",
		textureFolderPath + "editor_back.png" });
	skyEntity_setLightness("@@editorSky", 0.65f);
	skyEntity_setRotationSpeed("@@editorSky", 0.25f);

	// Default camera
	float mouseSpeed = camera_getMouseSensitivity();
	camera_load(camera_getFOV(), 0.1f, 10000.0f, vec3(0.0f));
	camera_setMouseSensitivity(mouseSpeed);

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
		camera_load(camera_getFOV(), 0.1f, 100.0f, vec3(0.0f));
		skyEntity_select("@@defaultSky");
	}
	lastScreen = activeScreen;

	// 3D tools only allowed when not running game preview or editing game scripts
	if (!_topViewportController.isScriptRunning() && _gui->getViewport("left")->getWindow("main")->getActiveScreen()->getID() != "scriptEditorMenuMain")
	{
		// Only allowed if cursor in 3D window
		input_setKeyTogglingLocked(_gui->getGlobalScreen()->isFocused() || !misc_isMouseInsideViewport());

		// Update wireframe visibility
		if (input_getKeyToggled(Input::KEY_F))
		{
			misc_enableWireframeRendering();
		}
		else
		{
			misc_disableWireframeRendering();
		}

		// Update debug rendering
		if (input_getKeyToggled(Input::KEY_H))
		{
			misc_enableDebugRendering();
		}
		else
		{
			misc_disableDebugRendering();
		}
	}

	// Update custom cursor
	guiEntity_setPosition("@@cursor", misc_convertToNDC(misc_convertFromScreenCoords(misc_getMousePos())));
	guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_default.png");
	misc_isMouseInsideWindow() ? guiEntity_show("@@cursor") : guiEntity_hide("@@cursor");
}