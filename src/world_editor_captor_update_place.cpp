#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateCaptorPlacing()
{
	if(_isPlacingCaptor)
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->captor_getPosition(TEMPLATE_CAPTOR_ID);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->captor_setPosition(TEMPLATE_CAPTOR_ID, fvec3(value, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_CAPTOR_ID, fvec3(value, newPosition.y, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->captor_setPosition(TEMPLATE_CAPTOR_ID, fvec3(newPosition.x, value, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_CAPTOR_ID, fvec3(newPosition.x, value, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newId = ("captor_" + to_string(_idCounter));
				const auto newModelId = ("@@captor_" + newId);

				_idCounter++;

				_loadedCaptorIds.push_back(newId);

				_fe3d->captor_create(newId);
				_fe3d->captor_setPosition(newId, fvec3(newPosition.x, newPosition.y, value));

				_fe3d->model_create(newModelId, TEMPLATE_CAPTOR_MODEL_PATH);
				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, value));
				_fe3d->model_setBaseSize(newModelId, DEFAULT_CAPTOR_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_CAPTOR_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);

				_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, false);

				_isPlacingCaptor = false;
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, false);

				_isPlacingCaptor = false;
			}
		}
		else
		{
			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, false);
				_isPlacingCaptor = false;

				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, false);

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + CAPTOR_TERRAIN_OFFSET);
			_fe3d->captor_setPosition(TEMPLATE_CAPTOR_ID, newPosition);
			_fe3d->model_setVisible(TEMPLATE_CAPTOR_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_CAPTOR_ID, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				auto newId = ("captor_" + to_string(_idCounter));
				auto newModelId = ("@@captor_" + newId);

				_idCounter++;

				_loadedCaptorIds.push_back(newId);

				_fe3d->captor_create(newId);
				_fe3d->captor_setPosition(newId, newPosition);

				_fe3d->model_create(newModelId, TEMPLATE_CAPTOR_MODEL_PATH);
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseSize(newModelId, DEFAULT_CAPTOR_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_CAPTOR_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
	}
}