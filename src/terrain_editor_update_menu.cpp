#include "terrain_editor.hpp"
#include "tools.hpp"

void TerrainEditor::_updateMainMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createTerrain", "Create Terrain", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto terrainIds = _loadedTerrainIds;

			for(auto & terrainId : terrainIds)
			{
				terrainId = terrainId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editTerrain", "Edit Terrain", LEFT_CHOICE_FORM_POSITION, terrainIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto terrainIds = _loadedTerrainIds;

			for(auto & terrainId : terrainIds)
			{
				terrainId = terrainId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteTerrain", "Delete Terrain", LEFT_CHOICE_FORM_POSITION, terrainIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveTerrainsToFile();

				unload();

				return;
			}
			else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void TerrainEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuMain");

			_gui->getOverlay()->getTextField(TERRAIN_TITLE_ID)->setVisible(false);

			_fe3d->terrain_setWireframed(_currentTerrainId, false);
			_fe3d->terrain_select("");

			_currentTerrainId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("diffuseTexturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuDiffuseTexturing");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("normalTexturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuNormalTexturing");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("blendTexturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuBlendTexturing");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuLighting");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuMiscellaneous");
		}
	}
}