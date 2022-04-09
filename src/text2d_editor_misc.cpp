#include "text2d_editor.hpp"

#include <algorithm>

const vector<string> & Text2dEditor::getLoadedEntityIds() const
{
	return _loadedEntityIds;
}

void Text2dEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedEntityIds)
	{
		_fe3d->text2d_delete(id);
	}

	_loadedEntityIds.clear();
}