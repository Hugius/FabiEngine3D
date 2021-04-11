#include "scene_editor.hpp"

void SceneEditor::_updateMainSoundMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuSound")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
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

					// Add every placed soundcaster name
					for (auto& soundID : _fe3d.soundEntity_getAllIDs())
					{
						// Check if soundcaster is not a preview
						if (soundID[0] != '@')
						{
							// Removing the unique number from the soundID
							std::reverse(soundID.begin(), soundID.end());
							string soundName = soundID.substr(soundID.find('_') + 1);
							std::reverse(soundName.begin(), soundName.end());
							std::reverse(soundID.begin(), soundID.end());

							// Add new button
							_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuSoundChoice")->
								getScrollingList("soundcasters")->addButton(soundID, soundName);
						}
					}
				}
			}
		}
	}
}

void SceneEditor::_updateSoundPlacingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuSoundPlace")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				// Back button
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSound");
				}
				else
				{
					// Loop over every created soundcaster
					for (auto& audioName : _audioEditor.getLoadedAudioIDs())
					{
						// Check if button is hovered
						if (screen->getScrollingList("soundcasters")->getButton(audioName)->isHovered())
						{
							// Set new preview soundcaster
							_currentPreviewSoundID = audioName;
							_fe3d.modelEntity_show(PREVIEW_SPEAKER_ID);
							string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedSoundName")->getEntityID();
							_fe3d.textEntity_show(textEntityID);
							_fe3d.textEntity_setTextContent(textEntityID, "Sound: " + _currentPreviewSoundID.substr(1), 0.025f);
							_fe3d.misc_setCursorPosition(_fe3d.misc_convertToScreenCoords(Vec2(0.5f)));
							break;
						}
					}
				}
			}
		}
	}
}

void SceneEditor::_updateSoundChoosingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuSoundChoice")
		{
			// Remove deleted soundcasters from the scrollingList buttons
			for (auto& button : screen->getScrollingList("soundcasters")->getButtons())
			{
				// Check if soundcaster is still existing
				if (!_fe3d.soundEntity_isExisting(button->getID()))
				{
					// Delete button
					screen->getScrollingList("soundcasters")->deleteButton(button->getID());
					break;
				}
			}

			// Loop over every placed soundcaster
			for (auto& soundName : _fe3d.soundEntity_getAllIDs())
			{
				// Check if soundcaster is not a preview
				if (soundName[0] != '@')
				{
					// Check if button is hovered
					if (screen->getScrollingList("soundcasters")->getButton(soundName)->isHovered())
					{
						// Check if LMB pressed (activation)
						if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							_activateSound(soundName);
						}
						else // Hovering (selection)
						{
							_dontResetSelectedSound = true;
							_selectSound(soundName);
						}

						break;
					}
				}
			}

			// Back button
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSound");
					_currentPreviewSoundID = "";
				}
			}
		}
	}
}