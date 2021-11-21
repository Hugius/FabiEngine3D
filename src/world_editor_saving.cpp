#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

const bool WorldEditor::saveEditorWorldToFile()
{
	// Must be editing a world
	if(_currentWorldID.empty())
	{
		return false;
	}

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("WorldEditor::saveEditorWorldToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\worlds\\editor\\" + _currentWorldID + ".fe3d");

	// Save all level of detail entity IDs
	vector<string> levelOfDetailEntityIDs;
	for(const auto& modelID : _fe3d.model_getAllIDs())
	{
		// Check if not preview entity
		if(modelID[0] != '@')
		{
			// Check if entity has level of detail model
			if(!_fe3d.model_getLevelOfDetailID(modelID).empty())
			{
				// Check if ID not already added to list
				if(find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) == levelOfDetailEntityIDs.end())
				{
					levelOfDetailEntityIDs.push_back(_fe3d.model_getLevelOfDetailID(modelID));
				}
			}
		}
	}

	// Camera position
	const auto cameraPosition = _fe3d.camera_getPosition();
	file << "CAMERA_POSITION " << cameraPosition.x << " " << cameraPosition.y << " " << cameraPosition.z << endl;

	// Camera yaw
	file << "CAMERA_YAW " << _fe3d.camera_getYaw() << endl;

	// Camera pitch
	file << "CAMERA_PITCH " << _fe3d.camera_getPitch() << endl;

	// Sky
	string skyID = _fe3d.sky_getSelectedID();
	if(!skyID.empty())
	{
		// Data to save
		string previewID = ("@" + skyID);

		// Write data
		file <<
			"SKY " <<
			skyID << " " <<
			previewID << endl;
	}

	// Terrain
	string terrainID = _fe3d.terrain_getSelectedID();
	if(!terrainID.empty())
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
	string waterID = _fe3d.water_getSelectedID();
	if(!waterID.empty())
	{
		// Data to save
		string previewID = ("@" + waterID);
		auto height = _fe3d.water_getHeight(waterID);

		// Write data
		file <<
			"WATER " <<
			waterID << " " <<
			previewID << " " <<
			height << endl;
	}

	// Models
	for(const auto& modelID : _fe3d.model_getAllIDs())
	{
		// Check if allowed to save
		bool isLevelOfDetailEntity = find(levelOfDetailEntityIDs.begin(), levelOfDetailEntityIDs.end(), modelID) != levelOfDetailEntityIDs.end();
		if((modelID[0] != '@') || isLevelOfDetailEntity)
		{
			// Check if model has bound animation
			if(!_animationEditor.getStartedAnimationIDs(modelID).empty())
			{
				// Reset main transformation
				_fe3d.model_setBasePosition(modelID, _initialModelPosition[modelID]);
				_fe3d.model_setBaseRotationOrigin(modelID, Vec3(0.0f));
				_fe3d.model_setBaseRotation(modelID, _initialModelRotation[modelID]);
				_fe3d.model_setBaseSize(modelID, _initialModelSize[modelID]);

				// Reset part transformations
				for(const auto& partID : _fe3d.model_getPartIDs(modelID))
				{
					// Only named parts
					if(!partID.empty())
					{
						_fe3d.model_setPartPosition(modelID, partID, Vec3(0.0f));
						_fe3d.model_setPartRotationOrigin(modelID, partID, Vec3(0.0f));
						_fe3d.model_setPartRotation(modelID, partID, Vec3(0.0f));
						_fe3d.model_setPartSize(modelID, partID, Vec3(1.0f));
					}
				}
			}

			// Data to save
			auto position = _fe3d.model_getBasePosition(modelID);
			auto rotation = _fe3d.model_getBaseRotation(modelID);
			auto size = _fe3d.model_getBaseSize(modelID);
			auto isFrozen = _fe3d.model_isStaticToCamera(modelID);
			auto animationID = (_animationEditor.getStartedAnimationIDs(modelID).empty()) ? "" :
				_animationEditor.getStartedAnimationIDs(modelID).front();

			// Convert empty string
			animationID = (animationID.empty()) ? "?" : animationID;

			// Convert spaces
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

	// Billboards
	for(const auto& billboardID : _fe3d.billboard_getAllIDs())
	{
		// Check if allowed to save
		if(billboardID[0] != '@')
		{
			// Data to save
			auto position = _fe3d.billboard_getPosition(billboardID);
			auto rotation = _fe3d.billboard_getRotation(billboardID);
			auto size = _fe3d.billboard_getSize(billboardID);

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
	for(const auto& soundID : _fe3d.sound_getAllIDs())
	{
		// Check if allowed to save
		if(soundID[0] != '@')
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

	// Pointlights
	for(const auto& pointlightID : _fe3d.pointlight_getAllIDs())
	{
		// Check if allowed to save
		if(pointlightID[0] != '@')
		{
			// Data to save
			auto position = _fe3d.pointlight_getPosition(pointlightID);
			auto radius = _fe3d.pointlight_getRadius(pointlightID);
			auto color = _fe3d.pointlight_getColor(pointlightID);
			auto intensity = _fe3d.pointlight_getIntensity(pointlightID);
			auto shape = static_cast<unsigned int>(_fe3d.pointlight_getShape(pointlightID));

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
				intensity << " " <<
				shape << endl;
		}
	}

	// Spotlights
	for(const auto& spotlightID : _fe3d.spotlight_getAllIDs())
	{
		// Check if allowed to save
		if(spotlightID[0] != '@')
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
	for(const auto& reflectionID : _fe3d.reflection_getAllIDs())
	{
		// Check if allowed to save
		if(reflectionID[0] != '@')
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

	// Editor camera speed
	file << "EDITOR_SPEED " << _editorSpeed << endl;

	// Level of detail distance
	file << "LOD_DISTANCE " << _fe3d.misc_getLevelOfDetailDistance() << endl;

	// Reflection height
	file << "PLANAR_REFLECTION_HEIGHT " << _fe3d.gfx_getPlanarReflectionHeight() << endl;

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
		auto billboardSize = _fe3d.billboard_getSize("@@directionalLightSource").x;
		auto billboardLightness = _fe3d.billboard_getLightness("@@directionalLightSource");

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

		// Convert to short path
		flareMapPath = string(flareMapPath.empty() ? "" : flareMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

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

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("World data saved!");

	// Return
	return true;
}