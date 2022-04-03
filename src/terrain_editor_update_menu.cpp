#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_isCreatingTerrain = true;
			//_gui->getOverlay()->openValueForm("terrainCreate", "Create Terrain", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _loadedEntityIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("terrainList", "Edit Terrain", fvec2(-0.5f, 0.1f), ids);
			_isChoosingTerrain = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _loadedEntityIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("terrainList", "Delete Terrain", fvec2(-0.5f, 0.1f), ids);
			_isChoosingTerrain = true;
			_isDeletingTerrain = true;
		}

		if(_gui->getOverlay()->getAnswerFormId() == "back")
		{
			if(_gui->getOverlay()->isAnswerFormAccepted())
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				saveEntitiesToFile();
				unload();

				_gui->getOverlay()->closeAnswerForm();
			}
			if(_gui->getOverlay()->isAnswerFormDenied())
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				unload();

				_gui->getOverlay()->closeAnswerForm();
			}
		}
	}
}

void TerrainEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuMain");
			_gui->getOverlay()->getTextField("terrainId")->setVisible(false);
			_fe3d->terrain_setWireframed(_currentTerrainId, false);
			_fe3d->terrain_select("");
			_currentTerrainId = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseTexturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuDiffuseTexturing");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalTexturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuNormalTexturing");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blendTexturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuBlendTexturing");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuLighting");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuMiscellaneous");
		}
	}
}