#include "quad3d_editor.hpp"

#include <algorithm>

const vector<string> & Quad3dEditor::getLoadedEntityIds() const
{
	return _loadedEntityIds;
}

void Quad3dEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedEntityIds)
	{
		_fe3d->quad3d_delete(id);
	}

	_loadedEntityIds.clear();
}