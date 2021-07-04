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
	string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : 
		("projects\\" + _currentProjectID)) + "\\scenes\\");
	if (!_fe3d.misc_isDirectoryExisting(directoryPath))
	{
		_fe3d.logger_throwError("Project \"" + _currentProjectID + "\" corrupted: \"scenes\\\" folder missing!");
	}
	else if (!_fe3d.misc_isDirectoryExisting(directoryPath + "editor\\"))
	{
		_fe3d.logger_throwError("Project \"" + _currentProjectID + "\" corrupted: \"scenes\\editor\\\" folder missing!");
	}

	// Check if scene file exists
	string fullFilePath = string(directoryPath + "editor\\" + fileName + ".fe3d");
	if (_fe3d.misc_isFileExisting(fullFilePath))
	{
		// Set new scene ID
		_loadedSceneID = fileName;

		// Load scene file
		std::ifstream file(fullFilePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// For file extraction
			std::istringstream iss(line);

			// Extract type from file
			string entityType;
			iss >> entityType;

			// Load entity according to type
			if (entityType == "SKY")
			{
				// Data placeholders
				string skyID, previewID;

				// Extract data
				iss >> skyID >> previewID;

				// Add sky
				if (_copyPreviewSky(skyID, previewID))
				{
					if (_isEditorLoaded)
					{
						_currentSkyID = skyID;
					}
				}
			}
			else if (entityType == "TERRAIN")
			{
				// Data placeholders
				string terrainID, previewID;

				// Extract data
				iss >> terrainID >> previewID;

				// Add terrain
				if (_copyPreviewTerrain(terrainID, previewID))
				{
					if (_isEditorLoaded)
					{
						_currentTerrainID = terrainID;
					}
				}
			}
			else if (entityType == "WATER")
			{
				// Data placeholders
				string waterID, previewID;

				// Extract data
				iss >> waterID >> previewID;

				// Add water
				if (_copyPreviewWater(waterID, previewID))
				{
					if (_isEditorLoaded)
					{
						_currentWaterID = waterID;
					}
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

				// Extract main data
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

				// Check if preview model instancing changed
				if (_fe3d.modelEntity_isExisting(previewID))
				{
					if (_fe3d.modelEntity_isInstanced(previewID) && (modelID != previewID.substr(1)) ||
						!_fe3d.modelEntity_isInstanced(previewID) && (modelID == previewID.substr(1)))
					{
						_fe3d.logger_throwWarning("Model instancing with ID \"" + modelID + "\" differs from base model!");
						continue;
					}
				}

				// Add model
				if (_copyPreviewModel(modelID, previewID, position))
				{
					// Set properties
					_fe3d.modelEntity_setRotation(modelID, rotation);
					_fe3d.modelEntity_setSize(modelID, size);
					_fe3d.modelEntity_setStaticToCamera(modelID, isFrozen);

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

					// Extract instanced offsets
					if (_fe3d.modelEntity_isInstanced(modelID))
					{
						vector<Vec3> instancedOffsets;
						while (true)
						{
							// Check if file has offset data left
							string nextElement;
							iss >> nextElement;

							// Check for end of line
							if (nextElement == "")
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
						_fe3d.modelEntity_setInstanced(modelID, true, instancedOffsets);
					}

					// Hide model if LOD (and executing game)
					if (makeInvisible)
					{
						_fe3d.modelEntity_setVisible(modelID, false);
					}
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
				if (_copyPreviewBillboard(billboardID, previewID, position))
				{
					_fe3d.billboardEntity_setRotation(billboardID, rotation);
					_fe3d.billboardEntity_setSize(billboardID, size);
				}
			}
			else if (entityType == "SOUND")
			{
				// Data placeholders
				string soundID, previewID;
				Vec3 position;
				float maxVolume, maxDistance;

				// Extract data
				iss >>
					soundID >>
					previewID >>
					position.x >>
					position.y >>
					position.z >>
					maxVolume >>
					maxDistance;

				// Add speaker if in editor
				if (_isEditorLoaded)
				{
					_fe3d.modelEntity_add("@speaker_" + soundID, "engine_assets\\meshes\\speaker.obj", position, Vec3(0.0f), DEFAULT_SPEAKER_SIZE);
					_fe3d.modelEntity_setShadowed("@speaker_" + soundID, false);
					_fe3d.aabbEntity_bindToModelEntity("@speaker_" + soundID, Vec3(0.0f), DEFAULT_SPEAKER_AABB_SIZE, true, true);
				}

				// Add sound
				if (_copyPreviewAudio(soundID, previewID, position))
				{
					_fe3d.soundEntity_setMaxVolume(soundID, maxVolume);
					_fe3d.soundEntity_setMaxDistance(soundID, maxDistance);
					_fe3d.soundEntity_play(soundID, -1, 0);
				}
			}
			else if (entityType == "AMBIENT_LIGHT")
			{
				// Values
				Vec3 ambientLightingColor;
				float ambientLightingIntensity;

				// Extract
				iss >>
					ambientLightingColor.r >>
					ambientLightingColor.g >>
					ambientLightingColor.b >>
					ambientLightingIntensity;

				// Add ambient lighting
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

				// Set lightsource billboard
				_fe3d.billboardEntity_setPosition("@@lightSource", directionalLightingPosition);
				_fe3d.billboardEntity_setSize("@@lightSource", Vec2(billboardSize));
				_fe3d.billboardEntity_setLightness("@@lightSource", billboardLightness);
				_fe3d.billboardEntity_setColor("@@lightSource", directionalLightingColor);
				_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
				_fe3d.billboardEntity_setShadowed("@@lightSource", false);
				_fe3d.billboardEntity_setVisible("@@lightSource", true);
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
					_fe3d.modelEntity_add("@" + lightID, "engine_assets\\meshes\\lamp.obj", position, Vec3(0.0f), DEFAULT_LIGHTBULB_SIZE);
					_fe3d.modelEntity_setShadowed("@" + lightID, false);
					_fe3d.modelEntity_setColor("@" + lightID, color);
					_fe3d.aabbEntity_bindToModelEntity("@" + lightID, Vec3(0.0f), DEFAULT_LIGHTBULB_AABB_SIZE, true, true);
				}

				// Add point light
				_fe3d.lightEntity_add(lightID, position, color, intensity, distance);
				_loadedLightIDs.push_back(lightID);
			}
			else if (entityType == "LOD_DISTANCE")
			{
				// Data placeholders
				float lodDistance;

				// Extract data
				iss >> lodDistance;

				// Set distance
				_fe3d.misc_setLevelOfDetailDistance(lodDistance);
			}
			else if (entityType == "EDITOR_SPEED")
			{
				if (_isEditorLoaded)
				{
					iss >> _editorSpeed;
				}
			}
			else if (entityType == "EDITOR_POSITION")
			{
				// Data placeholders
				Vec3 position;

				// Extract data
				iss >> position.x >> position.y >> position.z;

				// Set position
				if (_isEditorLoaded)
				{
					_fe3d.camera_setPosition(position);
				}
			}
			else if (entityType == "EDITOR_YAW")
			{
				// Data placeholders
				float yaw;

				// Extract data
				iss >> yaw;

				// Set yaw
				if (_isEditorLoaded)
				{
					_fe3d.camera_setYaw(yaw);
				}
			}
			else if (entityType == "EDITOR_PITCH")
			{
				// Data placeholders
				float pitch;

				// Extract data
				iss >> pitch;

				// Set pitch
				if (_isEditorLoaded)
				{
					_fe3d.camera_setPitch(pitch);
				}
			}
			else if (entityType == "GRAPHICS_SHADOWS")
			{
				// Data placeholders
				float size, lightness;
				Vec3 position, center;
				bool isFollowingCamera;
				bool isSoftShadowed;
				int interval;

				// Extract data
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
					isSoftShadowed >>
					interval;

				// Enable shadows
				_fe3d.gfx_enableShadows(position, center, size, size * 2.0f, lightness, isFollowingCamera, isSoftShadowed, interval);
			}
			else if (entityType == "GRAPHICS_MOTIONBLUR")
			{
				// Data placeholders
				float strength;

				// Extract data
				iss >> strength;

				// Enable motion blur
				_fe3d.gfx_enableMotionBlur(strength);
			}
			else if (entityType == "GRAPHICS_DOF")
			{
				// Data placeholders
				bool isDynamic;
				float blurDistance, maxDistance;

				// Extract data
				iss >> isDynamic >> blurDistance >> maxDistance;

				// Enable DOF
				_fe3d.gfx_enableDOF(isDynamic, maxDistance, blurDistance);
			}
			else if (entityType == "GRAPHICS_FOG")
			{
				// Data placeholders
				float minDistance, maxDistance, thickness;
				Vec3 color;

				// Extract data
				iss >> minDistance >> maxDistance >> thickness >> color.r >> color.g >> color.b;

				// Enable fog
				_fe3d.gfx_enableFog(minDistance, maxDistance, thickness, color);
			}
			else if (entityType == "GRAPHICS_LENSFLARE")
			{
				// Data placeholders
				string flareMapPath;
				float intensity, multiplier;

				// Extract data
				iss >> flareMapPath >> intensity >> multiplier;

				// Perform empty string & space conversions
				flareMapPath = (flareMapPath == "?") ? "" : flareMapPath;
				std::replace(flareMapPath.begin(), flareMapPath.end(), '?', ' ');

				// Enable lens flare
				_fe3d.gfx_enableLensFlare(flareMapPath, intensity, multiplier);
			}
			else if (entityType == "GRAPHICS_SKYHDR")
			{
				// Data placeholders
				float intensity;

				// Extract data
				iss >> intensity;
				
				// Enable skyHDR
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
		_fe3d.logger_throwWarning("Cannot load scene with ID \"" + fileName + "\"!");
	}
}