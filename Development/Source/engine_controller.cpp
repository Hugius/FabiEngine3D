#include "engine_controller.hpp"

EngineController::EngineController() :
	_gui(make_shared<EngineGuiManager>(*this)),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_topViewportController(*this, _gui, _leftViewportController.getModelEditor(), _leftViewportController.getWorldEditor(), 
		_leftViewportController.getBillboardEditor(), _leftViewportController.getSceneEditor()),
	_bottomViewportController(*this, _gui)
{

}

void EngineController::FE3D_CONTROLLER_INIT()
{
	_rightViewportController.initialize();
	_bottomViewportController.initialize();
	_topViewportController.initialize();
	_leftViewportController.initialize();
	_initializeMiscellaneous();
}

void EngineController::FE3D_CONTROLLER_UPDATE()
{
	_gui->update();
	_topViewportController.update();
	_leftViewportController.update();
	_rightViewportController.update();
	_bottomViewportController.update();
	_updateMiscellaneous();
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
	string textureFolderPath = "Engine\\Textures\\";
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

	// Default camera
	camera_load(90.0f, 0.1f, 10000.0f, vec3(0.0f));
}

void EngineController::_updateMiscellaneous()
{
	// Only allowed if in-game
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