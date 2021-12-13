#include "world_editor.hpp"

void WorldEditor::_updateWaterMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuWater")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			// Retrieve preview water IDs
			vector<string> waterIDs;
			for(const auto& ID : _waterEditor.getLoadedIDs())
			{
				if(ID[0] == '@')
				{
					waterIDs.push_back(ID.substr(1));
				}
			}

			// Add choice list
			_gui.getGlobalScreen()->createChoiceForm("waterList", "Select Water", fvec2(0.0f, 0.1f), waterIDs);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d.water_delete(_currentWaterID);
			_currentWaterID = "";
		}
		else if(_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("up")->isHovered())
		{
			_fe3d.water_setHeight(_currentWaterID, (_fe3d.water_getHeight(_currentWaterID) + (_editorSpeed / 100.0f)));
		}
		else if(_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("down")->isHovered())
		{
			_fe3d.water_setHeight(_currentWaterID, (_fe3d.water_getHeight(_currentWaterID) - (_editorSpeed / 100.0f)));
		}

		// Update water choosing
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("waterList");
			if(!selectedButtonID.empty())
			{
				// Delete old
				if(_fe3d.water_isExisting(selectedButtonID))
				{
					_fe3d.water_delete(selectedButtonID);
				}

				// Create new
				_currentWaterID = selectedButtonID;
				_copyPreviewWater(_currentWaterID, ("@" + selectedButtonID));
				_gui.getGlobalScreen()->deleteChoiceForm("waterList");
			}
			else if(_gui.getGlobalScreen()->isChoiceFormCancelled("waterList"))
			{
				_gui.getGlobalScreen()->deleteChoiceForm("waterList");
			}
		}

		// Update buttons hoverability
		screen->getButton("up")->setHoverable(_currentWaterID != "");
		screen->getButton("down")->setHoverable(_currentWaterID != "");
		screen->getButton("delete")->setHoverable(_currentWaterID != "");

		// Update water selection
		_fe3d.water_select(_currentWaterID);
	}
}