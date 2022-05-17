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

	for(const auto & skyId : _loadedSkyIds)
	{
		const auto rotation = _fe3d->sky_getRotation(skyId);
		const auto lightness = _fe3d->sky_getLightness(skyId);
		const auto color = _fe3d->sky_getColor(skyId);
		const auto rotationOrder = static_cast<int>(_fe3d->sky_getRotationOrder(skyId));

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
			<< endl;
	}

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
			<< endl;
	}

	for(const auto & waterId : _loadedWaterIds)
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

		auto dudvMapPath = _fe3d->water_getDudvMapPath(waterId);
		auto normalMapPath = _fe3d->water_getNormalMapPath(waterId);
		auto heightMapPath = _fe3d->water_getHeightMapPath(waterId);

		dudvMapPath = (dudvMapPath.empty() ? "" : dudvMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		heightMapPath = (heightMapPath.empty() ? "" : heightMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
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
			<< endl;
	}

	for(const auto & modelId : _loadedModelIds)
	{
		const auto partIds = _fe3d->model_getPartIds(modelId);
		const auto aabbIds = _fe3d->model_getChildAabbIds(modelId);
		const auto isMultiParted = _fe3d->model_isMultiParted(modelId);
		const auto modelSize = _fe3d->model_getBaseSize(modelId);
		const auto levelOfDetailDistance = _fe3d->model_getLevelOfDetailDistance(modelId);
		const auto rotationOrder = static_cast<int>(_fe3d->model_getRotationOrder(modelId));
		const auto isShadowed = _fe3d->model_isShadowed(modelId);
		const auto isReflected = _fe3d->model_isReflected(modelId);
		const auto isRefracted = _fe3d->model_isRefracted(modelId);

		auto meshPath = _fe3d->model_getMeshPath(modelId);
		auto levelOfDetailId = _fe3d->model_getLevelOfDetailId(modelId);

		meshPath = (meshPath.empty() ? "" : meshPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		meshPath = (meshPath.empty()) ? "?" : meshPath;
		levelOfDetailId = (levelOfDetailId.empty()) ? "?" : levelOfDetailId;

		replace(meshPath.begin(), meshPath.end(), ' ', '?');
		replace(levelOfDetailId.begin(), levelOfDetailId.end(), ' ', '?');

		file
			<< "MODEL "
			<< modelId
			<< " "
			<< meshPath
			<< " "
			<< modelSize.x
			<< " "
			<< modelSize.y
			<< " "
			<< modelSize.z
			<< " "
			<< levelOfDetailId
			<< " "
			<< levelOfDetailDistance
			<< " "
			<< rotationOrder
			<< " "
			<< isShadowed
			<< " "
			<< isReflected
			<< " "
			<< isRefracted
			<< endl;

		for(auto partId : partIds)
		{
			const auto isSpecular = _fe3d->model_isSpecular(modelId, partId);
			const auto specularShininess = _fe3d->model_getSpecularShininess(modelId, partId);
			const auto specularIntensity = _fe3d->model_getSpecularIntensity(modelId, partId);
			const auto reflectivity = _fe3d->model_getReflectivity(modelId, partId);
			const auto refractivity = _fe3d->model_getRefractivity(modelId, partId);
			const auto lightness = _fe3d->model_getLightness(modelId, partId);
			const auto color = _fe3d->model_getColor(modelId, partId);
			const auto textureRepeat = _fe3d->model_getTextureRepeat(modelId, partId);
			const auto isReflective = _fe3d->model_isReflective(modelId, partId);
			const auto isRefractive = _fe3d->model_isRefractive(modelId, partId);
			const auto reflectionType = static_cast<int>(_fe3d->model_getReflectionType(modelId, partId));
			const auto refractionType = static_cast<int>(_fe3d->model_getRefractionType(modelId, partId));
			const auto isFaceCulled = _fe3d->model_isFaceCulled(modelId, partId);
			const auto isBright = _fe3d->model_isBright(modelId, partId);
			const auto emissionIntensity = _fe3d->model_getEmissionIntensity(modelId, partId);
			const auto opacity = _fe3d->model_getOpacity(modelId, partId);
			const auto minTextureAlpha = _fe3d->model_getMinTextureAlpha(modelId, partId);

			auto diffuseMapPath = _fe3d->model_getDiffuseMapPath(modelId, partId);
			auto emissionMapPath = _fe3d->model_getEmissionMapPath(modelId, partId);
			auto specularMapPath = _fe3d->model_getSpecularMapPath(modelId, partId);
			auto reflectionMapPath = _fe3d->model_getReflectionMapPath(modelId, partId);
			auto refractionMapPath = _fe3d->model_getRefractionMapPath(modelId, partId);
			auto normalMapPath = _fe3d->model_getNormalMapPath(modelId, partId);

			diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			emissionMapPath = (emissionMapPath.empty() ? "" : emissionMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			specularMapPath = (specularMapPath.empty() ? "" : specularMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			reflectionMapPath = (reflectionMapPath.empty() ? "" : reflectionMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			refractionMapPath = (refractionMapPath.empty() ? "" : refractionMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			partId = (partId.empty()) ? "?" : partId;
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
			specularMapPath = (specularMapPath.empty()) ? "?" : specularMapPath;
			reflectionMapPath = (reflectionMapPath.empty()) ? "?" : reflectionMapPath;
			refractionMapPath = (refractionMapPath.empty()) ? "?" : refractionMapPath;
			normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
			replace(specularMapPath.begin(), specularMapPath.end(), ' ', '?');
			replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
			replace(refractionMapPath.begin(), refractionMapPath.end(), ' ', '?');
			replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');

			file
				<< "PART "
				<< modelId
				<< " "
				<< partId
				<< " "
				<< diffuseMapPath
				<< " "
				<< emissionMapPath
				<< " "
				<< specularMapPath
				<< " "
				<< reflectionMapPath
				<< " "
				<< refractionMapPath
				<< " "
				<< normalMapPath
				<< " "
				<< reflectionType
				<< " "
				<< refractionType
				<< " "
				<< isSpecular
				<< " "
				<< isReflective
				<< " "
				<< isRefractive
				<< " "
				<< specularShininess
				<< " "
				<< specularIntensity
				<< " "
				<< reflectivity
				<< " "
				<< refractivity
				<< " "
				<< lightness
				<< " "
				<< color.r
				<< " "
				<< color.g
				<< " "
				<< color.b
				<< " "
				<< textureRepeat
				<< " "
				<< isFaceCulled
				<< " "
				<< isBright
				<< " "
				<< emissionIntensity
				<< " "
				<< opacity
				<< " "
				<< minTextureAlpha
				<< endl;
		}

		for(const auto & aabbId : aabbIds)
		{
			const auto position = _fe3d->aabb_getLocalPosition(aabbId);
			const auto size = _fe3d->aabb_getLocalSize(aabbId);

			file
				<< "AABB "
				<< modelId
				<< " "
				<< aabbId
				<< " "
				<< position.x
				<< " "
				<< position.y
				<< " "
				<< position.z
				<< " "
				<< size.x
				<< " "
				<< size.y
				<< " "
				<< size.z
				<< endl;
		}
	}

	file.close();

	Logger::throwInfo("Custom world data saved");

	return true;
}