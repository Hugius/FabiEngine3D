#include "sound_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> SoundEditor::getAudioPathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("SoundEditor::getAudioPathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\sound.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `sound.fe3d` missing!");
		return {};
	}

	ifstream file(filePath);

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

	file.close();

	return audioPaths;
}

const bool SoundEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("SoundEditor::loadFromFile");
	}

	_loadedSoundIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\sound.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `sound.fe3d` missing!");
		return false;
	}

	ifstream file(filePath);

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

	file.close();

	Logger::throwInfo("Sound data loaded!");

	return true;
}