#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateReflectionPlacing()
{
	if(_isPlacingReflection)
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->reflection_getPosition(TEMPLATE_CAMERA_ID);
			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->reflection_setPosition(TEMPLATE_CAMERA_ID, newPosition);
			_fe3d->model_setBasePosition(TEMPLATE_CAMERA_ID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				BEGIN1:;
				const auto newID = ("reflection_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				const string newModelID = ("@@camera_" + newID);

				if(_fe3d->reflection_isExisting(newID))
				{
					goto BEGIN1;
				}

				_fe3d->reflection_create(newID);

				if(_fe3d->reflection_isExisting(newID))
				{
					_loadedReflectionIDs.push_back(newID);

					_fe3d->reflection_setPosition(newID, newPosition);

					_fe3d->model_create(newModelID, "engine\\assets\\mesh\\camera.obj");
					_fe3d->model_setBaseSize(newModelID, DEFAULT_CAMERA_SIZE);
					_fe3d->model_setShadowed(newModelID, false);
					_fe3d->model_setReflected(newModelID, false);
					_fe3d->model_setBright(newModelID, "", true);

					_fe3d->aabb_create(newModelID, true);
					_fe3d->aabb_setParentEntityID(newModelID, newModelID);
					_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d->aabb_setLocalSize(newModelID, DEFAULT_CAMERA_AABB_SIZE);
					_fe3d->aabb_setCollisionResponsive(newModelID, false);
				}
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->reflection_setVisible(TEMPLATE_CAMERA_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				_isPlacingReflection = false;
			}
		}
		else
		{
			if(!_fe3d->misc_isCursorInsideViewport() || _gui->getOverlay()->isFocused())
			{
				_fe3d->reflection_setVisible(TEMPLATE_CAMERA_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->reflection_setVisible(TEMPLATE_CAMERA_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->reflection_setVisible(TEMPLATE_CAMERA_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				_isPlacingReflection = false;
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->reflection_setVisible(TEMPLATE_CAMERA_ID, false);
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + REFLECTION_TERRAIN_OFFSET);
			_fe3d->reflection_setVisible(TEMPLATE_CAMERA_ID, true);
			_fe3d->reflection_setPosition(TEMPLATE_CAMERA_ID, newPosition);
			_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_CAMERA_ID, newPosition);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				BEGIN2:;
				const auto newID = ("reflection_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				const string newModelID = ("@@camera_" + newID);
				if(_fe3d->reflection_isExisting(newID))
				{
					goto BEGIN2;
				}

				_fe3d->reflection_create(newID);

				if(_fe3d->reflection_isExisting(newID))
				{
					_loadedReflectionIDs.push_back(newID);

					_fe3d->reflection_setPosition(newID, newPosition);

					_fe3d->model_create(newModelID, "engine\\assets\\mesh\\camera.obj");
					_fe3d->model_setBasePosition(newModelID, newPosition);
					_fe3d->model_setBaseSize(newModelID, DEFAULT_CAMERA_SIZE);
					_fe3d->model_setShadowed(newModelID, false);
					_fe3d->model_setReflected(newModelID, false);
					_fe3d->model_setBright(newModelID, "", true);

					_fe3d->aabb_create(newModelID, true);
					_fe3d->aabb_setParentEntityID(newModelID, newModelID);
					_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d->aabb_setLocalSize(newModelID, DEFAULT_CAMERA_AABB_SIZE);
					_fe3d->aabb_setCollisionResponsive(newModelID, false);
				}
			}
		}
	}
}