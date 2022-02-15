#include "text3d_editor.hpp"

#include <algorithm>

const vector<string>& Text3dEditor::getLoadedEntityIds() const
{
	return _loadedEntityIds;
}

void Text3dEditor::deleteLoadedEntities()
{
	for(const auto& id : _loadedEntityIds)
	{
		_fe3d->text3d_delete(id);
	}

	_loadedEntityIds.clear();
}