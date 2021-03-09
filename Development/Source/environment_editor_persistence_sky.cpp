#include "environment_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

const vector<array<string, 6>> EnvironmentEditor::getAllSkyTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> EnvironmentEditor::getAllSkyTexturePathsFromFile()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

	// Check if sky file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;
		vector<array<string, 6>> texturePaths;

		// Read sky data
		while (std::getline(file, line))
		{
			// Temporary values
			string skyID;
			array<string, 6> diffuseMapPaths = {};
			stringstream iss(line);

			// Load base data
			iss >>
				skyID >>
				diffuseMapPaths[0] >>
				diffuseMapPaths[1] >>
				diffuseMapPaths[2] >>
				diffuseMapPaths[3] >>
				diffuseMapPaths[4] >>
				diffuseMapPaths[5];

			// Perform empty string & space conversions
			for (auto& diffuseMapPath : diffuseMapPaths)
			{
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			}

			// Save file paths
			texturePaths.push_back(diffuseMapPaths);
		}

		// Close file
		file.close();

		// Return
		return texturePaths;
	}
	else
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: sky.fe3d missing!");
	}

	return {};
}

void EnvironmentEditor::loadSkyEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> EnvironmentEditor::loadSkyEntitiesFromFile()");
	}

	// Clear names list from previous loads
	_loadedSkyIDs.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

	// Check if sky file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;
		 
		// Read sky data
		while (std::getline(file, line))
		{
			stringstream iss(line);

			// Values
			string skyID;
			std::array<string, 6> diffuseMapPaths{};
			float rotationSpeed, lightness;
			Vec3 color;

			// Load base data
			iss >>
				skyID >>
				diffuseMapPaths[0] >>
				diffuseMapPaths[1] >>
				diffuseMapPaths[2] >>
				diffuseMapPaths[3] >>
				diffuseMapPaths[4] >>
				diffuseMapPaths[5] >>
				rotationSpeed >>
				lightness >>
				color.r >>
				color.g >>
				color.b;

			// Perform empty string & space conversions
			for (auto& diffuseMapPath : diffuseMapPaths)
			{
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			}

			// Load entity
			_loadedSkyIDs.push_back(skyID);
			_fe3d.skyEntity_add(skyID);
			_fe3d.skyEntity_setDiffuseMaps(skyID, diffuseMapPaths);
			_fe3d.skyEntity_setLightness(skyID, lightness);
			_fe3d.skyEntity_setRotationSpeed(skyID, rotationSpeed);
			_fe3d.skyEntity_setColor(skyID, color);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Sky data from project \"" + _currentProjectID + "\" loaded!");
	}
	else
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: sky.fe3d missing!");
	}
}

void EnvironmentEditor::unloadSkyEntities()
{
	for (auto& name : _loadedSkyIDs)
	{
		_fe3d.skyEntity_delete(name);
	}
}

void EnvironmentEditor::saveSkyEntitiesToFile()
{
	if (_isEditorLoaded)
	{
		// Error checking
		if (_currentProjectID == "")
		{
			_fe3d.logger_throwError("No current project loaded --> EnvironmentEditor::saveSkyEntitiesToFile()");
		}

		string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\sky.fe3d";

		// Load file
		std::ofstream file(filePath);

		// Write every sky to file
		for (auto& skyID : _loadedSkyIDs)
		{
			// Values
			auto diffuseMapPaths = _fe3d.skyEntity_getDiffuseMapPaths(skyID);
			float rotationSpeed = _fe3d.skyEntity_getRotationSpeed(skyID);
			float lightness = _fe3d.skyEntity_getLightness(skyID);
			Vec3 color = _fe3d.skyEntity_getColor(skyID);

			// Perform empty string & space conversions
			for (auto& diffuseMapPath : diffuseMapPaths)
			{
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			}

			// Write name to file
			file << skyID << " ";

			// Write paths to file
			for (auto& diffuseMapPath : diffuseMapPaths)
			{
				file << diffuseMapPath << " ";
			}

			// Write options to file
			file <<
				rotationSpeed << " " <<
				lightness << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Sky data from project \"" + _currentProjectID + "\" saved!");
	}
}

const vector<string>& EnvironmentEditor::getLoadedSkyIDs()
{
	std::sort(_loadedSkyIDs.begin(), _loadedSkyIDs.end());
	return _loadedSkyIDs;
}