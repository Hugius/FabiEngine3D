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
		// Data to save
		auto audioPath = _fe3d.sound2d_getAudioPath(soundID);

		// Convert to short path
		audioPath = string(audioPath.empty() ? "" : audioPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		// Convert empty string
		audioPath = (audioPath.empty()) ? "?" : audioPath;

		// Convert spaces
		replace(audioPath.begin(), audioPath.end(), ' ', '?');

		// Write data to file
		file << soundID << " " << audioPath << endl;
	}

	file.close();

	Logger::throwInfo("Sound data saved!");

	return true;
}