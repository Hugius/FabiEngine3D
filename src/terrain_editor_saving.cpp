#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool TerrainEditor::saveTerrainEntitiesToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\terrain.fe3d");

	// Write terrain data
	for(const auto& terrainID : _loadedTerrainIDs)
	{
		// Values
		auto heightMapPath = _fe3d.terrain_getHeightMapPath(terrainID);
		auto diffuseMapPath = _fe3d.terrain_getDiffuseMapPath(terrainID);
		auto normalMapPath = _fe3d.terrain_getNormalMapPath(terrainID);
		auto blendMapPath = _fe3d.terrain_getBlendMapPath(terrainID);
		auto blendMapPathR = _fe3d.terrain_getDiffuseMapPathR(terrainID);
		auto blendMapPathG = _fe3d.terrain_getDiffuseMapPathG(terrainID);
		auto blendMapPathB = _fe3d.terrain_getDiffuseMapPathB(terrainID);
		auto normalMapPathR = _fe3d.terrain_getNormalMapPathR(terrainID);
		auto normalMapPathG = _fe3d.terrain_getNormalMapPathG(terrainID);
		auto normalMapPathB = _fe3d.terrain_getNormalMapPathB(terrainID);
		auto maxHeight = _fe3d.terrain_getMaxHeight(terrainID);
		auto textureRepeat = _fe3d.terrain_getTextureRepeat(terrainID);
		auto lightness = _fe3d.terrain_getLightness(terrainID);
		auto specularShininess = _fe3d.terrain_getSpecularShininess(terrainID);
		auto specularIntensity = _fe3d.terrain_getSpecularIntensity(terrainID);
		auto redRepeat = _fe3d.terrain_getRedRepeat(terrainID);
		auto greenRepeat = _fe3d.terrain_getGreenRepeat(terrainID);
		auto blueRepeat = _fe3d.terrain_getBlueRepeat(terrainID);
		auto isSpecular = _fe3d.terrain_isSpecular(terrainID);

		// Convert to short path
		heightMapPath = string(heightMapPath.empty() ? "" : heightMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		blendMapPath = string(blendMapPath.empty() ? "" : blendMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		blendMapPathR = string(blendMapPathR.empty() ? "" : blendMapPathR.substr(string("projects\\" + _currentProjectID + "\\").size()));
		blendMapPathG = string(blendMapPathG.empty() ? "" : blendMapPathG.substr(string("projects\\" + _currentProjectID + "\\").size()));
		blendMapPathB = string(blendMapPathB.empty() ? "" : blendMapPathB.substr(string("projects\\" + _currentProjectID + "\\").size()));
		normalMapPathR = string(normalMapPathR.empty() ? "" : normalMapPathR.substr(string("projects\\" + _currentProjectID + "\\").size()));
		normalMapPathG = string(normalMapPathG.empty() ? "" : normalMapPathG.substr(string("projects\\" + _currentProjectID + "\\").size()));
		normalMapPathB = string(normalMapPathB.empty() ? "" : normalMapPathB.substr(string("projects\\" + _currentProjectID + "\\").size()));

		// Convert empty string
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

		// Convert spaces
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
	Logger::throwInfo("Terrain data saved!");

	// Return
	return true;
}