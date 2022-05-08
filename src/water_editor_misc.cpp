#include "water_editor.hpp"

#include <algorithm>

const vector<string> & WaterEditor::getLoadedWaterIds() const
{
	return _loadedWaterIds;
}

void WaterEditor::deleteLoadedWaters()
{
	for(const auto & waterId : _loadedWaterIds)
	{
		_fe3d->water_delete(waterId);
	}

	_loadedWaterIds.clear();
}

void WaterEditor::inject(shared_ptr<SkyEditor> skyEditor)
{
	_skyEditor = skyEditor;
}