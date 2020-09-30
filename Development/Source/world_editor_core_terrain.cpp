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
		float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB;
		bool isBlendMapped;

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
			blendRepeatB;

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
		_fe3d.terrainEntity_setMaxHeight("@terrain", maxHeight);
		_fe3d.terrainEntity_setUvRepeat("@terrain", uvRepeat);
		_fe3d.terrainEntity_setBlendMapped("@terrain", isBlendMapped);
		_fe3d.terrainEntity_setLightness("@terrain", lightness);
		_fe3d.terrainEntity_setBlendRepeatR("@terrain", blendRepeatR);
		_fe3d.terrainEntity_setBlendRepeatG("@terrain", blendRepeatG);
		_fe3d.terrainEntity_setBlendRepeatB("@terrain", blendRepeatB);
		if (diffuseMapPath != "") _fe3d.terrainEntity_setDiffuseMap("@terrain", diffuseMapPath);
		if (blendMapPath != "")   _fe3d.terrainEntity_setBlendMap("@terrain", blendMapPath);
		if (blendMapPathR != "")  _fe3d.terrainEntity_setBlendMapR("@terrain", blendMapPathR);
		if (blendMapPathG != "")  _fe3d.terrainEntity_setBlendMapG("@terrain", blendMapPathG);
		if (blendMapPathB != "")  _fe3d.terrainEntity_setBlendMapB("@terrain", blendMapPathB);

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
		if (_fe3d.terrainEntity_isExisting("@terrain"))
		{
			// Load file
			std::ofstream terrainFile(filePath);
			
			// Values
			string heightMapPath = _fe3d.terrainEntity_getHeightMapPath("@terrain");
			string diffuseMapPath = _fe3d.terrainEntity_getDiffuseMapPath("@terrain");
			string blendMapPath = _fe3d.terrainEntity_getBlendMapPath("@terrain");
			string blendMapPathR = _fe3d.terrainEntity_getBlendMapPathR("@terrain");
			string blendMapPathG = _fe3d.terrainEntity_getBlendMapPathG("@terrain");
			string blendMapPathB = _fe3d.terrainEntity_getBlendMapPathB("@terrain");
			float maxHeight = _fe3d.terrainEntity_getMaxHeight("@terrain");
			float uvRepeat = _fe3d.terrainEntity_getUvRepeat("@terrain");
			float lightness = _fe3d.terrainEntity_getLightness("@terrain");
			float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR("@terrain");
			float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG("@terrain");
			float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB("@terrain");
			bool isBlendMapped = _fe3d.terrainEntity_isBlendMapped("@terrain");

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
				blendRepeatB << std::endl;

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
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_delete("@terrain");
	}

	// Create new terrain entity
	_fe3d.terrainEntity_add("@terrain", heightMapPath);
	_fe3d.terrainEntity_select("@terrain");
	_fe3d.terrainEntity_hide("@terrain");
}