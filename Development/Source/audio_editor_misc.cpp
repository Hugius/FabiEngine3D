#include "audio_editor.hpp"

void AudioEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool AudioEditor::isLoaded()
{
	return _isEditorLoaded;
}

const vector<string>& AudioEditor::getAudioNames()
{
	return _audioIDs;
}

void AudioEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		// Temporary values
		bool isExisting = _fe3d.audioEntity_isExisting(_currentAudioID);
		bool isPlaying = isExisting && _fe3d.audioEntity_isPlaying(_currentAudioID);
		bool isPaused = isExisting && _fe3d.audioEntity_isPaused(_currentAudioID);

		// Update audio status symbol
		if (isPlaying)
		{
			_fe3d.billboardEntity_setDiffuseMap("@@audioStatus", "engine\\textures\\play.png");
		}
		else if (isPaused)
		{
			_fe3d.billboardEntity_setDiffuseMap("@@audioStatus", "engine\\textures\\pause.png");
		}
		else
		{
			_fe3d.billboardEntity_setDiffuseMap("@@audioStatus", "engine\\textures\\stop.png");
		}
		_fe3d.billboardEntity_rotate("@@audioStatus", Vec3(0.0f, 0.5f, 0.0f));
	}
}