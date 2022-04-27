#include "sky_editor.hpp"

#include <algorithm>

const vector<string> & SkyEditor::getLoadedEntityIds() const
{
	return _loadedSkyIds;
}

void SkyEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedSkyIds)
	{
		_fe3d->sky_delete(id);
	}

	_loadedSkyIds.clear();
}