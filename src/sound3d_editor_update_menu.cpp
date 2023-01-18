#include "sound3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void Sound3dEditor::_updateMainMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "sound3dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createSound3d", "Create Sound3d", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto sound3dIds = _loadedSound3dIds;

			for(auto & sound3dId : sound3dIds)
			{
				sound3dId = sound3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editSound3d", "Edit Sound3d", RIGHT_CHOICE_FORM_POSITION, sound3dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto sound3dIds = _loadedSound3dIds;

			for(auto & sound3dId : sound3dIds)
			{
				sound3dId = sound3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteSound3d", "Delete Sound3d", RIGHT_CHOICE_FORM_POSITION, sound3dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveSound3dsToFile();

				unload();

				return;
			}
			else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void Sound3dEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "sound3dEditorMenuChoice")
	{
		const auto maxVolume = _fe3d->sound3d_getMaxVolume(_currentSound3dId);
		const auto maxDistance = _fe3d->sound3d_getMaxDistance(_currentSound3dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->sound3d_isStarted(_currentSound3dId, 0))
			{
				_fe3d->sound3d_stop(_currentSound3dId, 0);
			}

			_fe3d->model_setVisible(SPEAKER_ID, false);

			_gui->getOverlay()->getTextField(SOUND3D_TITLE_ID)->setVisible(false);
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound3dEditorMenuMain");

			_currentSound3dId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("play")->isHovered())
		{
			_fe3d->sound3d_start(_currentSound3dId, 1, 0);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("pause")->isHovered())
		{
			_fe3d->sound3d_pause(_currentSound3dId, 0);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("resume")->isHovered())
		{
			_fe3d->sound3d_resume(_currentSound3dId, 0);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d->sound3d_stop(_currentSound3dId, 0);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("maxVolume")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxVolume", "Max Volume", (maxVolume * VOLUME_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("maxDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxDistance", "Max Distance", (maxDistance * DISTANCE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "maxVolume") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sound3d_setMaxVolume(_currentSound3dId, (value / VOLUME_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "maxDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sound3d_setMaxDistance(_currentSound3dId, (value / DISTANCE_FACTOR));
		}

		screen->getButton("play")->setHoverable(!_fe3d->sound3d_isStarted(_currentSound3dId, 0), true);
		screen->getButton("resume")->setHoverable((_fe3d->sound3d_isStarted(_currentSound3dId, 0) && _fe3d->sound3d_isPaused(_currentSound3dId, 0)), true);
		screen->getButton("pause")->setHoverable((_fe3d->sound3d_isStarted(_currentSound3dId, 0) && !_fe3d->sound3d_isPaused(_currentSound3dId, 0)), true);
		screen->getButton("stop")->setHoverable(_fe3d->sound3d_isStarted(_currentSound3dId, 0), true);
	}
}