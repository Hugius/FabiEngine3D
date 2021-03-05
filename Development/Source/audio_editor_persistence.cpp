#include "audio_editor.hpp"

#include <fstream>
#include <algorithm>

const vector<string> AudioEditor::getAllAudioPathsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> AudioEditor::getAllAudioPathsFromFile()");
	}

	// Clear names list from previous loads
	_loadedAudioIDs.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "projects\\" + _currentProjectID + "\\entities\\audio.fe3d";

	// Check if audio file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;
		vector<string> audioPaths;

		// Read model data
		while (std::getline(file, line))
		{
			// Temporary values
			string audioID, audioPath;
			std::istringstream iss(line);

			// Extract from file
			iss >> audioID >> audioPath;

			// Perform empty string & space conversions
			audioPath = (audioPath == "?") ? "" : audioPath;
			std::replace(audioPath.begin(), audioPath.end(), '?', ' ');

			// Save file path
			audioPaths.push_back(audioPath);
		}

		// Close file
		file.close();

		return audioPaths;
	}
	else
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: audio.fe3d missing!");
	}

	return {};
}

void AudioEditor::loadAudioEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> AudioEditor::loadAudioEntitiesFromFile()");
	}

	// Clear names list from previous loads
	_loadedAudioIDs.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "projects\\" + _currentProjectID + "\\entities\\audio.fe3d";

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
			_loadedAudioIDs.push_back(audioID);
			_fe3d.audioEntity_add2D(audioID, audioPath);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Audio data from project \"" + _currentProjectID + "\" loaded!");
	}
	else
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: audio.fe3d missing!");
	}
}

void AudioEditor::saveAudioEntitiesToFile()
{
	if (_isEditorLoaded)
	{
		// Error checking
		if (_currentProjectID == "")
		{
			_fe3d.logger_throwError("No current project loaded --> AudioEditor::saveAudioEntitiesToFile()");
		}

		// Create or overwrite audio file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "projects\\" + _currentProjectID + "\\entities\\audio.fe3d");

		// Write audio data into file
		for (auto& audioID : _loadedAudioIDs)
		{
			// Retrieve all values
			auto audioPath = _fe3d.audioEntity_getFilePath(audioID);

			// Perform empty string & space conversions
			audioPath = (audioPath == "") ? "?" : audioPath;
			std::replace(audioPath.begin(), audioPath.end(), ' ', '?');

			// Export data
			file << audioID << " " << audioPath << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Audio data from project \"" + _currentProjectID + "\" saved!");
	}
}