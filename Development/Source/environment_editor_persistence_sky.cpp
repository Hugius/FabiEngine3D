#include "environment_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void EnvironmentEditor::loadSkyEntitiesFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded!");
	}

	// Clear names list from previous loads
	_skyIDs.clear();

	// Compose full folder path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\sky.fe3d";

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
			_skyIDs.push_back(skyID);
			_fe3d.skyEntity_add(skyID);
			_fe3d.skyEntity_setDiffuseMaps(skyID, diffuseMapPaths);
			_fe3d.skyEntity_setLightness(skyID, lightness);
			_fe3d.skyEntity_setRotationSpeed(skyID, rotationSpeed);
			_fe3d.skyEntity_setColor(skyID, color);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Sky data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void EnvironmentEditor::unloadSkyEntities()
{
	for (auto& name : _skyIDs)
	{
		_fe3d.skyEntity_delete(name);
	}
}

void EnvironmentEditor::saveSkyEntitiesToFile()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\sky.fe3d";

		// Load file
		std::ofstream file(filePath);

		// Write every sky to file
		for (auto& skyID : _skyIDs)
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
		_fe3d.logger_throwInfo("Sky data from project \"" + _currentProjectName + "\" saved!");
	}
}