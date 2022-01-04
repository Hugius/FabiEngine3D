#include "billboard_editor.hpp"

#include <algorithm>

void BillboardEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool BillboardEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& BillboardEditor::getLoadedIDs()
{
	sort(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end());
	return _loadedBillboardIDs;
}