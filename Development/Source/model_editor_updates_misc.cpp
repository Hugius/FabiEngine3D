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
			if (_fe3d.input_getKeyPressed(InputType::KEY_UP))
			{
				_cameraSpeed *= 2.0f;
			}
			if (_fe3d.input_getKeyPressed(InputType::KEY_DOWN))
			{
				_cameraSpeed /= 2.0f;
			}

			// Update vertical lookat movement
			if (_fe3d.input_getKeyDown(InputType::KEY_SPACE))
			{
				_cameraLookatPosition.y += (_cameraSpeed / 2.0f);
			}
			if (_fe3d.input_getKeyDown(InputType::KEY_LSHIFT))
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
				_cameraScrollingAcceleration += float(-_fe3d.input_getMouseWheelY() / SCROLL_WHEEL_DIVIDER) * _cameraSpeed;
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
			if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
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
		_fe3d.camera_setLookatPosition(_cameraLookatPosition);

		// Update shadows
		_fe3d.gfx_enableShadows(Vec3(_cameraLookatPosition + Vec3(_cameraDistance * 2.0f)),
			_cameraLookatPosition, _cameraDistance * 4.0f, _cameraDistance * 6.0f, 0.5f, false, true, 0);
	}
}