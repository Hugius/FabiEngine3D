#include "scene_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void SceneEditor::loadSceneFromFile(bool isCustomScene, const string& fileName)
{
	// Error checking
	if (_currentProjectID == "" && !isCustomScene)
	{
		_fe3d.logger_throwError("No current project loaded --> SceneEditor::loadSceneFromFile()");
	}

	// Check if scene directory still exists
	string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\scenes\\";
	if (!_fe3d.misc_isDirectory(directoryPath) ||
		!_fe3d.misc_isDirectory(directoryPath + "custom\\") ||
		!_fe3d.misc_isDirectory(directoryPath + "editor\\"))
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: scenes folder(s) missing!");
	}

	// Check if scene file exists
	string fullFileName = (isCustomScene ? ("custom\\" + fileName) : ("editor\\" + fileName));
	string fullFilePath = (directoryPath + fullFileName + ".fe3d");
	if (_fe3d.misc_isFileExisting(fullFilePath))
	{
		// Set miscellaneous stuff
		_loadedSceneID = fileName;
		_loadedSkyID = "";
		_loadedTerrainID = "";
		_loadedWaterID = "";
		_loadedModelIDs.clear();
		_loadedBillboardIDs.clear();
		_loadedLightIDs.clear();
		_loadedAudioIDs.clear();

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
				// Values
				string skyID;
				std::array<string, 6> diffuseMapPaths{};
				float rotationSpeed, lightness;
				Vec3 color;

				// Load base data
				iss >>
					skyID >>
					diffuseMapPaths[0] >>
					diffuseMapPaths[1] >>
					diffuseMapPaths[2] >>
					diffuseMapPaths[3] >>
					diffuseMapPaths[4] >>
					diffuseMapPaths[5] >>
					rotationSpeed >>
					lightness >>
					color.r >>
					color.g >>
					color.b;

				// Perform empty string & space conversions
				for (auto& diffuseMapPath : diffuseMapPaths)
				{
					diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
					std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				}

				// Only for scene editing
				if (_isEditorLoaded)
				{
					_currentSkyID = skyID;
				}

				// Add new sky entity
				_placeSky(skyID, diffuseMapPaths, lightness, rotationSpeed, color);
			}
			else if (entityType == "TERRAIN")
			{
				// Values
				string terrainID, heightMapPath, diffuseMapPath, normalMapPath,
					normalMapPathR, normalMapPathG, normalMapPathB,
					blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
				float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB, specularFactor, specularIntensity;
				bool isBlendMapped, isNormalMapped, isNormalMappedR, isNormalMappedG, isNormalMappedB, isSpecular;

				// Load base data
				iss >>
					terrainID >>
					heightMapPath >>
					diffuseMapPath >>
					maxHeight >>
					uvRepeat >>
					lightness >>
					isBlendMapped >>
					blendMapPath >>
					blendMapPathR >>
					blendMapPathG >>
					blendMapPathB >>
					blendRepeatR >>
					blendRepeatG >>
					blendRepeatB >>
					isNormalMapped >>
					isNormalMappedR >>
					isNormalMappedG >>
					isNormalMappedB >>
					normalMapPath >>
					normalMapPathR >>
					normalMapPathG >>
					normalMapPathB >>
					isSpecular >>
					specularFactor >>
					specularIntensity;

				// Perform empty string & space conversions
				heightMapPath = (heightMapPath == "?") ? "" : heightMapPath;
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
				normalMapPathR = (normalMapPathR == "?") ? "" : normalMapPathR;
				normalMapPathG = (normalMapPathG == "?") ? "" : normalMapPathG;
				normalMapPathB = (normalMapPathB == "?") ? "" : normalMapPathB;
				blendMapPath = (blendMapPath == "?") ? "?" : blendMapPath;
				blendMapPathR = (blendMapPathR == "?") ? "" : blendMapPathR;
				blendMapPathG = (blendMapPathG == "?") ? "" : blendMapPathG;
				blendMapPathB = (blendMapPathB == "?") ? "" : blendMapPathB;
				std::replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
				std::replace(normalMapPathR.begin(), normalMapPathR.end(), '?', ' ');
				std::replace(normalMapPathG.begin(), normalMapPathG.end(), '?', ' ');
				std::replace(normalMapPathB.begin(), normalMapPathB.end(), '?', ' ');
				std::replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
				std::replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
				std::replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
				std::replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

				// Only for scene editing
				if (_isEditorLoaded)
				{
					_currentTerrainID = terrainID;
				}

				// Add new terrain entity
				_placeTerrain(terrainID, heightMapPath, maxHeight, uvRepeat, isBlendMapped, lightness,
					blendRepeatR, blendRepeatG, blendRepeatB, isNormalMapped, isNormalMappedR, isNormalMappedG, isNormalMappedB,
					isSpecular, specularFactor, specularIntensity, diffuseMapPath, normalMapPath, normalMapPathR, normalMapPathG,
					normalMapPathB, blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB);
			}
			else if (entityType == "WATER")
			{
				// Values
				string waterID, dudvMapPath, normalMapPath, displacementMapPath;
				bool isWaving, isRippling, isSpecularLighted, isReflective, isRefractive;
				Vec2 speed;
				Vec3 color, position;
				float size, uvRepeat, waveHeightFactor, transparency, specularFactor, specularIntensity;

				// Load base data
				iss >>
					waterID >>
					dudvMapPath >>
					normalMapPath >>
					displacementMapPath >>
					isWaving >>
					isRippling >>
					isSpecularLighted >>
					isReflective >>
					isRefractive >>
					color.r >>
					color.g >>
					color.b >>
					size >>
					position.x >>
					position.y >>
					position.z >>
					uvRepeat >>
					waveHeightFactor >>
					speed.x >>
					speed.y >>
					transparency >>
					specularFactor >>
					specularIntensity;

				// Perform empty string & space conversions
				dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
				normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
				displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);
				std::replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
				std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
				std::replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

				// Only for scene editing
				if (_isEditorLoaded)
				{
					_currentWaterID = waterID;
				}

				// Add new water entity
				_placeWater(waterID, position, size, isWaving, isRippling, isSpecularLighted, isReflective,
					isRefractive, waveHeightFactor, specularFactor, specularIntensity, transparency, color, uvRepeat,
					speed, dudvMapPath, normalMapPath, displacementMapPath);
			}
			else if (entityType == "MODEL")
			{
				// Model ID
				string modelID;
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

				// Values
				string meshPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, lodEntityID, animationID;
				Vec3 position, rotation, size, color;
				int reflectionType;
				float uvRepeat, specularFactor, specularIntensity, lightness;
				bool isFaceculled, isShadowed, isTransparent, isSpecular, isFrozen, isInstanced;
				vector<Vec3> instancedOffsets;
				vector<string> aabbNames;
				vector<Vec3> aabbPositions;
				vector<Vec3> aabbSizes;

				// Extract general data from file
				iss >>
					position.x >>
					position.y >>
					position.z >>
					rotation.x >>
					rotation.y >>
					rotation.z >>
					size.x >>
					size.y >>
					size.z >>
					meshPath >>
					diffuseMapPath >>
					lightMapPath >>
					reflectionMapPath >>
					normalMapPath >>
					isFrozen >>
					isFaceculled >>
					isShadowed >>
					isTransparent >>
					reflectionType >>
					isSpecular >>
					specularFactor >>
					specularIntensity >>
					lightness >>
					color.r >>
					color.g >>
					color.b >>
					uvRepeat >>
					lodEntityID >>
					isInstanced >>
					animationID;

				// Extract instanced offset data from file
				while (isInstanced)
				{
					// Check if file has offset data left
					string nextElement;
					iss >> nextElement;

					// Check if item is a number
					if (nextElement == "") // End of line, because instanced model cannot have AABB
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

				// Extract AABB data from file
				while (true)
				{
					// Check if file has AABB data left
					string aabbName;
					Vec3 position, size;
					iss >> aabbName;
					if (aabbName == "")
					{
						break;
					}
					else
					{
						iss >> position.x >> position.y >> position.z >> size.x >> size.y >> size.z;
						aabbNames.push_back(aabbName);
						aabbPositions.push_back(position);
						aabbSizes.push_back(size);
					}
				}

				// Perform empty string & space conversions
				meshPath = (meshPath == "?") ? "" : meshPath;
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				lightMapPath = (lightMapPath == "?") ? "" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
				normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
				lodEntityID = (lodEntityID == "?") ? "" : lodEntityID;
				animationID = (animationID == "?") ? "" : animationID;
				std::replace(meshPath.begin(), meshPath.end(), '?', ' ');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				std::replace(lightMapPath.begin(), lightMapPath.end(), '?', ' ');
				std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
				std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
				std::replace(lodEntityID.begin(), lodEntityID.end(), '?', ' ');
				std::replace(animationID.begin(), animationID.end(), '?', ' ');

				// Add the model
				_placeModel(modelID, position, rotation, size, meshPath, diffuseMapPath, lightMapPath,
					reflectionMapPath, normalMapPath, isFrozen, isFaceculled, isShadowed, isTransparent, isSpecular, reflectionType, specularFactor,
					specularIntensity, lightness, color, uvRepeat, lodEntityID,
					isInstanced, instancedOffsets, aabbNames, aabbPositions, aabbSizes, animationID);

				// Hide LOD entity (running script)
				if (makeInvisible)
				{
					_fe3d.gameEntity_hide(modelID);
				}
			}
			else if (entityType == "BILLBOARD")
			{
				// Placeholder variables
				string billboardID, diffusePath, fontPath, textContent;
				Vec3 position, rotation, color;
				Vec2 size;
				float lightness;
				bool facingX, facingY, isTransparent, isAnimated;
				int animationRows, animationColumns, animationFramestep;

				// Extract from file
				iss >>
					billboardID >>
					position.x >>
					position.y >>
					position.z >>
					rotation.x >>
					rotation.y >>
					rotation.z >>
					size.x >>
					size.y >>
					color.r >>
					color.g >>
					color.b >>
					facingX >>
					facingY >>
					diffusePath >>
					isTransparent >>
					fontPath >>
					textContent >>
					isAnimated >>
					animationRows >>
					animationColumns >>
					animationFramestep >>
					lightness;

				// Perform empty string & space conversions
				diffusePath = (diffusePath == "?") ? "" : diffusePath;
				fontPath = (fontPath == "?") ? "" : fontPath;
				textContent = (textContent == "?") ? "" : textContent;
				std::replace(diffusePath.begin(), diffusePath.end(), '?', ' ');
				std::replace(fontPath.begin(), fontPath.end(), '?', ' ');
				std::replace(textContent.begin(), textContent.end(), '?', ' ');

				// Add the billboard
				_placeBillboard(billboardID, diffusePath, fontPath, textContent, position, rotation, size, color, facingX, facingY, isTransparent, isAnimated,
					animationRows, animationColumns, animationFramestep, lightness);
			}
			else if (entityType == "AUDIO")
			{
				// Values
				string ID, audioPath;
				Vec3 position;
				float maxVolume, maxDistance;

				// Extract line data
				iss >> ID >> audioPath >> position.x >> position.y >> position.z >> maxVolume >> maxDistance;

				// Perform empty string & space conversions
				audioPath = (audioPath == "?") ? "" : audioPath;
				std::replace(audioPath.begin(), audioPath.end(), '?', ' ');

				// Add speaker
				if (_isEditorLoaded)
				{
					_fe3d.gameEntity_add("@speaker_" + ID, "engine_assets\\meshes\\speaker.obj", position, Vec3(0.0f), DEFAULT_SPEAKER_SIZE);
					_fe3d.gameEntity_setShadowed("@speaker_" + ID, false);
					_fe3d.aabbEntity_bindToGameEntity("@speaker_" + ID, Vec3(0.0f), DEFAULT_SPEAKER_AABB_SIZE, true, true);
				}

				// Add audio
				_fe3d.audioEntity_add3D(ID, audioPath, position, maxVolume, maxDistance);
				_fe3d.audioEntity_play(ID, -1, 0.0f);
				_loadedAudioIDs.push_back(ID);
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
				// Values
				Vec3 directionalLightingPosition, directionalLightingColor;
				float directionalLightingIntensity, billboardSize, billboardLightness;

				// Extract
				iss >> directionalLightingPosition.x >> directionalLightingPosition.y >> directionalLightingPosition.z >>
					directionalLightingColor.r >> directionalLightingColor.g >> directionalLightingColor.b >>
					directionalLightingIntensity >> billboardSize >> billboardLightness;

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
				// Values
				string ID;
				Vec3 position, color;
				float intensity, distance;

				// Extract line data
				iss >> ID >> position.x >> position.y >> position.z >> color.r >> color.g >> color.b >> intensity >> distance;

				// Add lightbulbs
				if (_isEditorLoaded)
				{
					_fe3d.gameEntity_add("@" + ID, "engine_assets\\meshes\\lamp.obj", position, Vec3(0.0f), DEFAULT_LIGHTBULB_SIZE);
					_fe3d.gameEntity_setShadowed("@" + ID, false);
					_fe3d.gameEntity_setColor("@" + ID, color);
					_fe3d.aabbEntity_bindToGameEntity("@" + ID, Vec3(0.0f), DEFAULT_LIGHTBULB_AABB_SIZE, true, true);
				}

				// Add light
				_fe3d.lightEntity_add(ID, position, color, intensity, distance);
				_loadedLightIDs.push_back(ID);
			}
			else if (entityType == "LOD_DISTANCE")
			{
				float lodDistance;
				iss >> lodDistance;
				_fe3d.gameEntity_setLevelOfDetailDistance(lodDistance);
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