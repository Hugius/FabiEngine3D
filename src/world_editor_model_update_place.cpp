#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updateModelPlacing()
{
	if(!_currentTemplateModelId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			auto newPosition = _fe3d->model_getBasePosition(_currentTemplateModelId);
			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->model_setBasePosition(_currentTemplateModelId, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				auto newId = string(_currentTemplateModelId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_copyTemplateModel(newId, _currentTemplateModelId, newPosition, false);
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), false);
				_currentTemplateModelId = "";
			}
		}
		else
		{
			if(!_fe3d->misc_isCursorInsideViewport() || _gui->getOverlay()->isFocused())
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), false);
				_currentTemplateModelId = "";
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + MODEL_TERRAIN_OFFSET);
			_fe3d->model_setVisible(_currentTemplateModelId, true);
			_fe3d->model_setBasePosition(_currentTemplateModelId, newPosition);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				auto newId = string(_currentTemplateModelId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_copyTemplateModel(newId, _currentTemplateModelId, newPosition, false);
			}
		}
	}
}