#include "pointlight_editor.hpp"

#include <algorithm>

const vector<string> & PointlightEditor::getLoadedPointlightIds() const
{
	return _loadedPointlightIds;
}

void PointlightEditor::deleteLoadedPointlights()
{
	for(const auto & pointlightId : _loadedPointlightIds)
	{
		_fe3d->pointlight_delete(pointlightId);
	}

	_loadedPointlightIds.clear();
}