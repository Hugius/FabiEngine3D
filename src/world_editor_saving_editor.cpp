#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

const bool WorldEditor::saveEditorWorldToFile()
{
	if(_currentWorldId.empty())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		abort();
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + getCurrentProjectId() + "\\worlds\\editor\\" + _currentWorldId + ".fe3d");

	vector<string> levelOfDetailEntityIds;
	for(const auto& modelId : _fe3d->model_getIds())
	{
		if(modelId[0] != '@')
		{
			if(!_fe3d->model_getLevelOfDetailEntityId(modelId).empty())
			{
				if(find(levelOfDetailEntityIds.begin(), levelOfDetailEntityIds.end(), modelId) == levelOfDetailEntityIds.end())
				{
					levelOfDetailEntityIds.push_back(_fe3d->model_getLevelOfDetailEntityId(modelId));
				}
			}
		}
	}

	const auto cameraPosition = _fe3d->camera_getPosition();
	file << "CAMERA_POSITION " << cameraPosition.x << " " << cameraPosition.y << " " << cameraPosition.z << endl;

	file << "CAMERA_YAW " << _fe3d->camera_getYaw() << endl;

	file << "CAMERA_PITCH " << _fe3d->camera_getPitch() << endl;

	string skyId = _fe3d->sky_getSelectedId();
	if(!skyId.empty())
	{
		string templateId = ("@" + skyId);

		file <<
			"SKY " <<
			skyId << " " <<
			templateId << endl;
	}

	string terrainId = _fe3d->terrain_getSelectedId();
	if(!terrainId.empty())
	{
		string templateId = ("@" + terrainId);

		file <<
			"TERRAIN " <<
			terrainId << " " <<
			templateId << endl;
	}

	string waterId = _fe3d->water_getSelectedId();
	if(!waterId.empty())
	{
		string templateId = ("@" + waterId);
		auto height = _fe3d->water_getHeight(waterId);

		file <<
			"WATER " <<
			waterId << " " <<
			templateId << " " <<
			height << endl;
	}

	for(const auto& modelId : _fe3d->model_getIds())
	{
		bool isLevelOfDetailEntity = find(levelOfDetailEntityIds.begin(), levelOfDetailEntityIds.end(), modelId) != levelOfDetailEntityIds.end();
		if((modelId[0] != '@') || isLevelOfDetailEntity)
		{
			auto startedAnimations = _animation3dEditor->getStartedModelAnimationIds(modelId);

			if(!startedAnimations.empty())
			{
				_fe3d->model_setBasePosition(modelId, _initialModelPosition[modelId]);
				_fe3d->model_setBaseRotationOrigin(modelId, fvec3(0.0f));
				_fe3d->model_setBaseRotation(modelId, _initialModelRotation[modelId]);
				_fe3d->model_setBaseSize(modelId, _initialModelSize[modelId]);

				for(const auto& partId : _fe3d->model_getPartIds(modelId))
				{
					if(!partId.empty())
					{
						_fe3d->model_setPartPosition(modelId, partId, fvec3(0.0f));
						_fe3d->model_setPartRotationOrigin(modelId, partId, fvec3(0.0f));
						_fe3d->model_setPartRotation(modelId, partId, fvec3(0.0f));
						_fe3d->model_setPartSize(modelId, partId, fvec3(1.0f));
					}
				}
			}

			auto position = _fe3d->model_getBasePosition(modelId);
			auto rotation = _fe3d->model_getBaseRotation(modelId);
			auto size = _fe3d->model_getBaseSize(modelId);
			auto isFrozen = _fe3d->model_isFrozen(modelId);
			auto animationId = (startedAnimations.empty()) ? "" : startedAnimations[0];

			animationId = (animationId.empty()) ? "?" : animationId;

			replace(animationId.begin(), animationId.end(), ' ', '?');

			string templateId = _loadedModelIds.at(modelId);

			file <<
				"MODEL " <<
				modelId << " " <<
				templateId << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				rotation.x << " " <<
				rotation.y << " " <<
				rotation.z << " " <<
				size.x << " " <<
				size.y << " " <<
				size.z << " " <<
				isFrozen << " " <<
				animationId;

			file << endl;
		}
	}

	for(const auto& quadId : _fe3d->quad3d_getIds())
	{
		if(quadId[0] != '@')
		{
			auto startedAnimations = _animation2dEditor->getStartedQuad3dAnimationIds(quadId);

			auto position = _fe3d->quad3d_getPosition(quadId);
			auto rotation = _fe3d->quad3d_getRotation(quadId);
			auto size = _fe3d->quad3d_getSize(quadId);
			auto animationId = (startedAnimations.empty() ? "" : startedAnimations[0]);

			animationId = (animationId.empty()) ? "?" : animationId;

			replace(animationId.begin(), animationId.end(), ' ', '?');

			string templateId = _loadedQuadIds.at(quadId);

			file <<
				"QUAD3D " <<
				quadId << " " <<
				templateId << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				rotation.x << " " <<
				rotation.y << " " <<
				rotation.z << " " <<
				size.x << " " <<
				size.y << " " <<
				animationId << endl;
		}
	}

	for(const auto& soundId : _fe3d->sound3d_getIds())
	{
		if(soundId[0] != '@')
		{
			auto position = _fe3d->sound3d_getPosition(soundId);
			auto maxVolume = _fe3d->sound3d_getMaxVolume(soundId);
			auto maxDistance = _fe3d->sound3d_getMaxDistance(soundId);

			string templateId = _loadedSoundIds.at(soundId);

			file <<
				"SOUND " <<
				soundId << " " <<
				templateId << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				maxVolume << " " <<
				maxDistance << endl;
		}
	}

	for(const auto& pointlightId : _fe3d->pointlight_getIds())
	{
		if(pointlightId[0] != '@')
		{
			auto position = _fe3d->pointlight_getPosition(pointlightId);
			auto radius = _fe3d->pointlight_getRadius(pointlightId);
			auto color = _fe3d->pointlight_getColor(pointlightId);
			auto intensity = _fe3d->pointlight_getIntensity(pointlightId);
			auto shape = static_cast<unsigned int>(_fe3d->pointlight_getShape(pointlightId));

			file <<
				"POINTLIGHT " <<
				pointlightId << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				radius.x << " " <<
				radius.y << " " <<
				radius.z << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				intensity << " " <<
				shape << endl;
		}
	}

	for(const auto& spotlightId : _fe3d->spotlight_getIds())
	{
		if(spotlightId[0] != '@')
		{
			auto position = _fe3d->spotlight_getPosition(spotlightId);
			auto color = _fe3d->spotlight_getColor(spotlightId);
			auto yaw = _fe3d->spotlight_getYaw(spotlightId);
			auto pitch = _fe3d->spotlight_getPitch(spotlightId);
			auto intensity = _fe3d->spotlight_getIntensity(spotlightId);
			auto angle = _fe3d->spotlight_getAngle(spotlightId);
			auto distance = _fe3d->spotlight_getDistance(spotlightId);

			file <<
				"SPOTLIGHT " <<
				spotlightId << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				yaw << " " <<
				pitch << " " <<
				intensity << " " <<
				angle << " " <<
				distance << endl;
		}
	}

	for(const auto& reflectionId : _fe3d->reflection_getIds())
	{
		if(reflectionId[0] != '@')
		{
			auto position = _fe3d->reflection_getPosition(reflectionId);

			file <<
				"REFLECTION " <<
				reflectionId << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << endl;
		}
	}

	{
		file <<
			"EDITOR_SPEED " <<
			_editorSpeed << endl;
	}

	if(_fe3d->gfx_isAmbientLightingEnabled())
	{
		auto ambientLightingColor = _fe3d->gfx_getAmbientLightingColor();
		auto ambientLightingIntensity = _fe3d->gfx_getAmbientLightingIntensity();

		file <<
			"LIGHTING_AMBIENT " <<
			ambientLightingColor.r << " " <<
			ambientLightingColor.g << " " <<
			ambientLightingColor.b << " " <<
			ambientLightingIntensity << endl;
	}

	if(_fe3d->gfx_isDirectionalLightingEnabled())
	{
		auto directionalLightingColor = _fe3d->gfx_getDirectionalLightingColor();
		auto directionalLightingPosition = _fe3d->gfx_getDirectionalLightingPosition();
		auto directionalLightingIntensity = _fe3d->gfx_getDirectionalLightingIntensity();

		file <<
			"LIGHTING_DIRECTIONAL " <<
			directionalLightingPosition.x << " " <<
			directionalLightingPosition.y << " " <<
			directionalLightingPosition.z << " " <<
			directionalLightingColor.r << " " <<
			directionalLightingColor.g << " " <<
			directionalLightingColor.b << " " <<
			directionalLightingIntensity << endl;
	}

	if(_fe3d->gfx_isShadowsEnabled())
	{
		auto size = _fe3d->gfx_getShadowSize();
		auto lightness = _fe3d->gfx_getShadowLightness();
		auto position = _fe3d->gfx_getShadowPositionOffset();
		auto lookat = _fe3d->gfx_getShadowLookatOffset();
		auto isFollowingCamera = _fe3d->gfx_isShadowFollowingCamera();
		auto interval = _fe3d->gfx_getShadowInterval();
		auto quality = _fe3d->gfx_getShadowQuality();

		file <<
			"GRAPHICS_SHADOWS " <<
			size << " " <<
			lightness << " " <<
			position.x << " " <<
			position.y << " " <<
			position.z << " " <<
			lookat.x << " " <<
			lookat.y << " " <<
			lookat.z << " " <<
			isFollowingCamera << " " <<
			interval << " " <<
			quality << endl;
	}

	{
		auto planarHeight = _fe3d->gfx_getPlanarReflectionHeight();
		auto cubeQuality = _fe3d->gfx_getCubeReflectionQuality();
		auto planarQuality = _fe3d->gfx_getPlanarReflectionQuality();

		file <<
			"GRAPHICS_REFLECTIONS " <<
			planarHeight << " " <<
			cubeQuality << " " <<
			planarQuality << endl;
	}

	{
		auto planarQuality = _fe3d->gfx_getPlanarReflectionQuality();

		file <<
			"GRAPHICS_REFRACTIONS " <<
			planarQuality << endl;
	}

	if(_fe3d->gfx_isDofEnabled())
	{
		auto dynamic = _fe3d->gfx_isDofDynamic();
		auto blurDistance = _fe3d->gfx_getDofBlurDistance();
		auto maxDistance = _fe3d->gfx_getDofDynamicDistance();
		auto quality = _fe3d->gfx_getDofQuality();

		file <<
			"GRAPHICS_DOF " <<
			dynamic << " " <<
			blurDistance << " " <<
			maxDistance << " " <<
			quality << endl;
	}

	if(_fe3d->gfx_isFogEnabled())
	{
		auto minDistance = _fe3d->gfx_getFogMinDistance();
		auto maxDistance = _fe3d->gfx_getFogMaxDistance();
		auto thickness = _fe3d->gfx_getFogThickness();
		auto color = _fe3d->gfx_getFogColor();

		file <<
			"GRAPHICS_FOG " <<
			minDistance << " " <<
			maxDistance << " " <<
			thickness << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << endl;
	}

	if(_fe3d->gfx_isLensFlareEnabled())
	{
		auto flareMapPath = _fe3d->gfx_getLensFlareMapPath();
		auto intensity = _fe3d->gfx_getLensFlareIntensity();
		auto sensitivity = _fe3d->gfx_getLensFlareSensitivity();

		flareMapPath = string(flareMapPath.empty() ? "" : flareMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));

		flareMapPath = (flareMapPath.empty()) ? "?" : flareMapPath;

		replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

		file <<
			"GRAPHICS_LENS_FLARE " <<
			flareMapPath << " " <<
			intensity << " " <<
			sensitivity << endl;
	}

	if(_fe3d->gfx_isSkyExposureEnabled())
	{
		file <<
			"GRAPHICS_SKY_EXPOSURE " <<
			_fe3d->gfx_getSkyExposureIntensity() << " "
			<< _fe3d->gfx_getSkyExposureSpeed() << endl;
	}

	if(_fe3d->gfx_isBloomEnabled())
	{
		auto type = static_cast<unsigned int>(_fe3d->gfx_getBloomType());
		auto intensity = _fe3d->gfx_getBloomIntensity();
		auto blurCount = _fe3d->gfx_getBloomBlurCount();
		auto quality = _fe3d->gfx_getBloomQuality();

		file <<
			"GRAPHICS_BLOOM " <<
			type << " " <<
			intensity << " " <<
			blurCount << " " <<
			quality << endl;
	}

	file.close();

	Logger::throwInfo("World editor data saved");

	return true;
}