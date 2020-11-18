#include "audio_editor.hpp"

void AudioEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool AudioEditor::isLoaded()
{
	return _isLoaded;
}