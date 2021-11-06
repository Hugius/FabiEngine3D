#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> TerrainEditor::getAllTerrainTexturePathsFromFile() const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::getAllTerrainTexturePathsFromFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\terrain.fe3d";

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `terrain.fe3d` missing!");
		return {};
	}

	// Load terrain file
	ifstream file(filePath);

	// Read terrain data
	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		// Values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			normalMapPathR, normalMapPathG, normalMapPathB,
			blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
		float maxHeight, textureRepeat, lightness, redRepeat, greenRepeat, blueRepeat;

		// For file extraction
		istringstream iss(line);

		// Load base data
		iss >>
			terrainID >>
			heightMapPath >>
			diffuseMapPath >>
			maxHeight >>
			textureRepeat >>
			lightness >>
			blendMapPath >>
			blendMapPathR >>
			blendMapPathG >>
			blendMapPathB >>
			redRepeat >>
			greenRepeat >>
			blueRepeat >>
			normalMapPath >>
			normalMapPathR >>
			normalMapPathG >>
			normalMapPathB;

		// Perform empty string & space conversions
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
		normalMapPathR = (normalMapPathR == "?") ? "" : normalMapPathR;
		normalMapPathG = (normalMapPathG == "?") ? "" : normalMapPathG;
		normalMapPathB = (normalMapPathB == "?") ? "" : normalMapPathB;
		blendMapPath = (blendMapPath == "?") ? "" : blendMapPath;
		blendMapPathR = (blendMapPathR == "?") ? "" : blendMapPathR;
		blendMapPathG = (blendMapPathG == "?") ? "" : blendMapPathG;
		blendMapPathB = (blendMapPathB == "?") ? "" : blendMapPathB;
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(normalMapPathR.begin(), normalMapPathR.end(), '?', ' ');
		replace(normalMapPathG.begin(), normalMapPathG.end(), '?', ' ');
		replace(normalMapPathB.begin(), normalMapPathB.end(), '?', ' ');
		replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
		replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
		replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
		replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

		// Save diffuse map path
		if(!diffuseMapPath.empty())
		{
			texturePaths.push_back(diffuseMapPath);
		}

		// Save normal map path
		if(!normalMapPath.empty())
		{
			texturePaths.push_back(normalMapPath);
		}

		// Save normal map R path
		if(!normalMapPathR.empty())
		{
			texturePaths.push_back(normalMapPathR);
		}

		// Save normal map G path
		if(!normalMapPathG.empty())
		{
			texturePaths.push_back(normalMapPathG);
		}

		// Save normal map B path
		if(!normalMapPathB.empty())
		{
			texturePaths.push_back(normalMapPathB);
		}

		// Save blend map path
		if(!blendMapPath.empty())
		{
			texturePaths.push_back(blendMapPath);
		}

		// Save blend map R path
		if(!blendMapPathR.empty())
		{
			texturePaths.push_back(blendMapPathR);
		}

		// Save blend map G path
		if(!blendMapPathG.empty())
		{
			texturePaths.push_back(blendMapPathG);
		}

		// Save blend map B path
		if(!blendMapPathB.empty())
		{
			texturePaths.push_back(blendMapPathB);
		}
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

const vector<string> TerrainEditor::getAllTerrainBitmapPathsFromFile() const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::getAllTerrainTexturePathsFromFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\terrain.fe3d";

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `terrain.fe3d` missing!");
		return {};
	}

	// Load terrain file
	ifstream file(filePath);

	// Read terrain data
	vector<string> bitmapPaths;
	string line;
	while(getline(file, line))
	{
		// Values
		string terrainID, heightMapPath;

		// For file extraction
		istringstream iss(line);

		// Load base data
		iss >>
			terrainID >>
			heightMapPath;

		// Perform empty string & space conversions
		heightMapPath = (heightMapPath == "?") ? "" : heightMapPath;
		replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');

		// Save height map path
		if(!heightMapPath.empty())
		{
			bitmapPaths.push_back(heightMapPath);
		}
	}

	// Close file
	file.close();

	// Return
	return bitmapPaths;
}

