#include "sky_editor.hpp"

#include <algorithm>

const bool SkyEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& SkyEditor::getLoadedIds()
{
	sort(_loadedSkyIds.begin(), _loadedSkyIds.end());
	return _loadedSkyIds;
}