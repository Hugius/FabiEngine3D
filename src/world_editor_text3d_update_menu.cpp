#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateText3dMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3d")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateText3dId.empty())
			{
				_fe3d->text3d_setVisible(_currentTemplateText3dId, false);

				_currentTemplateText3dId = "";
			}

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3dPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3dChoice");
			_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("placedText3ds")->deleteOptions();

			for(auto & text3dId : _loadedText3dIds)
			{
				_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("placedText3ds")->createOption(text3dId, text3dId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplateText3dId.empty());
	}
}

void WorldEditor::_updateText3dPlacingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3dPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("templateText3ds")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("empty");

				_deactivateModel();
				_deactivateQuad3d();
				_deactivateText3d();
				_deactivateAabb();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateCaptor();
				_deactivateSound3d();

				_currentTemplateText3dId = hoveredOptionId;

				_fe3d->text3d_setVisible(_currentTemplateText3dId, true);

				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->text3d_setPosition(_currentTemplateText3dId, fvec3(0.0f));

					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
				}
			}
		}
	}
}

void WorldEditor::_updateText3dChoosingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3dChoice")
	{
		for(const auto & optionId : screen->getScrollingList("placedText3ds")->getOptionIds())
		{
			if(!_fe3d->text3d_isExisting(optionId))
			{
				screen->getScrollingList("placedText3ds")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("placedText3ds")->getHoveredOptionId();

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
				_deactivateCaptor();
				_deactivateSound3d();

				_activateText3d(hoveredOptionId);
			}
			else
			{
				_selectText3d(hoveredOptionId);

				_dontResetSelectedText3d = true;
			}
		}

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");

			return;
		}
	}
}