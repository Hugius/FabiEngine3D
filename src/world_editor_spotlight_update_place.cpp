#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSpotlightPlacing()
{
	// Only if user is in placement mode
	if(_isPlacingSpotlight)
	{
		if(_fe3d.terrain_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.spotlight_getPosition(PREVIEW_TORCH_ID);

			// Update value forms
			_gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, {});
			_gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, {});
			_gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.spotlight_setPosition(PREVIEW_TORCH_ID, newPosition);

			// Check if spotlight must be placed
			if(_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Adding a number to make it unique
				BEGIN1:
				const string newID = ("spotlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));

				// Check if spotlight already exists
				if(_fe3d.spotlight_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Try to create spotlight
				_fe3d.spotlight_create(newID);

				// Check if spotlight creation went well
				if(_fe3d.spotlight_isExisting(newID))
				{
					// Create model
					const string newModelID = ("@@torch_" + newID);
					_fe3d.model_create(newModelID, "engine\\assets\\mesh\\torch.obj");
					_fe3d.model_setBaseSize(newModelID, DEFAULT_TORCH_SIZE);
					_fe3d.model_setShadowed(newModelID, false);
					_fe3d.model_setReflected(newModelID, false);
					_fe3d.model_setBright(newModelID, true);

					// Bind AABB
					_fe3d.aabb_create(newModelID);
					_fe3d.aabb_setParentEntityID(newModelID, newModelID);
					_fe3d.aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d.aabb_setLocalSize(newModelID, DEFAULT_TORCH_AABB_SIZE);
					_fe3d.aabb_setCollisionResponsive(newModelID, false);

					// Create spotlight
					_fe3d.spotlight_delete(newID);
					_fe3d.spotlight_create(newID);
					_fe3d.spotlight_setPosition(newID, newPosition);
					_fe3d.spotlight_setPitch(newID, DEFAULT_SPOTLIGHT_PITCH);
					_fe3d.spotlight_setIntensity(newID, DEFAULT_SPOTLIGHT_INTENSITY);
					_fe3d.spotlight_setAngle(newID, DEFAULT_SPOTLIGHT_ANGLE);
					_fe3d.spotlight_setDistance(newID, DEFAULT_SPOTLIGHT_DISTANCE);
					_loadedSpotlightIDs.push_back(newID);
				}
			}

			// Check if placement mode must be disabled
			if(_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				_fe3d.model_setVisible(PREVIEW_TORCH_ID, false);
				_fe3d.spotlight_setVisible(PREVIEW_TORCH_ID, false);
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
						_fe3d.spotlight_setVisible(PREVIEW_TORCH_ID, true);
						_fe3d.model_setVisible(PREVIEW_TORCH_ID, true);

						// Update position
						_fe3d.spotlight_setPosition(PREVIEW_TORCH_ID, (_fe3d.raycast_getPointOnTerrain() + SPOTLIGHT_TERRAIN_OFFSET));
					}
					else
					{
						// Hide preview spotlight
						_fe3d.model_setVisible(PREVIEW_TORCH_ID, false);
						_fe3d.spotlight_setVisible(PREVIEW_TORCH_ID, false);
					}

					// Check if spotlight must be placed
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						// Temporary values
						auto newPosition = _fe3d.spotlight_getPosition(PREVIEW_TORCH_ID);

						// Adding a number to make it unique
						BEGIN2:
						const string newID = ("spotlight_" + to_string(Math::getRandomNumber(0, INT_MAX)));

						// Check if spotlight already exists
						if(_fe3d.spotlight_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Try to create spotlight
						_fe3d.spotlight_create(newID);

						// Check if spotlight creation went well
						if(_fe3d.spotlight_isExisting(newID))
						{
							// Create model
							const string newModelID = ("@@torch_" + newID);
							_fe3d.model_create(newModelID, "engine\\assets\\mesh\\torch.obj");
							_fe3d.model_setBaseSize(newModelID, DEFAULT_TORCH_SIZE);
							_fe3d.model_setShadowed(newModelID, false);
							_fe3d.model_setReflected(newModelID, false);
							_fe3d.model_setBright(newModelID, true);

							// Bind AABB
							_fe3d.aabb_create(newModelID);
							_fe3d.aabb_setParentEntityID(newModelID, newModelID);
							_fe3d.aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
							_fe3d.aabb_setLocalSize(newModelID, DEFAULT_TORCH_AABB_SIZE);
							_fe3d.aabb_setCollisionResponsive(newModelID, false);

							// Create spotlight
							_fe3d.spotlight_delete(newID);
							_fe3d.spotlight_create(newID);
							_fe3d.spotlight_setPosition(newID, newPosition);
							_fe3d.spotlight_setPitch(newID, DEFAULT_SPOTLIGHT_PITCH);
							_fe3d.spotlight_setIntensity(newID, DEFAULT_SPOTLIGHT_INTENSITY);
							_fe3d.spotlight_setAngle(newID, DEFAULT_SPOTLIGHT_ANGLE);
							_fe3d.spotlight_setDistance(newID, DEFAULT_SPOTLIGHT_DISTANCE);
							_loadedSpotlightIDs.push_back(newID);
						}
					}
					else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						_fe3d.model_setVisible(PREVIEW_TORCH_ID, false);
						_fe3d.spotlight_setVisible(PREVIEW_TORCH_ID, false);
						_isPlacingSpotlight = false;
					}
				}
				else
				{
					_fe3d.model_setVisible(PREVIEW_TORCH_ID, false);
					_fe3d.spotlight_setVisible(PREVIEW_TORCH_ID, false);
				}
			}
			else
			{
				_fe3d.model_setVisible(PREVIEW_TORCH_ID, false);
				_fe3d.spotlight_setVisible(PREVIEW_TORCH_ID, false);
			}
		}

		// Update preview torch position
		if(_isPlacingSpotlight)
		{
			auto spotlightPosition = _fe3d.spotlight_getPosition(PREVIEW_TORCH_ID);
			spotlightPosition -= TORCH_OFFSET;
			_fe3d.model_setBasePosition(PREVIEW_TORCH_ID, spotlightPosition);
		}
	}

	// Update torch positions
	for(const auto& entityID : _fe3d.model_getIDs())
	{
		if(entityID.substr(0, string("@@torch").size()) == "@@torch")
		{
			auto spotlightPosition = _fe3d.spotlight_getPosition(entityID.substr(string("@@torch_").size()));
			spotlightPosition -= TORCH_OFFSET;
			_fe3d.model_setBasePosition(entityID, spotlightPosition);
		}
	}
}