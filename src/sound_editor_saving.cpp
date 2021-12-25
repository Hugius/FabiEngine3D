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

	if(_currentProjectID.empty())
	{
		Logger::throwError("SoundEditor::saveToFile");
	}

	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\sound.fe3d");

	for(const auto& soundID : _loadedSoundIDs)
	{
		auto audioPath = _fe3d.sound2d_getAudioPath(soundID);

		audioPath = string(audioPath.empty() ? "" : audioPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		audioPath = (audioPath.empty()) ? "?" : audioPath;

		replace(audioPath.begin(), audioPath.end(), ' ', '?');

		file << soundID << " " << audioPath << endl;
	}

	file.close();

	Logger::throwInfo("Sound data saved!");

	return true;
}