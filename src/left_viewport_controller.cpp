#include "left_viewport_controller.hpp"

#define TW(text) calculateTextWidth(text, CW)

using LVPC = LeftViewportController;

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	BaseViewportController(fe3d, gui),
	_settingsEditor(fe3d, gui),
	_skyEditor(fe3d, gui),
	_terrainEditor(fe3d, gui),
	_waterEditor(fe3d, gui),
	_modelEditor(fe3d, gui),
	_billboardEditor(fe3d, gui),
	_meshAnimationEditor(fe3d, gui, _modelEditor),
	_spriteAnimationEditor(fe3d, gui),
	_audioEditor(fe3d, gui),
	_worldEditor(fe3d, gui, _skyEditor, _terrainEditor, _waterEditor, _modelEditor, _billboardEditor, _meshAnimationEditor, _audioEditor),
	_scriptEditor(fe3d, gui, _skyEditor, _terrainEditor, _waterEditor, _modelEditor, _billboardEditor, _meshAnimationEditor, _audioEditor, _worldEditor)
{

}

void LeftViewportController::initialize()
{
	// Window
	_gui.getViewport("left")->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), LVPC::FRAME_COLOR);
	auto window = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: main
	auto positions = calculateButtonPositions(11, CH);
	window->createScreen("main");
	window->getScreen("main")->createButton("settingsEditor", fvec2(0.0f, positions[0]), fvec2(TW("Settings"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Settings", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("skyEditor", fvec2(0.0f, positions[1]), fvec2(TW("Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("terrainEditor", fvec2(0.0f, positions[2]), fvec2(TW("Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("waterEditor", fvec2(0.0f, positions[3]), fvec2(TW("Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("modelEditor", fvec2(0.0f, positions[4]), fvec2(TW("Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("billboardEditor", fvec2(0.0f, positions[5]), fvec2(TW("Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("meshAnimationEditor", fvec2(0.0f, positions[6]), fvec2(TW("3D Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("spriteAnimationEditor", fvec2(0.0f, positions[7]), fvec2(TW("2D Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "2D Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("audioEditor", fvec2(0.0f, positions[8]), fvec2(TW("Audio"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("worldEditor", fvec2(0.0f, positions[9]), fvec2(TW("World"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "World", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	window->getScreen("main")->createButton("scriptEditor", fvec2(0.0f, positions[10]), fvec2(TW("Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	
	// Default screen
	window->setActiveScreen("main");
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
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("settingsEditor")->isHovered())
		{
			if(_settingsEditor.loadSettingsFromFile())
			{
				_settingsEditor.load();
				window->setActiveScreen("settingsEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("skyEditor")->isHovered())
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
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("billboardEditor")->isHovered())
		{
			if(_billboardEditor.loadBillboardEntitiesFromFile())
			{
				_billboardEditor.load();
				window->setActiveScreen("billboardEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("meshAnimationEditor")->isHovered())
		{
			if(_modelEditor.loadModelEntitiesFromFile() && _meshAnimationEditor.loadAnimationsFromFile(true))
			{
				_meshAnimationEditor.load();
				window->setActiveScreen("meshAnimationEditorMenuMain");
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("spriteAnimationEditor")->isHovered())
		{
			if(_spriteAnimationEditor.loadAnimationsFromFile(true))
			{
				_spriteAnimationEditor.load();
				window->setActiveScreen("spriteAnimationEditorMenuMain");
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
	}

	// Update all editors
	_settingsEditor.update();
	_skyEditor.update();
	_terrainEditor.update();
	_waterEditor.update();
	_modelEditor.update();
	_billboardEditor.update();
	_meshAnimationEditor.update();
	_spriteAnimationEditor.update();
	_audioEditor.update();
	_worldEditor.update();
	_scriptEditor.update();
}

SettingsEditor& LeftViewportController::getSettingsEditor()
{
	return _settingsEditor;
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

BillboardEditor& LeftViewportController::getBillboardEditor()
{
	return _billboardEditor;
}

MeshAnimationEditor& LeftViewportController::getMeshAnimationEditor()
{
	return _meshAnimationEditor;
}

SpriteAnimationEditor& LeftViewportController::getSpriteAnimationEditor()
{
	return _spriteAnimationEditor;
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