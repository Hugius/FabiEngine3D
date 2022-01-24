#include "sky_editor.hpp"

#include <algorithm>

void SkyEditor::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
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