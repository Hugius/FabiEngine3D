#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool TerrainEditor::saveEntitiesToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\terrain.fe3d");

	for(const auto & terrainId : _loadedEntityIds)
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

		heightMapPath = (heightMapPath.empty() ? "" : heightMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		blendMapPath = (blendMapPath.empty() ? "" : blendMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		redDiffuseMapPath = (redDiffuseMapPath.empty() ? "" : redDiffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		greenDiffuseMapPath = (greenDiffuseMapPath.empty() ? "" : greenDiffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		blueDiffuseMapPath = (blueDiffuseMapPath.empty() ? "" : blueDiffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		redNormalMapPath = (redNormalMapPath.empty() ? "" : redNormalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		greenNormalMapPath = (greenNormalMapPath.empty() ? "" : greenNormalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		blueNormalMapPath = (blueNormalMapPath.empty() ? "" : blueNormalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));

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

		file
			<< terrainId
			<< " "
			<< heightMapPath
			<< " "
			<< diffuseMapPath
			<< " "
			<< blendMapPath
			<< " "
			<< redDiffuseMapPath
			<< " "
			<< greenDiffuseMapPath
			<< " "
			<< blueDiffuseMapPath
			<< " "
			<< normalMapPath
			<< " "
			<< redNormalMapPath
			<< " "
			<< greenNormalMapPath
			<< " "
			<< blueNormalMapPath
			<< " "
			<< maxHeight
			<< " "
			<< textureRepeat
			<< " "
			<< lightness
			<< " "
			<< redTextureRepeat
			<< " "
			<< greenTextureRepeat
			<< " "
			<< blueTextureRepeat
			<< " "
			<< isSpecular
			<< " "
			<< specularShininess
			<< " "
			<< specularIntensity
			<< endl;
	}

	file.close();

	Logger::throwInfo("Terrain editor data saved");

	return true;
}