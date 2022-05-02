#include "aabb_editor.hpp"

#include <algorithm>

const vector<string> & AabbEditor::getLoadedAabbIds() const
{
	return _loadedAabbIds;
}

void AabbEditor::deleteLoadedAabbs()
{
	for(const auto & aabbId : _loadedAabbIds)
	{
		_fe3d->aabb_delete(aabbId);
	}

	_loadedAabbIds.clear();
}