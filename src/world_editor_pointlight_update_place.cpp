#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updatePointlightPlacing()
{
	if(!_currentTemplatePointlightId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->pointlight_getPosition(_currentTemplatePointlightId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->pointlight_setPosition(_currentTemplatePointlightId, fvec3(value, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(LAMP_ID, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->pointlight_setPosition(_currentTemplatePointlightId, fvec3(newPosition.x, value, newPosition.z));
				_fe3d->model_setBasePosition(LAMP_ID, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				if(_fe3d->pointlight_getIds().size() == _fe3d->pointlight_getMaxCount())
				{
					Logger::throwWarning("pointlight maximum is reached");

					_fe3d->pointlight_setVisible(_currentTemplatePointlightId, false);
					_fe3d->model_setVisible(LAMP_ID, false);

					_currentTemplatePointlightId = "";

					return;
				}

				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newPointlightId = (_currentTemplatePointlightId.substr(1) + "_" + to_string(_pointlightIdCounter));
				const auto newModelId = ("@@lamp_" + newPointlightId);

				_pointlightIdCounter++;

				_duplicator->copyTemplatePointlight(newPointlightId, _currentTemplatePointlightId);

				_fe3d->pointlight_setPosition(newPointlightId, fvec3(newPosition.x, newPosition.y, value));

				_loadedPointlightIds.push_back(newPointlightId);

				sort(_loadedPointlightIds.begin(), _loadedPointlightIds.end());

				_fe3d->model_create(newModelId, LAMP_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, value));
				_fe3d->model_setBaseSize(newModelId, LAMP_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);
				_fe3d->model_setColor(newModelId, "", _fe3d->pointlight_getColor(newPointlightId));

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, LAMP_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);

				_fe3d->pointlight_setVisible(_currentTemplatePointlightId, false);
				_fe3d->model_setVisible(LAMP_ID, false);

				_currentTemplatePointlightId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->pointlight_setVisible(_currentTemplatePointlightId, false);
				_fe3d->model_setVisible(LAMP_ID, false);

				_currentTemplatePointlightId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->pointlight_setVisible(_currentTemplatePointlightId, false);
				_fe3d->model_setVisible(LAMP_ID, false);

				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->pointlight_setVisible(_currentTemplatePointlightId, false);
				_fe3d->model_setVisible(LAMP_ID, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->pointlight_setVisible(_currentTemplatePointlightId, false);
				_fe3d->model_setVisible(LAMP_ID, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->pointlight_setVisible(_currentTemplatePointlightId, false);
				_fe3d->model_setVisible(LAMP_ID, false);

				_currentTemplatePointlightId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + POINTLIGHT_TERRAIN_OFFSET);

			_fe3d->pointlight_setVisible(_currentTemplatePointlightId, true);
			_fe3d->pointlight_setPosition(_currentTemplatePointlightId, newPosition);
			_fe3d->model_setVisible(LAMP_ID, true);
			_fe3d->model_setBasePosition(LAMP_ID, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				if(_fe3d->pointlight_getIds().size() == _fe3d->pointlight_getMaxCount())
				{
					Logger::throwWarning("pointlight maximum is reached");

					return;
				}

				const auto newPointlightId = (_currentTemplatePointlightId.substr(1) + "_" + to_string(_pointlightIdCounter));
				const auto newModelId = ("@@lamp_" + newPointlightId);

				_pointlightIdCounter++;

				_duplicator->copyTemplatePointlight(newPointlightId, _currentTemplatePointlightId);

				_fe3d->pointlight_setPosition(newPointlightId, newPosition);

				_loadedPointlightIds.push_back(newPointlightId);

				sort(_loadedPointlightIds.begin(), _loadedPointlightIds.end());

				_fe3d->model_create(newModelId, LAMP_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseSize(newModelId, LAMP_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);
				_fe3d->model_setColor(newModelId, "", _fe3d->pointlight_getColor(newPointlightId));

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, LAMP_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
	}
}