#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updatePointlightPlacing()
{
	if(_isPlacingPointlight)
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->pointlight_getPosition(TEMPLATE_LAMP_ID);
			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->pointlight_setPosition(TEMPLATE_LAMP_ID, newPosition);
			_fe3d->model_setBasePosition(TEMPLATE_LAMP_ID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				auto newID = ("pointlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				auto newModelID = ("@@lamp_" + newID);

				while(_fe3d->pointlight_isExisting(newID))
				{
					newID = ("pointlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));
					newModelID = ("@@lamp_" + newID);
				}

				_fe3d->pointlight_create(newID);

				if(_fe3d->pointlight_isExisting(newID))
				{
					_loadedPointlightIDs.push_back(newID);

					_fe3d->pointlight_setPosition(newID, newPosition);
					_fe3d->pointlight_setRadius(newID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
					_fe3d->pointlight_setIntensity(newID, DEFAULT_POINTLIGHT_INTENSITY);

					_fe3d->model_create(newModelID, "engine\\assets\\mesh\\lamp.obj");
					_fe3d->model_setBasePosition(newModelID, newPosition);
					_fe3d->model_setBaseSize(newModelID, DEFAULT_LAMP_SIZE);
					_fe3d->model_setShadowed(newModelID, false);
					_fe3d->model_setReflected(newModelID, false);
					_fe3d->model_setBright(newModelID, "", true);

					_fe3d->aabb_create(newModelID, true);
					_fe3d->aabb_setParentEntityId(newModelID, newModelID);
					_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d->aabb_setLocalSize(newModelID, DEFAULT_LAMP_AABB_SIZE);
					_fe3d->aabb_setCollisionResponsive(newModelID, false);
				}
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->pointlight_setVisible(TEMPLATE_LAMP_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				_isPlacingPointlight = false;
			}
		}
		else
		{
			if(!_fe3d->misc_isCursorInsideViewport() || _gui->getOverlay()->isFocused())
			{
				_fe3d->pointlight_setVisible(TEMPLATE_LAMP_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->pointlight_setVisible(TEMPLATE_LAMP_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->pointlight_setVisible(TEMPLATE_LAMP_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				_isPlacingPointlight = false;
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->pointlight_setVisible(TEMPLATE_LAMP_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + POINTLIGHT_TERRAIN_OFFSET);
			_fe3d->pointlight_setVisible(TEMPLATE_LAMP_ID, true);
			_fe3d->pointlight_setPosition(TEMPLATE_LAMP_ID, newPosition);
			_fe3d->model_setVisible(TEMPLATE_LAMP_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_LAMP_ID, newPosition);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				auto newID = ("pointlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				auto newModelID = ("@@lamp_" + newID);

				while(_fe3d->pointlight_isExisting(newID))
				{
					newID = ("pointlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));
					newModelID = ("@@lamp_" + newID);
				}

				_fe3d->pointlight_create(newID);

				if(_fe3d->pointlight_isExisting(newID))
				{
					_loadedPointlightIDs.push_back(newID);

					_fe3d->pointlight_setPosition(newID, newPosition);
					_fe3d->pointlight_setRadius(newID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
					_fe3d->pointlight_setIntensity(newID, DEFAULT_POINTLIGHT_INTENSITY);

					_fe3d->model_create(newModelID, "engine\\assets\\mesh\\lamp.obj");
					_fe3d->model_setBasePosition(newModelID, newPosition);
					_fe3d->model_setBaseSize(newModelID, DEFAULT_LAMP_SIZE);
					_fe3d->model_setShadowed(newModelID, false);
					_fe3d->model_setReflected(newModelID, false);
					_fe3d->model_setBright(newModelID, "", true);

					_fe3d->aabb_create(newModelID, true);
					_fe3d->aabb_setParentEntityId(newModelID, newModelID);
					_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d->aabb_setLocalSize(newModelID, DEFAULT_LAMP_AABB_SIZE);
					_fe3d->aabb_setCollisionResponsive(newModelID, false);
				}
			}
		}
	}
}