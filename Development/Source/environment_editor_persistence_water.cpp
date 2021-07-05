#include "environment_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

const vector<string> EnvironmentEditor::getAllWaterTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("No current project loaded --> EnvironmentEditor::getAllWaterTexturePathsFromFile()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\water.fe3d";

	// Load water file
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Temporary values
		std::ifstream file(filePath);
		string line;
		vector<string> texturePaths;

		// Read water data
		while (std::getline(file, line))
		{
			// Temporary values
			string waterID, dudvMapPath, normalMapPath, displacementMapPath;
			std::istringstream iss(line);

			// Load base data
			iss >>
				waterID >>
				dudvMapPath >>
				normalMapPath >>
				displacementMapPath;

			// Perform empty string & space conversions
			dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
			normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
			displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);
			std::replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
			std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			std::replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

			// Save file paths
			if (!dudvMapPath.empty())
			{
				texturePaths.push_back(dudvMapPath);
			}
			if (!normalMapPath.empty())
			{
				texturePaths.push_back(normalMapPath);
			}
			if (!displacementMapPath.empty())
			{
				texturePaths.push_back(displacementMapPath);
			}
		}

		// Close file
		file.close();

		// Return
		return texturePaths;
	}
	else
	{
		Logger::throwError("Project \"" + _currentProjectID + "\" corrupted: \"water.fe3d\" missing!");
	}

	return {};
}

void EnvironmentEditor::loadWaterEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("No current project loaded --> EnvironmentEditor::loadWaterEntitiesFromFile()");
	}

	// Clear names list from previous loads
	_loadedWaterIDs.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\water.fe3d";

	// Load water file
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read water data
		while (std::getline(file, line))
		{
			std::istringstream iss(line);

			// Values
			string waterID, dudvMapPath, normalMapPath, displacementMapPath;
			Vec3 color, position;
			Vec2 speed;
			float size, uvRepeat, waveHeightFactor, transparency, specularFactor, specularIntensity;
			unsigned int quality;
			bool isWaving, isRippling, isSpecularLighted, isReflective, isRefractive;

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
				quality >>
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
			_loadedWaterIDs.push_back(waterID);
			_fe3d.waterEntity_add(waterID);
			_fe3d.waterEntity_setPosition(waterID, position);
			_fe3d.waterEntity_setSize(waterID, size);
			_fe3d.waterEntity_setWaving(waterID, isWaving);
			_fe3d.waterEntity_setRippling(waterID, isRippling);
			_fe3d.waterEntity_setSpecularLighted(waterID, isSpecularLighted);
			_fe3d.waterEntity_setReflective(waterID, isReflective);
			_fe3d.waterEntity_setRefractive(waterID, isRefractive);
			_fe3d.waterEntity_setWaveHeightFactor(waterID, waveHeightFactor);
			_fe3d.waterEntity_setQuality(waterID, static_cast<WaterQuality>(quality));
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
		Logger::throwInfo("Water data from project \"" + _currentProjectID + "\" loaded!");
	}
	else
	{
		Logger::throwError("Project \"" + _currentProjectID + "\" corrupted: \"water.fe3d\" missing!");
	}
}

void EnvironmentEditor::unloadWaterEntities()
{
	for (const auto& ID : _loadedWaterIDs)
	{
		if (_fe3d.waterEntity_isExisting(ID))
		{
			_fe3d.waterEntity_delete(ID);
		}
	}
}

void EnvironmentEditor::saveWaterEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("No current project loaded --> EnvironmentEditor::saveWaterEntitiesToFile()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\water.fe3d";

	// Load file
	std::ofstream file(filePath);

	// Write every water to file
	for (const auto& waterID : _loadedWaterIDs)
	{
		// Values
		auto dudvMapPath = _fe3d.waterEntity_getDudvMapPath(waterID);
		auto normalMapPath = _fe3d.waterEntity_getNormalMapPath(waterID);
		auto displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(waterID);
		auto color = _fe3d.waterEntity_getColor(waterID);
		auto position = _fe3d.waterEntity_getPosition(waterID);
		auto speed = _fe3d.waterEntity_getSpeed(waterID);
		auto size = _fe3d.waterEntity_getSize(waterID);
		auto uvRepeat = _fe3d.waterEntity_getUvRepeat(waterID);
		auto waveHeightFactor = _fe3d.waterEntity_getWaveHeightFactor(waterID);
		auto transparency = _fe3d.waterEntity_getTransparency(waterID);
		auto specularFactor = _fe3d.waterEntity_getSpecularLightingFactor(waterID);
		auto specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity(waterID);
		auto quality = static_cast<unsigned int>(_fe3d.waterEntity_getQuality(waterID));
		auto isWaving = _fe3d.waterEntity_isWaving(waterID);
		auto isRippling = _fe3d.waterEntity_isRippling(waterID);
		auto isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(waterID);
		auto isReflective = _fe3d.waterEntity_isReflective(waterID);
		auto isRefractive = _fe3d.waterEntity_isRefractive(waterID);

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
			quality << " " <<
			speed.x << " " <<
			speed.y << " " <<
			transparency << " " <<
			specularFactor << " " <<
			specularIntensity << std::endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Water data from project \"" + _currentProjectID + "\" saved!");
}

const vector<string>& EnvironmentEditor::getLoadedWaterIDs()
{
	std::sort(_loadedWaterIDs.begin(), _loadedWaterIDs.end());
	return _loadedWaterIDs;
}