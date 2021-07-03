#include "environment_editor.hpp"

#include <algorithm>

void EnvironmentEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool EnvironmentEditor::isLoaded()
{
	return _isEditorLoaded;
}

void EnvironmentEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Update wireframe rendering
			if (_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if (_fe3d.misc_isWireframeRenderingEnabled())
				{
					_fe3d.misc_disableWireframeRendering();
				}
				else
				{
					_fe3d.misc_enableWireframeRendering();
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
}