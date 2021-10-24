#include "scene_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

bool SceneEditor::loadEditorSceneFromFile(const string& filename)
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("SceneEditor::loadEditorSceneFromFile::1");
	}

	// Compose file path
	const string filePath = (Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scenes\\editor\\" + filename + ".fe3d");

	// Warning checking
	if (!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Cannot load scene with ID \"" + filename + "\"!");
		return false;
	}

	// Load scene file
	ifstream file(filePath);

	// Read scene data
	string line;
	while (getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Read type from file
		string lineType;
		iss >> lineType;

		// Determine line type
		if (lineType == "CAMERA_POSITION")
		{
			// Data placeholders
			Vec3 position;

			// Read data from file
			iss >> position.x >> position.y >> position.z;

			// Set position
			if (_isEditorLoaded)
			{
				_fe3d.camera_setPosition(position);
			}
		}
		else if (lineType == "CAMERA_YAW")
		{
			// Data placeholders
			float yaw;

			// Read data from file
			iss >> yaw;

			// Set yaw
			if (_isEditorLoaded)
			{
				_fe3d.camera_setYaw(yaw);
			}
		}
		else if (lineType == "CAMERA_PITCH")
		{
			// Data placeholders
			float pitch;

			// Read data from file
			iss >> pitch;

			// Set pitch
			if (_isEditorLoaded)
			{
				_fe3d.camera_setPitch(pitch);
			}
		}
		else if (lineType == "SKY")
		{
			// Data placeholders
			string skyID, previewID;

			// Read data from file
			iss >> skyID >> previewID;

			// Create sky
			if (_copyPreviewSky(skyID, previewID))
			{
				// Set ID
				if (_isEditorLoaded)
				{
					_currentSkyID = skyID;
				}
			}
		}
		else if (lineType == "TERRAIN")
		{
			// Data placeholders
			string terrainID, previewID;

			// Read data from file
			iss >> terrainID >> previewID;

			// Create terrain
			if (_copyPreviewTerrain(terrainID, previewID))
			{
				// Set ID
				if (_isEditorLoaded)
				{
					_currentTerrainID = terrainID;
				}
			}
		}
		else if (lineType == "WATER")
		{
			// Data placeholders
			string waterID, previewID;
			float height;

			// Read data from file
			iss >> waterID >> previewID >> height;

			// Create water
			if (_copyPreviewWater(waterID, previewID))
			{
				// Set ID
				if (_isEditorLoaded)
				{
					_currentWaterID = waterID;
				}

				// Set height
				_fe3d.waterEntity_setHeight(waterID, height);
			}
		}
		else if (lineType == "MODEL")
		{
			// Data placeholders
			string modelID, previewID, animationID;
			Vec3 position, rotation, size;
			bool isFrozen;

			// Read ID from file
			iss >> modelID;

			// If LOD entity, only load if executing game
			bool makeInvisible = false;
			if (modelID[0] == '@')
			{
				// Check if loading for scene editor
				if (_isEditorLoaded)
				{
					continue;
				}
				else // Loading for script execution
				{
					makeInvisible = true;
				}
			}

			// Read data from file
			iss >>
				previewID >>
				position.x >>
				position.y >>
				position.z >>
				rotation.x >>
				rotation.y >>
				rotation.z >>
				size.x >>
				size.y >>
				size.z >>
				isFrozen >>
				animationID;

			// Perform empty string & space conversions
			animationID = (animationID == "?") ? "" : animationID;
			replace(animationID.begin(), animationID.end(), '?', ' ');

			// Check if preview model instancing changed
			if (_fe3d.modelEntity_isExisting(previewID))
			{
				if (_fe3d.modelEntity_isInstanced(previewID) && (modelID != previewID.substr(1)) ||
					!_fe3d.modelEntity_isInstanced(previewID) && (modelID == previewID.substr(1)))
				{
					Logger::throwWarning("Model instancing with ID \"" + modelID + "\" differs from base model!");
					continue;
				}
			}

			// Create model
			if (_copyPreviewModel(modelID, previewID, position))
			{
				// Set properties
				_fe3d.modelEntity_setBaseRotation(modelID, rotation);
				_fe3d.modelEntity_setBaseSize(modelID, size);
				_fe3d.modelEntity_setStaticToCamera(modelID, isFrozen);
				
				// Set AABBs responsiveness
				for (const auto& aabbID : _fe3d.aabbEntity_getChildIDs(modelID, AabbParentType::MODEL_ENTITY))
				{
					_fe3d.aabbEntity_setRaycastResponsive(aabbID, !isFrozen);
					_fe3d.aabbEntity_setCollisionResponsive(aabbID, !isFrozen);
				}

				// Save original transformation
				if (_isEditorLoaded)
				{
					_initialModelPosition[modelID] = position;
					_initialModelRotation[modelID] = rotation;
					_initialModelSize[modelID] = size;
				}

				// Start animation
				if (!animationID.empty())
				{
					_animationEditor.startAnimation(animationID, modelID, -1);
				}

				// Check if instanced
				if (_fe3d.modelEntity_isInstanced(modelID))
				{
					// Read offset data from file
					vector<Vec3> instancedOffsets;
					while (true)
					{
						// Check if file has offset data left
						string nextElement;
						iss >> nextElement;

						// Check for end of line
						if (nextElement.empty())
						{
							break;
						}
						else // Add offset
						{
							Vec3 offset;
							offset.x = stof(nextElement);
							iss >> offset.y >> offset.z;
							instancedOffsets.push_back(offset);
						}
					}

					// Add offsets
					_fe3d.modelEntity_disableInstancing(modelID);
					_fe3d.modelEntity_enableInstancing(modelID, instancedOffsets);
				}

				// Hide model if LOD (and executing game)
				if (makeInvisible)
				{
					_fe3d.modelEntity_setVisible(modelID, false);
				}
			}
		}
		else if (lineType == "BILLBOARD")
		{
			// Data placeholders
			string billboardID, previewID;
			Vec3 position, rotation;
			Vec2 size;

			// Read data from file
			iss >>
				billboardID >>
				previewID >>
				position.x >>
				position.y >>
				position.z >>
				rotation.x >>
				rotation.y >>
				rotation.z >>
				size.x >>
				size.y;

			// Create billboard
			if (_copyPreviewBillboard(billboardID, previewID, position))
			{
				_fe3d.billboardEntity_setRotation(billboardID, rotation);
				_fe3d.billboardEntity_setSize(billboardID, size);
			}
		}
		else if (lineType == "SOUND")
		{
			// Data placeholders
			string soundID, previewID;
			Vec3 position;
			float maxVolume, maxDistance;

			// Read data from file
			iss >>
				soundID >>
				previewID >>
				position.x >>
				position.y >>
				position.z >>
				maxVolume >>
				maxDistance;

			// Create speaker if in editor
			if (_isEditorLoaded)
			{
				// Create model
				const string newModelID = ("@@speaker_" + soundID);
				_fe3d.modelEntity_create(newModelID, "engine_assets\\meshes\\speaker.obj");
				_fe3d.modelEntity_setBasePosition(newModelID, position);
				_fe3d.modelEntity_setBaseSize(newModelID, DEFAULT_SPEAKER_SIZE);
				_fe3d.modelEntity_setShadowed(newModelID, false);
				_fe3d.modelEntity_setReflected(newModelID, false);
				_fe3d.modelEntity_setBright(newModelID, true);

				// Bind AABB
				_fe3d.aabbEntity_create(newModelID);
				_fe3d.aabbEntity_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
				_fe3d.aabbEntity_setLocalSize(newModelID, DEFAULT_SPEAKER_AABB_SIZE);
				_fe3d.aabbEntity_setCollisionResponsive(newModelID, false);
			}

			// Create sound
			if (_copyPreviewSound(soundID, previewID, position))
			{
				_fe3d.sound_setMaxVolume(soundID, maxVolume);
				_fe3d.sound_setMaxDistance(soundID, maxDistance);
				_fe3d.sound_play(soundID, -1, 0);
			}
		}
		else if (lineType == "POINTLIGHT")
		{
			// Data placeholders
			string pointlightID;
			Vec3 position, radius, color;
			float intensity;
			unsigned int shape;

			// Read data from file
			iss >>
				pointlightID >>
				position.x >>
				position.y >>
				position.z >>
				radius.x >>
				radius.y >>
				radius.z >>
				color.r >>
				color.g >>
				color.b >>
				intensity >>
				shape;

			// Create lamp
			if (_isEditorLoaded)
			{
				// Create model
				const string newModelID = ("@@lamp_" + pointlightID);
				_fe3d.modelEntity_create(newModelID, "engine_assets\\meshes\\lamp.obj");
				_fe3d.modelEntity_setBasePosition(newModelID, position);
				_fe3d.modelEntity_setBaseSize(newModelID, DEFAULT_LAMP_SIZE);
				_fe3d.modelEntity_setColor(newModelID, "", color);
				_fe3d.modelEntity_setShadowed(newModelID, false);
				_fe3d.modelEntity_setReflected(newModelID, false);
				_fe3d.modelEntity_setBright(newModelID, true);

				// Bind AABB
				_fe3d.aabbEntity_create(newModelID);
				_fe3d.aabbEntity_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
				_fe3d.aabbEntity_setLocalSize(newModelID, DEFAULT_LAMP_AABB_SIZE);
				_fe3d.aabbEntity_setCollisionResponsive(newModelID, false);
			}

			// Create pointlight
			_fe3d.pointlightEntity_create(pointlightID);
			_fe3d.pointlightEntity_setPosition(pointlightID, position);
			_fe3d.pointlightEntity_setRadius(pointlightID, radius);
			_fe3d.pointlightEntity_setColor(pointlightID, color);
			_fe3d.pointlightEntity_setIntensity(pointlightID, intensity);
			_fe3d.pointlightEntity_setShape(pointlightID, PointlightShape(shape));
			_loadedPointlightIDs.push_back(pointlightID);
		}
		else if (lineType == "SPOTLIGHT")
		{
			// Data placeholders
			string spotlightID;
			Vec3 position, color;
			float yaw, pitch, intensity, angle, distance;

			// Read data from file
			iss >>
				spotlightID >>
				position.x >>
				position.y >>
				position.z >>
				color.r >>
				color.g >>
				color.b >>
				yaw >>
				pitch >>
				intensity >>
				angle >>
				distance;

			// Create torch
			if (_isEditorLoaded)
			{
				// Create model
				const string newModelID = ("@@torch_" + spotlightID);
				_fe3d.modelEntity_create(newModelID, "engine_assets\\meshes\\torch.obj");
				_fe3d.modelEntity_setBasePosition(newModelID, position);
				_fe3d.modelEntity_setBaseRotation(newModelID, Vec3(0.0f, -yaw, pitch));
				_fe3d.modelEntity_setBaseSize(newModelID, DEFAULT_TORCH_SIZE);
				_fe3d.modelEntity_setColor(newModelID, "", color);
				_fe3d.modelEntity_setShadowed(newModelID, false);
				_fe3d.modelEntity_setReflected(newModelID, false);
				_fe3d.modelEntity_setBright(newModelID, true);

				// Bind AABB
				_fe3d.aabbEntity_create(newModelID);
				_fe3d.aabbEntity_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
				_fe3d.aabbEntity_setLocalSize(newModelID, DEFAULT_TORCH_AABB_SIZE);
				_fe3d.aabbEntity_setCollisionResponsive(newModelID, false);
			}

			// Create spotlight
			_fe3d.spotlightEntity_create(spotlightID);
			_fe3d.spotlightEntity_setPosition(spotlightID, position);
			_fe3d.spotlightEntity_setColor(spotlightID, color);
			_fe3d.spotlightEntity_setYaw(spotlightID, yaw);
			_fe3d.spotlightEntity_setPitch(spotlightID, pitch);
			_fe3d.spotlightEntity_setIntensity(spotlightID, intensity);
			_fe3d.spotlightEntity_setAngle(spotlightID, angle);
			_fe3d.spotlightEntity_setDistance(spotlightID, distance);
			_loadedSpotlightIDs.push_back(spotlightID);
		}
		else if (lineType == "REFLECTION")
		{
			// Data placeholders
			string reflectionID;
			Vec3 position;

			// Read data from file
			iss >>
				reflectionID >>
				position.x >>
				position.y >>
				position.z;

			// Create camera
			if (_isEditorLoaded)
			{
				// Create model
				const string newModelID = ("@@camera_" + reflectionID);
				_fe3d.modelEntity_create(newModelID, "engine_assets\\meshes\\camera.obj");
				_fe3d.modelEntity_setBasePosition(newModelID, position);
				_fe3d.modelEntity_setBaseSize(newModelID, DEFAULT_CAMERA_SIZE);
				_fe3d.modelEntity_setShadowed(newModelID, false);
				_fe3d.modelEntity_setReflected(newModelID, false);
				_fe3d.modelEntity_setBright(newModelID, true);

				// Bind AABB
				_fe3d.aabbEntity_create(newModelID);
				_fe3d.aabbEntity_setParent(newModelID, newModelID, AabbParentType::MODEL_ENTITY);
				_fe3d.aabbEntity_setLocalSize(newModelID, DEFAULT_CAMERA_AABB_SIZE);
				_fe3d.aabbEntity_setCollisionResponsive(newModelID, false);
			}

			// Create reflection
			_fe3d.reflectionEntity_create(reflectionID);
			_fe3d.reflectionEntity_setPosition(reflectionID, position);
			_fe3d.reflectionEntity_capture(reflectionID);
			_loadedReflectionIDs.push_back(reflectionID);
		}
		else if (lineType == "EDITOR_SPEED")
		{
			if (_isEditorLoaded)
			{
				iss >> _editorSpeed;
			}
		}
		else if (lineType == "LOD_DISTANCE")
		{
			// Data placeholders
			float distance;

			// Read data from file
			iss >> distance;

			// Set distance
			_fe3d.misc_setLevelOfDetailDistance(distance);
		}
		else if (lineType == "PLANAR_REFLECTION_HEIGHT")
		{
			// Data placeholders
			float height;

			// Read data from file
			iss >>
				height;

			// Set height
			_fe3d.gfx_setPlanarReflectionHeight(height);
		}
		else if (lineType == "LIGHTING_AMBIENT")
		{
			// Data placeholders
			Vec3 color;
			float intensity;

			// Read data from file
			iss >>
				color.r >>
				color.g >>
				color.b >>
				intensity;

			// Enable ambient lighting
			_fe3d.gfx_enableAmbientLighting();
			_fe3d.gfx_setAmbientLightingColor(color);
			_fe3d.gfx_setAmbientLightingIntensity(intensity);
		}
		else if (lineType == "LIGHTING_DIRECTIONAL")
		{
			// Data placeholders
			Vec3 position, color;
			float intensity, billboardSize;

			// Read data from file
			iss >>
				position.x >>
				position.y >>
				position.z >>
				color.r >>
				color.g >>
				color.b >>
				intensity >>
				billboardSize;

			// Enable directional lighting
			_fe3d.gfx_enableDirectionalLighting();
			_fe3d.gfx_setDirectionalLightingPosition(position);
			_fe3d.gfx_setDirectionalLightingIntensity(intensity);
			_fe3d.gfx_setDirectionalLightingColor(color);

			// Set lightsource billboard
			_fe3d.billboardEntity_setPosition("@@lightSource", position);
			_fe3d.billboardEntity_setSize("@@lightSource", Vec2(billboardSize));
			_fe3d.billboardEntity_setColor("@@lightSource", color);
			_fe3d.billboardEntity_setVisible("@@lightSource", true);
		}
		else if (lineType == "GRAPHICS_SHADOWS")
		{
			// Data placeholders
			float size, lightness;
			Vec3 position, center;
			bool isFollowingCamera;
			int interval;

			// Read data from file
			iss >>
				size >>
				lightness >>
				position.x >>
				position.y >>
				position.z >>
				center.x >>
				center.y >>
				center.z >>
				isFollowingCamera >>
				interval;

			// Enable shadows
			_fe3d.gfx_enableShadows();
			_fe3d.gfx_setShadowEyePosition(position);
			_fe3d.gfx_setShadowCenterPosition(center);
			_fe3d.gfx_setShadowAreaSize(size);
			_fe3d.gfx_setShadowAreaReach(size * 2.0f);
			_fe3d.gfx_setShadowLightness(lightness);
			_fe3d.gfx_setShadowFollowingCamera(isFollowingCamera);
			_fe3d.gfx_setShadowInterval(interval);
		}
		else if (lineType == "GRAPHICS_MOTION_BLUR")
		{
			// Data placeholders
			float strength;

			// Read data from file
			iss >> strength;

			// Enable motion blur
			_fe3d.gfx_enableMotionBlur();
			_fe3d.gfx_setMotionBlurStrength(strength);
		}
		else if (lineType == "GRAPHICS_DOF")
		{
			// Data placeholders
			bool isDynamic;
			float blurDistance, maxDistance;

			// Read data from file
			iss >> isDynamic >> blurDistance >> maxDistance;

			// Enable DOF
			_fe3d.gfx_enableDOF();
			_fe3d.gfx_setDofDynamic(isDynamic);
			_fe3d.gfx_setDofMaxDistance(maxDistance);
			_fe3d.gfx_setDofBlurDistance(blurDistance);
		}
		else if (lineType == "GRAPHICS_FOG")
		{
			// Data placeholders
			float minDistance, maxDistance, thickness;
			Vec3 color;

			// Read data from file
			iss >> minDistance >> maxDistance >> thickness >> color.r >> color.g >> color.b;

			// Enable fog
			_fe3d.gfx_enableFog();
			_fe3d.gfx_setFogMinDistance(minDistance);
			_fe3d.gfx_setFogMaxDistance(maxDistance);
			_fe3d.gfx_setFogThickness(thickness);
			_fe3d.gfx_setFogColor(color);
		}
		else if (lineType == "GRAPHICS_LENS_FLARE")
		{
			// Data placeholders
			string flareMapPath;
			float intensity, sensitivity;

			// Read data from file
			iss >> flareMapPath >> intensity >> sensitivity;

			// Perform empty string & space conversions
			flareMapPath = (flareMapPath == "?") ? "" : flareMapPath;
			replace(flareMapPath.begin(), flareMapPath.end(), '?', ' ');

			// Enable lens flare
			_fe3d.gfx_enableLensFlare();
			_fe3d.gfx_setLensFlareMap(flareMapPath);
			_fe3d.gfx_setLensFlareIntensity(intensity);
			_fe3d.gfx_setLensFlareSensitivity(sensitivity);
		}
		else if (lineType == "GRAPHICS_SKY_EXPOSURE")
		{
			// Data placeholders
			float intensity, speed;

			// Read data from file
			iss >> intensity >> speed;

			// Enable sky exposure
			_fe3d.gfx_enableSkyExposure();
			_fe3d.gfx_setSkyExposureIntensity(intensity);
			_fe3d.gfx_setSkyExposureSpeed(speed);
		}
		else if (lineType == "GRAPHICS_BLOOM")
		{
			// Data placeholders
			unsigned int type, blurCount;
			float intensity;

			// Read data from file
			iss >> type >> intensity >> blurCount;

			// Enable bloom
			_fe3d.gfx_enableBloom();
			_fe3d.gfx_setBloomType(BloomType(type));
			_fe3d.gfx_setBloomIntensity(intensity);
			_fe3d.gfx_setBloomBlurCount(blurCount);
		}
		else
		{
			Logger::throwError("SceneEditor::loadEditorSceneFromFile::2");
		}
	}

	// Close file
	file.close();

	// Set new scene ID
	_loadedSceneID = filename;

	// Logging
	Logger::throwInfo("Scene data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}