#include "sound_editor.hpp"

#include <algorithm>

void SoundEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
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