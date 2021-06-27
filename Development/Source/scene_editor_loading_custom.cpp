#include "scene_editor.hpp"

#include <fstream>
#include <algorithm>

void SceneEditor::loadCustomSceneFromFile(const string& fileName)
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> SceneEditor::loadCustomSceneFromFile()");
	}
	if (_isEditorLoaded)
	{
		_fe3d.logger_throwWarning("Tried to call saveCustomSceneToFile() from within scene editor!");
	}

	// Check if scene directory still exists
	string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scenes\\");
	if (!_fe3d.misc_isDirectoryExisting(directoryPath))
	{
		_fe3d.logger_throwError("Project \"" + _currentProjectID + "\" corrupted: \"scenes\\\" folder missing!");
	}
	else if (!_fe3d.misc_isDirectoryExisting(directoryPath + "custom\\"))
	{
		_fe3d.logger_throwError("Project \"" + _currentProjectID + "\" corrupted: \"scenes\\custom\\\" folder missing!");
	}

	// Check if scene file exists
	string fullFilePath = string(directoryPath + "custom\\" + fileName + ".fe3d");
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
				Vec3 color;
				float rotationSpeed, lightness;

				// Extract data
				iss >>
					skyID >>
					previewID >>
					rotationSpeed >>
					lightness >>
					color.r >>
					color.g >>
					color.b;

				// Add sky
				if (_copyPreviewSky(skyID, previewID))
				{
					_fe3d.skyEntity_setRotationSpeed(skyID, rotationSpeed);
					_fe3d.skyEntity_setLightness(skyID, lightness);
					_fe3d.skyEntity_setColor(skyID, color);
				}
			}
			else if (entityType == "TERRAIN")
			{
				// Data placeholders
				string terrainID, previewID;

				// Extract data
				iss >> terrainID >> previewID;

				// Add terrain
				_copyPreviewTerrain(terrainID, previewID);
			}
			else if (entityType == "WATER")
			{
				// Data placeholders
				string waterID, previewID;
				Vec3 color;
				Vec2 speed;
				float transparency;

				// Extract data
				iss >>
					waterID >>
					previewID >>
					color.r >>
					color.g >>
					color.b >>
					speed.x >>
					speed.y >>
					transparency;

				// Add water
				if (_copyPreviewWater(waterID, previewID))
				{
					_fe3d.waterEntity_setColor(waterID, color);
					_fe3d.waterEntity_setSpeed(waterID, speed);
					_fe3d.waterEntity_setTransparency(waterID, transparency);
				}
			}
			else if (entityType == "MODEL")
			{
				// Data placeholders
				string modelID, previewID;
				Vec3 position, rotation, rotationOrigin, size, color;
				float minHeight, maxHeight, alpha, lightness;
				unsigned partCount;
				bool isVisible, isFrozen, isAabbRaycastResponsive, isAabbCollisionResponsive;

				// Extract ID
				iss >> modelID;

				// Check if LOD entitty
				bool makeInvisible = (modelID[0] == '@');

				// Extract main data
				iss >>
					previewID >>
					isVisible >>
					isFrozen >>
					isAabbRaycastResponsive >>
					isAabbCollisionResponsive >>
					position.x >>
					position.y >>
					position.z >>
					rotation.x >>
					rotation.y >>
					rotation.z >>
					rotationOrigin.x >>
					rotationOrigin.y >>
					rotationOrigin.z >>
					size.x >>
					size.y >>
					size.z >>
					color.r >>
					color.g >>
					color.b >>
					minHeight >>
					maxHeight >>
					alpha >>
					lightness >>
					partCount;

				// Perform part checks
				if (partCount > 1)
				{
					// Read model part IDs
					vector<string> partIDs;
					for (unsigned int i = 0; i < partCount; i++)
					{
						string partID;
						iss >> partID;
						partIDs.push_back(partID);
					}

					// Check if preview model parts count
					if (partIDs.size() != _fe3d.modelEntity_getPartIDs(previewID).size())
					{
						_fe3d.logger_throwWarning("Scene model parts with ID \"" + modelID + "\" differ from base model!");
						continue;
					}

					// Check if preview model parts changed
					for (size_t i = 0; i < partIDs.size(); i++)
					{
						if (partIDs[i] != _fe3d.modelEntity_getPartIDs(previewID)[i])
						{
							_fe3d.logger_throwWarning("Scene model parts with ID \"" + modelID + "\" differ from base model!");
							continue;
						}
					}
				}

				// Add model
				if (_copyPreviewModel(modelID, previewID, position))
				{
					// Check if preview model instancing changed
					if (_fe3d.modelEntity_isExisting(previewID))
					{
						if (_fe3d.modelEntity_isInstanced(modelID) != _fe3d.modelEntity_isInstanced(previewID))
						{
							_fe3d.logger_throwWarning("Model instancing with ID \"" + modelID + "\" differs from base model!");
							_fe3d.modelEntity_delete(modelID);
							continue;
						}
					}

					// Set properties
					_fe3d.modelEntity_setRotation(modelID, rotation);
					_fe3d.modelEntity_setRotationOrigin(modelID, rotationOrigin);
					_fe3d.modelEntity_setSize(modelID, size);
					_fe3d.modelEntity_setStaticToCamera(modelID, isFrozen);
					_fe3d.modelEntity_setColor(modelID, color);
					_fe3d.modelEntity_setMinHeight(modelID, minHeight);
					_fe3d.modelEntity_setMaxHeight(modelID, maxHeight);
					_fe3d.modelEntity_setAlpha(modelID, alpha);
					_fe3d.modelEntity_setLightness(modelID, lightness);
					!isVisible ? _fe3d.modelEntity_hide(modelID) : void();
					for (const auto& ID : _fe3d.aabbEntity_getBoundIDs(modelID, true, false))
					{
						_fe3d.aabbEntity_setRaycastResponsive(ID, isAabbRaycastResponsive);
						_fe3d.aabbEntity_setCollisionResponsive(ID, isAabbCollisionResponsive);
					}

					// Extract part transformations
					for (unsigned int i = 0; i < partCount; i++)
					{
						// Extract data
						string partID;
						iss >>
							partID >>
							position.x >>
							position.y >>
							position.z >>
							rotation.x >>
							rotation.y >>
							rotation.z >>
							rotationOrigin.x >>
							rotationOrigin.y >>
							rotationOrigin.z >>
							size.x >>
							size.y >>
							size.z;

						// Set part transformation
						_fe3d.modelEntity_setPosition(modelID, position, partID);
						_fe3d.modelEntity_setRotation(modelID, rotation, partID);
						_fe3d.modelEntity_setRotationOrigin(modelID, rotationOrigin, partID);
						_fe3d.modelEntity_setSize(modelID, size, partID);
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

					// Hide model if LOD
					if (makeInvisible)
					{
						_fe3d.modelEntity_hide(modelID);
					}
				}
			}
			else if (entityType == "ANIMATION")
			{
				// Data placeholders
				string animationID, modelID;
				float speedMultiplier;
				int remainingLoops, fadeFramestep;
				unsigned int frameIndex;
				bool isPaused;

				// Extract main data
				iss >>
					animationID >>
					modelID >>
					isPaused >>
					frameIndex >>
					speedMultiplier >>
					remainingLoops >>
					fadeFramestep;

				// Extract speeds
				map<string, Vec3> speeds;
				while (true)
				{
					// Check if file has speed data left
					string nextElement;
					iss >> nextElement;

					// Check for end of line
					if (nextElement == "")
					{
						break;
					}
					else // Add speed
					{
						string partID = (nextElement == "?") ? "" : nextElement;
						Vec3 speed;
						iss >> speed.x >> speed.y >> speed.z;
						speeds[partID] = speed;
					}
				}

				// Start animation
				_animationEditor.startAnimation(animationID, modelID, remainingLoops);

				// Check if animation exists
				if (_animationEditor.isAnimationExisting(animationID))
				{
					// Retrieve raw animation data for editing
					string errorMessage = "Trying to retrieve animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";
					auto animationData = _animationEditor.getAnimationData(animationID, modelID, errorMessage);

					// Set properties
					isPaused ? _animationEditor.pauseAnimation(animationID, modelID) : void();
					animationData->speedMultiplier = speedMultiplier;
					animationData->fadeFramestep = fadeFramestep;
					animationData->frameIndex = frameIndex;
					animationData->frames[frameIndex].speeds = speeds;

					// Retrieve parts
					auto partIDs = _fe3d.modelEntity_getPartIDs(modelID);
					for (const auto& partID : partIDs)
					{
						// Retrieve part transformation
						auto translation = _fe3d.modelEntity_getPosition(modelID, partID);
						auto rotation = _fe3d.modelEntity_getRotation(modelID, partID);
						auto scaling = _fe3d.modelEntity_getSize(modelID, partID);

						// Set properties
						animationData->totalTranslations[partID] = translation;
						animationData->totalRotations[partID] = rotation;
						animationData->totalScalings[partID] = scaling;
					}
				}
			}
			else if (entityType == "BILLBOARD")
			{
				// Data placeholders
				string billboardID, previewID, textContent;
				Vec3 position, rotation, color;
				Vec2 size;
				float lightness, minHeight, maxHeight;
				int remainingAnimationLoops;
				unsigned int animationRowIndex, animationColumnIndex;
				bool isVisible, isAabbRaycastResponsive, isAabbCollisionResponsive, isFacingX, isFacingY, isAnimationPlaying, isAnimationPaused;

				// Extract data
				iss >>
					billboardID >>
					previewID >>
					isVisible >>
					isAabbRaycastResponsive >>
					isAabbCollisionResponsive >>
					isFacingX >>
					isFacingY >>
					isAnimationPlaying >>
					isAnimationPaused >>
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
					textContent >>
					lightness >>
					minHeight >>
					maxHeight >>
					remainingAnimationLoops >>
					animationRowIndex >>
					animationColumnIndex;

				// Perform empty string & space conversions
				textContent = (textContent == "?") ? "" : textContent;
				std::replace(textContent.begin(), textContent.end(), '?', ' ');

				// Add billboard
				if (_copyPreviewBillboard(billboardID, previewID, position))
				{
					// Set properties
					_fe3d.billboardEntity_setRotation(billboardID, rotation);
					_fe3d.billboardEntity_setSize(billboardID, size);
					_fe3d.billboardEntity_setCameraFacingX(billboardID, isFacingX);
					_fe3d.billboardEntity_setCameraFacingY(billboardID, isFacingY);
					_fe3d.billboardEntity_setColor(billboardID, color);
					_fe3d.billboardEntity_setTextContent(billboardID, textContent);
					_fe3d.billboardEntity_setLightness(billboardID, lightness);
					_fe3d.billboardEntity_setMinHeight(billboardID, minHeight);
					_fe3d.billboardEntity_setMaxHeight(billboardID, maxHeight);
					!isVisible ? _fe3d.billboardEntity_hide(billboardID) : void();
					for (const auto& ID : _fe3d.aabbEntity_getBoundIDs(billboardID, false, true))
					{
						_fe3d.aabbEntity_setRaycastResponsive(ID, isAabbRaycastResponsive);
						_fe3d.aabbEntity_setCollisionResponsive(ID, isAabbCollisionResponsive);
					}

					// Set animation progresss
					if (isAnimationPlaying)
					{
						// Play
						_fe3d.billboardEntity_stopSpriteAnimation(billboardID);
						_fe3d.billboardEntity_startSpriteAnimation(billboardID, remainingAnimationLoops);

						// Pause
						if (isAnimationPaused)
						{
							_fe3d.billboardEntity_pauseSpriteAnimation(billboardID);
						}

						// Progress
						_fe3d.billboardEntity_setSpriteAnimationRowIndex(billboardID, animationRowIndex);
						_fe3d.billboardEntity_setSpriteAnimationColumnIndex(billboardID, animationColumnIndex);
					}
				}
			}
			else if (entityType == "AABB")
			{
				// Data placeholders
				string aabbID;
				Vec3 position, size;
				bool isVisible, isRaycastResponsive, isCollisionResponsive;

				// Extract data
				iss >>
					aabbID >>
					isVisible >>
					isRaycastResponsive >>
					isCollisionResponsive >>
					position.x >>
					position.y >>
					position.z >>
					size.x >>
					size.y >>
					size.z;

				// Add AABB
				_fe3d.aabbEntity_add(aabbID, position, size, isRaycastResponsive, isCollisionResponsive, isVisible);
				_loadedAabbIDs.push_back(aabbID);
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

				// Set lightsource billboard
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

				// Add point light
				_fe3d.lightEntity_add(lightID, position, color, intensity, distance);
				_loadedLightIDs.push_back(lightID);
			}
			else if (entityType == "LOD_DISTANCE")
			{
				// Data placeholders
				float lodDistance;

				// Extract data
				iss >>
					lodDistance;

				// Set distance
				_fe3d.misc_setLevelOfDetailDistance(lodDistance);
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
		_fe3d.logger_throwWarning("Could not load scene with ID\"" + fileName + "\"!");
	}
}