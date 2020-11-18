#include "environment_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void EnvironmentEditor::loadSkyEntities()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded!");
	}

	// Clear names list from previous loads
	_skyNames.clear();

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
			string name;
			std::array<string, 6> diffuseMapPaths{};
			float rotationSpeed, lightness;
			vec3 color;

			// Load base data
			iss >>
				name >>
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
			_skyNames.push_back(name);
			_fe3d.skyEntity_add(name);
			_fe3d.skyEntity_setDiffuseMaps(name, diffuseMapPaths);
			_fe3d.skyEntity_setLightness(name, lightness);
			_fe3d.skyEntity_setRotationSpeed(name, rotationSpeed);
			_fe3d.skyEntity_setColor(name, color);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Sky data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void EnvironmentEditor::_saveSkyData()
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
		for (auto& name : _skyNames)
		{
			// Values
			auto diffuseMapPaths = _fe3d.skyEntity_getDiffuseMapPaths(name);
			float rotationSpeed = _fe3d.skyEntity_getRotationSpeed(name);
			float lightness = _fe3d.skyEntity_getLightness(name);
			vec3 color = _fe3d.skyEntity_getColor(name);

			// Perform empty string & space conversions
			for (auto& diffuseMapPath : diffuseMapPaths)
			{
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			}

			// Write name to file
			file << name << " ";

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