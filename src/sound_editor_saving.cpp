#include "sound_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool SoundEditor::saveToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("SoundEditor::saveToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\sound.fe3d");

	// Write sound data
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

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Sound data saved!");

	// Return
	return true;
}