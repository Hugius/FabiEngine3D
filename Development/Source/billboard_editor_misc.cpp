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
		_fe3d.modelEntity_setVisible("@@cube", !_fe3d.input_isKeyToggled(InputType::KEY_R));

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
	}
}