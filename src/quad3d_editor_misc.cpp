#include "quad3d_editor.hpp"

#include <algorithm>

const vector<string> & Quad3dEditor::getLoadedEntityIds() const
{
	return _loadedQuad3dIds;
}

void Quad3dEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedQuad3dIds)
	{
		_fe3d->quad3d_delete(id);
	}

	_loadedQuad3dIds.clear();
}