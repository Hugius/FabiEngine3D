#include "audio_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> AudioEditor::getAllAudioPathsFromFile() const
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("AudioEditor::getAllAudioPathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\audio.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `audio.fe3d` missing!");
		return {};
	}

	// Load audio file
	ifstream file(filePath);

	// Read model data
	vector<string> audioPaths;
	string line;
	while(getline(file, line))
	{
		// Data placeholders
		string audioID, audioPath;

		// For file extraction
		istringstream iss(line);

		// Read from file
		iss >> audioID >> audioPath;

		// Convert empty string
		audioPath = (audioPath == "?") ? "" : audioPath;

		// Convert spaces
		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		// Convert to long path
		if(!Config::getInst().isApplicationExported())
		{
			audioPath = string("projects\\" + _currentProjectID + "\\" + audioPath);
		}

		// Save path
		audioPaths.push_back(audioPath);
	}

	// Close file
	file.close();

	return audioPaths;
}

const bool AudioEditor::loadAudioEntitiesFromFile()
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("AudioEditor::loadAudioEntitiesFromFile");
	}

	// Clear IDs from previous loads
	_loadedAudioIDs.clear();

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\audio.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `audio.fe3d` missing!");
		return false;
	}

	// Load audio file
	ifstream file(filePath);

	// Read audio file
	string line;
	while(getline(file, line))
	{
		// Data placeholders
		string audioID, audioPath;

		// For file extraction
		istringstream iss(line);

		// Read from file
		iss >> audioID >> audioPath;

		// Convert empty string
		audioPath = (audioPath == "?") ? "" : audioPath;

		// Convert spaces
		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		// Convert to long path
		if(!Config::getInst().isApplicationExported())
		{
			audioPath = string("projects\\" + _currentProjectID + "\\" + audioPath);
		}

		// Create audio
		_fe3d.sound2d_create(audioID, audioPath);

		// Check if audio creation went well
		if(_fe3d.sound2d_isExisting(audioID))
		{
			// Add audio ID
			_loadedAudioIDs.push_back(audioID);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Audio data loaded!");

	// Return
	return true;
}