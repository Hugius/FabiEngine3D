#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updateModelPlacing()
{
	if(!_currentTemplateModelID.empty())
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->model_getBasePosition(_currentTemplateModelID);
			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->model_setBasePosition(_currentTemplateModelID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				auto newID = (_currentTemplateModelID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

				while(_fe3d->model_isExisting(newID))
				{
					newID = (_currentTemplateModelID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				}

				_copyTemplateModel(newID, _currentTemplateModelID, newPosition, false);
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->model_setVisible(_currentTemplateModelID, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelID")->getEntityID(), false);
				_currentTemplateModelID = "";
			}
		}
		else
		{
			if(!_fe3d->misc_isCursorInsideViewport() || _gui->getOverlay()->isFocused())
			{
				_fe3d->model_setVisible(_currentTemplateModelID, false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->model_setVisible(_currentTemplateModelID, false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->model_setVisible(_currentTemplateModelID, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelID")->getEntityID(), false);
				_currentTemplateModelID = "";
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->model_setVisible(_currentTemplateModelID, false);
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + MODEL_TERRAIN_OFFSET);
			_fe3d->model_setVisible(_currentTemplateModelID, true);
			_fe3d->model_setBasePosition(_currentTemplateModelID, newPosition);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				auto newID = (_currentTemplateModelID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

				while(_fe3d->model_isExisting(newID))
				{
					newID = (_currentTemplateModelID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				}

				_copyTemplateModel(newID, _currentTemplateModelID, newPosition, false);
			}
		}
	}
}