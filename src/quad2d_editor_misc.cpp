#include "quad2d_editor.hpp"

#include <algorithm>

const vector<string> & Quad2dEditor::getLoadedEntityIds() const
{
	return _loadedQuad2dIds;
}

void Quad2dEditor::deleteLoadedQuad2ds()
{
	for(const auto & quad2dId : _loadedQuad2dIds)
	{
		_fe3d->quad2d_delete(quad2dId);
	}

	_loadedQuad2dIds.clear();
}