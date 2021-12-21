#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const bool WorldEditor::loadCustomWorldFromFile(const string& fileName)
{
	// Validate project ID
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("WorldEditor::loadCustomWorldFromFile::1");
	}
	if(_isEditorLoaded)
	{
		Logger::throwError("WorldEditor::loadCustomWorldFromFile::2");
	}

	// Compose file path
	const string filePath = (Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
							 ("projects\\" + _currentProjectID + "\\")) + "worlds\\custom\\" + fileName + ".fe3d");

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
		if(lineType == "SKY")
		{
			// Data placeholders
			string skyID, templateID;
			fvec3 color;
			float rotation, lightness;

			// Read data from file
			iss >>
				skyID >>
				templateID >>
				rotation >>
				lightness >>
				color.r >>
				color.g >>
				color.b;

			// Create sky
			if(_copyTemplateSky(skyID, templateID))
			{
				_fe3d.sky_setRotation(skyID, rotation);
				_fe3d.sky_setLightness(skyID, lightness);
				_fe3d.sky_setColor(skyID, color);
			}
		}
		else if(lineType == "TERRAIN")
		{
			// Data placeholders
			string terrainID, templateID;

			// Read data from file
			iss >> terrainID >> templateID;

			// Create terrain
			_copyTemplateTerrain(terrainID, templateID);
		}
		else if(lineType == "WATER")
		{
			// Data placeholders
			string waterID, templateID;
			fvec3 color;
			fvec2 speed;
			float transparency;

			// Read data from file
			iss >>
				waterID >>
				templateID >>
				color.r >>
				color.g >>
				color.b >>
				speed.x >>
				speed.y >>
				transparency;

			// Create water
			if(_copyTemplateWater(waterID, templateID))
			{
				_fe3d.water_setColor(waterID, color);
				_fe3d.water_setSpeed(waterID, speed);
				_fe3d.water_setTransparency(waterID, transparency);
			}
		}
		else if(lineType == "MODEL")
		{
			// Data placeholders
			string modelID, templateID;
			fvec3 position, rotation, rotationOrigin, size, color;
			float minHeight, maxHeight, transparency, lightness;
			unsigned partCount;
			bool isVisible, isFrozen, isAabbRaycastResponsive, isAabbCollisionResponsive;

			// Read ID from file
			iss >> modelID;

			// Check if level of detail entitty
			bool makeInvisible = (modelID[0] == '@');

			// Read main data from file
			iss >>
				templateID >>
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
				transparency >>
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

				// Check if template model parts changed
				if(partIDs.size() != _fe3d.model_getPartIDs(templateID).size())
				{
					Logger::throwWarning("World model parts with ID \"" + modelID + "\" differ from base model!");
					continue;
				}

				// Check if template model parts changed
				for(size_t i = 0; i < partIDs.size(); i++)
				{
					if(partIDs[i] != _fe3d.model_getPartIDs(templateID)[i])
					{
						Logger::throwWarning("World model parts with ID \"" + modelID + "\" differ from base model!");
						continue;
					}
				}
			}

			// Create model
			if(_copyTemplateModel(modelID, templateID, position, false))
			{
				// Check if template model instancing changed
				if(_fe3d.model_isExisting(templateID))
				{
					if(_fe3d.model_isInstanced(modelID) != _fe3d.model_isInstanced(templateID))
					{
						Logger::throwWarning("Model instancing with ID \"" + modelID + "\" differs from base model!");
						_fe3d.model_delete(modelID);
						continue;
					}
				}

				// Set properties
				_fe3d.model_setBaseRotation(modelID, rotation);
				_fe3d.model_setBaseRotationOrigin(modelID, rotationOrigin);
				_fe3d.model_setBaseSize(modelID, size);
				_fe3d.model_setFrozen(modelID, isFrozen);
				_fe3d.model_setColor(modelID, "", color);
				_fe3d.model_setMinHeight(modelID, minHeight);
				_fe3d.model_setMaxHeight(modelID, maxHeight);
				//_fe3d.model_setTransparency(modelID, transparency);
				//_fe3d.model_setLightness(modelID, lightness);
				_fe3d.model_setVisible(modelID, isVisible);
				for(const auto& ID : _fe3d.aabb_getChildIDs(modelID, AabbParentEntityType::MODEL))
				{
					_fe3d.aabb_setRaycastResponsive(ID, isAabbRaycastResponsive);
					_fe3d.aabb_setCollisionResponsive(ID, isAabbCollisionResponsive);
				}

				// Iterate through model parts
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
					_fe3d.model_setPartPosition(modelID, partID, position);
					_fe3d.model_setPartRotation(modelID, partID, rotation);
					_fe3d.model_setPartRotationOrigin(modelID, partID, rotationOrigin);
					_fe3d.model_setPartSize(modelID, partID, size);
				}

				// Read offset data from file
				if(_fe3d.model_isInstanced(modelID))
				{
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
		else if(lineType == "ANIMATION3D")
		{
			// Data placeholders
			string animationID, modelID;
			float speed;
			int remainingLoops;
			unsigned int frameIndex, fadeFramestep;
			bool isPaused;

			// Read main data from file
			iss >>
				animationID >>
				modelID >>
				isPaused >>
				frameIndex >>
				speed >>
				remainingLoops >>
				fadeFramestep;

			// Read speed data from file
			map<string, fvec3> speeds;
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
					fvec3 speed;
					iss >> speed.x >> speed.y >> speed.z;
					speeds[partID] = speed;
				}
			}

			// Start animation3D
			_animation3dEditor.startModelAnimation(animationID, modelID, remainingLoops);

			// Check if animation exists
			//if(_animation3dEditor.isAnimationExisting(animationID))
			//{
			//	// Retrieve raw animation data for editing
			//	string errorMessage = "Tried to retrieve animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";
			//	auto animationData = _animation3dEditor.getAnimationData(animationID, modelID, errorMessage);
			//	auto frameData = animationData->getFrames()[frameIndex];

			//	// Set properties
			//	isPaused ? _animation3dEditor.pauseModelAnimation(animationID, modelID) : void();
			//	animationData->setSpeedMultiplier(speedMultiplier);
			//	animationData->setFadeFramestep(fadeFramestep);
			//	animationData->setFrameIndex(frameIndex);
			//	for(const auto& [partID, speed] : speeds)
			//	{
			//		frameData.setSpeed(partID, speed);
			//	}

			//	// Retrieve parts
			//	auto partIDs = _fe3d.model_getPartIDs(modelID);
			//	for(const auto& partID : partIDs)
			//	{
			//		// Retrieve part transformation
			//		auto position = _fe3d.model_getPartPosition(modelID, partID);
			//		auto rotation = _fe3d.model_getPartRotation(modelID, partID);
			//		auto size = _fe3d.model_getPartSize(modelID, partID);

			//		// Set properties
			//		animationData->setTotalMovement(partID, position);
			//		animationData->setTotalRotation(partID, rotation);
			//		animationData->setTotalScaling(partID, size);
			//	}
			//}
		}
		else if(lineType == "BILLBOARD")
		{
			// Data placeholders
			string billboardID, templateID, textContent;
			fvec3 position, rotation, color;
			fvec2 size;
			float lightness, minHeight, maxHeight;
			int remainingAnimationLoops;
			unsigned int animationRowIndex, animationColumnIndex;
			bool isVisible, isAabbRaycastResponsive, isAabbCollisionResponsive, isFacingX, isFacingY, isAnimationPlaying, isAnimationPaused;

			// Read data from file
			iss >>
				billboardID >>
				templateID >>
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

			// Convert empty string
			textContent = (textContent == "?") ? "" : textContent;

			// Convert spaces
			replace(textContent.begin(), textContent.end(), '?', ' ');

			// Create billboard
			if(_copyTemplateBillboard(billboardID, templateID, position, false))
			{
				// Set properties
				_fe3d.billboard_setRotation(billboardID, rotation);
				_fe3d.billboard_setSize(billboardID, size);
				_fe3d.billboard_setFacingCameraX(billboardID, isFacingX);
				_fe3d.billboard_setFacingCameraY(billboardID, isFacingY);
				_fe3d.billboard_setColor(billboardID, color);
				_fe3d.billboard_setTextContent(billboardID, textContent);
				_fe3d.billboard_setLightness(billboardID, lightness);
				_fe3d.billboard_setMinHeight(billboardID, minHeight);
				_fe3d.billboard_setMaxHeight(billboardID, maxHeight);
				_fe3d.billboard_setVisible(billboardID, isVisible);
				for(const auto& ID : _fe3d.aabb_getChildIDs(billboardID, AabbParentEntityType::BILLBOARD))
				{
					_fe3d.aabb_setRaycastResponsive(ID, isAabbRaycastResponsive);
					_fe3d.aabb_setCollisionResponsive(ID, isAabbCollisionResponsive);
				}
			}
		}
		else if(lineType == "AABB")
		{
			// Data placeholders
			string aabbID;
			fvec3 position, size;
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
			_fe3d.aabb_create(aabbID);
			_fe3d.aabb_setBasePosition(aabbID, position);
			_fe3d.aabb_setBaseSize(aabbID, size);
			_fe3d.aabb_setRaycastResponsive(aabbID, isRaycastResponsive);
			_fe3d.aabb_setCollisionResponsive(aabbID, isCollisionResponsive);
			_fe3d.aabb_setVisible(aabbID, isVisible);
			_loadedAabbIDs.push_back(aabbID);
		}
		else if(lineType == "SOUND")
		{
			// Data placeholders
			string soundID, templateID;
			fvec3 position;
			float maxVolume, maxDistance;

			// Read data from file
			iss >>
				soundID >>
				templateID >>
				position.x >>
				position.y >>
				position.z >>
				maxVolume >>
				maxDistance;

			// Create sound
			if(_copyTemplateSound(soundID, templateID, position, false))
			{
				_fe3d.sound3d_setMaxVolume(soundID, maxVolume);
				_fe3d.sound3d_setMaxDistance(soundID, maxDistance);
				_fe3d.sound3d_start(soundID, -1, 0, false);
			}
		}
		else if(lineType == "POINTLIGHT")
		{
			// Data placeholders
			string pointlightID;
			fvec3 position, radius, color;
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
			_fe3d.pointlight_setPosition(pointlightID, position);
			_fe3d.pointlight_setRadius(pointlightID, radius);
			_fe3d.pointlight_setColor(pointlightID, color);
			_fe3d.pointlight_setIntensity(pointlightID, intensity);
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

			// Create spotlight
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

			// Create reflection
			_fe3d.reflection_create(reflectionID);
			_fe3d.reflection_setPosition(reflectionID, position);
			_fe3d.reflection_capture(reflectionID);
			_loadedReflectionIDs.push_back(reflectionID);
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
			_fe3d.gfx_setShadowSize(size);
			_fe3d.gfx_setShadowReach(size * 2.0f);
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
			Logger::throwError("WorldEditor::loadCustomWorldFromFile::3");
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