#include "sound2d_editor.hpp"

void Sound2dEditor::_updateMainMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "sound2dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createSound2d", "Create Sound2D", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto sound2dIds = _loadedSound2dIds;

			for(auto & sound2dId : sound2dIds)
			{
				sound2dId = sound2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editSound2d", "Edit Sound2D", fvec2(0.0f, 0.1f), sound2dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto sound2dIds = _loadedSound2dIds;

			for(auto & sound2dId : sound2dIds)
			{
				sound2dId = sound2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteSound2d", "Delete Sound2D", fvec2(0.0f, 0.1f), sound2dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveSound2dsToFile();
				unload();

				return;
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void Sound2dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "sound2dEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->sound2d_isStarted(_currentSound2dId, 0))
			{
				_fe3d->sound2d_stop(_currentSound2dId, 0);
			}

			_currentSound2dId = "";
			_gui->getOverlay()->getTextField("sound2dId")->setVisible(false);
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound2dEditorMenuMain");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("play")->isHovered())
		{
			_fe3d->sound2d_start(_currentSound2dId, 1);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("pause")->isHovered())
		{
			_fe3d->sound2d_pause(_currentSound2dId, 0);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("resume")->isHovered())
		{
			_fe3d->sound2d_resume(_currentSound2dId, 0);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d->sound2d_stop(_currentSound2dId, 0);
		}

		screen->getButton("play")->setHoverable(!_fe3d->sound2d_isStarted(_currentSound2dId, 0));
		screen->getButton("resume")->setHoverable(_fe3d->sound2d_isStarted(_currentSound2dId, 0) && _fe3d->sound2d_isPaused(_currentSound2dId, 0));
		screen->getButton("pause")->setHoverable(_fe3d->sound2d_isStarted(_currentSound2dId, 0) && !_fe3d->sound2d_isPaused(_currentSound2dId, 0));
		screen->getButton("stop")->setHoverable(_fe3d->sound2d_isStarted(_currentSound2dId, 0));
	}
}