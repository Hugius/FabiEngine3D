#include "sky_editor.hpp"

#include <algorithm>

const vector<string> & SkyEditor::getLoadedEntityIds() const
{
	return _loadedSkyIds;
}

void SkyEditor::deleteLoadedSkies()
{
	for(const auto & skyId : _loadedSkyIds)
	{
		_fe3d->sky_delete(skyId);
	}

	_loadedSkyIds.clear();
}