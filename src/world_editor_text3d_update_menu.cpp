#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateText3dMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

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

			_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("text3dList")->deleteOptions();

			for(auto & [placedText3dId, templateText3dId] : _loadedText3dIds)
			{
				_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("text3dList")->createOption(placedText3dId, placedText3dId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplateText3dId.empty());
	}
}

void WorldEditor::_updateText3dPlacingMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3dPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("text3dList")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("empty");

				_deactivateModel();
				_deactivateText3d();
				_deactivateSound3d();
				_deactivatePointlight();
				_deactivateCaptor();

				_currentTemplateText3dId = hoveredOptionId;
				_fe3d->text3d_setVisible(_currentTemplateText3dId, true);
				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->text3d_setPosition(_currentTemplateText3dId, fvec3(0.0f));
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
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3dChoice")
	{
		for(const auto & optionId : screen->getScrollingList("text3dList")->getOptionIds())
		{
			if(!_fe3d->text3d_isExisting(optionId))
			{
				screen->getScrollingList("text3dList")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("text3dList")->getHoveredOptionId();

		if(!hoveredOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad3d();
				_deactivateSound3d();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateCaptor();

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