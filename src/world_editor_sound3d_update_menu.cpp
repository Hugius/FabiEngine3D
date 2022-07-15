#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateSound3dMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSound3d")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentEditorSound3dId.empty())
			{
				if(_fe3d->sound3d_isStarted(_currentEditorSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentEditorSound3dId, 0);
				}

				_fe3d->model_setVisible(SPEAKER_ID, false);

				_currentEditorSound3dId = "";
			}

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3dPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3dChoice");
			_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuSound3dChoice")->getScrollingList("placedSound3ds")->deleteOptions();

			for(auto & sound3dId : _loadedSound3dIds)
			{
				_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuSound3dChoice")->getScrollingList("placedSound3ds")->createOption(sound3dId, sound3dId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentEditorSound3dId.empty(), true);
	}
}

void WorldEditor::_updateSound3dPlacingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSound3dPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3d");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("editorSound3ds")->getHoveredOptionId();

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

				_currentEditorSound3dId = hoveredOptionId;

				_fe3d->sound3d_start(_currentEditorSound3dId, -1, 0);
				_fe3d->model_setVisible(SPEAKER_ID, true);

				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->sound3d_setPosition(_currentEditorSound3dId, fvec3(0.0f));

					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
				}
			}
		}
	}
}

void WorldEditor::_updateSound3dChoosingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSound3dChoice")
	{
		for(const auto & optionId : screen->getScrollingList("placedSound3ds")->getOptionIds())
		{
			if(!_fe3d->sound3d_isExisting(optionId))
			{
				screen->getScrollingList("placedSound3ds")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("placedSound3ds")->getHoveredOptionId();

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
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound3d");

			return;
		}
	}
}