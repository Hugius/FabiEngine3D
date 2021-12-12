#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "terrainEditorMenuMain")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_isCreatingTerrain = true;
			_gui.getGlobalScreen()->createValueForm("terrainCreate", "Create Terrain", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedTerrainIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("terrainList", "Edit Terrain", fvec2(0.0f, 0.1f), IDs);
			_isChoosingTerrain = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedTerrainIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("terrainList", "Delete Terrain", fvec2(0.0f, 0.1f), IDs);
			_isChoosingTerrain = true;
			_isDeletingTerrain = true;
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveTerrainEntitiesToFile();
			unload();
			return;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void TerrainEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "terrainEditorMenuChoice")
	{
		// Temporary values
		float maxHeight = _fe3d.terrain_getMaxHeight(_currentTerrainID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMain");
			_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), false);
			_fe3d.terrain_setWireframed(_currentTerrainID, false);
			_fe3d.terrain_select("");
			_currentTerrainID = "";
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxHeight")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("maxHeight", "Max Height", maxHeight, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuDiffuseMap");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blendMap")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuBlendMap");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuNormalMap");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuLighting");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMiscellaneous");
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("maxHeight", maxHeight))
		{
			_fe3d.terrain_setMaxHeight(_currentTerrainID, maxHeight);
		}
	}
}