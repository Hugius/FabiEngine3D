#include "left_viewport_controller.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	BaseViewportController(fe3d, gui),
	_environmentEditor(fe3d, gui),
	_modelEditor(fe3d, gui),
	_animationEditor(fe3d, gui, _modelEditor),
	_billboardEditor(fe3d, gui),
	_audioEditor(fe3d, gui),
	_sceneEditor(fe3d, gui, _environmentEditor, _modelEditor, _animationEditor, _billboardEditor, _audioEditor),
	_scriptEditor(fe3d, gui, _sceneEditor, _modelEditor, _animationEditor, _billboardEditor, _audioEditor, _environmentEditor),
	_settingsEditor(fe3d, gui)
{

}

void LeftViewportController::initialize()
{
	// Left-viewport: mainWindow - mainScreen
	_gui.getViewport("left")->addWindow("main", Vec2(0.0f), Vec2(1.9f, 2.0f), LVPC::FRAME_COLOR);
	_gui.getViewport("left")->getWindow("main")->addScreen("main");
	_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("environmentEditor", Vec2(0.0f, 0.83f), Vec2(CW("Environment"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Environment", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("modelEditor", Vec2(0.0f, 0.59f), Vec2(CW("Models"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Models", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("animationEditor", Vec2(0.0f, 0.36f), Vec2(CW("Animations"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animations", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("billboardEditor", Vec2(0.0f, 0.13f), Vec2(CW("Billboards"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboards", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("audioEditor", Vec2(0.0f, -0.13f), Vec2(CW("Audio"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("sceneEditor", Vec2(0.0f, -0.36f), Vec2(CW("3D scenes"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D scenes", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("scriptEditor", Vec2(0.0f, -0.59f), Vec2(CW("Scripting"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Scripting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("settingsEditor", Vec2(0.0f, -0.83f), Vec2(CW("Settings"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Settings", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void LeftViewportController::update()
{
	auto window = _gui.getViewport("left")->getWindow("main");
	auto screen = window->getScreen("main");

	// Check if LMB is pressed
	if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("environmentEditor")->isHovered()) // Environment editor button
		{
			_environmentEditor.load();
			window->setActiveScreen("environmentEditorMenu");
			_lastActiveEditorScreen = "environmentEditorMenu";
		}
		else if (screen->getButton("modelEditor")->isHovered()) // Model editor button
		{
			_modelEditor.load();
			window->setActiveScreen("modelEditorMenuMain");
			_lastActiveEditorScreen = "modelEditorMenuMain";
		}
		else if (screen->getButton("animationEditor")->isHovered()) // Animation editor button
		{
			_animationEditor.load();
			window->setActiveScreen("animationEditorMenuMain");
			_lastActiveEditorScreen = "animationEditorMenuMain";
		}
		else if (screen->getButton("billboardEditor")->isHovered()) // Billboard editor button
		{
			_billboardEditor.load();
			window->setActiveScreen("billboardEditorMenuMain");
			_lastActiveEditorScreen = "billboardEditorMenuMain";
		}
		else if (screen->getButton("audioEditor")->isHovered()) // Audio editor button
		{
			_audioEditor.load();
			window->setActiveScreen("audioEditorMenuMain");
			_lastActiveEditorScreen = "audioEditorMenuMain";
		}
		else if (screen->getButton("sceneEditor")->isHovered()) // Scene editor button
		{
			_sceneEditor.load();
			window->setActiveScreen("sceneEditorMenuMain");
			_lastActiveEditorScreen = "sceneEditorMenuMain";
		}
		else if (screen->getButton("scriptEditor")->isHovered()) // Script editor button
		{
			_fe3d.gfx_setMsaaQuality(16); // Maximum MSAA for text quality
			_scriptEditor.load();
			window->setActiveScreen("scriptEditorMenuMain");
			_lastActiveEditorScreen = "scriptEditorMenuMain";
		}
		else if (screen->getButton("settingsEditor")->isHovered()) // Settings editor button
		{
			_settingsEditor.load();
			window->setActiveScreen("settingsEditorMenuMain");
			_lastActiveEditorScreen = "settingsEditorMenuMain";
		}
	}

	// Update all editors
	_environmentEditor.update();
	_modelEditor.update();
	_animationEditor.update();
	_billboardEditor.update();
	_audioEditor.update();
	_sceneEditor.update();
	_scriptEditor.update();
	_settingsEditor.update();

	// Check if project is loaded
	if (!_settingsEditor.getCurrentProjectID().empty())
	{
		// Check if user got out of script editor
		if (_lastActiveEditorScreen == "scriptEditorMenuMain" && window->getActiveScreen()->getID() != "scriptEditorMenuMain")
		{
			// Reload settings (MSAA in particular)
			_settingsEditor.loadSettings();
			_lastActiveEditorScreen = "";
		}
	}
}

EnvironmentEditor& LeftViewportController::getEnvironmentEditor()
{
	return _environmentEditor;
}

ModelEditor& LeftViewportController::getModelEditor()
{
	return _modelEditor;
}

AnimationEditor& LeftViewportController::getAnimationEditor()
{
	return _animationEditor;
}

BillboardEditor& LeftViewportController::getBillboardEditor()
{
	return _billboardEditor;
}

AudioEditor& LeftViewportController::getAudioEditor()
{
	return _audioEditor;
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