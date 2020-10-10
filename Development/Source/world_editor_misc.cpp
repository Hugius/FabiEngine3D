#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool WorldEditor::isLoaded()
{
	return _isLoaded;
}

void WorldEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		// Lock toggling if GUI focused
		_fe3d.input_setKeyTogglingLocked(_gui->getGlobalScreen()->isFocused());

		// Wireframe rendering
		if (_fe3d.input_getKeyToggled(InputType::KEY_F))
		{
			_fe3d.misc_enableWireframeRendering();
		}
		else
		{
			_fe3d.misc_disableWireframeRendering();
		}

		// Debug rendering
		if (_fe3d.input_getKeyToggled(InputType::KEY_H))
		{
			_fe3d.misc_enableDebugRendering();
		}
		else
		{
			_fe3d.misc_disableDebugRendering();
		}
	}
}