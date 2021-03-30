#include "scene_editor.hpp"

#include <fstream>
#include <algorithm>

void SceneEditor::saveEditorSceneToFile()
{
	// Must be editing a scene
	if (_currentSceneID.empty())
	{
		return;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> SceneEditor::saveEditorSceneToFile()");
	}

	// Check if scene directory still exists
	string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\");
	if (!_fe3d.misc_isDirectoryExisting(directoryPath) || !_fe3d.misc_isDirectoryExisting(directoryPath + "editor\\"))
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: scenes folder(s) missing!");
		return;
	}

	// Create or overwrite file
	string fullFilePath = (directoryPath + "editor\\" + _currentSceneID + ".fe3d");
	std::ofstream file(fullFilePath);

	// Save all LOD model IDs
	vector<string> lodIDs;
	for (auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if not preview entity
		if (modelID[0] != '@')
		{
			// Check if entity has LOD model
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
	if (!skyID.empty())
	{
		// Data to save
		string previewID = "@" + skyID;

		// Write data
		file <<
			"SKY " <<
			skyID << " " <<
			previewID << std::endl;
	}

	// Terrain
	string terrainID = _fe3d.terrainEntity_getSelectedID();
	if (!terrainID.empty())
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
	if (!waterID.empty())
	{
		// Data to save
		string previewID = "@" + waterID;

		// Write data
		file <<
			"WATER " <<
			waterID << " " <<
			previewID << std::endl;
	}

	// Models
	for (auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isLodModel = std::find(lodIDs.begin(), lodIDs.end(), modelID) != lodIDs.end();
		if ((modelID[0] != '@') || isLodModel)
		{
			// Check if model has bound animation
			if (!_animationEditor.getStartedAnimationIDs(modelID).empty())
			{
				// Reset main transformation
				_fe3d.modelEntity_setPosition(modelID, _initialModelPosition[modelID]);
				_fe3d.modelEntity_setRotationOrigin(modelID, Vec3(0.0f));
				_fe3d.modelEntity_setRotation(modelID, _initialModelRotation[modelID]);
				_fe3d.modelEntity_setSize(modelID, _initialModelSize[modelID]);

				// Reset part transformations
				for (auto& partID : _fe3d.modelEntity_getPartIDs(modelID))
				{
					// Only named parts
					if (!partID.empty())
					{
						_fe3d.modelEntity_setPosition(modelID, Vec3(0.0f), partID);
						_fe3d.modelEntity_setRotationOrigin(modelID, Vec3(0.0f), partID);
						_fe3d.modelEntity_setRotation(modelID, Vec3(0.0f), partID);
						_fe3d.modelEntity_setSize(modelID, Vec3(1.0f), partID);
					}
				}
			}

			// Data to save
			auto position = _fe3d.modelEntity_getPosition(modelID);
			auto rotation = _fe3d.modelEntity_getRotation(modelID);
			auto size = _fe3d.modelEntity_getSize(modelID);
			auto isFrozen = _fe3d.modelEntity_isStaticToCamera(modelID);
			auto animationID = (_animationEditor.getStartedAnimationIDs(modelID).empty()) ? "" :
				_animationEditor.getStartedAnimationIDs(modelID).front();

			// Perform empty string & space conversions
			animationID = (animationID == "") ? "?" : animationID;
			std::replace(animationID.begin(), animationID.end(), ' ', '?');

			// Extract preview ID
			string previewID = _loadedModelIDs.at(modelID);

			// Write main data
			file <<
				"MODEL " <<
				modelID << " " <<
				previewID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				rotation.x << " " <<
				rotation.y << " " <<
				rotation.z << " " <<
				size.x << " " <<
				size.y << " " <<
				size.z << " " <<
				isFrozen << " " <<
				animationID;

			// Write instanced offset
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

	// Billboards
	for (auto& billboardID : _fe3d.billboardEntity_getAllIDs())
	{
		// Check if allowed to save
		if (billboardID[0] != '@')
		{
			// Data to save
			auto position = _fe3d.billboardEntity_getPosition(billboardID);
			auto rotation = _fe3d.billboardEntity_getRotation(billboardID);
			auto size = _fe3d.billboardEntity_getSize(billboardID);

			// Extract preview ID
			string previewID = _loadedBillboardIDs.at(billboardID);

			// Write data
			file <<
				"BILLBOARD " <<
				billboardID << " " <<
				previewID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				rotation.x << " " <<
				rotation.y << " " <<
				rotation.z << " " <<
				size.x << " " <<
				size.y << std::endl;
		}
	}

	// Audio
	for (auto& audioID : _fe3d.audioEntity_getAllIDs())
	{
		// Check if allowed to save
		if (audioID[0] != '@')
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

	// Point lights
	for (auto& lightID : _fe3d.lightEntity_getAllIDs())
	{
		// Check if allowed to save
		if (lightID[0] != '@')
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

	// LOD distance
	file << "LOD_DISTANCE " << _fe3d.misc_getLevelOfDetailDistance() << std::endl;

	// Editor camera speed
	file << "EDITOR_SPEED " << _editorSpeed << std::endl;

	// Editor camera position
	Vec3 position = _fe3d.camera_getPosition();
	file << "EDITOR_POSITION " << position.x << " " << position.y << " " << position.z << std::endl;

	// Editor camera yaw
	file << "EDITOR_YAW " << _fe3d.camera_getYaw() << std::endl;

	// Editor camera pitch
	file << "EDITOR_PITCH " << _fe3d.camera_getPitch() << std::endl;

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
			_fe3d.misc_vec2str(color) <<std::endl;
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

	// Close file
	file.close();

	// Logging
	_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectID + "\" saved!");
}