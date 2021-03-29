#include "scene_editor.hpp"

#include <fstream>
#include <algorithm>

void SceneEditor::saveCustomSceneToFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> SceneEditor::saveCustomSceneToFile()");
	}
	if (_isEditorLoaded)
	{
		_fe3d.logger_throwWarning("Tried to call saveCustomSceneToFile() from within scene editor!");
	}
	if (_customSceneID.empty())
	{
		_fe3d.logger_throwWarning("Cannot save custom scene!");
	}

	// Check if scene directory still exists
	string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scenes\\";
	if (!_fe3d.misc_isDirectoryExisting(directoryPath) || !_fe3d.misc_isDirectoryExisting(directoryPath + "custom\\"))
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: scenes folder(s) missing!");
		return;
	}

	// Create or overwrite file
	string fullFilePath = (directoryPath + "custom\\" + _customSceneID + ".fe3d");
	std::ofstream file(fullFilePath);

	// Save model LOD IDs
	vector<string> lodIDs;
	for (auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneModel = std::find(_customSceneModelIDs.begin(), _customSceneModelIDs.end(), modelID) != _customSceneModelIDs.end();
		if ((modelID[0] != '@') && isCustomSceneModel)
		{
			// Check if entity has LOD ID
			if (!_fe3d.modelEntity_getLevelOfDetailEntityID(modelID).empty())
			{
				// Check if ID not already added to list
				if (std::find(lodIDs.begin(), lodIDs.end(), modelID) == lodIDs.end())
				{
					lodIDs.push_back(_fe3d.modelEntity_getLevelOfDetailEntityID(modelID));
				}
			}
		}
	}

	// Sky
	string skyID = _fe3d.skyEntity_getSelectedID();
	if (!skyID.empty() && _hasCustomSceneSky)
	{
		// Data to save
		string previewID = "@" + skyID;
		Vec3 color = _fe3d.skyEntity_getColor(skyID);
		float rotationSpeed = _fe3d.skyEntity_getRotationSpeed(skyID);
		float lightness = _fe3d.skyEntity_getOriginalLightness(skyID);

		// Write data
		file <<
			"SKY " <<
			skyID << " " <<
			previewID << " " <<
			rotationSpeed << " " <<
			lightness << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << std::endl;
	}

	// Terrain
	string terrainID = _fe3d.terrainEntity_getSelectedID();
	if (!terrainID.empty() && _hasCustomSceneTerrain)
	{
		// Data to save
		string previewID = "@" + terrainID;

		// Write data
		file <<
			"TERRAIN " <<
			terrainID << " " <<
			previewID << std::endl;
	}

	// Water
	string waterID = _fe3d.waterEntity_getSelectedID();
	if (!waterID.empty() && _hasCustomSceneWater)
	{
		// Data to save
		string previewID = "@" + waterID;
		Vec3 color = _fe3d.waterEntity_getColor(waterID);
		Vec2 speed = _fe3d.waterEntity_getSpeed(waterID);
		float transparency = _fe3d.waterEntity_getTransparency(waterID);

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
			transparency << std::endl;
	}

	// Models
	for (auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isLodModel = std::find(lodIDs.begin(), lodIDs.end(), modelID) != lodIDs.end();
		bool isCustomSceneModel =
			std::find(_customSceneModelIDs.begin(), _customSceneModelIDs.end(), modelID) != _customSceneModelIDs.end();
		if (((modelID[0] != '@') || isLodModel) && isCustomSceneModel)
		{
			// Retrieve all bound AABB IDs
			auto aabbIDs = _fe3d.aabbEntity_getBoundIDs(modelID, true, false);

			// Data to save
			auto isVisible = _fe3d.modelEntity_isVisible(modelID);
			auto isFrozen = _fe3d.modelEntity_isStaticToCamera(modelID);
			auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d.aabbEntity_isRaycastResponsive(aabbIDs.front());
			auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d.aabbEntity_isCollisionResponsive(aabbIDs.front());
			auto position = _fe3d.modelEntity_getPosition(modelID);
			auto rotation = _fe3d.modelEntity_getRotation(modelID);
			auto rotationOrigin = _fe3d.modelEntity_getRotationOrigin(modelID);
			auto size = _fe3d.modelEntity_getSize(modelID);
			auto color = _fe3d.modelEntity_getColor(modelID);
			auto minHeight = _fe3d.modelEntity_getMinHeight(modelID);
			auto maxHeight = _fe3d.modelEntity_getMaxHeight(modelID);
			auto alpha = _fe3d.modelEntity_getAlpha(modelID);
			auto lightness = _fe3d.modelEntity_getLightness(modelID);

			// Extract preview ID
			string previewID;
			if (_loadedModelIDs.find(modelID) == _loadedModelIDs.end())
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
			auto partNames = _fe3d.modelEntity_getPartIDs(modelID);
			if (partNames.size() > 1)
			{
				// Write part names
				for (auto& partName : partNames)
				{
					// Write space
					file << " ";

					// Write part name
					file << partName;
				}

				// Write part transformations
				for (unsigned int i = 0; i < partNames.size(); i++)
				{
					// Part name cannot be empty
					if (!partNames[i].empty())
					{
						// Write space
						file << " ";

						// Retrieve transformation
						position = _fe3d.modelEntity_getPosition(modelID, partNames[i]);
						rotation = _fe3d.modelEntity_getRotation(modelID, partNames[i]);
						rotationOrigin = _fe3d.modelEntity_getRotationOrigin(modelID, partNames[i]);
						size = _fe3d.modelEntity_getSize(modelID, partNames[i]);

						// Write transformation
						file <<
							partNames[i] << " " <<
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
			if (_fe3d.modelEntity_isInstanced(modelID))
			{
				// Check if model has any offsets
				auto instancedOffsets = _fe3d.modelEntity_getInstancedOffsets(modelID);
				if (!instancedOffsets.empty())
				{
					// Write space
					file << " ";

					// Write offsets
					for (unsigned int i = 0; i < instancedOffsets.size(); i++)
					{
						// Write offset
						file <<
							instancedOffsets[i].x << " " <<
							instancedOffsets[i].y << " " <<
							instancedOffsets[i].z;

						// Write space
						if (i != (instancedOffsets.size() - 1))
						{
							file << " ";
						}
					}
				}
			}

			// New line
			file << std::endl;
		}
	}

	// Animations
	for (auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isLodModel = std::find(lodIDs.begin(), lodIDs.end(), modelID) != lodIDs.end();
		bool isCustomSceneModel =
			std::find(_customSceneModelIDs.begin(), _customSceneModelIDs.end(), modelID) != _customSceneModelIDs.end();
		if (((modelID[0] != '@') || isLodModel) && isCustomSceneModel)
		{
			// Every playing animation on every model
			for (auto& animationID : _animationEditor.getStartedAnimationIDs(modelID))
			{
				// Data to save
				auto animationData = _animationEditor.getAnimationData(animationID, modelID);
				auto isPaused = animationData->isPaused;
				auto frameIndex = animationData->frameIndex;
				auto speedMultiplier = animationData->speedMultiplier;
				auto remainingLoops = (animationData->timesToPlay == -1) ? -1 : (animationData->timesToPlay - 1);

				// Write main data
				file <<
					"ANIMATION " <<
					animationID << " " <<
					modelID << " " <<
					isPaused << " " <<
					frameIndex << " " <<
					speedMultiplier << " " <<
					remainingLoops << " ";

				// Write speeds
				unsigned int index = 0;
				auto speeds = animationData->frames[animationData->frameIndex].speeds;
				for (auto& [partID, speed] : speeds)
				{
					// Write speed
					file << (partID.empty() ? "?" : partID) << " " << speed;

					// Write space
					if (index != (speeds.size() - 1))
					{
						file << " ";
					}
					index++;
				}

				file << std::endl;
			}
		}
	}

	// Billboards
	for (auto& billboardID : _fe3d.billboardEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneBillboard =
			std::find(_customSceneBillboardIDs.begin(), _customSceneBillboardIDs.end(), billboardID) != _customSceneBillboardIDs.end();
		if ((billboardID[0] != '@') && isCustomSceneBillboard)
		{
			// Retrieve all bound AABB IDs
			auto aabbIDs = _fe3d.aabbEntity_getBoundIDs(billboardID, false, true);

			// Data to save
			auto isVisible = _fe3d.billboardEntity_isVisible(billboardID);
			auto isAabbRaycastResponsive = aabbIDs.empty() ? false : _fe3d.aabbEntity_isRaycastResponsive(aabbIDs.front());
			auto isAabbCollisionResponsive = aabbIDs.empty() ? false : _fe3d.aabbEntity_isCollisionResponsive(aabbIDs.front());
			auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(billboardID);
			auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(billboardID);
			auto isAnimationPlaying = _fe3d.billboardEntity_isAnimationStarted(billboardID);
			auto isAnimationPaused = _fe3d.billboardEntity_isAnimationPaused(billboardID);
			auto position = _fe3d.billboardEntity_getPosition(billboardID);
			auto rotation = _fe3d.billboardEntity_getRotation(billboardID);
			auto size = _fe3d.billboardEntity_getSize(billboardID);
			auto color = _fe3d.billboardEntity_getColor(billboardID);
			auto textContent = _fe3d.billboardEntity_getTextContent(billboardID);
			auto lightness = _fe3d.billboardEntity_getLightness(billboardID);
			auto minHeight = _fe3d.billboardEntity_getMinHeight(billboardID);
			auto maxHeight = _fe3d.billboardEntity_getMaxHeight(billboardID);
			auto remainingAnimationRepeats = _fe3d.billboardEntity_getRemainingAnimationLoops(billboardID);
			auto animationRowIndex = _fe3d.billboardEntity_getAnimationRowIndex(billboardID);
			auto animationColumnIndex = _fe3d.billboardEntity_getAnimationColumnIndex(billboardID);

			// Perform empty string & space conversions
			textContent = (textContent == "") ? "?" : textContent;
			std::replace(textContent.begin(), textContent.end(), ' ', '?');

			// Extract preview ID
			string previewID;
			if (_loadedBillboardIDs.find(billboardID) == _loadedBillboardIDs.end())
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
				remainingAnimationRepeats << " " <<
				animationRowIndex << " " <<
				animationColumnIndex << std::endl;
		}
	}

	// AABBs
	for (auto& aabbID : _fe3d.aabbEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneAabb =
			std::find(_customSceneAabbIDs.begin(), _customSceneAabbIDs.end(), aabbID) != _customSceneAabbIDs.end();
		if ((aabbID[0] != '@') && isCustomSceneAabb && _fe3d.aabbEntity_getParentID(aabbID).empty())
		{
			// Data to save
			bool isVisible = _fe3d.aabbEntity_isVisible(aabbID);
			bool isRaycastResponsive = _fe3d.aabbEntity_isRaycastResponsive(aabbID);
			bool isCollisionResponsive = _fe3d.aabbEntity_isCollisionResponsive(aabbID);
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
				size.z << std::endl;
		}
	}

	// Audio casters
	for (auto& audioID : _fe3d.audioEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneAudio =
			std::find(_customSceneAudioIDs.begin(), _customSceneAudioIDs.end(), audioID) != _customSceneAudioIDs.end();
		if ((audioID[0] != '@') && isCustomSceneAudio && _fe3d.audioEntity_is3D(audioID))
		{
			// Data to save
			auto position = _fe3d.audioEntity_getPosition(audioID);
			auto maxVolume = _fe3d.audioEntity_getMaxVolume(audioID);
			auto maxDistance = _fe3d.audioEntity_getMaxDistance(audioID);

			// Extract preview ID
			string previewID;
			if (_loadedAudioIDs.find(audioID) == _loadedAudioIDs.end())
			{
				previewID = _outsideLoadedAudioIDs.at(audioID);
			}
			else
			{
				previewID = _loadedAudioIDs.at(audioID);
			}

			// Write data
			file <<
				"AUDIO " <<
				audioID << " " <<
				previewID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				maxVolume << " " <<
				maxDistance << std::endl;
		}
	}

	// Check if allowed to save
	if (_hasCustomSceneLighting)
	{
		// Ambient lighting
		if (_fe3d.gfx_isAmbientLightingEnabled())
		{
			// Data to save
			Vec3 ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
			float ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

			// Write data
			file <<
				"AMBIENT_LIGHT " <<
				ambientLightingColor.r << " " <<
				ambientLightingColor.g << " " <<
				ambientLightingColor.b << " " <<
				ambientLightingIntensity << std::endl;
		}

		// Directional lighting
		if (_fe3d.gfx_isDirectionalLightingEnabled())
		{
			// Data to save
			Vec3 directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
			Vec3 directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
			float directionalLightingIntensity = _fe3d.gfx_getDirectionalLightingIntensity();
			float billboardSize = _fe3d.billboardEntity_getSize("@@lightSource").x;
			float billboardLightness = _fe3d.billboardEntity_getLightness("@@lightSource");

			// Write data
			file <<
				"DIRECTIONAL_LIGHT " <<
				directionalLightingPosition.x << " " <<
				directionalLightingPosition.y << " " <<
				directionalLightingPosition.z << " " <<
				directionalLightingColor.r << " " <<
				directionalLightingColor.g << " " <<
				directionalLightingColor.b << " " <<
				directionalLightingIntensity << " " <<
				billboardSize << " " <<
				billboardLightness << std::endl;
		}
	}

	// Write point lights
	for (auto& lightID : _fe3d.lightEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneLight =
			std::find(_customSceneLightIDs.begin(), _customSceneLightIDs.end(), lightID) != _customSceneLightIDs.end();
		if ((lightID[0] != '@') && isCustomSceneLight)
		{
			// Data to save
			auto position = _fe3d.lightEntity_getPosition(lightID);
			auto color = _fe3d.lightEntity_getColor(lightID);
			auto intensity = _fe3d.lightEntity_getIntensity(lightID);
			auto distance = _fe3d.lightEntity_getDistanceFactor(lightID);

			// Write data
			file <<
				"POINT_LIGHT " <<
				lightID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				intensity << " " <<
				distance << std::endl;
		}
	}

	// LOD distance settings
	file << "LOD_DISTANCE " << _fe3d.misc_getLevelOfDetailDistance() << std::endl;

	// Check if allowed to save
	if (_hasCustomSceneGraphics)
	{
		// Shadow settings
		if (_fe3d.gfx_isShadowsEnabled())
		{
			// Data to save
			float size = _fe3d.gfx_getShadowSize();
			float lightness = _fe3d.gfx_getShadowLightness();
			Vec3 position = _fe3d.gfx_getShadowEyePosition();
			Vec3 center = _fe3d.gfx_getShadowCenter();
			bool isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
			bool isSoftShadowed = _fe3d.gfx_isSoftShadowingEnabled();
			int interval = _fe3d.gfx_getShadowInterval();

			// Write data
			file <<
				"GRAPHICS_SHADOWS " <<
				size << " " <<
				lightness << " " <<
				_fe3d.misc_vec2str(position) << " " <<
				_fe3d.misc_vec2str(center) << " " <<
				isFollowingCamera << " " <<
				isSoftShadowed << " " <<
				interval << std::endl;
		}

		// Motion blur settings
		if (_fe3d.gfx_isMotionBlurEnabled())
		{
			file << "GRAPHICS_MOTIONBLUR " << _fe3d.gfx_getMotionBlurStrength() << std::endl;
		}

		// DOF settings
		if (_fe3d.gfx_isDofEnabled())
		{
			// Data to save
			bool dynamic = _fe3d.gfx_isDofDynamic();
			float blurDistance = _fe3d.gfx_getDofBlurDistance();
			float maxDistance = _fe3d.gfx_getaMaxDofDistance();

			// Write data
			file <<
				"GRAPHICS_DOF " <<
				dynamic << " " <<
				blurDistance << " " <<
				maxDistance << std::endl;
		}

		// Fog settings
		if (_fe3d.gfx_isFogEnabled())
		{
			// Data to save
			float minDistance = _fe3d.gfx_getFogMinDistance();
			float maxDistance = _fe3d.gfx_getFogMaxDistance();
			float thickness = _fe3d.gfx_getFogThickness();
			Vec3 color = _fe3d.gfx_getFogColor();

			// Write data
			file <<
				"GRAPHICS_FOG " <<
				minDistance << " " <<
				maxDistance << " " <<
				thickness << " " <<
				_fe3d.misc_vec2str(color) << std::endl;
		}

		// Lens flare settings
		if (_fe3d.gfx_isLensFlareEnabled())
		{
			// Data to save
			string flareMapPath = _fe3d.gfx_getLensFlareMapPath();
			float intensity = _fe3d.gfx_getLensFlareIntensity();
			float multiplier = _fe3d.gfx_getLensFlareMultiplier();

			// Perform empty string & space conversions
			flareMapPath = (flareMapPath == "") ? "?" : flareMapPath;
			std::replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

			// Write data
			file <<
				"GRAPHICS_LENSFLARE " <<
				flareMapPath << " " <<
				intensity << " " <<
				multiplier << std::endl;
		}

		// Sky HDR settings
		if (_fe3d.gfx_isSkyHdrEnabled())
		{
			file << "GRAPHICS_SKYHDR " << _fe3d.gfx_getSkyHdrBrightnessFactor() << std::endl;
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
	_customSceneAudioIDs.clear();
	_customSceneLightIDs.clear();
}