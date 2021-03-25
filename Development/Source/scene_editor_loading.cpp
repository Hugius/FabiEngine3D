#include "scene_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void SceneEditor::loadEditorSceneFromFile(const string& fileName)
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> SceneEditor::loadEditorSceneFromFile()");
	}

	// Check if scene directory still exists
	string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\";
	if (!_fe3d.misc_isDirectoryExisting(directoryPath) || !_fe3d.misc_isDirectoryExisting(directoryPath + "editor\\"))
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: scenes folder(s) missing!");
	}

	// Check if scene file exists
	string fullFilePath = string(directoryPath + "editor\\" + fileName + ".fe3d");
	if (_fe3d.misc_isFileExisting(fullFilePath))
	{
		// Set miscellaneous stuff
		_loadedSceneID = fileName;
		_loadedSkyID = "";
		_loadedTerrainID = "";
		_loadedWaterID = "";
		_loadedModelIDs.clear();
		_loadedBillboardIDs.clear();
		_loadedAudioIDs.clear();
		_loadedLightIDs.clear();

		// No sky at default
		_fe3d.skyEntity_select("");

		// Default camera
		if (_isEditorLoaded)
		{
			_fe3d.camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f));
		}

		// Disable vsync
		_fe3d.misc_setVsync(false);

		// Default graphics
		_fe3d.gfx_enableSpecularLighting();
		_fe3d.gfx_enablePointLighting();
		_fe3d.gfx_enableSkyReflections(0.5f);
		_fe3d.gfx_enableSceneReflections(0.5f);
		_fe3d.gfx_enableLightMapping();
		_fe3d.gfx_enableNormalMapping();
		_fe3d.gfx_enableWaterEffects();

		// Load scene file
		std::ifstream file(fullFilePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string entityType;

			// For file extraction
			std::istringstream iss(line);

			// Extract type from file
			iss >> entityType;

			// Load entity according to type
			if (entityType == "SKY")
			{
				// Extract data
				string skyID;
				iss >> skyID;

				// Add sky
				copyPreviewSky(skyID, "@" + skyID);

				// Miscellaneous
				if (_isEditorLoaded)
				{
					_currentSkyID = skyID;
				}
			}
			else if (entityType == "TERRAIN")
			{
				// Extract data
				string terrainID;
				iss >> terrainID;

				// Add terrain
				copyPreviewTerrain(terrainID, "@" + terrainID);

				// Miscellaneous
				if (_isEditorLoaded)
				{
					_currentTerrainID = terrainID;
				}
			}
			else if (entityType == "WATER")
			{
				// Extract data
				string waterID;
				iss >> waterID;

				// Add water
				copyPreviewWater(waterID, "@" + waterID);

				// Miscellaneous
				if (_isEditorLoaded)
				{
					_currentWaterID = waterID;
				}
			}
			else if (entityType == "MODEL")
			{
				// Data placeholders
				string modelID, previewID, animationID;
				Vec3 position, rotation, size;
				bool isFrozen;

				// Extract ID
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

				// Extract data
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
				std::replace(animationID.begin(), animationID.end(), '?', ' ');

				// Add model
				copyPreviewModel(modelID, previewID, position);

				// Setting properties
				_fe3d.gameEntity_setRotation(modelID, rotation);
				_fe3d.gameEntity_setSize(modelID, size);
				_fe3d.gameEntity_setStaticToCamera(modelID, isFrozen);
				
				// Play animation
				if (!animationID.empty())
				{
					_animationEditor.startAnimation(animationID, modelID, -1);
				}

				// Hide model if LOD (and executing game)
				if (makeInvisible)
				{
					_fe3d.gameEntity_hide(modelID);
				}
			}
			else if (entityType == "BILLBOARD")
			{
				// Data placeholders
				string billboardID, previewID;
				Vec3 position, rotation;
				Vec2 size;

				// Extract data
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

				// Add billboard
				copyPreviewBillboard(billboardID, previewID, position);

				// Setting properties
				_fe3d.billboardEntity_setRotation(billboardID, rotation);
				_fe3d.billboardEntity_setSize(billboardID, size);
			}
			else if (entityType == "AUDIO")
			{
				// Data placeholders
				string audioID, previewID;
				Vec3 position;
				float maxVolume, maxDistance;

				// Extract data
				iss >>
					audioID >>
					previewID >>
					position.x >>
					position.y >>
					position.z >>
					maxVolume >>
					maxDistance;

				// Add audio
				copyPreviewAudio(audioID, previewID, position);
			}
			else if (entityType == "AMBIENT_LIGHT")
			{
				// Values
				Vec3 ambientLightingColor;
				float ambientLightingIntensity;

				// Extract
				iss >> ambientLightingColor.r >> ambientLightingColor.g >> ambientLightingColor.b >> ambientLightingIntensity;

				// Apply
				_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
			}
			else if (entityType == "DIRECTIONAL_LIGHT")
			{
				// Data placeholders
				Vec3 directionalLightingPosition, directionalLightingColor;
				float directionalLightingIntensity, billboardSize, billboardLightness;

				// Extract data
				iss >> 
					directionalLightingPosition.x >> 
					directionalLightingPosition.y >> 
					directionalLightingPosition.z >>
					directionalLightingColor.r >> 
					directionalLightingColor.g >> 
					directionalLightingColor.b >>
					directionalLightingIntensity >> 
					billboardSize >> 
					billboardLightness;

				// Add directional lighting
				_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);

				// Add lightsource billboard
				_fe3d.billboardEntity_setPosition("@@lightSource", directionalLightingPosition);
				_fe3d.billboardEntity_setSize("@@lightSource", Vec2(billboardSize));
				_fe3d.billboardEntity_setLightness("@@lightSource", billboardLightness);
				_fe3d.billboardEntity_setColor("@@lightSource", directionalLightingColor);
				_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
				_fe3d.billboardEntity_show("@@lightSource");
			}
			else if (entityType == "POINT_LIGHT")
			{
				// Data placeholders
				string lightID;
				Vec3 position, color;
				float intensity, distance;

				// Extract data
				iss >>
					lightID >>
					position.x >>
					position.y >>
					position.z >>
					color.r >>
					color.g >>
					color.b >>
					intensity >>
					distance;

				// Add lightbulb
				if (_isEditorLoaded)
				{
					_fe3d.gameEntity_add("@" + lightID, "engine_assets\\meshes\\lamp.obj", position, Vec3(0.0f), DEFAULT_LIGHTBULB_SIZE);
					_fe3d.gameEntity_setShadowed("@" + lightID, false);
					_fe3d.gameEntity_setColor("@" + lightID, color);
					_fe3d.aabbEntity_bindToGameEntity("@" + lightID, Vec3(0.0f), DEFAULT_LIGHTBULB_AABB_SIZE, true, true);
				}

				// Add point light
				_fe3d.lightEntity_add(lightID, position, color, intensity, distance);
				_loadedLightIDs.push_back(lightID);
			}
			else if (entityType == "LOD_DISTANCE")
			{
				float lodDistance;
				iss >> lodDistance;
				_fe3d.misc_setLevelOfDetailDistance(lodDistance);
			}
			else if (entityType == "EDITOR_SPEED")
			{
				iss >> _customEditorSpeed;
			}
			else if (entityType == "EDITOR_POSITION")
			{
				Vec3 position;
				iss >> position.x >> position.y >> position.z;
				_fe3d.camera_setPosition(position);
			}
			else if (entityType == "EDITOR_YAW")
			{
				float yaw;
				iss >> yaw;
				_fe3d.camera_setYaw(yaw);
			}
			else if (entityType == "EDITOR_PITCH")
			{
				float pitch;
				iss >> pitch;
				_fe3d.camera_setPitch(pitch);
			}
			else if (entityType == "GRAPHICS_SHADOWS")
			{
				bool enabled;
				float size, lightness;
				Vec3 position, center;
				bool isFollowingCamera;
				bool isSoftShadowed;
				int interval;
				iss >> enabled >> size >> lightness >> position.x >> position.y >> position.z >>
					center.x >> center.y >> center.z >> isFollowingCamera >> isSoftShadowed >> interval;
				_fe3d.gfx_enableShadows(position, center, size, size * 2.0f, lightness, isFollowingCamera, isSoftShadowed, interval);
			}
			else if (entityType == "GRAPHICS_MOTIONBLUR")
			{
				bool enabled;
				float strength;
				iss >> enabled >> strength;
				_fe3d.gfx_enableMotionBlur(strength);
			}
			else if (entityType == "GRAPHICS_DOF")
			{
				bool enabled, dynamic;
				float blurDistance, maxDistance;
				iss >> enabled >> dynamic >> blurDistance >> maxDistance;
				_fe3d.gfx_enableDOF(dynamic, maxDistance, blurDistance);
			}
			else if (entityType == "GRAPHICS_FOG")
			{
				bool enabled;
				float minDistance, maxDistance, thickness;
				Vec3 color;
				iss >> enabled >> minDistance >> maxDistance >> thickness >> color.r >> color.g >> color.b;
				_fe3d.gfx_enableFog(minDistance, maxDistance, thickness, color);
			}
			else if (entityType == "GRAPHICS_LENSFLARE")
			{
				bool enabled;
				string flareMapPath;
				float intensity, multiplier;
				iss >> enabled >> flareMapPath >> intensity >> multiplier;
				flareMapPath = (flareMapPath == "?") ? "" : flareMapPath;
				std::replace(flareMapPath.begin(), flareMapPath.end(), '?', ' ');
				_fe3d.gfx_enableLensFlare(flareMapPath, intensity, multiplier);
			}
			else if (entityType == "GRAPHICS_SKYHDR")
			{
				bool enabled;
				float intensity;
				iss >> enabled >> intensity;
				_fe3d.gfx_enableSkyHDR(intensity);
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectID + "\" loaded!");
	}
	else
	{
		_fe3d.logger_throwWarning("Could not load scene \"" + fileName + "\"!");
	}
}