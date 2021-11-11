#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> WaterEditor::getAllWaterTexturePathsFromFile() const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("WaterEditor::getAllWaterTexturePathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("game\\" + _currentProjectID + "\\")) + "data\\water.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `water.fe3d` missing!");
		return {};
	}

	// Load water file
	ifstream file(filePath);

	// Read water data
	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		// Values
		string waterID, dudvMapPath, normalMapPath, displacementMapPath;

		// For file extraction
		istringstream iss(line);

		// Load base data
		iss >>
			waterID >>
			dudvMapPath >>
			normalMapPath >>
			displacementMapPath;

		// Convert empty string
		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);

		// Convert spaces
		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

		// DUDV map
		if(!dudvMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				dudvMapPath = string("game\\" + _currentProjectID + "\\" + dudvMapPath);
			}

			// Save path
			texturePaths.push_back(dudvMapPath);
		}

		// Normal map
		if(!normalMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				normalMapPath = string("game\\" + _currentProjectID + "\\" + normalMapPath);
			}

			// Save path
			texturePaths.push_back(normalMapPath);
		}

		// Displacement map
		if(!displacementMapPath.empty())
		{
			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				displacementMapPath = string("game\\" + _currentProjectID + "\\" + displacementMapPath);
			}

			// Save path
			texturePaths.push_back(displacementMapPath);
		}
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

const bool WaterEditor::loadWaterEntitiesFromFile()
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("WaterEditor::loadWaterEntitiesFromFile");
	}

	// Clear IDs from previous loads
	_loadedWaterIDs.clear();

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("game\\" + _currentProjectID)) + "\\data\\water.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `water.fe3d` missing!");
		return false;
	}

	// Load water file
	ifstream file(filePath);

	// Read water data
	string line;
	while(getline(file, line))
	{
		// Values
		string waterID, dudvMapPath, normalMapPath, displacementMapPath;
		Vec3 color;
		Vec2 speed;
		float height, size, textureRepeat, waveHeight, transparency, specularShininess, specularIntensity;
		unsigned int quality;
		bool isSpecular, isReflective, isRefractive;

		// For file extraction
		istringstream iss(line);

		// Load base data
		iss >>
			waterID >>
			dudvMapPath >>
			normalMapPath >>
			displacementMapPath >>
			isSpecular >>
			isReflective >>
			isRefractive >>
			color.r >>
			color.g >>
			color.b >>
			size >>
			height >>
			textureRepeat >>
			waveHeight >>
			quality >>
			speed.x >>
			speed.y >>
			transparency >>
			specularShininess >>
			specularIntensity;

		// Convert empty string
		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);

		// Convert spaces
		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

		// Create water
		_fe3d.waterEntity_create(waterID);

		// Check if water creation went well
		if(_fe3d.waterEntity_isExisting(waterID))
		{
			// Add water ID
			_loadedWaterIDs.push_back(waterID);

			// DUDV map
			if(dudvMapPath != "")
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					dudvMapPath = string("game\\" + _currentProjectID + "\\" + dudvMapPath);
				}

				// Set path
				_fe3d.waterEntity_setDudvMap(waterID, dudvMapPath);
			}

			// Normal map
			if(normalMapPath != "")
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					normalMapPath = string("game\\" + _currentProjectID + "\\" + normalMapPath);
				}

				// Set path
				_fe3d.waterEntity_setNormalMap(waterID, normalMapPath);
			}

			// Displacement map
			if(displacementMapPath != "")
			{
				// Convert to long path
				if(!Config::getInst().isApplicationExported())
				{
					displacementMapPath = string("game\\" + _currentProjectID + "\\" + displacementMapPath);
				}

				// Set path
				_fe3d.waterEntity_setDisplacementMap(waterID, displacementMapPath);
			}

			// Set properties
			_fe3d.waterEntity_setHeight(waterID, height);
			_fe3d.waterEntity_setSize(waterID, size);
			_fe3d.waterEntity_setSpecular(waterID, isSpecular);
			_fe3d.waterEntity_setReflective(waterID, isReflective);
			_fe3d.waterEntity_setRefractive(waterID, isRefractive);
			_fe3d.waterEntity_setWaveHeight(waterID, waveHeight);
			_fe3d.waterEntity_setQuality(waterID, static_cast<WaterQuality>(quality));
			_fe3d.waterEntity_setSpecularShininess(waterID, specularShininess);
			_fe3d.waterEntity_setSpecularIntensity(waterID, specularIntensity);
			_fe3d.waterEntity_setTransparency(waterID, transparency);
			_fe3d.waterEntity_setColor(waterID, color);
			_fe3d.waterEntity_setTextureRepeat(waterID, textureRepeat);
			_fe3d.waterEntity_setSpeed(waterID, speed);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Water data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}