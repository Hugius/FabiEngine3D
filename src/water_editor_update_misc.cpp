#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WaterEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		const auto distanceOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_Q)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_E)));

		_fe3d->camera_setThirdPersonDistance(max(MIN_CAMERA_DISTANCE, (_fe3d->camera_getThirdPersonDistance() - (distanceOffset * CAMERA_DISTANCE_SPEED))));

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

void WaterEditor::_updateMiscellaneous()
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

		if(!_currentWaterId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->water_setWireframed(_currentWaterId, !_fe3d->water_isWireframed(_currentWaterId));
			}
		}
	}
}

void WaterEditor::_updateWaterCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createWater") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newWaterId = _gui->getOverlay()->getValueFormContent();

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

		if(find(_loadedWaterIds.begin(), _loadedWaterIds.end(), newWaterId) != _loadedWaterIds.end())
		{
			Logger::throwWarning("Water already exists");

			return;
		}

		_currentWaterId = newWaterId;
		_loadedWaterIds.push_back(newWaterId);
		sort(_loadedWaterIds.begin(), _loadedWaterIds.end());

		_fe3d->water_create(newWaterId);
		_fe3d->water_select(newWaterId);

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
		_gui->getOverlay()->getTextField("waterId")->setTextContent("Water: " + newWaterId.substr(1));
		_gui->getOverlay()->getTextField("waterId")->setVisible(true);
	}
}

void WaterEditor::_updateWaterChoosing()
{
	if(_isWaterHovered)
	{
		_fe3d->water_select("");

		_isWaterHovered = false;
	}

	if((_gui->getOverlay()->getChoiceFormId() == "editWater") || (_gui->getOverlay()->getChoiceFormId() == "deleteWater"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(!_isWaterHovered)
			{
				_isWaterHovered = true;

				_fe3d->water_select("@" + selectedOptionId);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentWaterId = _fe3d->water_getSelectedId();
				_isWaterHovered = false;

				if(_gui->getOverlay()->getChoiceFormId() == "deleteWater")
				{
					_gui->getOverlay()->openAnswerForm("deleteWater", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

					_gui->getOverlay()->getTextField("waterId")->setTextContent("Water: " + _currentWaterId.substr(1));
					_gui->getOverlay()->getTextField("waterId")->setVisible(true);
				}
			}
		}
	}
}

void WaterEditor::_updateWaterDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteWater") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->water_delete(_currentWaterId);

			_loadedWaterIds.erase(remove(_loadedWaterIds.begin(), _loadedWaterIds.end(), _currentWaterId), _loadedWaterIds.end());
			_currentWaterId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentWaterId = "";
		}
	}
}

void WaterEditor::_updateSkyChoosing()
{
	if(_isSkyHovered)
	{
		_fe3d->sky_select("");

		_isSkyHovered = false;
	}

	if(_gui->getOverlay()->getChoiceFormId() == "selectSky")
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(!_isSkyHovered)
			{
				_isSkyHovered = true;

				_fe3d->sky_select("@" + selectedOptionId);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_isSkyHovered = false;
			}
		}
	}
}