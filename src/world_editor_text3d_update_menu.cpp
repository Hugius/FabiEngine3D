#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateText3dMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3d")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateTextId.empty())
			{
				_fe3d->text3d_setVisible(_currentTemplateTextId, false);
				_currentTemplateTextId = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3dPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3dChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("textList")->deleteOptions();

			for(auto & [placedId, templateId] : _loadedTextIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("textList")->createOption(placedId, placedId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplateTextId.empty());
	}
}

void WorldEditor::_updateText3dPlacingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3dPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("textList")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

				_deactivateModel();
				_deactivateText();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateCaptor();

				_currentTemplateTextId = hoveredOptionId;
				_fe3d->text3d_setVisible(_currentTemplateTextId, true);
				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->text3d_setPosition(_currentTemplateTextId, fvec3(0.0f));
					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				}
			}
		}
	}
}

void WorldEditor::_updateText3dChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3dChoice")
	{
		for(const auto & optionId : screen->getScrollingList("textList")->getOptionIds())
		{
			if(!_fe3d->text3d_isExisting(optionId))
			{
				screen->getScrollingList("textList")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("textList")->getHoveredOptionId();

		if(!hoveredOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateCaptor();

				_activateText(hoveredOptionId);
			}
			else
			{
				_selectText(hoveredOptionId);

				_dontResetSelectedText3d = true;
			}
		}

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");

			return;
		}
	}
}