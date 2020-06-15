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

	string skyPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\sky.fe3d";

	_skyTexturePaths.clear();
	_skyTexturePaths.resize(6);

	// Load sky file
	if (_fe3d.misc_isFileExisting(skyPath))
	{
		// Open file
		std::ifstream skyFile(skyPath);

		// Load base data
		skyFile >>
			_skyTexturePaths[0] >> _skyTexturePaths[1] >> _skyTexturePaths[2] >> _skyTexturePaths[3] >> _skyTexturePaths[4] >> _skyTexturePaths[5] >>
			_skyRotationSpeed;

		// Close file
		skyFile.close();

		// Load entity
		_loadSkyEntity();
		_fe3d.skyEntity_hide("@sky");
	}

	// Logging
	_fe3d.logger_throwInfo("Sky data from project \"" + _currentProjectName + "\" loaded!");
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

		string skyPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\sky.fe3d";

		// Save sky data
		if (_fe3d.skyEntity_isExisting("@sky"))
		{
			// Load file
			std::ofstream skyFile(skyPath);

			// Add path to file
			for (auto& path : _skyTexturePaths)
			{
				skyFile << path << " ";
			}

			// Add options to file
			skyFile << _skyRotationSpeed;

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
	_skyRotationSpeed = 0.0f;
}

void WorldEditor::_loadSkyEntity()
{
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Add new skybox
	_fe3d.skyEntity_add("@sky", _skyTexturePaths);
	_fe3d.skyEntity_select("@sky");
}