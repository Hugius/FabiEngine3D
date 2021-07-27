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