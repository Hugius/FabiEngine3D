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

const vector<string>& SoundEditor::getLoadedIDs()
{
	sort(_loadedSoundIDs.begin(), _loadedSoundIDs.end());
	return _loadedSoundIDs;
}