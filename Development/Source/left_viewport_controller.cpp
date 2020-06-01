#include "left_viewport_controller.hpp"

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	ViewportController(fe3d, gui),
	_modelEditor(fe3d, gui),
	_worldEditor(fe3d, gui),
	_billboardEditor(fe3d, gui)
{

}

void LeftViewportController::initialize()
{
	// Left-viewport: mainWindow - mainScreen
	_gui->getViewport("left")->addWindow("main", vec2(0.0f), vec2(1.9f, 2.0f), vec3(0.5f));
	_gui->getViewport("left")->getWindow("main")->addScreen("main");
	_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("modelEditor", vec2(0.0f, 0.7f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Model editor", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("worldEditor", vec2(0.0f, 0.35f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "World editor", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("billboardEditor", vec2(0.0f, 0.0f), vec2(1.6f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Billboard editor", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("entityPlacer", vec2(0.0f, -0.35f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Entity placer", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("scriptEditor", vec2(0.0f, -0.7f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Script editor", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	
	// Initialize model editor GUI
	_modelEditor.initializeGUI();
	_worldEditor.initializeGUI();
	_billboardEditor.initializeGUI();
}

void LeftViewportController::update()
{
	auto window = _gui->getViewport("left")->getWindow("main");
	auto screen = window->getScreen("main");

	// Check if LMB is pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("modelEditor")->isHovered()) // Model editor button
		{
			_modelEditor.load();
			window->setActiveScreen("modelManagement");
		}
		else if (screen->getButton("worldEditor")->isHovered()) // World editor button
		{
			_worldEditor.load();
			window->setActiveScreen("worldManagement");
		}
		else if (screen->getButton("billboardEditor")->isHovered()) // Billboard editor button
		{
			_billboardEditor.load();
			window->setActiveScreen("billboardManagement");
		}
	}

	// Update all editors
	_modelEditor.update();
	_worldEditor.update();
	_billboardEditor.update();
}

ModelEditor& LeftViewportController::getModelEditor()
{
	return _modelEditor;
}

WorldEditor& LeftViewportController::getWorldEditor()
{
	return _worldEditor;
}

BillboardEditor& LeftViewportController::getBillboardEditor()
{
	return _billboardEditor;
}
