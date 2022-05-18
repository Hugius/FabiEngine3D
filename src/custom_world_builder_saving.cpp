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
			<< "SKY "
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
			<< "TERRAIN "
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
			<< "WATER "
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

	for(const auto & modelId : _addedModelIds)
	{
		const auto partIds = _fe3d->model_getPartIds(modelId);
		const auto aabbIds = _fe3d->model_getChildAabbIds(modelId);
		const auto isMultiParted = _fe3d->model_isMultiParted(modelId);
		const auto position = _fe3d->model_getBasePosition(modelId);
		const auto rotation = _fe3d->model_getBaseRotation(modelId);
		const auto rotationOrigin = _fe3d->model_getBaseRotationOrigin(modelId);
		const auto size = _fe3d->model_getBaseSize(modelId);
		const auto levelOfDetailDistance = _fe3d->model_getLevelOfDetailDistance(modelId);
		const auto rotationOrder = static_cast<int>(_fe3d->model_getRotationOrder(modelId));
		const auto isShadowed = _fe3d->model_isShadowed(modelId);
		const auto isReflected = _fe3d->model_isReflected(modelId);
		const auto isRefracted = _fe3d->model_isRefracted(modelId);
		const auto minClipPosition = _fe3d->model_getMinClipPosition(modelId);
		const auto maxClipPosition = _fe3d->model_getMaxClipPosition(modelId);
		const auto isVisible = _fe3d->model_isVisible(modelId);
		const auto isFrozen = _fe3d->model_isFrozen(modelId);

		auto meshPath = _fe3d->model_getMeshPath(modelId);
		auto levelOfDetailId = _fe3d->model_getLevelOfDetailId(modelId);

		meshPath = (meshPath.empty() ? "" : meshPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		meshPath = (meshPath.empty()) ? "?" : meshPath;
		levelOfDetailId = (levelOfDetailId.empty()) ? "?" : levelOfDetailId;

		replace(meshPath.begin(), meshPath.end(), ' ', '?');

		file
			<< "MODEL "
			<< modelId
			<< " "
			<< meshPath
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
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< size.z
			<< " "
			<< isFrozen
			<< endl;

		for(auto partId : partIds)
		{
			const auto position = _fe3d->model_getPartPosition(modelId, partId);
			const auto rotation = _fe3d->model_getPartRotation(modelId, partId);
			const auto rotationOrigin = _fe3d->model_getPartRotationOrigin(modelId, partId);
			const auto size = _fe3d->model_getPartSize(modelId, partId);
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
			const auto minAlpha = _fe3d->model_getMinAlpha(modelId, partId);
			const auto isWireframed = _fe3d->model_isWireframed(modelId, partId);
			const auto wireframeColor = _fe3d->model_getWireframeColor(modelId, partId);

			auto diffuseMapPath = _fe3d->model_getDiffuseMapPath(modelId, partId);
			auto emissionMapPath = _fe3d->model_getEmissionMapPath(modelId, partId);
			auto specularMapPath = _fe3d->model_getSpecularMapPath(modelId, partId);
			auto reflectionMapPath = _fe3d->model_getReflectionMapPath(modelId, partId);
			auto refractionMapPath = _fe3d->model_getRefractionMapPath(modelId, partId);
			auto normalMapPath = _fe3d->model_getNormalMapPath(modelId, partId);

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
			const auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(modelId);
			const auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(modelId);
			const auto isVisible = _fe3d->aabb_isVisible(modelId);

			file
				<< "MODEL_AABB "
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
				<< " "
				<< isRaycastResponsive
				<< " "
				<< isCollisionResponsive
				<< " "
				<< isVisible
				<< endl;
		}
	}

	for(const auto & quad3dId : _addedQuad3dIds)
	{
		const auto size = _fe3d->quad3d_getSize(quad3dId);
		const auto color = _fe3d->quad3d_getColor(quad3dId);
		const auto isFacingCameraHorizontally = _fe3d->quad3d_isFacingCameraHorizontally(quad3dId);
		const auto isFacingCameraVertically = _fe3d->quad3d_isFacingCameraVertically(quad3dId);
		const auto isHorizontallyFlipped = _fe3d->quad3d_isHorizontallyFlipped(quad3dId);
		const auto isVerticallyFlipped = _fe3d->quad3d_isVerticallyFlipped(quad3dId);
		const auto isReflected = _fe3d->quad3d_isReflected(quad3dId);
		const auto isRefracted = _fe3d->quad3d_isRefracted(quad3dId);
		const auto isShadowed = _fe3d->quad3d_isShadowed(quad3dId);
		const auto lightness = _fe3d->quad3d_getLightness(quad3dId);
		const auto textureRepeat = _fe3d->quad3d_getTextureRepeat(quad3dId);
		const auto isBright = _fe3d->quad3d_isBright(quad3dId);
		const auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(quad3dId);
		const auto opacity = _fe3d->quad3d_getOpacity(quad3dId);
		const auto minAlpha = _fe3d->quad3d_getMinAlpha(quad3dId);
		const auto rotationOrder = static_cast<int>(_fe3d->quad3d_getRotationOrder(quad3dId));
		const auto hasAabb = _fe3d->aabb_isExisting(quad3dId);
		const auto isVisible = _fe3d->quad3d_isVisible(quad3dId);

		auto diffuseMapPath = _fe3d->quad3d_getDiffuseMapPath(quad3dId);
		auto emissionMapPath = _fe3d->quad3d_getEmissionMapPath(quad3dId);

		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		emissionMapPath = (emissionMapPath.empty() ? "" : emissionMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');

		file
			<< quad3dId
			<< " "
			<< diffuseMapPath
			<< " "
			<< emissionMapPath
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
			<< hasAabb
			<< " "
			<< isVisible
			<< endl;
	}

	for(const auto & text3dId : _addedText3dIds)
	{
		const auto size = _fe3d->text3d_getSize(text3dId);
		const auto color = _fe3d->text3d_getColor(text3dId);
		const auto isFacingCameraHorizontally = _fe3d->text3d_isFacingCameraHorizontally(text3dId);
		const auto isFacingCameraVertically = _fe3d->text3d_isFacingCameraVertically(text3dId);
		const auto isHorizontallyFlipped = _fe3d->text3d_isHorizontallyFlipped(text3dId);
		const auto isVerticallyFlipped = _fe3d->text3d_isVerticallyFlipped(text3dId);
		const auto isReflected = _fe3d->text3d_isReflected(text3dId);
		const auto isRefracted = _fe3d->text3d_isRefracted(text3dId);
		const auto isShadowed = _fe3d->text3d_isShadowed(text3dId);
		const auto lightness = _fe3d->text3d_getLightness(text3dId);
		const auto isBright = _fe3d->text3d_isBright(text3dId);
		const auto opacity = _fe3d->text3d_getOpacity(text3dId);
		const auto minAlpha = _fe3d->text3d_getMinAlpha(text3dId);
		const auto rotationOrder = static_cast<int>(_fe3d->text3d_getRotationOrder(text3dId));
		const auto hasAabb = _fe3d->aabb_isExisting(text3dId);
		const auto isVisible = _fe3d->text3d_isVisible(text3dId);

		auto fontMapPath = _fe3d->text3d_getFontMapPath(text3dId);

		fontMapPath = (fontMapPath.empty() ? "" : fontMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		fontMapPath = (fontMapPath.empty()) ? "?" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), ' ', '?');

		file
			<< text3dId
			<< " "
			<< fontMapPath
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
			<< hasAabb
			<< " "
			<< isVisible
			<< endl;
	}

	for(const auto & aabbId : _addedAabbIds)
	{
		const auto size = _fe3d->aabb_getBaseSize(aabbId);
		const auto color = _fe3d->aabb_getColor(aabbId);
		const auto isVisible = _fe3d->aabb_isVisible(aabbId);

		file
			<< aabbId
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
			<< isVisible
			<< endl;
	}

	for(const auto & pointlightId : _addedPointlightIds)
	{
		const auto radius = _fe3d->pointlight_getRadius(pointlightId);
		const auto color = _fe3d->pointlight_getColor(pointlightId);
		const auto intensity = _fe3d->pointlight_getIntensity(pointlightId);
		const auto shape = static_cast<int>(_fe3d->pointlight_getShape(pointlightId));
		const auto isVisible = _fe3d->pointlight_isVisible(pointlightId);

		file
			<< pointlightId
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

	for(const auto & spotlightId : _addedSpotlightIds)
	{
		const auto color = _fe3d->spotlight_getColor(spotlightId);
		const auto intensity = _fe3d->spotlight_getIntensity(spotlightId);
		const auto angle = _fe3d->spotlight_getAngle(spotlightId);
		const auto distance = _fe3d->spotlight_getDistance(spotlightId);
		const auto isVisible = _fe3d->spotlight_isVisible(spotlightId);

		file
			<< spotlightId
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

	for(const auto & captorId : _addedCaptorIds)
	{
		const auto position = _fe3d->captor_getPosition(captorId);

		auto exceptionId = _fe3d->captor_getExceptionId(captorId);

		exceptionId = (exceptionId.empty()) ? "?" : exceptionId;

		file
			<< captorId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< exceptionId
			<< endl;
	}

	for(const auto & sound3dId : _addedSound3dIds)
	{
		const auto maxVolume = _fe3d->sound3d_getMaxVolume(sound3dId);
		const auto maxDistance = _fe3d->sound3d_getMaxDistance(sound3dId);

		auto audioPath = _fe3d->sound3d_getAudioPath(sound3dId);

		audioPath = (audioPath.empty() ? "" : audioPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		audioPath = (audioPath.empty()) ? "?" : audioPath;

		replace(audioPath.begin(), audioPath.end(), ' ', '?');

		file
			<< sound3dId
			<< " "
			<< audioPath
			<< " "
			<< maxVolume
			<< " "
			<< maxDistance
			<< endl;
	}

	// graphics

	file.close();

	Logger::throwInfo("Custom world data saved");

	return true;
}