#include "scene_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void SceneEditor::loadScene(const string& fileName)
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	// Compose full folder path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\scenes\\" + fileName + ".fe3d";

	// Check if scene file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Default camera
		_fe3d.camera_load(90.0f, 0.1f, 10000.0f, vec3(0.0f));

		// Default graphics
		_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 1.0f);
		_fe3d.gfx_enableSpecularLighting();
		_fe3d.gfx_enablePointLighting();
		_fe3d.gfx_enableSkyReflections(0.5f);
		_fe3d.gfx_enableSceneReflections(0.5f);
		_fe3d.gfx_enableLightMapping();
		_fe3d.gfx_enableNormalMapping();
		_fe3d.gfx_enableWaterEffects();

		// Load scene file
		std::ifstream file(filePath);
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
				string name;
				std::array<string, 6> diffuseMapPaths{};
				float rotationSpeed, lightness;
				vec3 color;

				// Load base data
				iss >>
					name >>
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

				// Load entity
				_currentSkyID = name;
				_placeSky(_currentSkyID, diffuseMapPaths, lightness, rotationSpeed, color);
			}
			else if (entityType == "TERRAIN")
			{
				// Values
				string name, heightMapPath, diffuseMapPath, blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB;
				float maxHeight, uvRepeat, lightness, blendRepeatR, blendRepeatG, blendRepeatB, specularIntensity;
				bool isBlendMapped, isSpecular;

				// Load base data
				iss >>
					name >>
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
					isSpecular >>
					specularIntensity;

				// Perform empty string & space conversions
				heightMapPath = (heightMapPath == "?") ? "" : heightMapPath;
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				blendMapPath = (blendMapPath == "?") ? "?" : blendMapPath;
				blendMapPathR = (blendMapPathR == "?") ? "" : blendMapPathR;
				blendMapPathG = (blendMapPathG == "?") ? "" : blendMapPathG;
				blendMapPathB = (blendMapPathB == "?") ? "" : blendMapPathB;
				std::replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				std::replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
				std::replace(blendMapPathR.begin(), blendMapPathR.end(), '?', ' ');
				std::replace(blendMapPathG.begin(), blendMapPathG.end(), '?', ' ');
				std::replace(blendMapPathB.begin(), blendMapPathB.end(), '?', ' ');

				// Add new terrain entity
				_currentTerrainID = name;
				_placeTerrain(_currentTerrainID, heightMapPath, maxHeight, uvRepeat, isBlendMapped, lightness, blendRepeatR, blendRepeatG, blendRepeatB, 
					isSpecular, specularIntensity, diffuseMapPath, blendMapPath, blendMapPathR, blendMapPathG, blendMapPathB);
			}
			else if (entityType == "WATER")
			{
				// Values
				string name, dudvMapPath, normalMapPath, displacementMapPath;
				bool isWaving, isRippling, isSpecularLighted, isReflective, isRefractive;
				vec2 speed;
				vec3 color, position;
				float size, uvRepeat, waveHeightFactor, transparency, specularFactor, specularIntensity;

				// Load base data
				iss >>
					name >>
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

				// Load entity
				_currentWaterID = name;
				_placeWater(_currentWaterID, position, size, isWaving, isRippling, isSpecularLighted, isReflective,
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
					if (_isLoaded)
					{
						continue;
					}
					else // Loading for script execution
					{
						makeInvisible = true;
					}
				}

				// Values
				string objPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, lodEntityID;
				vec3 position, rotation, size, color;
				float uvRepeat, specularFactor, specularIntensity, lightness;
				bool isFaceculled, isShadowed, isTransparent, isSpecular, isReflective, isFrozen, isInstanced;
				vector<vec3> instancedOffsets;
				vector<string> aabbNames;
				vector<vec3> aabbPositions;
				vector<vec3> aabbSizes;

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
					objPath >>
					diffuseMapPath >>
					lightMapPath >>
					reflectionMapPath >>
					normalMapPath >>
					isFrozen >>
					isFaceculled >>
					isShadowed >>
					isTransparent >>
					isReflective >>
					isSpecular >>
					specularFactor >>
					specularIntensity >>
					lightness >>
					color.r >>
					color.g >>
					color.b >>
					uvRepeat >>
					lodEntityID >>
					isInstanced;

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
						vec3 offset;
						offset.x = stof(nextElement);
						iss >> offset.y >> offset.z;
						instancedOffsets.push_back(offset);
					}
				}

				// Extract AABB data from file
				while (true)
				{
					// Check if file has AABB data left
					string name;
					vec3 position, size;
					iss >> name;
					if (name == "")
					{
						break;
					}
					else
					{
						iss >> position.x >> position.y >> position.z >> size.x >> size.y >> size.z;
						aabbNames.push_back(name);
						aabbPositions.push_back(position);
						aabbSizes.push_back(size);
					}
				}

				// Perform empty string & space conversions
				objPath = (objPath == "?") ? "" : objPath;
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				lightMapPath = (lightMapPath == "?") ? "" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
				normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
				lodEntityID = (lodEntityID == "?") ? "" : lodEntityID;
				std::replace(objPath.begin(), objPath.end(), '?', ' ');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				std::replace(lightMapPath.begin(), lightMapPath.end(), '?', ' ');
				std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
				std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
				std::replace(lodEntityID.begin(), lodEntityID.end(), '?', ' ');

				// Add the model
				_placeModel(modelID, position, rotation, size, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, isFrozen,
					isFaceculled, isShadowed, isTransparent, isReflective, isSpecular, specularFactor, specularIntensity, lightness,
					color, uvRepeat, lodEntityID, isInstanced, instancedOffsets, aabbNames, aabbPositions, aabbSizes);

				// Hide LOD entity
				if (makeInvisible)
				{
					_fe3d.gameEntity_hide(modelID);

				}
			}
			else if (entityType == "BILLBOARD")
			{
				// Placeholder variables
				string billboardID, diffusePath, fontPath, textContent;
				vec3 position, rotation, color;
				vec2 size;
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
					animationFramestep;

				// Perform empty string & space conversions
				diffusePath = (diffusePath == "?") ? "" : diffusePath;
				fontPath = (fontPath == "?") ? "" : fontPath;
				textContent = (textContent == "?") ? "" : textContent;
				std::replace(diffusePath.begin(), diffusePath.end(), '?', ' ');
				std::replace(fontPath.begin(), fontPath.end(), '?', ' ');
				std::replace(textContent.begin(), textContent.end(), '?', ' ');

				// Add the billboard
				_placeBillboard(billboardID, diffusePath, fontPath, textContent, position, rotation, size, color, facingX, facingY, isTransparent, isAnimated,
					animationRows, animationColumns, animationFramestep);
			}
			else if (entityType == "AMBIENT_LIGHT")
			{
				// Values
				vec3 ambientLightingColor;
				float ambientLightingIntensity;

				// Extract
				iss >> ambientLightingColor.r >> ambientLightingColor.g >> ambientLightingColor.b >> ambientLightingIntensity;

				// Apply
				_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
			}
			else if (entityType == "DIRECTIONAL_LIGHT")
			{
				// Values
				vec3 directionalLightingPosition, directionalLightingColor;
				float directionalLightingIntensity, billboardSize;

				// Extract
				iss >> directionalLightingPosition.x >> directionalLightingPosition.y >> directionalLightingPosition.z >>
					directionalLightingColor.r >> directionalLightingColor.g >> directionalLightingColor.b >>
					directionalLightingIntensity >> billboardSize;

				// Delete preview billboard
				if (_isLoaded)
				{
					_fe3d.billboardEntity_delete("@@lightSource");
				}

				// Apply
				_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);
				_fe3d.billBoardEntity_add("@@lightSource", "engine\\textures\\light_source.png", directionalLightingPosition, vec3(0.0f), vec2(billboardSize), true, true, true, true);
				_fe3d.billboardEntity_setDepthMapIncluded("@@lightSource", false);
			}
			else if (entityType == "POINT_LIGHT")
			{
				// Values
				string ID;
				vec3 position, color;
				float intensity, distance;

				// Extract line data
				iss >> ID >> position.x >> position.y >> position.z >> color.r >> color.g >> color.b >> intensity >> distance;

				// Add entities
				_fe3d.gameEntity_add("@" + ID, "engine\\models\\lamp.obj", position, vec3(0.0f), _defaultLightbulbSize);
				_fe3d.gameEntity_setShadowed("@" + ID, false);
				_fe3d.gameEntity_setDepthMapIncluded("@" + ID, false);
				_fe3d.aabbEntity_bindToGameEntity("@" + ID, vec3(0.0f), _defaultLightbulbAabbSize, true);
				_fe3d.lightEntity_add(ID, position, color, intensity, distance);
			}
			else if (entityType == "LOD_DISTANCE")
			{
				float lodDistance;
				iss >> lodDistance;
				_fe3d.gameEntity_setLevelOfDetailDistance(lodDistance);
			}
			else if (entityType == "EDITOR_SPEED")
			{
				iss >> _customCameraSpeed;
			}
			else if (entityType == "EDITOR_POSITION")
			{
				if (_isLoaded)
				{
					vec3 position;
					iss >> position.x >> position.y >> position.z;
					_fe3d.camera_setPosition(position);
				}
			}
			else if (entityType == "EDITOR_YAW")
			{
				if (_isLoaded)
				{
					float yaw;
					iss >> yaw;
					_fe3d.camera_setYaw(yaw);
				}
			}
			else if (entityType == "EDITOR_PITCH")
			{
				if (_isLoaded)
				{
					float pitch;
					iss >> pitch;
					_fe3d.camera_setPitch(pitch);
				}
			}
			else if (entityType == "GRAPHICS_SHADOWS")
			{
				bool enabled;
				float size;
				vec3 position, center;
				bool isFollowingCamera;
				int interval;
				iss >> enabled >> size >> position.x >> position.y >> position.z >> center.x >> center.y >> center.z >> isFollowingCamera >> interval;
				_fe3d.gfx_enableShadows(position, center, size, size * 1.5f, isFollowingCamera, interval);
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
				float minDistance, maxDistance, defaultFactor;
				vec3 color;
				iss >> enabled >> minDistance >> maxDistance >> defaultFactor >> color.r >> color.g >> color.b;
				_fe3d.gfx_enableFog(minDistance, maxDistance, defaultFactor, color);
			}
			else if (entityType == "GRAPHICS_LENSFLARE")
			{
				bool enabled;
				string flareMapPath;
				float intensity, multiplier;
				iss >> enabled >> flareMapPath >> intensity >> multiplier;
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
		_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectName + "\" loaded!");
	}
	else
	{
		_fe3d.logger_throwWarning("Could not load scene file \"" + fileName + "\"!");
	}
}

