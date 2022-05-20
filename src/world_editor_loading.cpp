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

	string line = "";

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
			string skyId;
			string templateSkyId;

			iss
				>> skyId
				>> templateSkyId;

			if(!_fe3d->sky_isExisting(templateSkyId))
			{
				continue;
			}

			_duplicator->copyTemplateSky(skyId, templateSkyId);

			_fe3d->sky_select(skyId);
		}
		else if(lineType == "TERRAIN")
		{
			string terrainId;
			string templateTerrainId;

			iss
				>> terrainId
				>> templateTerrainId;

			if(!_fe3d->terrain_isExisting(templateTerrainId))
			{
				continue;
			}

			_duplicator->copyTemplateTerrain(terrainId, templateTerrainId);

			_fe3d->terrain_select(terrainId);
		}
		else if(lineType == "WATER")
		{
			string waterId;
			string templateWaterId;
			float height;

			iss
				>> waterId
				>> templateWaterId
				>> height;

			if(!_fe3d->water_isExisting(templateWaterId))
			{
				continue;
			}

			_duplicator->copyTemplateWater(waterId, templateWaterId);

			_fe3d->water_setHeight(waterId, height);
			_fe3d->water_select(waterId);
		}
		else if(lineType == "MODEL")
		{
			string modelId;
			string templateModelId;
			string animation3dId;
			fvec3 position;
			fvec3 rotation;
			fvec3 size;
			bool isFrozen;

			iss
				>> modelId
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

			_duplicator->copyTemplateModel(modelId, templateModelId);

			_fe3d->model_setBasePosition(modelId, position);
			_fe3d->model_setBaseRotation(modelId, rotation);
			_fe3d->model_setBaseSize(modelId, size);
			_fe3d->model_setFrozen(modelId, isFrozen);

			if(_fe3d->animation3d_isExisting(animation3dId))
			{
				_fe3d->model_startAnimation3d(modelId, animation3dId, -1);
			}

			_loadedModelIds.push_back(modelId);
		}
		else if(lineType == "QUAD3D")
		{
			string quad3dId;
			string templateQuad3dId;
			string animation2dId;
			fvec3 position;
			fvec3 rotation;
			fvec2 size;

			iss
				>> quad3dId
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

			_duplicator->copyTemplateQuad3d(quad3dId, templateQuad3dId);

			_fe3d->quad3d_setPosition(quad3dId, position);
			_fe3d->quad3d_setRotation(quad3dId, rotation);
			_fe3d->quad3d_setSize(quad3dId, size);

			if(_fe3d->animation2d_isExisting(animation2dId))
			{
				_fe3d->quad3d_startAnimation2d(quad3dId, animation2dId, -1);
			}

			_loadedQuad3dIds.push_back(quad3dId);
		}
		else if(lineType == "TEXT3D")
		{
			string text3dId;
			string templateText3dId;
			string content;
			fvec3 position;
			fvec3 rotation;
			fvec2 size;

			iss
				>> text3dId
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

			_duplicator->copyTemplateText3d(text3dId, templateText3dId);

			_fe3d->text3d_setContent(text3dId, content);
			_fe3d->text3d_setPosition(text3dId, position);
			_fe3d->text3d_setRotation(text3dId, rotation);
			_fe3d->text3d_setSize(text3dId, size);

			_loadedText3dIds.push_back(text3dId);
		}
		else if(lineType == "AABB")
		{
			string aabbId;
			string templateAabbId;
			fvec3 position;
			fvec3 size;

			iss
				>> aabbId
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

			_duplicator->copyTemplateAabb(aabbId, templateAabbId);

			_fe3d->aabb_setBasePosition(aabbId, position);
			_fe3d->aabb_setBaseSize(aabbId, size);

			_loadedAabbIds.push_back(aabbId);
		}
		else if(lineType == "POINTLIGHT")
		{
			string pointlightId;
			string templatePointlightId;
			fvec3 position;

			iss
				>> pointlightId
				>> templatePointlightId
				>> position.x
				>> position.y
				>> position.z;

			if(!_fe3d->pointlight_isExisting(templatePointlightId))
			{
				continue;
			}

			_duplicator->copyTemplatePointlight(pointlightId, templatePointlightId);

			_fe3d->pointlight_setPosition(pointlightId, position);

			_loadedPointlightIds.push_back(pointlightId);

			if(isLoaded())
			{
				const auto newModelId = ("@@lamp_" + pointlightId);

				_fe3d->model_create(newModelId, LAMP_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseSize(newModelId, LAMP_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);
				_fe3d->model_setColor(newModelId, "", _fe3d->pointlight_getColor(pointlightId));

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
			string spotlightId;
			string templateSpotlightId;
			fvec3 position;
			float yaw;
			float pitch;

			iss
				>> spotlightId
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

			_duplicator->copyTemplateSpotlight(spotlightId, templateSpotlightId);

			_fe3d->spotlight_setPosition(spotlightId, position);
			_fe3d->spotlight_setYaw(spotlightId, yaw);
			_fe3d->spotlight_setPitch(spotlightId, pitch);

			_loadedSpotlightIds.push_back(spotlightId);

			if(isLoaded())
			{
				const auto newModelId = ("@@torch_" + spotlightId);

				_fe3d->model_create(newModelId, TORCH_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, position);
				_fe3d->model_setBaseRotation(newModelId, fvec3(0.0f, -yaw, pitch));
				_fe3d->model_setBaseSize(newModelId, TORCH_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);
				_fe3d->model_setColor(newModelId, "", _fe3d->spotlight_getColor(spotlightId));

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
			string sound3dId;
			string templateSound3dId;
			fvec3 position;

			iss
				>> sound3dId
				>> templateSound3dId
				>> position.x
				>> position.y
				>> position.z;

			if(!_fe3d->sound3d_isExisting(templateSound3dId))
			{
				continue;
			}

			_duplicator->copyTemplateSound3d(sound3dId, templateSound3dId);

			_fe3d->sound3d_setPosition(sound3dId, position);
			_fe3d->sound3d_start(sound3dId, -1);

			_loadedSound3dIds.push_back(sound3dId);

			if(isLoaded())
			{
				const auto newModelId = ("@@speaker_" + sound3dId);

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
			string captorId;
			string exceptionId;
			fvec3 position;

			iss
				>> captorId
				>> position.x
				>> position.y
				>> position.z
				>> exceptionId;

			_fe3d->captor_create(captorId);
			_fe3d->captor_setPosition(captorId, position);
			_fe3d->captor_setExceptionId(captorId, (_fe3d->model_isExisting(exceptionId) ? exceptionId : ""));
			_fe3d->captor_capture(captorId);

			_loadedCaptorIds.push_back(captorId);

			if(isLoaded())
			{
				const auto newModelId = ("@@lens_" + captorId);

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
			int planarQuality;

			iss
				>> planarHeight
				>> planarQuality;

			_fe3d->graphics_setPlanarReflectionHeight(planarHeight);
			_fe3d->graphics_setPlanarReflectionQuality(planarQuality);
		}
		else if(lineType == "GRAPHICS_REFRACTIONS")
		{
			float planarHeight;
			int planarQuality;

			iss
				>> planarHeight
				>> planarQuality;

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

	Logger::throwInfo("Editor world data loaded");

	return true;
}