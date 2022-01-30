#include "text3d_editor.hpp"

#include <algorithm>

const vector<string>& Text3dEditor::getLoadedIds()
{
	sort(_loadedTextIds.begin(), _loadedTextIds.end());
	return _loadedTextIds;
}