#include "aabb_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void AabbEditor::_updateCamera()
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

void AabbEditor::_updateMiscellaneous()
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

void AabbEditor::_updateAabbCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createAabb") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto aabbId = _gui->getOverlay()->getValueFormContent();

		if(aabbId.empty())
		{
			Logger::throwWarning("AABB ID cannot be empty");

			return;
		}

		if(any_of(aabbId.begin(), aabbId.end(), isspace))
		{
			Logger::throwWarning("AABB ID cannot contain any spaces");

			return;
		}

		if(any_of(aabbId.begin(), aabbId.end(), isupper))
		{
			Logger::throwWarning("AABB ID cannot contain any capitals");

			return;
		}

		aabbId = ("@" + aabbId);

		if(find(_loadedAabbIds.begin(), _loadedAabbIds.end(), aabbId) != _loadedAabbIds.end())
		{
			Logger::throwWarning("AABB already exists");

			return;
		}

		_fe3d->aabb_create(aabbId, false);

		_loadedAabbIds.push_back(aabbId);

		sort(_loadedAabbIds.begin(), _loadedAabbIds.end());

		_gui->getRightViewport()->getWindow("main")->setActiveScreen("aabbEditorMenuChoice");
		_gui->getOverlay()->getTextField(AABB_TITLE_ID)->setTextContent("AABB: " + aabbId.substr(1));
		_gui->getOverlay()->getTextField(AABB_TITLE_ID)->setVisible(true);

		_currentAabbId = aabbId;
	}
}

void AabbEditor::_updateAabbChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editAabb") || (_gui->getOverlay()->getChoiceFormId() == "deleteAabb"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredAabbId.empty())
			{
				_fe3d->aabb_setVisible(_hoveredAabbId, false);

				_hoveredAabbId = "";
			}
		}
		else
		{
			if(_hoveredAabbId.empty())
			{
				_hoveredAabbId = ("@" + selectedOptionId);

				_fe3d->aabb_setVisible(_hoveredAabbId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentAabbId = _hoveredAabbId;
				_hoveredAabbId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteAabb")
				{
					_gui->getOverlay()->openAnswerForm("deleteAabb", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getRightViewport()->getWindow("main")->setActiveScreen("aabbEditorMenuChoice");

					_gui->getOverlay()->getTextField(AABB_TITLE_ID)->setTextContent("AABB: " + _currentAabbId.substr(1));
					_gui->getOverlay()->getTextField(AABB_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(!_hoveredAabbId.empty())
		{
			_fe3d->aabb_setVisible(_hoveredAabbId, false);

			_hoveredAabbId = "";
		}
	}
}

void AabbEditor::_updateAabbDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteAabb") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->aabb_delete(_currentAabbId);

			_loadedAabbIds.erase(remove(_loadedAabbIds.begin(), _loadedAabbIds.end(), _currentAabbId), _loadedAabbIds.end());

			_currentAabbId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->aabb_setVisible(_currentAabbId, false);

			_currentAabbId = "";
		}
	}
}