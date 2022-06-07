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
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->model_setBasePosition(_currentTemplateModelId, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->model_setBasePosition(_currentTemplateModelId, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newModelId = (_currentTemplateModelId.substr(1) + "_" + to_string(_modelIdCounter));

				_modelIdCounter++;

				_duplicator->copyTemplateModel(newModelId, _currentTemplateModelId);

				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, value));

				_originalModelPositions.insert({newModelId, _fe3d->model_getBasePosition(newModelId)});
				_originalModelRotations.insert({newModelId, _fe3d->model_getBaseRotation(newModelId)});
				_originalModelSizes.insert({newModelId, _fe3d->model_getBaseSize(newModelId)});

				_loadedModelIds.push_back(newModelId);

				sort(_loadedModelIds.begin(), _loadedModelIds.end());

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

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->model_setVisible(_currentTemplateModelId, false);

				_currentTemplateModelId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + MODEL_TERRAIN_OFFSET);

			_fe3d->model_setVisible(_currentTemplateModelId, true);
			_fe3d->model_setBasePosition(_currentTemplateModelId, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				const auto newModelId = (_currentTemplateModelId.substr(1) + "_" + to_string(_modelIdCounter));

				_modelIdCounter++;

				_duplicator->copyTemplateModel(newModelId, _currentTemplateModelId);

				_fe3d->model_setBasePosition(newModelId, newPosition);

				_originalModelPositions.insert({newModelId, _fe3d->model_getBasePosition(newModelId)});
				_originalModelRotations.insert({newModelId, _fe3d->model_getBaseRotation(newModelId)});
				_originalModelSizes.insert({newModelId, _fe3d->model_getBaseSize(newModelId)});

				_loadedModelIds.push_back(newModelId);

				sort(_loadedModelIds.begin(), _loadedModelIds.end());
			}
		}
	}
}