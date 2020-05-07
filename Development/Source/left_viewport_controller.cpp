#include "left_viewport_controller.hpp"

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	ViewportController(fe3d, gui),
	_modelEditor(fe3d, gui)
{

}

void LeftViewportController::initialize()
{
	// Left-viewport: mainWindow - mainScreen
	_gui->getViewport("leftViewport")->addWindow("mainWindow", vec2(0.0f), vec2(1.9f, 2.0f), vec3(0.5f));
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("modelEditor", vec2(0.0f, 0.7f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Model editor", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("worldEditor", vec2(0.0f, 0.35f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "World editor", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("placingEditor", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Placing editor", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("lightingEditor", vec2(0.0f, -0.35f), vec2(1.6f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Lighting editor", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("scriptEditor", vec2(0.0f, -0.7f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Script editor", _leftVpTextColor, _leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelManagementScreen
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->addScreen("modelManagementScreen");
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("addModel", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Add model", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("editModel", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Edit model", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Delete model", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Go back", _leftVpTextColor, _leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelChoiceScreen
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->addScreen("modelChoiceScreen");
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), _leftVpButtonColor, _leftVpButtonHoverColor, _leftVpTextColor, _leftVpTextHoverColor, vec2(0.25f, 0.1f));
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->addButton("back", vec2(0.0f, -0.9f), vec2(1.0f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Go back", _leftVpTextColor, _leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelEditingScreen
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->addScreen("modelEditingScreen");
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadOBJ", vec2(0.0f, 0.7f), vec2(1.25f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load OBJ file", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadDiffuseMap", vec2(0.0f, 0.35f), vec2(1.6f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load diffusemap", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadLightMap", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load lightmap", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadReflectionMap", vec2(0.0f, -0.35f), vec2(1.6f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load reflectmap", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("back", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Go back", _leftVpTextColor, _leftVpTextHoverColor);
}

void LeftViewportController::update(float delta)
{
	_modelEditor.update(delta);
}