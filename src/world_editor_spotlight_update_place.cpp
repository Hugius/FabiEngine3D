#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updateSpotlightPlacing()
{
	if(!_currentEditorSpotlightId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->spotlight_getPosition(TORCH_ID);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->spotlight_setPosition(_currentEditorSpotlightId, fvec3(value, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(TORCH_ID, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->spotlight_setPosition(_currentEditorSpotlightId, fvec3(newPosition.x, value, newPosition.z));
				_fe3d->model_setBasePosition(TORCH_ID, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				if(_fe3d->spotlight_getIds().size() == _fe3d->spotlight_getMaxCount())
				{
					Logger::throwWarning("spotlight maximum is reached");

					_fe3d->spotlight_setVisible(_currentEditorSpotlightId, false);
					_fe3d->model_setVisible(TORCH_ID, false);

					_currentEditorSpotlightId = "";

					return;
				}

				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newSpotlightId = (_currentEditorSpotlightId.substr(1) + "_" + to_string(_spotlightIdCounter));
				const auto newModelId = ("@@torch_" + newSpotlightId);

				_spotlightIdCounter++;

				_duplicator->copyEditorSpotlight(newSpotlightId, _currentEditorSpotlightId);

				_fe3d->spotlight_setPosition(newSpotlightId, fvec3(newPosition.x, newPosition.y, value));

				_loadedSpotlightIds.push_back(newSpotlightId);

				sort(_loadedSpotlightIds.begin(), _loadedSpotlightIds.end());

				_fe3d->model_create(newModelId, TORCH_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, value));
				_fe3d->model_setBaseRotation(newModelId, fvec3(0.0f, 0.0f, DEFAULT_SPOTLIGHT_PITCH));
				_fe3d->model_setBaseSize(newModelId, TORCH_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);
				_fe3d->model_setColor(newModelId, "", _fe3d->spotlight_getColor(newSpotlightId));

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_bindToParent(newModelId, newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, TORCH_AABB_SIZE);

				_fe3d->spotlight_setVisible(_currentEditorSpotlightId, false);
				_fe3d->model_setVisible(TORCH_ID, false);

				_currentEditorSpotlightId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->spotlight_setVisible(_currentEditorSpotlightId, false);
				_fe3d->model_setVisible(TORCH_ID, false);

				_currentEditorSpotlightId = "";
			}
		}
		else
		{
			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->spotlight_setVisible(_currentEditorSpotlightId, false);
				_fe3d->model_setVisible(TORCH_ID, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->spotlight_setVisible(_currentEditorSpotlightId, false);
				_fe3d->model_setVisible(TORCH_ID, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->spotlight_setVisible(_currentEditorSpotlightId, false);
				_fe3d->model_setVisible(TORCH_ID, false);

				_currentEditorSpotlightId = "";

				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->spotlight_setVisible(_currentEditorSpotlightId, false);
				_fe3d->model_setVisible(TORCH_ID, false);

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + SPOTLIGHT_TERRAIN_OFFSET);

			_fe3d->spotlight_setVisible(_currentEditorSpotlightId, true);
			_fe3d->spotlight_setPosition(_currentEditorSpotlightId, newPosition);
			_fe3d->model_setVisible(TORCH_ID, true);
			_fe3d->model_setBasePosition(TORCH_ID, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				if(_fe3d->spotlight_getIds().size() == _fe3d->spotlight_getMaxCount())
				{
					Logger::throwWarning("spotlight maximum is reached");

					return;
				}

				const auto newSpotlightId = (_currentEditorSpotlightId.substr(1) + "_" + to_string(_spotlightIdCounter));
				const auto newModelId = ("@@torch_" + newSpotlightId);

				_spotlightIdCounter++;

				_duplicator->copyEditorSpotlight(newSpotlightId, _currentEditorSpotlightId);

				_fe3d->spotlight_setPosition(newSpotlightId, newPosition);

				_loadedSpotlightIds.push_back(newSpotlightId);

				sort(_loadedSpotlightIds.begin(), _loadedSpotlightIds.end());

				_fe3d->model_create(newModelId, TORCH_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseRotation(newModelId, fvec3(0.0f, 0.0f, DEFAULT_SPOTLIGHT_PITCH));
				_fe3d->model_setBaseSize(newModelId, TORCH_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);
				_fe3d->model_setColor(newModelId, "", _fe3d->spotlight_getColor(newSpotlightId));

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_bindToParent(newModelId, newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, TORCH_AABB_SIZE);
			}
		}
	}
}