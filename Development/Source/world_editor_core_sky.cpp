#include "world_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void WorldEditor::loadSkyEntity()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\sky.fe3d";

	// Load sky file
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Open file
		std::ifstream skyFile(filePath);

		// Values
		std::array<string, 6> diffuseMapPaths{};
		float rotationSpeed, lightness;
		vec3 color;
		
		// Load base data
		skyFile >>
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

		// Close file
		skyFile.close();

		// Load entity
		_fe3d.skyEntity_add(_currentSkyID);
		_fe3d.skyEntity_select(_currentSkyID);
		_fe3d.skyEntity_hide(_currentSkyID);
		_fe3d.skyEntity_setDiffuseMaps(_currentSkyID, diffuseMapPaths);
		_fe3d.skyEntity_setLightness(_currentSkyID, lightness);
		_fe3d.skyEntity_setRotationSpeed(_currentSkyID, rotationSpeed);
		_fe3d.skyEntity_setColor(_currentSkyID, color);

		// Logging
		_fe3d.logger_throwInfo("Sky data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void WorldEditor::_saveSkyData()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\sky.fe3d";

		// Save sky data
		if (_fe3d.skyEntity_isExisting(_currentSkyID))
		{
			// Load file
			std::ofstream skyFile(filePath);

			// Values
			auto diffuseMapPaths = _fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID);
			float rotationSpeed = _fe3d.skyEntity_getRotationSpeed(_currentSkyID);
			float lightness = _fe3d.skyEntity_getLightness(_currentSkyID);
			vec3 color = _fe3d.skyEntity_getColor(_currentSkyID);

			// Perform empty string & space conversions
			for (auto& diffuseMapPath : diffuseMapPaths)
			{
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			}

			// Write paths to file
			for (auto& diffuseMapPath : diffuseMapPaths)
			{
				skyFile << diffuseMapPath << " ";
			}

			// Write options to file
			skyFile << 
				rotationSpeed << " " <<
				lightness << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << std::endl;

			// Close file
			skyFile.close();
		}
		else
		{
			// Remove file if non-existent
			if (_fe3d.misc_isFileExisting(filePath))
			{
				std::remove(filePath.c_str());
			}
		}

		// Logging
		_fe3d.logger_throwInfo("Sky data from project \"" + _currentProjectName + "\" saved!");
	}
}