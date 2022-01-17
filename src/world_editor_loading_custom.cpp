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
	//if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	//{
	//	Logger::throwError("WorldEditor::loadCustomWorldFromFile::1");
	//}
	//if(_isEditorLoaded)
	//{
	//	Logger::throwError("WorldEditor::loadCustomWorldFromFile::2");
	//}

	//const auto rootPath = Tools::getRootDirectoryPath();
	//const auto filePath = (rootPath + (Config::getInst().isApplicationExported() ? "" :
	//					   ("projects\\" + _currentProjectID + "\\")) + "worlds\\custom\\" + fileName + ".fe3d");

	//auto file = ifstream(filePath);
	//if(!file)
	//{
	//	Logger::throwWarning("Cannot load world with ID \"" + fileName + "\"!");
	//	return false;
	//}

	//string line;
	//while(getline(file, line))
	//{
	//	istringstream iss(line);

	//	string lineType;
	//	iss >> lineType;

	//	if(lineType == "SKY")
	//	{
	//		string skyID, templateID;
	//		fvec3 color;
	//		float rotation, lightness;

	//		iss >>
	//			skyID >>
	//			templateID >>
	//			rotation >>
	//			lightness >>
	//			color.r >>
	//			color.g >>
	//			color.b;

	//		if(_copyTemplateSky(skyID, templateID))
	//		{
	//			_fe3d->sky_setRotation(skyID, rotation);
	//			_fe3d->sky_setLightness(skyID, lightness);
	//			_fe3d->sky_setColor(skyID, color);
	//		}
	//	}
	//	else if(lineType == "TERRAIN")
	//	{
	//		string terrainID, templateID;

	//		iss >> terrainID >> templateID;

	//		_copyTemplateTerrain(terrainID, templateID);
	//	}
	//	else if(lineType == "WATER")
	//	{
	//		string waterID, templateID;
	//		fvec3 color;
	//		fvec2 speed;
	//		float transparency;

	//		iss >>
	//			waterID >>
	//			templateID >>
	//			color.r >>
	//			color.g >>
	//			color.b >>
	//			speed.x >>
	//			speed.y >>
	//			transparency;

	//		if(_copyTemplateWater(waterID, templateID))
	//		{
	//			_fe3d->water_setColor(waterID, color);
	//			_fe3d->water_setSpeed(waterID, speed);
	//			_fe3d->water_setTransparency(waterID, transparency);
	//		}
	//	}
	//	else if(lineType == "MODEL")
	//	{
	//		string modelID, templateID;
	//		fvec3 position, rotation, rotationOrigin, size, color;
	//		float minHeight, maxHeight, transparency, lightness;
	//		unsigned partCount;
	//		bool isVisible, isFrozen, isAabbRaycastResponsive, isAabbCollisionResponsive;

	//		iss >> modelID;

	//		bool makeInvisible = (modelID[0] == '@');

	//		iss >>
	//			templateID >>
	//			isVisible >>
	//			isFrozen >>
	//			isAabbRaycastResponsive >>
	//			isAabbCollisionResponsive >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			rotation.x >>
	//			rotation.y >>
	//			rotation.z >>
	//			rotationOrigin.x >>
	//			rotationOrigin.y >>
	//			rotationOrigin.z >>
	//			size.x >>
	//			size.y >>
	//			size.z >>
	//			color.r >>
	//			color.g >>
	//			color.b >>
	//			minHeight >>
	//			maxHeight >>
	//			transparency >>
	//			lightness >>
	//			partCount;

	//		if(partCount > 1)
	//		{
	//			vector<string> partIDs;
	//			for(unsigned int i = 0; i < partCount; i++)
	//			{
	//				string partID;
	//				iss >> partID;
	//				partIDs.push_back(partID);
	//			}

	//			if(partIDs.size() != _fe3d->model_getPartIDs(templateID).size())
	//			{
	//				Logger::throwWarning("World model parts with ID \"" + modelID + "\" differ from base model!");
	//				continue;
	//			}

	//			for(size_t i = 0; i < partIDs.size(); i++)
	//			{
	//				if(partIDs[i] != _fe3d->model_getPartIDs(templateID)[i])
	//				{
	//					Logger::throwWarning("World model parts with ID \"" + modelID + "\" differ from base model!");
	//					continue;
	//				}
	//			}
	//		}

	//		if(_copyTemplateModel(modelID, templateID, position, false))
	//		{
	//			_fe3d->model_setBaseRotation(modelID, rotation);
	//			_fe3d->model_setBaseRotationOrigin(modelID, rotationOrigin);
	//			_fe3d->model_setBaseSize(modelID, size);
	//			_fe3d->model_setFrozen(modelID, isFrozen);
	//			_fe3d->model_setColor(modelID, "", color);
	//			_fe3d->model_setMinHeight(modelID, minHeight);
	//			_fe3d->model_setMaxHeight(modelID, maxHeight);
	//			//_fe3d->model_setTransparency(modelID, transparency);
	//			//_fe3d->model_setLightness(modelID, lightness);
	//			_fe3d->model_setVisible(modelID, isVisible);
	//			for(const auto& ID : _fe3d->aabb_getChildIDs(modelID, AabbParentEntityType::MODEL))
	//			{
	//				_fe3d->aabb_setRaycastResponsive(ID, isAabbRaycastResponsive);
	//				_fe3d->aabb_setCollisionResponsive(ID, isAabbCollisionResponsive);
	//			}

	//			for(unsigned int i = 0; i < partCount; i++)
	//			{
	//				string partID;
	//				iss >>
	//					partID >>
	//					position.x >>
	//					position.y >>
	//					position.z >>
	//					rotation.x >>
	//					rotation.y >>
	//					rotation.z >>
	//					rotationOrigin.x >>
	//					rotationOrigin.y >>
	//					rotationOrigin.z >>
	//					size.x >>
	//					size.y >>
	//					size.z;

	//				_fe3d->model_setPartPosition(modelID, partID, position);
	//				_fe3d->model_setPartRotation(modelID, partID, rotation);
	//				_fe3d->model_setPartRotationOrigin(modelID, partID, rotationOrigin);
	//				_fe3d->model_setPartSize(modelID, partID, size);
	//			}

	//			if(makeInvisible)
	//			{
	//				_fe3d->model_setVisible(modelID, false);
	//			}
	//		}
	//	}
	//	else if(lineType == "ANIMATION3D")
	//	{
	//		string animationID, modelID;
	//		float speed;
	//		int remainingLoops;
	//		unsigned int frameIndex, fadeFramestep;
	//		bool isPaused;

	//		iss >>
	//			animationID >>
	//			modelID >>
	//			isPaused >>
	//			frameIndex >>
	//			speed >>
	//			remainingLoops >>
	//			fadeFramestep;

	//		map<string, fvec3> speeds;
	//		while(true)
	//		{
	//			string nextElement;
	//			iss >> nextElement;

	//			if(nextElement.empty())
	//			{
	//				break;
	//			}
	//			else
	//			{
	//				string partID = (nextElement == "?") ? "" : nextElement;
	//				fvec3 speed;
	//				iss >> speed.x >> speed.y >> speed.z;
	//				speeds[partID] = speed;
	//			}
	//		}

	//		_animation3dEditor->startModelAnimation(animationID, modelID, remainingLoops);

	//		//if(_animation3dEditor->isAnimationExisting(animationID))
	//		//{
	//		//	// Retrieve raw animation data for editing
	//		//	string errorMessage = "Tried to retrieve animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";
	//		//	auto animationData = _animation3dEditor->getAnimationData(animationID, modelID, errorMessage);
	//		//	auto frameData = animationData->getFrames()[frameIndex];

	//		//	// Set properties
	//		//	isPaused ? _animation3dEditor->pauseModelAnimation(animationID, modelID) : void();
	//		//	animationData->setSpeedMultiplier(speedMultiplier);
	//		//	animationData->setFadeFramestep(fadeFramestep);
	//		//	animationData->setFrameIndex(frameIndex);
	//		//	for(const auto& [key, speed] : speeds)
	//		//	{
	//		//		frameData.setSpeed(partID, speed);
	//		//	}

	//		//	// Retrieve parts
	//		//	auto partIDs = _fe3d->model_getPartIDs(modelID);
	//		//	for(const auto& partID : partIDs)
	//		//	{
	//		//		// Retrieve part transformation
	//		//		auto position = _fe3d->model_getPartPosition(modelID, partID);
	//		//		auto rotation = _fe3d->model_getPartRotation(modelID, partID);
	//		//		auto size = _fe3d->model_getPartSize(modelID, partID);

	//		//		// Set properties
	//		//		animationData->setTotalMovement(partID, position);
	//		//		animationData->setTotalRotation(partID, rotation);
	//		//		animationData->setTotalScaling(partID, size);
	//		//	}
	//		//}
	//	}
	//	else if(lineType == "QUAD3D")
	//	{
	//		string quadID, templateID, textContent;
	//		fvec3 position, rotation, color;
	//		fvec2 size;
	//		float lightness, minHeight, maxHeight;
	//		int remainingAnimationLoops;
	//		unsigned int animationRowIndex, animationColumnIndex;
	//		bool isVisible, isAabbRaycastResponsive, isAabbCollisionResponsive, isFacingX, isFacingY, isAnimationPlaying, isAnimationPaused;

	//		iss >>
	//			quadID >>
	//			templateID >>
	//			isVisible >>
	//			isAabbRaycastResponsive >>
	//			isAabbCollisionResponsive >>
	//			isFacingX >>
	//			isFacingY >>
	//			isAnimationPlaying >>
	//			isAnimationPaused >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			rotation.x >>
	//			rotation.y >>
	//			rotation.z >>
	//			size.x >>
	//			size.y >>
	//			color.r >>
	//			color.g >>
	//			color.b >>
	//			textContent >>
	//			lightness >>
	//			minHeight >>
	//			maxHeight >>
	//			remainingAnimationLoops >>
	//			animationRowIndex >>
	//			animationColumnIndex;

	//		textContent = (textContent == "?") ? "" : textContent;

	//		replace(textContent.begin(), textContent.end(), '?', ' ');

	//		if(_copyTemplateQuad3d(quadID, templateID, position, false))
	//		{
	//			_fe3d->quad3d_setRotation(quadID, rotation);
	//			_fe3d->quad3d_setSize(quadID, size);
	//			_fe3d->quad3d_setFacingCameraX(quadID, isFacingX);
	//			_fe3d->quad3d_setFacingCameraY(quadID, isFacingY);
	//			_fe3d->quad3d_setColor(quadID, color);
	//			//_fe3d->quad3d_setTextContent(quadID, textContent);
	//			_fe3d->quad3d_setLightness(quadID, lightness);
	//			_fe3d->quad3d_setMinHeight(quadID, minHeight);
	//			_fe3d->quad3d_setMaxHeight(quadID, maxHeight);
	//			_fe3d->quad3d_setVisible(quadID, isVisible);
	//			for(const auto& ID : _fe3d->aabb_getChildIDs(quadID, AabbParentEntityType::QUAD3D))
	//			{
	//				_fe3d->aabb_setRaycastResponsive(ID, isAabbRaycastResponsive);
	//				_fe3d->aabb_setCollisionResponsive(ID, isAabbCollisionResponsive);
	//			}
	//		}
	//	}
	//	else if(lineType == "AABB")
	//	{
	//		string aabbID;
	//		fvec3 position, size;
	//		bool isVisible, isRaycastResponsive, isCollisionResponsive;

	//		iss >>
	//			aabbID >>
	//			isVisible >>
	//			isRaycastResponsive >>
	//			isCollisionResponsive >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			size.x >>
	//			size.y >>
	//			size.z;

	//		_fe3d->aabb_create(aabbID, false);
	//		_fe3d->aabb_setBasePosition(aabbID, position);
	//		_fe3d->aabb_setBaseSize(aabbID, size);
	//		_fe3d->aabb_setRaycastResponsive(aabbID, isRaycastResponsive);
	//		_fe3d->aabb_setCollisionResponsive(aabbID, isCollisionResponsive);
	//		_fe3d->aabb_setVisible(aabbID, isVisible);
	//		_loadedAabbIDs.push_back(aabbID);
	//	}
	//	else if(lineType == "SOUND")
	//	{
	//		string soundID, templateID;
	//		fvec3 position;
	//		float maxVolume, maxDistance;

	//		iss >>
	//			soundID >>
	//			templateID >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			maxVolume >>
	//			maxDistance;

	//		if(_copyTemplateSound(soundID, templateID, position, false))
	//		{
	//			_fe3d->sound3d_setMaxVolume(soundID, maxVolume);
	//			_fe3d->sound3d_setMaxDistance(soundID, maxDistance);
	//			_fe3d->sound3d_start(soundID, -1, 0, false);
	//		}
	//	}
	//	else if(lineType == "POINTLIGHT")
	//	{
	//		string pointlightID;
	//		fvec3 position, radius, color;
	//		float intensity;

	//		iss >>
	//			pointlightID >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			radius.x >>
	//			radius.y >>
	//			radius.z >>
	//			color.r >>
	//			color.g >>
	//			color.b >>
	//			intensity;

	//		_fe3d->pointlight_setPosition(pointlightID, position);
	//		_fe3d->pointlight_setRadius(pointlightID, radius);
	//		_fe3d->pointlight_setColor(pointlightID, color);
	//		_fe3d->pointlight_setIntensity(pointlightID, intensity);
	//		_loadedPointlightIDs.push_back(pointlightID);
	//	}
	//	else if(lineType == "SPOTLIGHT")
	//	{
	//		string spotlightID;
	//		fvec3 position, color;
	//		float yaw, pitch, intensity, angle, distance;

	//		iss >>
	//			spotlightID >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			color.r >>
	//			color.g >>
	//			color.b >>
	//			yaw >>
	//			pitch >>
	//			intensity >>
	//			angle >>
	//			distance;

	//		_fe3d->spotlight_setPosition(spotlightID, position);
	//		_fe3d->spotlight_setColor(spotlightID, color);
	//		_fe3d->spotlight_setYaw(spotlightID, yaw);
	//		_fe3d->spotlight_setPitch(spotlightID, pitch);
	//		_fe3d->spotlight_setIntensity(spotlightID, intensity);
	//		_fe3d->spotlight_setAngle(spotlightID, angle);
	//		_fe3d->spotlight_setDistance(spotlightID, distance);
	//		_loadedSpotlightIDs.push_back(spotlightID);
	//	}
	//	else if(lineType == "REFLECTION")
	//	{
	//		string reflectionID;
	//		fvec3 position;

	//		iss >>
	//			reflectionID >>
	//			position.x >>
	//			position.y >>
	//			position.z;

	//		_fe3d->reflection_create(reflectionID);
	//		_fe3d->reflection_setPosition(reflectionID, position);
	//		_fe3d->reflection_capture(reflectionID);
	//		_loadedReflectionIDs.push_back(reflectionID);
	//	}
	//	else if(lineType == "LIGHTING_AMBIENT")
	//	{
	//		fvec3 color;
	//		float intensity;

	//		iss >>
	//			color.r >>
	//			color.g >>
	//			color.b >>
	//			intensity;

	//		_fe3d->gfx_enableAmbientLighting();
	//		_fe3d->gfx_setAmbientLightingColor(color);
	//		_fe3d->gfx_setAmbientLightingIntensity(intensity);
	//	}
	//	else if(lineType == "LIGHTING_DIRECTIONAL")
	//	{
	//		fvec3 position, color;
	//		float intensity, quad3dSize;

	//		iss >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			color.r >>
	//			color.g >>
	//			color.b >>
	//			intensity >>
	//			quad3dSize;

	//		_fe3d->gfx_enableDirectionalLighting();
	//		_fe3d->gfx_setDirectionalLightingPosition(position);
	//		_fe3d->gfx_setDirectionalLightingIntensity(intensity);
	//		_fe3d->gfx_setDirectionalLightingColor(color);
	//	}
	//	else if(lineType == "GRAPHICS_SHADOWS")
	//	{
	//		float size, lightness;
	//		fvec3 position, center;
	//		bool isFollowingCamera;
	//		int interval;

	//		iss >>
	//			size >>
	//			lightness >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			center.x >>
	//			center.y >>
	//			center.z >>
	//			isFollowingCamera >>
	//			interval;

	//		_fe3d->gfx_enableShadows();
	//		_fe3d->gfx_setShadowEyePosition(position);
	//		_fe3d->gfx_setShadowCenterPosition(center);
	//		_fe3d->gfx_setShadowSize(size);
	//		_fe3d->gfx_setShadowReach(size * 2.0f);
	//		_fe3d->gfx_setShadowLightness(lightness);
	//		_fe3d->gfx_setShadowFollowingCamera(isFollowingCamera);
	//		_fe3d->gfx_setShadowInterval(interval);
	//	}
	//	else if(lineType == "GRAPHICS_MOTION_BLUR")
	//	{
	//		float strength;

	//		iss >> strength;

	//		_fe3d->gfx_enableMotionBlur();
	//		_fe3d->gfx_setMotionBlurStrength(strength);
	//	}
	//	else if(lineType == "GRAPHICS_DOF")
	//	{
	//		bool isDynamic;
	//		float blurDistance, maxDistance;

	//		iss >> isDynamic >> blurDistance >> maxDistance;

	//		_fe3d->gfx_enableDOF();
	//		_fe3d->gfx_setDofDynamic(isDynamic);
	//		_fe3d->gfx_setDofDynamicDistance(maxDistance);
	//		_fe3d->gfx_setDofBlurDistance(blurDistance);
	//	}
	//	else if(lineType == "GRAPHICS_FOG")
	//	{
	//		float minDistance, maxDistance, thickness;
	//		fvec3 color;

	//		iss >> minDistance >> maxDistance >> thickness >> color.r >> color.g >> color.b;

	//		_fe3d->gfx_enableFog();
	//		_fe3d->gfx_setFogMinDistance(minDistance);
	//		_fe3d->gfx_setFogMaxDistance(maxDistance);
	//		_fe3d->gfx_setFogThickness(thickness);
	//		_fe3d->gfx_setFogColor(color);
	//	}
	//	else if(lineType == "GRAPHICS_LENS_FLARE")
	//	{
	//		string flareMapPath;
	//		float intensity, sensitivity;

	//		iss >> flareMapPath >> intensity >> sensitivity;

	//		flareMapPath = (flareMapPath == "?") ? "" : flareMapPath;

	//		replace(flareMapPath.begin(), flareMapPath.end(), '?', ' ');

	//		_fe3d->gfx_enableLensFlare();
	//		_fe3d->gfx_setLensFlareMap(flareMapPath);
	//		_fe3d->gfx_setLensFlareIntensity(intensity);
	//		_fe3d->gfx_setLensFlareSensitivity(sensitivity);
	//	}
	//	else if(lineType == "GRAPHICS_SKY_EXPOSURE")
	//	{
	//		float intensity, speed;

	//		iss >> intensity >> speed;

	//		_fe3d->gfx_enableSkyExposure();
	//		_fe3d->gfx_setSkyExposureIntensity(intensity);
	//		_fe3d->gfx_setSkyExposureSpeed(speed);
	//	}
	//	else if(lineType == "GRAPHICS_BLOOM")
	//	{
	//		unsigned int type, blurCount;
	//		float intensity;

	//		iss >> type >> intensity >> blurCount;

	//		_fe3d->gfx_enableBloom();
	//		_fe3d->gfx_setBloomType(BloomType(type));
	//		_fe3d->gfx_setBloomIntensity(intensity);
	//		_fe3d->gfx_setBloomBlurCount(blurCount);
	//	}
	//	else
	//	{
	//		Logger::throwError("WorldEditor::loadCustomWorldFromFile::3");
	//	}
	//}

	//file.close();

	//_loadedWorldID = fileName;

	return true;
}