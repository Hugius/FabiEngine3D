#include "audio_editor.hpp"

#include <fstream>
#include <algorithm>

void AudioEditor::loadAudioEntitiesFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded!");
	}

	// Clear names list from previous loads
	_audioIDs.clear();

	// Compose full folder path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\audio.fe3d";

	// Check if audio file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string audioID, audioPath;

			// For file extraction
			std::istringstream iss(line);

			// Extract from file
			iss >> audioID >> audioPath;

			// Perform empty string & space conversions
			audioPath = (audioPath == "?") ? "" : audioPath;
			std::replace(audioPath.begin(), audioPath.end(), '?', ' ');

			// Add audio ID
			_audioIDs.push_back(audioID);
			_fe3d.audioEntity_add2D(audioID, audioPath);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Audio data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void AudioEditor::saveAudioEntitiesToFile()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite audio file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\audio.fe3d");

		// Write audio data into file
		for (auto& audioID : _audioIDs)
		{
			// Retrieve all values
			auto audioPath = _fe3d.audioEntity_getFilePath(audioID);

			// Perform empty string & space conversions
			audioPath = (audioPath == "") ? "?" : audioPath;
			std::replace(audioPath.begin(), audioPath.end(), ' ', '?');

			// Export data
			file << audioID << " " << audioPath << " " << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Audio data from project \"" + _currentProjectName + "\" saved!");
	}
}