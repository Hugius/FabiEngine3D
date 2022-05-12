#include "spotlight_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void SpotlightEditor::_updateCamera()
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

void SpotlightEditor::_updateMiscellaneous()
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

	if(!_currentSpotlightId.empty())
	{
		_fe3d->model_setColor("@@spotlight", "", _fe3d->spotlight_getColor(_currentSpotlightId));
	}
	if(!_hoveredSpotlightId.empty())
	{
		_fe3d->model_setColor("@@spotlight", "", _fe3d->spotlight_getColor(_hoveredSpotlightId));
	}
}

void SpotlightEditor::_updateSpotlightCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createSpotlight") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newSpotlightId = _gui->getOverlay()->getValueFormContent();

		if(newSpotlightId.empty())
		{
			Logger::throwWarning("Spotlight ID cannot be empty");

			return;
		}

		if(any_of(newSpotlightId.begin(), newSpotlightId.end(), isspace))
		{
			Logger::throwWarning("Spotlight ID cannot contain any spaces");

			return;
		}

		if(any_of(newSpotlightId.begin(), newSpotlightId.end(), isupper))
		{
			Logger::throwWarning("Spotlight ID cannot contain any capitals");

			return;
		}

		newSpotlightId = ("@" + newSpotlightId);

		if(find(_loadedSpotlightIds.begin(), _loadedSpotlightIds.end(), newSpotlightId) != _loadedSpotlightIds.end())
		{
			Logger::throwWarning("Spotlight already exists");

			return;
		}

		_currentSpotlightId = newSpotlightId;
		_loadedSpotlightIds.push_back(newSpotlightId);
		sort(_loadedSpotlightIds.begin(), _loadedSpotlightIds.end());

		_fe3d->spotlight_create(newSpotlightId);
		_fe3d->spotlight_setPosition(newSpotlightId, SPOTLIGHT_POSITION);
		_fe3d->spotlight_setPitch(newSpotlightId, -90.0f);

		_fe3d->model_setVisible("@@spotlight", true);
		_fe3d->model_setColor("@@spotlight", "", fvec3(1.0f));

		_gui->getRightViewport()->getWindow("main")->setActiveScreen("spotlightEditorMenuChoice");
		_gui->getOverlay()->getTextField("spotlightId")->setTextContent("Spotlight: " + newSpotlightId.substr(1));
		_gui->getOverlay()->getTextField("spotlightId")->setVisible(true);
	}
}

void SpotlightEditor::_updateSpotlightChoosing()
{
	if(!_hoveredSpotlightId.empty())
	{
		_fe3d->spotlight_setVisible(_hoveredSpotlightId, false);
		_fe3d->model_setVisible("@@spotlight", false);

		_hoveredSpotlightId = "";
	}

	if((_gui->getOverlay()->getChoiceFormId() == "editSpotlight") || (_gui->getOverlay()->getChoiceFormId() == "deleteSpotlight"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_hoveredSpotlightId.empty())
			{
				_hoveredSpotlightId = ("@" + selectedOptionId);

				_fe3d->spotlight_setVisible(_hoveredSpotlightId, true);
				_fe3d->model_setVisible("@@spotlight", true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentSpotlightId = _hoveredSpotlightId;
				_hoveredSpotlightId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteSpotlight")
				{
					_gui->getOverlay()->openAnswerForm("deleteSpotlight", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getRightViewport()->getWindow("main")->setActiveScreen("spotlightEditorMenuChoice");

					_gui->getOverlay()->getTextField("spotlightId")->setTextContent("Spotlight: " + _currentSpotlightId.substr(1));
					_gui->getOverlay()->getTextField("spotlightId")->setVisible(true);
				}
			}
		}
	}
}

void SpotlightEditor::_updateSpotlightDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteSpotlight") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->spotlight_delete(_currentSpotlightId);

			_loadedSpotlightIds.erase(remove(_loadedSpotlightIds.begin(), _loadedSpotlightIds.end(), _currentSpotlightId), _loadedSpotlightIds.end());
			_currentSpotlightId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->spotlight_setVisible(_currentSpotlightId, false);
			_fe3d->model_setVisible("@@spotlight", false);

			_currentSpotlightId = "";
		}
	}
}