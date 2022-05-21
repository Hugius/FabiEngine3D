#include "captor_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void CaptorEditor::_updateCamera()
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

void CaptorEditor::_updateMiscellaneous()
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

void CaptorEditor::_updateCaptorCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createCaptor") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newCaptorId = _gui->getOverlay()->getValueFormContent();

		if(newCaptorId.empty())
		{
			Logger::throwWarning("Captor ID cannot be empty");

			return;
		}

		if(any_of(newCaptorId.begin(), newCaptorId.end(), isspace))
		{
			Logger::throwWarning("Captor ID cannot contain any spaces");

			return;
		}

		if(any_of(newCaptorId.begin(), newCaptorId.end(), isupper))
		{
			Logger::throwWarning("Captor ID cannot contain any capitals");

			return;
		}

		newCaptorId = ("@" + newCaptorId);

		if(find(_loadedCaptorIds.begin(), _loadedCaptorIds.end(), newCaptorId) != _loadedCaptorIds.end())
		{
			Logger::throwWarning("Captor already exists");

			return;
		}

		_fe3d->captor_create(newCaptorId);
		_fe3d->captor_setExceptionId(newCaptorId, BOX_ID);
		_fe3d->captor_capture(newCaptorId);

		_currentCaptorId = newCaptorId;

		_loadedCaptorIds.push_back(newCaptorId);

		sort(_loadedCaptorIds.begin(), _loadedCaptorIds.end());

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("captorEditorMenuChoice");

		_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setTextContent("Captor: " + newCaptorId.substr(1));
		_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setVisible(true);
	}
}

void CaptorEditor::_updateCaptorChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editCaptor") || (_gui->getOverlay()->getChoiceFormId() == "deleteCaptor"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredCaptorId.empty())
			{
				_fe3d->model_setReflective(BOX_ID, "", false);
				_fe3d->model_setRefractive(BOX_ID, "", false);

				_hoveredCaptorId = "";
			}
		}
		else
		{
			if(_hoveredCaptorId.empty())
			{
				_hoveredCaptorId = ("@" + selectedOptionId);

				_fe3d->model_setReflective(BOX_ID, "", true);
				_fe3d->model_setRefractive(BOX_ID, "", true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentCaptorId = _hoveredCaptorId;
				_hoveredCaptorId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteCaptor")
				{
					_gui->getOverlay()->openAnswerForm("deleteCaptor", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("captorEditorMenuChoice");

					_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setTextContent("Captor: " + _currentCaptorId.substr(1));
					_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(!_hoveredCaptorId.empty())
		{
			_fe3d->model_setReflective(BOX_ID, "", false);
			_fe3d->model_setRefractive(BOX_ID, "", false);

			_hoveredCaptorId = "";
		}
	}
}

void CaptorEditor::_updateCaptorDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteCaptor") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->model_setReflective(BOX_ID, "", false);
			_fe3d->model_setRefractive(BOX_ID, "", false);

			_fe3d->captor_delete(_currentCaptorId);

			_loadedCaptorIds.erase(remove(_loadedCaptorIds.begin(), _loadedCaptorIds.end(), _currentCaptorId), _loadedCaptorIds.end());

			_currentCaptorId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->model_setReflective(BOX_ID, "", false);
			_fe3d->model_setRefractive(BOX_ID, "", false);

			_currentCaptorId = "";
		}
	}
}