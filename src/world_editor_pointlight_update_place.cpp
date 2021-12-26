#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updatePointlightPlacing()
{
	if(_isPlacingPointlight)
	{
		if(_fe3d.terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d.pointlight_getPosition(TEMPLATE_LAMP_ID);

			_gui.getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui.getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui.getOverlay()->checkValueForm("positionZ", newPosition.z, {});

			_fe3d.pointlight_setPosition(TEMPLATE_LAMP_ID, newPosition);

			if(_gui.getOverlay()->isValueFormConfirmed())
			{
				BEGIN1:;
				const string newID = ("pointlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));

				if(_fe3d.pointlight_isExisting(newID))
				{
					goto BEGIN1;
				}

				_fe3d.pointlight_create(newID);

				if(_fe3d.pointlight_isExisting(newID))
				{
					const string newModelID = ("@@lamp_" + newID);
					_fe3d.model_create(newModelID, "engine\\assets\\mesh\\lamp.obj");
					_fe3d.model_setBaseSize(newModelID, DEFAULT_LAMP_SIZE);
					_fe3d.model_setShadowed(newModelID, false);
					_fe3d.model_setReflected(newModelID, false);
					_fe3d.model_setBright(newModelID, true);

					_fe3d.aabb_create(newModelID, true);
					_fe3d.aabb_setParentEntityID(newModelID, newModelID);
					_fe3d.aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d.aabb_setLocalSize(newModelID, DEFAULT_LAMP_AABB_SIZE);
					_fe3d.aabb_setCollisionResponsive(newModelID, false);

					_fe3d.pointlight_delete(newID);
					_fe3d.pointlight_create(newID);
					_fe3d.pointlight_setPosition(newID, newPosition);
					_fe3d.pointlight_setRadius(newID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
					_fe3d.pointlight_setIntensity(newID, DEFAULT_POINTLIGHT_INTENSITY);
					_loadedPointlightIDs.push_back(newID);
				}
			}

			if(_gui.getOverlay()->isValueFormConfirmed() || _gui.getOverlay()->isValueFormCancelled())
			{
				_fe3d.model_setVisible(TEMPLATE_LAMP_ID, false);
				_fe3d.pointlight_setVisible(TEMPLATE_LAMP_ID, false);
				_isPlacingPointlight = false;
			}
		}
		else
		{
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getOverlay()->isFocused())
			{
				if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					if(_fe3d.raycast_isPointOnTerrainValid())
					{
						_fe3d.pointlight_setVisible(TEMPLATE_LAMP_ID, true);
						_fe3d.model_setVisible(TEMPLATE_LAMP_ID, true);

						_fe3d.pointlight_setPosition(TEMPLATE_LAMP_ID, (_fe3d.raycast_getPointOnTerrain() + POINTLIGHT_TERRAIN_OFFSET));
					}
					else
					{
						_fe3d.model_setVisible(TEMPLATE_LAMP_ID, false);
						_fe3d.pointlight_setVisible(TEMPLATE_LAMP_ID, false);
					}

					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						auto newPosition = _fe3d.pointlight_getPosition(TEMPLATE_LAMP_ID);

						BEGIN2:;
						const string newID = ("pointlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));

						if(_fe3d.pointlight_isExisting(newID))
						{
							goto BEGIN2;
						}

						_fe3d.pointlight_create(newID);

						if(_fe3d.pointlight_isExisting(newID))
						{
							const string newModelID = ("@@lamp_" + newID);
							_fe3d.model_create(newModelID, "engine\\assets\\mesh\\lamp.obj");
							_fe3d.model_setBaseSize(newModelID, DEFAULT_LAMP_SIZE);
							_fe3d.model_setShadowed(newModelID, false);
							_fe3d.model_setReflected(newModelID, false);
							_fe3d.model_setBright(newModelID, true);

							_fe3d.aabb_create(newModelID, true);
							_fe3d.aabb_setParentEntityID(newModelID, newModelID);
							_fe3d.aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
							_fe3d.aabb_setLocalSize(newModelID, DEFAULT_LAMP_AABB_SIZE);
							_fe3d.aabb_setCollisionResponsive(newModelID, false);

							_fe3d.pointlight_delete(newID);
							_fe3d.pointlight_create(newID);
							_fe3d.pointlight_setPosition(newID, newPosition);
							_fe3d.pointlight_setRadius(newID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
							_fe3d.pointlight_setIntensity(newID, DEFAULT_POINTLIGHT_INTENSITY);
							_loadedPointlightIDs.push_back(newID);
						}
					}
					else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_fe3d.model_setVisible(TEMPLATE_LAMP_ID, false);
						_fe3d.pointlight_setVisible(TEMPLATE_LAMP_ID, false);
						_isPlacingPointlight = false;
					}
				}
				else
				{
					_fe3d.model_setVisible(TEMPLATE_LAMP_ID, false);
					_fe3d.pointlight_setVisible(TEMPLATE_LAMP_ID, false);
				}
			}
			else
			{
				_fe3d.model_setVisible(TEMPLATE_LAMP_ID, false);
				_fe3d.pointlight_setVisible(TEMPLATE_LAMP_ID, false);
			}
		}

		if(_isPlacingPointlight)
		{
			auto pointlightPosition = _fe3d.pointlight_getPosition(TEMPLATE_LAMP_ID);
			pointlightPosition -= LAMP_OFFSET;
			_fe3d.model_setBasePosition(TEMPLATE_LAMP_ID, pointlightPosition);
		}
	}

	for(const auto& entityID : _fe3d.model_getIDs())
	{
		if(entityID.substr(0, string("@@lamp").size()) == "@@lamp")
		{
			auto pointlightPosition = _fe3d.pointlight_getPosition(entityID.substr(string("@@lamp_").size()));
			pointlightPosition -= LAMP_OFFSET;
			_fe3d.model_setBasePosition(entityID, pointlightPosition);
		}
	}
}