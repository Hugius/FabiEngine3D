#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

const bool WorldEditor::saveWorldToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		abort();
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\worlds\\editor\\" + _currentWorldId + ".fe3d");

	{
		file
			<< "ID_COUNTER "
			<< _idCounter
			<< endl;
	}

	{
		file
			<< "EDITOR_SPEED "
			<< _editorSpeed
			<< endl;
	}

	{
		auto cameraPosition = _fe3d->camera_getPosition();

		file
			<< "CAMERA_POSITION "
			<< cameraPosition.x
			<< " "
			<< cameraPosition.y
			<< " "
			<< cameraPosition.z
			<< endl;
	}

	{
		auto cameraYaw = _fe3d->camera_getYaw();

		file
			<< "CAMERA_YAW "
			<< cameraYaw
			<< endl;
	}

	{
		auto cameraPitch = _fe3d->camera_getPitch();

		file
			<< "CAMERA_PITCH "
			<< cameraPitch
			<< endl;
	}

	{
		auto skyId = _fe3d->sky_getSelectedId();
		auto templateId = ("@" + skyId);

		if(!skyId.empty())
		{
			file
				<< "SKY "
				<< skyId
				<< " "
				<< templateId
				<< endl;
		}
	}

	{
		auto terrainId = _fe3d->terrain_getSelectedId();
		auto templateId = ("@" + terrainId);

		if(!terrainId.empty())
		{
			file
				<< "TERRAIN "
				<< terrainId
				<< " "
				<< templateId
				<< endl;
		}
	}

	{
		auto waterId = _fe3d->water_getSelectedId();
		auto templateId = ("@" + waterId);
		auto height = _fe3d->water_getHeight(waterId);

		if(!waterId.empty())
		{
			file
				<< "WATER "
				<< waterId
				<< " "
				<< templateId
				<< " "
				<< height
				<< endl;
		}
	}

	for(const auto & [modelId, templateId] : _loadedModelIds)
	{
		auto startedAnimation3dIds = _fe3d->model_getAnimationIds(modelId);

		if(!startedAnimation3dIds.empty())
		{
			for(const auto & partId : _fe3d->model_getPartIds(modelId))
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
		auto animation3dId = (startedAnimation3dIds.empty()) ? "" : startedAnimation3dIds[0];

		animation3dId = (animation3dId.empty()) ? "?" : animation3dId;

		replace(animation3dId.begin(), animation3dId.end(), ' ', '?');

		file
			<< "MODEL "
			<< modelId
			<< " "
			<< templateId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< size.z
			<< " "
			<< isFrozen
			<< " "
			<< animation3dId;

		file << endl;
	}

	for(const auto & [quad3dId, templateId] : _loadedQuad3dIds)
	{
		auto startedAnimation2dIds = _fe3d->quad3d_getAnimationIds(quad3dId);
		auto position = _fe3d->quad3d_getPosition(quad3dId);
		auto rotation = _fe3d->quad3d_getRotation(quad3dId);
		auto size = _fe3d->quad3d_getSize(quad3dId);
		auto animation2dId = (startedAnimation2dIds.empty() ? "" : startedAnimation2dIds[0]);

		animation2dId = (animation2dId.empty()) ? "?" : animation2dId;

		replace(animation2dId.begin(), animation2dId.end(), ' ', '?');

		file
			<< "QUAD3D "
			<< quad3dId
			<< " "
			<< templateId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< animation2dId
			<< endl;
	}

	for(const auto & [text3dId, templateId] : _loadedText3dIds)
	{
		auto content = _fe3d->text3d_getContent(text3dId);
		auto position = _fe3d->text3d_getPosition(text3dId);
		auto rotation = _fe3d->text3d_getRotation(text3dId);
		auto size = _fe3d->text3d_getSize(text3dId);

		file
			<< "TEXT3D "
			<< text3dId
			<< " "
			<< templateId
			<< " "
			<< content
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< rotation.x
			<< " "
			<< rotation.y
			<< " "
			<< rotation.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< endl;
	}

	for(const auto & [soundId, templateId] : _loadedSoundIds)
	{
		auto position = _fe3d->sound3d_getPosition(soundId);
		auto maxVolume = _fe3d->sound3d_getMaxVolume(soundId);
		auto maxDistance = _fe3d->sound3d_getMaxDistance(soundId);

		file
			<< "SOUND "
			<< soundId
			<< " "
			<< templateId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< maxVolume
			<< " "
			<< maxDistance
			<< endl;
	}

	for(const auto & pointlightId : _loadedPointlightIds)
	{
		auto position = _fe3d->pointlight_getPosition(pointlightId);
		auto radius = _fe3d->pointlight_getRadius(pointlightId);
		auto color = _fe3d->pointlight_getColor(pointlightId);
		auto intensity = _fe3d->pointlight_getIntensity(pointlightId);
		auto shape = static_cast<int>(_fe3d->pointlight_getShape(pointlightId));

		file
			<< "POINTLIGHT "
			<< pointlightId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< radius.x
			<< " "
			<< radius.y
			<< " "
			<< radius.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< intensity
			<< " "
			<< shape
			<< endl;
	}

	for(const auto & spotlightId : _loadedSpotlightIds)
	{
		auto position = _fe3d->spotlight_getPosition(spotlightId);
		auto color = _fe3d->spotlight_getColor(spotlightId);
		auto yaw = _fe3d->spotlight_getYaw(spotlightId);
		auto pitch = _fe3d->spotlight_getPitch(spotlightId);
		auto intensity = _fe3d->spotlight_getIntensity(spotlightId);
		auto angle = _fe3d->spotlight_getAngle(spotlightId);
		auto distance = _fe3d->spotlight_getDistance(spotlightId);

		file
			<< "SPOTLIGHT "
			<< spotlightId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< yaw
			<< " "
			<< pitch
			<< " "
			<< intensity
			<< " "
			<< angle
			<< " "
			<< distance
			<< endl;
	}

	for(const auto & captorId : _loadedCaptorIds)
	{
		auto position = _fe3d->captor_getPosition(captorId);
		auto exceptionId = _fe3d->captor_getExceptionId(captorId);

		file
			<< "CAPTOR "
			<< captorId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< exceptionId
			<< endl;
	}

	if(_fe3d->graphics_isAmbientLightingEnabled())
	{
		auto ambientLightingColor = _fe3d->graphics_getAmbientLightingColor();
		auto ambientLightingIntensity = _fe3d->graphics_getAmbientLightingIntensity();

		file
			<< "LIGHTING_AMBIENT "
			<< ambientLightingColor.r
			<< " "
			<< ambientLightingColor.g
			<< " "
			<< ambientLightingColor.b
			<< " "
			<< ambientLightingIntensity
			<< endl;
	}

	if(_fe3d->graphics_isDirectionalLightingEnabled())
	{
		auto directionalLightingColor = _fe3d->graphics_getDirectionalLightingColor();
		auto directionalLightingPosition = _fe3d->graphics_getDirectionalLightingPosition();
		auto directionalLightingIntensity = _fe3d->graphics_getDirectionalLightingIntensity();

		file
			<< "LIGHTING_DIRECTIONAL "
			<< directionalLightingPosition.x
			<< " "
			<< directionalLightingPosition.y
			<< " "
			<< directionalLightingPosition.z
			<< " "
			<< directionalLightingColor.r
			<< " "
			<< directionalLightingColor.g
			<< " "
			<< directionalLightingColor.b
			<< " "
			<< directionalLightingIntensity
			<< endl;
	}

	if(_fe3d->graphics_isShadowsEnabled())
	{
		auto size = _fe3d->graphics_getShadowSize();
		auto lightness = _fe3d->graphics_getShadowLightness();
		auto position = _fe3d->graphics_getShadowPositionOffset();
		auto lookat = _fe3d->graphics_getShadowLookatOffset();
		auto isFollowingCamera = _fe3d->graphics_isShadowFollowingCamera();
		auto interval = _fe3d->graphics_getShadowInterval();
		auto quality = _fe3d->graphics_getShadowQuality();

		file
			<< "GRAPHICS_SHADOWS "
			<< size
			<< " "
			<< lightness
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< lookat.x
			<< " "
			<< lookat.y
			<< " "
			<< lookat.z
			<< " "
			<< isFollowingCamera
			<< " "
			<< interval
			<< " "
			<< quality
			<< endl;
	}

	{
		auto planarHeight = _fe3d->graphics_getPlanarReflectionHeight();
		auto cubeQuality = _fe3d->graphics_getCubeReflectionQuality();
		auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_REFLECTIONS "
			<< planarHeight
			<< " "
			<< cubeQuality
			<< " "
			<< planarQuality
			<< endl;
	}

	{
		auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_REFRACTIONS "
			<< planarQuality
			<< endl;
	}

	if(_fe3d->graphics_isDofEnabled())
	{
		auto dynamic = _fe3d->graphics_isDofDynamic();
		auto blurDistance = _fe3d->graphics_getDofBlurDistance();
		auto maxDistance = _fe3d->graphics_getDofDynamicDistance();
		auto quality = _fe3d->graphics_getDofQuality();

		file
			<< "GRAPHICS_DOF "
			<< dynamic
			<< " "
			<< blurDistance
			<< " "
			<< maxDistance
			<< " "
			<< quality
			<< endl;
	}

	if(_fe3d->graphics_isFogEnabled())
	{
		auto minDistance = _fe3d->graphics_getFogMinDistance();
		auto maxDistance = _fe3d->graphics_getFogMaxDistance();
		auto thickness = _fe3d->graphics_getFogThickness();
		auto color = _fe3d->graphics_getFogColor();

		file
			<< "GRAPHICS_FOG "
			<< minDistance
			<< " "
			<< maxDistance
			<< " "
			<< thickness
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< endl;
	}

	if(_fe3d->graphics_isLensFlareEnabled())
	{
		auto flareMapPath = _fe3d->graphics_getLensFlareMapPath();
		auto intensity = _fe3d->graphics_getLensFlareIntensity();
		auto sensitivity = _fe3d->graphics_getLensFlareSensitivity();

		flareMapPath = (flareMapPath.empty() ? "" : flareMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));

		flareMapPath = (flareMapPath.empty()) ? "?" : flareMapPath;

		replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');

		file
			<< "GRAPHICS_LENS_FLARE "
			<< flareMapPath
			<< " "
			<< intensity
			<< " "
			<< sensitivity
			<< endl;
	}

	if(_fe3d->graphics_isSkyExposureEnabled())
	{
		file
			<< "GRAPHICS_SKY_EXPOSURE "
			<< _fe3d->graphics_getSkyExposureIntensity()
			<< " "
			<< _fe3d->graphics_getSkyExposureSpeed()
			<< endl;
	}

	if(_fe3d->graphics_isBloomEnabled())
	{
		auto type = static_cast<int>(_fe3d->graphics_getBloomType());
		auto intensity = _fe3d->graphics_getBloomIntensity();
		auto blurCount = _fe3d->graphics_getBloomBlurCount();
		auto quality = _fe3d->graphics_getBloomQuality();

		file
			<< "GRAPHICS_BLOOM "
			<< type
			<< " "
			<< intensity
			<< " "
			<< blurCount
			<< " "
			<< quality
			<< endl;
	}

	file.close();

	Logger::throwInfo("World editor data saved");

	return true;
}