#include "audio_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> AudioEditor::getAllAudioPathsFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("AudioEditor::getAllAudioPathsFromFile");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `audio.fe3d` missing!");
		return {};
	}

	// Load audio file
	ifstream file(filePath);

	// Read model data
	vector<string> audioPaths;
	string line;
	while (getline(file, line))
	{
		// Data placeholders
		string audioID, audioPath;

		// For file extraction
		istringstream iss(line);

		// Read from file
		iss >> audioID >> audioPath;

		// Perform empty string & space conversions
		audioPath = (audioPath == "?") ? "" : audioPath;
		replace(audioPath.begin(), audioPath.end(), '?', ' ');

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
	if (_currentProjectID.empty())
	{
		Logger::throwError("AudioEditor::loadAudioEntitiesFromFile");
	}

	// Clear IDs from previous loads
	_loadedAudioIDs.clear();

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `audio.fe3d` missing!");
		return false;
	}

	// Load audio file
	ifstream file(filePath);

	// Read audio file
	string line;
	while (getline(file, line))
	{
		// Data placeholders
		string audioID, audioPath;

		// For file extraction
		istringstream iss(line);

		// Read from file
		iss >> audioID >> audioPath;

		// Perform empty string & space conversions
		audioPath = (audioPath == "?") ? "" : audioPath;
		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		// Create audio
		_fe3d.sound_create(audioID, audioPath);

		// Check if audio creation went well
		if (_fe3d.sound_isExisting(audioID))
		{
			// Add audio ID
			_loadedAudioIDs.push_back(audioID);
		}
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
	if (_currentProjectID.empty())
	{
		Logger::throwError("AudioEditor::saveAudioEntitiesToFile");
	}

	// Compose file path
	const string filePath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d");

	// Create or overwrite audio file
	ofstream file(filePath);

	// Write audio data
	for (const auto& audioID : _loadedAudioIDs)
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