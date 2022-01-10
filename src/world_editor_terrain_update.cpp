#include "world_editor.hpp"

void WorldEditor::_updateTerrainMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuTerrain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			vector<string> terrainIDs;
			for(const auto& ID : _terrainEditor.getLoadedIDs())
			{
				if(ID[0] == '@')
				{
					terrainIDs.push_back(ID.substr(1));
				}
			}

			_gui.getOverlay()->createChoiceForm("terrainList", "Select Terrain", fvec2(0.0f, 0.1f), terrainIDs);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->terrain_delete(_currentTerrainID);
			_currentTerrainID = "";
		}

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			auto selectedButtonID = _gui.getOverlay()->checkChoiceForm("terrainList");
			if(!selectedButtonID.empty())
			{
				if(_fe3d->terrain_isExisting(selectedButtonID))
				{
					_fe3d->terrain_delete(selectedButtonID);
				}

				_currentTerrainID = selectedButtonID;
				_copyTemplateTerrain(_currentTerrainID, ("@" + selectedButtonID));
				_gui.getOverlay()->deleteChoiceForm("terrainList");
			}
			else if(_gui.getOverlay()->isChoiceFormCancelled("terrainList"))
			{
				_gui.getOverlay()->deleteChoiceForm("terrainList");
			}
		}

		_fe3d->terrain_select(_currentTerrainID);

		screen->getButton("delete")->setHoverable(!_currentTerrainID.empty());
	}
}