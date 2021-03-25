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
			string previewID = _loadedModelIDs.at(modelID);

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
				lightness;

			// Write instanced offset
			if (_fe3d.modelEntity_isInstanced(modelID))
			{
				// Check if model has any offsets
				auto instancedOffsets = _fe3d.modelEntity_getInstancedOffsets(modelID);
				if (!instancedOffsets.empty())
				{
					file << " ";
				}

				// Write offsets
				for (unsigned int i = 0; i < instancedOffsets.size(); i++)
				{
					file <<
						instancedOffsets[i].x << " " <<
						instancedOffsets[i].y << " " <<
						instancedOffsets[i].z;

					// Add space
					if (i != (instancedOffsets.size() - 1))
					{
						file << " ";
					}
				}
			}

			// New line
			file << std::endl;
		}
	}

	// Write billboards
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
			auto position = _fe3d.billboardEntity_getPosition(billboardID);
			auto rotation = _fe3d.billboardEntity_getRotation(billboardID);
			auto size = _fe3d.billboardEntity_getSize(billboardID);
			auto color = _fe3d.billboardEntity_getColor(billboardID);
			auto textContent = _fe3d.billboardEntity_getTextContent(billboardID);
			auto lightness = _fe3d.billboardEntity_getLightness(billboardID);
			auto minHeight = _fe3d.billboardEntity_getMinHeight(billboardID);
			auto maxHeight = _fe3d.billboardEntity_getMaxHeight(billboardID);

			// Perform empty string & space conversions
			textContent = (textContent == "") ? "?" : textContent;
			std::replace(textContent.begin(), textContent.end(), ' ', '?');

			// Extract preview ID
			string previewID = _loadedBillboardIDs.at(billboardID);

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
				lightness << "" <<
				minHeight << " " <<
				maxHeight << std::endl;
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
			string previewID = _loadedAudioIDs.at(audioID);

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
		Vec3 ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
		float ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

		file <<
			"AMBIENT_LIGHT " <<
			ambientLightingColor.r << " " <<
			ambientLightingColor.g << " " <<
			ambientLightingColor.b << " " <<
			ambientLightingIntensity << std::endl;

		// Directional lighting
		Vec3 directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
		Vec3 directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
		float directionalLightingIntensity = _fe3d.gfx_getDirectionalLightingIntensity();
		float billboardSize = _fe3d.billboardEntity_getSize("@@lightSource").x;
		float billboardLightness = _fe3d.billboardEntity_getLightness("@@lightSource");

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
		bool enabled = _fe3d.gfx_isShadowsEnabled();
		if (enabled)
		{
			float size = _fe3d.gfx_getShadowSize();
			float lightness = _fe3d.gfx_getShadowLightness();
			Vec3 position = _fe3d.gfx_getShadowEyePosition();
			Vec3 center = _fe3d.gfx_getShadowCenter();
			bool isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
			bool isSoftShadowed = _fe3d.gfx_isSoftShadowingEnabled();
			int interval = _fe3d.gfx_getShadowInterval();
			file << "GRAPHICS_SHADOWS " << enabled << " " << size << " " << lightness << " " << _fe3d.misc_vec2str(position) << " " <<
				_fe3d.misc_vec2str(center) << " " << isFollowingCamera << " " << isSoftShadowed << " " << interval << std::endl;
		}

		// Motion blur settings
		enabled = _fe3d.gfx_isMotionBlurEnabled();
		if (enabled)
		{
			float strength = _fe3d.gfx_getMotionBlurStrength();
			file << "GRAPHICS_MOTIONBLUR " << enabled << " " << strength << std::endl;
		}

		// DOF settings
		enabled = _fe3d.gfx_isDofEnabled();
		if (enabled)
		{
			bool dynamic = _fe3d.gfx_isDofDynamic();
			float blurDistance = _fe3d.gfx_getDofBlurDistance();
			float maxDistance = _fe3d.gfx_getaMaxDofDistance();
			file << "GRAPHICS_DOF " << enabled << " " << dynamic << " " << blurDistance << " " << maxDistance << std::endl;
		}

		// Fog settings
		enabled = _fe3d.gfx_isFogEnabled();
		if (enabled)
		{
			float minDistance = _fe3d.gfx_getFogMinDistance();
			float maxDistance = _fe3d.gfx_getFogMaxDistance();
			float thickness = _fe3d.gfx_getFogThickness();
			Vec3 color = _fe3d.gfx_getFogColor();
			file << "GRAPHICS_FOG " << enabled << " " << minDistance << " " << maxDistance << " " << thickness << " " << _fe3d.misc_vec2str(color) << std::endl;
		}

		// Lens flare settings
		enabled = _fe3d.gfx_isLensFlareEnabled();
		if (enabled)
		{
			string flareMapPath = _fe3d.gfx_getLensFlareMapPath();
			float intensity = _fe3d.gfx_getLensFlareIntensity();
			float multiplier = _fe3d.gfx_getLensFlareMultiplier();
			flareMapPath = (flareMapPath == "") ? "?" : flareMapPath;
			std::replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');
			file << "GRAPHICS_LENSFLARE " << enabled << " " << flareMapPath << " " << intensity << " " << multiplier << std::endl;
		}

		// Sky HDR settings
		enabled = _fe3d.gfx_isSkyHdrEnabled();
		if (enabled)
		{
			float intensity = _fe3d.gfx_getSkyHdrBrightnessFactor();
			file << "GRAPHICS_SKYHDR " << enabled << " " << intensity << std::endl;
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
	_customSceneAudioIDs.clear();
	_customSceneLightIDs.clear();
}