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
	// Main color
	misc_setMainRenderingColor(vec3(1.0f));

	// Default cube map
	string path = "Engine\\Textures\\";
	skyEntity_add("@@sky");
	skyEntity_setDiffuseMapRight("@@sky", path + "right.png");
	skyEntity_setDiffuseMapLeft("@@sky", path + "left.png");
	skyEntity_setDiffuseMapTop("@@sky", path + "top.png");
	skyEntity_setDiffuseMapBottom("@@sky", path + "bottom.png");
	skyEntity_setDiffuseMapFront("@@sky", path + "front.png");
	skyEntity_setDiffuseMapBack("@@sky", path + "back.png");
	skyEntity_select("@@sky");
	skyEntity_setLightness("@@sky", 0.75f);

	// Default bloom effect for all scenes
	gfx_enableBloom(0.98f, 0.0f, 8);

	// Default camera
	camera_load(90.0f, 0.1f, 10000.0f, vec3(0.0f));
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