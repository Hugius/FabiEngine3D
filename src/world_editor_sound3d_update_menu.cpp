#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateSound3dMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSound3d")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateSound3dId.empty())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);

				if(_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				}

				_currentTemplateSound3dId = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3dPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3dChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSound3dChoice")->getScrollingList("sound3dList")->deleteOptions();

			for(auto & [placedSound3dId, templateSound3dId] : _loadedSound3dIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSound3dChoice")->getScrollingList("sound3dList")->createOption(placedSound3dId, placedSound3dId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplateSound3dId.empty());
	}
}

void WorldEditor::_updateSound3dPlacingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSound3dPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3d");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("sound3dList")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

				_deactivateModel();
				_deactivateQuad3d();
				_deactivateSound3d();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateCaptor();

				_currentTemplateSound3dId = hoveredOptionId;
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, true);
				_fe3d->sound3d_start(_currentTemplateSound3dId, -1);
				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->sound3d_setPosition(_currentTemplateSound3dId, fvec3(0.0f));
					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				}
			}
		}
	}
}

void WorldEditor::_updateSound3dChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSound3dChoice")
	{
		for(const auto & optionId : screen->getScrollingList("sound3dList")->getOptionIds())
		{
			if(!_fe3d->sound3d_isExisting(optionId))
			{
				screen->getScrollingList("sound3dList")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("sound3dList")->getHoveredOptionId();

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

				_activateSound3d(hoveredOptionId);
			}
			else
			{
				_selectSound3d(hoveredOptionId);

				_dontResetSelectedSound3d = true;
			}
		}

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3d");

			return;
		}
	}
}