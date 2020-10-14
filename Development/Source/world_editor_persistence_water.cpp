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

	// Clear names list from previous loads
	_waterNames.clear();

	// Compose full folder path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\water.fe3d";

	// Load water file
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read sky data
		while (std::getline(file, line))
		{
			stringstream iss(line);

			// Values
			string name, dudvMapPath, normalMapPath, displacementMapPath;
			bool isWaving, isRippling, isSpecularLighted, isReflective, isRefractive;
			vec2 speed;
			vec3 color, position;
			float size, uvRepeat, waveHeightFactor, transparency, specularFactor, specularIntensity;

			// Load base data
			iss >>
				name >>
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

			// Load entity
			_waterNames.push_back(name);
			_fe3d.waterEntity_add(name);
			_fe3d.waterEntity_hide(name);
			_fe3d.waterEntity_setPosition(name, position);
			_fe3d.waterEntity_setSize(name, size);
			_fe3d.waterEntity_setWaving(name, isWaving);
			_fe3d.waterEntity_setRippling(name, isRippling);
			_fe3d.waterEntity_setSpecularLighted(name, isSpecularLighted);
			_fe3d.waterEntity_setReflective(name, isReflective);
			_fe3d.waterEntity_setRefractive(name, isRefractive);
			_fe3d.waterEntity_setWaveHeightFactor(name, waveHeightFactor);
			_fe3d.waterEntity_setSpecularLightingFactor(name, specularFactor);
			_fe3d.waterEntity_setSpecularLightingIntensity(name, specularIntensity);
			_fe3d.waterEntity_setTransparency(name, transparency);
			_fe3d.waterEntity_setColor(name, color);
			_fe3d.waterEntity_setUvRepeat(name, uvRepeat);
			_fe3d.waterEntity_setSpeed(name, speed);
			if (dudvMapPath != "") _fe3d.waterEntity_setDudvMap(name, dudvMapPath);
			if (normalMapPath != "") _fe3d.waterEntity_setNormalMap(name, normalMapPath);
			if (displacementMapPath != "") _fe3d.waterEntity_setDisplacementMap(name, displacementMapPath);
		}

		// Close file
		file.close();

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

		// Compose full folder path
		string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\water.fe3d";

		// Load file
		std::ofstream file(filePath);

		// Write every water to file
		for (auto& name : _waterNames)
		{
			// Values
			string dudvMapPath = _fe3d.waterEntity_getDudvMapPath(name);
			string normalMapPath = _fe3d.waterEntity_getNormalMapPath(name);
			string displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(name);
			bool isWaving = _fe3d.waterEntity_isWaving(name);
			bool isRippling = _fe3d.waterEntity_isRippling(name);
			bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(name);
			bool isReflective = _fe3d.waterEntity_isReflective(name);
			bool isRefractive = _fe3d.waterEntity_isRefractive(name);
			vec3 color = _fe3d.waterEntity_getColor(name);
			float size = _fe3d.waterEntity_getSize(name);
			vec3 position = _fe3d.waterEntity_getPosition(name);
			float uvRepeat = _fe3d.waterEntity_getUvRepeat(name);
			float waveHeightFactor = _fe3d.waterEntity_getWaveHeightFactor(name);
			vec2 speed = _fe3d.waterEntity_getSpeed(name);
			float transparency = _fe3d.waterEntity_getTransparency(name);
			float specularFactor = _fe3d.waterEntity_getSpecularLightingFactor(name);
			float specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity(name);

			// Perform empty string & space conversions
			dudvMapPath = (dudvMapPath == "" ? "?" : dudvMapPath);
			normalMapPath = (normalMapPath == "" ? "?" : normalMapPath);
			displacementMapPath = (displacementMapPath == "" ? "?" : displacementMapPath);
			std::replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
			std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
			std::replace(displacementMapPath.begin(), displacementMapPath.end(), ' ', '?');

			// Write data to file
			file <<
				name << " " <<
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
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Water data from project \"" + _currentProjectName + "\" saved!");
	}
}