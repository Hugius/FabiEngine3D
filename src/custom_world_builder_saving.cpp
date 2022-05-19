#include "custom_world_builder.hpp"
#include "tools.hpp"
#include "configuration.hpp"
#include "logger.hpp"

using std::ofstream;
using std::endl;

void CustomWorldBuilder::saveWorldToFile(const string & fileName)
{
	if(!Configuration::getInst().isApplicationExported() && _currentProjectId.empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "worlds\\custom\\" + fileName + ".fe3d");

	auto file = ofstream(filePath);

	for(const auto & [placedSkyId, templateSkyId] : _addedSkyIds)
	{
		const auto rotation = _fe3d->sky_getRotation(placedSkyId);
		const auto lightness = _fe3d->sky_getLightness(placedSkyId);
		const auto color = _fe3d->sky_getColor(placedSkyId);
		const auto rotationOrder = static_cast<int>(_fe3d->sky_getRotationOrder(placedSkyId));
		const auto isWireframed = _fe3d->sky_isWireframed(placedSkyId);
		const auto wireframeColor = _fe3d->sky_getWireframeColor(placedSkyId);
		const auto isSelected = (placedSkyId == _fe3d->sky_getSelectedId());

		auto cubeMapPaths = _fe3d->sky_getCubeMapPaths(placedSkyId);

		for(auto & cubeMapPath : cubeMapPaths)
		{
			cubeMapPath = (cubeMapPath.empty() ? "" : cubeMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			cubeMapPath = (cubeMapPath.empty()) ? "?" : cubeMapPath;

			replace(cubeMapPath.begin(), cubeMapPath.end(), ' ', '?');
		}

		file
			<< "SKY "
			<< placedSkyId
			<< " "
			<< templateSkyId;

		for(const auto & cubeMapPath : cubeMapPaths)
		{
			file
				<< " "
				<< cubeMapPath;
		}

		file
			<< " "
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

	for(const auto & [placedTerrainId, templateTerrainId] : _addedTerrainIds)
	{
		const auto maxHeight = _fe3d->terrain_getMaxHeight(placedTerrainId);
		const auto textureRepeat = _fe3d->terrain_getTextureRepeat(placedTerrainId);
		const auto lightness = _fe3d->terrain_getLightness(placedTerrainId);
		const auto color = _fe3d->terrain_getColor(placedTerrainId);
		const auto specularShininess = _fe3d->terrain_getSpecularShininess(placedTerrainId);
		const auto specularIntensity = _fe3d->terrain_getSpecularIntensity(placedTerrainId);
		const auto redTextureRepeat = _fe3d->terrain_getRedTextureRepeat(placedTerrainId);
		const auto greenTextureRepeat = _fe3d->terrain_getGreenTextureRepeat(placedTerrainId);
		const auto blueTextureRepeat = _fe3d->terrain_getBlueTextureRepeat(placedTerrainId);
		const auto isSpecular = _fe3d->terrain_isSpecular(placedTerrainId);
		const auto isWireframed = _fe3d->terrain_isWireframed(placedTerrainId);
		const auto wireframeColor = _fe3d->terrain_getWireframeColor(placedTerrainId);
		const auto minClipPosition = _fe3d->terrain_getMinClipPosition(placedTerrainId);
		const auto maxClipPosition = _fe3d->terrain_getMaxClipPosition(placedTerrainId);
		const auto isSelected = (placedTerrainId == _fe3d->terrain_getSelectedId());

		auto diffuseMapPath = _fe3d->terrain_getDiffuseMapPath(placedTerrainId);
		auto normalMapPath = _fe3d->terrain_getNormalMapPath(placedTerrainId);
		auto blendMapPath = _fe3d->terrain_getBlendMapPath(placedTerrainId);
		auto redDiffuseMapPath = _fe3d->terrain_getRedDiffuseMapPath(placedTerrainId);
		auto greenDiffuseMapPath = _fe3d->terrain_getGreenDiffuseMapPath(placedTerrainId);
		auto blueDiffuseMapPath = _fe3d->terrain_getBlueDiffuseMapPath(placedTerrainId);
		auto redNormalMapPath = _fe3d->terrain_getRedNormalMapPath(placedTerrainId);
		auto greenNormalMapPath = _fe3d->terrain_getGreenNormalMapPath(placedTerrainId);
		auto blueNormalMapPath = _fe3d->terrain_getBlueNormalMapPath(placedTerrainId);

		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		blendMapPath = (blendMapPath.empty() ? "" : blendMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		redDiffuseMapPath = (redDiffuseMapPath.empty() ? "" : redDiffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		greenDiffuseMapPath = (greenDiffuseMapPath.empty() ? "" : greenDiffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		blueDiffuseMapPath = (blueDiffuseMapPath.empty() ? "" : blueDiffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		redNormalMapPath = (redNormalMapPath.empty() ? "" : redNormalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		greenNormalMapPath = (greenNormalMapPath.empty() ? "" : greenNormalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		blueNormalMapPath = (blueNormalMapPath.empty() ? "" : blueNormalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;
		blendMapPath = (blendMapPath.empty()) ? "?" : blendMapPath;
		redDiffuseMapPath = (redDiffuseMapPath.empty()) ? "?" : redDiffuseMapPath;
		greenDiffuseMapPath = (greenDiffuseMapPath.empty()) ? "?" : greenDiffuseMapPath;
		blueDiffuseMapPath = (blueDiffuseMapPath.empty()) ? "?" : blueDiffuseMapPath;
		redNormalMapPath = (redNormalMapPath.empty()) ? "?" : redNormalMapPath;
		greenNormalMapPath = (greenNormalMapPath.empty()) ? "?" : greenNormalMapPath;
		blueNormalMapPath = (blueNormalMapPath.empty()) ? "?" : blueNormalMapPath;

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
			<< "TERRAIN "
			<< placedTerrainId
			<< " "
			<< templateTerrainId
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

	for(const auto & [placedWaterId, templateWaterId] : _addedWaterIds)
	{
		const auto color = _fe3d->water_getColor(placedWaterId);
		const auto rippleSpeed = _fe3d->water_getRippleSpeed(placedWaterId);
		const auto waveSpeed = _fe3d->water_getWaveSpeed(placedWaterId);
		const auto size = _fe3d->water_getSize(placedWaterId);
		const auto textureRepeat = _fe3d->water_getTextureRepeat(placedWaterId);
		const auto waveHeight = _fe3d->water_getWaveHeight(placedWaterId);
		const auto maxDepth = _fe3d->water_getMaxDepth(placedWaterId);
		const auto isEdged = _fe3d->water_isEdged(placedWaterId);
		const auto specularShininess = _fe3d->water_getSpecularShininess(placedWaterId);
		const auto specularIntensity = _fe3d->water_getSpecularIntensity(placedWaterId);
		const auto isSpecular = _fe3d->water_isSpecular(placedWaterId);
		const auto isReflective = _fe3d->water_isReflective(placedWaterId);
		const auto isRefractive = _fe3d->water_isRefractive(placedWaterId);
		const auto height = _fe3d->water_getHeight(placedWaterId);
		const auto isWireframed = _fe3d->water_isWireframed(placedWaterId);
		const auto wireframeColor = _fe3d->water_getWireframeColor(placedWaterId);
		const auto minClipPosition = _fe3d->water_getMinClipPosition(placedWaterId);
		const auto maxClipPosition = _fe3d->water_getMaxClipPosition(placedWaterId);
		const auto isSelected = (placedWaterId == _fe3d->water_getSelectedId());

		auto dudvMapPath = _fe3d->water_getDudvMapPath(placedWaterId);
		auto normalMapPath = _fe3d->water_getNormalMapPath(placedWaterId);
		auto heightMapPath = _fe3d->water_getHeightMapPath(placedWaterId);

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
			<< "WATER "
			<< placedWaterId
			<< " "
			<< templateWaterId
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

	for(const auto & [placedModelId, templateModelId] : _addedModelIds)
	{
		const auto partIds = _fe3d->model_getPartIds(placedModelId);
		const auto aabbIds = _fe3d->model_getChildAabbIds(placedModelId);
		const auto animation3dIds = _fe3d->model_getAnimation3dIds(placedModelId);
		const auto position = _fe3d->model_getBasePosition(placedModelId);
		const auto rotation = _fe3d->model_getBaseRotation(placedModelId);
		const auto rotationOrigin = _fe3d->model_getBaseRotationOrigin(placedModelId);
		const auto size = _fe3d->model_getBaseSize(placedModelId);
		const auto levelOfDetailDistance = _fe3d->model_getLevelOfDetailDistance(placedModelId);
		const auto rotationOrder = static_cast<int>(_fe3d->model_getRotationOrder(placedModelId));
		const auto isShadowed = _fe3d->model_isShadowed(placedModelId);
		const auto isReflected = _fe3d->model_isReflected(placedModelId);
		const auto isRefracted = _fe3d->model_isRefracted(placedModelId);
		const auto minClipPosition = _fe3d->model_getMinClipPosition(placedModelId);
		const auto maxClipPosition = _fe3d->model_getMaxClipPosition(placedModelId);
		const auto isVisible = _fe3d->model_isVisible(placedModelId);
		const auto isFrozen = _fe3d->model_isFrozen(placedModelId);

		auto levelOfDetailId = _fe3d->model_getLevelOfDetailId(placedModelId);

		levelOfDetailId = (levelOfDetailId.empty()) ? "?" : levelOfDetailId;

		file
			<< "MODEL "
			<< placedModelId
			<< " "
			<< templateModelId
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
			<< " "
			<< isVisible
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< rotationOrigin.x
			<< " "
			<< rotationOrigin.y
			<< " "
			<< rotationOrigin.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< size.z
			<< " "
			<< isFrozen
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
			<< endl;

		for(auto partId : partIds)
		{
			const auto position = _fe3d->model_getPartPosition(placedModelId, partId);
			const auto rotation = _fe3d->model_getPartRotation(placedModelId, partId);
			const auto rotationOrigin = _fe3d->model_getPartRotationOrigin(placedModelId, partId);
			const auto size = _fe3d->model_getPartSize(placedModelId, partId);
			const auto isSpecular = _fe3d->model_isSpecular(placedModelId, partId);
			const auto specularShininess = _fe3d->model_getSpecularShininess(placedModelId, partId);
			const auto specularIntensity = _fe3d->model_getSpecularIntensity(placedModelId, partId);
			const auto reflectivity = _fe3d->model_getReflectivity(placedModelId, partId);
			const auto refractivity = _fe3d->model_getRefractivity(placedModelId, partId);
			const auto lightness = _fe3d->model_getLightness(placedModelId, partId);
			const auto color = _fe3d->model_getColor(placedModelId, partId);
			const auto textureRepeat = _fe3d->model_getTextureRepeat(placedModelId, partId);
			const auto isReflective = _fe3d->model_isReflective(placedModelId, partId);
			const auto isRefractive = _fe3d->model_isRefractive(placedModelId, partId);
			const auto reflectionType = static_cast<int>(_fe3d->model_getReflectionType(placedModelId, partId));
			const auto refractionType = static_cast<int>(_fe3d->model_getRefractionType(placedModelId, partId));
			const auto isFaceCulled = _fe3d->model_isFaceCulled(placedModelId, partId);
			const auto isBright = _fe3d->model_isBright(placedModelId, partId);
			const auto emissionIntensity = _fe3d->model_getEmissionIntensity(placedModelId, partId);
			const auto opacity = _fe3d->model_getOpacity(placedModelId, partId);
			const auto minAlpha = _fe3d->model_getMinAlpha(placedModelId, partId);
			const auto isWireframed = _fe3d->model_isWireframed(placedModelId, partId);
			const auto wireframeColor = _fe3d->model_getWireframeColor(placedModelId, partId);

			auto diffuseMapPath = _fe3d->model_getDiffuseMapPath(placedModelId, partId);
			auto emissionMapPath = _fe3d->model_getEmissionMapPath(placedModelId, partId);
			auto specularMapPath = _fe3d->model_getSpecularMapPath(placedModelId, partId);
			auto reflectionMapPath = _fe3d->model_getReflectionMapPath(placedModelId, partId);
			auto refractionMapPath = _fe3d->model_getRefractionMapPath(placedModelId, partId);
			auto normalMapPath = _fe3d->model_getNormalMapPath(placedModelId, partId);

			diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			emissionMapPath = (emissionMapPath.empty() ? "" : emissionMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			specularMapPath = (specularMapPath.empty() ? "" : specularMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			reflectionMapPath = (reflectionMapPath.empty() ? "" : reflectionMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			refractionMapPath = (refractionMapPath.empty() ? "" : refractionMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
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
				<< "MODEL_PART "
				<< placedModelId
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
				<< minAlpha
				<< " "
				<< position.x
				<< " "
				<< position.y
				<< " "
				<< position.z
				<< " "
				<< rotation.x
				<< " "
				<< rotation.y
				<< " "
				<< rotation.z
				<< " "
				<< rotationOrigin.x
				<< " "
				<< rotationOrigin.y
				<< " "
				<< rotationOrigin.z
				<< " "
				<< size.x
				<< " "
				<< size.y
				<< " "
				<< size.z
				<< " "
				<< isWireframed
				<< " "
				<< wireframeColor.r
				<< " "
				<< wireframeColor.g
				<< " "
				<< wireframeColor.b
				<< endl;
		}

		for(const auto & aabbId : aabbIds)
		{
			const auto position = _fe3d->aabb_getLocalPosition(aabbId);
			const auto size = _fe3d->aabb_getLocalSize(aabbId);
			const auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(placedModelId);
			const auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(placedModelId);
			const auto isVisible = _fe3d->aabb_isVisible(placedModelId);

			file
				<< "MODEL_AABB "
				<< placedModelId
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
				<< " "
				<< isRaycastResponsive
				<< " "
				<< isCollisionResponsive
				<< " "
				<< isVisible
				<< endl;
		}

		for(const auto & animation3dId : animation3dIds)
		{
			const auto isPaused = _fe3d->model_isAnimation3dPaused(placedModelId, animation3dId);
			const auto isAutoPaused = _fe3d->model_isAnimation3dAutopaused(placedModelId, animation3dId);
			const auto playCount = _fe3d->model_getAnimation3dPlayCount(placedModelId, animation3dId);
			const auto frameIndex = _fe3d->model_getAnimation3dFrameIndex(placedModelId, animation3dId);
			const auto speedMultiplier = _fe3d->model_getAnimation3dSpeedMultiplier(placedModelId, animation3dId);
			const auto partCount = partIds.size();

			file
				<< "MODEL_ANIMATION3D "
				<< placedModelId
				<< " "
				<< animation3dId
				<< " "
				<< isPaused
				<< " "
				<< isAutoPaused
				<< " "
				<< playCount
				<< " "
				<< frameIndex
				<< " "
				<< speedMultiplier
				<< " "
				<< partCount;

			for(auto partId : partIds)
			{
				const auto totalMovement = _fe3d->model_getAnimation3dTotalMovement(placedModelId, partId, animation3dId);
				const auto totalRotation = _fe3d->model_getAnimation3dTotalRotation(placedModelId, partId, animation3dId);
				const auto totalScaling = _fe3d->model_getAnimation3dTotalScaling(placedModelId, partId, animation3dId);
				const auto totalSpeed = _fe3d->model_getAnimation3dTotalSpeed(placedModelId, partId, animation3dId);

				file
					<< " "
					<< partId
					<< " "
					<< totalMovement.x
					<< " "
					<< totalMovement.y
					<< " "
					<< totalMovement.z
					<< " "
					<< totalRotation.x
					<< " "
					<< totalRotation.y
					<< " "
					<< totalRotation.z
					<< " "
					<< totalScaling.x
					<< " "
					<< totalScaling.y
					<< " "
					<< totalScaling.z
					<< " "
					<< totalSpeed.x
					<< " "
					<< totalSpeed.y
					<< " "
					<< totalSpeed.z;
			}

			file << endl;
		}
	}

	for(const auto & [placedQuad3dId, templateQuad3dId] : _addedQuad3dIds)
	{
		const auto position = _fe3d->quad3d_getPosition(placedQuad3dId);
		const auto rotation = _fe3d->quad3d_getRotation(placedQuad3dId);
		const auto size = _fe3d->quad3d_getSize(placedQuad3dId);
		const auto color = _fe3d->quad3d_getColor(placedQuad3dId);
		const auto isFacingCameraHorizontally = _fe3d->quad3d_isFacingCameraHorizontally(placedQuad3dId);
		const auto isFacingCameraVertically = _fe3d->quad3d_isFacingCameraVertically(placedQuad3dId);
		const auto isHorizontallyFlipped = _fe3d->quad3d_isHorizontallyFlipped(placedQuad3dId);
		const auto isVerticallyFlipped = _fe3d->quad3d_isVerticallyFlipped(placedQuad3dId);
		const auto isReflected = _fe3d->quad3d_isReflected(placedQuad3dId);
		const auto isRefracted = _fe3d->quad3d_isRefracted(placedQuad3dId);
		const auto isShadowed = _fe3d->quad3d_isShadowed(placedQuad3dId);
		const auto lightness = _fe3d->quad3d_getLightness(placedQuad3dId);
		const auto textureRepeat = _fe3d->quad3d_getTextureRepeat(placedQuad3dId);
		const auto isBright = _fe3d->quad3d_isBright(placedQuad3dId);
		const auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(placedQuad3dId);
		const auto opacity = _fe3d->quad3d_getOpacity(placedQuad3dId);
		const auto minAlpha = _fe3d->quad3d_getMinAlpha(placedQuad3dId);
		const auto rotationOrder = static_cast<int>(_fe3d->quad3d_getRotationOrder(placedQuad3dId));
		const auto isVisible = _fe3d->quad3d_isVisible(placedQuad3dId);
		const auto isWireframed = _fe3d->quad3d_isWireframed(placedQuad3dId);
		const auto wireframeColor = _fe3d->quad3d_getWireframeColor(placedQuad3dId);
		const auto minClipPosition = _fe3d->quad3d_getMinClipPosition(placedQuad3dId);
		const auto maxClipPosition = _fe3d->quad3d_getMaxClipPosition(placedQuad3dId);
		const auto isFrozen = _fe3d->quad3d_isFrozen(placedQuad3dId);
		const auto uvMultiplier = _fe3d->quad3d_getUvMultiplier(placedQuad3dId);
		const auto uvOffset = _fe3d->quad3d_getUvOffset(placedQuad3dId);
		const auto animation2dIds = _fe3d->quad3d_getAnimation2dIds(placedQuad3dId);

		auto diffuseMapPath = _fe3d->quad3d_getDiffuseMapPath(placedQuad3dId);
		auto emissionMapPath = _fe3d->quad3d_getEmissionMapPath(placedQuad3dId);

		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		emissionMapPath = (emissionMapPath.empty() ? "" : emissionMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');

		file
			<< "QUAD3D "
			<< placedQuad3dId
			<< " "
			<< templateQuad3dId
			<< " "
			<< diffuseMapPath
			<< " "
			<< emissionMapPath
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< isFacingCameraHorizontally
			<< " "
			<< isFacingCameraVertically
			<< " "
			<< isHorizontallyFlipped
			<< " "
			<< isVerticallyFlipped
			<< " "
			<< isReflected
			<< " "
			<< isRefracted
			<< " "
			<< isShadowed
			<< " "
			<< lightness
			<< " "
			<< textureRepeat
			<< " "
			<< isBright
			<< " "
			<< emissionIntensity
			<< " "
			<< opacity
			<< " "
			<< minAlpha
			<< " "
			<< rotationOrder
			<< " "
			<< isVisible
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< isFrozen
			<< " "
			<< uvMultiplier.x
			<< " "
			<< uvMultiplier.y
			<< " "
			<< uvOffset.x
			<< " "
			<< uvOffset.y
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
			<< endl;

		if(_fe3d->aabb_isExisting(placedQuad3dId))
		{
			const auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(placedQuad3dId);
			const auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(placedQuad3dId);
			const auto isVisible = _fe3d->aabb_isVisible(placedQuad3dId);

			file
				<< "QUAD3D_AABB "
				<< placedQuad3dId
				<< " "
				<< isRaycastResponsive
				<< " "
				<< isCollisionResponsive
				<< " "
				<< isVisible
				<< endl;
		}

		for(const auto & animation2dId : animation2dIds)
		{
			const auto isPaused = _fe3d->quad3d_isAnimation2dPaused(placedQuad3dId, animation2dId);
			const auto isAutoPaused = _fe3d->quad3d_isAnimation2dAutopaused(placedQuad3dId, animation2dId);
			const auto playCount = _fe3d->quad3d_getAnimation2dPlayCount(placedQuad3dId, animation2dId);
			const auto rowIndex = _fe3d->quad3d_getAnimation2dRowIndex(placedQuad3dId, animation2dId);
			const auto columnIndex = _fe3d->quad3d_getAnimation2dColumnIndex(placedQuad3dId, animation2dId);
			const auto intervalMultiplier = _fe3d->quad3d_getAnimation2dIntervalMultiplier(placedQuad3dId, animation2dId);
			const auto intervalDivider = _fe3d->quad3d_getAnimation2dIntervalDivider(placedQuad3dId, animation2dId);
			const auto updateCount = _fe3d->quad3d_getAnimation2dUpdateCount(placedQuad3dId, animation2dId);

			file
				<< "QUAD3D_ANIMATION2D "
				<< isPaused
				<< " "
				<< isAutoPaused
				<< " "
				<< playCount
				<< " "
				<< rowIndex
				<< " "
				<< columnIndex
				<< " "
				<< intervalMultiplier
				<< " "
				<< intervalDivider
				<< " "
				<< updateCount
				<< endl;
		}
	}

	for(const auto & [placedText3dId, templateText3dId] : _addedText3dIds)
	{
		const auto position = _fe3d->text3d_getPosition(placedText3dId);
		const auto rotation = _fe3d->text3d_getRotation(placedText3dId);
		const auto size = _fe3d->text3d_getSize(placedText3dId);
		const auto color = _fe3d->text3d_getColor(placedText3dId);
		const auto isFacingCameraHorizontally = _fe3d->text3d_isFacingCameraHorizontally(placedText3dId);
		const auto isFacingCameraVertically = _fe3d->text3d_isFacingCameraVertically(placedText3dId);
		const auto isHorizontallyFlipped = _fe3d->text3d_isHorizontallyFlipped(placedText3dId);
		const auto isVerticallyFlipped = _fe3d->text3d_isVerticallyFlipped(placedText3dId);
		const auto isReflected = _fe3d->text3d_isReflected(placedText3dId);
		const auto isRefracted = _fe3d->text3d_isRefracted(placedText3dId);
		const auto isShadowed = _fe3d->text3d_isShadowed(placedText3dId);
		const auto lightness = _fe3d->text3d_getLightness(placedText3dId);
		const auto isBright = _fe3d->text3d_isBright(placedText3dId);
		const auto opacity = _fe3d->text3d_getOpacity(placedText3dId);
		const auto minAlpha = _fe3d->text3d_getMinAlpha(placedText3dId);
		const auto rotationOrder = static_cast<int>(_fe3d->text3d_getRotationOrder(placedText3dId));
		const auto isVisible = _fe3d->text3d_isVisible(placedText3dId);
		const auto isWireframed = _fe3d->text3d_isWireframed(placedText3dId);
		const auto wireframeColor = _fe3d->text3d_getWireframeColor(placedText3dId);
		const auto minClipPosition = _fe3d->text3d_getMinClipPosition(placedText3dId);
		const auto maxClipPosition = _fe3d->text3d_getMaxClipPosition(placedText3dId);
		const auto isFrozen = _fe3d->text3d_isFrozen(placedText3dId);
		const auto content = _fe3d->text3d_getContent(placedText3dId);

		file
			<< "TEXT3D "
			<< placedText3dId
			<< " "
			<< templateText3dId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< isFacingCameraHorizontally
			<< " "
			<< isFacingCameraVertically
			<< " "
			<< isHorizontallyFlipped
			<< " "
			<< isVerticallyFlipped
			<< " "
			<< isReflected
			<< " "
			<< isRefracted
			<< " "
			<< isShadowed
			<< " "
			<< lightness
			<< " "
			<< isBright
			<< " "
			<< opacity
			<< " "
			<< minAlpha
			<< " "
			<< rotationOrder
			<< " "
			<< isVisible
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
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< isFrozen
			<< " "
			<< content
			<< endl;

		if(_fe3d->aabb_isExisting(placedText3dId))
		{
			const auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(placedText3dId);
			const auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(placedText3dId);
			const auto isVisible = _fe3d->aabb_isVisible(placedText3dId);

			file
				<< "TEXT3D_AABB "
				<< placedText3dId
				<< " "
				<< isRaycastResponsive
				<< " "
				<< isCollisionResponsive
				<< " "
				<< isVisible
				<< endl;
		}
	}

	for(const auto & [placedAabbId, templateAabbId] : _addedAabbIds)
	{
		const auto position = _fe3d->aabb_getBasePosition(placedAabbId);
		const auto size = _fe3d->aabb_getBaseSize(placedAabbId);
		const auto color = _fe3d->aabb_getColor(placedAabbId);
		const auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(placedAabbId);
		const auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(placedAabbId);
		const auto isVisible = _fe3d->aabb_isVisible(placedAabbId);
		const auto minClipPosition = _fe3d->aabb_getMinClipPosition(placedAabbId);
		const auto maxClipPosition = _fe3d->aabb_getMaxClipPosition(placedAabbId);

		file
			<< "AABB "
			<< placedAabbId
			<< " "
			<< templateAabbId
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
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< isRaycastResponsive
			<< " "
			<< isCollisionResponsive
			<< " "
			<< isVisible
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
			<< endl;
	}

	for(const auto & [placedPointlightId, templatePointlightId] : _addedPointlightIds)
	{
		const auto position = _fe3d->pointlight_getPosition(placedPointlightId);
		const auto radius = _fe3d->pointlight_getRadius(placedPointlightId);
		const auto color = _fe3d->pointlight_getColor(placedPointlightId);
		const auto intensity = _fe3d->pointlight_getIntensity(placedPointlightId);
		const auto shape = static_cast<int>(_fe3d->pointlight_getShape(placedPointlightId));
		const auto isVisible = _fe3d->pointlight_isVisible(placedPointlightId);

		file
			<< "POINTLIGHT "
			<< placedPointlightId
			<< " "
			<< templatePointlightId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< radius.x
			<< " "
			<< radius.y
			<< " "
			<< radius.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< intensity
			<< " "
			<< shape
			<< " "
			<< isVisible
			<< endl;
	}

	for(const auto & [placedSpotlightId, templateSpotlightId] : _addedSpotlightIds)
	{
		const auto position = _fe3d->spotlight_getPosition(placedSpotlightId);
		const auto yaw = _fe3d->spotlight_getYaw(placedSpotlightId);
		const auto pitch = _fe3d->spotlight_getPitch(placedSpotlightId);
		const auto color = _fe3d->spotlight_getColor(placedSpotlightId);
		const auto intensity = _fe3d->spotlight_getIntensity(placedSpotlightId);
		const auto angle = _fe3d->spotlight_getAngle(placedSpotlightId);
		const auto distance = _fe3d->spotlight_getDistance(placedSpotlightId);
		const auto isVisible = _fe3d->spotlight_isVisible(placedSpotlightId);

		file
			<< "SPOTLIGHT "
			<< placedSpotlightId
			<< " "
			<< templateSpotlightId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< yaw
			<< " "
			<< pitch
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< intensity
			<< " "
			<< angle
			<< " "
			<< distance
			<< " "
			<< isVisible
			<< endl;
	}

	for(const auto & [placedSound3dId, templateSound3dId] : _addedSound3dIds)
	{
		const auto position = _fe3d->sound3d_getPosition(placedSound3dId);
		const auto maxVolume = _fe3d->sound3d_getMaxVolume(placedSound3dId);
		const auto maxDistance = _fe3d->sound3d_getMaxDistance(placedSound3dId);

		file
			<< "SOUND3D "
			<< placedSound3dId
			<< " "
			<< templateSound3dId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< maxVolume
			<< " "
			<< maxDistance
			<< endl;
	}

	for(const auto & placedCaptorId : _addedCaptorIds)
	{
		const auto position = _fe3d->captor_getPosition(placedCaptorId);

		auto exceptionId = _fe3d->captor_getExceptionId(placedCaptorId);

		exceptionId = (exceptionId.empty()) ? "?" : exceptionId;

		file
			<< "CAPTOR "
			<< placedCaptorId
			<< " "
			<< exceptionId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< endl;
	}

	if(_fe3d->graphics_isAmbientLightingEnabled())
	{
		const auto ambientLightingColor = _fe3d->graphics_getAmbientLightingColor();
		const auto ambientLightingIntensity = _fe3d->graphics_getAmbientLightingIntensity();

		file
			<< "GRAPHICS_AMBIENT_LIGHTING "
			<< ambientLightingColor.r
			<< " "
			<< ambientLightingColor.g
			<< " "
			<< ambientLightingColor.b
			<< " "
			<< ambientLightingIntensity
			<< endl;
	}

	if(_fe3d->graphics_isDirectionalLightingEnabled())
	{
		const auto directionalLightingColor = _fe3d->graphics_getDirectionalLightingColor();
		const auto directionalLightingPosition = _fe3d->graphics_getDirectionalLightingPosition();
		const auto directionalLightingIntensity = _fe3d->graphics_getDirectionalLightingIntensity();

		file
			<< "GRAPHICS_DIRECTIONAL_LIGHTING "
			<< directionalLightingPosition.x
			<< " "
			<< directionalLightingPosition.y
			<< " "
			<< directionalLightingPosition.z
			<< " "
			<< directionalLightingColor.r
			<< " "
			<< directionalLightingColor.g
			<< " "
			<< directionalLightingColor.b
			<< " "
			<< directionalLightingIntensity
			<< endl;
	}

	if(_fe3d->graphics_isShadowsEnabled())
	{
		const auto size = _fe3d->graphics_getShadowSize();
		const auto lightness = _fe3d->graphics_getShadowLightness();
		const auto position = _fe3d->graphics_getShadowPositionOffset();
		const auto lookat = _fe3d->graphics_getShadowLookatOffset();
		const auto isFollowingCameraX = _fe3d->graphics_isShadowFollowingCameraX();
		const auto isFollowingCameraY = _fe3d->graphics_isShadowFollowingCameraY();
		const auto isFollowingCameraZ = _fe3d->graphics_isShadowFollowingCameraZ();
		const auto interval = _fe3d->graphics_getShadowInterval();
		const auto quality = _fe3d->graphics_getShadowQuality();

		file
			<< "GRAPHICS_SHADOWS "
			<< size
			<< " "
			<< lightness
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< lookat.x
			<< " "
			<< lookat.y
			<< " "
			<< lookat.z
			<< " "
			<< isFollowingCameraX
			<< " "
			<< isFollowingCameraY
			<< " "
			<< isFollowingCameraZ
			<< " "
			<< interval
			<< " "
			<< quality
			<< endl;
	}

	{
		const auto cubeInterval = _fe3d->graphics_getCubeReflectionInterval();
		const auto cubeQuality = _fe3d->graphics_getCubeReflectionQuality();
		const auto planarHeight = _fe3d->graphics_getPlanarReflectionHeight();
		const auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_REFLECTIONS "
			<< cubeInterval
			<< " "
			<< cubeQuality
			<< " "
			<< planarHeight
			<< " "
			<< planarQuality
			<< endl;
	}

	{
		const auto cubeInterval = _fe3d->graphics_getCubeReflectionInterval();
		const auto cubeQuality = _fe3d->graphics_getCubeReflectionQuality();
		const auto planarHeight = _fe3d->graphics_getPlanarRefractionHeight();
		const auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_REFRACTIONS "
			<< cubeInterval
			<< " "
			<< cubeQuality
			<< " "
			<< planarHeight
			<< " "
			<< planarQuality
			<< endl;
	}

	if(_fe3d->graphics_isDofEnabled())
	{
		const auto dynamic = _fe3d->graphics_isDofDynamic();
		const auto blurDistance = _fe3d->graphics_getDofBlurDistance();
		const auto maxDistance = _fe3d->graphics_getDofDynamicDistance();
		const auto quality = _fe3d->graphics_getDofQuality();

		file
			<< "GRAPHICS_DOF "
			<< dynamic
			<< " "
			<< blurDistance
			<< " "
			<< maxDistance
			<< " "
			<< quality
			<< endl;
	}

	if(_fe3d->graphics_isFogEnabled())
	{
		const auto minDistance = _fe3d->graphics_getFogMinDistance();
		const auto maxDistance = _fe3d->graphics_getFogMaxDistance();
		const auto thickness = _fe3d->graphics_getFogThickness();
		const auto color = _fe3d->graphics_getFogColor();

		file
			<< "GRAPHICS_FOG "
			<< minDistance
			<< " "
			<< maxDistance
			<< " "
			<< thickness
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< endl;
	}

	if(_fe3d->graphics_isLensFlareEnabled())
	{
		const auto intensity = _fe3d->graphics_getLensFlareIntensity();
		const auto sensitivity = _fe3d->graphics_getLensFlareSensitivity();

		auto flareMapPath = _fe3d->graphics_getLensFlareMapPath();

		flareMapPath = (flareMapPath.empty() ? "" : flareMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));

		flareMapPath = (flareMapPath.empty()) ? "?" : flareMapPath;

		replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

		file
			<< "GRAPHICS_LENS_FLARE "
			<< flareMapPath
			<< " "
			<< intensity
			<< " "
			<< sensitivity
			<< endl;
	}

	if(_fe3d->graphics_isSkyExposureEnabled())
	{
		const auto intensity = _fe3d->graphics_getSkyExposureIntensity();
		const auto speed = _fe3d->graphics_getSkyExposureSpeed();

		file
			<< "GRAPHICS_SKY_EXPOSURE "
			<< intensity
			<< " "
			<< speed
			<< endl;
	}

	if(_fe3d->graphics_isBloomEnabled())
	{
		const auto type = static_cast<int>(_fe3d->graphics_getBloomType());
		const auto intensity = _fe3d->graphics_getBloomIntensity();
		const auto blurCount = _fe3d->graphics_getBloomBlurCount();
		const auto quality = _fe3d->graphics_getBloomQuality();

		file
			<< "GRAPHICS_BLOOM "
			<< type
			<< " "
			<< intensity
			<< " "
			<< blurCount
			<< " "
			<< quality
			<< endl;
	}

	file.close();

	Logger::throwInfo("Custom world data saved");
}