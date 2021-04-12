#include "audio_editor.hpp"

void AudioEditor::_updateAudioEditing()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		if (screen->getID() == "audioEditorMenuChoice")
		{
			// Temporary values
			bool isExisting = _fe3d.soundEntity_isExisting(_currentAudioID);
			bool isPlaying = isExisting && _fe3d.soundEntity_isPlaying(_currentAudioID);
			bool isPaused = isExisting && _fe3d.soundEntity_isPaused(_currentAudioID);
			bool isLoaded = isExisting && _fe3d.soundEntity_isLoaded(_currentAudioID);
			
			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					// Stop sound preview
					if (isPlaying)
					{
						_fe3d.soundEntity_stop(_currentAudioID, 0);
					}

					// Miscellaneous
					_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID());
					_currentAudioID = "";
					_isEditingAudio = false;
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuMain");
				}
				else if (screen->getButton("load")->isHovered())
				{
					// Get the chosen filename
					const string rootDirectory = _fe3d.misc_getRootDirectory();
					const string targetDirectory = string("game_assets\\audio\\");
					const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "WAV");

					// Check if user did not cancel
					if (filePath != "")
					{
						// Check if user did not switch directory
						if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
							filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
						{
							const string newFilePath = filePath.substr(rootDirectory.size());

							// Remove old audio
							if (_fe3d.soundEntity_isExisting(_currentAudioID))
							{
								_fe3d.misc_clearAudioChunkCache(newFilePath);
								_fe3d.soundEntity_delete(_currentAudioID);
							}

							// Create new audio
							_fe3d.soundEntity_add(_currentAudioID, newFilePath);
						}
						else
						{
							_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
						}
					}
				}
				else if (screen->getButton("play")->isHovered())
				{
					_fe3d.soundEntity_play(_currentAudioID, 0, 0);
				}
				else if (screen->getButton("resume")->isHovered())
				{
					_fe3d.soundEntity_resume(_currentAudioID);
				}
				else if (screen->getButton("pause")->isHovered())
				{
					_fe3d.soundEntity_pause(_currentAudioID);
				}
				else if (screen->getButton("stop")->isHovered())
				{
					_fe3d.soundEntity_stop(_currentAudioID, 0);
				}
			}
			else
			{
				// Controlling audio playback through keyboard
				if (_fe3d.input_getKeyPressed(InputType::KEY_SPACE) && !isPlaying && !isPaused && isLoaded)
				{
					_fe3d.soundEntity_play(_currentAudioID, 0, 0);
				}
				else if (_fe3d.input_getKeyPressed(InputType::KEY_R) && isPaused)
				{
					_fe3d.soundEntity_resume(_currentAudioID);
				}
				else if (_fe3d.input_getKeyPressed(InputType::KEY_P) && isPlaying)
				{
					_fe3d.soundEntity_pause(_currentAudioID);
				}
				else if (_fe3d.input_getKeyPressed(InputType::KEY_S) && (isPlaying || isPaused))
				{
					_fe3d.soundEntity_stop(_currentAudioID, 0);
				}
			}

			// Buttons hoverability
			screen->getButton("play")->setHoverable(!isPlaying && !isPaused && isLoaded);
			screen->getButton("resume")->setHoverable(isPaused);
			screen->getButton("pause")->setHoverable(isPlaying);
			screen->getButton("stop")->setHoverable(isPlaying || isPaused);
		}
	}
}