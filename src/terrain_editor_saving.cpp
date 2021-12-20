#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool TerrainEditor::saveToFile() const
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
		auto redDiffuseMapPath = _fe3d.terrain_getRedDiffuseMapPath(terrainID);
		auto greenDiffuseMapPath = _fe3d.terrain_getGreenDiffuseMapPath(terrainID);
		auto blueDiffuseMapPath = _fe3d.terrain_getBlueDiffuseMapPath(terrainID);
		auto redNormalMapPath = _fe3d.terrain_getRedNormalMapPath(terrainID);
		auto greenNormalMapPath = _fe3d.terrain_getGreenNormalMapPath(terrainID);
		auto blueNormalMapPath = _fe3d.terrain_getBlueNormalMapPath(terrainID);
		auto maxHeight = _fe3d.terrain_getMaxHeight(terrainID);
		auto textureRepeat = _fe3d.terrain_getTextureRepeat(terrainID);
		auto lightness = _fe3d.terrain_getLightness(terrainID);
		auto specularShininess = _fe3d.terrain_getSpecularShininess(terrainID);
		auto specularIntensity = _fe3d.terrain_getSpecularIntensity(terrainID);
		auto redTextureRepeat = _fe3d.terrain_getRedTextureRepeat(terrainID);
		auto greenTextureRepeat = _fe3d.terrain_getGreenTextureRepeat(terrainID);
		auto blueTextureRepeat = _fe3d.terrain_getBlueTextureRepeat(terrainID);
		auto isSpecular = _fe3d.terrain_isSpecular(terrainID);

		// Convert to short path
		heightMapPath = string(heightMapPath.empty() ? "" : heightMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		blendMapPath = string(blendMapPath.empty() ? "" : blendMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		redDiffuseMapPath = string(redDiffuseMapPath.empty() ? "" : redDiffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		greenDiffuseMapPath = string(greenDiffuseMapPath.empty() ? "" : greenDiffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		blueDiffuseMapPath = string(blueDiffuseMapPath.empty() ? "" : blueDiffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		redNormalMapPath = string(redNormalMapPath.empty() ? "" : redNormalMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		greenNormalMapPath = string(greenNormalMapPath.empty() ? "" : greenNormalMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
		blueNormalMapPath = string(blueNormalMapPath.empty() ? "" : blueNormalMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		// Convert empty string
		heightMapPath = (heightMapPath.empty()) ? "?" : heightMapPath;
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;
		blendMapPath = (blendMapPath.empty()) ? "?" : blendMapPath;
		redDiffuseMapPath = (redDiffuseMapPath.empty()) ? "?" : redDiffuseMapPath;
		greenDiffuseMapPath = (greenDiffuseMapPath.empty()) ? "?" : greenDiffuseMapPath;
		blueDiffuseMapPath = (blueDiffuseMapPath.empty()) ? "?" : blueDiffuseMapPath;
		redNormalMapPath = (redNormalMapPath.empty()) ? "?" : redNormalMapPath;
		greenNormalMapPath = (greenNormalMapPath.empty()) ? "?" : greenNormalMapPath;
		blueNormalMapPath = (blueNormalMapPath.empty()) ? "?" : blueNormalMapPath;

		// Convert spaces
		replace(heightMapPath.begin(), heightMapPath.end(), ' ', '?');
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(blendMapPath.begin(), blendMapPath.end(), ' ', '?');
		replace(redDiffuseMapPath.begin(), redDiffuseMapPath.end(), ' ', '?');
		replace(greenDiffuseMapPath.begin(), greenDiffuseMapPath.end(), ' ', '?');
		replace(blueDiffuseMapPath.begin(), blueDiffuseMapPath.end(), ' ', '?');
		replace(redNormalMapPath.begin(), redNormalMapPath.end(), ' ', '?');
		replace(greenNormalMapPath.begin(), greenNormalMapPath.end(), ' ', '?');
		replace(blueNormalMapPath.begin(), blueNormalMapPath.end(), ' ', '?');

		// Write terrain data to file
		file <<
			terrainID << " " <<
			heightMapPath << " " <<
			diffuseMapPath << " " <<
			maxHeight << " " <<
			textureRepeat << " " <<
			lightness << " " <<
			blendMapPath << " " <<
			redDiffuseMapPath << " " <<
			greenDiffuseMapPath << " " <<
			blueDiffuseMapPath << " " <<
			redTextureRepeat << " " <<
			greenTextureRepeat << " " <<
			blueTextureRepeat << " " <<
			normalMapPath << " " <<
			redNormalMapPath << " " <<
			greenNormalMapPath << " " <<
			blueNormalMapPath << " " <<
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