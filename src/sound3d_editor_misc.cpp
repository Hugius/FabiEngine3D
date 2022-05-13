#include "sound3d_editor.hpp"

#include <algorithm>

const vector<string> & Sound3dEditor::getLoadedSound3dIds() const
{
	return _loadedSound3dIds;
}

void Sound3dEditor::deleteLoadedSound3ds()
{
	for(const auto & sound3dId : _loadedSound3dIds)
	{
		_fe3d->sound3d_delete(sound3dId);
	}

	_loadedSound3dIds.clear();
}