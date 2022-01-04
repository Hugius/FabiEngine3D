#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_tryPartChoosing(const string& nextActiveScreenID)
{
	if(_fe3d.model_isMultiParted(_currentModelID))
	{
		auto IDs = _fe3d.model_getPartIDs(_currentModelID);
		sort(IDs.begin(), IDs.end());
		_gui.getOverlay()->createChoiceForm("partList", "Select Part", fvec2(-0.5f, 0.1f), IDs);
		_isChoosingPart = true;
		_nextActiveScreenID = nextActiveScreenID;
	}
	else
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

const vector<string>& ModelEditor::getLoadedIDs()
{
	sort(_loadedModelIDs.begin(), _loadedModelIDs.end());
	return _loadedModelIDs;
}