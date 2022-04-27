#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updatePointlightMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuPointlight")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
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
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

			_deactivateModel();
			_deactivateQuad3d();
			_deactivateSound();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateCaptor();

			_isPlacingPointlight = true;
			_fe3d->model_setVisible(TEMPLATE_LAMP_ID, true);
			_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, true);
			Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

			if(_fe3d->terrain_getSelectedId().empty())
			{
				_fe3d->pointlight_setPosition(TEMPLATE_POINTLIGHT_ID, fvec3(0.0f));
				_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlightChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("pointlightList")->deleteOptions();

			for(auto & id : _loadedPointlightIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("pointlightList")->createOption(id, id);
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
		for(const auto & optionId : screen->getScrollingList("pointlightList")->getOptionIds())
		{
			if(!_fe3d->pointlight_isExisting(optionId))
			{
				screen->getScrollingList("pointlightList")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("pointlightList")->getHoveredOptionId();

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

				_activatePointlight(hoveredOptionId);
			}
			else
			{
				_selectPointlight(hoveredOptionId);

				_dontResetSelectedPointlight = true;
			}
		}

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");

			return;
		}
	}
}