const bool TerrainEditor::loadTerrainEntitiesFromFile()
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::loadTerrainEntitiesFromFile");
	}

	// Clear IDs from previous loads
	_loadedTerrainIDs.clear();

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\terrain.fe3d";

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `terrain.fe3d` missing!");
		return false;
	}

	// Load terrain file
	ifstream file(filePath);

	// Read terrain data
	string line;
	while(getline(file, line))
	{
		// Values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			normalMapPathR, normalMapPathG, normalMapPathB,
			blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
		float maxHeight, textureRepeat, lightness, redRepeat, greenRepeat, blueRepeat, specularShininess, specularIntensity;
		bool isSpecular;

		// For file extraction
		istringstream iss(line);

		// Load base data
		iss >>
			terrainID >>
			heightMapPath >>
			diffuseMapPath >>
			maxHeight >>
			textureRepeat >>
			lightness >>
			blendMapPath >>
			blendMapPathR >>
			blendMapPathG >>
			blendMapPathB >>
			redRepeat >>
			greenRepeat >>
			blueRepeat >>
			normalMapPath >>
			normalMapPathR >>
			normalMapPathG >>
			normalMapPathB >>
			isSpecular >>
			specularShininess >>
			specularIntensity;

		// Perform empty string & space conversions
		heightMapPath = (heightMapPath == "?") ? "" : heightMapPath;
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
		normalMapPathR = (normalMapPathR == "?") ? "" : normalMapPathR;
		normalMapPathG = (normalMapPathG == "?") ? "" : normalMapPathG;
		normalMapPathB = (normalMapPathB == "?") ? "" : normalMapPathB;
		blendMapPath = (blendMapPath == "?") ? "" : blendMapPath;
		blendMapPathR = (blendMapPathR == "?") ? "" : blendMapPathR;
		blendMapPathG = (blendMapPathG == "?") ? "" : blendMapPathG;
		blendMapPathB = (blendMapPathB == "?") ? "" : blendMapPathB;
		replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(normalMapPathR.begin(), normalMapPathR.end(), '?', ' ');
		replace(normalMapPathG.begin(), normalMapPathG.end(), '?', ' ');
		replace(normalMapPathB.begin(), normalMapPathB.end(), '?', ' ');
		replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
		replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
		replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
		replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

		// Create terrain
		_fe3d.terrainEntity_create(terrainID, heightMapPath);

		// Check if terrain creation went well
		if(_fe3d.terrainEntity_isExisting(terrainID))
		{
			// Add terrain ID
			_loadedTerrainIDs.push_back(terrainID);

			// Diffuse map
			if(!diffuseMapPath.empty())
			{
				_fe3d.terrainEntity_setDiffuseMap(terrainID, diffuseMapPath);
			}

			// Normal map
			if(!normalMapPath.empty())
			{
				_fe3d.terrainEntity_setNormalMap(terrainID, normalMapPath);
			}

			// Normal map R
			if(!normalMapPathR.empty())
			{
				_fe3d.terrainEntity_setNormalMapR(terrainID, normalMapPathR);
			}

			// Normal map G
			if(!normalMapPathG.empty())
			{
				_fe3d.terrainEntity_setNormalMapG(terrainID, normalMapPathG);
			}

			// Normal map B
			if(!normalMapPathB.empty())
			{
				_fe3d.terrainEntity_setNormalMapB(terrainID, normalMapPathB);
			}

			// Blend map
			if(!blendMapPath.empty())
			{
				_fe3d.terrainEntity_setBlendMap(terrainID, blendMapPath);
			}

			// Blend map R
			if(!blendMapPathR.empty())
			{
				_fe3d.terrainEntity_setDiffuseMapR(terrainID, blendMapPathR);
			}

			// Blend map G
			if(!blendMapPathG.empty())
			{
				_fe3d.terrainEntity_setDiffuseMapG(terrainID, blendMapPathG);
			}

			// Blend map B
			if(!blendMapPathB.empty())
			{
				_fe3d.terrainEntity_setDiffuseMapB(terrainID, blendMapPathB);
			}

			// Set properties
			_fe3d.terrainEntity_setMaxHeight(terrainID, maxHeight);
			_fe3d.terrainEntity_setTextureRepeat(terrainID, textureRepeat);
			_fe3d.terrainEntity_setLightness(terrainID, lightness);
			_fe3d.terrainEntity_setRedRepeat(terrainID, redRepeat);
			_fe3d.terrainEntity_setGreenRepeat(terrainID, greenRepeat);
			_fe3d.terrainEntity_setBlueRepeat(terrainID, blueRepeat);
			_fe3d.terrainEntity_setSpecular(terrainID, isSpecular);
			_fe3d.terrainEntity_setSpecularShininess(terrainID, specularShininess);
			_fe3d.terrainEntity_setSpecularIntensity(terrainID, specularIntensity);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Terrain data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}

const bool TerrainEditor::saveTerrainEntitiesToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::saveTerrainEntitiesToFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\terrain.fe3d";

	// Load terrain file
	ofstream file(filePath);

	// Write terrain data
	for(const auto& terrainID : _loadedTerrainIDs)
	{
		// Values
		string heightMapPath = _fe3d.terrainEntity_getHeightMapPath(terrainID);
		string diffuseMapPath = _fe3d.terrainEntity_getDiffuseMapPath(terrainID);
		string normalMapPath = _fe3d.terrainEntity_getNormalMapPath(terrainID);
		string blendMapPath = _fe3d.terrainEntity_getBlendMapPath(terrainID);
		string blendMapPathR = _fe3d.terrainEntity_getDiffuseMapPathR(terrainID);
		string blendMapPathG = _fe3d.terrainEntity_getDiffuseMapPathG(terrainID);
		string blendMapPathB = _fe3d.terrainEntity_getDiffuseMapPathB(terrainID);
		string normalMapPathR = _fe3d.terrainEntity_getNormalMapPathR(terrainID);
		string normalMapPathG = _fe3d.terrainEntity_getNormalMapPathG(terrainID);
		string normalMapPathB = _fe3d.terrainEntity_getNormalMapPathB(terrainID);
		float maxHeight = _fe3d.terrainEntity_getMaxHeight(terrainID);
		float textureRepeat = _fe3d.terrainEntity_getTextureRepeat(terrainID);
		float lightness = _fe3d.terrainEntity_getLightness(terrainID);
		float specularShininess = _fe3d.terrainEntity_getSpecularShininess(terrainID);
		float specularIntensity = _fe3d.terrainEntity_getSpecularIntensity(terrainID);
		float redRepeat = _fe3d.terrainEntity_getRedRepeat(terrainID);
		float greenRepeat = _fe3d.terrainEntity_getGreenRepeat(terrainID);
		float blueRepeat = _fe3d.terrainEntity_getBlueRepeat(terrainID);
		bool isSpecular = _fe3d.terrainEntity_isSpecular(terrainID);

		// Perform empty string & space conversions
		heightMapPath = (heightMapPath.empty()) ? "?" : heightMapPath;
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;
		blendMapPath = (blendMapPath.empty()) ? "?" : blendMapPath;
		blendMapPathR = (blendMapPathR.empty()) ? "?" : blendMapPathR;
		blendMapPathG = (blendMapPathG.empty()) ? "?" : blendMapPathG;
		blendMapPathB = (blendMapPathB.empty()) ? "?" : blendMapPathB;
		normalMapPathR = (normalMapPathR.empty()) ? "?" : normalMapPathR;
		normalMapPathG = (normalMapPathG.empty()) ? "?" : normalMapPathG;
		normalMapPathB = (normalMapPathB.empty()) ? "?" : normalMapPathB;
		replace(heightMapPath.begin(), heightMapPath.end(), ' ', '?');
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(blendMapPath.begin(), blendMapPath.end(), ' ', '?');
		replace(blendMapPathR.begin(), blendMapPathR.end(), ' ', '?');
		replace(blendMapPathG.begin(), blendMapPathG.end(), ' ', '?');
		replace(blendMapPathB.begin(), blendMapPathB.end(), ' ', '?');
		replace(normalMapPathR.begin(), normalMapPathR.end(), ' ', '?');
		replace(normalMapPathG.begin(), normalMapPathG.end(), ' ', '?');
		replace(normalMapPathB.begin(), normalMapPathB.end(), ' ', '?');

		// Write terrain data to file
		file <<
			terrainID << " " <<
			heightMapPath << " " <<
			diffuseMapPath << " " <<
			maxHeight << " " <<
			textureRepeat << " " <<
			lightness << " " <<
			blendMapPath << " " <<
			blendMapPathR << " " <<
			blendMapPathG << " " <<
			blendMapPathB << " " <<
			redRepeat << " " <<
			greenRepeat << " " <<
			blueRepeat << " " <<
			normalMapPath << " " <<
			normalMapPathR << " " <<
			normalMapPathG << " " <<
			normalMapPathB << " " <<
			isSpecular << " " <<
			specularShininess << " " <<
			specularIntensity << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Terrain data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}