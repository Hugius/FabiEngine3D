#include "scene_editor.hpp"
#include "logger.hpp"

void SceneEditor::_updateReflectionEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Reset selected camera from last frame
	if (!_dontResetSelectedCamera)
	{
		_selectedCameraID = "";
	}
	else
	{
		_dontResetSelectedCamera = false;
	}

	// User must not be in placement mode
	if (_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingLight && !_isPlacingReflection)
	{
		// Check which entity is selected
		auto hoveredAabbID = _fe3d.collision_checkCursorInAny().first;

		// Check if user selected a camera model
		for (const auto& entityID : _fe3d.modelEntity_getAllIDs())
		{
			// Must be reflection preview entity
			if (entityID.substr(0, string("@@camera").size()) == "@@camera")
			{
				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if (hoveredAabbID == entityID && _fe3d.misc_isCursorInsideViewport() &&
					!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered camera
					_selectReflection(entityID.substr(string("@@camera_").size()));

					// Check if user clicked camera
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same camera is not clicked again
						if (_selectedCameraID != _activeCameraID)
						{
							_activateReflection(_selectedCameraID.substr(string("@@camera_").size()));
						}
					}
				}
				else
				{
					// Don't reset if camera is active or selected
					if ((entityID != _activeCameraID) && (entityID != _selectedCameraID))
					{
						_fe3d.modelEntity_setSize(entityID, DEFAULT_CAMERA_SIZE);
						_fe3d.aabbEntity_setLocalSize(entityID, DEFAULT_CAMERA_AABB_SIZE);
					}
				}
			}
		}

		// Check if user made the active camera inactive
		if ((_selectedCameraID.empty()) && (_activeCameraID != "") && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
		{
			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_activeCameraID = "";
				rightWindow->setActiveScreen("sceneEditorControls");
			}
		}

		// Update camera animations
		if (_selectedCameraID != _activeCameraID)
		{
			_updateCameraAnimation(_selectedCameraID, _selectedCameraSizeDirection);
		}
		_updateCameraAnimation(_activeCameraID, _activeCameraSizeDirection);

		// Update properties screen
		if (!_activeCameraID.empty())
		{
			// Temporary values
			const string activeReflectionID = _activeCameraID.substr(string("@@camera_").size());
			auto screen = rightWindow->getScreen("reflectionPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("reflectionPropertiesMenu");

			// Button management
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("capture")->isHovered())
				{
					_fe3d.reflectionEntity_capture(activeReflectionID);
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.modelEntity_delete(_activeCameraID);
					_fe3d.reflectionEntity_delete(activeReflectionID);
					rightWindow->setActiveScreen("sceneEditorControls");
					_activeCameraID = "";
					return;
				}
			}

			// Alternative way of deleting
			if (_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.modelEntity_delete(_activeCameraID);
				_fe3d.reflectionEntity_delete(activeReflectionID);
				rightWindow->setActiveScreen("sceneEditorControls");
				_activeCameraID = "";
				return;
			}

			// Get current values
			auto position = _fe3d.reflectionEntity_getPosition(activeReflectionID);

			// Handle position
			_handleValueChanging("reflectionPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));
			_fe3d.reflectionEntity_setPosition(activeReflectionID, position);
		}
	}
}