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

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("TerrainEditor::saveTerrainEntitiesToFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
														 ("game\\" + _currentProjectID)) + "\\data\\terrain.fe3d";

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