#include "scene_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const bool SceneEditor::loadCustomSceneFromFile(const string& fileName)
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("SceneEditor::loadCustomSceneFromFile::1");
	}
	if(_isEditorLoaded)
	{
		Logger::throwError("SceneEditor::loadCustomSceneFromFile::2");
	}

	// Compose file path
	const string filePath = (Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
							 ("game\\" + _currentProjectID)) + "\\scenes\\custom\\" + fileName + ".fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Cannot load scene with ID \"" + fileName + "\"!");
		return false;
	}

	// Load scene file
	ifstream file(filePath);

	// Read scene data
	string line;
	while(getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Read type from file
		string lineType;
		iss >> lineType;

		// Determine line type
		if(lineType == "SKY")
		{
			// Data placeholders
			string skyID, previewID;
			Vec3 color;
			float rotationSpeed, lightness;

			// Read data from file
			iss >>
				skyID >>
				previewID >>
				rotationSpeed >>
				lightness >>
				color.r >>
				color.g >>
				color.b;

			// Create sky
			if(_copyPreviewSky(skyID, previewID))
			{
				_fe3d.skyEntity_setRotationSpeed(skyID, rotationSpeed);
				_fe3d.skyEntity_setLightness(skyID, lightness);
				_fe3d.skyEntity_setColor(skyID, color);
			}
		}
		else if(lineType == "TERRAIN")
		{
			// Data placeholders
			string terrainID, previewID;

			// Read data from file
			iss >> terrainID >> previewID;

			// Create terrain
			_copyPreviewTerrain(terrainID, previewID);
		}
		else if(lineType == "WATER")
		{
			// Data placeholders
			string waterID, previewID;
			Vec3 color;
			Vec2 speed;
			float transparency;

			// Read data from file
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
			if(_copyPreviewWater(waterID, previewID))
			{
				_fe3d.waterEntity_setColor(waterID, color);
				_fe3d.waterEntity_setSpeed(waterID, speed);
				_fe3d.waterEntity_setTransparency(waterID, transparency);
			}
		}
		else if(lineType == "MODEL")
		{
			// Data placeholders
			string modelID, previewID;
			Vec3 position, rotation, rotationOrigin, size, color;
			float minHeight, maxHeight, alpha, lightness;
			unsigned partCount;
			bool isVisible, isFrozen, isAabbRaycastResponsive, isAabbCollisionResponsive;

			// Read ID from file
			iss >> modelID;

			// Check if LOD entitty
			bool makeInvisible = (modelID[0] == '@');

			// Read main data from file
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
			if(partCount > 1)
			{
				// Read model part IDs
				vector<string> partIDs;
				for(unsigned int i = 0; i < partCount; i++)
				{
					string partID;
					iss >> partID;
					partIDs.push_back(partID);
				}

				// Check if preview model parts count
				if(partIDs.size() != _fe3d.modelEntity_getPartIDs(previewID).size())
				{
					Logger::throwWarning("Scene model parts with ID \"" + modelID + "\" differ from base model!");
					continue;
				}

				// Check if preview model parts changed
				for(size_t i = 0; i < partIDs.size(); i++)
				{
					if(partIDs[i] != _fe3d.modelEntity_getPartIDs(previewID)[i])
					{
						Logger::throwWarning("Scene model parts with ID \"" + modelID + "\" differ from base model!");
						continue;
					}
				}
			}

			// Create model
			if(_copyPreviewModel(modelID, previewID, position, false))
			{
				// Check if preview model instancing changed
				if(_fe3d.modelEntity_isExisting(previewID))
				{
					if(_fe3d.modelEntity_isInstanced(modelID) != _fe3d.modelEntity_isInstanced(previewID))
					{
						Logger::throwWarning("Model instancing with ID \"" + modelID + "\" differs from base model!");
						_fe3d.modelEntity_delete(modelID);
						continue;
					}
				}

				// Set properties
				_fe3d.modelEntity_setBaseRotation(modelID, rotation);
				_fe3d.modelEntity_setBaseRotationOrigin(modelID, rotationOrigin);
				_fe3d.modelEntity_setBaseSize(modelID, size);
				_fe3d.modelEntity_setStaticToCamera(modelID, isFrozen);
				_fe3d.modelEntity_setColor(modelID, "", color);
				_fe3d.modelEntity_setMinHeight(modelID, minHeight);
				_fe3d.modelEntity_setMaxHeight(modelID, maxHeight);
				//_fe3d.modelEntity_setAlpha(modelID, alpha);
				//_fe3d.modelEntity_setLightness(modelID, lightness);
				_fe3d.modelEntity_setVisible(modelID, isVisible);
				for(const auto& ID : _fe3d.aabbEntity_getChildIDs(modelID, AabbParentType::MODEL_ENTITY))
				{
					_fe3d.aabbEntity_setRaycastResponsive(ID, isAabbRaycastResponsive);
					_fe3d.aabbEntity_setCollisionResponsive(ID, isAabbCollisionResponsive);
				}

				// For every part
				for(unsigned int i = 0; i < partCount; i++)
				{
					// Read transformation data from file
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
					_fe3d.modelEntity_setPartPosition(modelID, partID, position);
					_fe3d.modelEntity_setPartRotation(modelID, partID, rotation);
					_fe3d.modelEntity_setPartRotationOrigin(modelID, partID, rotationOrigin);
					_fe3d.modelEntity_setPartSize(modelID, partID, size);
				}

				// Read offset data from file
				if(_fe3d.modelEntity_isInstanced(modelID))
				{
					vector<Vec3> instancedOffsets;
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
				if(makeInvisible)
				{
					_fe3d.modelEntity_setVisible(modelID, false);
				}
			}
		}
		else if(lineType == "ANIMATION")
		{
			// Data placeholders
			string animationID, modelID;
			float speedMultiplier;
			int remainingLoops, fadeFramestep;
			unsigned int frameIndex;
			bool isPaused;

			// Read main data from file
			iss >>
				animationID >>
				modelID >>
				isPaused >>
				frameIndex >>
				speedMultiplier >>
				remainingLoops >>
				fadeFramestep;

			// Read speed data from file
			map<string, Vec3> speeds;
			while(true)
			{
				// Check if file has speed data left
				string nextElement;
				iss >> nextElement;

				// Check for end of line
				if(nextElement.empty())
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
			if(_animationEditor.isAnimationExisting(animationID))
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
				for(const auto& [partID, speed] : speeds)
				{
					frameData.setSpeed(partID, speed);
				}

				// Retrieve parts
				auto partIDs = _fe3d.modelEntity_getPartIDs(modelID);
				for(const auto& partID : partIDs)
				{
					// Retrieve part transformation
					auto position = _fe3d.modelEntity_getPartPosition(modelID, partID);
					auto rotation = _fe3d.modelEntity_getPartRotation(modelID, partID);
					auto size = _fe3d.modelEntity_getPartSize(modelID, partID);

					// Set properties
					animationData->setTotalMovement(partID, position);
					animationData->setTotalRotation(partID, rotation);
					animationData->setTotalScaling(partID, size);
				}
			}
		}
		else if(lineType == "BILLBOARD")
		{
			// Data placeholders
			string billboardID, previewID, textContent;
			Vec3 position, rotation, color;
			Vec2 size;
			float lightness, minHeight, maxHeight;
			int remainingAnimationLoops;
			unsigned int animationRowIndex, animationColumnIndex;
			bool isVisible, isAabbRaycastResponsive, isAabbCollisionResponsive, isFacingX, isFacingY, isAnimationPlaying, isAnimationPaused;

			// Read data from file
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
			if(_copyPreviewBillboard(billboardID, previewID, position, false))
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
				for(const auto& ID : _fe3d.aabbEntity_getChildIDs(billboardID, AabbParentType::BILLBOARD_ENTITY))
				{
					_fe3d.aabbEntity_setRaycastResponsive(ID, isAabbRaycastResponsive);
					_fe3d.aabbEntity_setCollisionResponsive(ID, isAabbCollisionResponsive);
				}

				// Set animation progresss
				if(isAnimationPlaying)
				{
					// Play
					_fe3d.billboardEntity_stopSpriteAnimation(billboardID);
					_fe3d.billboardEntity_startSpriteAnimation(billboardID, remainingAnimationLoops);

					// Pause
					if(isAnimationPaused)
					{
						_fe3d.billboardEntity_pauseSpriteAnimation(billboardID);
					}

					// Progress
					_fe3d.billboardEntity_setSpriteAnimationRowIndex(billboardID, animationRowIndex);
					_fe3d.billboardEntity_setSpriteAnimationColumnIndex(billboardID, animationColumnIndex);
				}
			}
		}
		else if(lineType == "AABB")
		{
			// Data placeholders
			string aabbID;
			Vec3 position, size;
			bool isVisible, isRaycastResponsive, isCollisionResponsive;

			// Read data from file
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
			_fe3d.aabbEntity_setBasePosition(aabbID, position);
			_fe3d.aabbEntity_setBaseSize(aabbID, size);
			_fe3d.aabbEntity_setRaycastResponsive(aabbID, isRaycastResponsive);
			_fe3d.aabbEntity_setCollisionResponsive(aabbID, isCollisionResponsive);
			_fe3d.aabbEntity_setVisible(aabbID, isVisible);
			_loadedAabbIDs.push_back(aabbID);
		}
		else if(lineType == "SOUND")
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

			// Create sound
			if(_copyPreviewSound(soundID, previewID, position, false))
			{
				_fe3d.sound_setMaxVolume(soundID, maxVolume);
				_fe3d.sound_setMaxDistance(soundID, maxDistance);
				_fe3d.sound_play(soundID, -1, 0, false);
			}
		}
		else if(lineType == "POINTLIGHT")
		{
			// Data placeholders
			string pointlightID;
			Vec3 position, radius, color;
			float intensity;

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
				intensity;

			// Create pointlight
			_fe3d.pointlightEntity_setPosition(pointlightID, position);
			_fe3d.pointlightEntity_setRadius(pointlightID, radius);
			_fe3d.pointlightEntity_setColor(pointlightID, color);
			_fe3d.pointlightEntity_setIntensity(pointlightID, intensity);
			_loadedPointlightIDs.push_back(pointlightID);
		}
		else if(lineType == "SPOTLIGHT")
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

			// Create spotlight
			_fe3d.spotlightEntity_setPosition(spotlightID, position);
			_fe3d.spotlightEntity_setColor(spotlightID, color);
			_fe3d.spotlightEntity_setYaw(spotlightID, yaw);
			_fe3d.spotlightEntity_setPitch(spotlightID, pitch);
			_fe3d.spotlightEntity_setIntensity(spotlightID, intensity);
			_fe3d.spotlightEntity_setAngle(spotlightID, angle);
			_fe3d.spotlightEntity_setDistance(spotlightID, distance);
			_loadedSpotlightIDs.push_back(spotlightID);
		}
		else if(lineType == "REFLECTION")
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

			// Create reflection
			_fe3d.reflectionEntity_create(reflectionID);
			_fe3d.reflectionEntity_setPosition(reflectionID, position);
			_fe3d.reflectionEntity_capture(reflectionID);
			_loadedReflectionIDs.push_back(reflectionID);
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
		else if(lineType == "LIGHTING_DIRECTIONAL")
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
		else if(lineType == "GRAPHICS_SHADOWS")
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
		else if(lineType == "GRAPHICS_LENS_FLARE")
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
			Logger::throwError("SceneEditor::loadCustomSceneFromFile::3");
		}
	}

	// Close file
	file.close();

	// Set new scene ID
	_loadedSceneID = fileName;

	// Logging
	Logger::throwInfo("Scene data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}