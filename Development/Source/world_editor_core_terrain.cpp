#include "world_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void WorldEditor::loadTerrainEntity()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	// Compose full terrain file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\terrain.fe3d";

	// Load terrain file
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Load file
		std::ifstream terrainFile(filePath);

		// Values
		string heightMapPath, diffuseMapPath, blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
		float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB, specularIntensity;
		bool isBlendMapped, isSpecular;

		// Load base data
		terrainFile >>
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
			isSpecular >>
			specularIntensity;

		// Perform empty string & space conversions
		heightMapPath = (heightMapPath == "?") ? "" : heightMapPath;
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		blendMapPath = (blendMapPath == "?") ? "?" : blendMapPath;
		blendMapPathR = (blendMapPathR == "?") ? "" : blendMapPathR;
		blendMapPathG = (blendMapPathG == "?") ? "" : blendMapPathG;
		blendMapPathB = (blendMapPathB == "?") ? "" : blendMapPathB;
		std::replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
		std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		std::replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
		std::replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
		std::replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
		std::replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

		// Close file
		terrainFile.close();

		// Add new terrain entity
		_loadTerrainEntity(heightMapPath);
		_fe3d.terrainEntity_setMaxHeight(_currentTerrainID, maxHeight);
		_fe3d.terrainEntity_setUvRepeat(_currentTerrainID, uvRepeat);
		_fe3d.terrainEntity_setBlendMapped(_currentTerrainID, isBlendMapped);
		_fe3d.terrainEntity_setLightness(_currentTerrainID, lightness);
		_fe3d.terrainEntity_setBlendRepeatR(_currentTerrainID, blendRepeatR);
		_fe3d.terrainEntity_setBlendRepeatG(_currentTerrainID, blendRepeatG);
		_fe3d.terrainEntity_setBlendRepeatB(_currentTerrainID, blendRepeatB);
		_fe3d.terrainEntity_setSpecularLighted(_currentTerrainID, isSpecular);
		_fe3d.terrainEntity_setSpecularLightingIntensity(_currentTerrainID, specularIntensity);
		if (diffuseMapPath != "") _fe3d.terrainEntity_setDiffuseMap(_currentTerrainID, diffuseMapPath);
		if (blendMapPath != "")   _fe3d.terrainEntity_setBlendMap(_currentTerrainID, blendMapPath);
		if (blendMapPathR != "")  _fe3d.terrainEntity_setBlendMapR(_currentTerrainID, blendMapPathR);
		if (blendMapPathG != "")  _fe3d.terrainEntity_setBlendMapG(_currentTerrainID, blendMapPathG);
		if (blendMapPathB != "")  _fe3d.terrainEntity_setBlendMapB(_currentTerrainID, blendMapPathB);

		// Logging
		_fe3d.logger_throwInfo("Terrain data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void WorldEditor::_saveTerrainData()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\terrain.fe3d";

		// Save terrain data
		if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
		{
			// Load file
			std::ofstream terrainFile(filePath);
			
			// Values
			string heightMapPath = _fe3d.terrainEntity_getHeightMapPath(_currentTerrainID);
			string diffuseMapPath = _fe3d.terrainEntity_getDiffuseMapPath(_currentTerrainID);
			string blendMapPath = _fe3d.terrainEntity_getBlendMapPath(_currentTerrainID);
			string blendMapPathR = _fe3d.terrainEntity_getBlendMapPathR(_currentTerrainID);
			string blendMapPathG = _fe3d.terrainEntity_getBlendMapPathG(_currentTerrainID);
			string blendMapPathB = _fe3d.terrainEntity_getBlendMapPathB(_currentTerrainID);
			float maxHeight = _fe3d.terrainEntity_getMaxHeight(_currentTerrainID);
			float uvRepeat = _fe3d.terrainEntity_getUvRepeat(_currentTerrainID);
			float lightness = _fe3d.terrainEntity_getLightness(_currentTerrainID);
			float specularIntensity = _fe3d.terrainEntity_getSpecularLightingIntensity(_currentTerrainID);
			float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(_currentTerrainID);
			float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(_currentTerrainID);
			float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(_currentTerrainID);
			bool isBlendMapped = _fe3d.terrainEntity_isBlendMapped(_currentTerrainID);
			bool isSpecular = _fe3d.terrainEntity_isSpecularLighted(_currentTerrainID);

			// Perform empty string & space conversions
			heightMapPath = (heightMapPath == "") ? "?" : heightMapPath;
			diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
			blendMapPath = (blendMapPath == "") ? "?" : blendMapPath;
			blendMapPathR = (blendMapPathR == "") ? "?" : blendMapPathR;
			blendMapPathG = (blendMapPathG == "") ? "?" : blendMapPathG;
			blendMapPathB = (blendMapPathB == "") ? "?" : blendMapPathB;
			std::replace(heightMapPath.begin(), heightMapPath.end(), ' ', '?');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			std::replace(blendMapPath.begin(), blendMapPath.end(), ' ', '?');
			std::replace(blendMapPathR.begin(), blendMapPathR.end(), ' ', '?');
			std::replace(blendMapPathG.begin(), blendMapPathG.end(), ' ', '?');
			std::replace(blendMapPathB.begin(), blendMapPathB.end(), ' ', '?');

			// Write terrain data to file
			terrainFile <<
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
				isSpecular << " " << 
				specularIntensity << std::endl;

			// Close file
			terrainFile.close();
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
		_fe3d.logger_throwInfo("Terrain data from project \"" + _currentProjectName + "\" saved!");
	}
}

void WorldEditor::_loadTerrainEntity(const string& heightMapPath)
{
	// Remove existing terrain entity
	if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
	{
		_fe3d.terrainEntity_delete(_currentTerrainID);
	}

	// Create new terrain entity
	_fe3d.terrainEntity_add(_currentTerrainID, heightMapPath);
	_fe3d.terrainEntity_select(_currentTerrainID);
	_fe3d.terrainEntity_hide(_currentTerrainID);
}