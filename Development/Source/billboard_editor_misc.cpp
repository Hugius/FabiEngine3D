#include "billboard_editor.hpp"

#include <algorithm>

void BillboardEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool BillboardEditor::isLoaded()
{
	return _isEditorLoaded;
}

const vector<string>& BillboardEditor::getLoadedBillboardIDs()
{
	std::sort(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end());
	return _loadedBillboardIDs;
}

void BillboardEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		// Lock toggling if GUI focused or cursor not in 3D viewport
		_fe3d.input_setKeyTogglingLocked(_gui.getGlobalScreen()->isFocused() || !_fe3d.misc_isCursorInsideViewport());

		// Update reference model visibility
		if (_fe3d.input_getKeyToggled(InputType::KEY_R))
		{
			_fe3d.modelEntity_hide("@@cube");
		}
		else
		{
			_fe3d.modelEntity_show("@@cube");
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