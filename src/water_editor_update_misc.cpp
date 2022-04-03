#include "water_editor.hpp"
#include "logger.hpp"

void WaterEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		auto scrollOffset = _fe3d->input_getMouseWheelY();
		auto cameraDistance = _fe3d->camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d->camera_setThirdPersonDistance(cameraDistance);

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
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

void WaterEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
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

		//if(_gui->getOverlay()->checkValueForm("waterCreate", newWaterId, {}))
		{
			if(newWaterId.empty())
			{
				Logger::throwWarning("Water ID cannot be empty");
				return;
			}

			if(any_of(newWaterId.begin(), newWaterId.end(), isspace))
			{
				Logger::throwWarning("Water ID cannot contain any spaces");
				return;
			}

			if(any_of(newWaterId.begin(), newWaterId.end(), isupper))
			{
				Logger::throwWarning("Water ID cannot contain any capitals");
				return;
			}

			newWaterId = ("@" + newWaterId);

			if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), newWaterId) != _loadedEntityIds.end())
			{
				Logger::throwWarning("Water already exists");
				return;
			}

			_currentWaterId = newWaterId;
			_loadedEntityIds.push_back(newWaterId);
			sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

			_fe3d->water_create(newWaterId);
			_fe3d->water_select(newWaterId);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			_gui->getOverlay()->getTextField("waterId")->setTextContent("Water: " + newWaterId.substr(1));
			_gui->getOverlay()->getTextField("waterId")->setVisible(true);
			_isCreatingWater = false;
		}
	}
}

void WaterEditor::_updateWaterChoosing()
{
	if(_isChoosingWater)
	{
		const auto selectedOptionId = _gui->getOverlay()->getSelectedChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			_fe3d->water_select("@" + selectedOptionId);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentWaterId = _fe3d->water_getSelectedId();

				if(_isDeletingWater)
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

					_gui->getOverlay()->getTextField("waterId")->setTextContent("Water: " + _currentWaterId.substr(1));
					_gui->getOverlay()->getTextField("waterId")->setVisible(true);
				}

				_gui->getOverlay()->closeChoiceForm();
				_isChoosingWater = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled())
		{
			_gui->getOverlay()->closeChoiceForm();
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
	if(_isDeletingWater && !_isChoosingWater)
	{
		if(_gui->getOverlay()->isAnswerFormAccepted())
		{
			_fe3d->water_delete(_currentWaterId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentWaterId), _loadedEntityIds.end());
			_currentWaterId = "";
			_isDeletingWater = false;

			_gui->getOverlay()->closeAnswerForm();
		}
		if(_gui->getOverlay()->isAnswerFormDenied())
		{
			_currentWaterId = "";
			_isDeletingWater = false;

			_gui->getOverlay()->closeAnswerForm();
		}
	}
}