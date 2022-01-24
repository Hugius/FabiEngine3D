#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

const bool WorldEditor::saveEditorWorldToFile()
{
	if(_currentWorldID.empty())
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("WorldEditor::saveEditorWorldToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\worlds\\editor\\" + _currentWorldID + ".fe3d");

	vector<string> levelOfDetailEntityIds;
	for(const auto& modelID : _fe3d->model_getIds())
	{
		if(modelID[0] != '@')
		{
			if(!_fe3d->model_getLevelOfDetailEntityId(modelID).empty())
			{
				if(find(levelOfDetailEntityIds.begin(), levelOfDetailEntityIds.end(), modelID) == levelOfDetailEntityIds.end())
				{
					levelOfDetailEntityIds.push_back(_fe3d->model_getLevelOfDetailEntityId(modelID));
				}
			}
		}
	}

	const auto cameraPosition = _fe3d->camera_getPosition();
	file << "CAMERA_POSITION " << cameraPosition.x << " " << cameraPosition.y << " " << cameraPosition.z << endl;

	file << "CAMERA_YAW " << _fe3d->camera_getYaw() << endl;

	file << "CAMERA_PITCH " << _fe3d->camera_getPitch() << endl;

	string skyID = _fe3d->sky_getSelectedID();
	if(!skyID.empty())
	{
		string templateID = ("@" + skyID);

		file <<
			"SKY " <<
			skyID << " " <<
			templateID << endl;
	}

	string terrainID = _fe3d->terrain_getSelectedID();
	if(!terrainID.empty())
	{
		string templateID = ("@" + terrainID);

		file <<
			"TERRAIN " <<
			terrainID << " " <<
			templateID << endl;
	}

	string waterID = _fe3d->water_getSelectedID();
	if(!waterID.empty())
	{
		string templateID = ("@" + waterID);
		auto height = _fe3d->water_getHeight(waterID);

		file <<
			"WATER " <<
			waterID << " " <<
			templateID << " " <<
			height << endl;
	}

	for(const auto& modelID : _fe3d->model_getIds())
	{
		bool isLevelOfDetailEntity = find(levelOfDetailEntityIds.begin(), levelOfDetailEntityIds.end(), modelID) != levelOfDetailEntityIds.end();
		if((modelID[0] != '@') || isLevelOfDetailEntity)
		{
			auto startedAnimations = _animation3dEditor->getStartedModelAnimationIDs(modelID);

			if(!startedAnimations.empty())
			{
				_fe3d->model_setBasePosition(modelID, _initialModelPosition[modelID]);
				_fe3d->model_setBaseRotationOrigin(modelID, fvec3(0.0f));
				_fe3d->model_setBaseRotation(modelID, _initialModelRotation[modelID]);
				_fe3d->model_setBaseSize(modelID, _initialModelSize[modelID]);

				for(const auto& partId : _fe3d->model_getPartIDs(modelID))
				{
					if(!partId.empty())
					{
						_fe3d->model_setPartPosition(modelID, partId, fvec3(0.0f));
						_fe3d->model_setPartRotationOrigin(modelID, partId, fvec3(0.0f));
						_fe3d->model_setPartRotation(modelID, partId, fvec3(0.0f));
						_fe3d->model_setPartSize(modelID, partId, fvec3(1.0f));
					}
				}
			}

			auto position = _fe3d->model_getBasePosition(modelID);
			auto rotation = _fe3d->model_getBaseRotation(modelID);
			auto size = _fe3d->model_getBaseSize(modelID);
			auto isFrozen = _fe3d->model_isFrozen(modelID);
			auto animationID = (startedAnimations.empty()) ? "" : startedAnimations[0];

			animationID = (animationID.empty()) ? "?" : animationID;

			replace(animationID.begin(), animationID.end(), ' ', '?');

			string templateID = _loadedModelIDs.at(modelID);

			file <<
				"MODEL " <<
				modelID << " " <<
				templateID << " " <<
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
				animationID;

			file << endl;
		}
	}

	for(const auto& quadID : _fe3d->quad3d_getIds())
	{
		if(quadID[0] != '@')
		{
			auto startedAnimations = _animation2dEditor->getStartedQuad3dAnimationIDs(quadID);

			auto position = _fe3d->quad3d_getPosition(quadID);
			auto rotation = _fe3d->quad3d_getRotation(quadID);
			auto size = _fe3d->quad3d_getSize(quadID);
			auto animationID = (startedAnimations.empty() ? "" : startedAnimations[0]);

			animationID = (animationID.empty()) ? "?" : animationID;

			replace(animationID.begin(), animationID.end(), ' ', '?');

			string templateID = _loadedQuadIDs.at(quadID);

			file <<
				"QUAD3D " <<
				quadID << " " <<
				templateID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				rotation.x << " " <<
				rotation.y << " " <<
				rotation.z << " " <<
				size.x << " " <<
				size.y << " " <<
				animationID << endl;
		}
	}

	for(const auto& soundID : _fe3d->sound3d_getIds())
	{
		if(soundID[0] != '@')
		{
			auto position = _fe3d->sound3d_getPosition(soundID);
			auto maxVolume = _fe3d->sound3d_getMaxVolume(soundID);
			auto maxDistance = _fe3d->sound3d_getMaxDistance(soundID);

			string templateID = _loadedSoundIDs.at(soundID);

			file <<
				"SOUND " <<
				soundID << " " <<
				templateID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				maxVolume << " " <<
				maxDistance << endl;
		}
	}

	for(const auto& pointlightID : _fe3d->pointlight_getIds())
	{
		if(pointlightID[0] != '@')
		{
			auto position = _fe3d->pointlight_getPosition(pointlightID);
			auto radius = _fe3d->pointlight_getRadius(pointlightID);
			auto color = _fe3d->pointlight_getColor(pointlightID);
			auto intensity = _fe3d->pointlight_getIntensity(pointlightID);
			auto shape = static_cast<unsigned int>(_fe3d->pointlight_getShape(pointlightID));

			file <<
				"POINTLIGHT " <<
				pointlightID << " " <<
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

	for(const auto& spotlightID : _fe3d->spotlight_getIds())
	{
		if(spotlightID[0] != '@')
		{
			auto position = _fe3d->spotlight_getPosition(spotlightID);
			auto color = _fe3d->spotlight_getColor(spotlightID);
			auto yaw = _fe3d->spotlight_getYaw(spotlightID);
			auto pitch = _fe3d->spotlight_getPitch(spotlightID);
			auto intensity = _fe3d->spotlight_getIntensity(spotlightID);
			auto angle = _fe3d->spotlight_getAngle(spotlightID);
			auto distance = _fe3d->spotlight_getDistance(spotlightID);

			file <<
				"SPOTLIGHT " <<
				spotlightID << " " <<
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

	for(const auto& reflectionID : _fe3d->reflection_getIds())
	{
		if(reflectionID[0] != '@')
		{
			auto position = _fe3d->reflection_getPosition(reflectionID);

			file <<
				"REFLECTION " <<
				reflectionID << " " <<
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
		auto eye = _fe3d->gfx_getShadowEyeOffset();
		auto center = _fe3d->gfx_getShadowCenterOffset();
		auto isFollowingCamera = _fe3d->gfx_isShadowFollowingCamera();
		auto interval = _fe3d->gfx_getShadowInterval();
		auto quality = _fe3d->gfx_getShadowQuality();

		file <<
			"GRAPHICS_SHADOWS " <<
			size << " " <<
			lightness << " " <<
			Tools::vec2str(eye) << " " <<
			Tools::vec2str(center) << " " <<
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
			Tools::vec2str(color) << endl;
	}

	if(_fe3d->gfx_isLensFlareEnabled())
	{
		auto flareMapPath = _fe3d->gfx_getLensFlareMapPath();
		auto intensity = _fe3d->gfx_getLensFlareIntensity();
		auto sensitivity = _fe3d->gfx_getLensFlareSensitivity();

		flareMapPath = string(flareMapPath.empty() ? "" : flareMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

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

	Logger::throwInfo("World editor data saved!");

	return true;
}