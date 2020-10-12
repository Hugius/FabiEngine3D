#include "world_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void WorldEditor::loadWaterEntity()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\water.fe3d";

	// Load water file
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Open file
		std::ifstream waterFile(filePath);

		// Values
		string dudvMapPath, normalMapPath, displacementMapPath;
		bool isWaving, isRippling, isSpecularLighted, isReflective, isRefractive;
		vec2 speed;
		vec3 color, position;
		float size, uvRepeat, waveHeightFactor, transparency, specularFactor, specularIntensity;

		// Load base data
		waterFile >>
			dudvMapPath >>
			normalMapPath >>
			displacementMapPath >>
			isWaving >>
			isRippling >>
			isSpecularLighted >>
			isReflective >>
			isRefractive >>
			color.r >>
			color.g >>
			color.b >>
			size >>
			position.x >>
			position.y >>
			position.z >>
			uvRepeat >>
			waveHeightFactor >>
			speed.x >>
			speed.y >>
			transparency >>
			specularFactor >>
			specularIntensity;
		
		// Perform empty string & space conversions
		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);
		std::replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		std::replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

		// Close file
		waterFile.close();

		// Load entity
		_loadWaterEntity();
		_fe3d.waterEntity_setPosition(_currentWaterID, position);
		_fe3d.waterEntity_setSize(_currentWaterID, size);
		_fe3d.waterEntity_setWaving(_currentWaterID, isWaving);
		_fe3d.waterEntity_setRippling(_currentWaterID, isRippling);
		_fe3d.waterEntity_setSpecularLighted(_currentWaterID, isSpecularLighted);
		_fe3d.waterEntity_setReflective(_currentWaterID, isReflective);
		_fe3d.waterEntity_setRefractive(_currentWaterID, isRefractive);
		_fe3d.waterEntity_setWaveHeightFactor(_currentWaterID, waveHeightFactor);
		_fe3d.waterEntity_setSpecularLightingFactor(_currentWaterID, specularFactor);
		_fe3d.waterEntity_setSpecularLightingIntensity(_currentWaterID, specularIntensity);
		_fe3d.waterEntity_setTransparency(_currentWaterID, transparency);
		_fe3d.waterEntity_setColor(_currentWaterID, color);
		_fe3d.waterEntity_setUvRepeat(_currentWaterID, uvRepeat);
		_fe3d.waterEntity_setSpeed(_currentWaterID, speed);
		if (dudvMapPath != "") _fe3d.waterEntity_setDudvMap(_currentWaterID, dudvMapPath);
		if (normalMapPath != "") _fe3d.waterEntity_setNormalMap(_currentWaterID, normalMapPath);
		if (displacementMapPath != "") _fe3d.waterEntity_setDisplacementMap(_currentWaterID, displacementMapPath);

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

		string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\water.fe3d";

		// Save water dat
		if (_fe3d.waterEntity_isExisting(_currentWaterID))
		{
			// Load file
			std::ofstream waterFile(filePath);

			// Values
			string dudvMapPath = _fe3d.waterEntity_getDudvMapPath(_currentWaterID);
			string normalMapPath = _fe3d.waterEntity_getNormalMapPath(_currentWaterID);
			string displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(_currentWaterID);
			bool isWaving = _fe3d.waterEntity_isWaving(_currentWaterID);
			bool isRippling = _fe3d.waterEntity_isRippling(_currentWaterID);
			bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(_currentWaterID);
			bool isReflective = _fe3d.waterEntity_isReflective(_currentWaterID);
			bool isRefractive = _fe3d.waterEntity_isRefractive(_currentWaterID);
			vec3 color = _fe3d.waterEntity_getColor(_currentWaterID);
			float size = _fe3d.waterEntity_getSize(_currentWaterID);
			vec3 position = _fe3d.waterEntity_getPosition(_currentWaterID);
			float uvRepeat = _fe3d.waterEntity_getUvRepeat(_currentWaterID);
			float waveHeightFactor = _fe3d.waterEntity_getWaveHeightFactor(_currentWaterID);
			vec2 speed = _fe3d.waterEntity_getSpeed(_currentWaterID);
			float transparency = _fe3d.waterEntity_getTransparency(_currentWaterID);
			float specularFactor = _fe3d.waterEntity_getSpecularLightingFactor(_currentWaterID);
			float specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity(_currentWaterID);

			// Perform empty string & space conversions
			dudvMapPath = (dudvMapPath == "" ? "?" : dudvMapPath);
			normalMapPath = (normalMapPath == "" ? "?" : normalMapPath);
			displacementMapPath = (displacementMapPath == "" ? "?" : displacementMapPath);
			std::replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
			std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
			std::replace(displacementMapPath.begin(), displacementMapPath.end(), ' ', '?');

			// Write data to file
			waterFile <<
				dudvMapPath << " " << 
				normalMapPath << " " << 
				displacementMapPath << " " <<
				isWaving << " " << 
				isRippling << " " << 
				isSpecularLighted << " " << 
				isReflective << " " << 
				isRefractive << " " << 
				color.r << " " << 
				color.g << " " << 
				color.b << " " << 
				size << " " << 
				position.x << " " << 
				position.y << " " <<
				position.z << " " <<
				uvRepeat << " " << 
				waveHeightFactor << " " <<
				speed.x << " " << 
				speed.y << " " <<
				transparency << " " <<
				specularFactor << " " <<
				specularIntensity << std::endl;

			// Close file
			waterFile.close();
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
		_fe3d.logger_throwInfo("Water data from project \"" + _currentProjectName + "\" saved!");
	}
}

void WorldEditor::_loadWaterEntity()
{
	_fe3d.waterEntity_add(_currentWaterID);
	_fe3d.waterEntity_select(_currentWaterID);
	_fe3d.waterEntity_hide(_currentWaterID);
}