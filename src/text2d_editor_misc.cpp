#include "text2d_editor.hpp"

#include <algorithm>

const vector<string>& Text2dEditor::getLoadedIds()
{
	sort(_loadedTextIds.begin(), _loadedTextIds.end());
	return _loadedTextIds;
}