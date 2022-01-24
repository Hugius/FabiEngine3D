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

const vector<string>& SkyEditor::getLoadedIds()
{
	sort(_loadedSkyIds.begin(), _loadedSkyIds.end());
	return _loadedSkyIds;
}