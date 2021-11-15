#include "left_viewport_controller.hpp"

#define TW(text) calculateTextWidth(text, CW)

using LVPC = LeftViewportController;

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	BaseViewportController(fe3d, gui),
	_skyEditor(fe3d, gui),
	_terrainEditor(fe3d, gui),
	_waterEditor(fe3d, gui),
	_modelEditor(fe3d, gui),
	_animationEditor(fe3d, gui, _modelEditor),
	_billboardEditor(fe3d, gui),
	_audioEditor(fe3d, gui),
	_worldEditor(fe3d, gui, _skyEditor, _terrainEditor, _waterEditor, _modelEditor, _animationEditor, _billboardEditor, _audioEditor),
	_scriptEditor(fe3d, gui, _skyEditor, _terrainEditor, _waterEditor, _modelEditor, _animationEditor, _billboardEditor, _audioEditor, _worldEditor),
	_settingsEditor(fe3d, gui)
{

}

void LeftViewportController::initialize()
{
	// Window
	_gui.getViewport("left")->createWindow("main", Vec2(0.0f), Vec2(1.9f, 2.0f), LVPC::FRAME_COLOR);
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: main
	auto positions = calculateButtonPositions(10, CH);
	leftWindow->createScreen("main");
	leftWindow->getScreen("main")->createButton("skyEditor", Vec2(0.0f, positions[0]), Vec2(TW("Sky Editor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("main")->createButton("terrainEditor", Vec2(0.0f, positions[1]), Vec2(TW("Terrain Editor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("main")->createButton("waterEditor", Vec2(0.0f, positions[2]), Vec2(TW("Water Editor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("main")->createButton("modelEditor", Vec2(0.0f, positions[3]), Vec2(TW("Model Editor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Model Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("main")->createButton("animationEditor", Vec2(0.0f, positions[4]), Vec2(TW("Animation Editor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("main")->createButton("billboardEditor", Vec2(0.0f, positions[5]), Vec2(TW("Billboard Editor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboard Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("main")->createButton("audioEditor", Vec2(0.0f, positions[6]), Vec2(TW("Audio Editor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Audio Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("main")->createButton("worldEditor", Vec2(0.0f, positions[7]), Vec2(TW("World Editor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "World Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("main")->createButton("scriptEditor", Vec2(0.0f, positions[8]), Vec2(TW("Script Editor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Script Editor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("main")->createButton("settingsEditor", Vec2(0.0f, positions[9]), Vec2(TW("Settings"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Settings", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Default screen
	leftWindow->setActiveScreen("main");
}

void LeftViewportController::update()
{
	// Temporary values
	auto window = _gui.getViewport("left")->getWindow("main");
	auto screen = window->getActiveScreen();

	// Screen management
	if(screen->getID() == "main")
	{
		// Button management
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("skyEditor")->isHovered())
		{
			if(_skyEditor.loadSkyEntitiesFromFile())
			{
				_skyEditor.load();
				window->setActiveScreen("skyEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("terrainEditor")->isHovered())
		{
			if(_terrainEditor.loadTerrainEntitiesFromFile())
			{
				_terrainEditor.load();
				window->setActiveScreen("terrainEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waterEditor")->isHovered())
		{
			if(_waterEditor.loadWaterEntitiesFromFile())
			{
				_waterEditor.load();
				window->setActiveScreen("waterEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("modelEditor")->isHovered())
		{
			if(_modelEditor.loadModelEntitiesFromFile())
			{
				_modelEditor.load();
				window->setActiveScreen("modelEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animationEditor")->isHovered())
		{
			if(_modelEditor.loadModelEntitiesFromFile() && _animationEditor.loadAnimationsFromFile(true))
			{
				_animationEditor.load();
				window->setActiveScreen("animationEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("billboardEditor")->isHovered())
		{
			if(_billboardEditor.loadBillboardEntitiesFromFile())
			{
				_billboardEditor.load();
				window->setActiveScreen("billboardEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("audioEditor")->isHovered())
		{
			if(_audioEditor.loadAudioEntitiesFromFile())
			{
				_audioEditor.load();
				window->setActiveScreen("audioEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("worldEditor")->isHovered())
		{
			_worldEditor.load();
			window->setActiveScreen("worldEditorMenuMain");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("scriptEditor")->isHovered())
		{
			if(_scriptEditor.loadScriptFiles(true))
			{
				_scriptEditor.load();
				window->setActiveScreen("scriptEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("settingsEditor")->isHovered())
		{
			if(_settingsEditor.loadSettingsFromFile())
			{
				_settingsEditor.load();
				window->setActiveScreen("settingsEditorMenuMain");
			}
		}
	}

	// Update all editors
	_skyEditor.update();
	_terrainEditor.update();
	_waterEditor.update();
	_modelEditor.update();
	_animationEditor.update();
	_billboardEditor.update();
	_audioEditor.update();
	_worldEditor.update();
	_scriptEditor.update();
	_settingsEditor.update();
}

SkyEditor& LeftViewportController::getSkyEditor()
{
	return _skyEditor;
}

TerrainEditor& LeftViewportController::getTerrainEditor()
{
	return _terrainEditor;
}

WaterEditor& LeftViewportController::getWaterEditor()
{
	return _waterEditor;
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

WorldEditor& LeftViewportController::getWorldEditor()
{
	return _worldEditor;
}

ScriptEditor& LeftViewportController::getScriptEditor()
{
	return _scriptEditor;
}

SettingsEditor& LeftViewportController::getSettingsEditor()
{
	return _settingsEditor;
}