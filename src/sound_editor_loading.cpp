#include "sound_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> SoundEditor::getAudioPathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\sound.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sound.fe3d` missing");
		return {};
	}

	vector<string> audioPaths;
	string line;
	while(getline(file, line))
	{
		string soundId;
		string audioPath;

		istringstream iss(line);

		iss
			>> soundId
			>> audioPath;

		audioPath = (audioPath == "?") ? "" : audioPath;

		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		if(!Config::getInst().isApplicationExported())
		{
			audioPath = string("projects\\" + getCurrentProjectId() + "\\" + audioPath);
		}

		audioPaths.push_back(audioPath);
	}

	file.close();

	return audioPaths;
}

const bool SoundEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	_loadedSoundIds.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\sound.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sound.fe3d` missing");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string soundId, audioPath;

		istringstream iss(line);

		iss
			>> soundId
			>> audioPath;

		audioPath = (audioPath == "?") ? "" : audioPath;

		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		if(!Config::getInst().isApplicationExported())
		{
			audioPath = string("projects\\" + getCurrentProjectId() + "\\" + audioPath);
		}

		_fe3d->sound2d_create(soundId, audioPath);

		if(_fe3d->sound2d_isExisting(soundId))
		{
			_loadedSoundIds.push_back(soundId);
		}
	}

	file.close();

	Logger::throwInfo("Sound editor data loaded");

	return true;
}