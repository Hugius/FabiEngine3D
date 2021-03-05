#include "audio_editor.hpp"

#include <algorithm>

void AudioEditor::setCurrentProjectID(const string& projectName)
{
	_currentProjectID = projectName;
}

bool AudioEditor::isLoaded()
{
	return _isEditorLoaded;
}

const vector<string>& AudioEditor::getLoadedAudioIDs()
{
	std::sort(_loadedAudioIDs.begin(), _loadedAudioIDs.end());
	return _loadedAudioIDs;
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
			_fe3d.billboardEntity_setDiffuseMap("@@audioStatus", "engine_assets\\textures\\play.png");
		}
		else if (isPaused)
		{
			_fe3d.billboardEntity_setDiffuseMap("@@audioStatus", "engine_assets\\textures\\pause.png");
		}
		else
		{
			_fe3d.billboardEntity_setDiffuseMap("@@audioStatus", "engine_assets\\textures\\stop.png");
		}
		_fe3d.billboardEntity_rotate("@@audioStatus", Vec3(0.0f, 0.5f, 0.0f));
	}
}