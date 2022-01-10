#include "world_editor.hpp"

void WorldEditor::_updateSkyMenu()
{
	auto screen = _gui->getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSky")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			vector<string> skyIDs;
			for(const auto& ID : _skyEditor->getLoadedIDs())
			{
				if(ID[0] == '@')
				{
					skyIDs.push_back(ID.substr(1));
				}
			}

			_gui->getOverlay()->createChoiceForm("skyList", "Select Sky", fvec2(0.0f, 0.1f), skyIDs);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->sky_delete(_currentSkyID);
			_currentSkyID = "";
		}

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("skyList");
			if(!selectedButtonID.empty())
			{
				if(_fe3d->sky_isExisting(selectedButtonID))
				{
					_fe3d->sky_delete(selectedButtonID);
				}

				_currentSkyID = selectedButtonID;
				_copyTemplateSky(_currentSkyID, ("@" + selectedButtonID));
				_gui->getOverlay()->deleteChoiceForm("skyList");
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled("skyList"))
			{
				_gui->getOverlay()->deleteChoiceForm("skyList");
			}
		}

		screen->getButton("delete")->setHoverable(!_currentSkyID.empty());

		_fe3d->sky_selectMainSky(_currentSkyID);
	}
}