#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool TerrainEditor::saveTerrainsToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\domain\\terrain.fe3d");

	auto file = ofstream(filePath);

	for(const auto & terrainId : _loadedTerrainIds)
	{
		const auto maxHeight = _fe3d->terrain_getMaxHeight(terrainId);
		const auto textureRepeat = _fe3d->terrain_getTextureRepeat(terrainId);
		const auto lightness = _fe3d->terrain_getLightness(terrainId);
		const auto color = _fe3d->terrain_getColor(terrainId);
		const auto specularShininess = _fe3d->terrain_getSpecularShininess(terrainId);
		const auto specularIntensity = _fe3d->terrain_getSpecularIntensity(terrainId);
		const auto redTextureRepeat = _fe3d->terrain_getRedTextureRepeat(terrainId);
		const auto greenTextureRepeat = _fe3d->terrain_getGreenTextureRepeat(terrainId);
		const auto blueTextureRepeat = _fe3d->terrain_getBlueTextureRepeat(terrainId);
		const auto isSpecular = _fe3d->terrain_isSpecular(terrainId);
		const auto isShadowed = _fe3d->terrain_isShadowed(terrainId);

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

		if(!heightMapPath.empty())
		{
			heightMapPath = heightMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!diffuseMapPath.empty())
		{
			diffuseMapPath = diffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!normalMapPath.empty())
		{
			normalMapPath = normalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!blendMapPath.empty())
		{
			blendMapPath = blendMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!redDiffuseMapPath.empty())
		{
			redDiffuseMapPath = redDiffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!greenDiffuseMapPath.empty())
		{
			greenDiffuseMapPath = greenDiffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!blueDiffuseMapPath.empty())
		{
			blueDiffuseMapPath = blueDiffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!redNormalMapPath.empty())
		{
			redNormalMapPath = redNormalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!greenNormalMapPath.empty())
		{
			greenNormalMapPath = greenNormalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!blueNormalMapPath.empty())
		{
			blueNormalMapPath = blueNormalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

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
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
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
			<< " "
			<< isShadowed
			<< endl;
	}

	file.close();

	Logger::throwInfo("Terrain editor data saved");

	return true;
}