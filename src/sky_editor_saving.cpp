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

	if(_currentProjectID.empty())
	{
		Logger::throwError("SkyEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\sky.fe3d");

	for(const auto& skyID : _loadedSkyIDs)
	{
		auto cubeMapPaths = _fe3d->sky_getCubeMapPaths(skyID);
		auto rotation = _fe3d->sky_getRotation(skyID);
		auto lightness = _fe3d->sky_getLightness(skyID);
		auto color = _fe3d->sky_getColor(skyID);

		for(auto& cubeMapPath : cubeMapPaths)
		{
			cubeMapPath = string(cubeMapPath.empty() ? "" : cubeMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

			cubeMapPath = (cubeMapPath.empty()) ? "?" : cubeMapPath;

			replace(cubeMapPath.begin(), cubeMapPath.end(), ' ', '?');
		}

		file << skyID << " ";

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