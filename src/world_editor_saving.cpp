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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\worlds\\editor\\" + _currentWorldId + ".fe3d");

	auto file = ofstream(filePath);

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
		const auto cameraPosition = _fe3d->camera_getPosition();

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
		const auto cameraYaw = _fe3d->camera_getYaw();

		file
			<< "CAMERA_YAW "
			<< cameraYaw
			<< endl;
	}

	{
		const auto cameraPitch = _fe3d->camera_getPitch();

		file
			<< "CAMERA_PITCH "
			<< cameraPitch
			<< endl;
	}

	{
		const auto placedSkyId = _fe3d->sky_getSelectedId();

		if(!placedSkyId.empty())
		{
			const auto templateSkyId = ("@" + placedSkyId);

			file
				<< "SKY "
				<< placedSkyId
				<< " "
				<< templateSkyId
				<< endl;
		}
	}

	{
		const auto placedTerrainId = _fe3d->terrain_getSelectedId();

		if(!placedTerrainId.empty())
		{
			const auto templateTerrainId = ("@" + placedTerrainId);

			file
				<< "TERRAIN "
				<< placedTerrainId
				<< " "
				<< templateTerrainId
				<< endl;
		}
	}

	{
		const auto placedWaterId = _fe3d->water_getSelectedId();

		if(!placedWaterId.empty())
		{
			const auto templateWaterId = ("@" + placedWaterId);
			const auto height = _fe3d->water_getHeight(placedWaterId);

			file
				<< "WATER "
				<< placedWaterId
				<< " "
				<< templateWaterId
				<< " "
				<< height
				<< endl;
		}
	}

	for(const auto & [placedModelId, templateModelId] : _loadedModelIds)
	{
		const auto startedAnimation3dIds = _fe3d->model_getAnimation3dIds(placedModelId);

		if(!startedAnimation3dIds.empty())
		{
			for(const auto & partId : _fe3d->model_getPartIds(placedModelId))
			{
				if(!partId.empty())
				{
					_fe3d->model_setPartPosition(placedModelId, partId, fvec3(0.0f));
					_fe3d->model_setPartRotationOrigin(placedModelId, partId, fvec3(0.0f));
					_fe3d->model_setPartRotation(placedModelId, partId, fvec3(0.0f));
					_fe3d->model_setPartSize(placedModelId, partId, fvec3(1.0f));
				}
			}
		}

		const auto position = _fe3d->model_getBasePosition(placedModelId);
		const auto rotation = _fe3d->model_getBaseRotation(placedModelId);
		const auto size = _fe3d->model_getBaseSize(placedModelId);
		const auto isFrozen = _fe3d->model_isFrozen(placedModelId);

		auto animation3dId = (startedAnimation3dIds.empty()) ? "" : startedAnimation3dIds[0];

		animation3dId = (animation3dId.empty()) ? "?" : animation3dId;

		replace(animation3dId.begin(), animation3dId.end(), ' ', '?');

		file
			<< "MODEL "
			<< placedModelId
			<< " "
			<< templateModelId
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

	for(const auto & [placedQuad3dId, templateQuad3dId] : _loadedQuad3dIds)
	{
		const auto startedAnimation2dIds = _fe3d->quad3d_getAnimation2dIds(placedQuad3dId);
		const auto position = _fe3d->quad3d_getPosition(placedQuad3dId);
		const auto rotation = _fe3d->quad3d_getRotation(placedQuad3dId);
		const auto size = _fe3d->quad3d_getSize(placedQuad3dId);

		auto animation2dId = (startedAnimation2dIds.empty() ? "" : startedAnimation2dIds[0]);

		animation2dId = (animation2dId.empty()) ? "?" : animation2dId;

		replace(animation2dId.begin(), animation2dId.end(), ' ', '?');

		file
			<< "QUAD3D "
			<< placedQuad3dId
			<< " "
			<< templateQuad3dId
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

	for(const auto & [placedText3dId, templateText3dId] : _loadedText3dIds)
	{
		const auto content = _fe3d->text3d_getContent(placedText3dId);
		const auto position = _fe3d->text3d_getPosition(placedText3dId);
		const auto rotation = _fe3d->text3d_getRotation(placedText3dId);
		const auto size = _fe3d->text3d_getSize(placedText3dId);

		file
			<< "TEXT3D "
			<< placedText3dId
			<< " "
			<< templateText3dId
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

	for(const auto & [placedAabbId, templateAabbId] : _loadedAabbIds)
	{
		const auto position = _fe3d->aabb_getBasePosition(placedAabbId);
		const auto size = _fe3d->aabb_getBaseSize(placedAabbId);

		file
			<< "AABB "
			<< placedAabbId
			<< " "
			<< templateAabbId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< size.z
			<< " "
			<< endl;
	}

	for(const auto & [placedPointlightId, templatePointlightId] : _loadedPointlightIds)
	{
		const auto position = _fe3d->pointlight_getPosition(placedPointlightId);

		file
			<< "POINTLIGHT "
			<< placedPointlightId
			<< " "
			<< templatePointlightId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< endl;
	}

	for(const auto & [placedSpotlightId, templateSpotlightId] : _loadedSpotlightIds)
	{
		const auto position = _fe3d->spotlight_getPosition(placedSpotlightId);
		const auto yaw = _fe3d->spotlight_getYaw(placedSpotlightId);
		const auto pitch = _fe3d->spotlight_getPitch(placedSpotlightId);

		file
			<< "SPOTLIGHT "
			<< placedSpotlightId
			<< " "
			<< templateSpotlightId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< " "
			<< yaw
			<< " "
			<< pitch
			<< endl;
	}

	for(const auto & [placedSound3dId, templateSound3dId] : _loadedSound3dIds)
	{
		const auto position = _fe3d->sound3d_getPosition(placedSound3dId);

		file
			<< "SOUND3D "
			<< placedSound3dId
			<< " "
			<< templateSound3dId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< endl;
	}

	for(const auto & placedCaptorId : _loadedCaptorIds)
	{
		const auto position = _fe3d->captor_getPosition(placedCaptorId);
		const auto exceptionId = _fe3d->captor_getExceptionId(placedCaptorId);

		file
			<< "CAPTOR "
			<< placedCaptorId
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
		const auto ambientLightingColor = _fe3d->graphics_getAmbientLightingColor();
		const auto ambientLightingIntensity = _fe3d->graphics_getAmbientLightingIntensity();

		file
			<< "GRAPHICS_AMBIENT_LIGHTING "
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
		const auto directionalLightingColor = _fe3d->graphics_getDirectionalLightingColor();
		const auto directionalLightingPosition = _fe3d->graphics_getDirectionalLightingPosition();
		const auto directionalLightingIntensity = _fe3d->graphics_getDirectionalLightingIntensity();

		file
			<< "GRAPHICS_DIRECTIONAL_LIGHTING "
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
		const auto size = _fe3d->graphics_getShadowSize();
		const auto lightness = _fe3d->graphics_getShadowLightness();
		const auto position = _fe3d->graphics_getShadowPositionOffset();
		const auto lookat = _fe3d->graphics_getShadowLookatOffset();
		const auto isFollowingCameraX = _fe3d->graphics_isShadowFollowingCameraX();
		const auto isFollowingCameraY = _fe3d->graphics_isShadowFollowingCameraY();
		const auto isFollowingCameraZ = _fe3d->graphics_isShadowFollowingCameraZ();
		const auto interval = _fe3d->graphics_getShadowInterval();
		const auto quality = _fe3d->graphics_getShadowQuality();

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
			<< isFollowingCameraX
			<< " "
			<< isFollowingCameraY
			<< " "
			<< isFollowingCameraZ
			<< " "
			<< interval
			<< " "
			<< quality
			<< endl;
	}

	{
		const auto cubeInterval = _fe3d->graphics_getCubeReflectionInterval();
		const auto cubeQuality = _fe3d->graphics_getCubeReflectionQuality();
		const auto planarHeight = _fe3d->graphics_getPlanarReflectionHeight();
		const auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_REFLECTIONS "
			<< cubeInterval
			<< " "
			<< cubeQuality
			<< " "
			<< planarHeight
			<< " "
			<< planarQuality
			<< endl;
	}

	{
		const auto cubeInterval = _fe3d->graphics_getCubeReflectionInterval();
		const auto cubeQuality = _fe3d->graphics_getCubeReflectionQuality();
		const auto planarHeight = _fe3d->graphics_getPlanarRefractionHeight();
		const auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_REFRACTIONS "
			<< cubeInterval
			<< " "
			<< cubeQuality
			<< " "
			<< planarHeight
			<< " "
			<< planarQuality
			<< endl;
	}

	if(_fe3d->graphics_isDofEnabled())
	{
		const auto dynamic = _fe3d->graphics_isDofDynamic();
		const auto blurDistance = _fe3d->graphics_getDofBlurDistance();
		const auto maxDistance = _fe3d->graphics_getDofDynamicDistance();
		const auto quality = _fe3d->graphics_getDofQuality();

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
		const auto minDistance = _fe3d->graphics_getFogMinDistance();
		const auto maxDistance = _fe3d->graphics_getFogMaxDistance();
		const auto thickness = _fe3d->graphics_getFogThickness();
		const auto color = _fe3d->graphics_getFogColor();

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
		const auto intensity = _fe3d->graphics_getLensFlareIntensity();
		const auto sensitivity = _fe3d->graphics_getLensFlareSensitivity();

		auto flareMapPath = _fe3d->graphics_getLensFlareMapPath();

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
		const auto intensity = _fe3d->graphics_getSkyExposureIntensity();
		const auto speed = _fe3d->graphics_getSkyExposureSpeed();

		file
			<< "GRAPHICS_SKY_EXPOSURE "
			<< intensity
			<< " "
			<< speed
			<< endl;
	}

	if(_fe3d->graphics_isBloomEnabled())
	{
		const auto type = static_cast<int>(_fe3d->graphics_getBloomType());
		const auto intensity = _fe3d->graphics_getBloomIntensity();
		const auto blurCount = _fe3d->graphics_getBloomBlurCount();
		const auto quality = _fe3d->graphics_getBloomQuality();

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