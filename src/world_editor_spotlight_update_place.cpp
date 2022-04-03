#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updateSpotlightPlacing()
{
	if(_isPlacingSpotlight)
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			auto newPosition = _fe3d->spotlight_getPosition(TEMPLATE_TORCH_ID);
			//_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			//_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			//_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->spotlight_setPosition(TEMPLATE_SPOTLIGHT_ID, newPosition);
			_fe3d->model_setBasePosition(TEMPLATE_TORCH_ID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				auto newId = ("spotlight_" + to_string(_idCounter));
				auto newModelId = ("@@torch_" + newId);

				_idCounter++;

				if(_fe3d->spotlight_getIds().size() == _fe3d->spotlight_getMaxEntityCount())
				{
					Logger::throwWarning("spotlight maximum is reached");
					return;
				}

				_loadedSpotlightIds.push_back(newId);

				_fe3d->spotlight_create(newId);
				_fe3d->spotlight_setPosition(newId, newPosition);
				_fe3d->spotlight_setPitch(newId, DEFAULT_SPOTLIGHT_PITCH);
				_fe3d->spotlight_setIntensity(newId, DEFAULT_SPOTLIGHT_INTENSITY);
				_fe3d->spotlight_setAngle(newId, DEFAULT_SPOTLIGHT_ANGLE);
				_fe3d->spotlight_setDistance(newId, DEFAULT_SPOTLIGHT_DISTANCE);

				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\torch.obj");
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseRotation(newModelId, fvec3(0.0f, 0.0f, DEFAULT_SPOTLIGHT_PITCH));
				_fe3d->model_setBaseSize(newModelId, DEFAULT_TORCH_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_TORCH_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);

				_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				_isPlacingSpotlight = false;
			}

			if(_gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				_isPlacingSpotlight = false;
			}
		}
		else
		{
			if(!_fe3d->misc_isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				_isPlacingSpotlight = false;
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + SPOTLIGHT_TERRAIN_OFFSET);
			_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, true);
			_fe3d->spotlight_setPosition(TEMPLATE_SPOTLIGHT_ID, newPosition);
			_fe3d->model_setVisible(TEMPLATE_TORCH_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_TORCH_ID, newPosition);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				auto newId = ("spotlight_" + to_string(_idCounter));
				auto newModelId = ("@@torch_" + newId);

				_idCounter++;

				if(_fe3d->spotlight_getIds().size() == _fe3d->spotlight_getMaxEntityCount())
				{
					Logger::throwWarning("spotlight maximum is reached");
					return;
				}

				_loadedSpotlightIds.push_back(newId);

				_fe3d->spotlight_create(newId);
				_fe3d->spotlight_setPosition(newId, newPosition);
				_fe3d->spotlight_setPitch(newId, DEFAULT_SPOTLIGHT_PITCH);
				_fe3d->spotlight_setIntensity(newId, DEFAULT_SPOTLIGHT_INTENSITY);
				_fe3d->spotlight_setAngle(newId, DEFAULT_SPOTLIGHT_ANGLE);
				_fe3d->spotlight_setDistance(newId, DEFAULT_SPOTLIGHT_DISTANCE);

				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\torch.obj");
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseRotation(newModelId, fvec3(0.0f, 0.0f, DEFAULT_SPOTLIGHT_PITCH));
				_fe3d->model_setBaseSize(newModelId, DEFAULT_TORCH_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_TORCH_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
	}
}