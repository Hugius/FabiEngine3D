#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateSpotlightMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSpotlight")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_isPlacingSpotlight)
			{
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);
				_isPlacingSpotlight = false;
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

			_isPlacingSpotlight = true;
			_fe3d->model_setVisible(TEMPLATE_TORCH_ID, true);
			_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, true);
			_fe3d->misc_centerCursor();

			if(_fe3d->terrain_getSelectedId().empty())
			{
				_fe3d->spotlight_setPosition(TEMPLATE_SPOTLIGHT_ID, fvec3(0.0f));
				_gui->getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui->getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui->getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSpotlightChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSpotlightChoice")->getScrollingList("spotlightList")->deleteButtons();

			for(auto & id : _loadedSpotlightIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSpotlightChoice")->getScrollingList("spotlightList")->createButton(id, id, fvec2(0.9f, 0.1f));
			}
		}

		screen->getButton("choice")->setHoverable(!_isPlacingSpotlight);
	}
}

void WorldEditor::_updateSpotlightChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSpotlightChoice")
	{
		for(const auto & button : screen->getScrollingList("spotlightList")->getButtons())
		{
			if(!_fe3d->spotlight_isExisting(button->getId()))
			{
				screen->getScrollingList("spotlightList")->deleteButton(button->getId());
				break;
			}
		}

		for(auto & id : _loadedSpotlightIds)
		{
			if(screen->getScrollingList("spotlightList")->getButton(id)->isHovered())
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					_deactivateModel();
					_deactivateQuad3d();
					_deactivateSound();
					_deactivatePointlight();
					_deactivateSpotlight();
					_deactivateReflection();

					_activateSpotlight(id);
				}
				else
				{
					_selectSpotlight(id);

					_dontResetSelectedSpotlight = true;
				}

				break;
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSpotlight");
			return;
		}
	}
}