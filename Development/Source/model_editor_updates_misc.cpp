#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateCamera()
{
	if (_isEditorLoaded)
	{
		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Update camera speed alteration
			if (_fe3d.input_isKeyPressed(InputType::KEY_UP))
			{
				_cameraSpeed *= 2.0f;
			}
			if (_fe3d.input_isKeyPressed(InputType::KEY_DOWN))
			{
				_cameraSpeed /= 2.0f;
			}

			// Update vertical lookat movement
			if (_fe3d.input_isKeyDown(InputType::KEY_SPACE))
			{
				_cameraLookatPosition.y += (_cameraSpeed / 2.0f);
			}
			if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT))
			{
				_cameraLookatPosition.y -= (_cameraSpeed / 2.0f);

				// Cannot be negative
				if (_cameraLookatPosition.y < 0.0f)
				{
					_cameraLookatPosition = 0.0f;
				}
			}
		}

		// Update scrolling
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			if (!_isMovingToggled && !_isResizingToggled) // No active moving or resizing
			{
				// Add to acceleration
				_cameraScrollingAcceleration += static_cast<float>(-_fe3d.input_getMouseWheelY() / SCROLL_WHEEL_DIVIDER) * _cameraSpeed;
			}
		}
		_cameraScrollingAcceleration *= 0.975f; // Slowing down (smoothing)

		// Update camera distance
		_cameraDistance += _cameraScrollingAcceleration;

		// Small offset so user cannot zoom inverted
		if (_cameraDistance < 0.1f)
		{
			_cameraDistance = 0.1f;
		}

		// Disable third person view
		if (_fe3d.camera_isThirdPersonViewEnabled())
		{
			_fe3d.camera_disableThirdPersonView();
		}

		// Check if MMB pressed
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && _fe3d.misc_isCursorInsideViewport())
			{
				_fe3d.camera_enableThirdPersonView();
			}
		}

		// Update camera
		_fe3d.camera_setThirdPersonPosition(_cameraLookatPosition);
		_fe3d.camera_setThirdPersonDistance(_cameraDistance);

		// Disable shadows
		if (_fe3d.gfx_isShadowsEnabled())
		{
			_fe3d.gfx_disableShadows();
		}

		// Enable shadows
		_fe3d.gfx_enableShadows(Vec3(_cameraLookatPosition + Vec3(_cameraDistance * 2.0f)),
			_cameraLookatPosition, _cameraDistance * 4.0f, _cameraDistance * 8.0f, 0.5f, false, false, 0);
	}
}