#include "world_editor.hpp"

#include <fstream>
#include <sstream>

void WorldEditor::loadTerrainEntity()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string terrainPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\terrain.fe3d";

	// Load terrain file
	if (_fe3d.misc_isFileExisting(terrainPath))
	{
		// Load file
		std::ifstream terrainFile(terrainPath);

		// Load base data
		terrainFile >> _terrainHeightmapPath >> _terrainDiffusemapPath >> _terrainSize >> _maxTerrainHeight >> _terrainUvRepeat >> _isTerrainBlendmapped >> _terrainLightness;

		// Load blendmapping data
		if (_isTerrainBlendmapped)
		{
			terrainFile >>
				_terrainBlendmapPath >> _terrainRedPath >> _terrainGreenPath >> _terrainBluePath >>
				_terrainRedUvRepeat >> _terrainGreenUvRepeat >> _terrainBlueUvRepeat;
		}

		// Close file
		terrainFile.close();

		// Load entity
		_loadTerrainEntity();
		_fe3d.terrainEntity_hide("@terrain");

		// Logging
		_fe3d.logger_throwInfo("Terrain data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void WorldEditor::_saveTerrainData()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		string terrainPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\terrain.fe3d";

		// Save terrain data
		if (_fe3d.terrainEntity_isExisting("@terrain"))
		{
			// Load file
			std::ofstream terrainFile(terrainPath);

			// Write base data to file
			terrainFile << _terrainHeightmapPath << " " << _terrainDiffusemapPath << " " << _terrainSize << " " << _maxTerrainHeight << " " << _terrainUvRepeat << " " << _isTerrainBlendmapped << " " << _terrainLightness;

			// Write blendmapping data to file
			if (_isTerrainBlendmapped)
			{
				terrainFile << _terrainBlendmapPath << " " << _terrainRedPath << " " << _terrainGreenPath << " " << _terrainBluePath << " " <<
					_terrainRedUvRepeat << " " << _terrainGreenUvRepeat << " " << _terrainBlueUvRepeat;
			}

			// Close file
			terrainFile.close();
		}
		else
		{
			// Remove file if non-existent
			if (_fe3d.misc_isFileExisting(terrainPath))
			{
				std::remove(terrainPath.c_str());
			}
		}

		// Logging
		_fe3d.logger_throwInfo("Terrain data from project \"" + _currentProjectName + "\" saved!");
	}
}

void WorldEditor::_unloadTerrainData()
{
	// Delete terrain
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_delete("@terrain");
	}

	// Clear variables
	_isTerrainBlendmapped = false;
	_terrainHeightmapPath = "";
	_terrainDiffusemapPath = "";
	_terrainBlendmapPath = "";
	_terrainRedPath = "";
	_terrainGreenPath = "";
	_terrainBluePath = "";
	_terrainSize = 0.0f;
	_maxTerrainHeight = 0.0f;
	_terrainUvRepeat = 0.0f;
	_terrainRedUvRepeat = 0.0f;
	_terrainGreenUvRepeat = 0.0f;
	_terrainBlueUvRepeat = 0.0f;
	_terrainCameraHeight = 0.0f;
	_terrainCameraDistance = 0.0f;
}

void WorldEditor::_loadTerrainEntity()
{
	// Remove existing terrain
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_delete("@terrain");
	}

	// Add new terrain
	_fe3d.terrainEntity_add("@terrain", _terrainHeightmapPath, _terrainDiffusemapPath, vec3(0.0f), _terrainSize, _maxTerrainHeight, _terrainUvRepeat, _terrainLightness);
	_fe3d.terrainEntity_select("@terrain");

	// Get possibly corrected size
	_terrainSize = _fe3d.terrainEntity_getSize("@terrain");

	// Camera
	_terrainCameraHeight = _maxTerrainHeight * 1.25f;
	_terrainCameraDistance = _terrainSize / 2.0f;

	// Blendmapping
	if (_isTerrainBlendmapped)
	{
		_fe3d.terrainEntity_addBlending("@terrain", _terrainBlendmapPath, _terrainRedPath, _terrainGreenPath, _terrainBluePath, _terrainRedUvRepeat, _terrainGreenUvRepeat, _terrainBlueUvRepeat);
	}
}