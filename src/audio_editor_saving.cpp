#include "audio_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool AudioEditor::saveAudioEntitiesToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("AudioEditor::saveAudioEntitiesToFile");
	}

	// Create or overwrite file
	ofstream file;
	if(Config::getInst().isApplicationExported())
	{
		file.open(Tools::getRootDirectoryPath() + "data\\billboard.fe3d");
	}
	else
	{
		file.open(Tools::getRootDirectoryPath() + "game\\" + _currentProjectID + "\\data\\billboard.fe3d");
	}

	// Write audio data
	for(const auto& audioID : _loadedAudioIDs)
	{
		// Retrieve all values
		auto audioPath = _fe3d.sound_getFilePath(audioID);

		// Perform empty string & space conversions
		audioPath = (audioPath.empty()) ? "?" : audioPath;
		replace(audioPath.begin(), audioPath.end(), ' ', '?');

		// Write data to file
		file << audioID << " " << audioPath << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Audio data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}