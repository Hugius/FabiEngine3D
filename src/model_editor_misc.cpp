#include "model_editor.hpp"

#include <algorithm>

const bool ModelEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& ModelEditor::getLoadedIds()
{
	sort(_loadedModelIds.begin(), _loadedModelIds.end());
	return _loadedModelIds;
}