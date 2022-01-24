#include "sound_editor.hpp"
#include "logger.hpp"

void SoundEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "soundEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("soundCreate", "Create Sound", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingSound = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& id : IDs)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("soundList", "Edit Sound", fvec2(0.0f, 0.1f), IDs);
			_isChoosingSound = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& id : IDs)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("soundList", "Delete Sound", fvec2(0.0f, 0.1f), IDs);
			_isChoosingSound = true;
			_isDeletingSound = true;
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			saveToFile();
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

	if(screen->getID() == "soundEditorMenuChoice")
	{
		bool isExisting = _fe3d->sound2d_isExisting(_currentSoundID);
		bool isPlaying = isExisting && _fe3d->sound2d_isPlaying(_currentSoundID);
		bool isPaused = isExisting && _fe3d->sound2d_isPaused(_currentSoundID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(isPlaying)
			{
				_fe3d->sound2d_stop(_currentSoundID, 0);
			}

			_currentSoundID = "";
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityID(), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("soundEditorMenuMain");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("play")->isHovered())
		{
			_fe3d->sound2d_start(_currentSoundID, 1, 0, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("resume")->isHovered())
		{
			_fe3d->sound2d_resume(_currentSoundID);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("pause")->isHovered())
		{
			_fe3d->sound2d_pause(_currentSoundID);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d->sound2d_stop(_currentSoundID, 0);
		}

		screen->getButton("play")->setHoverable(!isPlaying && !isPaused);
		screen->getButton("resume")->setHoverable(isPaused);
		screen->getButton("pause")->setHoverable(isPlaying);
		screen->getButton("stop")->setHoverable(isPlaying || isPaused);
	}
}