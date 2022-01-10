#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateSoundMenu()
{
	auto screen = _gui->getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSound")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSoundPlace");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSoundChoice");

			_gui->getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSoundChoice")->getScrollingList("sounds")->deleteButtons();

			auto IDs = _fe3d->sound3d_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& soundID : IDs)
			{
				if(soundID[0] != '@')
				{
					reverse(soundID.begin(), soundID.end());
					string rawID = soundID.substr(soundID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(soundID.begin(), soundID.end());

					_gui->getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSoundChoice")->getScrollingList("sounds")->createButton(soundID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateSoundPlacingMenu()
{
	auto screen = _gui->getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSoundPlace")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateSoundID.empty())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);

				if(_fe3d->sound3d_isStarted(_currentTemplateSoundID))
				{
					_fe3d->sound3d_stop(_currentTemplateSoundID, 0);
				}

				_fe3d->text_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityID(), false);
				_currentTemplateSoundID = "";
			}

			_gui->getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSound");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			for(const auto& soundID : _soundEditor->getLoadedIDs())
			{
				if(screen->getScrollingList("sounds")->getButton(soundID)->isHovered())
				{
					_gui->getViewport("right")->getWindow("main")->setActiveScreen("main");

					_deactivateModel();
					_deactivateBillboard();
					_deactivateSound();
					_deactivatePointlight();
					_deactivateSpotlight();
					_deactivateReflection();

					_currentTemplateSoundID = soundID;
					_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, true);
					_fe3d->sound3d_setPosition(_currentTemplateSoundID, fvec3(0.0f));
					_fe3d->sound3d_start(_currentTemplateSoundID, -1, 0, false);
					_fe3d->text_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityID(), true);
					_fe3d->text_setContent(_gui->getOverlay()->getTextField("soundID")->getEntityID(), "Sound: " + _currentTemplateSoundID.substr(1), 0.025f);
					_fe3d->misc_centerCursor();

					if(_fe3d->terrain_getSelectedID().empty())
					{
						_gui->getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
						_gui->getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
						_gui->getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
					}

					break;
				}
			}
		}
	}
}

void WorldEditor::_updateSoundChoosingMenu()
{
	auto screen = _gui->getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSoundChoice")
	{
		for(const auto& button : screen->getScrollingList("sounds")->getButtons())
		{
			if(!_fe3d->sound3d_isExisting(button->getID()))
			{
				screen->getScrollingList("sounds")->deleteButton(button->getID());
				break;
			}
		}

		for(const auto& soundID : _fe3d->sound3d_getIDs())
		{
			if(soundID[0] != '@')
			{
				if(screen->getScrollingList("sounds")->getButton(soundID)->isHovered())
				{
					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateSound(soundID);
					}
					else
					{
						_dontResetSelectedSpeaker = true;
						_selectSound(soundID);
					}

					break;
				}
			}
		}

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d->input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
			{
				_gui->getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSound");
				return;
			}
		}
	}
}