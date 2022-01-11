#include "billboard_editor.hpp"
#include "logger.hpp"

using std::max;

void BillboardEditor::_updateCamera()
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

		_fe3d->quad_setVisible("@@cursor", false);

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

void BillboardEditor::_updateMiscellaneous()
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

		if(!_currentBillboardID.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d->billboard_isWireframed(_currentBillboardID))
				{
					_fe3d->billboard_setWireframed(_currentBillboardID, false);
				}
				else
				{
					_fe3d->billboard_setWireframed(_currentBillboardID, true);
				}
			}
		}
	}
}

void BillboardEditor::_updateBillboardCreating()
{
	if(_isCreatingBillboard)
	{
		string newBillboardID;

		if(_gui->getOverlay()->checkValueForm("billboardCreate", newBillboardID, {_currentBillboardID}))
		{
			if(newBillboardID.find(' ') != string::npos)
			{
				Logger::throwWarning("Billboard ID cannot contain any spaces!");
				return;
			}

			if(newBillboardID.find('@') != string::npos)
			{
				Logger::throwWarning("Billboard ID cannot contain '@'!");
				return;
			}

			newBillboardID = ("@" + newBillboardID);

			if(find(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), newBillboardID) != _loadedBillboardIDs.end())
			{
				Logger::throwWarning("Billboard with ID \"" + newBillboardID.substr(1) + "\" already exists!");
				return;
			}

			_fe3d->billboard_create(newBillboardID, false);

			if(_fe3d->billboard_isExisting(newBillboardID))
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");

				_currentBillboardID = newBillboardID;
				_loadedBillboardIDs.push_back(newBillboardID);

				_fe3d->text_setContent(_gui->getOverlay()->getTextField("billboardID")->getEntityID(), "Billboard: " + newBillboardID.substr(1), 0.025f);
				_fe3d->text_setVisible(_gui->getOverlay()->getTextField("billboardID")->getEntityID(), true);
				_isCreatingBillboard = false;
			}
		}
	}
}

void BillboardEditor::_updateBillboardChoosing()
{
	if(_isChoosingBillboard)
	{
		if(!_hoveredBillboardID.empty())
		{
			_fe3d->billboard_setVisible(_hoveredBillboardID, false);
		}

		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("billboardList");

		if(!selectedButtonID.empty())
		{
			_hoveredBillboardID = ("@" + selectedButtonID);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentBillboardID = ("@" + selectedButtonID);
				_hoveredBillboardID = "";

				if(!_isDeletingBillboard)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					_fe3d->text_setContent(_gui->getOverlay()->getTextField("billboardID")->getEntityID(), "Billboard: " + _currentBillboardID.substr(1), 0.025f);
					_fe3d->text_setVisible(_gui->getOverlay()->getTextField("billboardID")->getEntityID(), true);
				}

				_fe3d->billboard_setVisible(_currentBillboardID, true);
				_gui->getOverlay()->deleteChoiceForm("billboardList");
				_isChoosingBillboard = false;
			}
			else
			{
				_hoveredBillboardID = ("@" + selectedButtonID);
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
			_hoveredBillboardID = "";
		}

		if(!_hoveredBillboardID.empty())
		{
			_fe3d->billboard_setVisible(_hoveredBillboardID, true);
		}
	}
}

void BillboardEditor::_updateBillboardDeleting()
{
	if(_isDeletingBillboard && !_currentBillboardID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->billboard_delete(_currentBillboardID);

			_loadedBillboardIDs.erase(remove(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), _currentBillboardID), _loadedBillboardIDs.end());
			_currentBillboardID = "";
			_isDeletingBillboard = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d->billboard_setVisible(_currentBillboardID, false);

			_currentBillboardID = "";
			_isDeletingBillboard = false;
		}
	}
}