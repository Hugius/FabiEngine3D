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

		// Update cursor difference
		Vec2 cursorPosition = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition());
		Vec2 cursorDifference = cursorPosition - _lastCursorPos;
		_lastCursorPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition());

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

		// Adding movement to the 3rd person view
		_cameraDistance += _cameraScrollingAcceleration;

		// Small offset so user cannot zoom inverted
		if (_cameraDistance < 0.1f)
		{
			_cameraDistance = 0.1f;
		}

		// Check if MMB pressed
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
			{
				if (_fe3d.misc_isCursorInsideViewport()) // Only if cursor inside 3d screen
				{
					_cameraAcceleration.x += cursorDifference.x * _cameraSpeed;
					_cameraAcceleration.y += cursorDifference.y * _cameraSpeed;
				}
			}
		}

		// Calculate cursor moving speed
		_cameraAcceleration *= 0.975f;
		_totalCursorDifference += _cameraAcceleration;
		_totalCursorDifference.y = std::clamp(_totalCursorDifference.y, 0.0f, 1.0f);

		// Calculate new camera position
		float x = (_cameraDistance * sin(_totalCursorDifference.x));
		float y = MIN_CAMERA_HEIGHT + (_cameraDistance * _totalCursorDifference.y);
		float z = (_cameraDistance * cos(_totalCursorDifference.x));

		// Update camera position
		_fe3d.camera_setPosition(_cameraLookatPosition + Vec3(x, y, z));

		// Update camera lookat position
		_fe3d.camera_setLookatPosition(_cameraLookatPosition);

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