#include "quad2d_editor.hpp"

#include <algorithm>

const vector<string>& Quad2dEditor::getLoadedIds()
{
	sort(_loadedQuadIds.begin(), _loadedQuadIds.end());

	return _loadedQuadIds;
}