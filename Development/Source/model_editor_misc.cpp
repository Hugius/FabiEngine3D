#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void ModelEditor::_preparePartChoosing(function<void()>&& executionFunction)
{
	auto IDs = _fe3d.modelEntity_getPartIDs(_currentModelID);
	sort(IDs.begin(), IDs.end());
	_gui.getGlobalScreen()->createChoiceForm("partList", "Select Part", Vec2(0.0f, 0.1f), IDs);
	_isChoosingPart = true;
	_partExecutionFunction = executionFunction;
}

void ModelEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool ModelEditor::isLoaded()
{
	return _isEditorLoaded;
}

const vector<string>& ModelEditor::getLoadedModelIDs()
{
	sort(_loadedModelIDs.begin(), _loadedModelIDs.end());
	return _loadedModelIDs;
}