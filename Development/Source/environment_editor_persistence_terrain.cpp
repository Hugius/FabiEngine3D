#include "environment_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

const vector<string> EnvironmentEditor::getAllTerrainTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded --> EnvironmentEditor::getAllTerrainTexturePathsFromFile()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\terrain.fe3d";

	// Load terrain file
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Temporary values
		std::ifstream file(filePath);
		string line;
		vector<string> texturePaths;

		// Read terrain data
		while (std::getline(file, line))
		{
			// Temporary values
			string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
				normalMapPathR, normalMapPathG, normalMapPathB,
				blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
			float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB, specularFactor, specularIntensity;
			bool isBlendMapped, isNormalMapped, isNormalMappedR, isNormalMappedG, isNormalMappedB, isSpecular;
			stringstream iss(line);

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
			blendMapPath = (blendMapPath == "?") ? "?" : blendMapPath;
			blendMapPathR = (blendMapPathR == "?") ? "" : blendMapPathR;
			blendMapPathG = (blendMapPathG == "?") ? "" : blendMapPathG;
			blendMapPathB = (blendMapPathB == "?") ? "" : blendMapPathB;
			std::replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
			std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			std::replace(normalMapPathR.begin(), normalMapPathR.end(), '?', ' ');
			std::replace(normalMapPathG.begin(), normalMapPathG.end(), '?', ' ');
			std::replace(normalMapPathB.begin(), normalMapPathB.end(), '?', ' ');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			std::replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
			std::replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
			std::replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
			std::replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

			// Save file paths
			if (!heightMapPath.empty())  texturePaths.push_back(heightMapPath);
			if (!normalMapPath.empty())  texturePaths.push_back(normalMapPath);
			if (!normalMapPathR.empty()) texturePaths.push_back(normalMapPathR);
			if (!normalMapPathG.empty()) texturePaths.push_back(normalMapPathG);
			if (!normalMapPathB.empty()) texturePaths.push_back(normalMapPathB);
			if (!diffuseMapPath.empty()) texturePaths.push_back(diffuseMapPath);
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
}

void EnvironmentEditor::loadTerrainEntitiesFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded --> EnvironmentEditor::loadTerrainEntitiesFromFile()");
	}

	// Clear names list from previous loads
	_terrainIDs.clear();

	// Compose full terrain file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\terrain.fe3d";

	// Check if terrain file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read terrain data
		while (std::getline(file, line))
		{
			stringstream iss(line);

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
			blendMapPath = (blendMapPath == "?") ? "?" : blendMapPath;
			blendMapPathR = (blendMapPathR == "?") ? "" : blendMapPathR;
			blendMapPathG = (blendMapPathG == "?") ? "" : blendMapPathG;
			blendMapPathB = (blendMapPathB == "?") ? "" : blendMapPathB;
			std::replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
			std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			std::replace(normalMapPathR.begin(), normalMapPathR.end(), '?', ' ');
			std::replace(normalMapPathG.begin(), normalMapPathG.end(), '?', ' ');
			std::replace(normalMapPathB.begin(), normalMapPathB.end(), '?', ' ');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			std::replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
			std::replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
			std::replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
			std::replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

			// Add new terrain entity
			_terrainIDs.push_back(terrainID);
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
				if (normalMapPathR != "")  _fe3d.terrainEntity_setNormalMapR(terrainID, normalMapPathR);
				if (normalMapPathG != "")  _fe3d.terrainEntity_setNormalMapG(terrainID, normalMapPathG);
				if (normalMapPathB != "")  _fe3d.terrainEntity_setNormalMapB(terrainID, normalMapPathB);
				if (blendMapPath != "")   _fe3d.terrainEntity_setBlendMap(terrainID, blendMapPath);
				if (blendMapPathR != "")  _fe3d.terrainEntity_setBlendMapR(terrainID, blendMapPathR);
				if (blendMapPathG != "")  _fe3d.terrainEntity_setBlendMapG(terrainID, blendMapPathG);
				if (blendMapPathB != "")  _fe3d.terrainEntity_setBlendMapB(terrainID, blendMapPathB);
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Terrain data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void EnvironmentEditor::unloadTerrainEntities()
{
	for (auto& name : _terrainIDs)
	{
		_fe3d.terrainEntity_delete(name);
	}
}

void EnvironmentEditor::saveTerrainEntitiesToFile()
{
	if (_isEditorLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Compose full terrain file path
		string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\terrain.fe3d";

		// Load file
		std::ofstream file(filePath);
			
		// Write every terrain to file
		for (auto& terrainID : _terrainIDs)
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
		_fe3d.logger_throwInfo("Terrain data from project \"" + _currentProjectName + "\" saved!");
	}
}