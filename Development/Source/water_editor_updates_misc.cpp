#include "water_editor.hpp"
#include "logger.hpp"

void WaterEditor::_updateCamera()
{
	// Disable third person view
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}

	// Check if water is inactive
	if (_currentWaterID.empty() || !_fe3d.waterEntity_isExisting(_currentWaterID))
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
				// Enable third person view
				_fe3d.camera_enableThirdPersonView(
					_fe3d.camera_getThirdPersonYaw(),
					_fe3d.camera_getThirdPersonPitch(),
					_fe3d.camera_getThirdPersonDistance());

				// Hide cursor
				_fe3d.imageEntity_setVisible("@@cursor", false);
			}
		}
	}
}

void WaterEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update reference model visibility
		if (_fe3d.input_isKeyPressed(InputType::KEY_R))
		{
			if (_fe3d.modelEntity_isVisible("@@cube"))
			{
				_fe3d.modelEntity_setVisible("@@cube", false);
			}
			else
			{
				_fe3d.modelEntity_setVisible("@@cube", true);
			}
		}

		// Update wire frame rendering
		if (_fe3d.waterEntity_isExisting(_currentWaterID))
		{
			if (_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if (_fe3d.waterEntity_isWireFramed(_currentWaterID))
				{
					_fe3d.waterEntity_setWireFramed(_currentWaterID, false);
				}
				else
				{
					_fe3d.waterEntity_setWireFramed(_currentWaterID, true);
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