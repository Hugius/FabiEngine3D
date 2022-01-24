#include "sound_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool SoundEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectId.empty())
	{
		Logger::throwError("SoundEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectId + "\\data\\sound.fe3d");

	for(const auto& soundID : _loadedSoundIDs)
	{
		auto audioPath = _fe3d->sound2d_getAudioPath(soundID);

		audioPath = string(audioPath.empty() ? "" : audioPath.substr(string("projects\\" + _currentProjectId + "\\").size()));

		audioPath = (audioPath.empty()) ? "?" : audioPath;

		replace(audioPath.begin(), audioPath.end(), ' ', '?');

		file << soundID << " " << audioPath << endl;
	}

	file.close();

	Logger::throwInfo("Sound editor data saved!");

	return true;
}