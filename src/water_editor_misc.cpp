#include "water_editor.hpp"

#include <algorithm>

const vector<string>& WaterEditor::getLoadedEntityIds() const
{
	return _loadedEntityIds;
}

void WaterEditor::deleteLoadedEntities()
{
	for(const auto& id : _loadedEntityIds)
	{
		_fe3d->water_delete(id);
	}

	_loadedEntityIds.clear();
}