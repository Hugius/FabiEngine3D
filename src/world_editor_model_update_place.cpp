#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateModelPlacing()
{
	if(!_currentTemplateModelId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->model_getBasePosition(_currentTemplateModelId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->model_setBasePosition(_currentTemplateModelId, fvec3(content, newPosition.y, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->model_setBasePosition(_currentTemplateModelId, fvec3(newPosition.x, content, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				const auto newId = (_currentTemplateModelId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_worldUtilities->copyTemplateModel(newId, _currentTemplateModelId);

				_loadedModelIds.insert({newId, _currentTemplateModelId});

				_fe3d->model_setBasePosition(newId, fvec3(newPosition.x, newPosition.y, content));

				_fe3d->model_setVisible(_currentTemplateModelId, false);

				_currentTemplateModelId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);

				_currentTemplateModelId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				return;
			}

			if(!_fe3d->misc_isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				return;
			}

			if(_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				return;
			}

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_MIDDLE))
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);
				_currentTemplateModelId = "";
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + MODEL_TERRAIN_OFFSET);
			_fe3d->model_setVisible(_currentTemplateModelId, true);
			_fe3d->model_setBasePosition(_currentTemplateModelId, newPosition);

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
			{
				auto newId = (_currentTemplateModelId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_worldUtilities->copyTemplateModel(newId, _currentTemplateModelId);
				_loadedModelIds.insert({newId, _currentTemplateModelId});

				_fe3d->model_setBasePosition(newId, newPosition);
			}
		}
	}
}