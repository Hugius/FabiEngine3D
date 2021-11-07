#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

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
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\water.fe3d";

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

		// Perform empty string & space conversions
		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);
		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

		// Save file path
		if(!dudvMapPath.empty())
		{
			texturePaths.push_back(dudvMapPath);
		}
		if(!normalMapPath.empty())
		{
			texturePaths.push_back(normalMapPath);
		}
		if(!displacementMapPath.empty())
		{
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
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\water.fe3d";

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

		// Perform empty string & space conversions
		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);
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
				_fe3d.waterEntity_setDudvMap(waterID, dudvMapPath);
			}

			// Normal map
			if(normalMapPath != "")
			{
				_fe3d.waterEntity_setNormalMap(waterID, normalMapPath);
			}

			// Displacement map
			if(displacementMapPath != "")
			{
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