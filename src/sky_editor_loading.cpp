#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> SkyEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\sky.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sky.fe3d` missing!");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string skyId;
		array<string, 6> cubeMapPaths{};

		istringstream iss(line);

		iss
			>> skyId
			>> cubeMapPaths[0]
			>> cubeMapPaths[1]
			>> cubeMapPaths[2]
			>> cubeMapPaths[3]
			>> cubeMapPaths[4]
			>> cubeMapPaths[5];

		for(auto& cubeMapPath : cubeMapPaths)
		{
			cubeMapPath = (cubeMapPath == "?") ? "" : cubeMapPath;

			replace(cubeMapPath.begin(), cubeMapPath.end(), '?', ' ');

			if(!cubeMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					cubeMapPath = string("projects\\" + getCurrentProjectId() + "\\" + cubeMapPath);
				}

				imagePaths.push_back(cubeMapPath);
			}
		}
	}

	file.close();

	return imagePaths;
}

const bool SkyEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	_loadedSkyIds.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\sky.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `sky.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string skyId;
		array<string, 6> cubeMapPaths{};
		fvec3 color;
		float rotation;
		float lightness;

		istringstream iss(line);

		iss
			>> skyId
			>> cubeMapPaths[0]
			>> cubeMapPaths[1]
			>> cubeMapPaths[2]
			>> cubeMapPaths[3]
			>> cubeMapPaths[4]
			>> cubeMapPaths[5]
			>> rotation
			>> lightness
			>> color.r
			>> color.g
			>> color.b;

		for(auto& cubeMapPath : cubeMapPaths)
		{
			cubeMapPath = (cubeMapPath == "?") ? "" : cubeMapPath;

			replace(cubeMapPath.begin(), cubeMapPath.end(), '?', ' ');

			if(!cubeMapPath.empty())
			{
				if(!Config::getInst().isApplicationExported())
				{
					cubeMapPath = string("projects\\" + getCurrentProjectId() + "\\" + cubeMapPath);
				}
			}
		}

		_fe3d->sky_create(skyId);

		if(_fe3d->sky_isExisting(skyId))
		{
			_loadedSkyIds.push_back(skyId);

			_fe3d->sky_setCubeMaps(skyId, cubeMapPaths);
			_fe3d->sky_setLightness(skyId, lightness);
			_fe3d->sky_setRotation(skyId, rotation);
			_fe3d->sky_setColor(skyId, color);
		}
	}

	file.close();

	Logger::throwInfo("Sky editor data loaded!");

	return true;
}