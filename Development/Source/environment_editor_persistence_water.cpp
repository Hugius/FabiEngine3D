#include "environment_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void EnvironmentEditor::loadWaterEntitiesFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded!");
	}

	// Clear names list from previous loads
	_waterIDs.clear();

	// Compose full file path
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
			string waterID, dudvMapPath, normalMapPath, displacementMapPath;
			bool isWaving, isRippling, isSpecularLighted, isReflective, isRefractive;
			Vec2 speed;
			Vec3 color, position;
			float size, uvRepeat, waveHeightFactor, transparency, specularFactor, specularIntensity;

			// Load base data
			iss >>
				waterID >>
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
			_waterIDs.push_back(waterID);
			_fe3d.waterEntity_add(waterID);
			_fe3d.waterEntity_setPosition(waterID, position);
			_fe3d.waterEntity_setSize(waterID, size);
			_fe3d.waterEntity_setWaving(waterID, isWaving);
			_fe3d.waterEntity_setRippling(waterID, isRippling);
			_fe3d.waterEntity_setSpecularLighted(waterID, isSpecularLighted);
			_fe3d.waterEntity_setReflective(waterID, isReflective);
			_fe3d.waterEntity_setRefractive(waterID, isRefractive);
			_fe3d.waterEntity_setWaveHeightFactor(waterID, waveHeightFactor);
			_fe3d.waterEntity_setSpecularLightingFactor(waterID, specularFactor);
			_fe3d.waterEntity_setSpecularLightingIntensity(waterID, specularIntensity);
			_fe3d.waterEntity_setTransparency(waterID, transparency);
			_fe3d.waterEntity_setColor(waterID, color);
			_fe3d.waterEntity_setUvRepeat(waterID, uvRepeat);
			_fe3d.waterEntity_setSpeed(waterID, speed);
			if (dudvMapPath != "") _fe3d.waterEntity_setDudvMap(waterID, dudvMapPath);
			if (normalMapPath != "") _fe3d.waterEntity_setNormalMap(waterID, normalMapPath);
			if (displacementMapPath != "") _fe3d.waterEntity_setDisplacementMap(waterID, displacementMapPath);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Water data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void EnvironmentEditor::unloadWaterEntities()
{
	for (auto& name : _waterIDs)
	{
		_fe3d.waterEntity_delete(name);
	}
}

void EnvironmentEditor::saveWaterEntitiesToFile()
{
	if (_isEditorLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Compose full file path
		string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\water.fe3d";

		// Load file
		std::ofstream file(filePath);

		// Write every water to file
		for (auto& waterID : _waterIDs)
		{
			// Values
			string dudvMapPath = _fe3d.waterEntity_getDudvMapPath(waterID);
			string normalMapPath = _fe3d.waterEntity_getNormalMapPath(waterID);
			string displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(waterID);
			bool isWaving = _fe3d.waterEntity_isWaving(waterID);
			bool isRippling = _fe3d.waterEntity_isRippling(waterID);
			bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(waterID);
			bool isReflective = _fe3d.waterEntity_isReflective(waterID);
			bool isRefractive = _fe3d.waterEntity_isRefractive(waterID);
			Vec3 color = _fe3d.waterEntity_getColor(waterID);
			float size = _fe3d.waterEntity_getSize(waterID);
			Vec3 position = _fe3d.waterEntity_getPosition(waterID);
			float uvRepeat = _fe3d.waterEntity_getUvRepeat(waterID);
			float waveHeightFactor = _fe3d.waterEntity_getWaveHeightFactor(waterID);
			Vec2 speed = _fe3d.waterEntity_getSpeed(waterID);
			float transparency = _fe3d.waterEntity_getTransparency(waterID);
			float specularFactor = _fe3d.waterEntity_getSpecularLightingFactor(waterID);
			float specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity(waterID);

			// Perform empty string & space conversions
			dudvMapPath = (dudvMapPath == "" ? "?" : dudvMapPath);
			normalMapPath = (normalMapPath == "" ? "?" : normalMapPath);
			displacementMapPath = (displacementMapPath == "" ? "?" : displacementMapPath);
			std::replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
			std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
			std::replace(displacementMapPath.begin(), displacementMapPath.end(), ' ', '?');

			// Write data to file
			file <<
				waterID << " " <<
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