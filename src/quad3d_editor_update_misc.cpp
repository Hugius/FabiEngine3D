#include "quad3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::max;

void Quad3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		const auto distanceOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_Q)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_E)));

		_fe3d->camera_setThirdPersonDistance(max(MIN_CAMERA_DISTANCE, (_fe3d->camera_getThirdPersonDistance() - (distanceOffset * CAMERA_DISTANCE_SPEED))));

		auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SPACEBAR))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		cameraLookat.y = max(-GRID_Y_OFFSET, cameraLookat.y);
		_fe3d->camera_setThirdPersonLookat(cameraLookat);

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);

		const auto distance = _fe3d->camera_getThirdPersonDistance();
		_fe3d->graphics_setShadowPositionOffset(fvec3(cameraLookat + fvec3(distance)));
		_fe3d->graphics_setShadowLookatOffset(cameraLookat);
		_fe3d->graphics_setShadowSize(distance * 2.0f);
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

void Quad3dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}

		if(!_currentQuadId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->quad3d_setWireframed(_currentQuadId, !_fe3d->quad3d_isWireframed(_currentQuadId));
			}
		}
	}
}

void Quad3dEditor::_updateQuad3dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createQuad") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newQuadId = _gui->getOverlay()->getValueFormContent();

		if(newQuadId.empty())
		{
			Logger::throwWarning("Quad ID cannot be empty");

			return;
		}

		if(any_of(newQuadId.begin(), newQuadId.end(), isspace))
		{
			Logger::throwWarning("Quad ID cannot contain any spaces");

			return;
		}

		if(any_of(newQuadId.begin(), newQuadId.end(), isupper))
		{
			Logger::throwWarning("Quad ID cannot contain any capitals");

			return;
		}

		newQuadId = ("@" + newQuadId);

		if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), newQuadId) != _loadedEntityIds.end())
		{
			Logger::throwWarning("Quad already exists");

			return;
		}

		_currentQuadId = newQuadId;
		_loadedEntityIds.push_back(newQuadId);
		sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

		_fe3d->quad3d_create(newQuadId, false);

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
		_gui->getOverlay()->getTextField("quadId")->setTextContent("Quad3D: " + newQuadId.substr(1));
		_gui->getOverlay()->getTextField("quadId")->setVisible(true);
	}
}

void Quad3dEditor::_updateQuad3dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editQuad") || (_gui->getOverlay()->getChoiceFormId() == "deleteQuad"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredQuadId.empty())
			{
				_fe3d->quad3d_setVisible(_hoveredQuadId, false);
				_hoveredQuadId = "";
			}
		}
		else
		{
			if(_hoveredQuadId.empty())
			{
				_hoveredQuadId = ("@" + selectedOptionId);
				_fe3d->quad3d_setVisible(_hoveredQuadId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentQuadId = _hoveredQuadId;
				_hoveredQuadId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteQuad")
				{
					_gui->getOverlay()->openAnswerForm("deleteQuad", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

					_gui->getOverlay()->getTextField("quadId")->setTextContent("Quad3D: " + _currentQuadId.substr(1));
					_gui->getOverlay()->getTextField("quadId")->setVisible(true);
				}

				_fe3d->quad3d_setVisible(_currentQuadId, true);
			}
		}
	}
}

void Quad3dEditor::_updateQuad3dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteQuad") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->quad3d_delete(_currentQuadId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentQuadId), _loadedEntityIds.end());
			_currentQuadId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->quad3d_setVisible(_currentQuadId, false);

			_currentQuadId = "";
		}
	}
}