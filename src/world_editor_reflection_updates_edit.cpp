#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateReflectionEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// User must not be placing anything
	if(_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		// Reset selected camera from last frame
		if(!_dontResetSelectedCamera)
		{
			_selectedCameraID = "";
		}
		else
		{
			_dontResetSelectedCamera = false;
		}

		// Check which entity is selected
		auto hoveredAabbID = _fe3d.raycast_checkCursorInAny().first;

		// Check if user selected a camera model
		for(const auto& ID : _fe3d.model_getAllIDs())
		{
			// Must be reflection preview entity
			if(ID.substr(0, string("@@camera").size()) == "@@camera")
			{
				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if(hoveredAabbID == ID && _fe3d.misc_isCursorInsideViewport() &&
				   !_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered camera
					_selectReflection(ID.substr(string("@@camera_").size()));

					// Check if user clicked camera
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same camera is not clicked again
						if(_selectedCameraID != _activeCameraID)
						{
							_activateReflection(_selectedCameraID.substr(string("@@camera_").size()));
						}
					}
				}
				else
				{
					// Unselect if necessary
					if((ID != _selectedCameraID) && (ID != _activeCameraID))
					{
						_unselectReflection(ID);
					}
				}
			}
		}

		// Check if RMB not down
		if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if camera is active
				if(_activeCameraID != "")
				{
					// Check if active camera cancelled
					if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedCameraID.empty()) || _fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeCameraID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		// Update camera highlighting
		if(_selectedCameraID != _activeCameraID)
		{
			_updateCameraHighlighting(_selectedCameraID, _selectedCameraHighlightDirection);
		}
		_updateCameraHighlighting(_activeCameraID, _activeCameraHighlightDirection);

		// Update properties screen
		if(!_activeCameraID.empty())
		{
			// Temporary values
			const string activeReflectionID = _activeCameraID.substr(string("@@camera_").size());
			auto screen = rightWindow->getScreen("reflectionPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("reflectionPropertiesMenu");

			// Button management
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("capture")->isHovered())
				{
					_fe3d.reflection_capture(activeReflectionID);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.model_delete(_activeCameraID);
					_fe3d.reflection_delete(activeReflectionID);
					rightWindow->setActiveScreen("main");
					_activeCameraID = "";
					return;
				}
			}

			// Alternative way of deleting
			if(_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.model_delete(_activeCameraID);
				_fe3d.reflection_delete(activeReflectionID);
				rightWindow->setActiveScreen("main");
				_activeCameraID = "";
				return;
			}

			// Get current values
			auto position = _fe3d.reflection_getPosition(activeReflectionID);

			// Update value filling and changing
			_handleValueChanging("reflectionPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
			_handleValueChanging("reflectionPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));

			// Apply new values
			_fe3d.reflection_setPosition(activeReflectionID, position);
		}
	}
}