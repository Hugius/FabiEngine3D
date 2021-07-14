#include "audio_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

const vector<string> AudioEditor::getAllAudioPathsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("AudioEditor::getAllAudioPathsFromFile() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"audio.fe3d\" file missing!");
		return {};
	}

	// Load audio file
	std::ifstream file(filePath);

	// Read model data
	vector<string> audioPaths;
	string line;
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

bool AudioEditor::loadAudioEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("AudioEditor::loadAudioEntitiesFromFile() ---> no current project loaded!");
	}

	// Clear IDs from previous loads
	_loadedAudioIDs.clear();

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"audio.fe3d\" file missing!");
		return false;
	}

	// Load audio file
	std::ifstream file(filePath);

	// Read audio file
	string line;
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
		_fe3d.soundEntity_add(audioID, audioPath);
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Audio data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}

bool AudioEditor::saveAudioEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("AudioEditor::saveAudioEntitiesToFile() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d");

	// Create or overwrite audio file
	std::ofstream file(filePath);

	// Write audio data
	for (const auto& audioID : _loadedAudioIDs)
	{
		// Retrieve all values
		auto audioPath = _fe3d.soundEntity_getFilePath(audioID);

		// Perform empty string & space conversions
		audioPath = (audioPath == "") ? "?" : audioPath;
		std::replace(audioPath.begin(), audioPath.end(), ' ', '?');

		// Export data
		file << audioID << " " << audioPath << std::endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Audio data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}