#include "left_viewport_controller.hpp"

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	ViewportController(fe3d, gui),
	_modelEditor(fe3d, gui)
{

}

void LeftViewportController::initialize()
{
	// Left-viewport: mainWindow - mainScreen
	_gui->getViewport("left")->addWindow("main", vec2(0.0f), vec2(1.9f, 2.0f), vec3(0.5f));
	_gui->getViewport("left")->getWindow("main")->addScreen("main");
	_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("modelEditor", vec2(0.0f, 0.7f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Model editor", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("worldEditor", vec2(0.0f, 0.35f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "World editor", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("placingEditor", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Placing editor", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("lightingEditor", vec2(0.0f, -0.35f), vec2(1.6f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Lighting editor", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("scriptEditor", vec2(0.0f, -0.7f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Script editor", _leftVpTextColor, _leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelManagementScreen
	_gui->getViewport("left")->getWindow("main")->addScreen("modelManagement");
	_gui->getViewport("left")->getWindow("main")->getScreen("modelManagement")->addButton("addModel", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Add model", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelManagement")->addButton("editModel", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Edit model", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelManagement")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Delete model", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Go back", _leftVpTextColor, _leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelChoiceScreen
	_gui->getViewport("left")->getWindow("main")->addScreen("modelChoice");
	_gui->getViewport("left")->getWindow("main")->getScreen("modelChoice")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), _leftVpButtonColor, _leftVpButtonHoverColor, _leftVpTextColor, _leftVpTextHoverColor, vec2(0.25f, 0.1f));
	_gui->getViewport("left")->getWindow("main")->getScreen("modelChoice")->addButton("back", vec2(0.0f, -0.9f), vec2(1.0f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Go back", _leftVpTextColor, _leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelEditingScreen
	_gui->getViewport("left")->getWindow("main")->addScreen("modelEditing");
	_gui->getViewport("left")->getWindow("main")->getScreen("modelEditing")->addButton("loadOBJ", vec2(0.0f, 0.75f), vec2(1.25f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load OBJ file", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelEditing")->addButton("loadDiffuseMap", vec2(0.0f, 0.45f), vec2(1.6f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load diffusemap", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelEditing")->addButton("loadLightMap", vec2(0.0f, 0.15f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load lightmap", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelEditing")->addButton("loadReflectionMap", vec2(0.0f, -0.15f), vec2(1.6f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load reflectmap", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelEditing")->addButton("setSize", vec2(0.0f, -0.45f), vec2(1.25f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Set size", _leftVpTextColor, _leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelEditing")->addButton("back", vec2(0.0f, -0.75f), vec2(1.0f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Go back", _leftVpTextColor, _leftVpTextHoverColor);

	// Pre-load model editor environment
	_modelEditor.load();
	_modelEditor.unload();
}

void LeftViewportController::update(float delta)
{
	// Check if LMB is pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("modelEditor")->isHovered()) // Model editor button
		{
			_modelEditor.load();
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelManagement");
		}
	}

	// Update all editors
	_modelEditor.update(delta);
}

ModelEditor& LeftViewportController::getModelEditor()
{
	return _modelEditor;
}