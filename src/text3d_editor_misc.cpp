#include "text3d_editor.hpp"

#include <algorithm>

const vector<string> & Text3dEditor::getLoadedEntityIds() const
{
	return _loadedText3dIds;
}

void Text3dEditor::deleteLoadedText3ds()
{
	for(const auto & text3dId : _loadedText3dIds)
	{
		_fe3d->text3d_delete(text3dId);
	}

	_loadedText3dIds.clear();
}