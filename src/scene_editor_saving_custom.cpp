#include "scene_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;

const bool SceneEditor::saveCustomSceneToFile()
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("SceneEditor::saveCustomSceneToFile::1");
	}
	if(_isEditorLoaded)
	{
		Logger::throwError("SceneEditor::saveCustomSceneToFile::2");
	}

	// Warning checking
	if(_customSceneID.empty())
	{
		Logger::throwWarning("Cannot save custom scene!");
		return false;
	}

	// Compose file path
	const string filePath = (Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
							 ("projects\\" + _currentProjectID + "\\")) + "scenes\\custom\\" + _customSceneID + ".fe3d");

	// Create or overwrite file
	ofstream file(filePath);

	// Save model LOD IDs
	vector<string> lodEntityIDs;
	for(const auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneModel = find(_customSceneModelIDs.begin(), _customSceneModelIDs.end(), modelID) != _customSceneModelIDs.end();
		if((modelID[0] != '@') && isCustomSceneModel)
		{
			// Check if entity has LOD ID
			if(!_fe3d.modelEntity_getLevelOfDetailEntityID(modelID).empty())
			{
				// Check if ID not already added to list
				if(find(lodEntityIDs.begin(), lodEntityIDs.end(), modelID) == lodEntityIDs.end())
				{
					lodEntityIDs.push_back(_fe3d.modelEntity_getLevelOfDetailEntityID(modelID));
				}
			}
		}
	}

	// Sky
	string skyID = _fe3d.skyEntity_getSelectedID();
	if(!skyID.empty() && _hasCustomSceneSky)
	{
		// Data to save
		auto previewID = ("@" + skyID);
		auto color = _fe3d.skyEntity_getColor(skyID);
		auto rotationSpeed = _fe3d.skyEntity_getRotationSpeed(skyID);
		auto lightness = _fe3d.skyEntity_getOriginalLightness(skyID);

		// Write data
		file <<
			"SKY " <<
			skyID << " " <<
			previewID << " " <<
			rotationSpeed << " " <<
			lightness << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << endl;
	}

	// Terrain
	string terrainID = _fe3d.terrainEntity_getSelectedID();
	if(!terrainID.empty() && _hasCustomSceneTerrain)
	{
		// Data to save
		string previewID = ("@" + terrainID);

		// Write data
		file <<
			"TERRAIN " <<
			terrainID << " " <<
			previewID << endl;
	}

	// Water
	string waterID = _fe3d.waterEntity_getSelectedID();
	if(!waterID.empty() && _hasCustomSceneWater)
	{
		// Data to save
		string previewID = ("@" + waterID);
		auto color = _fe3d.waterEntity_getColor(waterID);
		auto speed = _fe3d.waterEntity_getSpeed(waterID);
		auto transparency = _fe3d.waterEntity_getTransparency(waterID);

		// Write data
		file <<
			"WATER " <<
			waterID << " " <<
			previewID << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << " " <<
			speed.x << " " <<
			speed.y << " " <<
			transparency << endl;
	}

	// Models
	for(const auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isLodModel = find(lodEntityIDs.begin(), lodEntityIDs.end(), modelID) != lodEntityIDs.end();
		bool isCustomSceneModel =
			find(_customSceneModelIDs.begin(), _customSceneModelIDs.end(), modelID) != _customSceneModelIDs.end();
		if(((modelID[0] != '@') || isLodModel) && isCustomSceneModel)
		{
			// Retrieve all bound AABB IDs
			auto aabbIDs = _fe3d.aabbEntity_getChildIDs(modelID, AabbParentType::MODEL_ENTITY);

			// Data to save
			auto isVisible = _fe3d.modelEntity_isVisible(modelID);
			auto isFrozen = _fe3d.modelEntity_isStaticToCamera(modelID);
			auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d.aabbEntity_isRaycastResponsive(aabbIDs.front());
			auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d.aabbEntity_isCollisionResponsive(aabbIDs.front());
			auto position = _fe3d.modelEntity_getBasePosition(modelID);
			auto rotation = _fe3d.modelEntity_getBaseRotation(modelID);
			auto rotationOrigin = _fe3d.modelEntity_getBaseRotationOrigin(modelID);
			auto size = _fe3d.modelEntity_getBaseSize(modelID);
			auto color = _fe3d.modelEntity_getColor(modelID, "");
			auto minHeight = _fe3d.modelEntity_getMinHeight(modelID);
			auto maxHeight = _fe3d.modelEntity_getMaxHeight(modelID);
			auto alpha = _fe3d.modelEntity_getAlpha(modelID, "");
			auto lightness = _fe3d.modelEntity_getLightness(modelID, "");

			// Extract preview ID
			string previewID;
			if(_loadedModelIDs.find(modelID) == _loadedModelIDs.end())
			{
				previewID = _outsideLoadedModelIDs.at(modelID);
			}
			else
			{
				previewID = _loadedModelIDs.at(modelID);
			}

			// Write data
			file <<
				"MODEL " <<
				modelID << " " <<
				previewID << " " <<
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
				alpha << " " <<
				lightness << " " <<
				_fe3d.modelEntity_getPartIDs(modelID).size();

			// Check if model is multi-parted
			auto partIDs = _fe3d.modelEntity_getPartIDs(modelID);
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
						position = _fe3d.modelEntity_getPartPosition(modelID, partIDs[i]);
						rotation = _fe3d.modelEntity_getPartRotation(modelID, partIDs[i]);
						rotationOrigin = _fe3d.modelEntity_getPartRotationOrigin(modelID, partIDs[i]);
						size = _fe3d.modelEntity_getPartSize(modelID, partIDs[i]);

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
			if(_fe3d.modelEntity_isInstanced(modelID))
			{
				// Check if model has any offsets
				auto instancedOffsets = _fe3d.modelEntity_getInstancedOffsets(modelID);
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
	for(const auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isLodModel = find(lodEntityIDs.begin(), lodEntityIDs.end(), modelID) != lodEntityIDs.end();
		bool isCustomSceneModel =
			find(_customSceneModelIDs.begin(), _customSceneModelIDs.end(), modelID) != _customSceneModelIDs.end();
		if(((modelID[0] != '@') || isLodModel) && isCustomSceneModel)
		{
			// Every playing animation on every model
			for(const auto& animationID : _animationEditor.getStartedAnimationIDs(modelID))
			{
				// Retrieve raw animation data for retrieving
				string errorMessage = "Tried to retrieve animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";
				auto animationData = _animationEditor.getAnimationData(animationID, modelID, errorMessage);

				// Data to save
				auto isPaused = animationData->isPaused();
				auto frameIndex = animationData->getFrameIndex();
				auto speedMultiplier = animationData->getSpeedMultiplier();
				auto remainingLoops = (animationData->getTimesToPlay() == -1) ? -1 : (animationData->getTimesToPlay() - 1);
				auto fadeFramestep = animationData->getFadeFramestep();

				// Write main data
				file <<
					"ANIMATION " <<
					animationID << " " <<
					modelID << " " <<
					isPaused << " " <<
					frameIndex << " " <<
					speedMultiplier << " " <<
					remainingLoops << " " <<
					fadeFramestep << " ";

				// Write speeds
				unsigned int index = 0;
				auto frame = animationData->getFrames().at(animationData->getFrameIndex());
				for(const auto& [partID, speed] : frame.getSpeeds())
				{
					// Write speed
					file << (partID.empty() ? "?" : partID) << " " << speed.x << " " << speed.y << " " << speed.z;

					// Write space
					if(index != (frame.getSpeeds().size() - 1))
					{
						file << " ";
					}
					index++;
				}

				file << endl;
			}
		}
	}

	// Billboards
	for(const auto& billboardID : _fe3d.billboardEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneBillboard =
			find(_customSceneBillboardIDs.begin(), _customSceneBillboardIDs.end(), billboardID) != _customSceneBillboardIDs.end();
		if((billboardID[0] != '@') && isCustomSceneBillboard)
		{
			// Retrieve all bound AABB IDs
			auto aabbIDs = _fe3d.aabbEntity_getChildIDs(billboardID, AabbParentType::BILLBOARD_ENTITY);

			// Data to save
			auto isVisible = _fe3d.billboardEntity_isVisible(billboardID);
			auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d.aabbEntity_isRaycastResponsive(aabbIDs.front());
			auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d.aabbEntity_isCollisionResponsive(aabbIDs.front());
			auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(billboardID);
			auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(billboardID);
			auto isAnimationPlaying = _fe3d.billboardEntity_isSpriteAnimationStarted(billboardID);
			auto isAnimationPaused = _fe3d.billboardEntity_isSpriteAnimationPaused(billboardID);
			auto position = _fe3d.billboardEntity_getPosition(billboardID);
			auto rotation = _fe3d.billboardEntity_getRotation(billboardID);
			auto size = _fe3d.billboardEntity_getSize(billboardID);
			auto color = _fe3d.billboardEntity_getColor(billboardID);
			auto textContent = _fe3d.billboardEntity_getTextContent(billboardID);
			auto lightness = _fe3d.billboardEntity_getLightness(billboardID);
			auto minHeight = _fe3d.billboardEntity_getMinHeight(billboardID);
			auto maxHeight = _fe3d.billboardEntity_getMaxHeight(billboardID);
			auto remainingAnimationLoops = _fe3d.billboardEntity_getRemainingSpriteAnimationLoops(billboardID);
			auto animationRowIndex = _fe3d.billboardEntity_getSpriteAnimationRowIndex(billboardID);
			auto animationColumnIndex = _fe3d.billboardEntity_getSpriteAnimationColumnIndex(billboardID);

			// Convert empty string
			textContent = (textContent.empty()) ? "?" : textContent;

			// Convert spaces
			replace(textContent.begin(), textContent.end(), ' ', '?');

			// Extract preview ID
			string previewID;
			if(_loadedBillboardIDs.find(billboardID) == _loadedBillboardIDs.end())
			{
				previewID = _outsideLoadedBillboardIDs.at(billboardID);
			}
			else
			{
				previewID = _loadedBillboardIDs.at(billboardID);
			}

			// Write data
			file <<
				"BILLBOARD " <<
				billboardID << " " <<
				previewID << " " <<
				isVisible << " " <<
				isAabbRaycastResponsive << " " <<
				isAabbCollisionResponsive << " " <<
				isFacingX << " " <<
				isFacingY << " " <<
				isAnimationPlaying << " " <<
				isAnimationPaused << " " <<
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
				maxHeight << " " <<
				remainingAnimationLoops << " " <<
				animationRowIndex << " " <<
				animationColumnIndex << endl;
		}
	}

	// AABBs
	for(const auto& aabbID : _fe3d.aabbEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneAabb =
			find(_customSceneAabbIDs.begin(), _customSceneAabbIDs.end(), aabbID) != _customSceneAabbIDs.end();
		if((aabbID[0] != '@') && isCustomSceneAabb && _fe3d.aabbEntity_getParentID(aabbID).empty())
		{
			// Data to save
			auto isVisible = _fe3d.aabbEntity_isVisible(aabbID);
			auto isRaycastResponsive = _fe3d.aabbEntity_isRaycastResponsive(aabbID);
			auto isCollisionResponsive = _fe3d.aabbEntity_isCollisionResponsive(aabbID);
			auto position = _fe3d.aabbEntity_getPosition(aabbID);
			auto size = _fe3d.aabbEntity_getSize(aabbID);

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
	for(const auto& soundID : _fe3d.sound_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneSound =
			find(_customSceneSoundIDs.begin(), _customSceneSoundIDs.end(), soundID) != _customSceneSoundIDs.end();
		if((soundID[0] != '@') && isCustomSceneSound && _fe3d.sound_is3D(soundID))
		{
			// Data to save
			auto position = _fe3d.sound_getPosition(soundID);
			auto maxVolume = _fe3d.sound_getMaxVolume(soundID);
			auto maxDistance = _fe3d.sound_getMaxDistance(soundID);

			// Extract preview ID
			string previewID;
			if(_loadedSoundIDs.find(soundID) == _loadedSoundIDs.end())
			{
				previewID = _outsideLoadedSoundIDs.at(soundID);
			}
			else
			{
				previewID = _loadedSoundIDs.at(soundID);
			}

			// Write data
			file <<
				"SOUND " <<
				soundID << " " <<
				previewID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				maxVolume << " " <<
				maxDistance << endl;
		}
	}

	// Pointlights
	for(const auto& pointlightID : _fe3d.pointlightEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomScenePointlight =
			find(_customScenePointlightIDs.begin(), _customScenePointlightIDs.end(), pointlightID) != _customScenePointlightIDs.end();
		if((pointlightID[0] != '@') && isCustomScenePointlight)
		{
			// Data to save
			auto position = _fe3d.pointlightEntity_getPosition(pointlightID);
			auto radius = _fe3d.pointlightEntity_getRadius(pointlightID);
			auto color = _fe3d.pointlightEntity_getColor(pointlightID);
			auto intensity = _fe3d.pointlightEntity_getIntensity(pointlightID);

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
	for(const auto& spotlightID : _fe3d.spotlightEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneSpotlight =
			find(_customSceneSpotlightIDs.begin(), _customSceneSpotlightIDs.end(), spotlightID) != _customSceneSpotlightIDs.end();
		if((spotlightID[0] != '@') && isCustomSceneSpotlight)
		{
			// Data to save
			auto position = _fe3d.spotlightEntity_getPosition(spotlightID);
			auto color = _fe3d.spotlightEntity_getColor(spotlightID);
			auto yaw = _fe3d.spotlightEntity_getYaw(spotlightID);
			auto pitch = _fe3d.spotlightEntity_getPitch(spotlightID);
			auto intensity = _fe3d.spotlightEntity_getIntensity(spotlightID);
			auto angle = _fe3d.spotlightEntity_getAngle(spotlightID);
			auto distance = _fe3d.spotlightEntity_getDistance(spotlightID);

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
	for(const auto& reflectionID : _fe3d.reflectionEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneReflection =
			find(_customSceneReflectionIDs.begin(), _customSceneReflectionIDs.end(), reflectionID) != _customSceneReflectionIDs.end();
		if((reflectionID[0] != '@') && isCustomSceneReflection)
		{
			// Data to save
			auto position = _fe3d.reflectionEntity_getPosition(reflectionID);

			// Write data
			file <<
				"REFLECTION " <<
				reflectionID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << endl;
		}
	}

	// LOD distance settings
	file << "LOD_DISTANCE " << _fe3d.misc_getLevelOfDetailDistance() << endl;

	// Planar reflection height
	file << "PLANAR_REFLECTION_HEIGHT " << _fe3d.gfx_getPlanarReflectionHeight() << endl;

	// Check if allowed to save
	if(_hasCustomSceneLighting)
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
			auto billboardSize = _fe3d.billboardEntity_getSize("@@directionalLightSource").x;
			auto billboardLightness = _fe3d.billboardEntity_getLightness("@@directionalLightSource");

			// Write data
			file <<
				"LIGHTING_DIRECTIONAL " <<
				directionalLightingPosition.x << " " <<
				directionalLightingPosition.y << " " <<
				directionalLightingPosition.z << " " <<
				directionalLightingColor.r << " " <<
				directionalLightingColor.g << " " <<
				directionalLightingColor.b << " " <<
				directionalLightingIntensity << " " <<
				billboardSize << " " <<
				billboardLightness << endl;
		}
	}

	// Check if allowed to save
	if(_hasCustomSceneGraphics)
	{
		// Shadow settings
		if(_fe3d.gfx_isShadowsEnabled())
		{
			// Data to save
			auto size = _fe3d.gfx_getShadowSize();
			auto lightness = _fe3d.gfx_getShadowLightness();
			auto position = _fe3d.gfx_getShadowEye();
			auto center = _fe3d.gfx_getShadowCenter();
			auto isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
			auto interval = _fe3d.gfx_getShadowInterval();

			// Write data
			file <<
				"GRAPHICS_SHADOWS " <<
				size << " " <<
				lightness << " " <<
				Tools::vec2str(position) << " " <<
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
			auto maxDistance = _fe3d.gfx_getaMaxDofDistance();

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

	// Reset custom scene builder values
	_customSceneID = "";
	_hasCustomSceneLighting = false;
	_hasCustomSceneGraphics = false;
	_hasCustomSceneSky = false;
	_hasCustomSceneTerrain = false;
	_hasCustomSceneWater = false;
	_customSceneModelIDs.clear();
	_customSceneBillboardIDs.clear();
	_customSceneAabbIDs.clear();
	_customSceneSoundIDs.clear();
	_customScenePointlightIDs.clear();
	_customSceneSpotlightIDs.clear();

	// Return
	return true;
}