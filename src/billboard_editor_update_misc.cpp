#include "billboard_editor.hpp"
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
		_fe3d->gfx_setShadowEyePosition(fvec3(cameraLookat + fvec3(distance * 2.0f)));
		_fe3d->gfx_setShadowCenterPosition(cameraLookat);
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

		if(!_currentQuad3dID.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d->quad3d_isWireframed(_currentQuad3dID))
				{
					_fe3d->quad3d_setWireframed(_currentQuad3dID, false);
				}
				else
				{
					_fe3d->quad3d_setWireframed(_currentQuad3dID, true);
				}
			}
		}
	}
}

void Quad3dEditor::_updateBillboardCreating()
{
	if(_isCreatingBillboard)
	{
		string newQuad3dID;

		if(_gui->getOverlay()->checkValueForm("billboardCreate", newQuad3dID, {_currentQuad3dID}))
		{
			if(newQuad3dID.find(' ') != string::npos)
			{
				Logger::throwWarning("Billboard ID cannot contain any spaces!");
				return;
			}

			if(newQuad3dID.find('@') != string::npos)
			{
				Logger::throwWarning("Billboard ID cannot contain '@'!");
				return;
			}

			newQuad3dID = ("@" + newQuad3dID);

			if(find(_loadedQuad3dIDs.begin(), _loadedQuad3dIDs.end(), newQuad3dID) != _loadedQuad3dIDs.end())
			{
				Logger::throwWarning("Billboard with ID \"" + newQuad3dID.substr(1) + "\" already exists!");
				return;
			}

			_fe3d->quad3d_create(newQuad3dID, false);

			if(_fe3d->quad3d_isExisting(newQuad3dID))
			{
				_currentQuad3dID = newQuad3dID;
				_loadedQuad3dIDs.push_back(newQuad3dID);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quad3dID")->getEntityID(), "Billboard: " + newQuad3dID.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quad3dID")->getEntityID(), true);
				_isCreatingBillboard = false;
			}
		}
	}
}

void Quad3dEditor::_updateBillboardChoosing()
{
	if(_isChoosingBillboard)
	{
		if(!_hoveredQuad3dID.empty())
		{
			_fe3d->quad3d_setVisible(_hoveredQuad3dID, false);
		}

		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("billboardList");

		if(!selectedButtonID.empty())
		{
			_hoveredQuad3dID = ("@" + selectedButtonID);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentQuad3dID = ("@" + selectedButtonID);
				_hoveredQuad3dID = "";

				if(!_isDeletingBillboard)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quad3dID")->getEntityID(), "Billboard: " + _currentQuad3dID.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quad3dID")->getEntityID(), true);
				}

				_fe3d->quad3d_setVisible(_currentQuad3dID, true);
				_gui->getOverlay()->deleteChoiceForm("billboardList");
				_isChoosingBillboard = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("billboardList"))
		{
			_gui->getOverlay()->deleteChoiceForm("billboardList");
			_isChoosingBillboard = false;
			_isDeletingBillboard = false;
		}
		else
		{
			_hoveredQuad3dID = "";
		}

		if(!_hoveredQuad3dID.empty())
		{
			_fe3d->quad3d_setVisible(_hoveredQuad3dID, true);
		}
	}
}

void Quad3dEditor::_updateBillboardDeleting()
{
	if(_isDeletingBillboard && !_currentQuad3dID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->quad3d_delete(_currentQuad3dID);

			_loadedQuad3dIDs.erase(remove(_loadedQuad3dIDs.begin(), _loadedQuad3dIDs.end(), _currentQuad3dID), _loadedQuad3dIDs.end());
			_currentQuad3dID = "";
			_isDeletingBillboard = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d->quad3d_setVisible(_currentQuad3dID, false);

			_currentQuad3dID = "";
			_isDeletingBillboard = false;
		}
	}
}