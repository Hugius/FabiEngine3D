#include "water_editor.hpp"
#include "logger.hpp"

void WaterEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonViewEnabled())
	{
		auto scrollOffset = _fe3d->input_getMouseWheelY();
		auto cameraDistance = _fe3d->camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d->camera_setThirdPersonDistance(cameraDistance);

		_fe3d->quad_setVisible("@@cursor", false);
	}

	if(!_gui.getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
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
		if(_gui.getOverlay()->isFocused())
		{
			_fe3d->camera_disableThirdPersonView();
		}
	}
}

void WaterEditor::_updateMiscellaneous()
{
	if(!_gui.getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
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

		if(!_currentWaterID.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d->water_isWireframed(_currentWaterID))
				{
					_fe3d->water_setWireframed(_currentWaterID, false);
				}
				else
				{
					_fe3d->water_setWireframed(_currentWaterID, true);
				}
			}
		}
	}
}

void WaterEditor::_updateWaterCreating()
{
	if(_isCreatingWater)
	{
		string newWaterID;

		if(_gui.getOverlay()->checkValueForm("waterCreate", newWaterID, {}))
		{
			if(newWaterID.find(' ') != string::npos)
			{
				Logger::throwWarning("Water ID cannot contain any spaces!");
				return;
			}

			if(newWaterID.find('@') != string::npos)
			{
				Logger::throwWarning("Water ID cannot contain '@'!");
				return;
			}

			newWaterID = ("@" + newWaterID);

			if(find(_loadedWaterIDs.begin(), _loadedWaterIDs.end(), newWaterID) != _loadedWaterIDs.end())
			{
				Logger::throwWarning("Water with ID \"" + newWaterID.substr(1) + "\" already exists!");
				return;
			}

			_fe3d->water_create(newWaterID);

			if(_fe3d->water_isExisting(newWaterID))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

				_currentWaterID = newWaterID;
				_loadedWaterIDs.push_back(newWaterID);
				_fe3d->water_select(newWaterID);

				_fe3d->text_setContent(_gui.getOverlay()->getTextField("waterID")->getEntityID(), "Water: " + newWaterID.substr(1), 0.025f);
				_fe3d->text_setVisible(_gui.getOverlay()->getTextField("waterID")->getEntityID(), true);
				_isCreatingWater = false;
			}
		}
	}
}

void WaterEditor::_updateWaterChoosing()
{
	if(_isChoosingWater)
	{
		auto selectedButtonID = _gui.getOverlay()->checkChoiceForm("waterList");

		_fe3d->water_select("");

		if(!selectedButtonID.empty())
		{
			_fe3d->water_select("@" + selectedButtonID);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentWaterID = ("@" + selectedButtonID);

				if(!_isDeletingWater)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
					_fe3d->text_setContent(_gui.getOverlay()->getTextField("waterID")->getEntityID(), "Water: " + _currentWaterID.substr(1), 0.025f);
					_fe3d->text_setVisible(_gui.getOverlay()->getTextField("waterID")->getEntityID(), true);
				}

				_gui.getOverlay()->deleteChoiceForm("waterList");
				_isChoosingWater = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("waterList"))
		{
			_gui.getOverlay()->deleteChoiceForm("waterList");
			_isChoosingWater = false;
			_isDeletingWater = false;
		}
	}
}

void WaterEditor::_updateWaterDeleting()
{
	if(_isDeletingWater && !_currentWaterID.empty())
	{
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->water_delete(_currentWaterID);

			_loadedWaterIDs.erase(remove(_loadedWaterIDs.begin(), _loadedWaterIDs.end(), _currentWaterID), _loadedWaterIDs.end());
			_currentWaterID = "";
			_isDeletingWater = false;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d->water_select("");

			_currentWaterID = "";
			_isDeletingWater = false;
		}
	}
}