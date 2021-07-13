#include "environment_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

const vector<string> EnvironmentEditor::getAllTerrainTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("EnvironmentEditor::getAllTerrainTexturePathsFromFile() --> no current project loaded!");
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
	std::ifstream file(filePath);

	// Read terrain data
	vector<string> texturePaths;
	string line;
	while (std::getline(file, line))
	{
		// Temporary values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			normalMapPathR, normalMapPathG, normalMapPathB,
			blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
		float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB;
		bool isBlendMapped, isNormalMapped, isNormalMappedR, isNormalMappedG, isNormalMappedB;
		std::istringstream iss(line);

		// Load base data
		iss >>
			terrainID >>
			heightMapPath >>
			diffuseMapPath >>
			maxHeight >>
			uvRepeat >>
			lightness >>
			isBlendMapped >>
			blendMapPath >>
			blendMapPathR >>
			blendMapPathG >>
			blendMapPathB >>
			blendRepeatR >>
			blendRepeatG >>
			blendRepeatB >>
			isNormalMapped >>
			isNormalMappedR >>
			isNormalMappedG >>
			isNormalMappedB >>
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
		std::replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
		std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		std::replace(normalMapPathR.begin(), normalMapPathR.end(), '?', ' ');
		std::replace(normalMapPathG.begin(), normalMapPathG.end(), '?', ' ');
		std::replace(normalMapPathB.begin(), normalMapPathB.end(), '?', ' ');
		std::replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
		std::replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
		std::replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
		std::replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

		// Save file paths
		if (!diffuseMapPath.empty()) texturePaths.push_back(diffuseMapPath);
		if (!heightMapPath.empty())  texturePaths.push_back(heightMapPath);
		if (!normalMapPath.empty())  texturePaths.push_back(normalMapPath);
		if (!normalMapPathR.empty()) texturePaths.push_back(normalMapPathR);
		if (!normalMapPathG.empty()) texturePaths.push_back(normalMapPathG);
		if (!normalMapPathB.empty()) texturePaths.push_back(normalMapPathB);
		if (!blendMapPath.empty())   texturePaths.push_back(blendMapPath);
		if (!blendMapPathR.empty())  texturePaths.push_back(blendMapPathR);
		if (!blendMapPathG.empty())  texturePaths.push_back(blendMapPathG);
		if (!blendMapPathB.empty())  texturePaths.push_back(blendMapPathB);
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

bool EnvironmentEditor::loadTerrainEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("EnvironmentEditor::loadTerrainEntitiesFromFile() --> no current project loaded!");
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
	std::ifstream file(filePath);

	// Read terrain data
	string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);

		// Values
		string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
			normalMapPathR, normalMapPathG, normalMapPathB,
			blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
		float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB, specularFactor, specularIntensity;
		bool isBlendMapped, isNormalMapped, isNormalMappedR, isNormalMappedG, isNormalMappedB, isSpecular;

		// Load base data
		iss >>
			terrainID >>
			heightMapPath >>
			diffuseMapPath >>
			maxHeight >>
			uvRepeat >>
			lightness >>
			isBlendMapped >>
			blendMapPath >>
			blendMapPathR >>
			blendMapPathG >>
			blendMapPathB >>
			blendRepeatR >>
			blendRepeatG >>
			blendRepeatB >>
			isNormalMapped >>
			isNormalMappedR >>
			isNormalMappedG >>
			isNormalMappedB >>
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
		std::replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
		std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		std::replace(normalMapPathR.begin(), normalMapPathR.end(), '?', ' ');
		std::replace(normalMapPathG.begin(), normalMapPathG.end(), '?', ' ');
		std::replace(normalMapPathB.begin(), normalMapPathB.end(), '?', ' ');
		std::replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
		std::replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
		std::replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
		std::replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

		// Add new terrain entity
		_loadedTerrainIDs.push_back(terrainID);
		if (heightMapPath != "")
		{
			_fe3d.terrainEntity_add(terrainID, heightMapPath);
			_fe3d.terrainEntity_setMaxHeight(terrainID, maxHeight);
			_fe3d.terrainEntity_setUvRepeat(terrainID, uvRepeat);
			_fe3d.terrainEntity_setBlendMapped(terrainID, isBlendMapped);
			_fe3d.terrainEntity_setLightness(terrainID, lightness);
			_fe3d.terrainEntity_setBlendRepeatR(terrainID, blendRepeatR);
			_fe3d.terrainEntity_setBlendRepeatG(terrainID, blendRepeatG);
			_fe3d.terrainEntity_setBlendRepeatB(terrainID, blendRepeatB);
			_fe3d.terrainEntity_setNormalMapped(terrainID, isNormalMapped);
			_fe3d.terrainEntity_setNormalMappedR(terrainID, isNormalMappedR);
			_fe3d.terrainEntity_setNormalMappedG(terrainID, isNormalMappedG);
			_fe3d.terrainEntity_setNormalMappedB(terrainID, isNormalMappedB);
			_fe3d.terrainEntity_setSpecularLighted(terrainID, isSpecular);
			_fe3d.terrainEntity_setSpecularLightingFactor(terrainID, specularFactor);
			_fe3d.terrainEntity_setSpecularLightingIntensity(terrainID, specularIntensity);
			if (diffuseMapPath != "") _fe3d.terrainEntity_setDiffuseMap(terrainID, diffuseMapPath);
			if (normalMapPath != "")  _fe3d.terrainEntity_setNormalMap(terrainID, normalMapPath);
			if (normalMapPathR != "") _fe3d.terrainEntity_setNormalMapR(terrainID, normalMapPathR);
			if (normalMapPathG != "") _fe3d.terrainEntity_setNormalMapG(terrainID, normalMapPathG);
			if (normalMapPathB != "") _fe3d.terrainEntity_setNormalMapB(terrainID, normalMapPathB);
			if (blendMapPath != "")   _fe3d.terrainEntity_setBlendMap(terrainID, blendMapPath);
			if (blendMapPathR != "")  _fe3d.terrainEntity_setDiffuseMapR(terrainID, blendMapPathR);
			if (blendMapPathG != "")  _fe3d.terrainEntity_setDiffuseMapG(terrainID, blendMapPathG);
			if (blendMapPathB != "")  _fe3d.terrainEntity_setDiffuseMapB(terrainID, blendMapPathB);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Terrain data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}

