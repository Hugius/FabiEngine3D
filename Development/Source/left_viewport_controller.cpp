#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.125f, 1.8f)

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	ViewportController(fe3d, gui),
	_environmentEditor(fe3d, gui),
	_modelEditor(fe3d, gui),
	_billboardEditor(fe3d, gui),
	_sceneEditor(fe3d, gui, _environmentEditor, _modelEditor, _billboardEditor),
	_scriptEditor(fe3d, gui, _sceneEditor),
	_audioEditor(fe3d, gui),
	_settingsEditor(fe3d, gui)
{

}

void LeftViewportController::initialize()
{
	// Left-viewport: mainWindow - mainScreen
	_gui.getViewport("left")->addWindow("main", vec2(0.0f), vec2(1.9f, 2.0f), LVPC::frameColor);
	_gui.getViewport("left")->getWindow("main")->addScreen("main");
	_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("environmentEditor", vec2(0.0f, 0.83f), vec2(GW("Environment"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Environment", LVPC::textColor, LVPC::textHoverColor);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("modelEditor", vec2(0.0f, 0.59f), vec2(GW("Models"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Models", LVPC::textColor, LVPC::textHoverColor);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("billboardEditor", vec2(0.0f, 0.36f), vec2(GW("Billboards"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Billboards", LVPC::textColor, LVPC::textHoverColor);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("sceneEditor", vec2(0.0f, 0.13f), vec2(GW("3D scenes"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "3D scenes", LVPC::textColor, LVPC::textHoverColor);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("animationEditor", vec2(0.0f, -0.13f), vec2(GW("Animations"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Animations", LVPC::textColor, LVPC::textHoverColor);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("scriptEditor", vec2(0.0f, -0.36f), vec2(GW("Scripting"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Scripting", LVPC::textColor, LVPC::textHoverColor);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("audioEditor", vec2(0.0f, -0.59f), vec2(GW("Audio"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Audio", LVPC::textColor, LVPC::textHoverColor);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("settingsEditor", vec2(0.0f, -0.83f), vec2(GW("Settings"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Settings", LVPC::textColor, LVPC::textHoverColor);
	
	// Initialize editors GUI
	_environmentEditor.initializeGUI();
	_modelEditor.initializeGUI();
	_billboardEditor.initializeGUI();
	_sceneEditor.initializeGUI();
	_scriptEditor.initializeGUI();
	_audioEditor.initializeGUI();
	_settingsEditor.initializeGUI();

	// Load settings editor (project independent)
	_settingsEditor.load();
}

void LeftViewportController::update()
{	
	auto window = _gui.getViewport("left")->getWindow("main");
	auto screen = window->getScreen("main");

	// Check if LMB is pressed
	if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("environmentEditor")->isHovered()) // Environment editor button
		{
			_environmentEditor.load();
			window->setActiveScreen("environmentEditorMenu");
		}
		else if (screen->getButton("modelEditor")->isHovered()) // Model editor button
		{
			_modelEditor.load();
			window->setActiveScreen("modelEditorMenuMain");
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
		else if (screen->getButton("animationEditor")->isHovered()) // Animation editor button
		{

		}
		else if (screen->getButton("scriptEditor")->isHovered()) // Script editor button
		{
			_scriptEditor.load();
			window->setActiveScreen("scriptEditorMenuMain");
		}
		else if (screen->getButton("audioEditor")->isHovered()) // Audio editor button
		{
			_audioEditor.load();
			window->setActiveScreen("audioEditorMenuMain");
		}
		else if (screen->getButton("settingsEditor")->isHovered()) // Settings editor button
		{
			window->setActiveScreen("settingsEditorMenuMain");
		}
	}

	// Update all editors
	_environmentEditor.update();
	_modelEditor.update();
	_billboardEditor.update();
	_sceneEditor.update();
	_scriptEditor.update();
	_audioEditor.update();
	_settingsEditor.update();
}

ModelEditor& LeftViewportController::getModelEditor()
{
	return _modelEditor;
}

EnvironmentEditor& LeftViewportController::getEnvironmentEditor()
{
	return _environmentEditor;
}

BillboardEditor& LeftViewportController::getBillboardEditor()
{
	return _billboardEditor;
}

SceneEditor& LeftViewportController::getSceneEditor()
{
	return _sceneEditor;
}

ScriptEditor& LeftViewportController::getScriptEditor()
{
	return _scriptEditor;
}

SettingsEditor& LeftViewportController::getSettingsEditor()
{
	return _settingsEditor;
}