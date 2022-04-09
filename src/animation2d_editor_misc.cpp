#include "animation2d_editor.hpp"

const vector<string> & Animation2dEditor::getLoadedAnimationIds() const
{
	return _loadedAnimationIds;
}

void Animation2dEditor::deleteLoadedAnimations()
{
	for(const auto & id : _loadedAnimationIds)
	{
		_fe3d->animation2d_delete(id);
	}

	_loadedAnimationIds.clear();
}