#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool SkyEditor::saveToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		abort();
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\sky.fe3d");

	for(const auto& skyId : _loadedEntityIds)
	{
		auto cubeMapPaths = _fe3d->sky_getCubeMapPaths(skyId);
		auto rotation = _fe3d->sky_getRotation(skyId);
		auto lightness = _fe3d->sky_getLightness(skyId);
		auto color = _fe3d->sky_getColor(skyId);

		for(auto& cubeMapPath : cubeMapPaths)
		{
			cubeMapPath = (cubeMapPath.empty() ? "" : cubeMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));

			cubeMapPath = (cubeMapPath.empty()) ? "?" : cubeMapPath;

			replace(cubeMapPath.begin(), cubeMapPath.end(), ' ', '?');
		}

		file << skyId << " ";

		for(const auto& cubeMapPath : cubeMapPaths)
		{
			file << cubeMapPath << " ";
		}

		file <<
			rotation << " " <<
			lightness << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << endl;
	}

	file.close();

	Logger::throwInfo("Sky editor data saved");

	return true;
}