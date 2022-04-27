#include "model_editor.hpp"

#include <algorithm>

const vector<string> & ModelEditor::getLoadedEntityIds() const
{
	return _loadedModelIds;
}

void ModelEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedModelIds)
	{
		_fe3d->model_delete(id);
	}

	_loadedModelIds.clear();
}