bool EnvironmentEditor::saveTerrainEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("EnvironmentEditor::saveTerrainEntitiesToFile() --> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\terrain.fe3d";

	// Load terrain file
	std::ofstream file(filePath);

	// Write terrain data
	for (const auto& terrainID : _loadedTerrainIDs)
	{
		// Values
		string heightMapPath = _fe3d.terrainEntity_getHeightMapPath(terrainID);
		string diffuseMapPath = _fe3d.terrainEntity_getDiffuseMapPath(terrainID);
		string normalMapPath = _fe3d.terrainEntity_getNormalMapPath(terrainID);
		string blendMapPath = _fe3d.terrainEntity_getBlendMapPath(terrainID);
		string blendMapPathR = _fe3d.terrainEntity_getBlendMapPathR(terrainID);
		string blendMapPathG = _fe3d.terrainEntity_getBlendMapPathG(terrainID);
		string blendMapPathB = _fe3d.terrainEntity_getBlendMapPathB(terrainID);
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
		bool isBlendMapped = _fe3d.terrainEntity_isBlendMapped(terrainID);
		bool isNormalMapped = _fe3d.terrainEntity_isNormalMapped(terrainID);
		bool isNormalMappedR = _fe3d.terrainEntity_isNormalMappedR(terrainID);
		bool isNormalMappedG = _fe3d.terrainEntity_isNormalMappedG(terrainID);
		bool isNormalMappedB = _fe3d.terrainEntity_isNormalMappedB(terrainID);
		bool isSpecular = _fe3d.terrainEntity_isSpecularLighted(terrainID);

		// Perform empty string & space conversions
		heightMapPath = (heightMapPath == "") ? "?" : heightMapPath;
		diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
		normalMapPath = (normalMapPath == "") ? "?" : normalMapPath;
		blendMapPath = (blendMapPath == "") ? "?" : blendMapPath;
		blendMapPathR = (blendMapPathR == "") ? "?" : blendMapPathR;
		blendMapPathG = (blendMapPathG == "") ? "?" : blendMapPathG;
		blendMapPathB = (blendMapPathB == "") ? "?" : blendMapPathB;
		normalMapPathR = (normalMapPathR == "") ? "?" : normalMapPathR;
		normalMapPathG = (normalMapPathG == "") ? "?" : normalMapPathG;
		normalMapPathB = (normalMapPathB == "") ? "?" : normalMapPathB;
		std::replace(heightMapPath.begin(), heightMapPath.end(), ' ', '?');
		std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		std::replace(blendMapPath.begin(), blendMapPath.end(), ' ', '?');
		std::replace(blendMapPathR.begin(), blendMapPathR.end(), ' ', '?');
		std::replace(blendMapPathG.begin(), blendMapPathG.end(), ' ', '?');
		std::replace(blendMapPathB.begin(), blendMapPathB.end(), ' ', '?');
		std::replace(normalMapPathR.begin(), normalMapPathR.end(), ' ', '?');
		std::replace(normalMapPathG.begin(), normalMapPathG.end(), ' ', '?');
		std::replace(normalMapPathB.begin(), normalMapPathB.end(), ' ', '?');

		// Write terrain data to file
		file <<
			terrainID << " " <<
			heightMapPath << " " <<
			diffuseMapPath << " " <<
			maxHeight << " " <<
			uvRepeat << " " <<
			lightness << " " <<
			isBlendMapped << " " <<
			blendMapPath << " " <<
			blendMapPathR << " " <<
			blendMapPathG << " " <<
			blendMapPathB << " " <<
			blendRepeatR << " " <<
			blendRepeatG << " " <<
			blendRepeatB << " " <<
			isNormalMapped << " " <<
			isNormalMappedR << " " <<
			isNormalMappedG << " " <<
			isNormalMappedB << " " <<
			normalMapPath << " " <<
			normalMapPathR << " " <<
			normalMapPathG << " " <<
			normalMapPathB << " " <<
			isSpecular << " " <<
			specularFactor << " " <<
			specularIntensity << std::endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Terrain data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}