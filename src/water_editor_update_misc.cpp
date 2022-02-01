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

		_fe3d->quad2d_setVisible("@@cursor", false);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			_fe3d->camera_setThirdPersonViewEnabled(!_fe3d->camera_isThirdPersonViewEnabled());
		}
	}

	if(_gui->getOverlay()->isFocused())
	{
		_fe3d->camera_setThirdPersonViewEnabled(false);
	}
}

void WaterEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}

		if(!_currentWaterId.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				_fe3d->water_setWireframed(_currentWaterId, !_fe3d->water_isWireframed(_currentWaterId));
			}
		}
	}
}

void WaterEditor::_updateWaterCreating()
{
	if(_isCreatingWater)
	{
		string newWaterId;

		if(_gui->getOverlay()->checkValueForm("waterCreate", newWaterId, {}))
		{
			if(newWaterId.find(' ') != string::npos)
			{
				Logger::throwWarning("Water id cannot contain any spaces!");
				return;
			}

			if(newWaterId.find('@') != string::npos)
			{
				Logger::throwWarning("Water id cannot contain '@'!");
				return;
			}

			newWaterId = ("@" + newWaterId);

			if(find(_loadedWaterIds.begin(), _loadedWaterIds.end(), newWaterId) != _loadedWaterIds.end())
			{
				Logger::throwWarning("Water with id \"" + newWaterId.substr(1) + "\" already exists!");
				return;
			}

			_fe3d->water_create(newWaterId);

			if(_fe3d->water_isExisting(newWaterId))
			{
				_fe3d->water_select(newWaterId);

				_currentWaterId = newWaterId;
				_loadedWaterIds.push_back(newWaterId);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("waterId")->getEntityId(), "Water: " + newWaterId.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("waterId")->getEntityId(), true);
				_isCreatingWater = false;
			}
		}
	}
}

void WaterEditor::_updateWaterChoosing()
{
	if(_isChoosingWater)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("waterList");

		if(!selectedButtonId.empty())
		{
			_fe3d->water_select("@" + selectedButtonId);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentWaterId = _fe3d->water_getSelectedId();

				if(!_isDeletingWater)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("waterId")->getEntityId(), "Water: " + _currentWaterId.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("waterId")->getEntityId(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("waterList");
				_isChoosingWater = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("waterList"))
		{
			_gui->getOverlay()->deleteChoiceForm("waterList");
			_isChoosingWater = false;
			_isDeletingWater = false;
		}
		else
		{
			_fe3d->water_select("");
		}
	}
}

void WaterEditor::_updateWaterDeleting()
{
	if(_isDeletingWater && !_currentWaterId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->water_delete(_currentWaterId);

			_loadedWaterIds.erase(remove(_loadedWaterIds.begin(), _loadedWaterIds.end(), _currentWaterId), _loadedWaterIds.end());
			_currentWaterId = "";
			_isDeletingWater = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentWaterId = "";
			_isDeletingWater = false;
		}
	}
}