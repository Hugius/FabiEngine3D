#include "world_editor.hpp"

void WorldEditor::_updateWaterMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuWater")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			vector<string> waterIDs;
			for(const auto& ID : _waterEditor->getLoadedIDs())
			{
				if(ID[0] == '@')
				{
					waterIDs.push_back(ID.substr(1));
				}
			}

			_gui->getOverlay()->createChoiceForm("waterList", "Select Water", fvec2(0.0f, 0.1f), waterIDs);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->water_delete(_currentWaterID);
			_currentWaterID = "";
		}
		else if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("up")->isHovered())
		{
			_fe3d->water_setHeight(_currentWaterID, (_fe3d->water_getHeight(_currentWaterID) + (_editorSpeed / 100.0f)));
		}
		else if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("down")->isHovered())
		{
			_fe3d->water_setHeight(_currentWaterID, (_fe3d->water_getHeight(_currentWaterID) - (_editorSpeed / 100.0f)));
		}

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("waterList");
			if(!selectedButtonID.empty())
			{
				if(_fe3d->water_isExisting(selectedButtonID))
				{
					_fe3d->water_delete(selectedButtonID);
				}

				_currentWaterID = selectedButtonID;
				_copyTemplateWater(_currentWaterID, ("@" + selectedButtonID));
				_gui->getOverlay()->deleteChoiceForm("waterList");
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled("waterList"))
			{
				_gui->getOverlay()->deleteChoiceForm("waterList");
			}
		}

		screen->getButton("up")->setHoverable(!_currentWaterID.empty());
		screen->getButton("down")->setHoverable(!_currentWaterID.empty());
		screen->getButton("delete")->setHoverable(!_currentWaterID.empty());

		_fe3d->water_select(_currentWaterID);
	}
}