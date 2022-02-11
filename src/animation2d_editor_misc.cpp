#include "animation2d_editor.hpp"

const vector<string> Animation2dEditor::getLoadedIds()
{
	sort(_loadedAnimationIds.begin(), _loadedAnimationIds.end());

	return _loadedAnimationIds;
}