#include "world_editor.hpp"

#include <fstream>
#include <sstream>

void WorldEditor::loadWaterEntity()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string waterPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\water.fe3d";

	// Load water file
	if (_fe3d.misc_isFileExisting(waterPath))
	{
		// Open file
		std::ifstream waterFile(waterPath);

		// Load base data
		waterFile >>
			_waterDudvmapPath >> _waterNormalmapPath >>
			_waterWavingEnabled >> _waterRipplingEnabled >> _waterSpecularEnabled >> _waterReflectionEnabled >>
			_waterRefractionEnabled >> _waterColor.r >> _waterColor.g >> _waterColor.b >> _waterSize >>
			_waterUvRepeat >> _waterHeight >> _waterSpeed >> _waterTransparency >> _waterShininess;

		// Perform checks
		_waterDudvmapPath = (_waterDudvmapPath == "-" ? "" : _waterDudvmapPath);
		_waterNormalmapPath = (_waterNormalmapPath == "-" ? "" : _waterNormalmapPath);

		// Close file
		waterFile.close();

		// Load entity
		_loadWaterEntity();
		_fe3d.waterEntity_hide("@water");
	}

	// Logging
	_fe3d.logger_throwInfo("Water data from project \"" + _currentProjectName + "\" loaded!");
}

void WorldEditor::_saveWaterData()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		string waterPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\water.fe3d";

		// Save water dat
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			// Load file
			std::ofstream waterFile(waterPath);

			// Write data to file
			waterFile <<
				(_waterDudvmapPath == "" ? "-" : _waterDudvmapPath) << " " << (_waterNormalmapPath == "" ? "-" : _waterNormalmapPath) << " " <<
				_waterWavingEnabled << " " << _waterRipplingEnabled << " " << _waterSpecularEnabled << " " << _waterReflectionEnabled << " " <<
				_waterRefractionEnabled << " " << _waterColor.r << " " << _waterColor.g << " " << _waterColor.b << " " << _waterSize << " " <<
				_waterUvRepeat << " " << _waterHeight << " " << _waterSpeed << " " << _waterTransparency << " " << _waterShininess;

			// Close file
			waterFile.close();
		}
		else
		{
			// Remove file if non-existent
			if (_fe3d.misc_isFileExisting(waterPath))
			{
				std::remove(waterPath.c_str());
			}
		}

		// Logging
		_fe3d.logger_throwInfo("Water data from project \"" + _currentProjectName + "\" saved!");
	}
}

void WorldEditor::_unloadWaterData()
{
	// Delete water
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_delete("@water");
	}

	// Clear variables
	_waterDudvmapPath = "";
	_waterNormalmapPath = "";
	_waterWavingEnabled = false;
	_waterRipplingEnabled = false;
	_waterSpecularEnabled = false;
	_waterReflectionEnabled = false;
	_waterRefractionEnabled = false;
	_waterColor = vec3(0.0f);
	_waterSize = 0.0f;
	_waterUvRepeat = 0.0f;
	_waterHeight = 0.0f;
	_waterSpeed = 0.0f;
	_waterTransparency = 0.0f;
	_waterShininess = 16.0f;
	_waterCameraHeight = 0.0f;
	_waterCameraDistance = 0.0f;
}

void WorldEditor::_loadWaterEntity()
{
	// Remove existing terrain
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_delete("@water");
	}

	// Add new terrain
	_fe3d.waterEntity_add("@water", vec3(0.0f, _waterHeight, 0.0f), _waterSize);
	_fe3d.waterEntity_select("@water");
	_fe3d.waterEntity_setReflective("@water", _waterReflectionEnabled);
	_fe3d.waterEntity_setRefractive("@water", _waterRefractionEnabled);
	_fe3d.waterEntity_setWaving("@water", _waterWavingEnabled);
	_fe3d.waterEntity_setRippling("@water", _waterDudvmapPath, _waterRipplingEnabled);
	_fe3d.waterEntity_setSpecular("@water", _waterNormalmapPath, _waterShininess, _waterSpecularEnabled);
	_fe3d.waterEntity_setTransparency("@water", _waterTransparency);
	_fe3d.waterEntity_setColor("@water", _waterColor);
	_fe3d.waterEntity_setSurfaceHeight("@water", _waterHeight);
	_fe3d.waterEntity_setUvRepeat("@water", _waterUvRepeat);
	_fe3d.waterEntity_setSpeed("@water", _waterSpeed);
}