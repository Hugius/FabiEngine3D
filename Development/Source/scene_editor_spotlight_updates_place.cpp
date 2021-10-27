#include "scene_editor.hpp"
#include "tools.hpp"

void SceneEditor::_updateSpotlightPlacing()
{
	// Only if user is in placement mode
	if(_isPlacingSpotlight)
	{
		if(_fe3d.terrainEntity_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.spotlightEntity_getPosition(PREVIEW_TORCH_ID);

			// Update value forms
			_gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, {});
			_gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, {});
			_gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.spotlightEntity_setPosition(PREVIEW_TORCH_ID, newPosition);

			// Check if spotlight must be placed
			if(_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Adding a number to make it unique
			BEGIN1:
				const string newID = ("spotlight_" + to_string(Math::getRandomInteger(0, INT_MAX)));

				// Check if spotlight already exists
				if(_fe3d.spotlightEntity_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Try to create spotlight
				_fe3d.spotlightEntity_create(newID);

				// Check if spotlight creation went well
				if(_fe3d.spotlightEntity_isExisting(newID))
				{
					// Create model
					const string newModelID = ("@@torch_" + newID);
					_fe3d.modelEntity_create(newModelID, "engine_assets\\meshes\\torch.obj");
					_fe3d.modelEntity_setBaseSize(newModelID, DEFAULT_TORCH_SIZE);
					_fe3d.modelEntity_setShadowed(newModelID, false);
					_fe3d.modelEntity_setReflected(newModelID, false);
					_fe3d.modelEntity_setBright(newModelID, true);

					// Bind AABB
					_fe3d.aabbEntity_create(newModelID);
					_fe3d.aabbEntity_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
					_fe3d.aabbEntity_setLocalSize(newModelID, DEFAULT_TORCH_AABB_SIZE);
					_fe3d.aabbEntity_setCollisionResponsive(newModelID, false);

					// Create spotlight
					_fe3d.spotlightEntity_delete(newID);
					_fe3d.spotlightEntity_create(newID);
					_fe3d.spotlightEntity_setPosition(newID, newPosition);
					_fe3d.spotlightEntity_setPitch(newID, DEFAULT_SPOTLIGHT_PITCH);
					_fe3d.spotlightEntity_setIntensity(newID, DEFAULT_SPOTLIGHT_INTENSITY);
					_fe3d.spotlightEntity_setAngle(newID, DEFAULT_SPOTLIGHT_ANGLE);
					_fe3d.spotlightEntity_setDistance(newID, DEFAULT_SPOTLIGHT_DISTANCE);
					_loadedSpotlightIDs.push_back(newID);
				}
			}

			// Check if placement mode must be disabled
			if(_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				_fe3d.modelEntity_setVisible(PREVIEW_TORCH_ID, false);
				_fe3d.spotlightEntity_setVisible(PREVIEW_TORCH_ID, false);
				_isPlacingSpotlight = false;
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
						// Show preview spotlight
						_fe3d.spotlightEntity_setVisible(PREVIEW_TORCH_ID, true);
						_fe3d.modelEntity_setVisible(PREVIEW_TORCH_ID, true);

						// Update position
						_fe3d.spotlightEntity_setPosition(PREVIEW_TORCH_ID, (_fe3d.raycast_getPointOnTerrain() + SPOTLIGHT_TERRAIN_OFFSET));
					}
					else
					{
						// Hide preview spotlight
						_fe3d.modelEntity_setVisible(PREVIEW_TORCH_ID, false);
						_fe3d.spotlightEntity_setVisible(PREVIEW_TORCH_ID, false);
					}

					// Check if spotlight must be placed
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						// Temporary values
						auto newPosition = _fe3d.spotlightEntity_getPosition(PREVIEW_TORCH_ID);

						// Adding a number to make it unique
					BEGIN2:
						const string newID = ("spotlight_" + to_string(Math::getRandomInteger(0, INT_MAX)));

						// Check if spotlight already exists
						if(_fe3d.spotlightEntity_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Try to create spotlight
						_fe3d.spotlightEntity_create(newID);

						// Check if spotlight creation went well
						if(_fe3d.spotlightEntity_isExisting(newID))
						{
							// Create model
							const string newModelID = ("@@torch_" + newID);
							_fe3d.modelEntity_create(newModelID, "engine_assets\\meshes\\torch.obj");
							_fe3d.modelEntity_setBaseSize(newModelID, DEFAULT_TORCH_SIZE);
							_fe3d.modelEntity_setShadowed(newModelID, false);
							_fe3d.modelEntity_setReflected(newModelID, false);
							_fe3d.modelEntity_setBright(newModelID, true);

							// Bind AABB
							_fe3d.aabbEntity_create(newModelID);
							_fe3d.aabbEntity_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
							_fe3d.aabbEntity_setLocalSize(newModelID, DEFAULT_TORCH_AABB_SIZE);
							_fe3d.aabbEntity_setCollisionResponsive(newModelID, false);

							// Create spotlight
							_fe3d.spotlightEntity_delete(newID);
							_fe3d.spotlightEntity_create(newID);
							_fe3d.spotlightEntity_setPosition(newID, newPosition);
							_fe3d.spotlightEntity_setPitch(newID, DEFAULT_SPOTLIGHT_PITCH);
							_fe3d.spotlightEntity_setIntensity(newID, DEFAULT_SPOTLIGHT_INTENSITY);
							_fe3d.spotlightEntity_setAngle(newID, DEFAULT_SPOTLIGHT_ANGLE);
							_fe3d.spotlightEntity_setDistance(newID, DEFAULT_SPOTLIGHT_DISTANCE);
							_loadedSpotlightIDs.push_back(newID);
						}
					}
					else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						_fe3d.modelEntity_setVisible(PREVIEW_TORCH_ID, false);
						_fe3d.spotlightEntity_setVisible(PREVIEW_TORCH_ID, false);
						_isPlacingSpotlight = false;
					}
				}
				else
				{
					_fe3d.modelEntity_setVisible(PREVIEW_TORCH_ID, false);
					_fe3d.spotlightEntity_setVisible(PREVIEW_TORCH_ID, false);
				}
			}
			else
			{
				_fe3d.modelEntity_setVisible(PREVIEW_TORCH_ID, false);
				_fe3d.spotlightEntity_setVisible(PREVIEW_TORCH_ID, false);
			}
		}

		// Update preview torch position
		if(_isPlacingSpotlight)
		{
			auto spotlightPosition = _fe3d.spotlightEntity_getPosition(PREVIEW_TORCH_ID);
			spotlightPosition -= TORCH_OFFSET;
			_fe3d.modelEntity_setBasePosition(PREVIEW_TORCH_ID, spotlightPosition);
		}
	}

	// Update torch positions
	for(const auto& entityID : _fe3d.modelEntity_getAllIDs())
	{
		if(entityID.substr(0, string("@@torch").size()) == "@@torch")
		{
			auto spotlightPosition = _fe3d.spotlightEntity_getPosition(entityID.substr(string("@@torch_").size()));
			spotlightPosition -= TORCH_OFFSET;
			_fe3d.modelEntity_setBasePosition(entityID, spotlightPosition);
		}
	}
}