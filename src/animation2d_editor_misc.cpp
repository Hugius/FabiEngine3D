#include "animation2d_editor.hpp"

const vector<string> & Animation2dEditor::getLoadedAnimationIds() const
{
	return _loadedAnimation2dIds;
}

void Animation2dEditor::deleteLoadedAnimations()
{
	for(const auto & id : _loadedAnimation2dIds)
	{
		_fe3d->animation2d_delete(id);
	}

	_loadedAnimation2dIds.clear();
}