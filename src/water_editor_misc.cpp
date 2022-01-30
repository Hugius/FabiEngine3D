#include "water_editor.hpp"

#include <algorithm>

const vector<string>& WaterEditor::getLoadedIds()
{
	sort(_loadedWaterIds.begin(), _loadedWaterIds.end());
	return _loadedWaterIds;
}