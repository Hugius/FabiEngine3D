#include "audio_editor.hpp"

void AudioEditor::_updateAudioEditing()
{
	if (_isLoaded)
	{
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("audioEditorMenuChoice");
		bool isExisting = _fe3d.audioEntity_isExisting(_currentAudioID);
		bool isPlaying = isExisting && _fe3d.audioEntity_isPlaying(_currentAudioID);
		bool isPaused = isExisting && _fe3d.audioEntity_isPaused(_currentAudioID);

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("load")->isHovered())
			{
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\audio\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "MP3");

				// Check if user did not cancel
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());

						// Remove old audio
						if (_fe3d.audioEntity_isExisting(_currentAudioID))
						{
							_fe3d.misc_clearAudioChunkCache(newFilePath);
							_fe3d.audioEntity_delete(_currentAudioID);
						}

						// Create new audio
						_fe3d.audioEntity_addGlobal(_currentAudioID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("play")->isHovered())
			{
				_fe3d.audioEntity_play(_currentAudioID, 0, 50);
			}
			else if (screen->getButton("resume")->isHovered())
			{
				_fe3d.audioEntity_resume(_currentAudioID);
			}
			else if (screen->getButton("pause")->isHovered())
			{
				_fe3d.audioEntity_pause(_currentAudioID);
			}
			else if (screen->getButton("stop")->isHovered())
			{
				_fe3d.audioEntity_stop(_currentAudioID);
			}
			else if (screen->getButton("back")->isHovered())
			{
				// Stop sound preview
				if (isPlaying)
				{
					_fe3d.audioEntity_stop(_currentAudioID);
				}

				// Miscellaneous
				_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID());
				_currentAudioID = "";
				_isEditingAudio = false;
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuMain");
			}
		}

		// Buttons hoverability
		screen->getButton("play")->setHoverable(!isPlaying && !isPaused);
		screen->getButton("resume")->setHoverable(isPaused);
		screen->getButton("pause")->setHoverable(isPlaying);
		screen->getButton("stop")->setHoverable(isPlaying || isPaused);

		// Update audio status symbol
		if (isPlaying)
		{
			_fe3d.billboardEntity_setDiffuseMap("@@audioStatus", "engine\\textures\\play.png", true);
		}
		else if (isPaused)
		{
			_fe3d.billboardEntity_setDiffuseMap("@@audioStatus", "engine\\textures\\pause.png", true);
		}
		else
		{
			_fe3d.billboardEntity_setDiffuseMap("@@audioStatus", "engine\\textures\\stop.png", true);
		}
		_fe3d.billboardEntity_rotate("@@audioStatus", vec3(0.0f, 0.5f, 0.0f));
	}
}