#include "engine_controller.hpp"

EngineController::EngineController() :
	_gui(make_shared<EngineGuiManager>(*this)),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_topViewportController(*this, _gui, _leftViewportController.getModelEditor(), _leftViewportController.getWorldEditor(), 
		_leftViewportController.getBillboardEditor(), _leftViewportController.getEntityPlacer()),
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
	// Main color
	misc_setMainRenderingColor(vec3(0.5f, 0.5f, 1.0f));

	// Default cube map
	string path = "Engine\\Textures\\";
	skyEntity_add("@defaultSky", { path + "right.png", path + "left.png", path + "top.png", path + "bottom.png", path + "back.png", path + "front.png" });
	skyEntity_select("@defaultSky");

	// Default bloom effect for all scenes
	gfx_enableBloom(1.0f, 0.0f, 10);
	gfx_setSkyBrightness(0.75f);

	// Default camera
	camera_load(90.0f, 0.1f, 10000.0f, vec3(0.0f), 0.0f, 0.0f);
}

void EngineController::_updateMiscellaneous()
{
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
}