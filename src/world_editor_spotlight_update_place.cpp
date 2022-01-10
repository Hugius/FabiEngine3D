#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSpotlightPlacing()
{
	if(_isPlacingSpotlight)
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->spotlight_getPosition(TEMPLATE_TORCH_ID);
			_gui.getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui.getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui.getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->spotlight_setPosition(TEMPLATE_TORCH_ID, newPosition);
			_fe3d->model_setBasePosition(TEMPLATE_TORCH_ID, newPosition);

			if(_gui.getOverlay()->isValueFormConfirmed())
			{
				BEGIN1:;
				const string newID = ("spotlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				const string newModelID = ("@@torch_" + newID);
				if(_fe3d->spotlight_isExisting(newID))
				{
					goto BEGIN1;
				}

				_fe3d->spotlight_create(newID);
				if(_fe3d->spotlight_isExisting(newID))
				{
					_loadedSpotlightIDs.push_back(newID);

					_fe3d->spotlight_setPosition(newID, newPosition);
					_fe3d->spotlight_setPitch(newID, DEFAULT_SPOTLIGHT_PITCH);
					_fe3d->spotlight_setIntensity(newID, DEFAULT_SPOTLIGHT_INTENSITY);
					_fe3d->spotlight_setAngle(newID, DEFAULT_SPOTLIGHT_ANGLE);
					_fe3d->spotlight_setDistance(newID, DEFAULT_SPOTLIGHT_DISTANCE);

					_fe3d->model_create(newModelID, "engine\\assets\\mesh\\torch.obj");
					_fe3d->model_setBasePosition(newModelID, newPosition);
					_fe3d->model_setBaseRotation(newModelID, fvec3(0.0f, 0.0f, DEFAULT_SPOTLIGHT_PITCH));
					_fe3d->model_setBaseSize(newModelID, DEFAULT_TORCH_SIZE);
					_fe3d->model_setShadowed(newModelID, false);
					_fe3d->model_setReflected(newModelID, false);
					_fe3d->model_setBright(newModelID, true);

					_fe3d->aabb_create(newModelID, true);
					_fe3d->aabb_setParentEntityID(newModelID, newModelID);
					_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d->aabb_setLocalSize(newModelID, DEFAULT_TORCH_AABB_SIZE);
					_fe3d->aabb_setCollisionResponsive(newModelID, false);
				}
			}

			if(_gui.getOverlay()->isValueFormConfirmed() || _gui.getOverlay()->isValueFormCancelled())
			{
				_fe3d->spotlight_setVisible(TEMPLATE_TORCH_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				_isPlacingSpotlight = false;
			}
		}
		else
		{
			if(!_fe3d->misc_isCursorInsideViewport() || _gui.getOverlay()->isFocused())
			{
				_fe3d->spotlight_setVisible(TEMPLATE_TORCH_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->spotlight_setVisible(TEMPLATE_TORCH_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->spotlight_setVisible(TEMPLATE_TORCH_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				_isPlacingSpotlight = false;
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->spotlight_setVisible(TEMPLATE_TORCH_ID, false);
				_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
				return;
			}

			auto newPosition = (_fe3d->raycast_getPointOnTerrain() + SPOTLIGHT_TERRAIN_OFFSET);
			_fe3d->spotlight_setVisible(TEMPLATE_TORCH_ID, true);
			_fe3d->spotlight_setPosition(TEMPLATE_TORCH_ID, newPosition);
			_fe3d->model_setVisible(TEMPLATE_TORCH_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_TORCH_ID, newPosition);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				BEGIN2:;
				const string newID = ("spotlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				const string newModelID = ("@@torch_" + newID);
				if(_fe3d->spotlight_isExisting(newID))
				{
					goto BEGIN2;
				}

				_fe3d->spotlight_create(newID);
				if(_fe3d->spotlight_isExisting(newID))
				{
					_loadedSpotlightIDs.push_back(newID);

					_fe3d->spotlight_setPosition(newID, newPosition);
					_fe3d->spotlight_setPitch(newID, DEFAULT_SPOTLIGHT_PITCH);
					_fe3d->spotlight_setIntensity(newID, DEFAULT_SPOTLIGHT_INTENSITY);
					_fe3d->spotlight_setAngle(newID, DEFAULT_SPOTLIGHT_ANGLE);
					_fe3d->spotlight_setDistance(newID, DEFAULT_SPOTLIGHT_DISTANCE);

					_fe3d->model_create(newModelID, "engine\\assets\\mesh\\torch.obj");
					_fe3d->model_setBasePosition(newModelID, newPosition);
					_fe3d->model_setBaseRotation(newModelID, fvec3(0.0f, 0.0f, DEFAULT_SPOTLIGHT_PITCH));
					_fe3d->model_setBaseSize(newModelID, DEFAULT_TORCH_SIZE);
					_fe3d->model_setShadowed(newModelID, false);
					_fe3d->model_setReflected(newModelID, false);
					_fe3d->model_setBright(newModelID, true);

					_fe3d->aabb_create(newModelID, true);
					_fe3d->aabb_setParentEntityID(newModelID, newModelID);
					_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d->aabb_setLocalSize(newModelID, DEFAULT_TORCH_AABB_SIZE);
					_fe3d->aabb_setCollisionResponsive(newModelID, false);
				}
			}
		}
	}
}