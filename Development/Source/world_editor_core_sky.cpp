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
		_loadSkyEntity();
		_fe3d.skyEntity_setDiffuseMaps("@sky", diffuseMapPaths);
		_fe3d.skyEntity_setLightness("@sky", lightness);
		_fe3d.skyEntity_setRotationSpeed("@sky", rotationSpeed);
		_fe3d.skyEntity_setColor("@sky", color);

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
		if (_fe3d.skyEntity_isExisting("@sky"))
		{
			// Load file
			std::ofstream skyFile(filePath);

			// Values
			auto diffuseMapPaths = _fe3d.skyEntity_getDiffuseMapPaths("@sky");
			float rotationSpeed = _fe3d.skyEntity_getRotationSpeed("@sky");
			float lightness = _fe3d.skyEntity_getLightness("@sky");
			vec3 color = _fe3d.skyEntity_getColor("@sky");

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

void WorldEditor::_loadSkyEntity()
{
	_fe3d.skyEntity_add("@sky");
	_fe3d.skyEntity_select("@sky");
	_fe3d.skyEntity_hide("@sky");
}