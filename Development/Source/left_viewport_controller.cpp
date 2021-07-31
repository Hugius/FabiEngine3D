#include "left_viewport_controller.hpp"

#define CW(text) calculateTextWidth(text, 0.115f)

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
	auto positions = calculateButtonPositions(10, TH);
	_gui.getViewport("left")->addWindow("main", Vec2(0.0f), Vec2(1.9f, 2.0f), LVPC::FRAME_COLOR);
	_gui.getViewport("left")->getWindow("main")->addScreen("main");
	_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("skyEditor", Vec2(0.0f, positions[0]), Vec2(CW("Sky Editor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("terrainEditor", Vec2(0.0f, positions[1]), Vec2(CW("Terrain Editor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("waterEditor", Vec2(0.0f, positions[2]), Vec2(CW("Water Editor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("modelEditor", Vec2(0.0f, positions[3]), Vec2(CW("Model Editor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Model Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("animationEditor", Vec2(0.0f, positions[4]), Vec2(CW("Animation Editor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("billboardEditor", Vec2(0.0f, positions[5]), Vec2(CW("Billboard Editor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboard Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("audioEditor", Vec2(0.0f, positions[6]), Vec2(CW("Audio Editor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Audio Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("sceneEditor", Vec2(0.0f, positions[7]), Vec2(CW("Scene Editor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Scene Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("scriptEditor", Vec2(0.0f, positions[8]), Vec2(CW("Script Editor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Script Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->addButton("settingsEditor", Vec2(0.0f, positions[9]), Vec2(CW("Settings"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Settings", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void LeftViewportController::update()
{
	// Temporary values
	auto window = _gui.getViewport("left")->getWindow("main");
	auto screen = window->getActiveScreen();
	
	// GUI management
	if (screen->getID() == "main")
	{
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("skyEditor")->isHovered()) // Sky editor button
			{
				_environmentEditor.load();
				window->setActiveScreen("environmentEditorMenuMain");
			}
			else if (screen->getButton("terrainEditor")->isHovered()) // Terrain editor button
			{
				_environmentEditor.load();
				window->setActiveScreen("environmentEditorMenuMain");
			}
			else if (screen->getButton("waterEditor")->isHovered()) // Water editor button
			{
				_environmentEditor.load();
				window->setActiveScreen("environmentEditorMenuMain");
			}
			else if (screen->getButton("modelEditor")->isHovered()) // Model editor button
			{
				if (_modelEditor.loadModelEntitiesFromFile())
				{
					_modelEditor.load();
					window->setActiveScreen("modelEditorMenuMain");
				}
			}
			else if (screen->getButton("animationEditor")->isHovered()) // Animation editor button
			{
				if (_modelEditor.loadModelEntitiesFromFile() && _animationEditor.loadAnimationsFromFile())
				{
					_animationEditor.load();
					window->setActiveScreen("animationEditorMenuMain");
				}
			}
			else if (screen->getButton("billboardEditor")->isHovered()) // Billboard editor button
			{
				if (_billboardEditor.loadBillboardEntitiesFromFile())
				{
					_billboardEditor.load();
					window->setActiveScreen("billboardEditorMenuMain");
				}
			}
			else if (screen->getButton("audioEditor")->isHovered()) // Audio editor button
			{
				if (_audioEditor.loadAudioEntitiesFromFile())
				{
					_audioEditor.load();
					window->setActiveScreen("audioEditorMenuMain");
				}
			}
			else if (screen->getButton("sceneEditor")->isHovered()) // Scene editor button
			{
				_sceneEditor.load();
				window->setActiveScreen("sceneEditorMenuMain");
			}
			else if (screen->getButton("scriptEditor")->isHovered()) // Script editor button
			{
				if (_scriptEditor.loadScriptFiles())
				{
					_scriptEditor.load();
					window->setActiveScreen("scriptEditorMenuMain");
				}
			}
			else if (screen->getButton("settingsEditor")->isHovered()) // Settings editor button
			{
				if (_settingsEditor.loadSettingsFromFile())
				{
					_settingsEditor.load();
					window->setActiveScreen("settingsEditorMenuMain");
				}
			}
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