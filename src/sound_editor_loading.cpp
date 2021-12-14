#include "sound_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> SoundEditor::getAllAudioPathsFromFile() const
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("SoundEditor::getAllAudioPathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\sound.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `sound.fe3d` missing!");
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
		string soundID, audioPath;

		// For file extraction
		istringstream iss(line);

		// Read from file
		iss >> soundID >> audioPath;

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

const bool SoundEditor::loadFromFile()
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("SoundEditor::loadFromFile");
	}

	// Clear IDs from previous loads
	_loadedSoundIDs.clear();

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\sound.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `sound.fe3d` missing!");
		return false;
	}

	// Load sound file
	ifstream file(filePath);

	// Read sound file
	string line;
	while(getline(file, line))
	{
		// Data placeholders
		string soundID, audioPath;

		// For file extraction
		istringstream iss(line);

		// Read from file
		iss >> soundID >> audioPath;

		// Convert empty string
		audioPath = (audioPath == "?") ? "" : audioPath;

		// Convert spaces
		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		// Convert to long path
		if(!Config::getInst().isApplicationExported())
		{
			audioPath = string("projects\\" + _currentProjectID + "\\" + audioPath);
		}

		// Create sound
		_fe3d.sound2d_create(soundID, audioPath);

		// Check if sound creation went well
		if(_fe3d.sound2d_isExisting(soundID))
		{
			// Add sound ID
			_loadedSoundIDs.push_back(soundID);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Sound data loaded!");

	// Return
	return true;
}