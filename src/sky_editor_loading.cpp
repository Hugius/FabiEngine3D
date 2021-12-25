#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<array<string, 6>> SkyEditor::getTexturePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("SkyEditor::getTexturePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\sky.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `sky.fe3d` missing!");
		return {};
	}

	ifstream file(filePath);

	vector<array<string, 6>> texturePaths;
	string line;
	while(getline(file, line))
	{
		// Values
		string skyID;
		array<string, 6> cubeMapPaths = {};

		// For file extraction
		istringstream iss(line);

		// Load base data
		iss >>
			skyID >>
			cubeMapPaths[0] >>
			cubeMapPaths[1] >>
			cubeMapPaths[2] >>
			cubeMapPaths[3] >>
			cubeMapPaths[4] >>
			cubeMapPaths[5];

		// Iterate through paths
		for(auto& diffuseMapPath : cubeMapPaths)
		{
			// Convert empty string
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;

			// Convert spaces
			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
			}
		}

		// Save paths
		texturePaths.push_back(cubeMapPaths);
	}

	file.close();

	return texturePaths;
}

const bool SkyEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("SkyEditor::loadFromFile");
	}

	_loadedSkyIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\sky.fe3d");

	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `sky.fe3d` missing!");
		return false;
	}

	ifstream file(filePath);

	string line;
	while(getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Values
		string skyID;
		array<string, 6> cubeMapPaths{};
		float rotation, lightness;
		fvec3 color;

		// Load base data
		iss >>
			skyID >>
			cubeMapPaths[0] >>
			cubeMapPaths[1] >>
			cubeMapPaths[2] >>
			cubeMapPaths[3] >>
			cubeMapPaths[4] >>
			cubeMapPaths[5] >>
			rotation >>
			lightness >>
			color.r >>
			color.g >>
			color.b;

		// Iterate through paths
		for(auto& cubeMapPath : cubeMapPaths)
		{
			// Convert empty string
			cubeMapPath = (cubeMapPath == "?") ? "" : cubeMapPath;

			// Convert spaces
			replace(cubeMapPath.begin(), cubeMapPath.end(), '?', ' ');

			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				cubeMapPath = string("projects\\" + _currentProjectID + "\\" + cubeMapPath);
			}
		}

		// Create sky
		_fe3d.sky_create(skyID);

		// Check if sky creation went well
		if(_fe3d.sky_isExisting(skyID))
		{
			// Add sky ID
			_loadedSkyIDs.push_back(skyID);

			// Set properties
			_fe3d.sky_setCubeMaps(skyID, cubeMapPaths);
			_fe3d.sky_setLightness(skyID, lightness);
			_fe3d.sky_setRotation(skyID, rotation);
			_fe3d.sky_setColor(skyID, color);
		}
	}

	file.close();

	Logger::throwInfo("Sky data loaded!");

	return true;
}