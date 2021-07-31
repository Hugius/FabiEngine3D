#include "sky_editor.hpp"

void SkyEditor::_updateCamera()
{
	// Disable first person view
	if (_fe3d.camera_isFirstPersonViewEnabled())
	{
		_fe3d.camera_disableFirstPersonView();
	}

	// Check if sky is inactive
	if (_currentSkyID.empty() || !_fe3d.skyEntity_isExisting(_currentSkyID))
	{
		// Reset camera
		_fe3d.camera_reset();
		_fe3d.camera_setMouseSensitivity(MOUSE_SENSITIVITY);
	}
	else
	{
		// Show cursor
		_fe3d.imageEntity_setVisible("@@cursor", true);

		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Check if RMB pressed
			if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				// Enable first person view
				_fe3d.camera_enableFirstPersonView(_fe3d.camera_getFirstPersonYaw(), _fe3d.camera_getFirstPersonPitch());

				// Hide cursor
				_fe3d.imageEntity_setVisible("@@cursor", false);
			}
		}
	}
}

void SkyEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update wire frame rendering
		if (_fe3d.skyEntity_isExisting(_currentSkyID))
		{
			if (_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if (_fe3d.skyEntity_isWireFramed(_currentSkyID))
				{
					_fe3d.skyEntity_setWireFramed(_currentSkyID, false);
				}
				else
				{
					_fe3d.skyEntity_setWireFramed(_currentSkyID, true);
				}
			}
		}

		// Update debug rendering
		if (_fe3d.input_isKeyPressed(InputType::KEY_H))
		{
			if (_fe3d.misc_isDebugRenderingEnabled())
			{
				_fe3d.misc_disableDebugRendering();
			}
			else
			{
				_fe3d.misc_enableDebugRendering();
			}
		}
	}
}