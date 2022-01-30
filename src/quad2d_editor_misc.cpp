#include "quad2d_editor.hpp"

#include <algorithm>

const bool Quad2dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& Quad2dEditor::getLoadedIds()
{
	sort(_loadedQuadIds.begin(), _loadedQuadIds.end());
	return _loadedQuadIds;
}