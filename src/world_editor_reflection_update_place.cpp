#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateReflectionPlacing()
{
	if(_isPlacingReflection)
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->reflection_getPosition(TEMPLATE_CAMERA_ID);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->reflection_setPosition(TEMPLATE_REFLECTION_ID, fvec3(content, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_CAMERA_ID, fvec3(content, newPosition.y, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->reflection_setPosition(TEMPLATE_REFLECTION_ID, fvec3(newPosition.x, content, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_CAMERA_ID, fvec3(newPosition.x, content, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));
				const auto newId = ("reflection_" + to_string(_idCounter));
				const auto newModelId = ("@@camera_" + newId);

				_idCounter++;

				_loadedReflectionIds.push_back(newId);

				_fe3d->reflection_create(newId);
				_fe3d->reflection_setPosition(newId, fvec3(newPosition.x, newPosition.y, content));

				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\camera.obj");
				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, content));
				_fe3d->model_setBaseSize(newModelId, DEFAULT_CAMERA_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_CAMERA_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);

				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);

				_isPlacingReflection = false;
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);

				_isPlacingReflection = false;
			}
		}
		else
		{
			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				return;
			}

			if(_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
			{
				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				return;
			}

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_MIDDLE))
			{
				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				_isPlacingReflection = false;
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + REFLECTION_TERRAIN_OFFSET);
			_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, true);
			_fe3d->reflection_setPosition(TEMPLATE_REFLECTION_ID, newPosition);
			_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_CAMERA_ID, newPosition);

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
			{
				auto newId = ("reflection_" + to_string(_idCounter));
				auto newModelId = ("@@camera_" + newId);

				_idCounter++;

				_loadedReflectionIds.push_back(newId);

				_fe3d->reflection_create(newId);
				_fe3d->reflection_setPosition(newId, newPosition);

				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\camera.obj");
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseSize(newModelId, DEFAULT_CAMERA_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_CAMERA_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
	}
}