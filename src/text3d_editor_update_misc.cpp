#include "text3d_editor.hpp"
#include "logger.hpp"

using std::max;

void Text3dEditor::_updateCamera()
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

void Text3dEditor::_updateMiscellaneous()
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

		if(!_currentTextID.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d->text3d_isWireframed(_currentTextID))
				{
					_fe3d->text3d_setWireframed(_currentTextID, false);
				}
				else
				{
					_fe3d->text3d_setWireframed(_currentTextID, true);
				}
			}
		}
	}
}

void Text3dEditor::_updateText3dCreating()
{
	if(_isCreatingText3d)
	{
		string newTextID;

		if(_gui->getOverlay()->checkValueForm("text3dCreate", newTextID, {_currentTextID}))
		{
			if(newTextID.find(' ') != string::npos)
			{
				Logger::throwWarning("Text3d ID cannot contain any spaces!");
				return;
			}

			if(newTextID.find('@') != string::npos)
			{
				Logger::throwWarning("Text3d ID cannot contain '@'!");
				return;
			}

			newTextID = ("@" + newTextID);

			if(find(_loadedTextIDs.begin(), _loadedTextIDs.end(), newTextID) != _loadedTextIDs.end())
			{
				Logger::throwWarning("Text3d with ID \"" + newTextID.substr(1) + "\" already exists!");
				return;
			}

			_fe3d->text3d_create(newTextID, false);

			if(_fe3d->text3d_isExisting(newTextID))
			{
				_currentTextID = newTextID;
				_loadedTextIDs.push_back(newTextID);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("textID")->getEntityID(), "Text3d: " + newTextID.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), true);
				_isCreatingText3d = false;
			}
		}
	}
}

void Text3dEditor::_updateText3dChoosing()
{
	if(_isChoosingText3d)
	{
		if(!_hoveredTextID.empty())
		{
			_fe3d->text3d_setVisible(_hoveredTextID, false);
		}

		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("text3dList");

		if(!selectedButtonID.empty())
		{
			_hoveredTextID = ("@" + selectedButtonID);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentTextID = ("@" + selectedButtonID);
				_hoveredTextID = "";

				if(!_isDeletingText3d)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("textID")->getEntityID(), "Text3d: " + _currentTextID.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), true);
				}

				_fe3d->text3d_setVisible(_currentTextID, true);
				_gui->getOverlay()->deleteChoiceForm("text3dList");
				_isChoosingText3d = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("text3dList"))
		{
			_gui->getOverlay()->deleteChoiceForm("text3dList");
			_isChoosingText3d = false;
			_isDeletingText3d = false;
		}
		else
		{
			_hoveredTextID = "";
		}

		if(!_hoveredTextID.empty())
		{
			_fe3d->text3d_setVisible(_hoveredTextID, true);
		}
	}
}

void Text3dEditor::_updateText3dDeleting()
{
	if(_isDeletingText3d && !_currentTextID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->text3d_delete(_currentTextID);

			_loadedTextIDs.erase(remove(_loadedTextIDs.begin(), _loadedTextIDs.end(), _currentTextID), _loadedTextIDs.end());
			_currentTextID = "";
			_isDeletingText3d = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d->text3d_setVisible(_currentTextID, false);

			_currentTextID = "";
			_isDeletingText3d = false;
		}
	}
}