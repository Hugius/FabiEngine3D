#include "audio_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

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

	// Compose file path
	const string filePath = (Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
							 ("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d");

	// Create or overwrite audio file
	ofstream file(filePath);

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