void SceneEditor::clearScene()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableSpecularLighting();
	_fe3d.gfx_disablePointLighting();
	_fe3d.gfx_disableFog();
	_fe3d.gfx_disableSkyReflections();
	_fe3d.gfx_disableSceneReflections();
	_fe3d.gfx_disableLightMapping();
	_fe3d.gfx_disableNormalMapping();
	_fe3d.gfx_disableShadows();
	_fe3d.gfx_disableWaterEffects();
	_fe3d.gfx_disableSkyHDR();
	_fe3d.gfx_disableDOF();
	_fe3d.gfx_disableMotionBlur();
	_fe3d.gfx_disableLensFlare();

	if (_isLoaded) // Currently in scene editor
	{
		// Delete sky entities
		for (auto& ID : _fe3d.skyEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.skyEntity_delete(ID);
			}
		}

		// Delete TERRAIN entities
		for (auto& ID : _fe3d.terrainEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.terrainEntity_delete(ID);
			}
		}

		// Delete WATER entities
		for (auto& ID : _fe3d.waterEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.waterEntity_delete(ID);
			}
		}

		// Delete GAME entities
		for (auto& ID : _fe3d.gameEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.gameEntity_delete(ID);
			}
		}

		// Delete BILLBOARD entities
		for (auto& ID : _fe3d.billboardEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.billboardEntity_delete(ID);
			}
			else if(ID == "@@lightSource") // Hide special "preview" entity
			{
				_fe3d.billboardEntity_hide(ID);
			}
		}

		// Delete LIGHT entities
		for (auto& ID : _fe3d.lightEntity_getAllIDs())
		{
			if (ID[0] != '@')
			{
				_fe3d.lightEntity_delete(ID);
			}
		}
	}
	else // Playing game
	{
		// Delete all sky entities except the engine background
		for (auto& ID : _fe3d.skyEntity_getAllIDs())
		{
			if (ID != "@@engineBackground")
			{
				_fe3d.skyEntity_delete(ID);
			}
		}

		// Delete all other entities
		_fe3d.terrainEntity_deleteAll();
		_fe3d.waterEntity_deleteAll();
		_fe3d.gameEntity_deleteAll();
		_fe3d.billboardEntity_deleteAll();
		_fe3d.lightEntity_deleteAll();
	}
}