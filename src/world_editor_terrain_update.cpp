#include "world_editor.hpp"

void WorldEditor::_updateTerrainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuTerrain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			vector<string> terrainIds;

			for(const auto & id : _terrainEditor->getLoadedEntityIds())
			{
				if(id[0] == '@')
				{
					terrainIds.push_back(id.substr(1));
				}
			}

			_gui->getOverlay()->openChoiceForm("selectTerrain", "Select Terrain", fvec2(0.0f, 0.1f), terrainIds);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->terrain_delete(_fe3d->terrain_getSelectedId());
		}

		if((_gui->getOverlay()->getChoiceFormId() == "selectTerrain") && _gui->getOverlay()->isChoiceFormConfirmed())
		{
			const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

			_worldUtilities->copyTemplateTerrain(selectedOptionId, ("@" + selectedOptionId));

			_fe3d->terrain_select(selectedOptionId);
		}

		screen->getButton("choose")->setHoverable(_fe3d->terrain_getSelectedId().empty());
		screen->getButton("delete")->setHoverable(!_fe3d->terrain_getSelectedId().empty());
	}
}