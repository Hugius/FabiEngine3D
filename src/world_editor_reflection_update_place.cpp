#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateReflectionPlacing()
{
	if(_isPlacingReflection)
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			auto newPosition = _fe3d->reflection_getPosition(TEMPLATE_CAMERA_ID);
			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->reflection_setPosition(TEMPLATE_REFLECTION_ID, newPosition);
			_fe3d->model_setBasePosition(TEMPLATE_CAMERA_ID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
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

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				_isPlacingReflection = false;
			}
		}
		else
		{
			if(!_fe3d->misc_isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->reflection_setVisible(TEMPLATE_REFLECTION_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
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

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
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