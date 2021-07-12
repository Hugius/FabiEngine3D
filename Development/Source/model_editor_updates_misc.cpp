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
		
		// Check if third person view is enabled
		if (_fe3d.camera_isThirdPersonViewEnabled())
		{
			// Disable third person view
			_fe3d.camera_disableThirdPersonView();

			// Show cursor
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
				// Update lookat position
				_fe3d.camera_setThirdPersonLookat(_cameraLookatPosition);

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

void ModelEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		// Lock toggling if GUI focused or cursor not in 3D viewport
		_fe3d.input_setKeyTogglingLocked(_gui.getGlobalScreen()->isFocused() || !_fe3d.misc_isCursorInsideViewport());

		// Update reference model visibility
		if (_fe3d.input_isKeyToggled(InputType::KEY_R))
		{
			_fe3d.modelEntity_setVisible("@@cube", false);
		}
		else
		{
			_fe3d.modelEntity_setVisible("@@cube", true);
		}

		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
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

		// Update wireframed model rendering
		string modelID = _currentModelID.empty() ? _hoveredModelID : _currentModelID;
		if (!modelID.empty() && _fe3d.modelEntity_isExisting(modelID))
		{
			if (_fe3d.input_isKeyToggled(InputType::KEY_F))
			{
				_fe3d.modelEntity_setWireframed(modelID, true);
			}
			else
			{
				_fe3d.modelEntity_setWireframed(modelID, false);
			}
		}
	}
}