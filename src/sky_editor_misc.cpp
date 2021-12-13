#include "sky_editor.hpp"

#include <algorithm>

void SkyEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool SkyEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& SkyEditor::getLoadedIDs()
{
	sort(_loadedSkyIDs.begin(), _loadedSkyIDs.end());
	return _loadedSkyIDs;
}