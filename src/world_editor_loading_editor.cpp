#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const bool WorldEditor::loadEditorWorldFromFile(const string& fileName)
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("WorldEditor::loadEditorWorldFromFile::1");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "worlds\\editor\\" + fileName + ".fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Cannot load world with ID \"" + fileName + "\"!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		istringstream iss(line);

		string lineType;
		iss >> lineType;

		if(lineType == "CAMERA_POSITION")
		{
			fvec3 position;

			iss >> position.x >> position.y >> position.z;

			if(_isEditorLoaded)
			{
				_fe3d->camera_setPosition(position);
			}
		}
		else if(lineType == "CAMERA_YAW")
		{
			float yaw;

			iss >> yaw;

			if(_isEditorLoaded)
			{
				_fe3d->camera_setYaw(yaw);
			}
		}
		else if(lineType == "CAMERA_PITCH")
		{
			float pitch;

			iss >> pitch;

			if(_isEditorLoaded)
			{
				_fe3d->camera_setPitch(pitch);
			}
		}
		else if(lineType == "SKY")
		{
			string skyID;
			string templateID;

			iss >> skyID >> templateID;

			if(_copyTemplateSky(skyID, templateID))
			{
				if(_isEditorLoaded)
				{
					_currentSkyID = skyID;
				}
			}
		}
		else if(lineType == "TERRAIN")
		{
			string terrainID;
			string templateID;

			iss >> terrainID >> templateID;

			if(_copyTemplateTerrain(terrainID, templateID))
			{
				if(_isEditorLoaded)
				{
					_currentTerrainID = terrainID;
				}
			}
		}
		else if(lineType == "WATER")
		{
			string waterID;
			string templateID;
			float height;

			iss >> waterID >> templateID >> height;

			if(_copyTemplateWater(waterID, templateID))
			{
				if(_isEditorLoaded)
				{
					_currentWaterID = waterID;
				}

				_fe3d->water_setHeight(waterID, height);
			}
		}
		else if(lineType == "MODEL")
		{
			string modelID;
			string templateID;
			string animationID;
			fvec3 position;
			fvec3 rotation;
			fvec3 size;
			bool isFrozen;

			iss >> modelID;

			bool makeInvisible = false;
			if(modelID[0] == '@')
			{
				if(_isEditorLoaded)
				{
					continue;
				}
				else
				{
					makeInvisible = true;
				}
			}

			iss >>
				templateID >>
				position.x >>
				position.y >>
				position.z >>
				rotation.x >>
				rotation.y >>
				rotation.z >>
				size.x >>
				size.y >>
				size.z >>
				isFrozen >>
				animationID;

			animationID = (animationID == "?") ? "" : animationID;

			replace(animationID.begin(), animationID.end(), '?', ' ');

			if(_copyTemplateModel(modelID, templateID, position, false))
			{
				_fe3d->model_setBaseRotation(modelID, rotation);
				_fe3d->model_setBaseSize(modelID, size);
				_fe3d->model_setFrozen(modelID, isFrozen);

				if(_isEditorLoaded)
				{
					_initialModelPosition[modelID] = position;
					_initialModelRotation[modelID] = rotation;
					_initialModelSize[modelID] = size;
				}

				if(!animationID.empty())
				{
					_animation3dEditor->startModelAnimation(animationID, modelID, -1);
				}

				if(makeInvisible)
				{
					_fe3d->model_setVisible(modelID, false);
				}
			}
		}
		else if(lineType == "QUAD3D")
		{
			string quadID;
			string templateID;
			string animationID;
			fvec3 position;
			fvec3 rotation;
			fvec2 size;

			iss >>
				quadID >>
				templateID >>
				position.x >>
				position.y >>
				position.z >>
				rotation.x >>
				rotation.y >>
				rotation.z >>
				size.x >>
				size.y >>
				animationID;

			animationID = (animationID == "?") ? "" : animationID;

			replace(animationID.begin(), animationID.end(), '?', ' ');

			if(_copyTemplateQuad3d(quadID, templateID, position, false))
			{
				_fe3d->quad3d_setRotation(quadID, rotation);
				_fe3d->quad3d_setSize(quadID, size);

				if(!animationID.empty())
				{
					_animation2dEditor->startQuad3dAnimation(animationID, quadID, -1);
				}
			}
		}
		else if(lineType == "SOUND")
		{
			string soundID;
			string templateID;
			fvec3 position;
			float maxVolume;
			float maxDistance;

			iss >>
				soundID >>
				templateID >>
				position.x >>
				position.y >>
				position.z >>
				maxVolume >>
				maxDistance;

			if(_isEditorLoaded)
			{
				const string newModelID = ("@@speaker_" + soundID);
				_fe3d->model_create(newModelID, "engine\\assets\\mesh\\speaker.obj");
				_fe3d->model_setBasePosition(newModelID, position);
				_fe3d->model_setBaseSize(newModelID, DEFAULT_SPEAKER_SIZE);
				_fe3d->model_setShadowed(newModelID, false);
				_fe3d->model_setReflected(newModelID, false);
				_fe3d->model_setBright(newModelID, "", true);

				_fe3d->aabb_create(newModelID, true);
				_fe3d->aabb_setParentEntityID(newModelID, newModelID);
				_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
				_fe3d->aabb_setLocalSize(newModelID, DEFAULT_SPEAKER_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelID, false);
			}

			if(_copyTemplateSound(soundID, templateID, position, false))
			{
				_fe3d->sound3d_setMaxVolume(soundID, maxVolume);
				_fe3d->sound3d_setMaxDistance(soundID, maxDistance);
				_fe3d->sound3d_start(soundID, -1, 0, false);
			}
		}
		else if(lineType == "POINTLIGHT")
		{
			string pointlightID;
			fvec3 position;
			fvec3 radius;
			fvec3 color;
			float intensity;
			unsigned int shape;

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
				intensity >>
				shape;

			if(_isEditorLoaded)
			{
				const string newModelID = ("@@lamp_" + pointlightID);
				_fe3d->model_create(newModelID, "engine\\assets\\mesh\\lamp.obj");
				_fe3d->model_setBasePosition(newModelID, position);
				_fe3d->model_setBaseSize(newModelID, DEFAULT_LAMP_SIZE);
				_fe3d->model_setColor(newModelID, "", color);
				_fe3d->model_setShadowed(newModelID, false);
				_fe3d->model_setReflected(newModelID, false);
				_fe3d->model_setBright(newModelID, "", true);

				_fe3d->aabb_create(newModelID, true);
				_fe3d->aabb_setParentEntityID(newModelID, newModelID);
				_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
				_fe3d->aabb_setLocalSize(newModelID, DEFAULT_LAMP_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelID, false);
			}

			_fe3d->pointlight_create(pointlightID);
			_fe3d->pointlight_setPosition(pointlightID, position);
			_fe3d->pointlight_setRadius(pointlightID, radius);
			_fe3d->pointlight_setColor(pointlightID, color);
			_fe3d->pointlight_setIntensity(pointlightID, intensity);
			_fe3d->pointlight_setShape(pointlightID, PointlightShape(shape));
			_loadedPointlightIDs.push_back(pointlightID);
		}
		else if(lineType == "SPOTLIGHT")
		{
			string spotlightID;
			fvec3 position;
			fvec3 color;
			float yaw;
			float pitch;
			float intensity;
			float angle;
			float distance;

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

			if(_isEditorLoaded)
			{
				const string newModelID = ("@@torch_" + spotlightID);
				_fe3d->model_create(newModelID, "engine\\assets\\mesh\\torch.obj");
				_fe3d->model_setBasePosition(newModelID, position);
				_fe3d->model_setBaseRotation(newModelID, fvec3(0.0f, -yaw, pitch));
				_fe3d->model_setBaseSize(newModelID, DEFAULT_TORCH_SIZE);
				_fe3d->model_setColor(newModelID, "", color);
				_fe3d->model_setShadowed(newModelID, false);
				_fe3d->model_setReflected(newModelID, false);
				_fe3d->model_setBright(newModelID, "", true);

				_fe3d->aabb_create(newModelID, true);
				_fe3d->aabb_setParentEntityID(newModelID, newModelID);
				_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
				_fe3d->aabb_setLocalSize(newModelID, DEFAULT_TORCH_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelID, false);
			}

			_fe3d->spotlight_create(spotlightID);
			_fe3d->spotlight_setPosition(spotlightID, position);
			_fe3d->spotlight_setColor(spotlightID, color);
			_fe3d->spotlight_setYaw(spotlightID, yaw);
			_fe3d->spotlight_setPitch(spotlightID, pitch);
			_fe3d->spotlight_setIntensity(spotlightID, intensity);
			_fe3d->spotlight_setAngle(spotlightID, angle);
			_fe3d->spotlight_setDistance(spotlightID, distance);
			_loadedSpotlightIDs.push_back(spotlightID);
		}
		else if(lineType == "REFLECTION")
		{
			string reflectionID;
			fvec3 position;

			iss >>
				reflectionID >>
				position.x >>
				position.y >>
				position.z;

			if(_isEditorLoaded)
			{
				const string newModelID = ("@@camera_" + reflectionID);
				_fe3d->model_create(newModelID, "engine\\assets\\mesh\\camera.obj");
				_fe3d->model_setBasePosition(newModelID, position);
				_fe3d->model_setBaseSize(newModelID, DEFAULT_CAMERA_SIZE);
				_fe3d->model_setShadowed(newModelID, false);
				_fe3d->model_setReflected(newModelID, false);
				_fe3d->model_setBright(newModelID, "", true);

				_fe3d->aabb_create(newModelID, true);
				_fe3d->aabb_setParentEntityID(newModelID, newModelID);
				_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
				_fe3d->aabb_setLocalSize(newModelID, DEFAULT_CAMERA_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelID, false);
			}

			_fe3d->reflection_create(reflectionID);
			_fe3d->reflection_setPosition(reflectionID, position);
			_fe3d->reflection_capture(reflectionID);
			_loadedReflectionIDs.push_back(reflectionID);
		}
		else if(lineType == "EDITOR_SPEED")
		{
			if(_isEditorLoaded)
			{
				iss >> _editorSpeed;
			}
		}
		else if(lineType == "LIGHTING_AMBIENT")
		{
			fvec3 color;
			float intensity;

			iss >>
				color.r >>
				color.g >>
				color.b >>
				intensity;

			_fe3d->gfx_enableAmbientLighting();
			_fe3d->gfx_setAmbientLightingColor(color);
			_fe3d->gfx_setAmbientLightingIntensity(intensity);
		}
		else if(lineType == "LIGHTING_DIRECTIONAL")
		{
			fvec3 position;
			fvec3 color;
			float intensity;
			float quad3dSize;

			iss >>
				position.x >>
				position.y >>
				position.z >>
				color.r >>
				color.g >>
				color.b >>
				intensity >>
				quad3dSize;

			_fe3d->gfx_enableDirectionalLighting();
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
				interval >>
				quality;

			_fe3d->gfx_enableShadows();
			_fe3d->gfx_setShadowEyePosition(position);
			_fe3d->gfx_setShadowCenterPosition(center);
			_fe3d->gfx_setShadowSize(size);
			_fe3d->gfx_setShadowReach(size * 2.0f);
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

			iss >>
				planarHeight >>
				cubeQuality >>
				planarQuality;

			_fe3d->gfx_setPlanarReflectionHeight(planarHeight);
			_fe3d->gfx_setCubeReflectionQuality(cubeQuality);
			_fe3d->gfx_setPlanarReflectionQuality(planarQuality);
		}
		else if(lineType == "GRAPHICS_REFRACTIONS")
		{
			unsigned int planarQuality;

			iss >>
				planarQuality;

			_fe3d->gfx_setPlanarRefractionQuality(planarQuality);
		}
		else if(lineType == "GRAPHICS_DOF")
		{
			bool isDynamic;
			float blurDistance;
			float maxDistance;
			unsigned int quality;

			iss >>
				isDynamic >>
				blurDistance >>
				maxDistance >>
				quality;

			_fe3d->gfx_enableDOF();
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

			iss >> minDistance >> maxDistance >> thickness >> color.r >> color.g >> color.b;

			_fe3d->gfx_enableFog();
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

			iss >> flareMapPath >> intensity >> sensitivity;

			flareMapPath = (flareMapPath == "?") ? "" : flareMapPath;

			replace(flareMapPath.begin(), flareMapPath.end(), '?', ' ');

			if(!Config::getInst().isApplicationExported())
			{
				flareMapPath = string("projects\\" + _currentProjectID + "\\" + flareMapPath);
			}

			_fe3d->gfx_enableLensFlare();
			_fe3d->gfx_setLensFlareMap(flareMapPath);
			_fe3d->gfx_setLensFlareIntensity(intensity);
			_fe3d->gfx_setLensFlareSensitivity(sensitivity);
		}
		else if(lineType == "GRAPHICS_SKY_EXPOSURE")
		{
			float intensity;
			float speed;

			iss >> intensity >> speed;

			_fe3d->gfx_enableSkyExposure();
			_fe3d->gfx_setSkyExposureIntensity(intensity);
			_fe3d->gfx_setSkyExposureSpeed(speed);
		}
		else if(lineType == "GRAPHICS_BLOOM")
		{
			float intensity;
			unsigned int type;
			unsigned int blurCount;
			unsigned int quality;

			iss >>
				type >>
				intensity >>
				blurCount >>
				quality;

			_fe3d->gfx_enableBloom();
			_fe3d->gfx_setBloomType(BloomType(type));
			_fe3d->gfx_setBloomIntensity(intensity);
			_fe3d->gfx_setBloomBlurCount(blurCount);
			_fe3d->gfx_setBloomQuality(quality);
		}
		else
		{
			Logger::throwError("WorldEditor::loadEditorWorldFromFile::2");
		}
	}

	file.close();

	_loadedWorldID = fileName;

	Logger::throwInfo("World editor data loaded!");

	return true;
}