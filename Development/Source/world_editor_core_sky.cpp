#include "world_editor.hpp"

#include <fstream>
#include <sstream>

void WorldEditor::loadSkyEntity()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string skyPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\sky.fe3d";

	// Reserve for either loading or creation later on
	_skyTexturePaths.clear();
	_skyTexturePaths.resize(6);

	// Load sky file
	if (_fe3d.misc_isFileExisting(skyPath))
	{
		// Open file
		std::ifstream skyFile(skyPath);

		// Get values
		float skyRotationSpeed, skyLightness;
		vec3 skyColor;

		// Load base data
		skyFile >>
			_skyTexturePaths[0] >> 
			_skyTexturePaths[1] >> 
			_skyTexturePaths[2] >> 
			_skyTexturePaths[3] >> 
			_skyTexturePaths[4] >> 
			_skyTexturePaths[5] >>
			skyRotationSpeed >> 
			skyLightness >> 
			skyColor.r >> 
			skyColor.g >> 
			skyColor.b;

		// Close file
		skyFile.close();

		// Load entity
		_loadSkyEntity();
		_fe3d.skyEntity_hide("@sky");
		_fe3d.skyEntity_setRotationSpeed("@sky", skyRotationSpeed);
		_fe3d.skyEntity_setLightness("@sky", skyLightness);
		_fe3d.skyEntity_setColor("@sky", skyColor);

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

		string skyPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\sky.fe3d";

		// Save sky data
		if (_fe3d.skyEntity_isExisting("@sky"))
		{
			// Load file
			std::ofstream skyFile(skyPath);

			float skyRotationSpeed = _fe3d.skyEntity_getRotationSpeed("@sky");
			float skyLightness = _fe3d.skyEntity_getLightness("@sky");
			vec3 skyColor = _fe3d.skyEntity_getColor("@sky");

			// Write paths to file
			for (auto& path : _skyTexturePaths)
			{
				skyFile << path << " ";
			}

			// Write options to file
			skyFile << 
				skyRotationSpeed << " " <<
				skyLightness << " " <<
				skyColor.r << " " <<
				skyColor.g << " " <<
				skyColor.b << std::endl;

			// Close file
			skyFile.close();
		}
		else
		{
			// Remove file if non-existent
			if (_fe3d.misc_isFileExisting(skyPath))
			{
				std::remove(skyPath.c_str());
			}
		}

		// Logging
		_fe3d.logger_throwInfo("Sky data from project \"" + _currentProjectName + "\" saved!");
	}
}

void WorldEditor::_unloadSkyData()
{
	// Delete sky
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Clear variables
	_skyTexturePaths.clear();
	_skyTexturePaths.resize(6);
}

void WorldEditor::_loadSkyEntity()
{
	// Delete existing entity
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Add new skybox
	_fe3d.skyEntity_add("@sky", _skyTexturePaths);
	_fe3d.skyEntity_select("@sky");
}