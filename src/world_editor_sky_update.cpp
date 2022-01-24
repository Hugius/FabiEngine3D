#include "world_editor.hpp"

void WorldEditor::_updateSkyMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSky")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			vector<string> skyIds;
			for(const auto& id : _skyEditor->getLoadedIds())
			{
				if(id[0] == '@')
				{
					skyIds.push_back(id.substr(1));
				}
			}

			_gui->getOverlay()->createChoiceForm("skyList", "Select Sky", fvec2(0.0f, 0.1f), skyIds);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->sky_delete(_currentSkyId);
			_currentSkyId = "";
		}

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("skyList");

			if(!selectedButtonId.empty())
			{
				if(_fe3d->sky_isExisting(selectedButtonId))
				{
					_fe3d->sky_delete(selectedButtonId);
				}

				_currentSkyId = selectedButtonId;
				_copyTemplateSky(_currentSkyId, ("@" + selectedButtonId));
				_fe3d->sky_select(_currentSkyId);
				_gui->getOverlay()->deleteChoiceForm("skyList");
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled("skyList"))
			{
				_gui->getOverlay()->deleteChoiceForm("skyList");
			}
		}

		screen->getButton("delete")->setHoverable(!_currentSkyId.empty());
	}
}