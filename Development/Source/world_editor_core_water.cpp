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

	string waterPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\water.fe3d";

	// Load water file
	if (_fe3d.misc_isFileExisting(waterPath))
	{
		// Open file
		std::ifstream waterFile(waterPath);

		// Load base data
		waterFile >>
			_waterDudvMapPath >>
			_waterNormalMapPath >>
			_waterDisplacementMapPath >>
			_waterWavingEnabled >>
			_waterRipplingEnabled >>
			_waterSpecularEnabled >> 
			_waterReflectionEnabled >>
			_waterRefractionEnabled >>
			_waterColor.r >> 
			_waterColor.g >> 
			_waterColor.b >> 
			_waterSize >> 
			_waterPosition.x >> 
			_waterPosition.y >> 
			_waterPosition.z >>
			_waterUvRepeat >>
			_waterWaveHeightFactor >>
			_waterSpeed >> 
			_waterTransparency >>
			_waterSpecularFactor >> 
			_waterSpecularIntensity;
		
		// Perform empty string conversions
		_waterDudvMapPath = (_waterDudvMapPath == "-" ? "" : _waterDudvMapPath);
		_waterNormalMapPath = (_waterNormalMapPath == "-" ? "" : _waterNormalMapPath);
		_waterDisplacementMapPath = (_waterDisplacementMapPath == "-" ? "" : _waterDisplacementMapPath);

		// Close file
		waterFile.close();

		// Load entity
		_loadWaterEntity();
		_fe3d.waterEntity_hide("@water");

		// Logging
		_fe3d.logger_throwInfo("Water data from project \"" + _currentProjectName + "\" loaded!");
	}
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

		string waterPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\water.fe3d";

		// Save water dat
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			// Load file
			std::ofstream waterFile(waterPath);

			// String value conversions
			_waterDudvMapPath = (_waterDudvMapPath == "" ? "-" : _waterDudvMapPath);
			_waterNormalMapPath = (_waterNormalMapPath == "" ? "-" : _waterNormalMapPath);
			_waterDisplacementMapPath = (_waterDisplacementMapPath == "" ? "-" : _waterDisplacementMapPath);

			// Write data to file
			waterFile <<
				_waterDudvMapPath << " " << 
				_waterNormalMapPath << " " << 
				_waterDisplacementMapPath << " " <<
				_waterWavingEnabled << " " << 
				_waterRipplingEnabled << " " << 
				_waterSpecularEnabled << " " << 
				_waterReflectionEnabled << " " << 
				_waterRefractionEnabled << " " << 
				_waterColor.r << " " << 
				_waterColor.g << " " << 
				_waterColor.b << " " << 
				_waterSize << " " << 
				_waterPosition.x << " " << 
				_waterPosition.y << " " <<
				_waterPosition.z << " " <<
				_waterUvRepeat << " " << 
				_waterWaveHeightFactor << " " <<
				_waterSpeed << " " << 
				_waterTransparency << " " <<
				_waterSpecularFactor << " " <<
				_waterSpecularIntensity << std::endl;

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
}

void WorldEditor::_loadWaterEntity()
{
	_fe3d.waterEntity_add("@water");
	_fe3d.waterEntity_select("@water");
	_fe3d.waterEntity_hide("@water");
}