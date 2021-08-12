#include "audio_editor.hpp"
#include "logger.hpp"

void AudioEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "audioEditorMenuChoice")
	{
		// Temporary values
		bool isExisting = _fe3d.sound_isExisting(_currentAudioID);
		bool isPlaying = isExisting && _fe3d.sound_isPlaying(_currentAudioID);
		bool isPaused = isExisting && _fe3d.sound_isPaused(_currentAudioID);
		bool isLoaded = isExisting && _fe3d.sound_isLoaded(_currentAudioID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				// Stop sound preview
				if (isPlaying)
				{
					_fe3d.sound_stop(_currentAudioID, 0);
				}

				// Miscellaneous
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAudioID")->getEntityID(), false);
				_currentAudioID = "";
				_isEditingAudio = false;
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuMain");
				return;
			}
			else if (screen->getButton("play")->isHovered())
			{
				_fe3d.sound_play(_currentAudioID, 0, 0);
			}
			else if (screen->getButton("resume")->isHovered())
			{
				_fe3d.sound_resume(_currentAudioID);
			}
			else if (screen->getButton("pause")->isHovered())
			{
				_fe3d.sound_pause(_currentAudioID);
			}
			else if (screen->getButton("stop")->isHovered())
			{
				_fe3d.sound_stop(_currentAudioID, 0);
			}
		}
		else
		{
			// Controlling audio playback through keyboard
			if (_fe3d.input_isKeyPressed(InputType::KEY_SPACE) && !isPlaying && !isPaused && isLoaded)
			{
				_fe3d.sound_play(_currentAudioID, 0, 0);
			}
			else if (_fe3d.input_isKeyPressed(InputType::KEY_R) && isPaused)
			{
				_fe3d.sound_resume(_currentAudioID);
			}
			else if (_fe3d.input_isKeyPressed(InputType::KEY_P) && isPlaying)
			{
				_fe3d.sound_pause(_currentAudioID);
			}
			else if (_fe3d.input_isKeyPressed(InputType::KEY_S) && (isPlaying || isPaused))
			{
				_fe3d.sound_stop(_currentAudioID, 0);
			}
		}

		// Button hoverabilities
		screen->getButton("play")->setHoverable(!isPlaying && !isPaused && isLoaded);
		screen->getButton("resume")->setHoverable(isPaused);
		screen->getButton("pause")->setHoverable(isPlaying);
		screen->getButton("stop")->setHoverable(isPlaying || isPaused);
	}
}