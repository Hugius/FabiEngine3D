#include "sky_editor.hpp"

#include <algorithm>

const vector<string>& SkyEditor::getLoadedIds()
{
	sort(_loadedSkyIds.begin(), _loadedSkyIds.end());
	return _loadedSkyIds;
}