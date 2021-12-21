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
	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("WorldEditor::saveCustomWorldToFile::1");
	}
	if(_isEditorLoaded)
	{
		Logger::throwError("WorldEditor::saveCustomWorldToFile::2");
	}

	// Warning checking
	if(_customWorldID.empty())
	{
		Logger::throwWarning("Cannot save custom world!");
		return false;
	}

	// Compose file path
	const string filePath = (Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
							 ("projects\\" + _currentProjectID + "\\")) + "worlds\\custom\\" + _customWorldID + ".fe3d");

	// Create or overwrite file
	ofstream file(filePath);

	// Save model level of detail IDs
	vector<string> levelOfDetailEntityIDs;
	for(const auto& modelID : _fe3d.model_getIDs())
	{
		// Check if allowed to save
		bool isCustomWorldModel = find(_customWorldModelIDs.begin(), _customWorldModelIDs.end(), modelID) != _customWorldModelIDs.end();
		if((modelID[0] != '@') && isCustomWorldModel)
		{
			// Check if entity has level of detail entity
			if(!_fe3d.model_getLevelOfDetailEntityID(modelID).empty())
			{
				// Check if ID not already added to list
				if(find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) == levelOfDetailEntityIDs.end())
				{
					levelOfDetailEntityIDs.push_back(_fe3d.model_getLevelOfDetailEntityID(modelID));
				}
			}
		}
	}

	// Sky
	string skyID = _fe3d.sky_getSelectedID();
	if(!skyID.empty() && _hasCustomWorldSky)
	{
		// Data to save
		auto templateID = ("@" + skyID);
		auto color = _fe3d.sky_getColor(skyID);
		auto rotation = _fe3d.sky_getRotation(skyID);
		auto lightness = _fe3d.sky_getInitialLightness(skyID);

		// Write data
		file <<
			"SKY " <<
			skyID << " " <<
			templateID << " " <<
			rotation << " " <<
			lightness << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << endl;
	}

	// Terrain
	string terrainID = _fe3d.terrain_getSelectedID();
	if(!terrainID.empty() && _hasCustomWorldTerrain)
	{
		// Data to save
		string templateID = ("@" + terrainID);

		// Write data
		file <<
			"TERRAIN " <<
			terrainID << " " <<
			templateID << endl;
	}

	// Water
	string waterID = _fe3d.water_getSelectedID();
	if(!waterID.empty() && _hasCustomWorldWater)
	{
		// Data to save
		string templateID = ("@" + waterID);
		auto color = _fe3d.water_getColor(waterID);
		auto speed = _fe3d.water_getSpeed(waterID);
		auto transparency = _fe3d.water_getTransparency(waterID);

		// Write data
		file <<
			"WATER " <<
			waterID << " " <<
			templateID << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << " " <<
			speed.x << " " <<
			speed.y << " " <<
			transparency << endl;
	}

	// Models
	for(const auto& modelID : _fe3d.model_getIDs())
	{
		// Check if allowed to save
		bool isLevelOfDetailEntity = find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) != levelOfDetailEntityIDs.end();
		bool isCustomWorldModel =
			find(_customWorldModelIDs.begin(), _customWorldModelIDs.end(), modelID) != _customWorldModelIDs.end();
		if(((modelID[0] != '@') || isLevelOfDetailEntity) && isCustomWorldModel)
		{
			// Retrieve all bound AABB IDs
			auto aabbIDs = _fe3d.aabb_getChildIDs(modelID, AabbParentEntityType::MODEL);

			// Data to save
			auto isVisible = _fe3d.model_isVisible(modelID);
			auto isFrozen = _fe3d.model_isFrozen(modelID);
			auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d.aabb_isRaycastResponsive(aabbIDs[0]);
			auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d.aabb_isCollisionResponsive(aabbIDs[0]);
			auto position = _fe3d.model_getBasePosition(modelID);
			auto rotation = _fe3d.model_getBaseRotation(modelID);
			auto rotationOrigin = _fe3d.model_getBaseRotationOrigin(modelID);
			auto size = _fe3d.model_getBaseSize(modelID);
			auto color = _fe3d.model_getColor(modelID, "");
			auto minHeight = _fe3d.model_getMinHeight(modelID);
			auto maxHeight = _fe3d.model_getMaxHeight(modelID);
			auto transparency = _fe3d.model_getTransparency(modelID, "");
			auto lightness = _fe3d.model_getLightness(modelID, "");

			// Extract template ID
			string templateID;
			if(_loadedModelIDs.find(modelID) == _loadedModelIDs.end())
			{
				templateID = _outsideLoadedModelIDs.at(modelID);
			}
			else
			{
				templateID = _loadedModelIDs.at(modelID);
			}

			// Write data
			file <<
				"MODEL " <<
				modelID << " " <<
				templateID << " " <<
				isVisible << " " <<
				isFrozen << " " <<
				isAabbRaycastResponsive << " " <<
				isAabbCollisionResponsive << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				rotation.x << " " <<
				rotation.y << " " <<
				rotation.z << " " <<
				rotationOrigin.x << " " <<
				rotationOrigin.y << " " <<
				rotationOrigin.z << " " <<
				size.x << " " <<
				size.y << " " <<
				size.z << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				minHeight << " " <<
				maxHeight << " " <<
				transparency << " " <<
				lightness << " " <<
				_fe3d.model_getPartIDs(modelID).size();

			// Check if model is multi-parted
			auto partIDs = _fe3d.model_getPartIDs(modelID);
			if(partIDs.size() > 1)
			{
				// Write part IDs
				for(const auto& partID : partIDs)
				{
					// Write space
					file << " ";

					// Write part ID
					file << partID;
				}

				// Write part transformations
				for(size_t i = 0; i < partIDs.size(); i++)
				{
					// Part ID cannot be empty
					if(!partIDs[i].empty())
					{
						// Write space
						file << " ";

						// Retrieve transformation
						position = _fe3d.model_getPartPosition(modelID, partIDs[i]);
						rotation = _fe3d.model_getPartRotation(modelID, partIDs[i]);
						rotationOrigin = _fe3d.model_getPartRotationOrigin(modelID, partIDs[i]);
						size = _fe3d.model_getPartSize(modelID, partIDs[i]);

						// Write transformation
						file <<
							partIDs[i] << " " <<
							position.x << " " <<
							position.y << " " <<
							position.z << " " <<
							rotation.x << " " <<
							rotation.y << " " <<
							rotation.z << " " <<
							rotationOrigin.x << " " <<
							rotationOrigin.y << " " <<
							rotationOrigin.z << " " <<
							size.x << " " <<
							size.y << " " <<
							size.z;
					}
				}
			}

			// Write instanced offsets
			if(_fe3d.model_isInstanced(modelID))
			{
				// Check if model has any offsets
				auto instancedOffsets = _fe3d.model_getInstancedOffsets(modelID);
				if(!instancedOffsets.empty())
				{
					// Write space
					file << " ";

					// Write offsets
					for(size_t i = 0; i < instancedOffsets.size(); i++)
					{
						// Write offset
						file <<
							instancedOffsets[i].x << " " <<
							instancedOffsets[i].y << " " <<
							instancedOffsets[i].z;

						// Write space
						if(i != (instancedOffsets.size() - 1))
						{
							file << " ";
						}
					}
				}
			}

			// New line
			file << endl;
		}
	}

	// Animations
	for(const auto& modelID : _fe3d.model_getIDs())
	{
		// Check if allowed to save
		bool isLodModel = find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) != levelOfDetailEntityIDs.end();
		bool isCustomWorldModel =
			find(_customWorldModelIDs.begin(), _customWorldModelIDs.end(), modelID) != _customWorldModelIDs.end();
		if(((modelID[0] != '@') || isLodModel) && isCustomWorldModel)
		{
			// Every playing animation on every model
			//for(const auto& animationID : _animation3dEditor.getStartedModelAnimationIDs(modelID))
			//{
			//	// Retrieve raw animation data for retrieving
			//	string errorMessage = "Tried to retrieve animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";
			//	auto animationData = _animation3dEditor.getAnimationData(animationID, modelID, errorMessage);

			//	// Data to save
			//	auto isPaused = animationData->isPaused();
			//	auto frameIndex = animationData->getFrameIndex();
			//	auto speedMultiplier = animationData->getSpeedMultiplier();
			//	auto remainingLoops = (animationData->getPlayCount() == -1) ? -1 : (animationData->getPlayCount() - 1);
			//	auto fadeFramestep = animationData->getFadeFramestep();

			//	// Write main data
			//	file <<
			//		"ANIMATION " <<
			//		animationID << " " <<
			//		modelID << " " <<
			//		isPaused << " " <<
			//		frameIndex << " " <<
			//		speedMultiplier << " " <<
			//		remainingLoops << " " <<
			//		fadeFramestep << " ";

			//	// Write speeds
			//	unsigned int index = 0;
			//	auto frame = animationData->getFrames().at(animationData->getFrameIndex());
			//	for(const auto& [partID, speed] : frame.getSpeeds())
			//	{
			//		// Write speed
			//		file << (partID.empty() ? "?" : partID) << " " << speed.x << " " << speed.y << " " << speed.z;

			//		// Write space
			//		if(index != (frame.getSpeeds().size() - 1))
			//		{
			//			file << " ";
			//		}
			//		index++;
			//	}

			//	file << endl;
			//}
		}
	}

	// Billboards
	for(const auto& billboardID : _fe3d.billboard_getIDs())
	{
		// Check if allowed to save
		bool isCustomWorldBillboard =
			find(_customWorldBillboardIDs.begin(), _customWorldBillboardIDs.end(), billboardID) != _customWorldBillboardIDs.end();
		if((billboardID[0] != '@') && isCustomWorldBillboard)
		{
			// Retrieve all bound AABB IDs
			auto aabbIDs = _fe3d.aabb_getChildIDs(billboardID, AabbParentEntityType::BILLBOARD);

			// Data to save
			auto isVisible = _fe3d.billboard_isVisible(billboardID);
			auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d.aabb_isRaycastResponsive(aabbIDs[0]);
			auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d.aabb_isCollisionResponsive(aabbIDs[0]);
			auto isFacingX = _fe3d.billboard_isFacingCameraX(billboardID);
			auto isFacingY = _fe3d.billboard_isFacingCameraY(billboardID);
			//auto isAnimationPlaying = _fe3d.billboard_isSpriteAnimationStarted(billboardID);
			//auto isAnimationPaused = _fe3d.billboard_isSpriteAnimationPaused(billboardID);
			auto position = _fe3d.billboard_getPosition(billboardID);
			auto rotation = _fe3d.billboard_getRotation(billboardID);
			auto size = _fe3d.billboard_getSize(billboardID);
			auto color = _fe3d.billboard_getColor(billboardID);
			auto textContent = _fe3d.billboard_getTextContent(billboardID);
			auto lightness = _fe3d.billboard_getLightness(billboardID);
			auto minHeight = _fe3d.billboard_getMinHeight(billboardID);
			auto maxHeight = _fe3d.billboard_getMaxHeight(billboardID);
			//auto remainingAnimationLoops = _fe3d.billboard_getRemainingSpriteAnimationLoops(billboardID);
			//auto animationRowIndex = _fe3d.billboard_getSpriteAnimationRowIndex(billboardID);
			//auto animationColumnIndex = _fe3d.billboard_getSpriteAnimationColumnIndex(billboardID);

			// Convert empty string
			textContent = (textContent.empty()) ? "?" : textContent;

			// Convert spaces
			replace(textContent.begin(), textContent.end(), ' ', '?');

			// Extract template ID
			string templateID;
			if(_loadedBillboardIDs.find(billboardID) == _loadedBillboardIDs.end())
			{
				templateID = _outsideLoadedBillboardIDs.at(billboardID);
			}
			else
			{
				templateID = _loadedBillboardIDs.at(billboardID);
			}

			// Write data
			file <<
				"BILLBOARD " <<
				billboardID << " " <<
				templateID << " " <<
				isVisible << " " <<
				isAabbRaycastResponsive << " " <<
				isAabbCollisionResponsive << " " <<
				isFacingX << " " <<
				isFacingY << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				rotation.x << " " <<
				rotation.y << " " <<
				rotation.z << " " <<
				size.x << " " <<
				size.y << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				textContent << " " <<
				lightness << " " <<
				minHeight << " " <<
				maxHeight << endl;
		}
	}

	// AABBs
	for(const auto& aabbID : _fe3d.aabb_getIDs())
	{
		// Check if allowed to save
		bool isCustomWorldAabb =
			find(_customWorldAabbIDs.begin(), _customWorldAabbIDs.end(), aabbID) != _customWorldAabbIDs.end();
		if((aabbID[0] != '@') && isCustomWorldAabb && _fe3d.aabb_getParentEntityID(aabbID).empty())
		{
			// Data to save
			auto isVisible = _fe3d.aabb_isVisible(aabbID);
			auto isRaycastResponsive = _fe3d.aabb_isRaycastResponsive(aabbID);
			auto isCollisionResponsive = _fe3d.aabb_isCollisionResponsive(aabbID);
			auto position = _fe3d.aabb_getPosition(aabbID);
			auto size = _fe3d.aabb_getSize(aabbID);

			// Write data
			file <<
				"AABB " <<
				aabbID << " " <<
				isVisible << " " <<
				isRaycastResponsive << " " <<
				isCollisionResponsive << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				size.x << " " <<
				size.y << " " <<
				size.z << endl;
		}
	}

	// Sounds
	//for(const auto& soundID : _fe3d.sound3d_getIDs())
	//{
	//	// Check if allowed to save
	//	bool isCustomWorldSound =
	//		find(_customWorldSoundIDs.begin(), _customWorldSoundIDs.end(), soundID) != _customWorldSoundIDs.end();
	//	if((soundID[0] != '@') && isCustomWorldSound && _fe3d.sound_is3D(soundID))
	//	{
	//		// Data to save
	//		auto position = _fe3d.sound_getPosition(soundID);
	//		auto maxVolume = _fe3d.sound_getMaxVolume(soundID);
	//		auto maxDistance = _fe3d.sound_getMaxDistance(soundID);

	//		// Extract template ID
	//		string templateID;
	//		if(_loadedSoundIDs.find(soundID) == _loadedSoundIDs.end())
	//		{
	//			templateID = _outsideLoadedSoundIDs.at(soundID);
	//		}
	//		else
	//		{
	//			templateID = _loadedSoundIDs.at(soundID);
	//		}

	//		// Write data
	//		file <<
	//			"SOUND " <<
	//			soundID << " " <<
	//			templateID << " " <<
	//			position.x << " " <<
	//			position.y << " " <<
	//			position.z << " " <<
	//			maxVolume << " " <<
	//			maxDistance << endl;
	//	}
	//}

	// Pointlights
	for(const auto& pointlightID : _fe3d.pointlight_getIDs())
	{
		// Check if allowed to save
		bool isCustomWorldPointlight =
			find(_customWorldPointlightIDs.begin(), _customWorldPointlightIDs.end(), pointlightID) != _customWorldPointlightIDs.end();
		if((pointlightID[0] != '@') && isCustomWorldPointlight)
		{
			// Data to save
			auto position = _fe3d.pointlight_getPosition(pointlightID);
			auto radius = _fe3d.pointlight_getRadius(pointlightID);
			auto color = _fe3d.pointlight_getColor(pointlightID);
			auto intensity = _fe3d.pointlight_getIntensity(pointlightID);

			// Write data
			file <<
				"POINTLIGHT " <<
				pointlightID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				radius.x << " " <<
				radius.y << " " <<
				radius.z << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				intensity << endl;
		}
	}

	// Spotlights
	for(const auto& spotlightID : _fe3d.spotlight_getIDs())
	{
		// Check if allowed to save
		bool isCustomWorldSpotlight =
			find(_customWorldSpotlightIDs.begin(), _customWorldSpotlightIDs.end(), spotlightID) != _customWorldSpotlightIDs.end();
		if((spotlightID[0] != '@') && isCustomWorldSpotlight)
		{
			// Data to save
			auto position = _fe3d.spotlight_getPosition(spotlightID);
			auto color = _fe3d.spotlight_getColor(spotlightID);
			auto yaw = _fe3d.spotlight_getYaw(spotlightID);
			auto pitch = _fe3d.spotlight_getPitch(spotlightID);
			auto intensity = _fe3d.spotlight_getIntensity(spotlightID);
			auto angle = _fe3d.spotlight_getAngle(spotlightID);
			auto distance = _fe3d.spotlight_getDistance(spotlightID);

			// Write data
			file <<
				"SPOTLIGHT " <<
				spotlightID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				yaw << " " <<
				pitch << " " <<
				intensity << " " <<
				angle << " " <<
				distance << endl;
		}
	}

	// Reflections
	for(const auto& reflectionID : _fe3d.reflection_getIDs())
	{
		// Check if allowed to save
		bool isCustomWorldReflection =
			find(_customWorldReflectionIDs.begin(), _customWorldReflectionIDs.end(), reflectionID) != _customWorldReflectionIDs.end();
		if((reflectionID[0] != '@') && isCustomWorldReflection)
		{
			// Data to save
			auto position = _fe3d.reflection_getPosition(reflectionID);

			// Write data
			file <<
				"REFLECTION " <<
				reflectionID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << endl;
		}
	}

	// Check if allowed to save
	if(_hasCustomWorldLighting)
	{
		// Ambient lighting
		if(_fe3d.gfx_isAmbientLightingEnabled())
		{
			// Data to save
			auto ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
			auto ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

			// Write data
			file <<
				"LIGHTING_AMBIENT " <<
				ambientLightingColor.r << " " <<
				ambientLightingColor.g << " " <<
				ambientLightingColor.b << " " <<
				ambientLightingIntensity << endl;
		}

		// Directional lighting
		if(_fe3d.gfx_isDirectionalLightingEnabled())
		{
			// Data to save
			auto directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
			auto directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
			auto directionalLightingIntensity = _fe3d.gfx_getDirectionalLightingIntensity();

			// Write data
			file <<
				"LIGHTING_DIRECTIONAL " <<
				directionalLightingPosition.x << " " <<
				directionalLightingPosition.y << " " <<
				directionalLightingPosition.z << " " <<
				directionalLightingColor.r << " " <<
				directionalLightingColor.g << " " <<
				directionalLightingColor.b << " " <<
				directionalLightingIntensity << endl;
		}
	}

	// Check if allowed to save
	if(_hasCustomWorldGraphics)
	{
		// Shadow settings
		if(_fe3d.gfx_isShadowsEnabled())
		{
			// Data to save
			auto size = _fe3d.gfx_getShadowSize();
			auto lightness = _fe3d.gfx_getShadowLightness();
			auto eye = _fe3d.gfx_getShadowEyePosition();
			auto center = _fe3d.gfx_getShadowCenterPosition();
			auto isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
			auto interval = _fe3d.gfx_getShadowInterval();

			// Write data
			file <<
				"GRAPHICS_SHADOWS " <<
				size << " " <<
				lightness << " " <<
				Tools::vec2str(eye) << " " <<
				Tools::vec2str(center) << " " <<
				isFollowingCamera << " " <<
				interval << endl;
		}

		// Motion blur settings
		if(_fe3d.gfx_isMotionBlurEnabled())
		{
			file << "GRAPHICS_MOTION_BLUR " << _fe3d.gfx_getMotionBlurStrength() << endl;
		}

		// DOF settings
		if(_fe3d.gfx_isDofEnabled())
		{
			// Data to save
			auto dynamic = _fe3d.gfx_isDofDynamic();
			auto blurDistance = _fe3d.gfx_getDofBlurDistance();
			auto maxDistance = _fe3d.gfx_getMaxDofDistance();

			// Write data
			file <<
				"GRAPHICS_DOF " <<
				dynamic << " " <<
				blurDistance << " " <<
				maxDistance << endl;
		}

		// Fog settings
		if(_fe3d.gfx_isFogEnabled())
		{
			// Data to save
			auto minDistance = _fe3d.gfx_getFogMinDistance();
			auto maxDistance = _fe3d.gfx_getFogMaxDistance();
			auto thickness = _fe3d.gfx_getFogThickness();
			auto color = _fe3d.gfx_getFogColor();

			// Write data
			file <<
				"GRAPHICS_FOG " <<
				minDistance << " " <<
				maxDistance << " " <<
				thickness << " " <<
				Tools::vec2str(color) << endl;
		}

		// Lens flare settings
		if(_fe3d.gfx_isLensFlareEnabled())
		{
			// Data to save
			auto flareMapPath = _fe3d.gfx_getLensFlareMapPath();
			auto intensity = _fe3d.gfx_getLensFlareIntensity();
			auto sensitivity = _fe3d.gfx_getLensFlareSensitivity();

			// Convert empty string
			flareMapPath = (flareMapPath.empty()) ? "?" : flareMapPath;

			// Convert spaces
			replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

			// Write data
			file <<
				"GRAPHICS_LENS_FLARE " <<
				flareMapPath << " " <<
				intensity << " " <<
				sensitivity << endl;
		}

		// Sky exposure settings
		if(_fe3d.gfx_isSkyExposureEnabled())
		{
			file << "GRAPHICS_SKY_EXPOSURE " << _fe3d.gfx_getSkyExposureIntensity() << " " << _fe3d.gfx_getSkyExposureSpeed() << endl;
		}

		// Bloom settings
		if(_fe3d.gfx_isBloomEnabled())
		{
			// Data to save
			auto type = static_cast<unsigned int>(_fe3d.gfx_getBloomType());
			auto intensity = _fe3d.gfx_getBloomIntensity();
			auto blurCount = _fe3d.gfx_getBloomBlurCount();

			// Write data
			file <<
				"GRAPHICS_BLOOM " <<
				type << " " <<
				intensity << " " <<
				blurCount << endl;
		}
	}

	// Close file
	file.close();

	// Reset custom world builder values
	_customWorldID = "";
	_hasCustomWorldLighting = false;
	_hasCustomWorldGraphics = false;
	_hasCustomWorldSky = false;
	_hasCustomWorldTerrain = false;
	_hasCustomWorldWater = false;
	_customWorldModelIDs.clear();
	_customWorldBillboardIDs.clear();
	_customWorldAabbIDs.clear();
	_customWorldSoundIDs.clear();
	_customWorldPointlightIDs.clear();
	_customWorldSpotlightIDs.clear();

	// Return
	return true;
}