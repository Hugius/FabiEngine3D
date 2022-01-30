#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool TerrainEditor::saveToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\terrain.fe3d");

	for(const auto& terrainId : _loadedTerrainIds)
	{
		auto heightMapPath = _fe3d->terrain_getHeightMapPath(terrainId);
		auto diffuseMapPath = _fe3d->terrain_getDiffuseMapPath(terrainId);
		auto normalMapPath = _fe3d->terrain_getNormalMapPath(terrainId);
		auto blendMapPath = _fe3d->terrain_getBlendMapPath(terrainId);
		auto redDiffuseMapPath = _fe3d->terrain_getRedDiffuseMapPath(terrainId);
		auto greenDiffuseMapPath = _fe3d->terrain_getGreenDiffuseMapPath(terrainId);
		auto blueDiffuseMapPath = _fe3d->terrain_getBlueDiffuseMapPath(terrainId);
		auto redNormalMapPath = _fe3d->terrain_getRedNormalMapPath(terrainId);
		auto greenNormalMapPath = _fe3d->terrain_getGreenNormalMapPath(terrainId);
		auto blueNormalMapPath = _fe3d->terrain_getBlueNormalMapPath(terrainId);
		auto maxHeight = _fe3d->terrain_getMaxHeight(terrainId);
		auto textureRepeat = _fe3d->terrain_getTextureRepeat(terrainId);
		auto lightness = _fe3d->terrain_getLightness(terrainId);
		auto specularShininess = _fe3d->terrain_getSpecularShininess(terrainId);
		auto specularIntensity = _fe3d->terrain_getSpecularIntensity(terrainId);
		auto redTextureRepeat = _fe3d->terrain_getRedTextureRepeat(terrainId);
		auto greenTextureRepeat = _fe3d->terrain_getGreenTextureRepeat(terrainId);
		auto blueTextureRepeat = _fe3d->terrain_getBlueTextureRepeat(terrainId);
		auto isSpecular = _fe3d->terrain_isSpecular(terrainId);

		heightMapPath = string(heightMapPath.empty() ? "" : heightMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		blendMapPath = string(blendMapPath.empty() ? "" : blendMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		redDiffuseMapPath = string(redDiffuseMapPath.empty() ? "" : redDiffuseMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		greenDiffuseMapPath = string(greenDiffuseMapPath.empty() ? "" : greenDiffuseMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		blueDiffuseMapPath = string(blueDiffuseMapPath.empty() ? "" : blueDiffuseMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		redNormalMapPath = string(redNormalMapPath.empty() ? "" : redNormalMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		greenNormalMapPath = string(greenNormalMapPath.empty() ? "" : greenNormalMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
		blueNormalMapPath = string(blueNormalMapPath.empty() ? "" : blueNormalMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));

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

		file <<
			terrainId << " " <<
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

	file.close();

	Logger::throwInfo("Terrain editor data saved!");

	return true;
}