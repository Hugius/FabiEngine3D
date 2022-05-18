#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updatePointlightMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuPointlight")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplatePointlightId.empty())
			{
				_fe3d->pointlight_setVisible(_currentTemplatePointlightId, false);
				_fe3d->model_setVisible(LAMP_ID, false);

				_currentTemplatePointlightId = "";
			}

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlightPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlightChoice");
			_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("placedPointlights")->deleteOptions();

			for(auto & [placedPointlightId, templatePointlightId] : _loadedPointlightIds)
			{
				_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("placedPointlights")->createOption(placedPointlightId, placedPointlightId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplatePointlightId.empty());
	}
}

void WorldEditor::_updatePointlightPlacingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuPointlightPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("templatePointlights")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("empty");

				_deactivateModel();
				_deactivateQuad3d();
				_deactivateText3d();
				_deactivateAabb();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateSound3d();
				_deactivateCaptor();

				_currentTemplatePointlightId = hoveredOptionId;

				_fe3d->pointlight_setVisible(_currentTemplatePointlightId, true);
				_fe3d->model_setVisible(LAMP_ID, true);
				_fe3d->model_setColor(LAMP_ID, "", _fe3d->pointlight_getColor(_currentTemplatePointlightId));

				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->pointlight_setPosition(_currentTemplatePointlightId, fvec3(0.0f));

					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
				}
			}
		}
	}
}

void WorldEditor::_updatePointlightChoosingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuPointlightChoice")
	{
		for(const auto & optionId : screen->getScrollingList("placedPointlights")->getOptionIds())
		{
			if(!_fe3d->pointlight_isExisting(optionId))
			{
				screen->getScrollingList("placedPointlights")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("placedPointlights")->getHoveredOptionId();

		if(!hoveredOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad3d();
				_deactivateText3d();
				_deactivateAabb();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateSound3d();
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
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");

			return;
		}
	}
}