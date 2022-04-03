#include "sound_editor.hpp"
#include "logger.hpp"

void SoundEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "soundEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("soundCreate", "Create Sound", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingSound = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _loadedSoundIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("soundList", "Edit Sound", fvec2(0.0f, 0.1f), ids);
			_isChoosingSound = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _loadedSoundIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("soundList", "Delete Sound", fvec2(0.0f, 0.1f), ids);
			_isChoosingSound = true;
			_isDeletingSound = true;
		}

		if(_gui->getOverlay()->isAnswerFormAccepted("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			saveSoundsToFile();
			unload();
			return;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void SoundEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "soundEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->sound2d_isStarted(_currentSoundId, 0))
			{
				_fe3d->sound2d_stop(_currentSoundId, 0);
			}

			_currentSoundId = "";
			_gui->getOverlay()->getTextField("soundId")->setVisible(false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("soundEditorMenuMain");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("play")->isHovered())
		{
			_fe3d->sound2d_start(_currentSoundId, 1);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("pause")->isHovered())
		{
			_fe3d->sound2d_pause(_currentSoundId, 0);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("resume")->isHovered())
		{
			_fe3d->sound2d_resume(_currentSoundId, 0);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d->sound2d_stop(_currentSoundId, 0);
		}

		screen->getButton("play")->setHoverable(!_fe3d->sound2d_isStarted(_currentSoundId, 0));
		screen->getButton("resume")->setHoverable(_fe3d->sound2d_isStarted(_currentSoundId, 0) && _fe3d->sound2d_isPaused(_currentSoundId, 0));
		screen->getButton("pause")->setHoverable(_fe3d->sound2d_isStarted(_currentSoundId, 0) && !_fe3d->sound2d_isPaused(_currentSoundId, 0));
		screen->getButton("stop")->setHoverable(_fe3d->sound2d_isStarted(_currentSoundId, 0));
	}
}