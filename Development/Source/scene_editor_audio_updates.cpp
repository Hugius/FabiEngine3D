#include "scene_editor.hpp"

void SceneEditor::_updateMainAudioMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuAudio")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				}
				else if (screen->getButton("place")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuAudioPlace");
				}
				else if (screen->getButton("choice")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuAudioChoice");

					// Clear all buttons from scrolling list
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuAudioChoice")->getScrollingList("audiocasters")->deleteButtons();

					// Add every placed audiocaster name
					for (auto& audioID : _fe3d.audioEntity_getAllIDs())
					{
						// Check if audiocaster is not a preview
						if (audioID[0] != '@')
						{
							// Removing the unique number from the audioID
							string audioName = audioID.substr(audioID.find('@') + 1);

							// Add new button
							_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuAudioChoice")->
								getScrollingList("audiocasters")->addButton(audioID, audioName);
						}
					}
				}
			}
		}
	}
}

void SceneEditor::_updateAudioPlacingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuAudioPlace")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				// Back button
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuAudio");
				}
				else
				{
					// Loop over every created audiocaster
					for (auto& audioName : _audioEditor.getLoadedAudioIDs())
					{
						// Check if button is hovered
						if (screen->getScrollingList("audiocasters")->getButton(audioName)->isHovered())
						{
							// Set new preview audiocaster
							_currentPreviewAudioName = audioName;
							_fe3d.gameEntity_show(_previewSpeakerID);
							string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID();
							_fe3d.textEntity_show(textEntityID);
							_fe3d.textEntity_setTextContent(textEntityID, "Audio: " + _currentPreviewAudioName.substr(1), 0.025f);
							_fe3d.misc_setCursorPosition(_fe3d.misc_convertToScreenCoords(Vec2(0.5f)));
							break;
						}
					}
				}
			}
		}
	}
}

void SceneEditor::_updateAudioChoosingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuAudioChoice")
		{
			// Remove deleted audiocasters from the scrollingList buttons
			for (auto& button : screen->getScrollingList("audiocasters")->getButtons())
			{
				// Check if audiocaster is still existing
				if (!_fe3d.audioEntity_isExisting(button->getID()))
				{
					// Delete button
					screen->getScrollingList("audiocasters")->deleteButton(button->getID());
					break;
				}
			}

			// Loop over every placed audiocaster
			for (auto& audioName : _fe3d.audioEntity_getAllIDs())
			{
				// Check if audiocaster is not a preview
				if (audioName[0] != '@')
				{
					// Check if button is hovered
					if (screen->getScrollingList("audiocasters")->getButton(audioName)->isHovered())
					{
						// Check if LMB pressed (activation)
						if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							_activateAudio(audioName);
						}
						else // Hovering (selection)
						{
							_dontResetSelectedAudio = true;
							_selectAudio(audioName);
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
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuAudio");
					_currentPreviewAudioName = "";
				}
			}
		}
	}
}