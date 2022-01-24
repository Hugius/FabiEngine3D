#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;

const bool WorldEditor::saveCustomWorldToFile()
{
	//if(_currentProjectId.empty())
	//{
	//	Logger::throwError("WorldEditor::saveCustomWorldToFile::1");
	//}
	//if(_isEditorLoaded)
	//{
	//	Logger::throwError("WorldEditor::saveCustomWorldToFile::2");
	//}

	//if(_customWorldID.empty())
	//{
	//	Logger::throwWarning("Cannot save custom world!");
	//	return false;
	//}

	//const auto rootPath = Tools::getRootDirectoryPath();
	//const auto filePath = (rootPath + (Config::getInst().isApplicationExported() ? "" :
	//					   ("projects\\" + _currentProjectId + "\\")) + "worlds\\custom\\" + _customWorldID + ".fe3d");

	//ofstream file(filePath);

	//vector<string> levelOfDetailEntityIds;
	//for(const auto& modelId : _fe3d->model_getIds())
	//{
	//	bool isCustomWorldModel = find(_customWorldModelIds.begin(), _customWorldModelIds.end(), modelId) != _customWorldModelIds.end();
	//	if((modelId[0] != '@') && isCustomWorldModel)
	//	{
	//		if(!_fe3d->model_getLevelOfDetailEntityId(modelId).empty())
	//		{
	//			if(find(levelOfDetailEntityIds.begin(), levelOfDetailEntityIds.end(), modelId) == levelOfDetailEntityIds.end())
	//			{
	//				levelOfDetailEntityIds.push_back(_fe3d->model_getLevelOfDetailEntityId(modelId));
	//			}
	//		}
	//	}
	//}

	//string skyID = _fe3d->sky_getSelectedID();
	//if(!skyID.empty() && _hasCustomWorldSky)
	//{
	//	auto templateID = ("@" + skyID);
	//	auto color = _fe3d->sky_getColor(skyID);
	//	auto rotation = _fe3d->sky_getRotation(skyID);
	//	auto lightness = _fe3d->sky_getInitialLightness(skyID);

	//	file <<
	//		"SKY " <<
	//		skyID << " " <<
	//		templateID << " " <<
	//		rotation << " " <<
	//		lightness << " " <<
	//		color.r << " " <<
	//		color.g << " " <<
	//		color.b << endl;
	//}

	//string terrainID = _fe3d->terrain_getSelectedID();
	//if(!terrainID.empty() && _hasCustomWorldTerrain)
	//{
	//	string templateID = ("@" + terrainID);

	//	file <<
	//		"TERRAIN " <<
	//		terrainID << " " <<
	//		templateID << endl;
	//}

	//string waterID = _fe3d->water_getSelectedID();
	//if(!waterID.empty() && _hasCustomWorldWater)
	//{
	//	string templateID = ("@" + waterID);
	//	auto color = _fe3d->water_getColor(waterID);
	//	auto speed = _fe3d->water_getSpeed(waterID);
	//	auto opacity = _fe3d->water_getOpacity(waterID);

	//	file <<
	//		"WATER " <<
	//		waterID << " " <<
	//		templateID << " " <<
	//		color.r << " " <<
	//		color.g << " " <<
	//		color.b << " " <<
	//		speed.x << " " <<
	//		speed.y << " " <<
	//		opacity << endl;
	//}

	//for(const auto& modelId : _fe3d->model_getIds())
	//{
	//	bool isLevelOfDetailEntity = find(levelOfDetailEntityIds.begin(), levelOfDetailEntityIds.end(), modelId) != levelOfDetailEntityIds.end();
	//	bool isCustomWorldModel =
	//		find(_customWorldModelIds.begin(), _customWorldModelIds.end(), modelId) != _customWorldModelIds.end();
	//	if(((modelId[0] != '@') || isLevelOfDetailEntity) && isCustomWorldModel)
	//	{
	//		auto aabbIDs = _fe3d->aabb_getChildIDs(modelId, AabbParentEntityType::MODEL);

	//		auto isVisible = _fe3d->model_isVisible(modelId);
	//		auto isFrozen = _fe3d->model_isFrozen(modelId);
	//		auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d->aabb_isRaycastResponsive(aabbIDs[0]);
	//		auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d->aabb_isCollisionResponsive(aabbIDs[0]);
	//		auto position = _fe3d->model_getBasePosition(modelId);
	//		auto rotation = _fe3d->model_getBaseRotation(modelId);
	//		auto rotationOrigin = _fe3d->model_getBaseRotationOrigin(modelId);
	//		auto size = _fe3d->model_getBaseSize(modelId);
	//		auto color = _fe3d->model_getColor(modelId, "");
	//		auto minHeight = _fe3d->model_getMinHeight(modelId);
	//		auto maxHeight = _fe3d->model_getMaxHeight(modelId);
	//		auto opacity = _fe3d->model_getOpacity(modelId, "");
	//		auto lightness = _fe3d->model_getLightness(modelId, "");

	//		string templateID;
	//		if(_loadedModelIds.find(modelId) == _loadedModelIds.end())
	//		{
	//			templateID = _outsideLoadedModelIds.at(modelId);
	//		}
	//		else
	//		{
	//			templateID = _loadedModelIds.at(modelId);
	//		}

	//		file <<
	//			"MODEL " <<
	//			modelId << " " <<
	//			templateID << " " <<
	//			isVisible << " " <<
	//			isFrozen << " " <<
	//			isAabbRaycastResponsive << " " <<
	//			isAabbCollisionResponsive << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			rotation.x << " " <<
	//			rotation.y << " " <<
	//			rotation.z << " " <<
	//			rotationOrigin.x << " " <<
	//			rotationOrigin.y << " " <<
	//			rotationOrigin.z << " " <<
	//			size.x << " " <<
	//			size.y << " " <<
	//			size.z << " " <<
	//			color.r << " " <<
	//			color.g << " " <<
	//			color.b << " " <<
	//			minHeight << " " <<
	//			maxHeight << " " <<
	//			opacity << " " <<
	//			lightness << " " <<
	//			_fe3d->model_getPartIds(modelId).size();

	//		auto partIds = _fe3d->model_getPartIds(modelId);
	//		if(partIds.size() > 1)
	//		{
	//			for(const auto& partId : partIds)
	//			{
	//				file << " ";

	//				file << partId;
	//			}

	//			for(size_t i = 0; i < partIds.size(); i++)
	//			{
	//				if(!partIds[i].empty())
	//				{
	//					file << " ";

	//					position = _fe3d->model_getPartPosition(modelId, partIds[i]);
	//					rotation = _fe3d->model_getPartRotation(modelId, partIds[i]);
	//					rotationOrigin = _fe3d->model_getPartRotationOrigin(modelId, partIds[i]);
	//					size = _fe3d->model_getPartSize(modelId, partIds[i]);

	//					file <<
	//						partIds[i] << " " <<
	//						position.x << " " <<
	//						position.y << " " <<
	//						position.z << " " <<
	//						rotation.x << " " <<
	//						rotation.y << " " <<
	//						rotation.z << " " <<
	//						rotationOrigin.x << " " <<
	//						rotationOrigin.y << " " <<
	//						rotationOrigin.z << " " <<
	//						size.x << " " <<
	//						size.y << " " <<
	//						size.z;
	//				}
	//			}
	//		}

	//		file << endl;
	//	}
	//}

	//for(const auto& modelId : _fe3d->model_getIds())
	//{
	//	bool isLodModel = find(levelOfDetailEntityIds.begin(), levelOfDetailEntityIds.end(), modelId) != levelOfDetailEntityIds.end();
	//	bool isCustomWorldModel =
	//		find(_customWorldModelIds.begin(), _customWorldModelIds.end(), modelId) != _customWorldModelIds.end();
	//	if(((modelId[0] != '@') || isLodModel) && isCustomWorldModel)
	//	{
	//		//for(const auto& animationId : _animation3dEditor->getStartedModelAnimationIds(modelId))
	//		//{
	//		//	// Retrieve raw animation data for retrieving
	//		//	string errorMessage = "Tried to retrieve animation with id \"" + animationId + "\" on model with id \"" + modelId + "\": ";
	//		//	auto animationData = _animation3dEditor->getAnimationData(animationId, modelId, errorMessage);

	//		//	// Data to save
	//		//	auto isPaused = animationData->isPaused();
	//		//	auto frameIndex = animationData->getFrameIndex();
	//		//	auto speedMultiplier = animationData->getSpeedMultiplier();
	//		//	auto remainingLoops = (animationData->getPlayCount() == -1) ? -1 : (animationData->getPlayCount() - 1);
	//		//	auto fadeFramestep = animationData->getFadeFramestep();

	//		//	// Write main data
	//		//	file <<
	//		//		"ANIMATION " <<
	//		//		animationId << " " <<
	//		//		modelId << " " <<
	//		//		isPaused << " " <<
	//		//		frameIndex << " " <<
	//		//		speedMultiplier << " " <<
	//		//		remainingLoops << " " <<
	//		//		fadeFramestep << " ";

	//		//	// Write speeds
	//		//	unsigned int index = 0;
	//		//	auto frame = animationData->getFrames().at(animationData->getFrameIndex());
	//		//	for(const auto& [key, speed] : frame.getSpeeds())
	//		//	{
	//		//		// Write speed
	//		//		file << (partId.empty() ? "?" : partId) << " " << speed.x << " " << speed.y << " " << speed.z;

	//		//		// Write space
	//		//		if(index != (frame.getSpeeds().size() - 1))
	//		//		{
	//		//			file << " ";
	//		//		}
	//		//		index++;
	//		//	}

	//		//	file << endl;
	//		//}
	//	}
	//}

	//for(const auto& quadId : _fe3d->quad3d_getIds())
	//{
	//	bool isCustomWorldQuad3d =
	//		find(_customWorldQuadIds.begin(), _customWorldQuadIds.end(), quadId) != _customWorldQuadIds.end();
	//	if((quadId[0] != '@') && isCustomWorldQuad3d)
	//	{
	//		auto aabbIDs = _fe3d->aabb_getChildIDs(quadId, AabbParentEntityType::QUAD3D);

	//		auto isVisible = _fe3d->quad3d_isVisible(quadId);
	//		auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d->aabb_isRaycastResponsive(aabbIDs[0]);
	//		auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d->aabb_isCollisionResponsive(aabbIDs[0]);
	//		auto isFacingX = _fe3d->quad3d_isFacingCameraX(quadId);
	//		auto isFacingY = _fe3d->quad3d_isFacingCameraY(quadId);
	//		//auto isAnimationPlaying = _fe3d->quad3d_isSpriteAnimationStarted(quadId);
	//		//auto isAnimationPaused = _fe3d->quad3d_isSpriteAnimationPaused(quadId);
	//		auto position = _fe3d->quad3d_getPosition(quadId);
	//		auto rotation = _fe3d->quad3d_getRotation(quadId);
	//		auto size = _fe3d->quad3d_getSize(quadId);
	//		auto color = _fe3d->quad3d_getColor(quadId);
	//		//auto textContent = _fe3d->quad3d_getTextContent(quadId);
	//		auto lightness = _fe3d->quad3d_getLightness(quadId);
	//		auto minHeight = _fe3d->quad3d_getMinHeight(quadId);
	//		auto maxHeight = _fe3d->quad3d_getMaxHeight(quadId);
	//		//auto remainingAnimationLoops = _fe3d->quad3d_getRemainingSpriteAnimationLoops(quadId);
	//		//auto animationRowIndex = _fe3d->quad3d_getSpriteAnimationRowIndex(quadId);
	//		//auto animationColumnIndex = _fe3d->quad3d_getSpriteAnimationColumnIndex(quadId);

	//		//textContent = (textContent.empty()) ? "?" : textContent;

	//		//replace(textContent.begin(), textContent.end(), ' ', '?');

	//		string templateID;
	//		if(_loadedQuadIds.find(quadId) == _loadedQuadIds.end())
	//		{
	//			templateID = _outsideLoadedQuadIds.at(quadId);
	//		}
	//		else
	//		{
	//			templateID = _loadedQuadIds.at(quadId);
	//		}

	//		file <<
	//			"QUAD3D " <<
	//			quadId << " " <<
	//			templateID << " " <<
	//			isVisible << " " <<
	//			isAabbRaycastResponsive << " " <<
	//			isAabbCollisionResponsive << " " <<
	//			isFacingX << " " <<
	//			isFacingY << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			rotation.x << " " <<
	//			rotation.y << " " <<
	//			rotation.z << " " <<
	//			size.x << " " <<
	//			size.y << " " <<
	//			color.r << " " <<
	//			color.g << " " <<
	//			color.b << " " <<
	//			textContent << " " <<
	//			lightness << " " <<
	//			minHeight << " " <<
	//			maxHeight << endl;
	//	}
	//}

	//for(const auto& aabbID : _fe3d->aabb_getIds())
	//{
	//	bool isCustomWorldAabb =
	//		find(_customWorldAabbIDs.begin(), _customWorldAabbIDs.end(), aabbID) != _customWorldAabbIDs.end();
	//	if((aabbID[0] != '@') && isCustomWorldAabb && _fe3d->aabb_getParentEntityId(aabbID).empty())
	//	{
	//		auto isVisible = _fe3d->aabb_isVisible(aabbID);
	//		auto isRaycastResponsive = _fe3d->aabb_isRaycastResponsive(aabbID);
	//		auto isCollisionResponsive = _fe3d->aabb_isCollisionResponsive(aabbID);
	//		auto position = _fe3d->aabb_getPosition(aabbID);
	//		auto size = _fe3d->aabb_getSize(aabbID);

	//		file <<
	//			"AABB " <<
	//			aabbID << " " <<
	//			isVisible << " " <<
	//			isRaycastResponsive << " " <<
	//			isCollisionResponsive << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			size.x << " " <<
	//			size.y << " " <<
	//			size.z << endl;
	//	}
	//}

	////for(const auto& soundID : _fe3d->sound3d_getIds())
	////{
	////	// Check if allowed to save
	////	bool isCustomWorldSound =
	////		find(_customWorldSoundIDs.begin(), _customWorldSoundIDs.end(), soundID) != _customWorldSoundIDs.end();
	////	if((soundID[0] != '@') && isCustomWorldSound && _fe3d->sound_is3D(soundID))
	////	{
	////		// Data to save
	////		auto position = _fe3d->sound_getPosition(soundID);
	////		auto maxVolume = _fe3d->sound_getMaxVolume(soundID);
	////		auto maxDistance = _fe3d->sound_getMaxDistance(soundID);

	////		// Extract template id
	////		string templateID;
	////		if(_loadedSoundIDs.find(soundID) == _loadedSoundIDs.end())
	////		{
	////			templateID = _outsideLoadedSoundIDs.at(soundID);
	////		}
	////		else
	////		{
	////			templateID = _loadedSoundIDs.at(soundID);
	////		}

	////		// Write data
	////		file <<
	////			"SOUND " <<
	////			soundID << " " <<
	////			templateID << " " <<
	////			position.x << " " <<
	////			position.y << " " <<
	////			position.z << " " <<
	////			maxVolume << " " <<
	////			maxDistance << endl;
	////	}
	////}

	//for(const auto& pointlightID : _fe3d->pointlight_getIds())
	//{
	//	bool isCustomWorldPointlight =
	//		find(_customWorldPointlightIDs.begin(), _customWorldPointlightIDs.end(), pointlightID) != _customWorldPointlightIDs.end();
	//	if((pointlightID[0] != '@') && isCustomWorldPointlight)
	//	{
	//		auto position = _fe3d->pointlight_getPosition(pointlightID);
	//		auto radius = _fe3d->pointlight_getRadius(pointlightID);
	//		auto color = _fe3d->pointlight_getColor(pointlightID);
	//		auto intensity = _fe3d->pointlight_getIntensity(pointlightID);

	//		file <<
	//			"POINTLIGHT " <<
	//			pointlightID << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			radius.x << " " <<
	//			radius.y << " " <<
	//			radius.z << " " <<
	//			color.r << " " <<
	//			color.g << " " <<
	//			color.b << " " <<
	//			intensity << endl;
	//	}
	//}

	//for(const auto& spotlightID : _fe3d->spotlight_getIds())
	//{
	//	bool isCustomWorldSpotlight =
	//		find(_customWorldSpotlightIDs.begin(), _customWorldSpotlightIDs.end(), spotlightID) != _customWorldSpotlightIDs.end();
	//	if((spotlightID[0] != '@') && isCustomWorldSpotlight)
	//	{
	//		auto position = _fe3d->spotlight_getPosition(spotlightID);
	//		auto color = _fe3d->spotlight_getColor(spotlightID);
	//		auto yaw = _fe3d->spotlight_getYaw(spotlightID);
	//		auto pitch = _fe3d->spotlight_getPitch(spotlightID);
	//		auto intensity = _fe3d->spotlight_getIntensity(spotlightID);
	//		auto angle = _fe3d->spotlight_getAngle(spotlightID);
	//		auto distance = _fe3d->spotlight_getDistance(spotlightID);

	//		file <<
	//			"SPOTLIGHT " <<
	//			spotlightID << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			color.r << " " <<
	//			color.g << " " <<
	//			color.b << " " <<
	//			yaw << " " <<
	//			pitch << " " <<
	//			intensity << " " <<
	//			angle << " " <<
	//			distance << endl;
	//	}
	//}

	//for(const auto& reflectionID : _fe3d->reflection_getIds())
	//{
	//	bool isCustomWorldReflection =
	//		find(_customWorldReflectionIDs.begin(), _customWorldReflectionIDs.end(), reflectionID) != _customWorldReflectionIDs.end();
	//	if((reflectionID[0] != '@') && isCustomWorldReflection)
	//	{
	//		auto position = _fe3d->reflection_getPosition(reflectionID);

	//		file <<
	//			"REFLECTION " <<
	//			reflectionID << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << endl;
	//	}
	//}

	//if(_hasCustomWorldLighting)
	//{
	//	if(_fe3d->gfx_isAmbientLightingEnabled())
	//	{
	//		auto ambientLightingColor = _fe3d->gfx_getAmbientLightingColor();
	//		auto ambientLightingIntensity = _fe3d->gfx_getAmbientLightingIntensity();

	//		file <<
	//			"LIGHTING_AMBIENT " <<
	//			ambientLightingColor.r << " " <<
	//			ambientLightingColor.g << " " <<
	//			ambientLightingColor.b << " " <<
	//			ambientLightingIntensity << endl;
	//	}

	//	if(_fe3d->gfx_isDirectionalLightingEnabled())
	//	{
	//		auto directionalLightingColor = _fe3d->gfx_getDirectionalLightingColor();
	//		auto directionalLightingPosition = _fe3d->gfx_getDirectionalLightingPosition();
	//		auto directionalLightingIntensity = _fe3d->gfx_getDirectionalLightingIntensity();

	//		file <<
	//			"LIGHTING_DIRECTIONAL " <<
	//			directionalLightingPosition.x << " " <<
	//			directionalLightingPosition.y << " " <<
	//			directionalLightingPosition.z << " " <<
	//			directionalLightingColor.r << " " <<
	//			directionalLightingColor.g << " " <<
	//			directionalLightingColor.b << " " <<
	//			directionalLightingIntensity << endl;
	//	}
	//}

	//if(_hasCustomWorldGraphics)
	//{
	//	if(_fe3d->gfx_isShadowsEnabled())
	//	{
	//		auto size = _fe3d->gfx_getShadowSize();
	//		auto lightness = _fe3d->gfx_getShadowLightness();
	//		auto eye = _fe3d->gfx_getShadowEyePosition();
	//		auto center = _fe3d->gfx_getShadowCenterPosition();
	//		auto isFollowingCamera = _fe3d->gfx_isShadowFollowingCamera();
	//		auto interval = _fe3d->gfx_getShadowInterval();

	//		file <<
	//			"GRAPHICS_SHADOWS " <<
	//			size << " " <<
	//			lightness << " " <<
	//			Tools::vec2str(eye) << " " <<
	//			Tools::vec2str(center) << " " <<
	//			isFollowingCamera << " " <<
	//			interval << endl;
	//	}

	//	if(_fe3d->gfx_isMotionBlurEnabled())
	//	{
	//		file << "GRAPHICS_MOTION_BLUR " << _fe3d->gfx_getMotionBlurStrength() << endl;
	//	}

	//	if(_fe3d->gfx_isDofEnabled())
	//	{
	//		auto dynamic = _fe3d->gfx_isDofDynamic();
	//		auto blurDistance = _fe3d->gfx_getDofBlurDistance();
	//		auto maxDistance = _fe3d->gfx_getDofDynamicDistance();

	//		file <<
	//			"GRAPHICS_DOF " <<
	//			dynamic << " " <<
	//			blurDistance << " " <<
	//			maxDistance << endl;
	//	}

	//	if(_fe3d->gfx_isFogEnabled())
	//	{
	//		auto minDistance = _fe3d->gfx_getFogMinDistance();
	//		auto maxDistance = _fe3d->gfx_getFogMaxDistance();
	//		auto thickness = _fe3d->gfx_getFogThickness();
	//		auto color = _fe3d->gfx_getFogColor();

	//		file <<
	//			"GRAPHICS_FOG " <<
	//			minDistance << " " <<
	//			maxDistance << " " <<
	//			thickness << " " <<
	//			Tools::vec2str(color) << endl;
	//	}

	//	if(_fe3d->gfx_isLensFlareEnabled())
	//	{
	//		auto flareMapPath = _fe3d->gfx_getLensFlareMapPath();
	//		auto intensity = _fe3d->gfx_getLensFlareIntensity();
	//		auto sensitivity = _fe3d->gfx_getLensFlareSensitivity();

	//		flareMapPath = (flareMapPath.empty()) ? "?" : flareMapPath;

	//		replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

	//		file <<
	//			"GRAPHICS_LENS_FLARE " <<
	//			flareMapPath << " " <<
	//			intensity << " " <<
	//			sensitivity << endl;
	//	}

	//	if(_fe3d->gfx_isSkyExposureEnabled())
	//	{
	//		file << "GRAPHICS_SKY_EXPOSURE " << _fe3d->gfx_getSkyExposureIntensity() << " " << _fe3d->gfx_getSkyExposureSpeed() << endl;
	//	}

	//	if(_fe3d->gfx_isBloomEnabled())
	//	{
	//		auto type = static_cast<unsigned int>(_fe3d->gfx_getBloomType());
	//		auto intensity = _fe3d->gfx_getBloomIntensity();
	//		auto blurCount = _fe3d->gfx_getBloomBlurCount();

	//		file <<
	//			"GRAPHICS_BLOOM " <<
	//			type << " " <<
	//			intensity << " " <<
	//			blurCount << endl;
	//	}
	//}

	//file.close();

	//_customWorldID = "";
	//_hasCustomWorldLighting = false;
	//_hasCustomWorldGraphics = false;
	//_hasCustomWorldSky = false;
	//_hasCustomWorldTerrain = false;
	//_hasCustomWorldWater = false;
	//_customWorldModelIds.clear();
	//_customWorldQuadIds.clear();
	//_customWorldAabbIDs.clear();
	//_customWorldSoundIDs.clear();
	//_customWorldPointlightIDs.clear();
	//_customWorldSpotlightIDs.clear();

	return true;
}