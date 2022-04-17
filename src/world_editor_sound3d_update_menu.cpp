#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateSoundMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSound")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateSoundId.empty())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);

				if(_fe3d->sound3d_isStarted(_currentTemplateSoundId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSoundId, 0);
				}

				_currentTemplateSoundId = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSoundPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSoundChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSoundChoice")->getScrollingList("soundList")->deleteOptions();

			for(auto & [placedId, templateId] : _loadedSoundIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSoundChoice")->getScrollingList("soundList")->createOption(placedId, placedId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplateSoundId.empty());
	}
}

void WorldEditor::_updateSoundPlacingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSoundPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound");
			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("soundList")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

				_deactivateModel();
				_deactivateQuad();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateReflection();

				_currentTemplateSoundId = hoveredOptionId;
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, true);
				_fe3d->sound3d_start(_currentTemplateSoundId, -1);
				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->sound3d_setPosition(_currentTemplateSoundId, fvec3(0.0f));
					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, fvec2(0.0f, 0.1f), 5, false, true, false);
				}
			}
		}
	}
}

void WorldEditor::_updateSoundChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSoundChoice")
	{
		for(const auto & optionId : screen->getScrollingList("soundList")->getOptionIds())
		{
			if(!_fe3d->sound3d_isExisting(optionId))
			{
				screen->getScrollingList("soundList")->deleteOption(optionId);
				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("soundList")->getHoveredOptionId();

		if(!hoveredOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad();
				_deactivateSound();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateReflection();

				_activateSound(hoveredOptionId);
			}
			else
			{
				_selectSound(hoveredOptionId);

				_dontResetSelectedSound = true;
			}
		}

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSound");
			return;
		}
	}
}