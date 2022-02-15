#include "sky_editor.hpp"

#include <algorithm>

const vector<string>& SkyEditor::getLoadedEntityIds() const
{
	return _loadedEntityIds;
}

void SkyEditor::deleteLoadedEntities()
{
	for(const auto& id : _loadedEntityIds)
	{
		_fe3d->sky_delete(id);
	}

	_loadedEntityIds.clear();
}