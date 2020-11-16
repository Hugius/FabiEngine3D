#include "world_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void WorldEditor::loadTerrainEntities()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded!");
	}

	// Clear names list from previous loads
	_terrainNames.clear();

	// Compose full terrain file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\terrain.fe3d";

	// Check if terrain file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read sky data
		while (std::getline(file, line))
		{
			stringstream iss(line);

			// Values
			string name, heightMapPath, diffuseMapPath, blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
			float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB, specularIntensity;
			bool isBlendMapped, isSpecular;

			// Load base data
			iss >>
				name >>
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

			// Add new terrain entity
			_terrainNames.push_back(name);
			if (heightMapPath != "")
			{
				_fe3d.terrainEntity_add(name, heightMapPath);
				_fe3d.terrainEntity_setMaxHeight(name, maxHeight);
				_fe3d.terrainEntity_setUvRepeat(name, uvRepeat);
				_fe3d.terrainEntity_setBlendMapped(name, isBlendMapped);
				_fe3d.terrainEntity_setLightness(name, lightness);
				_fe3d.terrainEntity_setBlendRepeatR(name, blendRepeatR);
				_fe3d.terrainEntity_setBlendRepeatG(name, blendRepeatG);
				_fe3d.terrainEntity_setBlendRepeatB(name, blendRepeatB);
				_fe3d.terrainEntity_setSpecularLighted(name, isSpecular);
				_fe3d.terrainEntity_setSpecularLightingIntensity(name, specularIntensity);
				if (diffuseMapPath != "") _fe3d.terrainEntity_setDiffuseMap(name, diffuseMapPath);
				if (blendMapPath != "")   _fe3d.terrainEntity_setBlendMap(name, blendMapPath);
				if (blendMapPathR != "")  _fe3d.terrainEntity_setBlendMapR(name, blendMapPathR);
				if (blendMapPathG != "")  _fe3d.terrainEntity_setBlendMapG(name, blendMapPathG);
				if (blendMapPathB != "")  _fe3d.terrainEntity_setBlendMapB(name, blendMapPathB);
			}
		}

		// Close file
		file.close();

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

		// Compose full terrain file path
		string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\terrain.fe3d";

		// Load file
		std::ofstream file(filePath);
			
		// Write every terrain to file
		for (auto& name : _terrainNames)
		{
			// Values
			string heightMapPath = _fe3d.terrainEntity_getHeightMapPath(name);
			string diffuseMapPath = _fe3d.terrainEntity_getDiffuseMapPath(name);
			string blendMapPath = _fe3d.terrainEntity_getBlendMapPath(name);
			string blendMapPathR = _fe3d.terrainEntity_getBlendMapPathR(name);
			string blendMapPathG = _fe3d.terrainEntity_getBlendMapPathG(name);
			string blendMapPathB = _fe3d.terrainEntity_getBlendMapPathB(name);
			float maxHeight = _fe3d.terrainEntity_getMaxHeight(name);
			float uvRepeat = _fe3d.terrainEntity_getUvRepeat(name);
			float lightness = _fe3d.terrainEntity_getLightness(name);
			float specularIntensity = _fe3d.terrainEntity_getSpecularLightingIntensity(name);
			float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(name);
			float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(name);
			float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(name);
			bool isBlendMapped = _fe3d.terrainEntity_isBlendMapped(name);
			bool isSpecular = _fe3d.terrainEntity_isSpecularLighted(name);

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
			file <<
				name << " " <<
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
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Terrain data from project \"" + _currentProjectName + "\" saved!");
	}
}