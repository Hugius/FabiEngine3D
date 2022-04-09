#include "quad2d_editor.hpp"

#include <algorithm>

const vector<string> & Quad2dEditor::getLoadedEntityIds() const
{
	return _loadedEntityIds;
}

void Quad2dEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedEntityIds)
	{
		_fe3d->quad2d_delete(id);
	}

	_loadedEntityIds.clear();
}