#include "text3d_editor.hpp"

#include <algorithm>

const vector<string> & Text3dEditor::getLoadedEntityIds() const
{
	return _loadedText3dIds;
}

void Text3dEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedText3dIds)
	{
		_fe3d->text3d_delete(id);
	}

	_loadedText3dIds.clear();
}