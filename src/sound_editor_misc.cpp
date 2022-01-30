#include "sound_editor.hpp"

#include <algorithm>

const bool SoundEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& SoundEditor::getLoadedIds()
{
	sort(_loadedSoundIds.begin(), _loadedSoundIds.end());
	return _loadedSoundIds;
}