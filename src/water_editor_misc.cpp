#include "water_editor.hpp"

#include <algorithm>

const vector<string> & WaterEditor::getLoadedEntityIds() const
{
	return _loadedWaterIds;
}

void WaterEditor::deleteLoadedEntities()
{
	for(const auto & waterId : _loadedWaterIds)
	{
		_fe3d->water_delete(waterId);
	}

	_loadedWaterIds.clear();
}