#include "quad3d_editor.hpp"

#include <algorithm>

const vector<string> & Quad3dEditor::getLoadedEntityIds() const
{
	return _loadedQuad3dIds;
}

void Quad3dEditor::deleteLoadedQuad3ds()
{
	for(const auto & quad3dId : _loadedQuad3dIds)
	{
		_fe3d->quad3d_delete(quad3dId);
	}

	_loadedQuad3dIds.clear();
}