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

	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("AudioEditor::saveAudioEntitiesToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\audio.fe3d");

	// Write audio data
	for(const auto& audioID : _loadedAudioIDs)
	{
		// Retrieve all values
		auto audioPath = _fe3d.sound2D_getAudioPath(audioID);

		// Convert to short path
		audioPath = string(audioPath.empty() ? "" : audioPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		// Convert empty string
		audioPath = (audioPath.empty()) ? "?" : audioPath;

		// Convert spaces
		replace(audioPath.begin(), audioPath.end(), ' ', '?');

		// Write data to file
		file << audioID << " " << audioPath << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Audio data saved!");

	// Return
	return true;
}