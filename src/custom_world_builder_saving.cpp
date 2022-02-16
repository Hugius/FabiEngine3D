#include "custom_world_builder.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;
using std::endl;

const bool CustomWorldBuilder::saveWorldToFile(const string& fileName)
{
	const auto rootPath = Tools::getRootDirectoryPath();
	auto file = ofstream(rootPath + "projects\\" + _currentProjectId + "\\worlds\\custom\\" + fileName + ".fe3d");

	for(const auto& skyId : _addedSkyIds)
	{
		auto cubeMapPaths = _fe3d->sky_getCubeMapPaths(skyId);
		auto rotation = _fe3d->sky_getRotation(skyId);
		auto lightness = _fe3d->sky_getLightness(skyId);
		auto color = _fe3d->sky_getColor(skyId);
		auto isWireframed = _fe3d->sky_isWireframed(skyId);
		auto wireframeColor = _fe3d->sky_getWireframeColor(skyId);
		auto isVisible = _fe3d->sky_isVisible(skyId);

		for(auto& cubeMapPath : cubeMapPaths)
		{
			cubeMapPath = (cubeMapPath.empty() ? "" : cubeMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));

			cubeMapPath = (cubeMapPath.empty()) ? "?" : cubeMapPath;

			replace(cubeMapPath.begin(), cubeMapPath.end(), ' ', '?');
		}

		file
			<< "SKY "
			<< skyId
			<< " ";

		for(const auto& cubeMapPath : cubeMapPaths)
		{
			file
				<< cubeMapPath
				<< " ";
		}

		file
			<< rotation
			<< " "
			<< lightness
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< isVisible
			<< endl;
	}

	for(const auto& terrainId : _addedTerrainIds)
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
		auto isWireframed = _fe3d->terrain_isWireframed(terrainId);
		auto wireframeColor = _fe3d->terrain_getWireframeColor(terrainId);
		auto isVisible = _fe3d->terrain_isVisible(terrainId);

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
			<< maxHeight
			<< " "
			<< textureRepeat
			<< " "
			<< lightness
			<< " "
			<< blendMapPath
			<< " "
			<< redDiffuseMapPath
			<< " "
			<< greenDiffuseMapPath
			<< " "
			<< blueDiffuseMapPath
			<< " "
			<< redTextureRepeat
			<< " "
			<< greenTextureRepeat
			<< " "
			<< blueTextureRepeat
			<< " "
			<< normalMapPath
			<< " "
			<< redNormalMapPath
			<< " "
			<< greenNormalMapPath
			<< " "
			<< blueNormalMapPath
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
			<< isVisible
			<< endl;
	}

	for(const auto& waterId : _addedWaterIds)
	{
		auto dudvMapPath = _fe3d->water_getDudvMapPath(waterId);
		auto normalMapPath = _fe3d->water_getNormalMapPath(waterId);
		auto displacementMapPath = _fe3d->water_getDisplacementMapPath(waterId);
		auto color = _fe3d->water_getColor(waterId);
		auto height = _fe3d->water_getHeight(waterId);
		auto rippleSpeed = _fe3d->water_getRippleSpeed(waterId);
		auto waveSpeed = _fe3d->water_getWaveSpeed(waterId);
		auto size = _fe3d->water_getSize(waterId);
		auto textureRepeat = _fe3d->water_getTextureRepeat(waterId);
		auto waveHeight = _fe3d->water_getWaveHeight(waterId);
		auto maxDepth = _fe3d->water_getMaxDepth(waterId);
		auto isEdged = _fe3d->water_isEdged(waterId);
		auto specularShininess = _fe3d->water_getSpecularShininess(waterId);
		auto specularIntensity = _fe3d->water_getSpecularIntensity(waterId);
		auto isSpecular = _fe3d->water_isSpecular(waterId);
		auto isReflective = _fe3d->water_isReflective(waterId);
		auto isRefractive = _fe3d->water_isRefractive(waterId);
		auto isWireframed = _fe3d->water_isWireframed(waterId);
		auto wireframeColor = _fe3d->water_getWireframeColor(waterId);
		auto isVisible = _fe3d->water_isVisible(waterId);

		dudvMapPath = (dudvMapPath.empty() ? "" : dudvMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		displacementMapPath = (displacementMapPath.empty() ? "" : displacementMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));

		dudvMapPath = (dudvMapPath.empty() ? "?" : dudvMapPath);
		normalMapPath = (normalMapPath.empty() ? "?" : normalMapPath);
		displacementMapPath = (displacementMapPath.empty() ? "?" : displacementMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(displacementMapPath.begin(), displacementMapPath.end(), ' ', '?');

		file
			<< "WATER "
			<< waterId
			<< " "
			<< dudvMapPath
			<< " "
			<< normalMapPath
			<< " "
			<< displacementMapPath
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
			<< height
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
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< isVisible
			<< endl;
	}

	for(const auto& modelId : _addedModelIds)
	{
		auto partIds = _fe3d->model_getPartIds(modelId);
		auto aabbIds = _fe3d->model_getChildAabbIds(modelId);
		auto isMultiParted = _fe3d->model_isMultiParted(modelId);
		auto meshPath = _fe3d->model_getMeshPath(modelId);
		auto basePosition = _fe3d->model_getBasePosition(modelId);
		auto baseRotation = _fe3d->model_getBaseRotation(modelId);
		auto baseRotationOrigin = _fe3d->model_getBaseRotationOrigin(modelId);
		auto baseSize = _fe3d->model_getBaseSize(modelId);
		auto levelOfDetailEntityId = _fe3d->model_getLevelOfDetailEntityId(modelId);
		auto levelOfDetailDistance = _fe3d->model_getLevelOfDetailDistance(modelId);
		auto rotationOrder = static_cast<unsigned int>(_fe3d->model_getRotationOrder(modelId));
		auto isShadowed = _fe3d->model_isShadowed(modelId);
		auto isReflected = _fe3d->model_isReflected(modelId);
		auto isFrozen = _fe3d->model_isFrozen(modelId);
		auto minHeight = _fe3d->model_getMinHeight(modelId);
		auto maxHeight = _fe3d->model_getMaxHeight(modelId);
		auto isVisible = _fe3d->model_isVisible(modelId);

		meshPath = (meshPath.empty() ? "" : meshPath.substr(("projects\\" + _currentProjectId + "\\").size()));

		meshPath = (meshPath.empty()) ? "?" : meshPath;
		levelOfDetailEntityId = (levelOfDetailEntityId.empty()) ? "?" : levelOfDetailEntityId;

		replace(meshPath.begin(), meshPath.end(), ' ', '?');
		replace(levelOfDetailEntityId.begin(), levelOfDetailEntityId.end(), ' ', '?');

		file
			<< "MODEL "
			<< modelId
			<< " "
			<< meshPath
			<< " "
			<< basePosition.x
			<< " "
			<< basePosition.y
			<< " "
			<< basePosition.z
			<< " "
			<< baseRotation.x
			<< " "
			<< baseRotation.y
			<< " "
			<< baseRotation.z
			<< " "
			<< baseRotationOrigin.x
			<< " "
			<< baseRotationOrigin.y
			<< " "
			<< baseRotationOrigin.z
			<< " "
			<< baseSize.x
			<< " "
			<< baseSize.y
			<< " "
			<< baseSize.z
			<< " "
			<< levelOfDetailEntityId
			<< " "
			<< levelOfDetailDistance
			<< " "
			<< rotationOrder
			<< " "
			<< isShadowed
			<< " "
			<< isReflected
			<< " "
			<< isFrozen
			<< " "
			<< minHeight
			<< " "
			<< maxHeight
			<< " "
			<< isVisible
			<< endl;

		for(auto partId : partIds)
		{
			auto partPosition = _fe3d->model_getPartPosition(modelId, partId);
			auto partRotation = _fe3d->model_getPartRotation(modelId, partId);
			auto partRotationOrigin = _fe3d->model_getPartRotationOrigin(modelId, partId);
			auto partSize = _fe3d->model_getPartSize(modelId, partId);
			auto diffuseMapPath = _fe3d->model_getDiffuseMapPath(modelId, partId);
			auto emissionMapPath = _fe3d->model_getEmissionMapPath(modelId, partId);
			auto specularMapPath = _fe3d->model_getSpecularMapPath(modelId, partId);
			auto reflectionMapPath = _fe3d->model_getReflectionMapPath(modelId, partId);
			auto normalMapPath = _fe3d->model_getNormalMapPath(modelId, partId);
			auto isSpecular = _fe3d->model_isSpecular(modelId, partId);
			auto specularShininess = _fe3d->model_getSpecularShininess(modelId, partId);
			auto specularIntensity = _fe3d->model_getSpecularIntensity(modelId, partId);
			auto reflectivity = _fe3d->model_getReflectivity(modelId, partId);
			auto lightness = _fe3d->model_getLightness(modelId, partId);
			auto color = _fe3d->model_getColor(modelId, partId);
			auto textureRepeat = _fe3d->model_getTextureRepeat(modelId, partId);
			auto isReflective = _fe3d->model_isReflective(modelId, partId);
			auto reflectionType = static_cast<unsigned int>(_fe3d->model_getReflectionType(modelId, partId));
			auto isFaceCulled = _fe3d->model_isFaceCulled(modelId, partId);
			auto isBright = _fe3d->model_isBright(modelId, partId);
			auto emissionIntensity = _fe3d->model_getEmissionIntensity(modelId, partId);
			auto opacity = _fe3d->model_getOpacity(modelId, partId);
			auto minTextureAlpha = _fe3d->model_getMinTextureAlpha(modelId, partId);
			auto isWireframed = _fe3d->model_isWireframed(modelId, partId);
			auto wireframeColor = _fe3d->model_getWireframeColor(modelId, partId);

			diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			emissionMapPath = (emissionMapPath.empty() ? "" : emissionMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			specularMapPath = (specularMapPath.empty() ? "" : specularMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			reflectionMapPath = (reflectionMapPath.empty() ? "" : reflectionMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
			normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));

			partId = (partId.empty()) ? "?" : partId;
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
			specularMapPath = (specularMapPath.empty()) ? "?" : specularMapPath;
			reflectionMapPath = (reflectionMapPath.empty()) ? "?" : reflectionMapPath;
			normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
			replace(specularMapPath.begin(), specularMapPath.end(), ' ', '?');
			replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
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
				<< normalMapPath
				<< " "
				<< reflectionType
				<< " "
				<< isSpecular
				<< " "
				<< isReflective
				<< " "
				<< specularShininess
				<< " "
				<< specularIntensity
				<< " "
				<< reflectivity
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
				<< " "
				<< partPosition.x
				<< " "
				<< partPosition.y
				<< " "
				<< partPosition.z
				<< " "
				<< partRotation.x
				<< " "
				<< partRotation.y
				<< " "
				<< partRotation.z
				<< " "
				<< partRotationOrigin.x
				<< " "
				<< partRotationOrigin.y
				<< " "
				<< partRotationOrigin.z
				<< " "
				<< partSize.x
				<< " "
				<< partSize.y
				<< " "
				<< partSize.z
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

		for(const string& aabbId : aabbIds)
		{
			auto position = _fe3d->aabb_getLocalPosition(aabbId);
			auto size = _fe3d->aabb_getLocalSize(aabbId);
			auto color = _fe3d->aabb_getColor(aabbId);
			auto isVisible = _fe3d->aabb_isVisible(aabbId);
			auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(aabbId);
			auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(aabbId);

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
				<< color.r
				<< " "
				<< color.g
				<< " "
				<< color.b
				<< " "
				<< isVisible
				<< " "
				<< isRaycastResponsive
				<< " "
				<< isCollisionResponsive
				<< endl;
		}

		// ANIMATION
	}

	for(const auto& quadId : _addedQuad3dIds)
	{
		auto aabbIds = _fe3d->quad3d_getChildAabbIds(quadId);
		auto position = _fe3d->quad3d_getPosition(quadId);
		auto rotation = _fe3d->quad3d_getRotation(quadId);
		auto size = _fe3d->quad3d_getSize(quadId);
		auto color = _fe3d->quad3d_getColor(quadId);
		auto diffuseMapPath = _fe3d->quad3d_getDiffuseMapPath(quadId);
		auto emissionMapPath = _fe3d->quad3d_getEmissionMapPath(quadId);
		auto isFacingCameraHorizontally = _fe3d->quad3d_isFacingCameraHorizontally(quadId);
		auto isFacingCameraVertically = _fe3d->quad3d_isFacingCameraVertically(quadId);
		auto isReflected = _fe3d->quad3d_isReflected(quadId);
		auto isShadowed = _fe3d->quad3d_isShadowed(quadId);
		auto lightness = _fe3d->quad3d_getLightness(quadId);
		auto textureRepeat = _fe3d->quad3d_getTextureRepeat(quadId);
		auto isBright = _fe3d->quad3d_isBright(quadId);
		auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(quadId);
		auto opacity = _fe3d->quad3d_getOpacity(quadId);
		auto minTextureAlpha = _fe3d->quad3d_getMinTextureAlpha(quadId);
		auto isVisible = _fe3d->quad3d_isVisible(quadId);
		auto isWireframed = _fe3d->quad3d_isWireframed(quadId);
		auto wireframeColor = _fe3d->quad3d_getWireframeColor(quadId);
		auto isFrozen = _fe3d->quad3d_isFrozen(quadId);
		auto minHeight = _fe3d->quad3d_getMinHeight(quadId);
		auto maxHeight = _fe3d->quad3d_getMaxHeight(quadId);
		auto uvMultiplier = _fe3d->quad3d_getUvMultiplier(quadId);
		auto uvOffset = _fe3d->quad3d_getUvOffset(quadId);

		diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));
		emissionMapPath = (emissionMapPath.empty() ? "" : emissionMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));

		diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
		emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;

		replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
		replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');

		file
			<< "QUAD3D "
			<< quadId
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
			<< diffuseMapPath
			<< " "
			<< emissionMapPath
			<< " "
			<< isReflected
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
			<< minTextureAlpha
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< isVisible
			<< " "
			<< isFrozen
			<< " "
			<< minHeight
			<< " "
			<< maxHeight
			<< " "
			<< uvMultiplier.x
			<< " "
			<< uvMultiplier.y
			<< " "
			<< uvOffset.x
			<< " "
			<< uvOffset.y
			<< endl;

		for(const string& aabbId : aabbIds)
		{
			auto position = _fe3d->aabb_getLocalPosition(aabbId);
			auto size = _fe3d->aabb_getLocalSize(aabbId);
			auto color = _fe3d->aabb_getColor(aabbId);
			auto isVisible = _fe3d->aabb_isVisible(aabbId);
			auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(aabbId);
			auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(aabbId);

			file
				<< "QUAD3D_AABB "
				<< quadId
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
				<< color.r
				<< " "
				<< color.g
				<< " "
				<< color.b
				<< " "
				<< isVisible
				<< " "
				<< isRaycastResponsive
				<< " "
				<< isCollisionResponsive
				<< endl;
		}

		// ANIMATION
	}

	for(const auto& textId : _addedText3dIds)
	{
		auto aabbIds = _fe3d->text3d_getChildAabbIds(textId);
		auto position = _fe3d->text3d_getPosition(textId);
		auto rotation = _fe3d->text3d_getRotation(textId);
		auto size = _fe3d->text3d_getSize(textId);
		auto content = _fe3d->text3d_getContent(textId);
		auto color = _fe3d->text3d_getColor(textId);
		auto fontMapPath = _fe3d->text3d_getFontMapPath(textId);
		auto isFacingCameraHorizontally = _fe3d->text3d_isFacingCameraHorizontally(textId);
		auto isFacingCameraVertically = _fe3d->text3d_isFacingCameraVertically(textId);
		auto isReflected = _fe3d->text3d_isReflected(textId);
		auto isShadowed = _fe3d->text3d_isShadowed(textId);
		auto lightness = _fe3d->text3d_getLightness(textId);
		auto isBright = _fe3d->text3d_isBright(textId);
		auto opacity = _fe3d->text3d_getOpacity(textId);
		auto minTextureAlpha = _fe3d->text3d_getMinTextureAlpha(textId);
		auto isVisible = _fe3d->text3d_isVisible(textId);
		auto isWireframed = _fe3d->text3d_isWireframed(textId);
		auto wireframeColor = _fe3d->text3d_getWireframeColor(textId);
		auto isFrozen = _fe3d->text3d_isFrozen(textId);
		auto minHeight = _fe3d->text3d_getMinHeight(textId);
		auto maxHeight = _fe3d->text3d_getMaxHeight(textId);

		fontMapPath = (fontMapPath.empty() ? "" : fontMapPath.substr(("projects\\" + _currentProjectId + "\\").size()));

		fontMapPath = (fontMapPath.empty()) ? "?" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), ' ', '?');

		file
			<< textId
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
			<< fontMapPath
			<< " "
			<< isReflected
			<< " "
			<< isShadowed
			<< " "
			<< lightness
			<< " "
			<< isBright
			<< " "
			<< opacity
			<< " "
			<< minTextureAlpha
			<< " "
			<< content
			<< " "
			<< isWireframed
			<< " "
			<< wireframeColor.r
			<< " "
			<< wireframeColor.g
			<< " "
			<< wireframeColor.b
			<< " "
			<< isVisible
			<< " "
			<< isFrozen
			<< " "
			<< minHeight
			<< " "
			<< maxHeight
			<< endl;

		for(const string& aabbId : aabbIds)
		{
			auto position = _fe3d->aabb_getLocalPosition(aabbId);
			auto size = _fe3d->aabb_getLocalSize(aabbId);
			auto color = _fe3d->aabb_getColor(aabbId);
			auto isVisible = _fe3d->aabb_isVisible(aabbId);
			auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(aabbId);
			auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(aabbId);

			file
				<< "TEXT3D_AABB "
				<< textId
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
				<< color.r
				<< " "
				<< color.g
				<< " "
				<< color.b
				<< " "
				<< isVisible
				<< " "
				<< isRaycastResponsive
				<< " "
				<< isCollisionResponsive
				<< endl;
		}
	}

	for(const string& aabbId : _addedAabbIds)
	{
		auto position = _fe3d->aabb_getBasePosition(aabbId);
		auto size = _fe3d->aabb_getBaseSize(aabbId);
		auto color = _fe3d->aabb_getColor(aabbId);
		auto isVisible = _fe3d->aabb_isVisible(aabbId);
		auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(aabbId);
		auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(aabbId);

		file
			<< "AABB "
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
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< isVisible
			<< " "
			<< isRaycastResponsive
			<< " "
			<< isCollisionResponsive
			<< endl;
	}

	for(const auto& pointlightId : _addedPointlightIds)
	{
		auto position = _fe3d->pointlight_getPosition(pointlightId);
		auto radius = _fe3d->pointlight_getRadius(pointlightId);
		auto color = _fe3d->pointlight_getColor(pointlightId);
		auto intensity = _fe3d->pointlight_getIntensity(pointlightId);
		auto shape = static_cast<unsigned int>(_fe3d->pointlight_getShape(pointlightId));

		file
			<< "POINTLIGHT "
			<< pointlightId
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
			<< endl;
	}

	for(const auto& spotlightId : _addedSpotlightIds)
	{
		auto position = _fe3d->spotlight_getPosition(spotlightId);
		auto color = _fe3d->spotlight_getColor(spotlightId);
		auto yaw = _fe3d->spotlight_getYaw(spotlightId);
		auto pitch = _fe3d->spotlight_getPitch(spotlightId);
		auto intensity = _fe3d->spotlight_getIntensity(spotlightId);
		auto angle = _fe3d->spotlight_getAngle(spotlightId);
		auto distance = _fe3d->spotlight_getDistance(spotlightId);

		file
			<< "SPOTLIGHT "
			<< spotlightId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< yaw
			<< " "
			<< pitch
			<< " "
			<< intensity
			<< " "
			<< angle
			<< " "
			<< distance
			<< endl;
	}

	for(const auto& reflectionId : _addedReflectionIds)
	{
		auto position = _fe3d->reflection_getPosition(reflectionId);
		auto exceptionModelId = _fe3d->reflection_getExceptionModelId(reflectionId);

		file
			<< "REFLECTION "
			<< reflectionId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< exceptionModelId
			<< endl;
	}

	for(const auto& soundId : _loadedSoundIds)
	{
		auto position = _fe3d->sound3d_getPosition(soundId);
		auto maxVolume = _fe3d->sound3d_getMaxVolume(soundId);
		auto maxDistance = _fe3d->sound3d_getMaxDistance(soundId);

		file
			<< "SOUND "
			<< soundId
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

	if(_isGraphicsAdded)
	{
		if(_fe3d->gfx_isAmbientLightingEnabled())
		{
			auto ambientLightingColor = _fe3d->gfx_getAmbientLightingColor();
			auto ambientLightingIntensity = _fe3d->gfx_getAmbientLightingIntensity();

			file
				<< "LIGHTING_AMBIENT "
				<< ambientLightingColor.r
				<< " "
				<< ambientLightingColor.g
				<< " "
				<< ambientLightingColor.b
				<< " "
				<< ambientLightingIntensity
				<< endl;
		}

		if(_fe3d->gfx_isDirectionalLightingEnabled())
		{
			auto directionalLightingColor = _fe3d->gfx_getDirectionalLightingColor();
			auto directionalLightingPosition = _fe3d->gfx_getDirectionalLightingPosition();
			auto directionalLightingIntensity = _fe3d->gfx_getDirectionalLightingIntensity();

			file
				<< "LIGHTING_DIRECTIONAL "
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

		if(_fe3d->gfx_isShadowsEnabled())
		{
			auto size = _fe3d->gfx_getShadowSize();
			auto lightness = _fe3d->gfx_getShadowLightness();
			auto position = _fe3d->gfx_getShadowPositionOffset();
			auto lookat = _fe3d->gfx_getShadowLookatOffset();
			auto isFollowingCamera = _fe3d->gfx_isShadowFollowingCamera();
			auto interval = _fe3d->gfx_getShadowInterval();
			auto quality = _fe3d->gfx_getShadowQuality();

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
				<< isFollowingCamera
				<< " "
				<< interval
				<< " "
				<< quality
				<< endl;
		}

		{
			auto planarHeight = _fe3d->gfx_getPlanarReflectionHeight();
			auto cubeQuality = _fe3d->gfx_getCubeReflectionQuality();
			auto planarQuality = _fe3d->gfx_getPlanarReflectionQuality();

			file
				<< "GRAPHICS_REFLECTIONS "
				<< planarHeight
				<< " "
				<< cubeQuality
				<< " "
				<< planarQuality
				<< endl;
		}

		{
			auto planarQuality = _fe3d->gfx_getPlanarReflectionQuality();

			file
				<< "GRAPHICS_REFRACTIONS "
				<< planarQuality
				<< endl;
		}

		if(_fe3d->gfx_isDofEnabled())
		{
			auto dynamic = _fe3d->gfx_isDofDynamic();
			auto blurDistance = _fe3d->gfx_getDofBlurDistance();
			auto maxDistance = _fe3d->gfx_getDofDynamicDistance();
			auto quality = _fe3d->gfx_getDofQuality();

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

		if(_fe3d->gfx_isFogEnabled())
		{
			auto minDistance = _fe3d->gfx_getFogMinDistance();
			auto maxDistance = _fe3d->gfx_getFogMaxDistance();
			auto thickness = _fe3d->gfx_getFogThickness();
			auto color = _fe3d->gfx_getFogColor();

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

		if(_fe3d->gfx_isLensFlareEnabled())
		{
			auto flareMapPath = _fe3d->gfx_getLensFlareMapPath();
			auto intensity = _fe3d->gfx_getLensFlareIntensity();
			auto sensitivity = _fe3d->gfx_getLensFlareSensitivity();

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

		if(_fe3d->gfx_isSkyExposureEnabled())
		{
			file
				<< "GRAPHICS_SKY_EXPOSURE "
				<< _fe3d->gfx_getSkyExposureIntensity()
				<< " "
				<< _fe3d->gfx_getSkyExposureSpeed()
				<< endl;
		}

		if(_fe3d->gfx_isBloomEnabled())
		{
			auto type = static_cast<unsigned int>(_fe3d->gfx_getBloomType());
			auto intensity = _fe3d->gfx_getBloomIntensity();
			auto blurCount = _fe3d->gfx_getBloomBlurCount();
			auto quality = _fe3d->gfx_getBloomQuality();

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
	}

	file.close();

	return true;
}