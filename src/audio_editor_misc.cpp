#include "audio_editor.hpp"

#include <algorithm>

void AudioEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool AudioEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& AudioEditor::getLoadedAudioIDs()
{
	sort(_loadedAudioIDs.begin(), _loadedAudioIDs.end());
	return _loadedAudioIDs;
}

void AudioEditor::_updateMiscellaneous()
{
	// Temporary values
	bool isExisting = _fe3d.sound2d_isExisting(_currentAudioID);
	bool isPlaying = isExisting && _fe3d.sound2d_isPlaying(_currentAudioID);
	bool isPaused = isExisting && _fe3d.sound2d_isPaused(_currentAudioID);

	// Update audio status symbol
	if(isPlaying)
	{
		_fe3d.billboard_setDiffuseMap("@@icon", "engine\\assets\\textures\\play.png");
	}
	else if(isPaused)
	{
		_fe3d.billboard_setDiffuseMap("@@icon", "engine\\assets\\textures\\pause.png");
	}
	else
	{
		_fe3d.billboard_setDiffuseMap("@@icon", "engine\\assets\\textures\\stop.png");
	}
	_fe3d.billboard_rotate("@@icon", fvec3(0.0f, 0.5f, 0.0f));
}