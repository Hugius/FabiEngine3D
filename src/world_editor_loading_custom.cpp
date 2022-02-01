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
	//if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	//{
	//	abort();
	//}
	//if(isLoaded())
	//{
	//	abort();
	//}

	//const auto rootPath = Tools::getRootDirectoryPath();
	//const auto filePath = (rootPath + (Config::getInst().isApplicationExported() ? "" :
	//					   ("projects\\" + getCurrentProjectId() + "\\")) + "worlds\\custom\\" + fileName + ".fe3d");

	//auto file = ifstream(filePath);
	//if(!file)
	//{
	//	Logger::throwWarning("Cannot load world with id \"" + fileName + "\"!");
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
	//		string skyId, templateId;
	//		fvec3 color;
	//		float rotation, lightness;

	//		iss >>
	//			skyId >>
	//			templateId >>
	//			rotation >>
	//			lightness >>
	//			color.r >>
	//			color.g >>
	//			color.b;

	//		if(_copyTemplateSky(skyId, templateId))
	//		{
	//			_fe3d->sky_setRotation(skyId, rotation);
	//			_fe3d->sky_setLightness(skyId, lightness);
	//			_fe3d->sky_setColor(skyId, color);
	//		}
	//	}
	//	else if(lineType == "TERRAIN")
	//	{
	//		string terrainId, templateId;

	//		iss >> terrainId >> templateId;

	//		_copyTemplateTerrain(terrainId, templateId);
	//	}
	//	else if(lineType == "WATER")
	//	{
	//		string waterId, templateId;
	//		fvec3 color;
	//		fvec2 speed;
	//		float opacity;

	//		iss >>
	//			waterId >>
	//			templateId >>
	//			color.r >>
	//			color.g >>
	//			color.b >>
	//			speed.x >>
	//			speed.y >>
	//			opacity;

	//		if(_copyTemplateWater(waterId, templateId))
	//		{
	//			_fe3d->water_setColor(waterId, color);
	//			_fe3d->water_setSpeed(waterId, speed);
	//			_fe3d->water_setOpacity(waterId, opacity);
	//		}
	//	}
	//	else if(lineType == "MODEL")
	//	{
	//		string modelId, templateId;
	//		fvec3 position, rotation, rotationOrigin, size, color;
	//		float minHeight, maxHeight, opacity, lightness;
	//		unsigned partCount;
	//		bool isVisible, isFrozen, isAabbRaycastResponsive, isAabbCollisionResponsive;

	//		iss >> modelId;

	//		bool makeInvisible = (modelId[0] == '@');

	//		iss >>
	//			templateId >>
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
	//			opacity >>
	//			lightness >>
	//			partCount;

	//		if(partCount > 1)
	//		{
	//			vector<string> partIds;
	//			for(unsigned int i = 0; i < partCount; i++)
	//			{
	//				string partId;
	//				iss >> partId;
	//				partIds.push_back(partId);
	//			}

	//			if(partIds.size() != _fe3d->model_getPartIds(templateId).size())
	//			{
	//				Logger::throwWarning("World model parts with id \"" + modelId + "\" differ from base model!");
	//				continue;
	//			}

	//			for(size_t i = 0; i < partIds.size(); i++)
	//			{
	//				if(partIds[i] != _fe3d->model_getPartIds(templateId)[i])
	//				{
	//					Logger::throwWarning("World model parts with id \"" + modelId + "\" differ from base model!");
	//					continue;
	//				}
	//			}
	//		}

	//		if(_copyTemplateModel(modelId, templateId, position, false))
	//		{
	//			_fe3d->model_setBaseRotation(modelId, rotation);
	//			_fe3d->model_setBaseRotationOrigin(modelId, rotationOrigin);
	//			_fe3d->model_setBaseSize(modelId, size);
	//			_fe3d->model_setFrozen(modelId, isFrozen);
	//			_fe3d->model_setColor(modelId, "", color);
	//			_fe3d->model_setMinHeight(modelId, minHeight);
	//			_fe3d->model_setMaxHeight(modelId, maxHeight);
	//			//_fe3d->model_setOpacity(modelId, opacity);
	//			//_fe3d->model_setLightness(modelId, lightness);
	//			_fe3d->model_setVisible(modelId, isVisible);
	//			for(const auto& id : _fe3d->aabb_getChildIds(modelId, AabbParentEntityType::MODEL))
	//			{
	//				_fe3d->aabb_setRaycastResponsive(id, isAabbRaycastResponsive);
	//				_fe3d->aabb_setCollisionResponsive(id, isAabbCollisionResponsive);
	//			}

	//			for(unsigned int i = 0; i < partCount; i++)
	//			{
	//				string partId;
	//				iss >>
	//					partId >>
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

	//				_fe3d->model_setPartPosition(modelId, partId, position);
	//				_fe3d->model_setPartRotation(modelId, partId, rotation);
	//				_fe3d->model_setPartRotationOrigin(modelId, partId, rotationOrigin);
	//				_fe3d->model_setPartSize(modelId, partId, size);
	//			}

	//			if(makeInvisible)
	//			{
	//				_fe3d->model_setVisible(modelId, false);
	//			}
	//		}
	//	}
	//	else if(lineType == "ANIMATION3D")
	//	{
	//		string animationId, modelId;
	//		float speed;
	//		int remainingLoops;
	//		unsigned int frameIndex, fadeInterval;
	//		bool isPaused;

	//		iss >>
	//			animationId >>
	//			modelId >>
	//			isPaused >>
	//			frameIndex >>
	//			speed >>
	//			remainingLoops >>
	//			fadeInterval;

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
	//				string partId = (nextElement == "?") ? "" : nextElement;
	//				fvec3 speed;
	//				iss >> speed.x >> speed.y >> speed.z;
	//				speeds[partId] = speed;
	//			}
	//		}

	//		_animation3dEditor->startModelAnimation(animationId, modelId, remainingLoops);

	//		//if(_animation3dEditor->isAnimationExisting(animationId))
	//		//{
	//		//	// Retrieve raw animation data for editing
	//		//	string errorMessage = "Tried to retrieve animation with id \"" + animationId + "\" on model with id \"" + modelId + "\": ";
	//		//	auto animationData = _animation3dEditor->getAnimationData(animationId, modelId, errorMessage);
	//		//	auto frameData = animationData->getFrames()[frameIndex];

	//		//	// Set properties
	//		//	isPaused ? _animation3dEditor->pauseModelAnimation(animationId, modelId) : void();
	//		//	animationData->setSpeedMultiplier(speedMultiplier);
	//		//	animationData->setFadeInterval(fadeInterval);
	//		//	animationData->setFrameIndex(frameIndex);
	//		//	for(const auto& [key, speed] : speeds)
	//		//	{
	//		//		frameData.setSpeed(partId, speed);
	//		//	}

	//		//	// Retrieve parts
	//		//	auto partIds = _fe3d->model_getPartIds(modelId);
	//		//	for(const auto& partId : partIds)
	//		//	{
	//		//		// Retrieve part transformation
	//		//		auto position = _fe3d->model_getPartPosition(modelId, partId);
	//		//		auto rotation = _fe3d->model_getPartRotation(modelId, partId);
	//		//		auto size = _fe3d->model_getPartSize(modelId, partId);

	//		//		// Set properties
	//		//		animationData->setTotalMovement(partId, position);
	//		//		animationData->setTotalRotation(partId, rotation);
	//		//		animationData->setTotalScaling(partId, size);
	//		//	}
	//		//}
	//	}
	//	else if(lineType == "QUAD3D")
	//	{
	//		string quadId, templateId, textContent;
	//		fvec3 position, rotation, color;
	//		fvec2 size;
	//		float lightness, minHeight, maxHeight;
	//		int remainingAnimationLoops;
	//		unsigned int animationRowIndex, animationColumnIndex;
	//		bool isVisible, isAabbRaycastResponsive, isAabbCollisionResponsive, isFacingCameraHorizontally, isFacingCameraVertically, isAnimationPlaying, isAnimationPaused;

	//		iss >>
	//			quadId >>
	//			templateId >>
	//			isVisible >>
	//			isAabbRaycastResponsive >>
	//			isAabbCollisionResponsive >>
	//			isFacingCameraHorizontally >>
	//			isFacingCameraVertically >>
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

	//		if(_copyTemplateQuad3d(quadId, templateId, position, false))
	//		{
	//			_fe3d->quad3d_setRotation(quadId, rotation);
	//			_fe3d->quad3d_setSize(quadId, size);
	//			_fe3d->quad3d_setFacingCameraHorizontally(quadId, isFacingCameraHorizontally);
	//			_fe3d->quad3d_setFacingCameraVertically(quadId, isFacingCameraVertically);
	//			_fe3d->quad3d_setColor(quadId, color);
	//			//_fe3d->quad3d_setTextContent(quadId, textContent);
	//			_fe3d->quad3d_setLightness(quadId, lightness);
	//			_fe3d->quad3d_setMinHeight(quadId, minHeight);
	//			_fe3d->quad3d_setMaxHeight(quadId, maxHeight);
	//			_fe3d->quad3d_setVisible(quadId, isVisible);
	//			for(const auto& id : _fe3d->aabb_getChildIds(quadId, AabbParentEntityType::QUAD3D))
	//			{
	//				_fe3d->aabb_setRaycastResponsive(id, isAabbRaycastResponsive);
	//				_fe3d->aabb_setCollisionResponsive(id, isAabbCollisionResponsive);
	//			}
	//		}
	//	}
	//	else if(lineType == "AABB")
	//	{
	//		string aabbId;
	//		fvec3 position, size;
	//		bool isVisible, isRaycastResponsive, isCollisionResponsive;

	//		iss >>
	//			aabbId >>
	//			isVisible >>
	//			isRaycastResponsive >>
	//			isCollisionResponsive >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			size.x >>
	//			size.y >>
	//			size.z;

	//		_fe3d->aabb_create(aabbId, false);
	//		_fe3d->aabb_setBasePosition(aabbId, position);
	//		_fe3d->aabb_setBaseSize(aabbId, size);
	//		_fe3d->aabb_setRaycastResponsive(aabbId, isRaycastResponsive);
	//		_fe3d->aabb_setCollisionResponsive(aabbId, isCollisionResponsive);
	//		_fe3d->aabb_setVisible(aabbId, isVisible);
	//		_loadedAabbIds.push_back(aabbId);
	//	}
	//	else if(lineType == "SOUND")
	//	{
	//		string soundId, templateId;
	//		fvec3 position;
	//		float maxVolume, maxDistance;

	//		iss >>
	//			soundId >>
	//			templateId >>
	//			position.x >>
	//			position.y >>
	//			position.z >>
	//			maxVolume >>
	//			maxDistance;

	//		if(_copyTemplateSound(soundId, templateId, position, false))
	//		{
	//			_fe3d->sound3d_setMaxVolume(soundId, maxVolume);
	//			_fe3d->sound3d_setMaxDistance(soundId, maxDistance);
	//			_fe3d->sound3d_start(soundId, -1, 0, false);
	//		}
	//	}
	//	else if(lineType == "POINTLIGHT")
	//	{
	//		string pointlightId;
	//		fvec3 position, radius, color;
	//		float intensity;

	//		iss >>
	//			pointlightId >>
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

	//		_fe3d->pointlight_setPosition(pointlightId, position);
	//		_fe3d->pointlight_setRadius(pointlightId, radius);
	//		_fe3d->pointlight_setColor(pointlightId, color);
	//		_fe3d->pointlight_setIntensity(pointlightId, intensity);
	//		_loadedPointlightIds.push_back(pointlightId);
	//	}
	//	else if(lineType == "SPOTLIGHT")
	//	{
	//		string spotlightId;
	//		fvec3 position, color;
	//		float yaw, pitch, intensity, angle, distance;

	//		iss >>
	//			spotlightId >>
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

	//		_fe3d->spotlight_setPosition(spotlightId, position);
	//		_fe3d->spotlight_setColor(spotlightId, color);
	//		_fe3d->spotlight_setYaw(spotlightId, yaw);
	//		_fe3d->spotlight_setPitch(spotlightId, pitch);
	//		_fe3d->spotlight_setIntensity(spotlightId, intensity);
	//		_fe3d->spotlight_setAngle(spotlightId, angle);
	//		_fe3d->spotlight_setDistance(spotlightId, distance);
	//		_loadedSpotlightIds.push_back(spotlightId);
	//	}
	//	else if(lineType == "REFLECTION")
	//	{
	//		string reflectionId;
	//		fvec3 position;

	//		iss >>
	//			reflectionId >>
	//			position.x >>
	//			position.y >>
	//			position.z;

	//		_fe3d->reflection_create(reflectionId);
	//		_fe3d->reflection_setPosition(reflectionId, position);
	//		_fe3d->reflection_capture(reflectionId);
	//		_loadedReflectionIds.push_back(reflectionId);
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
	//		_fe3d->gfx_setShadowPosition(position);
	//		_fe3d->gfx_setShadowLookat(center);
	//		_fe3d->gfx_setShadowSize(size);
	//		_fe3d->gfx_setShadowLightness(lightness);
	//		_fe3d->gfx_setShadowFollowingCamera(isFollowingCamera);
	//		_fe3d->gfx_setShadowInterval(interval);
	//	}
	//	else if(lineType == "GRAPHICS_MOTION_BLUR")
	//	{
	//		float intensity;

	//		iss >> intensity;

	//		_fe3d->gfx_enableMotionBlur();
	//		_fe3d->gfx_setMotionBlurIntensity(intensity);
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
	//		abort();
	//	}
	//}

	//file.close();

	//_loadedWorldId = fileName;

	return true;
}