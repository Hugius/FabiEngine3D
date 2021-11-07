#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_tryPartChoosing(const string& nextActiveScreenID)
{
	if(_fe3d.modelEntity_isMultiParted(_currentModelID)) // Multiple parts
	{
		auto IDs = _fe3d.modelEntity_getPartIDs(_currentModelID);
		sort(IDs.begin(), IDs.end());
		_gui.getGlobalScreen()->createChoiceForm("partList", "Select Part", Vec2(0.0f, 0.1f), IDs);
		_isChoosingPart = true;
		_nextActiveScreenID = nextActiveScreenID;
	}
	else // Single part
	{
		_gui.getViewport("left")->getWindow("main")->setActiveScreen(nextActiveScreenID);
	}
}

void ModelEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool ModelEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& ModelEditor::getLoadedModelIDs()
{
	sort(_loadedModelIDs.begin(), _loadedModelIDs.end());
	return _loadedModelIDs;
}