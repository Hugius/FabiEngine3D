#include "sound2d_editor.hpp"

#include <algorithm>

const vector<string> & Sound2dEditor::getLoadedSound2dIds() const
{
	return _loadedSound2dIds;
}

void Sound2dEditor::deleteLoadedSound2ds()
{
	for(const auto & sound2dId : _loadedSound2dIds)
	{
		_fe3d->sound2d_delete(sound2dId);
	}
}