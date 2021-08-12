#include "scene_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;

bool SceneEditor::saveEditorSceneToFile()
{
	// Must be editing a scene
	if (_currentSceneID.empty())
	{
		return false;
	}

	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("SceneEditor::saveEditorSceneToFile");
	}

	// Compose file path
	const string filePath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\" + _currentSceneID + ".fe3d");

	// Create or overwrite scene file
	ofstream file(filePath);

	// Save all LOD model IDs
	vector<string> lodIDs;
	for (const auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if not preview entity
		if (modelID[0] != '@')
		{
			// Check if entity has LOD model
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
	if (!skyID.empty())
	{
		// Data to save
		string previewID = "@" + skyID;

		// Write data
		file <<
			"SKY " <<
			skyID << " " <<
			previewID << endl;
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
			previewID << endl;
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
			previewID << endl;
	}

	// Models
	for (const auto& modelID : _fe3d.modelEntity_getAllIDs())
	{
		// Check if allowed to save
		bool isLodModel = find(lodIDs.begin(), lodIDs.end(), modelID) != lodIDs.end();
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
				for (const auto& partID : _fe3d.modelEntity_getPartIDs(modelID))
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
			animationID = (animationID.empty()) ? "?" : animationID;
			replace(animationID.begin(), animationID.end(), ' ', '?');

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

	// Billboards
	for (const auto& billboardID : _fe3d.billboardEntity_getAllIDs())
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
				size.y << endl;
		}
	}

	// Sounds
	for (const auto& soundID : _fe3d.sound_getAllIDs())
	{
		// Check if allowed to save
		if (soundID[0] != '@')
		{
			// Data to save
			auto position = _fe3d.sound_getPosition(soundID);
			auto maxVolume = _fe3d.sound_getMaxVolume(soundID);
			auto maxDistance = _fe3d.sound_getMaxDistance(soundID);

			// Extract preview ID
			string previewID = _loadedSoundIDs.at(soundID);

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

	// Point lights
	for (const auto& lightID : _fe3d.lightEntity_getAllIDs())
	{
		// Check if allowed to save
		if (lightID[0] != '@')
		{
			// Data to save
			auto position = _fe3d.lightEntity_getPosition(lightID);
			auto radius = _fe3d.lightEntity_getRadius(lightID);
			auto color = _fe3d.lightEntity_getColor(lightID);
			auto intensity = _fe3d.lightEntity_getIntensity(lightID);
			auto shape = static_cast<unsigned int>(_fe3d.lightEntity_getShape(lightID));

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
				intensity << " " <<
				shape << endl;
		}
	}

	// LOD distance
	file << "LOD_DISTANCE " << _fe3d.misc_getLevelOfDetailDistance() << endl;

	// Reflection height
	file << "SCENE_REFLECTION_HEIGHT " << _fe3d.gfx_getSceneReflectionHeight() << endl;

	// Editor camera speed
	file << "EDITOR_SPEED " << _editorSpeed << endl;

	// Editor camera position
	auto position = _fe3d.camera_getPosition();
	file << "EDITOR_POSITION " << position.x << " " << position.y << " " << position.z << endl;

	// Editor camera yaw
	file << "EDITOR_YAW " << _fe3d.camera_getYaw() << endl;

	// Editor camera pitch
	file << "EDITOR_PITCH " << _fe3d.camera_getPitch() << endl;

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

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Scene data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}