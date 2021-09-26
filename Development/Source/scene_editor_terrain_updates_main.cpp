#include "scene_editor.hpp"

void SceneEditor::_updateTerrainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuTerrain")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			// Retrieve preview terrain IDs
			vector<string> terrainIDs;
			for (const auto& ID : _terrainEditor.getLoadedTerrainIDs())
			{
				if (ID[0] == '@')
				{
					terrainIDs.push_back(ID.substr(1));
				}
			}

			// Add choice list
			_gui.getGlobalScreen()->createChoiceForm("terrainList", "Select Terrain", Vec2(0.0f, 0.1f), terrainIDs);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d.terrainEntity_delete(_currentTerrainID);
			_currentTerrainID = "";
		}

		// Update terrain choosing
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("terrainList");
			if (!selectedButtonID.empty())
			{
				// Delete old
				if (_fe3d.terrainEntity_isExisting(selectedButtonID))
				{
					_fe3d.terrainEntity_delete(selectedButtonID);
				}

				// Create new
				_currentTerrainID = selectedButtonID;
				_copyPreviewTerrain(_currentTerrainID, ("@" + selectedButtonID));
				_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList"))
			{
				_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
			}
		}

		// Update terrain selection
		_fe3d.terrainEntity_select(_currentTerrainID);

		// Update buttons hoverability
		screen->getButton("delete")->setHoverable(_currentTerrainID != "");
	}
}