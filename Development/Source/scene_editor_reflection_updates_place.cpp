#include "scene_editor.hpp"
#include "tools.hpp"

void SceneEditor::_updateReflectionPlacing()
{
	// Only if user is in placement mode
	if (_isPlacingReflection)
	{
		if (_fe3d.terrainEntity_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.reflectionEntity_getPosition(PREVIEW_CAMERA_ID);

			// Update value forms
			_gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, {});
			_gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, {});
			_gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.reflectionEntity_setPosition(PREVIEW_CAMERA_ID, newPosition);

			// Check if reflection must be placed
			if (_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Adding a number to make it unique
			BEGIN1:
				const string newID = ("reflection_" + to_string(Tools::getRandomInteger(0, INT_MAX)));

				// Check if reflection already exists
				if (_fe3d.reflectionEntity_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Create model
				const string newModelID = ("@@camera_" + newID);
				_fe3d.modelEntity_create(newModelID, "engine_assets\\meshes\\camera.obj");
				_fe3d.modelEntity_setBaseSize(newModelID, DEFAULT_CAMERA_SIZE);
				_fe3d.modelEntity_setShadowed(newModelID, false);
				_fe3d.modelEntity_setReflected(newModelID, false);
				_fe3d.modelEntity_setBright(newModelID, true);

				// Bind AABB
				_fe3d.aabbEntity_create(newModelID);
				_fe3d.aabbEntity_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
				_fe3d.aabbEntity_setLocalSize(newModelID, DEFAULT_CAMERA_AABB_SIZE);
				_fe3d.aabbEntity_setCollisionResponsive(newModelID, false);

				// Create reflection
				_fe3d.reflectionEntity_create(newID);
				_fe3d.reflectionEntity_setPosition(newID, newPosition);
				_loadedReflectionIDs.push_back(newID);
			}

			// Check if placement mode must be disabled
			if (_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				_fe3d.modelEntity_setVisible(PREVIEW_CAMERA_ID, false);
				_isPlacingReflection = false;
			}
		}
		else
		{
			// Check if allowed by GUI
			if (_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if allowed by mouse
				if (!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Check if a terrain is loaded
					if (_fe3d.misc_isRaycastPointOnTerrainValid())
					{
						// Show preview reflection
						_fe3d.modelEntity_setVisible(PREVIEW_CAMERA_ID, true);

						// Update position
						_fe3d.reflectionEntity_setPosition(PREVIEW_CAMERA_ID, (_fe3d.misc_getRaycastPointOnTerrain() + REFLECTION_TERRAIN_OFFSET));
					}
					else
					{
						// Hide preview reflection
						_fe3d.modelEntity_setVisible(PREVIEW_CAMERA_ID, false);
					}

					// Check if reflection must be placed
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid())
					{
						// Temporary values
						auto newPosition = _fe3d.reflectionEntity_getPosition(PREVIEW_CAMERA_ID);

						// Adding a number to make it unique
					BEGIN2:
						const string newID = ("reflection_" + to_string(Tools::getRandomInteger(0, INT_MAX)));

						// Check if reflection already exists
						if (_fe3d.reflectionEntity_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Try to create reflection
						_fe3d.reflectionEntity_create(newID);

						// Check if reflection creation went well
						if (_fe3d.reflectionEntity_isExisting(newID))
						{
							// Create model
							const string newModelID = ("@@camera_" + newID);
							_fe3d.modelEntity_create(newModelID, "engine_assets\\meshes\\camera.obj");
							_fe3d.modelEntity_setBaseSize(newModelID, DEFAULT_CAMERA_SIZE);
							_fe3d.modelEntity_setShadowed(newModelID, false);
							_fe3d.modelEntity_setReflected(newModelID, false);
							_fe3d.modelEntity_setBright(newModelID, true);

							// Bind AABB
							_fe3d.aabbEntity_create(newModelID);
							_fe3d.aabbEntity_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
							_fe3d.aabbEntity_setLocalSize(newModelID, DEFAULT_CAMERA_AABB_SIZE);
							_fe3d.aabbEntity_setCollisionResponsive(newModelID, false);

							// Create reflection
							_fe3d.reflectionEntity_delete(newID);
							_fe3d.reflectionEntity_create(newID);
							_fe3d.reflectionEntity_setPosition(newID, newPosition);
							_loadedReflectionIDs.push_back(newID);
						}
					}
					else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						_fe3d.modelEntity_setVisible(PREVIEW_CAMERA_ID, false);
						_isPlacingReflection = false;
					}
				}
				else
				{
					_fe3d.modelEntity_setVisible(PREVIEW_CAMERA_ID, false);
				}
			}
			else
			{
				_fe3d.modelEntity_setVisible(PREVIEW_CAMERA_ID, false);
			}
		}

		// Update preview camera position
		if (_isPlacingReflection)
		{
			auto reflectionPosition = _fe3d.reflectionEntity_getPosition(PREVIEW_CAMERA_ID);
			reflectionPosition -= CAMERA_OFFSET;
			_fe3d.modelEntity_setBasePosition(PREVIEW_CAMERA_ID, reflectionPosition);
		}
	}

	// Update camera positions
	for (const auto& entityID : _fe3d.modelEntity_getAllIDs())
	{
		if (entityID.substr(0, string("@@camera").size()) == "@@camera")
		{
			auto reflectionPosition = _fe3d.reflectionEntity_getPosition(entityID.substr(string("@@camera_").size()));
			reflectionPosition -= CAMERA_OFFSET;
			_fe3d.modelEntity_setBasePosition(entityID, reflectionPosition);
		}
	}
}