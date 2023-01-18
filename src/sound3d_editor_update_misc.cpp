#include "sound3d_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void Sound3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		const auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		const auto distanceOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_Q)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_E)));
		const auto lookatOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SPACEBAR)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT)));

		_fe3d->camera_setThirdPersonDistance(max(MIN_CAMERA_DISTANCE, (_fe3d->camera_getThirdPersonDistance() - (distanceOffset * CAMERA_DISTANCE_SPEED))));
		_fe3d->camera_setThirdPersonLookat(fvec3(cameraLookat.x, max(0.0f, (cameraLookat.y + (lookatOffset * CAMERA_LOOKAT_SPEED))), cameraLookat.z));
		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), false);
	}

	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_RIGHT))
		{
			_fe3d->camera_setThirdPersonEnabled(!_fe3d->camera_isThirdPersonEnabled());
		}
	}

	if(_gui->getOverlay()->isFocused())
	{
		_fe3d->camera_setThirdPersonEnabled(false);
	}
}

void Sound3dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_G))
		{
			_fe3d->model_setVisible(GRID_ID, !_fe3d->model_isVisible(GRID_ID));
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
		{
			_fe3d->model_setVisible(BOX_ID, !_fe3d->model_isVisible(BOX_ID));
		}
	}
}

void Sound3dEditor::_updateSound3dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createSound3d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto sound3dId = _gui->getOverlay()->getValueFormContent();

		if(sound3dId.empty())
		{
			Logger::throwWarning("Sound3D ID cannot be empty");

			return;
		}

		if(any_of(sound3dId.begin(), sound3dId.end(), isspace))
		{
			Logger::throwWarning("Sound3D ID cannot contain any spaces");

			return;
		}

		if(any_of(sound3dId.begin(), sound3dId.end(), isupper))
		{
			Logger::throwWarning("Sound3D ID cannot contain any capitals");

			return;
		}

		if(sound3dId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Sound3D ID cannot contain any specials");

			return;
		}

		sound3dId = ("@" + sound3dId);

		if(find(_loadedSound3dIds.begin(), _loadedSound3dIds.end(), sound3dId) != _loadedSound3dIds.end())
		{
			Logger::throwWarning("Sound3d already exists");

			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\audio\\");

		if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

			return;
		}

		const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "WAV");

		if(filePath.empty())
		{
			return;
		}

		if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
		{
			Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

			return;
		}

		const auto finalFilePath = filePath.substr(rootPath.size());

		_fe3d->misc_clearAudioCache(finalFilePath);

		_fe3d->sound3d_create(sound3dId, finalFilePath);

		if(_fe3d->sound3d_isExisting(sound3dId))
		{
			_fe3d->sound3d_setPosition(sound3dId, SOUND3D_POSITION);

			_loadedSound3dIds.push_back(sound3dId);

			sort(_loadedSound3dIds.begin(), _loadedSound3dIds.end());

			_fe3d->model_setVisible(SPEAKER_ID, true);
			_fe3d->model_setColor(SPEAKER_ID, "", fvec3(1.0f));

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound3dEditorMenuChoice");
			_gui->getOverlay()->getTextField(SOUND3D_TITLE_ID)->setTextContent("Sound3d: " + sound3dId.substr(1));
			_gui->getOverlay()->getTextField(SOUND3D_TITLE_ID)->setVisible(true);

			_currentSound3dId = sound3dId;
		}
	}
}

void Sound3dEditor::_updateSound3dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editSound3d") || (_gui->getOverlay()->getChoiceFormId() == "deleteSound3d"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredSound3dId.empty())
			{
				_fe3d->model_setVisible(SPEAKER_ID, false);

				_hoveredSound3dId = "";
			}
		}
		else
		{
			if(_hoveredSound3dId.empty())
			{
				_hoveredSound3dId = ("@" + selectedOptionId);

				_fe3d->model_setVisible(SPEAKER_ID, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentSound3dId = _hoveredSound3dId;
				_hoveredSound3dId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteSound3d")
				{
					_gui->getOverlay()->openAnswerForm("deleteSound3d", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound3dEditorMenuChoice");
					_gui->getOverlay()->getTextField(SOUND3D_TITLE_ID)->setTextContent("Sound3d: " + _currentSound3dId.substr(1));
					_gui->getOverlay()->getTextField(SOUND3D_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(!_hoveredSound3dId.empty())
		{
			_fe3d->model_setVisible(SPEAKER_ID, false);

			_hoveredSound3dId = "";
		}
	}
}

void Sound3dEditor::_updateSound3dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteSound3d") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->sound3d_delete(_currentSound3dId);

			_loadedSound3dIds.erase(remove(_loadedSound3dIds.begin(), _loadedSound3dIds.end(), _currentSound3dId), _loadedSound3dIds.end());

			_currentSound3dId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->model_setVisible(SPEAKER_ID, false);

			_currentSound3dId = "";
		}
	}
}