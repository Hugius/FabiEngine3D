#include "custom_world_builder.hpp"
#include "tools.hpp"
#include "configuration.hpp"
#include "logger.hpp"

using std::ofstream;
using std::endl;

const bool CustomWorldBuilder::saveWorldToFile(const string & fileName) const
{
	if(_currentProjectId.empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "worlds\\custom\\" + fileName + ".fe3d");

	auto file = ofstream(filePath);

	for(const auto & skyId : _addedSkyIds)
	{
		const auto rotation = _fe3d->sky_getRotation(skyId);
		const auto lightness = _fe3d->sky_getLightness(skyId);
		const auto color = _fe3d->sky_getColor(skyId);
		const auto rotationOrder = static_cast<int>(_fe3d->sky_getRotationOrder(skyId));
		const auto isWireframed = _fe3d->sky_isWireframed(skyId);
		const auto wireframeColor = _fe3d->sky_getWireframeColor(skyId);
		const auto isSelected = (skyId == _fe3d->sky_getSelectedId());

		auto cubeMapPaths = _fe3d->sky_getCubeMapPaths(skyId);

		for(auto & cubeMapPath : cubeMapPaths)
		{
			cubeMapPath = (cubeMapPath.empty() ? "" : cubeMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			cubeMapPath = (cubeMapPath.empty()) ? "?" : cubeMapPath;

			replace(cubeMapPath.begin(), cubeMapPath.end(), ' ', '?');
		}

		file
			<< skyId
			<< " ";

		for(const auto & cubeMapPath : cubeMapPaths)
		{
			file
				<< cubeMapPath
				<< " ";
		}

		file
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< lightness
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< rotationOrder
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< isSelected
			<< endl;
	}

	for(const auto & terrainId : _addedTerrainIds)
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
		const auto isWireframed = _fe3d->terrain_isWireframed(terrainId);
		const auto wireframeColor = _fe3d->terrain_getWireframeColor(terrainId);
		const auto minClipPosition = _fe3d->terrain_getMinClipPosition(terrainId);
		const auto maxClipPosition = _fe3d->terrain_getMaxClipPosition(terrainId);
		const auto isSelected = (terrainId == _fe3d->terrain_getSelectedId());

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

		heightMapPath = (heightMapPath.empty() ? "" : heightMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		blendMapPath = (blendMapPath.empty() ? "" : blendMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		redDiffuseMapPath = (redDiffuseMapPath.empty() ? "" : redDiffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		greenDiffuseMapPath = (greenDiffuseMapPath.empty() ? "" : greenDiffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		blueDiffuseMapPath = (blueDiffuseMapPath.empty() ? "" : blueDiffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		redNormalMapPath = (redNormalMapPath.empty() ? "" : redNormalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		greenNormalMapPath = (greenNormalMapPath.empty() ? "" : greenNormalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		blueNormalMapPath = (blueNormalMapPath.empty() ? "" : blueNormalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
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
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< minClipPosition.x
			<< " "
			<< minClipPosition.y
			<< " "
			<< minClipPosition.z
			<< " "
			<< maxClipPosition.x
			<< " "
			<< maxClipPosition.y
			<< " "
			<< maxClipPosition.z
			<< " "
			<< isSelected
			<< endl;
	}

	for(const auto & waterId : _addedWaterIds)
	{
		const auto color = _fe3d->water_getColor(waterId);
		const auto rippleSpeed = _fe3d->water_getRippleSpeed(waterId);
		const auto waveSpeed = _fe3d->water_getWaveSpeed(waterId);
		const auto size = _fe3d->water_getSize(waterId);
		const auto textureRepeat = _fe3d->water_getTextureRepeat(waterId);
		const auto waveHeight = _fe3d->water_getWaveHeight(waterId);
		const auto maxDepth = _fe3d->water_getMaxDepth(waterId);
		const auto isEdged = _fe3d->water_isEdged(waterId);
		const auto specularShininess = _fe3d->water_getSpecularShininess(waterId);
		const auto specularIntensity = _fe3d->water_getSpecularIntensity(waterId);
		const auto isSpecular = _fe3d->water_isSpecular(waterId);
		const auto isReflective = _fe3d->water_isReflective(waterId);
		const auto isRefractive = _fe3d->water_isRefractive(waterId);
		const auto height = _fe3d->water_getHeight(waterId);
		const auto isWireframed = _fe3d->water_isWireframed(waterId);
		const auto wireframeColor = _fe3d->water_getWireframeColor(waterId);
		const auto minClipPosition = _fe3d->water_getMinClipPosition(waterId);
		const auto maxClipPosition = _fe3d->water_getMaxClipPosition(waterId);
		const auto isSelected = (waterId == _fe3d->water_getSelectedId());

		auto dudvMapPath = _fe3d->water_getDudvMapPath(waterId);
		auto normalMapPath = _fe3d->water_getNormalMapPath(waterId);
		auto heightMapPath = _fe3d->water_getHeightMapPath(waterId);

		dudvMapPath = (dudvMapPath.empty() ? "" : dudvMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		heightMapPath = (heightMapPath.empty() ? "" : heightMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		dudvMapPath = (dudvMapPath.empty() ? "?" : dudvMapPath);
		normalMapPath = (normalMapPath.empty() ? "?" : normalMapPath);
		heightMapPath = (heightMapPath.empty() ? "?" : heightMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(heightMapPath.begin(), heightMapPath.end(), ' ', '?');

		file
			<< waterId
			<< " "
			<< dudvMapPath
			<< " "
			<< normalMapPath
			<< " "
			<< heightMapPath
			<< " "
			<< isSpecular
			<< " "
			<< isReflective
			<< " "
			<< isRefractive
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< size
			<< " "
			<< textureRepeat
			<< " "
			<< waveHeight
			<< " "
			<< rippleSpeed.x
			<< " "
			<< rippleSpeed.y
			<< " "
			<< waveSpeed.x
			<< " "
			<< waveSpeed.y
			<< " "
			<< isEdged
			<< " "
			<< specularShininess
			<< " "
			<< specularIntensity
			<< " "
			<< maxDepth
			<< " "
			<< height
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< minClipPosition.x
			<< " "
			<< minClipPosition.y
			<< " "
			<< minClipPosition.z
			<< " "
			<< maxClipPosition.x
			<< " "
			<< maxClipPosition.y
			<< " "
			<< maxClipPosition.z
			<< " "
			<< isSelected
			<< endl;
	}

	file.close();

	Logger::throwInfo("Custom world data saved");

	return true;
}