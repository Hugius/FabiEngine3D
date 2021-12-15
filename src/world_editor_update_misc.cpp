#include "world_editor.hpp"

void WorldEditor::_updateCamera()
{
	if(!_currentWorldID.empty())
	{
		// Camera looking
		if(_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && !_gui.getOverlay()->isFocused())
		{
			// Enable first person view
			if(_fe3d.misc_isCursorInsideViewport() && !_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.camera_enableFirstPersonView(_fe3d.camera_getFirstPersonYaw(), _fe3d.camera_getFirstPersonPitch());
			}

			// Disable cursor while in FPS mode
			if(_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.image_setVisible("@@cursor", false);
			}
		}
		else
		{
			// Disable first person view
			if(_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.camera_disableFirstPersonView();
			}

			// Cannot show cursor if outside of engine window
			if(_fe3d.misc_isCursorInsideWindow())
			{
				_fe3d.image_setVisible("@@cursor", true);
			}
		}

		// Camera movement
		if(!_gui.getOverlay()->isFocused())
		{
			// X movement
			if(_fe3d.input_isKeyDown(InputType::KEY_A))
			{
				_fe3d.camera_moveFollowX(-_editorSpeed / 100.0f);
			}
			if(_fe3d.input_isKeyDown(InputType::KEY_D))
			{
				_fe3d.camera_moveFollowX(_editorSpeed / 100.0f);
			}

			// Y movement
			if(_fe3d.input_isKeyDown(InputType::KEY_SPACE))
			{
				_fe3d.camera_move(fvec3(0.0f, _editorSpeed / 75.0f, 0.0f));
			}
			if(_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
			{
				_fe3d.camera_move(fvec3(0.0f, -(_editorSpeed / 75.0f), 0.0f));
			}

			// Z movement
			if(_fe3d.input_isKeyDown(InputType::KEY_W))
			{
				_fe3d.camera_moveFollowZ(_editorSpeed / 100.0f);
			}
			if(_fe3d.input_isKeyDown(InputType::KEY_S))
			{
				_fe3d.camera_moveFollowZ(-_editorSpeed / 100.0f);
			}
		}
	}
	else
	{
		// Reset camera view
		_fe3d.camera_setYaw(0.0f);
		_fe3d.camera_setPitch(0.0f);
	}
}