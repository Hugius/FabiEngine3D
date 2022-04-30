#include "world_editor.hpp"

void WorldEditor::_updateWaterMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuWater")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			vector<string> waterIds;

			for(const auto & waterId : _waterEditor->getLoadedWaterIds())
			{
				if(waterId[0] == '@')
				{
					waterIds.push_back(waterId.substr(1));
				}
			}

			_gui->getOverlay()->openChoiceForm("selectWater", "Select Water", fvec2(0.0f, 0.1f), waterIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->water_delete(_fe3d->water_getSelectedId());
		}
		else if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_LEFT) && screen->getButton("up")->isHovered())
		{
			_fe3d->water_setHeight(_fe3d->water_getSelectedId(), (_fe3d->water_getHeight(_fe3d->water_getSelectedId()) + (_editorSpeed / 100.0f)));
		}
		else if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_LEFT) && screen->getButton("down")->isHovered())
		{
			_fe3d->water_setHeight(_fe3d->water_getSelectedId(), (_fe3d->water_getHeight(_fe3d->water_getSelectedId()) - (_editorSpeed / 100.0f)));
		}

		if((_gui->getOverlay()->getChoiceFormId() == "selectWater") && _gui->getOverlay()->isChoiceFormConfirmed())
		{
			const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

			_worldHelper->copyTemplateWater(selectedOptionId, ("@" + selectedOptionId));

			_fe3d->water_select(selectedOptionId);
		}

		screen->getButton("choose")->setHoverable(_fe3d->water_getSelectedId().empty());
		screen->getButton("up")->setHoverable(!_fe3d->water_getSelectedId().empty());
		screen->getButton("down")->setHoverable(!_fe3d->water_getSelectedId().empty());
		screen->getButton("delete")->setHoverable(!_fe3d->water_getSelectedId().empty());
	}
}