#include "scene_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

bool SceneEditor::loadCustomSceneFromFile(const string& filename)
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("SceneEditor::loadCustomSceneFromFile::1");
	}
	if (_isEditorLoaded)
	{
		Logger::throwError("SceneEditor::loadCustomSceneFromFile::2");
	}

	// Compose file path
	const string filePath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scenes\\custom\\" + filename + ".fe3d");

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
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

		// Extract type from file
		string lineType;
		iss >> lineType;

		// Load entity according to type
		if (lineType == "SKY")
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

			// Create sky
			if (_copyPreviewSky(skyID, previewID))
			{
				_fe3d.skyEntity_setRotationSpeed(skyID, rotationSpeed);
				_fe3d.skyEntity_setLightness(skyID, lightness);
				_fe3d.skyEntity_setColor(skyID, color);
			}
		}
		else if (lineType == "TERRAIN")
		{
			// Data placeholders
			string terrainID, previewID;

			// Extract data
			iss >> terrainID >> previewID;

			// Create terrain
			_copyPreviewTerrain(terrainID, previewID);
		}
		else if (lineType == "WATER")
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

			// Create water
			if (_copyPreviewWater(waterID, previewID))
			{
				_fe3d.waterEntity_setColor(waterID, color);
				_fe3d.waterEntity_setSpeed(waterID, speed);
				_fe3d.waterEntity_setTransparency(waterID, transparency);
			}
		}
		else if (lineType == "MODEL")
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
					Logger::throwWarning("Scene model parts with ID \"" + modelID + "\" differ from base model!");
					continue;
				}

				// Check if preview model parts changed
				for (size_t i = 0; i < partIDs.size(); i++)
				{
					if (partIDs[i] != _fe3d.modelEntity_getPartIDs(previewID)[i])
					{
						Logger::throwWarning("Scene model parts with ID \"" + modelID + "\" differ from base model!");
						continue;
					}
				}
			}

			// Create model
			if (_copyPreviewModel(modelID, previewID, position))
			{
				// Check if preview model instancing changed
				if (_fe3d.modelEntity_isExisting(previewID))
				{
					if (_fe3d.modelEntity_isInstanced(modelID) != _fe3d.modelEntity_isInstanced(previewID))
					{
						Logger::throwWarning("Model instancing with ID \"" + modelID + "\" differs from base model!");
						_fe3d.modelEntity_delete(modelID);
						continue;
					}
				}

				// Set properties
				_fe3d.modelEntity_setRotation(modelID, "", rotation);
				_fe3d.modelEntity_setRotationOrigin(modelID, "", rotationOrigin);
				_fe3d.modelEntity_setSize(modelID, "", size);
				_fe3d.modelEntity_setStaticToCamera(modelID, isFrozen);
				_fe3d.modelEntity_setColor(modelID, "", color);
				_fe3d.modelEntity_setMinHeight(modelID, minHeight);
				_fe3d.modelEntity_setMaxHeight(modelID, maxHeight);
				_fe3d.modelEntity_setAlpha(modelID, alpha);
				_fe3d.modelEntity_setLightness(modelID, lightness);
				_fe3d.modelEntity_setVisible(modelID, isVisible);
				for (const auto& ID : _fe3d.aabbEntity_getBoundIDs(modelID, AabbParentType::MODEL_ENTITY))
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
					_fe3d.modelEntity_setPosition(modelID, partID, position);
					_fe3d.modelEntity_setRotation(modelID, partID, rotation);
					_fe3d.modelEntity_setRotationOrigin(modelID, partID, rotationOrigin);
					_fe3d.modelEntity_setSize(modelID, partID, size);
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

				// Hide model if LOD
				if (makeInvisible)
				{
					_fe3d.modelEntity_setVisible(modelID, false);
				}
			}
		}
		else if (lineType == "ANIMATION")
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
				if (nextElement.empty())
				{
					break;
				}
				else // Create speed
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
				string errorMessage = "Tried to retrieve animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";
				auto animationData = _animationEditor.getAnimationData(animationID, modelID, errorMessage);
				auto frameData = animationData->getFrames()[frameIndex];

				// Set properties
				isPaused ? _animationEditor.pauseAnimation(animationID, modelID) : void();
				animationData->setSpeedMultiplier(speedMultiplier);
				animationData->setFadeFramestep(fadeFramestep);
				animationData->setFrameIndex(frameIndex);
				for (const auto& [partID, speed] : speeds)
				{
					frameData.setSpeed(partID, speed);
				}
				
				// Retrieve parts
				auto partIDs = _fe3d.modelEntity_getPartIDs(modelID);
				for (const auto& partID : partIDs)
				{
					// Retrieve part transformation
					auto position = _fe3d.modelEntity_getPosition(modelID, partID);
					auto rotation = _fe3d.modelEntity_getRotation(modelID, partID);
					auto size = _fe3d.modelEntity_getSize(modelID, partID);

					// Set properties
					animationData->setTotalMovement(partID, position);
					animationData->setTotalRotation(partID, rotation);
					animationData->setTotalScaling(partID, size);
				}
			}
		}
		else if (lineType == "BILLBOARD")
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
			replace(textContent.begin(), textContent.end(), '?', ' ');

			// Create billboard
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
				_fe3d.billboardEntity_setVisible(billboardID, isVisible);
				for (const auto& ID : _fe3d.aabbEntity_getBoundIDs(billboardID, AabbParentType::BILLBOARD_ENTITY))
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
		else if (lineType == "AABB")
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

			// Create AABB
			_fe3d.aabbEntity_create(aabbID);
			_fe3d.aabbEntity_setPosition(aabbID, position);
			_fe3d.aabbEntity_setSize(aabbID, size);
			_fe3d.aabbEntity_setRaycastResponsive(aabbID, isRaycastResponsive);
			_fe3d.aabbEntity_setCollisionResponsive(aabbID, isCollisionResponsive);
			_fe3d.aabbEntity_setVisible(aabbID, isVisible);
			_loadedAabbIDs.push_back(aabbID);
		}
		else if (lineType == "SOUND")
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

			// Create sound
			if (_copyPreviewSound(soundID, previewID, position))
			{
				_fe3d.sound_setMaxVolume(soundID, maxVolume);
				_fe3d.sound_setMaxDistance(soundID, maxDistance);
				_fe3d.sound_play(soundID, -1, 0);
			}
		}
		else if (lineType == "LIGHT")
		{
			// Data placeholders
			string lightID;
			Vec3 position, radius, color;
			float intensity;

			// Extract data
			iss >>
				lightID >>
				position.x >>
				position.y >>
				position.z >>
				radius.x >>
				radius.y >>
				radius.z >>
				color.r >>
				color.g >>
				color.b >>
				intensity;

			// Create light
			_fe3d.lightEntity_setPosition(lightID, position);
			_fe3d.lightEntity_setRadius(lightID, radius);
			_fe3d.lightEntity_setColor(lightID, color);
			_fe3d.lightEntity_setIntensity(lightID, intensity);
			_loadedLightIDs.push_back(lightID);
		}
		else if (lineType == "REFLECTION")
		{
			// Data placeholders
			string reflectionID;
			Vec3 position;

			// Extract data
			iss >>
				reflectionID >>
				position.x >>
				position.y >>
				position.z;

			// Create reflection
			_fe3d.reflectionEntity_create(reflectionID);
			_fe3d.reflectionEntity_setPosition(reflectionID, position);
			_fe3d.reflectionEntity_capture(reflectionID);
			_loadedReflectionIDs.push_back(reflectionID);
		}
		else if (lineType == "LOD_DISTANCE")
		{
			// Data placeholders
			float lodDistance;

			// Extract data
			iss >> lodDistance;

			// Set distance
			_fe3d.misc_setLevelOfDetailDistance(lodDistance);
		}
		else if (lineType == "PLANAR_REFLECTION_HEIGHT")
		{
			// Data placeholders
			float reflectionHeight;

			// Extract data
			iss >> reflectionHeight;

			// Set height
			_fe3d.gfx_setPlanarReflectionHeight(reflectionHeight);
		}
		else if (lineType == "LIGHTING_AMBIENT")
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

			// Enable ambient lighting
			_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
		}
		else if (lineType == "LIGHTING_DIRECTIONAL")
		{
			// Data placeholders
			Vec3 directionalLightingPosition, directionalLightingColor;
			float directionalLightingIntensity, billboardSize;

			// Extract data
			iss >>
				directionalLightingPosition.x >>
				directionalLightingPosition.y >>
				directionalLightingPosition.z >>
				directionalLightingColor.r >>
				directionalLightingColor.g >>
				directionalLightingColor.b >>
				directionalLightingIntensity >>
				billboardSize;

			// Enable directional lighting
			_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);

			// Set lightsource billboard
			_fe3d.billboardEntity_setPosition("@@lightSource", directionalLightingPosition);
			_fe3d.billboardEntity_setSize("@@lightSource", Vec2(billboardSize));
			_fe3d.billboardEntity_setColor("@@lightSource", directionalLightingColor);
			_fe3d.billboardEntity_setVisible("@@lightSource", true);
		}
		else if (lineType == "GRAPHICS_SHADOWS")
		{
			// Data placeholders
			float size, lightness;
			Vec3 position, center;
			bool isFollowingCamera;
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
				interval;

			// Enable shadows
			_fe3d.gfx_enableShadows(position, center, size, size * 2.0f, lightness, isFollowingCamera, interval);
		}
		else if (lineType == "GRAPHICS_MOTION_BLUR")
		{
			// Data placeholders
			float strength;

			// Extract data
			iss >> strength;

			// Enable motion blur
			_fe3d.gfx_enableMotionBlur(strength);
		}
		else if (lineType == "GRAPHICS_DOF")
		{
			// Data placeholders
			bool isDynamic;
			float blurDistance, maxDistance;

			// Extract data
			iss >> isDynamic >> blurDistance >> maxDistance;

			// Enable DOF
			_fe3d.gfx_enableDOF(isDynamic, maxDistance, blurDistance);
		}
		else if (lineType == "GRAPHICS_FOG")
		{
			// Data placeholders
			float minDistance, maxDistance, thickness;
			Vec3 color;

			// Extract data
			iss >> minDistance >> maxDistance >> thickness >> color.r >> color.g >> color.b;

			// Enable fog
			_fe3d.gfx_enableFog(minDistance, maxDistance, thickness, color);
		}
		else if (lineType == "GRAPHICS_LENS_FLARE")
		{
			// Data placeholders
			string flareMapPath;
			float intensity, multiplier;

			// Extract data
			iss >> flareMapPath >> intensity >> multiplier;

			// Perform empty string & space conversions
			flareMapPath = (flareMapPath == "?") ? "" : flareMapPath;
			replace(flareMapPath.begin(), flareMapPath.end(), '?', ' ');

			// Enable lens flare
			_fe3d.gfx_enableLensFlare(flareMapPath, intensity, multiplier);
		}
		else if (lineType == "GRAPHICS_SKY_EXPOSURE")
		{
			// Data placeholders
			float intensity, speed;

			// Extract data
			iss >> intensity >> speed;

			// Enable sky exposure
			_fe3d.gfx_enableSkyExposure(intensity, speed);
		}
		else if (lineType == "GRAPHICS_BLOOM")
		{
			// Data placeholders
			unsigned int type, blurCount;
			float intensity;

			// Extract data
			iss >> type >> intensity >> blurCount;

			// Enable bloom
			_fe3d.gfx_enableBloom(BloomType(type), intensity, blurCount);
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