#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updatePointlightPlacing()
{
	// Only if user is in placement mode
	if(_isPlacingPointlight)
	{
		if(_fe3d.terrain_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.pointlight_getPosition(PREVIEW_LAMP_ID);

			// Update value forms
			_gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, {});
			_gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, {});
			_gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.pointlight_setPosition(PREVIEW_LAMP_ID, newPosition);

			// Check if pointlight must be placed
			if(_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Adding a number to make it unique
			BEGIN1:
				const string newID = ("pointlight_" + to_string(Math::getRandomInteger(0, INT_MAX)));

				// Check if pointlight already exists
				if(_fe3d.pointlight_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Try to create pointlight
				_fe3d.pointlight_create(newID);

				// Check if pointlight creation went well
				if(_fe3d.pointlight_isExisting(newID))
				{
					// Create model
					const string newModelID = ("@@lamp_" + newID);
					_fe3d.model_create(newModelID, "engine\\assets\\meshes\\lamp.obj");
					_fe3d.model_setBaseSize(newModelID, DEFAULT_LAMP_SIZE);
					_fe3d.model_setShadowed(newModelID, false);
					_fe3d.model_setReflected(newModelID, false);
					_fe3d.model_setBright(newModelID, true);

					// Bind AABB
					_fe3d.aabb_create(newModelID);
					_fe3d.aabb_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
					_fe3d.aabb_setLocalSize(newModelID, DEFAULT_LAMP_AABB_SIZE);
					_fe3d.aabb_setCollisionResponsive(newModelID, false);

					// Create pointlight
					_fe3d.pointlight_delete(newID);
					_fe3d.pointlight_create(newID);
					_fe3d.pointlight_setPosition(newID, newPosition);
					_fe3d.pointlight_setRadius(newID, Vec3(DEFAULT_POINTLIGHT_RADIUS));
					_fe3d.pointlight_setIntensity(newID, DEFAULT_POINTLIGHT_INTENSITY);
					_loadedPointlightIDs.push_back(newID);
				}
			}

			// Check if placement mode must be disabled
			if(_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				_fe3d.model_setVisible(PREVIEW_LAMP_ID, false);
				_fe3d.pointlight_setVisible(PREVIEW_LAMP_ID, false);
				_isPlacingPointlight = false;
			}
		}
		else
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if allowed by mouse
				if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Check if a terrain is loaded
					if(_fe3d.raycast_isPointOnTerrainValid())
					{
						// Show preview pointlight
						_fe3d.pointlight_setVisible(PREVIEW_LAMP_ID, true);
						_fe3d.model_setVisible(PREVIEW_LAMP_ID, true);

						// Update position
						_fe3d.pointlight_setPosition(PREVIEW_LAMP_ID, (_fe3d.raycast_getPointOnTerrain() + POINTLIGHT_TERRAIN_OFFSET));
					}
					else
					{
						// Hide preview pointlight
						_fe3d.model_setVisible(PREVIEW_LAMP_ID, false);
						_fe3d.pointlight_setVisible(PREVIEW_LAMP_ID, false);
					}

					// Check if pointlight must be placed
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						// Temporary values
						auto newPosition = _fe3d.pointlight_getPosition(PREVIEW_LAMP_ID);

						// Adding a number to make it unique
					BEGIN2:
						const string newID = ("pointlight_" + to_string(Math::getRandomInteger(0, INT_MAX)));

						// Check if pointlight already exists
						if(_fe3d.pointlight_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Try to create pointlight
						_fe3d.pointlight_create(newID);

						// Check if pointlight creation went well
						if(_fe3d.pointlight_isExisting(newID))
						{
							// Create model
							const string newModelID = ("@@lamp_" + newID);
							_fe3d.model_create(newModelID, "engine\\assets\\meshes\\lamp.obj");
							_fe3d.model_setBaseSize(newModelID, DEFAULT_LAMP_SIZE);
							_fe3d.model_setShadowed(newModelID, false);
							_fe3d.model_setReflected(newModelID, false);
							_fe3d.model_setBright(newModelID, true);

							// Bind AABB
							_fe3d.aabb_create(newModelID);
							_fe3d.aabb_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
							_fe3d.aabb_setLocalSize(newModelID, DEFAULT_LAMP_AABB_SIZE);
							_fe3d.aabb_setCollisionResponsive(newModelID, false);

							// Create pointlight
							_fe3d.pointlight_delete(newID);
							_fe3d.pointlight_create(newID);
							_fe3d.pointlight_setPosition(newID, newPosition);
							_fe3d.pointlight_setRadius(newID, Vec3(DEFAULT_POINTLIGHT_RADIUS));
							_fe3d.pointlight_setIntensity(newID, DEFAULT_POINTLIGHT_INTENSITY);
							_loadedPointlightIDs.push_back(newID);
						}
					}
					else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						_fe3d.model_setVisible(PREVIEW_LAMP_ID, false);
						_fe3d.pointlight_setVisible(PREVIEW_LAMP_ID, false);
						_isPlacingPointlight = false;
					}
				}
				else
				{
					_fe3d.model_setVisible(PREVIEW_LAMP_ID, false);
					_fe3d.pointlight_setVisible(PREVIEW_LAMP_ID, false);
				}
			}
			else
			{
				_fe3d.model_setVisible(PREVIEW_LAMP_ID, false);
				_fe3d.pointlight_setVisible(PREVIEW_LAMP_ID, false);
			}
		}

		// Update preview lamp position
		if(_isPlacingPointlight)
		{
			auto pointlightPosition = _fe3d.pointlight_getPosition(PREVIEW_LAMP_ID);
			pointlightPosition -= LAMP_OFFSET;
			_fe3d.model_setBasePosition(PREVIEW_LAMP_ID, pointlightPosition);
		}
	}

	// Update lamp positions
	for(const auto& entityID : _fe3d.model_getAllIDs())
	{
		if(entityID.substr(0, string("@@lamp").size()) == "@@lamp")
		{
			auto pointlightPosition = _fe3d.pointlight_getPosition(entityID.substr(string("@@lamp_").size()));
			pointlightPosition -= LAMP_OFFSET;
			_fe3d.model_setBasePosition(entityID, pointlightPosition);
		}
	}
}