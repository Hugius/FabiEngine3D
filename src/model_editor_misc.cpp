#include "model_editor.hpp"

#include <algorithm>

const vector<string> & ModelEditor::getLoadedEntityIds() const
{
	return _loadedEntityIds;
}

void ModelEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedEntityIds)
	{
		_fe3d->model_delete(id);
	}

	_loadedEntityIds.clear();
}