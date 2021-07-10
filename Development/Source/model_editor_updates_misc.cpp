#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateCamera()
{
	if (_isEditorLoaded)
	{
		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Update moving up
			if (_fe3d.input_isKeyDown(InputType::KEY_SPACE))
			{
				_cameraLookatPosition.y += LOOKAT_MOVEMENT_SPEED;
			}

			// Update moving down
			if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT))
			{
				_cameraLookatPosition.y -= LOOKAT_MOVEMENT_SPEED;
				_cameraLookatPosition.y = std::max(0.0f, _cameraLookatPosition.y);
			}
		}

		// Disable third person view
		if (_fe3d.camera_isThirdPersonViewEnabled())
		{
			_fe3d.camera_disableThirdPersonView();
			_fe3d.imageEntity_setVisible("@@cursor", true);

			// Disable shadows
			if (_fe3d.gfx_isShadowsEnabled())
			{
				_fe3d.gfx_disableShadows();
			}

			// Enable shadows
			const auto distance = _fe3d.camera_getThirdPersonDistance();
			_fe3d.gfx_enableShadows(Vec3(_cameraLookatPosition + Vec3(distance * 2.0f)),
				_cameraLookatPosition, distance * 4.0f, distance * 8.0f, 0.5f, false, false, 0);
		}

		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Check if RMB pressed
			if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d.camera_enableThirdPersonView(
					_fe3d.camera_getThirdPersonYaw(), 
					_fe3d.camera_getThirdPersonPitch(), 
					_fe3d.camera_getThirdPersonDistance());
				_fe3d.camera_setThirdPersonLookat(_cameraLookatPosition);
				_fe3d.imageEntity_setVisible("@@cursor", false);
			}
		}
	}
}