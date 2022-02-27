#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const bool WorldEditor::loadWorldFromFile(const string& fileName)
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "worlds\\editor\\" + fileName + ".fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string lineType;

		istringstream iss(line);

		iss >> lineType;

		if(lineType == "ID_COUNTER")
		{
			if(isLoaded())
			{
				iss >> _idCounter;
			}
		}
		else if(lineType == "EDITOR_SPEED")
		{
			if(isLoaded())
			{
				iss >> _editorSpeed;
			}
		}
		else if(lineType == "CAMERA_POSITION")
		{
			if(isLoaded())
			{
				fvec3 position;

				iss
					>> position.x
					>> position.y
					>> position.z;
				_fe3d->camera_setPosition(position);
			}
		}
		else if(lineType == "CAMERA_YAW")
		{
			if(isLoaded())
			{
				float yaw;

				iss >> yaw;

				_fe3d->camera_setYaw(yaw);
				_fe3d->camera_setFirstPersonYaw(yaw);
			}
		}
		else if(lineType == "CAMERA_PITCH")
		{
			if(isLoaded())
			{
				float pitch;

				iss >> pitch;

				_fe3d->camera_setPitch(pitch);
				_fe3d->camera_setFirstPersonPitch(pitch);
			}
		}
		else if(lineType == "SKY")
		{
			string skyId;
			string templateId;

			iss
				>> skyId
				>> templateId;

			if(!_fe3d->sky_isExisting(templateId))
			{
				continue;
			}

			_worldUtilities->copyTemplateSky(skyId, templateId);

			_fe3d->sky_select(skyId);
		}
		else if(lineType == "TERRAIN")
		{
			string terrainId;
			string templateId;

			iss
				>> terrainId
				>> templateId;

			if(!_fe3d->terrain_isExisting(templateId))
			{
				continue;
			}

			_worldUtilities->copyTemplateTerrain(terrainId, templateId);

			_fe3d->terrain_select(terrainId);
		}
		else if(lineType == "WATER")
		{
			string waterId;
			string templateId;
			float height;

			iss
				>> waterId
				>> templateId
				>> height;

			if(!_fe3d->water_isExisting(templateId))
			{
				continue;
			}

			_worldUtilities->copyTemplateWater(waterId, templateId);

			_fe3d->water_setHeight(waterId, height);

			_fe3d->water_select(waterId);
		}
		else if(lineType == "MODEL")
		{
			string modelId;
			string templateId;
			string animationId;
			fvec3 position;
			fvec3 rotation;
			fvec3 size;
			bool isFrozen;

			iss >> modelId;

			iss
				>> templateId
				>> position.x
				>> position.y
				>> position.z
				>> rotation.x
				>> rotation.y
				>> rotation.z
				>> size.x
				>> size.y
				>> size.z
				>> isFrozen
				>> animationId;

			animationId = (animationId == "?") ? "" : animationId;

			replace(animationId.begin(), animationId.end(), '?', ' ');

			if(!_fe3d->model_isExisting(templateId))
			{
				continue;
			}

			_loadedModelIds.insert({modelId, templateId});

			_worldUtilities->copyTemplateModel(modelId, templateId);

			_fe3d->model_setBasePosition(modelId, position);
			_fe3d->model_setBaseRotation(modelId, rotation);
			_fe3d->model_setBaseSize(modelId, size);
			_fe3d->model_setFrozen(modelId, isFrozen);

			if(_fe3d->animation3d_isExisting(animationId))
			{
				_fe3d->model_startAnimation(modelId, animationId, -1);
			}
		}
		else if(lineType == "QUAD3D")
		{
			string quadId;
			string templateId;
			string animationId;
			fvec3 position;
			fvec3 rotation;
			fvec2 size;

			iss
				>> quadId
				>> templateId
				>> position.x
				>> position.y
				>> position.z
				>> rotation.x
				>> rotation.y
				>> rotation.z
				>> size.x
				>> size.y
				>> animationId;

			animationId = (animationId == "?") ? "" : animationId;

			replace(animationId.begin(), animationId.end(), '?', ' ');

			if(!_fe3d->quad3d_isExisting(templateId))
			{
				continue;
			}

			_loadedQuadIds.insert({quadId, templateId});

			_worldUtilities->copyTemplateQuad3d(quadId, templateId);

			_fe3d->quad3d_setPosition(quadId, position);
			_fe3d->quad3d_setRotation(quadId, rotation);
			_fe3d->quad3d_setSize(quadId, size);

			if(_fe3d->animation2d_isExisting(animationId))
			{
				_fe3d->quad3d_startAnimation(quadId, animationId, -1);
			}
		}
		else if(lineType == "TEXT3D")
		{
			string textId;
			string templateId;
			fvec3 position;
			fvec3 rotation;
			fvec2 size;

			iss
				>> textId
				>> templateId
				>> position.x
				>> position.y
				>> position.z
				>> rotation.x
				>> rotation.y
				>> rotation.z
				>> size.x
				>> size.y;

			if(!_fe3d->text3d_isExisting(templateId))
			{
				continue;
			}

			_loadedTextIds.insert({textId, templateId});

			_worldUtilities->copyTemplateText3d(textId, templateId);

			_fe3d->text3d_setPosition(textId, position);
			_fe3d->text3d_setRotation(textId, rotation);
			_fe3d->text3d_setSize(textId, size);
		}
		else if(lineType == "SOUND")
		{
			string soundId;
			string templateId;
			fvec3 position;
			float maxVolume;
			float maxDistance;

			iss
				>> soundId
				>> templateId
				>> position.x
				>> position.y
				>> position.z
				>> maxVolume
				>> maxDistance;

			if(isLoaded())
			{
				const string newModelId = ("@@speaker_" + soundId);
				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\speaker.obj");
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseSize(newModelId, DEFAULT_SPEAKER_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_SPEAKER_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}

			if(!_fe3d->sound2d_isExisting(templateId))
			{
				continue;
			}

			_loadedSoundIds.insert({soundId, templateId});

			_worldUtilities->copyTemplateSound3d(soundId, templateId);

			_fe3d->sound3d_setPosition(soundId, position);
			_fe3d->sound3d_setMaxVolume(soundId, maxVolume);
			_fe3d->sound3d_setMaxDistance(soundId, maxDistance);
			_fe3d->sound3d_start(soundId, -1, 0, false);
		}
		else if(lineType == "POINTLIGHT")
		{
			string pointlightId;
			fvec3 position;
			fvec3 radius;
			fvec3 color;
			float intensity;
			unsigned int shape;

			iss
				>> pointlightId
				>> position.x
				>> position.y
				>> position.z
				>> radius.x
				>> radius.y
				>> radius.z
				>> color.r
				>> color.g
				>> color.b
				>> intensity
				>> shape;

			if(isLoaded())
			{
				const string newModelId = ("@@lamp_" + pointlightId);
				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\lamp.obj");
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseSize(newModelId, DEFAULT_LAMP_SIZE);
				_fe3d->model_setColor(newModelId, "", color);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_LAMP_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}

			_fe3d->pointlight_create(pointlightId);
			_fe3d->pointlight_setPosition(pointlightId, position);
			_fe3d->pointlight_setRadius(pointlightId, radius);
			_fe3d->pointlight_setColor(pointlightId, color);
			_fe3d->pointlight_setIntensity(pointlightId, intensity);
			_fe3d->pointlight_setShape(pointlightId, PointlightShape(shape));

			_loadedPointlightIds.push_back(pointlightId);
		}
		else if(lineType == "SPOTLIGHT")
		{
			string spotlightId;
			fvec3 position;
			fvec3 color;
			float yaw;
			float pitch;
			float intensity;
			float angle;
			float distance;

			iss
				>> spotlightId
				>> position.x
				>> position.y
				>> position.z
				>> color.r
				>> color.g
				>> color.b
				>> yaw
				>> pitch
				>> intensity
				>> angle
				>> distance;

			if(isLoaded())
			{
				const string newModelId = ("@@torch_" + spotlightId);
				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\torch.obj");
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseRotation(newModelId, fvec3(0.0f, -yaw, pitch));
				_fe3d->model_setBaseSize(newModelId, DEFAULT_TORCH_SIZE);
				_fe3d->model_setColor(newModelId, "", color);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_TORCH_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}

			_fe3d->spotlight_create(spotlightId);
			_fe3d->spotlight_setPosition(spotlightId, position);
			_fe3d->spotlight_setColor(spotlightId, color);
			_fe3d->spotlight_setYaw(spotlightId, yaw);
			_fe3d->spotlight_setPitch(spotlightId, pitch);
			_fe3d->spotlight_setIntensity(spotlightId, intensity);
			_fe3d->spotlight_setAngle(spotlightId, angle);
			_fe3d->spotlight_setDistance(spotlightId, distance);

			_loadedSpotlightIds.push_back(spotlightId);
		}
		else if(lineType == "REFLECTION")
		{
			string reflectionId, exceptionModelId;
			fvec3 position;

			iss
				>> reflectionId
				>> position.x
				>> position.y
				>> position.z
				>> exceptionModelId;

			if(isLoaded())
			{
				const string newModelId = ("@@camera_" + reflectionId);
				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\camera.obj");
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseSize(newModelId, DEFAULT_CAMERA_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_CAMERA_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}

			_fe3d->reflection_create(reflectionId);
			_fe3d->reflection_setPosition(reflectionId, position);
			_fe3d->reflection_setExceptionModelId(reflectionId, (_fe3d->model_isExisting(exceptionModelId) ? exceptionModelId : ""));
			_fe3d->reflection_capture(reflectionId);

			_loadedReflectionIds.push_back(reflectionId);
		}
		else if(lineType == "LIGHTING_AMBIENT")
		{
			fvec3 color;
			float intensity;

			iss
				>> color.r
				>> color.g
				>> color.b
				>> intensity;

			_fe3d->gfx_setAmbientLightingEnabled(true);
			_fe3d->gfx_setAmbientLightingColor(color);
			_fe3d->gfx_setAmbientLightingIntensity(intensity);
		}
		else if(lineType == "LIGHTING_DIRECTIONAL")
		{
			fvec3 position;
			fvec3 color;
			float intensity;
			float quad3dSize;

			iss
				>> position.x
				>> position.y
				>> position.z
				>> color.r
				>> color.g
				>> color.b
				>> intensity
				>> quad3dSize;

			_fe3d->gfx_setDirectionalLightingEnabled(true);
			_fe3d->gfx_setDirectionalLightingPosition(position);
			_fe3d->gfx_setDirectionalLightingIntensity(intensity);
			_fe3d->gfx_setDirectionalLightingColor(color);
		}
		else if(lineType == "GRAPHICS_SHADOWS")
		{
			float size;
			float lightness;
			fvec3 position;
			fvec3 center;
			bool isFollowingCamera;
			unsigned int interval;
			unsigned int quality;

			iss
				>> size
				>> lightness
				>> position.x
				>> position.y
				>> position.z
				>> center.x
				>> center.y
				>> center.z
				>> isFollowingCamera
				>> interval
				>> quality;

			_fe3d->gfx_setShadowsEnabled(true);
			_fe3d->gfx_setShadowPositionOffset(position);
			_fe3d->gfx_setShadowLookatOffset(center);
			_fe3d->gfx_setShadowSize(size);
			_fe3d->gfx_setShadowLightness(lightness);
			_fe3d->gfx_setShadowFollowingCamera(isFollowingCamera);
			_fe3d->gfx_setShadowInterval(interval);
			_fe3d->gfx_setShadowQuality(quality);
		}
		else if(lineType == "GRAPHICS_REFLECTIONS")
		{
			float planarHeight;
			unsigned int cubeQuality;
			unsigned int planarQuality;

			iss
				>> planarHeight
				>> cubeQuality
				>> planarQuality;

			_fe3d->gfx_setPlanarReflectionHeight(planarHeight);
			_fe3d->gfx_setCubeReflectionQuality(cubeQuality);
			_fe3d->gfx_setPlanarReflectionQuality(planarQuality);
		}
		else if(lineType == "GRAPHICS_REFRACTIONS")
		{
			unsigned int planarQuality;

			iss >> planarQuality;

			_fe3d->gfx_setPlanarRefractionQuality(planarQuality);
		}
		else if(lineType == "GRAPHICS_DOF")
		{
			bool isDynamic;
			float blurDistance;
			float maxDistance;
			unsigned int quality;

			iss
				>> isDynamic
				>> blurDistance
				>> maxDistance
				>> quality;

			_fe3d->gfx_setDofEnabled(true);
			_fe3d->gfx_setDofDynamic(isDynamic);
			_fe3d->gfx_setDofDynamicDistance(maxDistance);
			_fe3d->gfx_setDofBlurDistance(blurDistance);
			_fe3d->gfx_setDofQuality(quality);
		}
		else if(lineType == "GRAPHICS_FOG")
		{
			float minDistance;
			float maxDistance;
			float thickness;
			fvec3 color;

			iss
				>> minDistance
				>> maxDistance
				>> thickness
				>> color.r
				>> color.g
				>> color.b;

			_fe3d->gfx_setFogEnabled(true);
			_fe3d->gfx_setFogMinDistance(minDistance);
			_fe3d->gfx_setFogMaxDistance(maxDistance);
			_fe3d->gfx_setFogThickness(thickness);
			_fe3d->gfx_setFogColor(color);
		}
		else if(lineType == "GRAPHICS_LENS_FLARE")
		{
			string flareMapPath;
			float intensity;
			float sensitivity;

			iss
				>> flareMapPath
				>> intensity
				>> sensitivity;

			flareMapPath = (flareMapPath == "?") ? "" : flareMapPath;

			replace(flareMapPath.begin(), flareMapPath.end(), '?', ' ');

			if(!Config::getInst().isApplicationExported())
			{
				flareMapPath = ("projects\\" + getCurrentProjectId() + "\\" + flareMapPath);
			}

			_fe3d->gfx_setLensFlareEnabled(true);
			_fe3d->gfx_setLensFlareMap(flareMapPath);
			_fe3d->gfx_setLensFlareIntensity(intensity);
			_fe3d->gfx_setLensFlareSensitivity(sensitivity);
		}
		else if(lineType == "GRAPHICS_SKY_EXPOSURE")
		{
			float intensity;
			float speed;

			iss
				>> intensity
				>> speed;

			_fe3d->gfx_setSkyExposureEnabled(true);
			_fe3d->gfx_setSkyExposureIntensity(intensity);
			_fe3d->gfx_setSkyExposureSpeed(speed);
		}
		else if(lineType == "GRAPHICS_BLOOM")
		{
			float intensity;
			unsigned int type;
			unsigned int blurCount;
			unsigned int quality;

			iss
				>> type
				>> intensity
				>> blurCount
				>> quality;

			_fe3d->gfx_setBloomEnabled(true);
			_fe3d->gfx_setBloomType(BloomType(type));
			_fe3d->gfx_setBloomIntensity(intensity);
			_fe3d->gfx_setBloomBlurCount(blurCount);
			_fe3d->gfx_setBloomQuality(quality);
		}
		else
		{
			abort();
		}
	}

	file.close();

	_loadedWorldId = fileName;

	Logger::throwInfo("World editor data loaded");

	return true;
}