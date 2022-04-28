#include "sound_editor.hpp"

#include <algorithm>

const vector<string> & SoundEditor::getLoadedSoundIds() const
{
	return _loadedSoundIds;
}

void SoundEditor::deleteLoadedSounds()
{
	for(const auto & soundId : _loadedSoundIds)
	{
		_fe3d->sound2d_delete(soundId);
	}
}