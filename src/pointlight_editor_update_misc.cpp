#include "pointlight_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void PointlightEditor::_updateCamera()
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

void PointlightEditor::_updateMiscellaneous()
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

void PointlightEditor::_updatePointlightCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createPointlight") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newPointlightId = _gui->getOverlay()->getValueFormContent();

		if(newPointlightId.empty())
		{
			Logger::throwWarning("Pointlight ID cannot be empty");

			return;
		}

		if(any_of(newPointlightId.begin(), newPointlightId.end(), isspace))
		{
			Logger::throwWarning("Pointlight ID cannot contain any spaces");

			return;
		}

		if(any_of(newPointlightId.begin(), newPointlightId.end(), isupper))
		{
			Logger::throwWarning("Pointlight ID cannot contain any capitals");

			return;
		}

		newPointlightId = ("@" + newPointlightId);

		if(find(_loadedPointlightIds.begin(), _loadedPointlightIds.end(), newPointlightId) != _loadedPointlightIds.end())
		{
			Logger::throwWarning("Pointlight already exists");

			return;
		}

		_currentPointlightId = newPointlightId;
		_loadedPointlightIds.push_back(newPointlightId);
		sort(_loadedPointlightIds.begin(), _loadedPointlightIds.end());

		_fe3d->pointlight_create(newPointlightId, false);

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("pointlightEditorMenuChoice");
		_gui->getOverlay()->getTextField("pointlightId")->setTextContent("Pointlight: " + newPointlightId.substr(1));
		_gui->getOverlay()->getTextField("pointlightId")->setVisible(true);
	}
}

void PointlightEditor::_updatePointlightChoosing()
{
	if(!_hoveredPointlightId.empty())
	{
		_fe3d->pointlight_setVisible(_hoveredPointlightId, false);

		_hoveredPointlightId = "";
	}

	if((_gui->getOverlay()->getChoiceFormId() == "editPointlight") || (_gui->getOverlay()->getChoiceFormId() == "deletePointlight"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_hoveredPointlightId.empty())
			{
				_hoveredPointlightId = ("@" + selectedOptionId);
				_fe3d->pointlight_setVisible(_hoveredPointlightId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentPointlightId = _hoveredPointlightId;
				_hoveredPointlightId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deletePointlight")
				{
					_gui->getOverlay()->openAnswerForm("deletePointlight", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("pointlightEditorMenuChoice");

					_gui->getOverlay()->getTextField("pointlightId")->setTextContent("Pointlight: " + _currentPointlightId.substr(1));
					_gui->getOverlay()->getTextField("pointlightId")->setVisible(true);
				}

				_fe3d->pointlight_setVisible(_currentPointlightId, true);
			}
		}
	}
}

void PointlightEditor::_updatePointlightDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deletePointlight") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->pointlight_delete(_currentPointlightId);

			_loadedPointlightIds.erase(remove(_loadedPointlightIds.begin(), _loadedPointlightIds.end(), _currentPointlightId), _loadedPointlightIds.end());
			_currentPointlightId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->pointlight_setVisible(_currentPointlightId, false);

			_currentPointlightId = "";
		}
	}
}