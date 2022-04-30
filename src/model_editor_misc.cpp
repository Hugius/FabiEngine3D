#include "model_editor.hpp"

#include <algorithm>

const vector<string> & ModelEditor::getLoadedEntityIds() const
{
	return _loadedModelIds;
}

void ModelEditor::deleteLoadedModels()
{
	for(const auto & modelId : _loadedModelIds)
	{
		_fe3d->model_delete(modelId);
	}

	_loadedModelIds.clear();
}