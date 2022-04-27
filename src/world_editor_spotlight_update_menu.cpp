#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateSpotlightMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSpotlight")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
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
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

			_deactivateModel();
			_deactivateQuad3d();
			_deactivateSound();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateCaptor();

			_isPlacingSpotlight = true;
			_fe3d->model_setVisible(TEMPLATE_TORCH_ID, true);
			_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, true);
			Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

			if(_fe3d->terrain_getSelectedId().empty())
			{
				_fe3d->spotlight_setPosition(TEMPLATE_SPOTLIGHT_ID, fvec3(0.0f));
				_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSpotlightChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSpotlightChoice")->getScrollingList("spotlightList")->deleteOptions();

			for(auto & id : _loadedSpotlightIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSpotlightChoice")->getScrollingList("spotlightList")->createOption(id, id);
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
		for(const auto & optionId : screen->getScrollingList("spotlightList")->getOptionIds())
		{
			if(!_fe3d->spotlight_isExisting(optionId))
			{
				screen->getScrollingList("spotlightList")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("spotlightList")->getHoveredOptionId();

		if(!hoveredOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad3d();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateCaptor();

				_activateSpotlight(hoveredOptionId);
			}
			else
			{
				_selectSpotlight(hoveredOptionId);

				_dontResetSelectedSpotlight = true;
			}
		}

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSpotlight");

			return;
		}
	}
}