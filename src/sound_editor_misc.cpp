#include "sound_editor.hpp"

#include <algorithm>

void SoundEditor::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
}

const bool SoundEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& SoundEditor::getLoadedIds()
{
	sort(_loadedSoundIds.begin(), _loadedSoundIds.end());
	return _loadedSoundIds;
}