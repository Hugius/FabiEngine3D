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
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\sound.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sound.fe3d` missing!");
		return {};
	}

	vector<string> audioPaths;
	string line;
	while(getline(file, line))
	{
		string soundID;
		string audioPath;

		istringstream iss(line);

		iss >> soundID >> audioPath;

		audioPath = (audioPath == "?") ? "" : audioPath;

		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		if(!Config::getInst().isApplicationExported())
		{
			audioPath = string("projects\\" + _currentProjectID + "\\" + audioPath);
		}

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
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\sound.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sound.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string soundID, audioPath;

		istringstream iss(line);

		iss >> soundID >> audioPath;

		audioPath = (audioPath == "?") ? "" : audioPath;

		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		if(!Config::getInst().isApplicationExported())
		{
			audioPath = string("projects\\" + _currentProjectID + "\\" + audioPath);
		}

		_fe3d->sound2d_create(soundID, audioPath);

		if(_fe3d->sound2d_isExisting(soundID))
		{
			_loadedSoundIDs.push_back(soundID);
		}
	}

	file.close();

	Logger::throwInfo("Sound editor data loaded!");

	return true;
}