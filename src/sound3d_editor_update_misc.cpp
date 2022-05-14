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
			_fe3d->model_setVisible("@@grid", !_fe3d->model_isVisible("@@grid"));
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}
	}
}

void Sound3dEditor::_updateSound3dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createSound3d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newSound3dId = _gui->getOverlay()->getValueFormContent();

		if(newSound3dId.empty())
		{
			Logger::throwWarning("Sound3d ID cannot be empty");

			return;
		}

		if(any_of(newSound3dId.begin(), newSound3dId.end(), isspace))
		{
			Logger::throwWarning("Sound3d ID cannot contain any spaces");

			return;
		}

		if(any_of(newSound3dId.begin(), newSound3dId.end(), isupper))
		{
			Logger::throwWarning("Sound3d ID cannot contain any capitals");

			return;
		}

		newSound3dId = ("@" + newSound3dId);

		if(find(_loadedSound3dIds.begin(), _loadedSound3dIds.end(), newSound3dId) != _loadedSound3dIds.end())
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

		const string finalFilePath = filePath.substr(rootPath.size());
		_fe3d->misc_clearAudioCache(finalFilePath);

		_fe3d->sound3d_create(newSound3dId, finalFilePath);

		if(_fe3d->sound3d_isExisting(newSound3dId))
		{
			_currentSound3dId = newSound3dId;
			_loadedSound3dIds.push_back(newSound3dId);
			sort(_loadedSound3dIds.begin(), _loadedSound3dIds.end());

			_fe3d->sound3d_setPosition(newSound3dId, SOUND3D_POSITION);
			_fe3d->sound3d_start(newSound3dId, -1);

			_fe3d->model_setVisible("@@sound3d", true);
			_fe3d->model_setColor("@@sound3d", "", fvec3(1.0f));

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound3dEditorMenuChoice");
			_gui->getOverlay()->getTextField("sound3dId")->setTextContent("Sound3d: " + newSound3dId.substr(1));
			_gui->getOverlay()->getTextField("sound3dId")->setVisible(true);
		}
	}
}

void Sound3dEditor::_updateSound3dChoosing()
{
	if(!_hoveredSound3dId.empty())
	{
		_fe3d->sound3d_pause(_hoveredSound3dId, 0);
		_fe3d->model_setVisible("@@sound3d", false);

		_hoveredSound3dId = "";
	}

	if((_gui->getOverlay()->getChoiceFormId() == "editSound3d") || (_gui->getOverlay()->getChoiceFormId() == "deleteSound3d"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_hoveredSound3dId.empty())
			{
				_hoveredSound3dId = ("@" + selectedOptionId);

				_fe3d->sound3d_resume(_hoveredSound3dId, 0);
				_fe3d->model_setVisible("@@sound3d", true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentSound3dId = _hoveredSound3dId;
				_hoveredSound3dId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteSound3d")
				{
					_gui->getOverlay()->openAnswerForm("deleteSound3d", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound3dEditorMenuChoice");

					_gui->getOverlay()->getTextField("sound3dId")->setTextContent("Sound3d: " + _currentSound3dId.substr(1));
					_gui->getOverlay()->getTextField("sound3dId")->setVisible(true);
				}
			}
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
			_fe3d->sound3d_pause(_currentSound3dId, 0);
			_fe3d->model_setVisible("@@sound3d", false);

			_currentSound3dId = "";
		}
	}
}