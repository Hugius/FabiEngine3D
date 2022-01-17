#include "billboard_editor.hpp"

#include <algorithm>

void Quad3dEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool Quad3dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& Quad3dEditor::getLoadedIDs()
{
	sort(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end());
	return _loadedBillboardIDs;
}