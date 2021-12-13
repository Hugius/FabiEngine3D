#include "audio_editor.hpp"
#include "logger.hpp"

void AudioEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "audioEditorMenuMain")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("audioCreate", "Create Audio", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAudio = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedAudioIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("audioList", "Edit Audio", fvec2(0.0f, 0.1f), IDs);
			_isChoosingAudio = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedAudioIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("audioList", "Delete Audio", fvec2(0.0f, 0.1f), IDs);
			_isChoosingAudio = true;
			_isDeletingAudio = true;
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveAudioEntitiesToFile();
			unload();
			return;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void AudioEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "audioEditorMenuChoice")
	{
		// Temporary values
		bool isExisting = _fe3d.sound2d_isExisting(_currentAudioID);
		bool isPlaying = isExisting && _fe3d.sound2d_isPlaying(_currentAudioID);
		bool isPaused = isExisting && _fe3d.sound2d_isPaused(_currentAudioID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Stop audio preview
			if(isPlaying)
			{
				_fe3d.sound2d_stop(_currentAudioID, 0);
			}

			// Miscellaneous
			_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("audioID")->getEntityID(), false);
			_currentAudioID = "";
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuMain");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("play")->isHovered())
		{
			_fe3d.sound2d_play(_currentAudioID, 0, 0, false);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("resume")->isHovered())
		{
			_fe3d.sound2d_resume(_currentAudioID);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("pause")->isHovered())
		{
			_fe3d.sound2d_pause(_currentAudioID);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d.sound2d_stop(_currentAudioID, 0);
		}

		// Controlling audio playback through keyboard
		if(_fe3d.input_isKeyPressed(InputType::KEY_SPACE) && !isPlaying && !isPaused)
		{
			_fe3d.sound2d_play(_currentAudioID, 0, 0, false);
		}
		else if(_fe3d.input_isKeyPressed(InputType::KEY_R) && isPaused)
		{
			_fe3d.sound2d_resume(_currentAudioID);
		}
		else if(_fe3d.input_isKeyPressed(InputType::KEY_P) && isPlaying)
		{
			_fe3d.sound2d_pause(_currentAudioID);
		}
		else if(_fe3d.input_isKeyPressed(InputType::KEY_S) && (isPlaying || isPaused))
		{
			_fe3d.sound2d_stop(_currentAudioID, 0);
		}

		// Update buttons hoverability
		screen->getButton("play")->setHoverable(!isPlaying && !isPaused);
		screen->getButton("resume")->setHoverable(isPaused);
		screen->getButton("pause")->setHoverable(isPlaying);
		screen->getButton("stop")->setHoverable(isPlaying || isPaused);
	}
}