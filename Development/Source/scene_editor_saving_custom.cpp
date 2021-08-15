#include "scene_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;

bool SceneEditor::saveCustomSceneToFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwFatalError("SceneEditor::saveCustomSceneToFile::1");
	}
	if (_isEditorLoaded)
	{
		Logger::throwFatalError("SceneEditor::saveCustomSceneToFile::2");
	}

	// Warning checking
	if (_customSceneID.empty())
	{
		Logger::throwWarning("Cannot save custom scene!");
		return false;
	}

	// Compose file path
	const string filePath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scenes\\custom\\" + _customSceneID + ".fe3d");

	// Create or overwrite file
	ofstream file(filePath);

	// Save model LOD IDs
	vector<string> lodIDs;
	for (const auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneModel = find(_customSceneModelIDs.begin(), _customSceneModelIDs.end(), modelID) != _customSceneModelIDs.end();
		if ((modelID[0] != '@') && isCustomSceneModel)
		{
			// Check if entity has LOD ID
			if (!_fe3d.modelEntity_getLevelOfDetailEntityID(modelID).empty())
			{
				// Check if ID not already added to list
				if (find(lodIDs.begin(), lodIDs.end(), modelID) == lodIDs.end())
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
		auto previewID = "@" + skyID;
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
	if (!terrainID.empty() && _hasCustomSceneTerrain)
	{
		// Data to save
		string previewID = "@" + terrainID;

		// Write data
		file <<
			"TERRAIN " <<
			terrainID << " " <<
			previewID << endl;
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
			transparency << endl;
	}

	// Models
	for (const auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isLodModel = find(lodIDs.begin(), lodIDs.end(), modelID) != lodIDs.end();
		bool isCustomSceneModel =
			find(_customSceneModelIDs.begin(), _customSceneModelIDs.end(), modelID) != _customSceneModelIDs.end();
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
			auto partIDs = _fe3d.modelEntity_getPartIDs(modelID);
			if (partIDs.size() > 1)
			{
				// Write part IDs
				for (const auto& partID : partIDs)
				{
					// Write space
					file << " ";

					// Write part ID
					file << partID;
				}

				// Write part transformations
				for (size_t i = 0; i < partIDs.size(); i++)
				{
					// Part ID cannot be empty
					if (!partIDs[i].empty())
					{
						// Write space
						file << " ";

						// Retrieve transformation
						position = _fe3d.modelEntity_getPosition(modelID, partIDs[i]);
						rotation = _fe3d.modelEntity_getRotation(modelID, partIDs[i]);
						rotationOrigin = _fe3d.modelEntity_getRotationOrigin(modelID, partIDs[i]);
						size = _fe3d.modelEntity_getSize(modelID, partIDs[i]);

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
			if (_fe3d.modelEntity_isInstanced(modelID))
			{
				// Check if model has any offsets
				auto instancedOffsets = _fe3d.modelEntity_getInstancedOffsets(modelID);
				if (!instancedOffsets.empty())
				{
					// Write space
					file << " ";

					// Write offsets
					for (size_t i = 0; i < instancedOffsets.size(); i++)
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
			file << endl;
		}
	}

	// Animations
	for (const auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isLodModel = find(lodIDs.begin(), lodIDs.end(), modelID) != lodIDs.end();
		bool isCustomSceneModel =
			find(_customSceneModelIDs.begin(), _customSceneModelIDs.end(), modelID) != _customSceneModelIDs.end();
		if (((modelID[0] != '@') || isLodModel) && isCustomSceneModel)
		{
			// Every playing animation on every model
			for (const auto& animationID : _animationEditor.getStartedAnimationIDs(modelID))
			{
				// Retrieve raw animation data for retrieving
				string errorMessage = "Trying to retrieve animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";
				auto animationData = _animationEditor.getAnimationData(animationID, modelID, errorMessage);

				// Data to save
				auto isPaused		 = animationData->isPaused;
				auto frameIndex		 = animationData->frameIndex;
				auto speedMultiplier = animationData->speedMultiplier;
				auto remainingLoops  = (animationData->timesToPlay == -1) ? -1 : (animationData->timesToPlay - 1);
				auto fadeFramestep   = animationData->fadeFramestep;

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
				auto speeds = animationData->frames[animationData->frameIndex].speeds;
				for (const auto& [partID, speed] : speeds)
				{
					// Write speed
					file << (partID.empty() ? "?" : partID) << " " << speed.x << " " << speed.y << " " << speed.z;

					// Write space
					if (index != (speeds.size() - 1))
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
	for (const auto& billboardID : _fe3d.billboardEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneBillboard =
			find(_customSceneBillboardIDs.begin(), _customSceneBillboardIDs.end(), billboardID) != _customSceneBillboardIDs.end();
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

			// Perform empty string & space conversions
			textContent = (textContent.empty()) ? "?" : textContent;
			replace(textContent.begin(), textContent.end(), ' ', '?');

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
				remainingAnimationLoops << " " <<
				animationRowIndex << " " <<
				animationColumnIndex << endl;
		}
	}

	// AABBs
	for (const auto& aabbID : _fe3d.aabbEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneAabb =
			find(_customSceneAabbIDs.begin(), _customSceneAabbIDs.end(), aabbID) != _customSceneAabbIDs.end();
		if ((aabbID[0] != '@') && isCustomSceneAabb && _fe3d.aabbEntity_getParentID(aabbID).empty())
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

	// Sound casters
	for (const auto& soundID : _fe3d.sound_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneSound =
			find(_customSceneSoundIDs.begin(), _customSceneSoundIDs.end(), soundID) != _customSceneSoundIDs.end();
		if ((soundID[0] != '@') && isCustomSceneSound && _fe3d.sound_is3D(soundID))
		{
			// Data to save
			auto position = _fe3d.sound_getPosition(soundID);
			auto maxVolume = _fe3d.sound_getMaxVolume(soundID);
			auto maxDistance = _fe3d.sound_getMaxDistance(soundID);

			// Extract preview ID
			string previewID;
			if (_loadedSoundIDs.find(soundID) == _loadedSoundIDs.end())
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

	// Check if allowed to save
	if (_hasCustomSceneLighting)
	{
		// Ambient lighting
		if (_fe3d.gfx_isAmbientLightingEnabled())
		{
			// Data to save
			auto ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
			auto ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

			// Write data
			file <<
				"AMBIENT_LIGHT " <<
				ambientLightingColor.r << " " <<
				ambientLightingColor.g << " " <<
				ambientLightingColor.b << " " <<
				ambientLightingIntensity << endl;
		}

		// Directional lighting
		if (_fe3d.gfx_isDirectionalLightingEnabled())
		{
			// Data to save
			auto directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
			auto directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
			auto directionalLightingIntensity = _fe3d.gfx_getDirectionalLightingIntensity();
			auto billboardSize = _fe3d.billboardEntity_getSize("@@lightSource").x;
			auto billboardLightness = _fe3d.billboardEntity_getLightness("@@lightSource");

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
				billboardLightness << endl;
		}
	}

	// Write point lights
	for (const auto& lightID : _fe3d.lightEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isCustomSceneLight =
			find(_customSceneLightIDs.begin(), _customSceneLightIDs.end(), lightID) != _customSceneLightIDs.end();
		if ((lightID[0] != '@') && isCustomSceneLight)
		{
			// Data to save
			auto position = _fe3d.lightEntity_getPosition(lightID);
			auto radius = _fe3d.lightEntity_getRadius(lightID);
			auto color = _fe3d.lightEntity_getColor(lightID);
			auto intensity = _fe3d.lightEntity_getIntensity(lightID);

			// Write data
			file <<
				"POINT_LIGHT " <<
				lightID << " " <<
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

	// LOD distance settings
	file << "LOD_DISTANCE " << _fe3d.misc_getLevelOfDetailDistance() << endl;

	// Reflection height
	file << "SCENE_REFLECTION_HEIGHT " << _fe3d.gfx_getSceneReflectionHeight() << endl;

	// Check if allowed to save
	if (_hasCustomSceneGraphics)
	{
		// Shadow settings
		if (_fe3d.gfx_isShadowsEnabled())
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
				_fe3d.misc_vec2str(position) << " " <<
				_fe3d.misc_vec2str(center) << " " <<
				isFollowingCamera << " " <<
				interval << endl;
		}

		// Motion blur settings
		if (_fe3d.gfx_isMotionBlurEnabled())
		{
			file << "GRAPHICS_MOTION_BLUR " << _fe3d.gfx_getMotionBlurStrength() << endl;
		}

		// DOF settings
		if (_fe3d.gfx_isDofEnabled())
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
		if (_fe3d.gfx_isFogEnabled())
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
				_fe3d.misc_vec2str(color) << endl;
		}

		// Lens flare settings
		if (_fe3d.gfx_isLensFlareEnabled())
		{
			// Data to save
			auto flareMapPath = _fe3d.gfx_getLensFlareMapPath();
			auto intensity = _fe3d.gfx_getLensFlareIntensity();
			auto multiplier = _fe3d.gfx_getLensFlareMultiplier();

			// Perform empty string & space conversions
			flareMapPath = (flareMapPath.empty()) ? "?" : flareMapPath;
			replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

			// Write data
			file <<
				"GRAPHICS_LENS_FLARE " <<
				flareMapPath << " " <<
				intensity << " " <<
				multiplier << endl;
		}

		// Sky exposure settings
		if (_fe3d.gfx_isSkyExposureEnabled())
		{
			file << "GRAPHICS_SKY_EXPOSURE " << _fe3d.gfx_getSkyExposureFactor() << " " << _fe3d.gfx_getSkyExposureSpeed() << endl;
		}

		// Bloom settings
		if (_fe3d.gfx_isBloomEnabled())
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
	_customSceneLightIDs.clear();

	// Return
	return true;
}