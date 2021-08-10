#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateSoundMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSound")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				return;
			}
			else if (screen->getButton("place")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSoundPlace");
			}
			else if (screen->getButton("choice")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSoundChoice");

				// Clear all buttons from scrolling list
				_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuSoundChoice")->getScrollingList("soundcasters")->deleteButtons();

				// Add the ID of every placed sound
				auto IDs = _fe3d.sound_getAllIDs();
				sort(IDs.begin(), IDs.end());
				for (auto& soundID : IDs)
				{
					// Check if soundcaster is not a preview
					if (soundID[0] != '@')
					{
						// Removing the unique number from the ID
						reverse(soundID.begin(), soundID.end());
						string rawID = soundID.substr(soundID.find('_') + 1);
						reverse(rawID.begin(), rawID.end());
						reverse(soundID.begin(), soundID.end());

						// Add new button
						_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuSoundChoice")->
							getScrollingList("soundcasters")->createButton(soundID, rawID);
					}
				}
			}
		}
	}
}

void SceneEditor::_updateSoundPlacingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSoundPlace")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			// Back button
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSound");
				return;
			}
			else
			{
				// Iterate through every created soundcaster
				for (const auto& audioID : _audioEditor.getLoadedAudioIDs())
				{
					// Check if button is hovered
					if (screen->getScrollingList("soundcasters")->getButton(audioID)->isHovered())
					{
						// Set new preview soundcaster
						_currentPreviewSoundID = audioID;
						_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);
						string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedSoundID")->getEntityID();
						_fe3d.textEntity_setVisible(textEntityID, false);
						_fe3d.textEntity_setTextContent(textEntityID, "Sound: " + _currentPreviewSoundID.substr(1), 0.025f);
						_fe3d.misc_centerCursor();
						break;
					}
				}
			}
		}
	}
}

void SceneEditor::_updateSoundChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSoundChoice")
	{
		// Remove deleted soundcasters from the scrollingList buttons
		for (const auto& button : screen->getScrollingList("soundcasters")->getButtons())
		{
			// Check if soundcaster is still existing
			if (!_fe3d.sound_isExisting(button->getID()))
			{
				// Delete button
				screen->getScrollingList("soundcasters")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed soundcaster
		for (const auto& soundID : _fe3d.sound_getAllIDs())
		{
			// Check if soundcaster is not a preview
			if (soundID[0] != '@')
			{
				// Check if button is hovered
				if (screen->getScrollingList("soundcasters")->getButton(soundID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
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
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSound");
				_currentPreviewSoundID = "";
				return;
			}
		}
	}
}