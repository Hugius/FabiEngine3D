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
			_fe3d->model_setVisible(GRID_ID, !_fe3d->model_isVisible(GRID_ID));
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
		{
			_fe3d->model_setVisible(BOX_ID, !_fe3d->model_isVisible(BOX_ID));
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
		auto waterId = _gui->getOverlay()->getValueFormContent();

		if(waterId.empty())
		{
			Logger::throwWarning("Water ID cannot be empty");

			return;
		}

		if(any_of(waterId.begin(), waterId.end(), isspace))
		{
			Logger::throwWarning("Water ID cannot contain any spaces");

			return;
		}

		if(any_of(waterId.begin(), waterId.end(), isupper))
		{
			Logger::throwWarning("Water ID cannot contain any capitals");

			return;
		}

		if(waterId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Water ID cannot contain any specials");

			return;
		}

		waterId = ("@" + waterId);

		if(find(_loadedWaterIds.begin(), _loadedWaterIds.end(), waterId) != _loadedWaterIds.end())
		{
			Logger::throwWarning("Water already exists");

			return;
		}

		_fe3d->water_create(waterId);
		_fe3d->water_select(waterId);

		_loadedWaterIds.push_back(waterId);

		sort(_loadedWaterIds.begin(), _loadedWaterIds.end());

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
		_gui->getOverlay()->getTextField(WATER_TITLE_ID)->setTextContent("Water: " + waterId.substr(1));
		_gui->getOverlay()->getTextField(WATER_TITLE_ID)->setVisible(true);

		_currentWaterId = waterId;
	}
}

void WaterEditor::_updateWaterChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editWater") || (_gui->getOverlay()->getChoiceFormId() == "deleteWater"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(_isWaterHovered)
			{
				_fe3d->water_select("");

				_isWaterHovered = false;
			}
		}
		else
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
					_gui->getOverlay()->openAnswerForm("deleteWater", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

					_gui->getOverlay()->getTextField(WATER_TITLE_ID)->setTextContent("Water: " + _currentWaterId.substr(1));
					_gui->getOverlay()->getTextField(WATER_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(_isWaterHovered)
		{
			_fe3d->water_select("");

			_isWaterHovered = false;
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
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentWaterId = "";
		}
	}
}

void WaterEditor::_updateSkyChoosing()
{
	if(_gui->getOverlay()->getChoiceFormId() == "selectSky")
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(_isSkyHovered)
			{
				_fe3d->sky_select("");

				_isSkyHovered = false;
			}
		}
		else
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
	else
	{
		if(_isSkyHovered)
		{
			_fe3d->sky_select("");

			_isSkyHovered = false;
		}
	}
}