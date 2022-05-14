#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updateSpotlightPlacing()
{
	if(_isPlacingSpotlight)
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->spotlight_getPosition(SPOTLIGHT_MODEL_ID);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->spotlight_setPosition(SPOTLIGHT_MODEL_ID, fvec3(value, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(SPOTLIGHT_MODEL_ID, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->spotlight_setPosition(SPOTLIGHT_MODEL_ID, fvec3(newPosition.x, value, newPosition.z));
				_fe3d->model_setBasePosition(SPOTLIGHT_MODEL_ID, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newId = ("spotlight_" + to_string(_idCounter));
				const auto newModelId = ("@@spotlight_" + newId);

				_idCounter++;

				if(_fe3d->spotlight_getIds().size() == _fe3d->spotlight_getMaxCount())
				{
					Logger::throwWarning("spotlight maximum is reached");

					return;
				}

				_loadedSpotlightIds.push_back(newId);

				_fe3d->spotlight_create(newId);
				_fe3d->spotlight_setPosition(newId, fvec3(newPosition.x, newPosition.y, value));
				_fe3d->spotlight_setPitch(newId, SPOTLIGHT_PITCH);
				_fe3d->spotlight_setIntensity(newId, SPOTLIGHT_INTENSITY);
				_fe3d->spotlight_setAngle(newId, SPOTLIGHT_ANGLE);
				_fe3d->spotlight_setDistance(newId, SPOTLIGHT_DISTANCE);

				_fe3d->model_create(newModelId, SPOTLIGHT_MODEL_PATH);
				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, value));
				_fe3d->model_setBaseRotation(newModelId, fvec3(0.0f, 0.0f, SPOTLIGHT_PITCH));
				_fe3d->model_setBaseSize(newModelId, SPOTLIGHT_MODEL_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, SPOTLIGHT_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);

				_fe3d->spotlight_setVisible(SPOTLIGHT_MODEL_ID, false);
				_fe3d->model_setVisible(SPOTLIGHT_MODEL_ID, false);

				_isPlacingSpotlight = false;
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->spotlight_setVisible(SPOTLIGHT_MODEL_ID, false);
				_fe3d->model_setVisible(SPOTLIGHT_MODEL_ID, false);

				_isPlacingSpotlight = false;
			}
		}
		else
		{
			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->spotlight_setVisible(SPOTLIGHT_MODEL_ID, false);
				_fe3d->model_setVisible(SPOTLIGHT_MODEL_ID, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->spotlight_setVisible(SPOTLIGHT_MODEL_ID, false);
				_fe3d->model_setVisible(SPOTLIGHT_MODEL_ID, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->spotlight_setVisible(SPOTLIGHT_MODEL_ID, false);
				_fe3d->model_setVisible(SPOTLIGHT_MODEL_ID, false);
				_isPlacingSpotlight = false;

				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->spotlight_setVisible(SPOTLIGHT_MODEL_ID, false);
				_fe3d->model_setVisible(SPOTLIGHT_MODEL_ID, false);

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + SPOTLIGHT_TERRAIN_OFFSET);
			_fe3d->spotlight_setVisible(SPOTLIGHT_MODEL_ID, true);
			_fe3d->spotlight_setPosition(SPOTLIGHT_MODEL_ID, newPosition);
			_fe3d->model_setVisible(SPOTLIGHT_MODEL_ID, true);
			_fe3d->model_setBasePosition(SPOTLIGHT_MODEL_ID, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				auto newId = ("spotlight_" + to_string(_idCounter));
				auto newModelId = ("@@spotlight_" + newId);

				_idCounter++;

				if(_fe3d->spotlight_getIds().size() == _fe3d->spotlight_getMaxCount())
				{
					Logger::throwWarning("spotlight maximum is reached");

					return;
				}

				_loadedSpotlightIds.push_back(newId);

				_fe3d->spotlight_create(newId);
				_fe3d->spotlight_setPosition(newId, newPosition);
				_fe3d->spotlight_setPitch(newId, SPOTLIGHT_PITCH);
				_fe3d->spotlight_setIntensity(newId, SPOTLIGHT_INTENSITY);
				_fe3d->spotlight_setAngle(newId, SPOTLIGHT_ANGLE);
				_fe3d->spotlight_setDistance(newId, SPOTLIGHT_DISTANCE);

				_fe3d->model_create(newModelId, SPOTLIGHT_MODEL_PATH);
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseRotation(newModelId, fvec3(0.0f, 0.0f, SPOTLIGHT_PITCH));
				_fe3d->model_setBaseSize(newModelId, SPOTLIGHT_MODEL_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, SPOTLIGHT_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
	}
}