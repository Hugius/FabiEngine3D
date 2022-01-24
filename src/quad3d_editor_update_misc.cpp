#include "quad3d_editor.hpp"
#include "logger.hpp"

using std::max;

void Quad3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonViewEnabled())
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
		_fe3d->gfx_setShadowEyeOffset(fvec3(cameraLookat + fvec3(distance * 2.0f)));
		_fe3d->gfx_setShadowCenterOffset(cameraLookat);
		_fe3d->gfx_setShadowSize(distance * 4.0f);
		_fe3d->gfx_setShadowReach(distance * 8.0f);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->camera_isThirdPersonViewEnabled())
			{
				_fe3d->camera_disableThirdPersonView();
			}
			else
			{
				_fe3d->camera_enableThirdPersonView(_fe3d->camera_getThirdPersonYaw(), _fe3d->camera_getThirdPersonPitch());
			}
		}
	}

	if(_fe3d->camera_isThirdPersonViewEnabled())
	{
		if(_gui->getOverlay()->isFocused())
		{
			_fe3d->camera_disableThirdPersonView();
		}
	}
}

void Quad3dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_R))
		{
			if(_fe3d->model_isVisible("@@box"))
			{
				_fe3d->model_setVisible("@@box", false);
			}
			else
			{
				_fe3d->model_setVisible("@@box", true);
			}
		}

		if(!_currentQuadID.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d->quad3d_isWireframed(_currentQuadID))
				{
					_fe3d->quad3d_setWireframed(_currentQuadID, false);
				}
				else
				{
					_fe3d->quad3d_setWireframed(_currentQuadID, true);
				}
			}
		}
	}
}

void Quad3dEditor::_updateQuad3dCreating()
{
	if(_isCreatingQuad3d)
	{
		string newQuadID;

		if(_gui->getOverlay()->checkValueForm("quad3dCreate", newQuadID, {_currentQuadID}))
		{
			if(newQuadID.find(' ') != string::npos)
			{
				Logger::throwWarning("Quad3d id cannot contain any spaces!");
				return;
			}

			if(newQuadID.find('@') != string::npos)
			{
				Logger::throwWarning("Quad3d id cannot contain '@'!");
				return;
			}

			newQuadID = ("@" + newQuadID);

			if(find(_loadedQuadIDs.begin(), _loadedQuadIDs.end(), newQuadID) != _loadedQuadIDs.end())
			{
				Logger::throwWarning("Quad3d with id \"" + newQuadID.substr(1) + "\" already exists!");
				return;
			}

			_fe3d->quad3d_create(newQuadID, false);

			if(_fe3d->quad3d_isExisting(newQuadID))
			{
				_currentQuadID = newQuadID;
				_loadedQuadIDs.push_back(newQuadID);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quadID")->getEntityID(), "Quad3d: " + newQuadID.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityID(), true);
				_isCreatingQuad3d = false;
			}
		}
	}
}

void Quad3dEditor::_updateQuad3dChoosing()
{
	if(_isChoosingQuad3d)
	{
		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("quad3dList");

		if(!selectedButtonID.empty())
		{
			if(_hoveredQuadID.empty())
			{
				_hoveredQuadID = ("@" + selectedButtonID);
				_fe3d->quad3d_setVisible(_hoveredQuadID, true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentQuadID = ("@" + selectedButtonID);
				_hoveredQuadID = "";

				if(!_isDeletingQuad3d)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quadID")->getEntityID(), "Quad3d: " + _currentQuadID.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityID(), true);
				}

				_fe3d->quad3d_setVisible(_currentQuadID, true);
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
			if(!_hoveredQuadID.empty())
			{
				_fe3d->quad3d_setVisible(_hoveredQuadID, false);
				_hoveredQuadID = "";
			}
		}
	}
}

void Quad3dEditor::_updateQuad3dDeleting()
{
	if(_isDeletingQuad3d && !_currentQuadID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->quad3d_delete(_currentQuadID);

			_loadedQuadIDs.erase(remove(_loadedQuadIDs.begin(), _loadedQuadIDs.end(), _currentQuadID), _loadedQuadIDs.end());
			_currentQuadID = "";
			_isDeletingQuad3d = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d->quad3d_setVisible(_currentQuadID, false);

			_currentQuadID = "";
			_isDeletingQuad3d = false;
		}
	}
}