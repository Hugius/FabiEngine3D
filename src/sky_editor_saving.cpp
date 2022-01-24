#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool SkyEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectId.empty())
	{
		Logger::throwError("SkyEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectId + "\\data\\sky.fe3d");

	for(const auto& skyId : _loadedSkyIds)
	{
		auto cubeMapPaths = _fe3d->sky_getCubeMapPaths(skyId);
		auto rotation = _fe3d->sky_getRotation(skyId);
		auto lightness = _fe3d->sky_getLightness(skyId);
		auto color = _fe3d->sky_getColor(skyId);

		for(auto& cubeMapPath : cubeMapPaths)
		{
			cubeMapPath = string(cubeMapPath.empty() ? "" : cubeMapPath.substr(string("projects\\" + _currentProjectId + "\\").size()));

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

	Logger::throwInfo("Sky editor data saved!");

	return true;
}