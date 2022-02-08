#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updatePointlightMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuPointlight")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_isPlacingPointlight)
			{
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);
				_isPlacingPointlight = false;
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

			_deactivateModel();
			_deactivateQuad3d();
			_deactivateSound();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateReflection();

			_isPlacingPointlight = true;
			_fe3d->model_setVisible(TEMPLATE_LAMP_ID, true);
			_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, true);
			_fe3d->misc_centerCursor();

			if(_fe3d->terrain_getSelectedId().empty())
			{
				_fe3d->pointlight_setPosition(TEMPLATE_POINTLIGHT_ID, fvec3(0.0f));
				_gui->getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui->getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui->getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlightChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("pointlightList")->deleteButtons();

			for(auto& id : _loadedPointlightIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("pointlightList")->createButton(id, id);
			}
		}

		screen->getButton("choice")->setHoverable(!_isPlacingPointlight);
	}
}

void WorldEditor::_updatePointlightChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuPointlightChoice")
	{
		for(const auto& button : screen->getScrollingList("pointlightList")->getButtons())
		{
			if(!_fe3d->pointlight_isExisting(button->getId()))
			{
				screen->getScrollingList("pointlightList")->deleteButton(button->getId());
				break;
			}
		}

		for(auto& id : _loadedPointlightIds)
		{
			if(screen->getScrollingList("pointlightList")->getButton(id)->isHovered())
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					_deactivateModel();
					_deactivateQuad3d();
					_deactivateSound();
					_deactivatePointlight();
					_deactivateSpotlight();
					_deactivateReflection();

					_activatePointlight(id);
				}
				else
				{
					_selectPointlight(id);

					_dontResetSelectedPointlight = true;
				}

				break;
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");
			return;
		}
	}
}