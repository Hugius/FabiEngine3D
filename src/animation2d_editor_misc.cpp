#include "animation2d_editor.hpp"

const vector<string> & Animation2dEditor::getLoadedAnimation2dIds() const
{
	return _loadedAnimation2dIds;
}

void Animation2dEditor::deleteLoadedAnimation2ds()
{
	for(const auto & animation2dId : _loadedAnimation2dIds)
	{
		_fe3d->animation2d_delete(animation2dId);
	}

	_loadedAnimation2dIds.clear();
}