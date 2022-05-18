#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const bool WorldEditor::loadWorldFromFile(const string & fileName)
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
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

		auto iss = istringstream(line);

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
			string placedSkyId;
			string templateSkyId;

			iss
				>> placedSkyId
				>> templateSkyId;

			if(!_fe3d->sky_isExisting(templateSkyId))
			{
				continue;
			}

			_duplicator->copyTemplateSky(placedSkyId, templateSkyId);

			_fe3d->sky_select(placedSkyId);
		}
		else if(lineType == "TERRAIN")
		{
			string placedTerrainId;
			string templateTerrainId;

			iss
				>> placedTerrainId
				>> templateTerrainId;

			if(!_fe3d->terrain_isExisting(templateTerrainId))
			{
				continue;
			}

			_duplicator->copyTemplateTerrain(placedTerrainId, templateTerrainId);

			_fe3d->terrain_select(placedTerrainId);
		}
		else if(lineType == "WATER")
		{
			string placedWaterId;
			string templateWaterId;
			float height;

			iss
				>> placedWaterId
				>> templateWaterId
				>> height;

			if(!_fe3d->water_isExisting(templateWaterId))
			{
				continue;
			}

			_duplicator->copyTemplateWater(placedWaterId, templateWaterId);

			_fe3d->water_setHeight(placedWaterId, height);
			_fe3d->water_select(placedWaterId);
		}
		else if(lineType == "MODEL")
		{
			string placedModelId;
			string templateModelId;
			string animation3dId;
			fvec3 position;
			fvec3 rotation;
			fvec3 size;
			bool isFrozen;

			iss
				>> placedModelId
				>> templateModelId
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
				>> animation3dId;

			animation3dId = (animation3dId == "?") ? "" : animation3dId;

			replace(animation3dId.begin(), animation3dId.end(), '?', ' ');

			if(!_fe3d->model_isExisting(templateModelId))
			{
				continue;
			}

			_duplicator->copyTemplateModel(placedModelId, templateModelId);

			_loadedModelIds.insert({placedModelId, templateModelId});

			_fe3d->model_setBasePosition(placedModelId, position);
			_fe3d->model_setBaseRotation(placedModelId, rotation);
			_fe3d->model_setBaseSize(placedModelId, size);
			_fe3d->model_setFrozen(placedModelId, isFrozen);

			if(_fe3d->animation3d_isExisting(animation3dId))
			{
				_fe3d->model_startAnimation3d(placedModelId, animation3dId, -1);
			}
		}
		else if(lineType == "QUAD3D")
		{
			string placedQuad3dId;
			string templateQuad3dId;
			string animation2dId;
			fvec3 position;
			fvec3 rotation;
			fvec2 size;

			iss
				>> placedQuad3dId
				>> templateQuad3dId
				>> position.x
				>> position.y
				>> position.z
				>> rotation.x
				>> rotation.y
				>> rotation.z
				>> size.x
				>> size.y
				>> animation2dId;

			animation2dId = (animation2dId == "?") ? "" : animation2dId;

			replace(animation2dId.begin(), animation2dId.end(), '?', ' ');

			if(!_fe3d->quad3d_isExisting(templateQuad3dId))
			{
				continue;
			}

			_duplicator->copyTemplateQuad3d(placedQuad3dId, templateQuad3dId);

			_loadedQuad3dIds.insert({placedQuad3dId, templateQuad3dId});

			_fe3d->quad3d_setPosition(placedQuad3dId, position);
			_fe3d->quad3d_setRotation(placedQuad3dId, rotation);
			_fe3d->quad3d_setSize(placedQuad3dId, size);

			if(_fe3d->animation2d_isExisting(animation2dId))
			{
				_fe3d->quad3d_startAnimation2d(placedQuad3dId, animation2dId, -1);
			}
		}
		else if(lineType == "TEXT3D")
		{
			string placedText3dId;
			string templateText3dId;
			string content;
			fvec3 position;
			fvec3 rotation;
			fvec2 size;

			iss
				>> placedText3dId
				>> templateText3dId
				>> content
				>> position.x
				>> position.y
				>> position.z
				>> rotation.x
				>> rotation.y
				>> rotation.z
				>> size.x
				>> size.y;

			if(!_fe3d->text3d_isExisting(templateText3dId))
			{
				continue;
			}

			_duplicator->copyTemplateText3d(placedText3dId, templateText3dId);

			_loadedText3dIds.insert({placedText3dId, templateText3dId});

			_fe3d->text3d_setContent(placedText3dId, content);
			_fe3d->text3d_setPosition(placedText3dId, position);
			_fe3d->text3d_setRotation(placedText3dId, rotation);
			_fe3d->text3d_setSize(placedText3dId, size);
		}
		else if(lineType == "AABB")
		{
			string placedAabbId;
			string templateAabbId;
			fvec3 position;
			fvec3 size;

			iss
				>> placedAabbId
				>> templateAabbId
				>> position.x
				>> position.y
				>> position.z
				>> size.x
				>> size.y
				>> size.z;

			if(!_fe3d->aabb_isExisting(templateAabbId))
			{
				continue;
			}

			_duplicator->copyTemplateAabb(placedAabbId, templateAabbId);

			_loadedAabbIds.insert({placedAabbId, templateAabbId});

			_fe3d->aabb_setBasePosition(placedAabbId, position);
			_fe3d->aabb_setBaseSize(placedAabbId, size);
		}
		else if(lineType == "POINTLIGHT")
		{
			string placedPointlightId;
			string templatePointlightId;
			fvec3 position;

			iss
				>> placedPointlightId
				>> templatePointlightId
				>> position.x
				>> position.y
				>> position.z;

			if(!_fe3d->pointlight_isExisting(templatePointlightId))
			{
				continue;
			}

			_duplicator->copyTemplatePointlight(placedPointlightId, templatePointlightId);

			_fe3d->pointlight_setPosition(placedPointlightId, position);

			_loadedPointlightIds.insert({placedPointlightId, templatePointlightId});

			if(isLoaded())
			{
				const auto newModelId = ("@@lamp_" + placedPointlightId);

				_fe3d->model_create(newModelId, LAMP_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseSize(newModelId, LAMP_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);
				_fe3d->model_setColor(newModelId, "", _fe3d->pointlight_getColor(placedPointlightId));

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, LAMP_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
		else if(lineType == "SPOTLIGHT")
		{
			string placedSpotlightId;
			string templateSpotlightId;
			fvec3 position;
			float yaw;
			float pitch;

			iss
				>> placedSpotlightId
				>> templateSpotlightId
				>> position.x
				>> position.y
				>> position.z
				>> yaw
				>> pitch;

			if(!_fe3d->spotlight_isExisting(templateSpotlightId))
			{
				continue;
			}

			_duplicator->copyTemplateSpotlight(placedSpotlightId, templateSpotlightId);

			_fe3d->spotlight_setPosition(placedSpotlightId, position);
			_fe3d->spotlight_setYaw(placedSpotlightId, yaw);
			_fe3d->spotlight_setPitch(placedSpotlightId, pitch);

			_loadedSpotlightIds.insert({placedSpotlightId, templateSpotlightId});

			if(isLoaded())
			{
				const auto newModelId = ("@@torch_" + placedSpotlightId);

				_fe3d->model_create(newModelId, TORCH_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseRotation(newModelId, fvec3(0.0f, -yaw, pitch));
				_fe3d->model_setBaseSize(newModelId, TORCH_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);
				_fe3d->model_setColor(newModelId, "", _fe3d->spotlight_getColor(placedSpotlightId));

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, TORCH_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
		else if(lineType == "SOUND3D")
		{
			string placedSound3dId;
			string templateSound3dId;
			fvec3 position;

			iss
				>> placedSound3dId
				>> templateSound3dId
				>> position.x
				>> position.y
				>> position.z;

			if(!_fe3d->sound3d_isExisting(templateSound3dId))
			{
				continue;
			}

			_duplicator->copyTemplateSound3d(placedSound3dId, templateSound3dId);

			_fe3d->sound3d_setPosition(placedSound3dId, position);
			_fe3d->sound3d_start(placedSound3dId, -1);

			_loadedSound3dIds.insert({placedSound3dId, templateSound3dId});

			if(isLoaded())
			{
				const auto newModelId = ("@@speaker_" + placedSound3dId);

				_fe3d->model_create(newModelId, SPEAKER_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseSize(newModelId, SPEAKER_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, SPEAKER_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
		else if(lineType == "CAPTOR")
		{
			string placedCaptorId;
			string exceptionId;
			fvec3 position;

			iss
				>> placedCaptorId
				>> position.x
				>> position.y
				>> position.z
				>> exceptionId;

			_fe3d->captor_create(placedCaptorId);
			_fe3d->captor_setPosition(placedCaptorId, position);
			_fe3d->captor_setExceptionId(placedCaptorId, (_fe3d->model_isExisting(exceptionId) ? exceptionId : ""));
			_fe3d->captor_capture(placedCaptorId);

			_loadedCaptorIds.push_back(placedCaptorId);

			if(isLoaded())
			{
				const auto newModelId = ("@@lens_" + placedCaptorId);

				_fe3d->model_create(newModelId, LENS_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseSize(newModelId, LENS_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, LENS_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
		else if(lineType == "GRAPHICS_AMBIENT_LIGHTING")
		{
			fvec3 color;
			float intensity;

			iss
				>> color.r
				>> color.g
				>> color.b
				>> intensity;

			_fe3d->graphics_setAmbientLightingEnabled(true);
			_fe3d->graphics_setAmbientLightingColor(color);
			_fe3d->graphics_setAmbientLightingIntensity(intensity);
		}
		else if(lineType == "GRAPHICS_DIRECTIONAL_LIGHTING")
		{
			fvec3 position;
			fvec3 color;
			float intensity;

			iss
				>> position.x
				>> position.y
				>> position.z
				>> color.r
				>> color.g
				>> color.b
				>> intensity;

			_fe3d->graphics_setDirectionalLightingEnabled(true);
			_fe3d->graphics_setDirectionalLightingPosition(position);
			_fe3d->graphics_setDirectionalLightingIntensity(intensity);
			_fe3d->graphics_setDirectionalLightingColor(color);
		}
		else if(lineType == "GRAPHICS_SHADOWS")
		{
			float size;
			float lightness;
			fvec3 position;
			fvec3 center;
			bool isFollowingCameraX;
			bool isFollowingCameraY;
			bool isFollowingCameraZ;
			int interval;
			int quality;

			iss
				>> size
				>> lightness
				>> position.x
				>> position.y
				>> position.z
				>> center.x
				>> center.y
				>> center.z
				>> isFollowingCameraX
				>> isFollowingCameraY
				>> isFollowingCameraZ
				>> interval
				>> quality;

			_fe3d->graphics_setShadowsEnabled(true);
			_fe3d->graphics_setShadowPositionOffset(position);
			_fe3d->graphics_setShadowLookatOffset(center);
			_fe3d->graphics_setShadowSize(size);
			_fe3d->graphics_setShadowLightness(lightness);
			_fe3d->graphics_setShadowFollowingCameraX(isFollowingCameraX);
			_fe3d->graphics_setShadowFollowingCameraY(isFollowingCameraY);
			_fe3d->graphics_setShadowFollowingCameraZ(isFollowingCameraZ);
			_fe3d->graphics_setShadowInterval(interval);
			_fe3d->graphics_setShadowQuality(quality);
		}
		else if(lineType == "GRAPHICS_REFLECTIONS")
		{
			float planarHeight;
			int cubeInterval;
			int cubeQuality;
			int planarQuality;

			iss
				>> cubeInterval
				>> cubeQuality
				>> planarHeight
				>> planarQuality;

			_fe3d->graphics_setCubeReflectionInterval(cubeInterval);
			_fe3d->graphics_setCubeReflectionQuality(cubeQuality);
			_fe3d->graphics_setPlanarReflectionHeight(planarHeight);
			_fe3d->graphics_setPlanarReflectionQuality(planarQuality);
		}
		else if(lineType == "GRAPHICS_REFRACTIONS")
		{
			float planarHeight;
			int cubeInterval;
			int cubeQuality;
			int planarQuality;

			iss
				>> cubeInterval
				>> cubeQuality
				>> planarHeight
				>> planarQuality;

			_fe3d->graphics_setCubeRefractionInterval(cubeInterval);
			_fe3d->graphics_setCubeRefractionQuality(cubeQuality);
			_fe3d->graphics_setPlanarRefractionHeight(planarHeight);
			_fe3d->graphics_setPlanarRefractionQuality(planarQuality);
		}
		else if(lineType == "GRAPHICS_DOF")
		{
			bool isDynamic;
			float blurDistance;
			float maxDistance;
			int quality;

			iss
				>> isDynamic
				>> blurDistance
				>> maxDistance
				>> quality;

			_fe3d->graphics_setDofEnabled(true);
			_fe3d->graphics_setDofDynamic(isDynamic);
			_fe3d->graphics_setDofDynamicDistance(maxDistance);
			_fe3d->graphics_setDofBlurDistance(blurDistance);
			_fe3d->graphics_setDofQuality(quality);
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

			_fe3d->graphics_setFogEnabled(true);
			_fe3d->graphics_setFogMinDistance(minDistance);
			_fe3d->graphics_setFogMaxDistance(maxDistance);
			_fe3d->graphics_setFogThickness(thickness);
			_fe3d->graphics_setFogColor(color);
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

			if(!Configuration::getInst().isApplicationExported())
			{
				flareMapPath = ("projects\\" + getCurrentProjectId() + "\\" + flareMapPath);
			}

			_fe3d->graphics_setLensFlareEnabled(true);
			_fe3d->graphics_setLensFlareMap(flareMapPath);
			_fe3d->graphics_setLensFlareIntensity(intensity);
			_fe3d->graphics_setLensFlareSensitivity(sensitivity);
		}
		else if(lineType == "GRAPHICS_SKY_EXPOSURE")
		{
			float intensity;
			float speed;

			iss
				>> intensity
				>> speed;

			_fe3d->graphics_setSkyExposureEnabled(true);
			_fe3d->graphics_setSkyExposureIntensity(intensity);
			_fe3d->graphics_setSkyExposureSpeed(speed);
		}
		else if(lineType == "GRAPHICS_BLOOM")
		{
			float intensity;
			int type;
			int blurCount;
			int quality;

			iss
				>> type
				>> intensity
				>> blurCount
				>> quality;

			_fe3d->graphics_setBloomEnabled(true);
			_fe3d->graphics_setBloomType(BloomType(type));
			_fe3d->graphics_setBloomIntensity(intensity);
			_fe3d->graphics_setBloomBlurCount(blurCount);
			_fe3d->graphics_setBloomQuality(quality);
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