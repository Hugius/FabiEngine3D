#include "left_viewport_controller.hpp"

#define GET_WIDTH(text) LVC::calcTextWidth(text, 0.125f, 1.8f)

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	ViewportController(fe3d, gui),
	_modelEditor(fe3d, gui),
	_worldEditor(fe3d, gui),
	_billboardEditor(fe3d, gui),
	_settingsEditor(fe3d, gui),
	_sceneEditor(fe3d, gui, _worldEditor, _modelEditor, _billboardEditor)
{

}

void LeftViewportController::initialize()
{
	// Left-viewport: mainWindow - mainScreen
	_gui->getViewport("left")->addWindow("main", vec2(0.0f), vec2(1.9f, 2.0f), LVC::frameColor);
	_gui->getViewport("left")->getWindow("main")->addScreen("main");
	_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("modelEditor", vec2(0.0f, 0.75f), vec2(GET_WIDTH("Model editor"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Model editor", LVC::textColor, LVC::textHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("worldEditor", vec2(0.0f, 0.45f), vec2(GET_WIDTH("World editor"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "World editor", LVC::textColor, LVC::textHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("billboardEditor", vec2(0.0f, 0.15f), vec2(GET_WIDTH("Billboard editor"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Billboard editor", LVC::textColor, LVC::textHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("sceneEditor", vec2(0.0f, -0.15f), vec2(GET_WIDTH("Scene editor"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Scene editor", LVC::textColor, LVC::textHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("scriptEditor", vec2(0.0f, -0.45f), vec2(GET_WIDTH("Script editor"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Script editor", LVC::textColor, LVC::textHoverColor);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->addButton("settingsEditor", vec2(0.0f, -0.75f), vec2(GET_WIDTH("Settings"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Settings", LVC::textColor, LVC::textHoverColor);
	
	// Initialize editors GUI
	_modelEditor.initializeGUI();
	_worldEditor.initializeGUI();
	_billboardEditor.initializeGUI();
	_sceneEditor.initializeGUI();
	_settingsEditor.initializeGUI();

	// Load settings editor (project independent)
	_settingsEditor.load();
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
			window->setActiveScreen("modelEditorMenuMain");
		}
		else if (screen->getButton("worldEditor")->isHovered()) // World editor button
		{
			_worldEditor.load();
			window->setActiveScreen("worldEditorMenu");
		}
		else if (screen->getButton("billboardEditor")->isHovered()) // Billboard editor button
		{
			_billboardEditor.load();
			window->setActiveScreen("billboardEditorMenuMain");
		}
		else if (screen->getButton("sceneEditor")->isHovered()) // Scene editor button
		{
			_sceneEditor.load();
			window->setActiveScreen("sceneEditorMenuMain");
		}
		else if (screen->getButton("settingsEditor")->isHovered()) // Settings editor button
		{
			_settingsEditor.load();
			window->setActiveScreen("settingsEditorMenuMain");
		}
	}

	// Update all editors
	_modelEditor.update();
	_worldEditor.update();
	_billboardEditor.update();
	_sceneEditor.update();
	_settingsEditor.update();
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

SceneEditor& LeftViewportController::getSceneEditor()
{
	return _sceneEditor;
}

SettingsEditor& LeftViewportController::getSettingsEditor()
{
	return _settingsEditor;
}