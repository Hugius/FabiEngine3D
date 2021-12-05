#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const bool WorldEditor::loadEditorWorldFromFile(const string& fileName)
{
	// Error checking
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("WorldEditor::loadEditorWorldFromFile::1");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "worlds\\editor\\" + fileName + ".fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Cannot load world with ID \"" + fileName + "\"!");
		return false;
	}

	// Load world file
	ifstream file(filePath);

	// Read world data
	string line;
	while(getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Read type from file
		string lineType;
		iss >> lineType;

		// Determine line type
		if(lineType == "CAMERA_POSITION")
		{
			// Data placeholders
			fvec3 position;

			// Read data from file
			iss >> position.x >> position.y >> position.z;

			// Set position
			if(_isEditorLoaded)
			{
				_fe3d.camera_setPosition(position);
			}
		}
		else if(lineType == "CAMERA_YAW")
		{
			// Data placeholders
			float yaw;

			// Read data from file
			iss >> yaw;

			// Set yaw
			if(_isEditorLoaded)
			{
				_fe3d.camera_setYaw(yaw);
			}
		}
		else if(lineType == "CAMERA_PITCH")
		{
			// Data placeholders
			float pitch;

			// Read data from file
			iss >> pitch;

			// Set pitch
			if(_isEditorLoaded)
			{
				_fe3d.camera_setPitch(pitch);
			}
		}
		else if(lineType == "SKY")
		{
			// Data placeholders
			string skyID, previewID;

			// Read data from file
			iss >> skyID >> previewID;

			// Create sky
			if(_copyPreviewSky(skyID, previewID))
			{
				// Set ID
				if(_isEditorLoaded)
				{
					_currentSkyID = skyID;
				}
			}
		}
		else if(lineType == "TERRAIN")
		{
			// Data placeholders
			string terrainID, previewID;

			// Read data from file
			iss >> terrainID >> previewID;

			// Create terrain
			if(_copyPreviewTerrain(terrainID, previewID))
			{
				// Set ID
				if(_isEditorLoaded)
				{
					_currentTerrainID = terrainID;
				}
			}
		}
		else if(lineType == "WATER")
		{
			// Data placeholders
			string waterID, previewID;
			float height;

			// Read data from file
			iss >> waterID >> previewID >> height;

			// Create water
			if(_copyPreviewWater(waterID, previewID))
			{
				// Set ID
				if(_isEditorLoaded)
				{
					_currentWaterID = waterID;
				}

				// Set height
				_fe3d.water_setHeight(waterID, height);
			}
		}
		else if(lineType == "MODEL")
		{
			// Data placeholders
			string modelID, previewID, animationID;
			fvec3 position, rotation, size;
			bool isFrozen;

			// Read ID from file
			iss >> modelID;

			// If level of detail entity, only load if executing game
			bool makeInvisible = false;
			if(modelID[0] == '@')
			{
				// Check if loading for world editor
				if(_isEditorLoaded)
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

			// Convert empty string
			animationID = (animationID == "?") ? "" : animationID;

			// Convert spaces
			replace(animationID.begin(), animationID.end(), '?', ' ');

			// Check if preview model instancing changed
			if(_fe3d.model_isExisting(previewID))
			{
				if(_fe3d.model_isInstanced(previewID) && (modelID != previewID.substr(1)) ||
				   !_fe3d.model_isInstanced(previewID) && (modelID == previewID.substr(1)))
				{
					Logger::throwWarning("Model instancing with ID \"" + modelID + "\" differs from base model!");
					continue;
				}
			}

			// Create model
			if(_copyPreviewModel(modelID, previewID, position, false))
			{
				// Set properties
				_fe3d.model_setBaseRotation(modelID, rotation);
				_fe3d.model_setBaseSize(modelID, size);
				_fe3d.model_setStaticToCamera(modelID, isFrozen);

				// Save initial transformation
				if(_isEditorLoaded)
				{
					_initialModelPosition[modelID] = position;
					_initialModelRotation[modelID] = rotation;
					_initialModelSize[modelID] = size;
				}

				// Start animation
				if(!animationID.empty())
				{
					_animationEditor.startAnimation(animationID, modelID, -1);
				}

				// Check if instanced
				if(_fe3d.model_isInstanced(modelID))
				{
					// Read offset data from file
					vector<fvec3> instancedOffsets;
					while(true)
					{
						// Check if file has offset data left
						string nextElement;
						iss >> nextElement;

						// Check for end of line
						if(nextElement.empty())
						{
							break;
						}
						else // Add offset
						{
							fvec3 offset;
							offset.x = stof(nextElement);
							iss >> offset.y >> offset.z;
							instancedOffsets.push_back(offset);
						}
					}

					// Add offsets
					_fe3d.model_disableInstancing(modelID);
					_fe3d.model_enableInstancing(modelID, instancedOffsets);
				}

				// Make invisible
				if(makeInvisible)
				{
					_fe3d.model_setVisible(modelID, false);
				}
			}
		}
		else if(lineType == "BILLBOARD")
		{
			// Data placeholders
			string billboardID, previewID;
			fvec3 position, rotation;
			fvec2 size;

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
			if(_copyPreviewBillboard(billboardID, previewID, position, false))
			{
				_fe3d.billboard_setRotation(billboardID, rotation);
				_fe3d.billboard_setSize(billboardID, size);
			}
		}
		else if(lineType == "SOUND")
		{
			// Data placeholders
			string soundID, previewID;
			fvec3 position;
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
			if(_isEditorLoaded)
			{
				// Create model
				const string newModelID = ("@@speaker_" + soundID);
				_fe3d.model_create(newModelID, "engine\\assets\\meshes\\speaker.obj");
				_fe3d.model_setBasePosition(newModelID, position);
				_fe3d.model_setBaseSize(newModelID, DEFAULT_SPEAKER_SIZE);
				_fe3d.model_setShadowed(newModelID, false);
				_fe3d.model_setReflected(newModelID, false);
				_fe3d.model_setBright(newModelID, true);

				// Bind AABB
				_fe3d.aabb_create(newModelID);
				_fe3d.aabb_setParent(newModelID, newModelID, AabbParentEntityType::MODEL);
				_fe3d.aabb_setLocalSize(newModelID, DEFAULT_SPEAKER_AABB_SIZE);
				_fe3d.aabb_setCollisionResponsive(newModelID, false);
			}

			// Create sound
			if(_copyPreviewSound(soundID, previewID, position, false))
			{
				_fe3d.sound3D_setMaxVolume(soundID, maxVolume);
				_fe3d.sound3D_setMaxDistance(soundID, maxDistance);
				_fe3d.sound3D_play(soundID, -1, 0, false);
			}
		}
		else if(lineType == "POINTLIGHT")
		{
			// Data placeholders
			string pointlightID;
			fvec3 position, radius, color;
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
			if(_isEditorLoaded)
			{
				// Create model
				const string newModelID = ("@@lamp_" + pointlightID);
				_fe3d.model_create(newModelID, "engine\\assets\\meshes\\lamp.obj");
				_fe3d.model_setBasePosition(newModelID, position);
				_fe3d.model_setBaseSize(newModelID, DEFAULT_LAMP_SIZE);
				_fe3d.model_setColor(newModelID, "", color);
				_fe3d.model_setShadowed(newModelID, false);
				_fe3d.model_setReflected(newModelID, false);
				_fe3d.model_setBright(newModelID, true);

				// Bind AABB
				_fe3d.aabb_create(newModelID);
				_fe3d.aabb_setParent(newModelID, newModelID, AabbParentEntityType::MODEL);
				_fe3d.aabb_setLocalSize(newModelID, DEFAULT_LAMP_AABB_SIZE);
				_fe3d.aabb_setCollisionResponsive(newModelID, false);
			}

			// Create pointlight
			_fe3d.pointlight_create(pointlightID);
			_fe3d.pointlight_setPosition(pointlightID, position);
			_fe3d.pointlight_setRadius(pointlightID, radius);
			_fe3d.pointlight_setColor(pointlightID, color);
			_fe3d.pointlight_setIntensity(pointlightID, intensity);
			_fe3d.pointlight_setShape(pointlightID, PointlightShape(shape));
			_loadedPointlightIDs.push_back(pointlightID);
		}
		else if(lineType == "SPOTLIGHT")
		{
			// Data placeholders
			string spotlightID;
			fvec3 position, color;
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
			if(_isEditorLoaded)
			{
				// Create model
				const string newModelID = ("@@torch_" + spotlightID);
				_fe3d.model_create(newModelID, "engine\\assets\\meshes\\torch.obj");
				_fe3d.model_setBasePosition(newModelID, position);
				_fe3d.model_setBaseRotation(newModelID, fvec3(0.0f, -yaw, pitch));
				_fe3d.model_setBaseSize(newModelID, DEFAULT_TORCH_SIZE);
				_fe3d.model_setColor(newModelID, "", color);
				_fe3d.model_setShadowed(newModelID, false);
				_fe3d.model_setReflected(newModelID, false);
				_fe3d.model_setBright(newModelID, true);

				// Bind AABB
				_fe3d.aabb_create(newModelID);
				_fe3d.aabb_setParent(newModelID, newModelID, AabbParentEntityType::MODEL);
				_fe3d.aabb_setLocalSize(newModelID, DEFAULT_TORCH_AABB_SIZE);
				_fe3d.aabb_setCollisionResponsive(newModelID, false);
			}

			// Create spotlight
			_fe3d.spotlight_create(spotlightID);
			_fe3d.spotlight_setPosition(spotlightID, position);
			_fe3d.spotlight_setColor(spotlightID, color);
			_fe3d.spotlight_setYaw(spotlightID, yaw);
			_fe3d.spotlight_setPitch(spotlightID, pitch);
			_fe3d.spotlight_setIntensity(spotlightID, intensity);
			_fe3d.spotlight_setAngle(spotlightID, angle);
			_fe3d.spotlight_setDistance(spotlightID, distance);
			_loadedSpotlightIDs.push_back(spotlightID);
		}
		else if(lineType == "REFLECTION")
		{
			// Data placeholders
			string reflectionID;
			fvec3 position;

			// Read data from file
			iss >>
				reflectionID >>
				position.x >>
				position.y >>
				position.z;

			// Create camera
			if(_isEditorLoaded)
			{
				// Create model
				const string newModelID = ("@@camera_" + reflectionID);
				_fe3d.model_create(newModelID, "engine\\assets\\meshes\\camera.obj");
				_fe3d.model_setBasePosition(newModelID, position);
				_fe3d.model_setBaseSize(newModelID, DEFAULT_CAMERA_SIZE);
				_fe3d.model_setShadowed(newModelID, false);
				_fe3d.model_setReflected(newModelID, false);
				_fe3d.model_setBright(newModelID, true);

				// Bind AABB
				_fe3d.aabb_create(newModelID);
				_fe3d.aabb_setParent(newModelID, newModelID, AabbParentEntityType::MODEL);
				_fe3d.aabb_setLocalSize(newModelID, DEFAULT_CAMERA_AABB_SIZE);
				_fe3d.aabb_setCollisionResponsive(newModelID, false);
			}

			// Create reflection
			_fe3d.reflection_create(reflectionID);
			_fe3d.reflection_setPosition(reflectionID, position);
			_fe3d.reflection_capture(reflectionID);
			_loadedReflectionIDs.push_back(reflectionID);
		}
		else if(lineType == "EDITOR_SPEED")
		{
			if(_isEditorLoaded)
			{
				iss >> _editorSpeed;
			}
		}
		else if(lineType == "LOD_DISTANCE")
		{
			// Data placeholders
			float distance;

			// Read data from file
			iss >> distance;

			// Set distance
			_fe3d.misc_setLevelOfDetailDistance(distance);
		}
		else if(lineType == "PLANAR_REFLECTION_HEIGHT")
		{
			// Data placeholders
			float height;

			// Read data from file
			iss >>
				height;

			// Set height
			_fe3d.gfx_setPlanarReflectionHeight(height);
		}
		else if(lineType == "LIGHTING_AMBIENT")
		{
			// Data placeholders
			fvec3 color;
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
		else if(lineType == "LIGHTING_DIRECTIONAL")
		{
			// Data placeholders
			fvec3 position, color;
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
		}
		else if(lineType == "GRAPHICS_SHADOWS")
		{
			// Data placeholders
			float size, lightness;
			fvec3 position, center;
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
		else if(lineType == "GRAPHICS_MOTION_BLUR")
		{
			// Data placeholders
			float strength;

			// Read data from file
			iss >> strength;

			// Enable motion blur
			_fe3d.gfx_enableMotionBlur();
			_fe3d.gfx_setMotionBlurStrength(strength);
		}
		else if(lineType == "GRAPHICS_DOF")
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
		else if(lineType == "GRAPHICS_FOG")
		{
			// Data placeholders
			float minDistance, maxDistance, thickness;
			fvec3 color;

			// Read data from file
			iss >> minDistance >> maxDistance >> thickness >> color.r >> color.g >> color.b;

			// Enable fog
			_fe3d.gfx_enableFog();
			_fe3d.gfx_setFogMinDistance(minDistance);
			_fe3d.gfx_setFogMaxDistance(maxDistance);
			_fe3d.gfx_setFogThickness(thickness);
			_fe3d.gfx_setFogColor(color);
		}
		else if(lineType == "GRAPHICS_LENS_FLARE")
		{
			// Data placeholders
			string flareMapPath;
			float intensity, sensitivity;

			// Read data from file
			iss >> flareMapPath >> intensity >> sensitivity;

			// Convert empty string
			flareMapPath = (flareMapPath == "?") ? "" : flareMapPath;

			// Convert spaces
			replace(flareMapPath.begin(), flareMapPath.end(), '?', ' ');

			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				flareMapPath = string("projects\\" + _currentProjectID + "\\" + flareMapPath);
			}

			// Enable lens flare
			_fe3d.gfx_enableLensFlare();
			_fe3d.gfx_setLensFlareMap(flareMapPath);
			_fe3d.gfx_setLensFlareIntensity(intensity);
			_fe3d.gfx_setLensFlareSensitivity(sensitivity);
		}
		else if(lineType == "GRAPHICS_SKY_EXPOSURE")
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
		else if(lineType == "GRAPHICS_BLOOM")
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
			Logger::throwError("WorldEditor::loadEditorWorldFromFile::2");
		}
	}

	// Close file
	file.close();

	// Set new world ID
	_loadedWorldID = fileName;

	// Logging
	Logger::throwInfo("World data loaded!");

	// Return
	return true;
}