#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateSoundMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSound")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSoundPlace");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSoundChoice");

			// Clear all buttons from scrolling list
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSoundChoice")->getScrollingList("sounds")->deleteButtons();

			// Add the ID of every placed sound
			auto IDs = _fe3d.sound3d_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& soundID : IDs)
			{
				// Must not be template entity
				if(soundID[0] != '@')
				{
					// Removing the unique number from the ID
					reverse(soundID.begin(), soundID.end());
					string rawID = soundID.substr(soundID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(soundID.begin(), soundID.end());

					// Add new button
					_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSoundChoice")->getScrollingList("sounds")->createButton(soundID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateSoundPlacingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSoundPlace")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Reset placing
			if(!_currentTemplateSoundID.empty())
			{
				// Hide template speaker
				_fe3d.model_setVisible(TEMPLATE_SPEAKER_ID, false);

				// Stop template sound playback
				if(_fe3d.sound3d_isStarted(_currentTemplateSoundID))
				{
					_fe3d.sound3d_stop(_currentTemplateSoundID, 0);
				}

				// Miscellaneous
				_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), false);
				_currentTemplateSoundID = "";
			}

			// Miscellaneous
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSound");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			// Iterate through every created sound
			for(const auto& soundID : _soundEditor.getLoadedIDs())
			{
				// Check if button is hovered
				if(screen->getScrollingList("sounds")->getButton(soundID)->isHovered())
				{
					// Reset right window
					_gui.getViewport("right")->getWindow("main")->setActiveScreen("main");

					// Deactivate everything
					_deactivateModel();
					_deactivateBillboard();
					_deactivateSound();
					_deactivatePointlight();
					_deactivateSpotlight();
					_deactivateReflection();

					// Set new template sound
					_currentTemplateSoundID = soundID;
					_fe3d.model_setVisible(TEMPLATE_SPEAKER_ID, true);
					_fe3d.sound3d_setPosition(_currentTemplateSoundID, fvec3(0.0f));
					_fe3d.sound3d_play(_currentTemplateSoundID, -1, 0, false);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), true);
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), "Sound: " + _currentTemplateSoundID.substr(1), 0.025f);
					_fe3d.misc_centerCursor();

					// Add position value forms for placing without terrain
					if(_fe3d.terrain_getSelectedID().empty())
					{
						_gui.getGlobalScreen()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
						_gui.getGlobalScreen()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
						_gui.getGlobalScreen()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
					}

					// Disable sound choosing
					break;
				}
			}
		}
	}
}

void WorldEditor::_updateSoundChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSoundChoice")
	{
		// Remove deleted sounds from the scrollingList buttons
		for(const auto& button : screen->getScrollingList("sounds")->getButtons())
		{
			// Check if sound is still existing
			if(!_fe3d.sound3d_isExisting(button->getID()))
			{
				// Delete button
				screen->getScrollingList("sounds")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed sound
		for(const auto& soundID : _fe3d.sound3d_getIDs())
		{
			// Must not be template entity
			if(soundID[0] != '@')
			{
				// Check if button is hovered
				if(screen->getScrollingList("sounds")->getButton(soundID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateSound(soundID);
					}
					else // Hovering (selection)
					{
						_dontResetSelectedSpeaker = true;
						_selectSound(soundID);
					}

					break;
				}
			}
		}

		// Back button
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSound");
				return;
			}
		}
	}
}