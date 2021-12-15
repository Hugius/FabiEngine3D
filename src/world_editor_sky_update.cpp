#include "world_editor.hpp"

void WorldEditor::_updateSkyMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSky")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			// Retrieve template sky IDs
			vector<string> skyIDs;
			for(const auto& ID : _skyEditor.getLoadedIDs())
			{
				if((ID[0] == '@') && (ID != "@@background"))
				{
					skyIDs.push_back(ID.substr(1));
				}
			}

			// Add choice list
			_gui.getOverlay()->createChoiceForm("skyList", "Select Sky", fvec2(0.0f, 0.1f), skyIDs);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d.sky_delete(_currentSkyID);
			_currentSkyID = "";
		}

		// Update sky choosing
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getOverlay()->checkChoiceForm("skyList");
			if(!selectedButtonID.empty())
			{
				// Delete old
				if(_fe3d.sky_isExisting(selectedButtonID))
				{
					_fe3d.sky_delete(selectedButtonID);
				}

				// Create new
				_currentSkyID = selectedButtonID;
				_copyTemplateSky(_currentSkyID, ("@" + selectedButtonID));
				_gui.getOverlay()->deleteChoiceForm("skyList");
			}
			else if(_gui.getOverlay()->isChoiceFormCancelled("skyList"))
			{
				_gui.getOverlay()->deleteChoiceForm("skyList");
			}
		}

		// Update buttons hoverability
		screen->getButton("delete")->setHoverable(!_currentSkyID.empty());

		// Update sky selection
		_fe3d.sky_selectMainSky(_currentSkyID);
	}
}