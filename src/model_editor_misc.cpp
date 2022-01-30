#include "model_editor.hpp"

#include <algorithm>

const vector<string>& ModelEditor::getLoadedIds()
{
	sort(_loadedModelIds.begin(), _loadedModelIds.end());
	return _loadedModelIds;
}