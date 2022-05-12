#include "spotlight_editor.hpp"

#include <algorithm>

const vector<string> & SpotlightEditor::getLoadedSpotlightIds() const
{
	return _loadedSpotlightIds;
}

void SpotlightEditor::deleteLoadedSpotlights()
{
	for(const auto & spotlightId : _loadedSpotlightIds)
	{
		_fe3d->spotlight_delete(spotlightId);
	}

	_loadedSpotlightIds.clear();
}