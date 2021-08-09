#include "terrain_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> TerrainEditor::getAllTerrainTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("EnvironmentEditor::getAllTerrainTexturePathsFromFile() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\terrain.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"terrain.fe3d\" file missing!");
		return {};
	}

	// Load terrain file
	ifstream file(filePath);

	// Read terrain data
	vector<string> texturePaths;
	string line;
	while (getline(file, line))
	{
		// Temporary values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			normalMapPathR, normalMapPathG, normalMapPathB,
			blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
		float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB;
		istringstream iss(line);

		// Load base data
		iss >>
			terrainID >>
			heightMapPath >>
			diffuseMapPath >>
			maxHeight >>
			uvRepeat >>
			lightness >>
			blendMapPath >>
			blendMapPathR >>
			blendMapPathG >>
			blendMapPathB >>
			blendRepeatR >>
			blendRepeatG >>
			blendRepeatB >>
			normalMapPath >>
			normalMapPathR >>
			normalMapPathG >>
			normalMapPathB;

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

		// Save diffuse map path
		if (!diffuseMapPath.empty())
		{
			texturePaths.push_back(diffuseMapPath);
		}

		// Save height map path
		if (!heightMapPath.empty())
		{
			texturePaths.push_back(heightMapPath);
		}

		// Save normal map path
		if (!normalMapPath.empty())
		{
			texturePaths.push_back(normalMapPath);
		}

		// Save normal map R path
		if (!normalMapPathR.empty())
		{
			texturePaths.push_back(normalMapPathR);
		}

		// Save normal map G path
		if (!normalMapPathG.empty())
		{
			texturePaths.push_back(normalMapPathG);
		}

		// Save normal map B path
		if (!normalMapPathB.empty())
		{
			texturePaths.push_back(normalMapPathB);
		}

		// Save blend map path
		if (!blendMapPath.empty())
		{
			texturePaths.push_back(blendMapPath);
		}

		// Save blend map R path
		if (!blendMapPathR.empty())
		{
			texturePaths.push_back(blendMapPathR);
		}

		// Save blend map G path
		if (!blendMapPathG.empty())
		{
			texturePaths.push_back(blendMapPathG);
		}

		// Save blend map B path
		if (!blendMapPathB.empty())
		{
			texturePaths.push_back(blendMapPathB);
		}
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

bool TerrainEditor::loadTerrainEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("EnvironmentEditor::loadTerrainEntitiesFromFile() ---> no current project loaded!");
	}

	// Clear IDs from previous loads
	_loadedTerrainIDs.clear();

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\terrain.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"terrain.fe3d\" file missing!");
		return false;
	}

	// Load terrain file
	ifstream file(filePath);

	// Read terrain data
	string line;
	while (getline(file, line))
	{
		istringstream iss(line);

		// Values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			normalMapPathR, normalMapPathG, normalMapPathB,
			blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
		float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB, specularFactor, specularIntensity;
		bool isSpecular;

		// Load base data
		iss >>
			terrainID >>
			heightMapPath >>
			diffuseMapPath >>
			maxHeight >>
			uvRepeat >>
			lightness >>
			blendMapPath >>
			blendMapPathR >>
			blendMapPathG >>
			blendMapPathB >>
			blendRepeatR >>
			blendRepeatG >>
			blendRepeatB >>
			normalMapPath >>
			normalMapPathR >>
			normalMapPathG >>
			normalMapPathB >>
			isSpecular >>
			specularFactor >>
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
		if (_fe3d.terrainEntity_isExisting(terrainID))
		{
			// Add terrain ID
			_loadedTerrainIDs.push_back(terrainID);

			// Diffuse map
			if (!diffuseMapPath.empty())
			{
				_fe3d.terrainEntity_setDiffuseMap(terrainID, diffuseMapPath);
			}

			// Normal map
			if (!normalMapPath.empty())
			{
				_fe3d.terrainEntity_setNormalMap(terrainID, normalMapPath);
			}

			// Normal map R
			if (!normalMapPathR.empty())
			{
				_fe3d.terrainEntity_setNormalMapR(terrainID, normalMapPathR);
			}

			// Normal map G
			if (!normalMapPathG.empty())
			{
				_fe3d.terrainEntity_setNormalMapG(terrainID, normalMapPathG);
			}

			// Normal map B
			if (!normalMapPathB.empty())
			{
				_fe3d.terrainEntity_setNormalMapB(terrainID, normalMapPathB);
			}

			// Blend map
			if (!blendMapPath.empty())
			{
				_fe3d.terrainEntity_setBlendMap(terrainID, blendMapPath);
			}

			// Blend map R
			if (!blendMapPathR.empty())
			{
				_fe3d.terrainEntity_setDiffuseMapR(terrainID, blendMapPathR);
			}

			// Blend map G
			if (!blendMapPathG.empty())
			{
				_fe3d.terrainEntity_setDiffuseMapG(terrainID, blendMapPathG);
			}

			// Blend map B
			if (!blendMapPathB.empty())
			{
				_fe3d.terrainEntity_setDiffuseMapB(terrainID, blendMapPathB);
			}

			// Set properties
			_fe3d.terrainEntity_setMaxHeight(terrainID, maxHeight);
			_fe3d.terrainEntity_setUvRepeat(terrainID, uvRepeat);
			_fe3d.terrainEntity_setLightness(terrainID, lightness);
			_fe3d.terrainEntity_setBlendRepeatR(terrainID, blendRepeatR);
			_fe3d.terrainEntity_setBlendRepeatG(terrainID, blendRepeatG);
			_fe3d.terrainEntity_setBlendRepeatB(terrainID, blendRepeatB);
			_fe3d.terrainEntity_setSpecularLighted(terrainID, isSpecular);
			_fe3d.terrainEntity_setSpecularLightingFactor(terrainID, specularFactor);
			_fe3d.terrainEntity_setSpecularLightingIntensity(terrainID, specularIntensity);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Terrain data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}

bool TerrainEditor::saveTerrainEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("EnvironmentEditor::saveTerrainEntitiesToFile() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\terrain.fe3d";

	// Load terrain file
	ofstream file(filePath);

	// Write terrain data
	for (const auto& terrainID : _loadedTerrainIDs)
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
		float uvRepeat = _fe3d.terrainEntity_getUvRepeat(terrainID);
		float lightness = _fe3d.terrainEntity_getLightness(terrainID);
		float specularFactor = _fe3d.terrainEntity_getSpecularLightingFactor(terrainID);
		float specularIntensity = _fe3d.terrainEntity_getSpecularLightingIntensity(terrainID);
		float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(terrainID);
		float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(terrainID);
		float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(terrainID);
		bool isSpecular = _fe3d.terrainEntity_isSpecularLighted(terrainID);

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
			uvRepeat << " " <<
			lightness << " " <<
			blendMapPath << " " <<
			blendMapPathR << " " <<
			blendMapPathG << " " <<
			blendMapPathB << " " <<
			blendRepeatR << " " <<
			blendRepeatG << " " <<
			blendRepeatB << " " <<
			normalMapPath << " " <<
			normalMapPathR << " " <<
			normalMapPathG << " " <<
			normalMapPathB << " " <<
			isSpecular << " " <<
			specularFactor << " " <<
			specularIntensity << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Terrain data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}