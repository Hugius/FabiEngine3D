#include "sound2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> Sound2dEditor::getAudioPathsFromFile() const
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\sound2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sound2d.fe3d` does not exist");

		return {};
	}

	vector<string> audioPaths = {};
	string line;
	while(getline(file, line))
	{
		string sound2dId;
		string audioPath;

		auto iss = istringstream(line);

		iss
			>> sound2dId
			>> audioPath;

		audioPath = (audioPath == "?") ? "" : audioPath;

		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		if(!Configuration::getInst().isApplicationExported())
		{
			audioPath = ("projects\\" + getCurrentProjectId() + "\\" + audioPath);
		}

		audioPaths.push_back(audioPath);
	}

	file.close();

	return audioPaths;
}

const bool Sound2dEditor::loadSound2dsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	_loadedSound2dIds.clear();

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\sound2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sound2d.fe3d` does not exist");

		return false;
	}

	string line;
	while(getline(file, line))
	{
		string sound2dId, audioPath;

		auto iss = istringstream(line);

		iss
			>> sound2dId
			>> audioPath;

		audioPath = (audioPath == "?") ? "" : audioPath;

		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		if(!Configuration::getInst().isApplicationExported())
		{
			audioPath = ("projects\\" + getCurrentProjectId() + "\\" + audioPath);
		}

		_fe3d->sound2d_create(sound2dId, audioPath);

		if(_fe3d->sound2d_isExisting(sound2dId))
		{
			_loadedSound2dIds.push_back(sound2dId);
		}
	}

	file.close();

	Logger::throwInfo("Sound2D editor data loaded");

	return true;
}