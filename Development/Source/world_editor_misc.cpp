#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::setCurrentProjectName(string projectName)
{
	_currentProjectName = projectName;
}

bool WorldEditor::isLoaded()
{
	return _isLoaded;
}

void WorldEditor::_updateMiscellaneous()
{
	// Update wireframe visibility
	if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport())
	{
		_fe3d.input_getKeyToggled(Input::KEY_W) ? _fe3d.misc_enableWireframeRendering() : _fe3d.misc_disableWireframeRendering();
	}
}