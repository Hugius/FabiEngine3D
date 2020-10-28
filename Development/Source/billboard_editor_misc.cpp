#include "billboard_editor.hpp"

void BillboardEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool BillboardEditor::isLoaded()
{
	return _isLoaded;
}

vector<string>& BillboardEditor::getBillboardNames()
{
	return _billboardNames;
}

void BillboardEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		// Lock toggling if GUI focused or cursor not in 3D viewport
		_fe3d.input_setKeyTogglingLocked(_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport());

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