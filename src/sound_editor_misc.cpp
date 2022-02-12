#include "sound_editor.hpp"

#include <algorithm>

const vector<string>& SoundEditor::getLoadedSoundIds()
{
	return _loadedSoundIds;
}