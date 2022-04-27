#include "water_editor.hpp"

#include <algorithm>

const vector<string> & WaterEditor::getLoadedEntityIds() const
{
	return _loadedWaterIds;
}

void WaterEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedWaterIds)
	{
		_fe3d->water_delete(id);
	}

	_loadedWaterIds.clear();
}