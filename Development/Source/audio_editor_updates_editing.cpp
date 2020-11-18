#include "audio_editor.hpp"

void AudioEditor::_updateAudioEditing()
{
	if (_isLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("audioEditorMenuChoice");

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
				if (!_fe3d.audioEntity_isPlaying(_currentAudioID))
				{

				}
			}
			else if (screen->getButton("pause")->isHovered())
			{

			}
			else if (screen->getButton("stop")->isHovered())
			{

			}
			else if (screen->getButton("volume")->isHovered())
			{

			}
			else if (screen->getButton("back")->isHovered())
			{
				_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID());
				_currentAudioID = "";
				_isEditingAudio = false;
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuMain");
			}
		}


	}
}