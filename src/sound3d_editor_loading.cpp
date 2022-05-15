#include "sound3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> Sound3dEditor::getAudioPathsFromFile() const
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\sound3d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sound3d.fe3d` does not exist");

		return {};
	}

	vector<string> audioPaths = {};
	string line;

	while(getline(file, line))
	{
		string sound3dId;
		string audioPath;

		auto iss = istringstream(line);

		iss
			>> sound3dId
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

const bool Sound3dEditor::loadSound3dsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\sound3d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sound3d.fe3d` does not exist");

		return false;
	}

	string line;

	while(getline(file, line))
	{
		string sound3dId;
		string audioPath;
		float maxVolume;
		float maxDistance;

		auto iss = istringstream(line);

		iss
			>> sound3dId
			>> audioPath
			>> maxVolume
			>> maxDistance;

		audioPath = (audioPath == "?") ? "" : audioPath;

		replace(audioPath.begin(), audioPath.end(), '?', ' ');

		if(!Configuration::getInst().isApplicationExported())
		{
			audioPath = ("projects\\" + getCurrentProjectId() + "\\" + audioPath);
		}

		_fe3d->sound3d_create(sound3dId, audioPath);

		if(_fe3d->sound3d_isExisting(sound3dId))
		{
			_fe3d->sound3d_setPosition(sound3dId, SOUND3D_POSITION);
			_fe3d->sound3d_setMaxVolume(sound3dId, maxVolume);
			_fe3d->sound3d_setMaxDistance(sound3dId, maxDistance);
			_fe3d->sound3d_start(sound3dId, -1);
			_fe3d->sound3d_pause(sound3dId, 0);

			_loadedSound3dIds.push_back(sound3dId);

			sort(_loadedSound3dIds.begin(), _loadedSound3dIds.end());
		}
	}

	file.close();

	Logger::throwInfo("Sound3d editor data loaded");

	return true;
}