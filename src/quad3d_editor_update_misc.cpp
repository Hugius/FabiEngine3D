#include "quad3d_editor.hpp"
#include "logger.hpp"

using std::max;

void Quad3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		auto scrollOffset = _fe3d->input_getMouseWheelY();
		auto cameraDistance = _fe3d->camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d->camera_setThirdPersonDistance(cameraDistance);

		auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		if(_fe3d->input_isKeyDown(InputType::KEY_SPACE))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		cameraLookat.y = max(-GRID_Y_OFFSET, cameraLookat.y);
		_fe3d->camera_setThirdPersonLookat(cameraLookat);

		_fe3d->quad2d_setVisible("@@cursor", false);

		const auto distance = _fe3d->camera_getThirdPersonDistance();
		_fe3d->gfx_setShadowPositionOffset(fvec3(cameraLookat + fvec3(distance * 2.0f)));
		_fe3d->gfx_setShadowLookatOffset(cameraLookat);
		_fe3d->gfx_setShadowSize(distance * 4.0f);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
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
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}

		if(!_currentQuadId.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				_fe3d->quad3d_setWireframed(_currentQuadId, !_fe3d->quad3d_isWireframed(_currentQuadId));
			}
		}
	}
}

void Quad3dEditor::_updateQuad3dCreating()
{
	if(_isCreatingQuad3d)
	{
		string newQuadId;

		if(_gui->getOverlay()->checkValueForm("quad3dCreate", newQuadId, {_currentQuadId}))
		{
			if(newQuadId.find('@') != string::npos)
			{
				Logger::throwWarning("Quad ID cannot contain '@'");
				return;
			}

			if(newQuadId.find(' ') != string::npos)
			{
				Logger::throwWarning("Quad ID cannot contain any spaces");
				return;
			}

			newQuadId = ("@" + newQuadId);

			if(find(_loadedQuadIds.begin(), _loadedQuadIds.end(), newQuadId) != _loadedQuadIds.end())
			{
				Logger::throwWarning("Quad already exists");
				return;
			}

			_fe3d->quad3d_create(newQuadId, false);

			if(_fe3d->quad3d_isExisting(newQuadId))
			{
				_currentQuadId = newQuadId;
				_loadedQuadIds.push_back(newQuadId);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quadId")->getEntityId(), "Quad3d: " + newQuadId.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), true);
				_isCreatingQuad3d = false;
			}
		}
	}
}

void Quad3dEditor::_updateQuad3dChoosing()
{
	if(_isChoosingQuad3d)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("quad3dList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredQuadId.empty())
			{
				_hoveredQuadId = ("@" + selectedButtonId);
				_fe3d->quad3d_setVisible(_hoveredQuadId, true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentQuadId = _hoveredQuadId;
				_hoveredQuadId = "";

				if(!_isDeletingQuad3d)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quadId")->getEntityId(), "Quad3d: " + _currentQuadId.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), true);
				}

				_fe3d->quad3d_setVisible(_currentQuadId, true);
				_gui->getOverlay()->deleteChoiceForm("quad3dList");
				_isChoosingQuad3d = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("quad3dList"))
		{
			_gui->getOverlay()->deleteChoiceForm("quad3dList");
			_isChoosingQuad3d = false;
			_isDeletingQuad3d = false;
		}
		else
		{
			if(!_hoveredQuadId.empty())
			{
				_fe3d->quad3d_setVisible(_hoveredQuadId, false);
				_hoveredQuadId = "";
			}
		}
	}
}

void Quad3dEditor::_updateQuad3dDeleting()
{
	if(_isDeletingQuad3d && !_currentQuadId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->quad3d_delete(_currentQuadId);

			_loadedQuadIds.erase(remove(_loadedQuadIds.begin(), _loadedQuadIds.end(), _currentQuadId), _loadedQuadIds.end());
			_currentQuadId = "";
			_isDeletingQuad3d = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d->quad3d_setVisible(_currentQuadId, false);

			_currentQuadId = "";
			_isDeletingQuad3d = false;
		}
	}
}