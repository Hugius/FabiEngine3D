#include "sky_editor.hpp"

void SkyEditor::_updateCamera()
{
	// Check if first person view is enabled
	if (_fe3d.camera_isFirstPersonViewEnabled())
	{
		// Hide cursor
		_fe3d.imageEntity_setVisible("@@cursor", false);
	}

	// Check if allowed by GUI
	if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Check if RMB pressed
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check first person view status
			if (_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.camera_disableFirstPersonView();
			}
			else
			{
				_fe3d.camera_enableFirstPersonView(_fe3d.camera_getFirstPersonYaw(), _fe3d.camera_getFirstPersonPitch());
			}
		}
	}

	// Disable first person view if necessary
	if (_fe3d.camera_isFirstPersonViewEnabled())
	{
		if (_gui.getGlobalScreen()->isFocused())
		{
			_fe3d.camera_disableFirstPersonView();
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