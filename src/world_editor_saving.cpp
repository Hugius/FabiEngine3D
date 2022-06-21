#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

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
			<< "MODEL_ID_COUNTER "
			<< _modelIdCounter
			<< endl;
	}

	{
		file
			<< "QUAD3D_ID_COUNTER "
			<< _quad3dIdCounter
			<< endl;
	}

	{
		file
			<< "TEXT3D_ID_COUNTER "
			<< _text3dIdCounter
			<< endl;
	}

	{
		file
			<< "AABB_ID_COUNTER "
			<< _aabbIdCounter
			<< endl;
	}

	{
		file
			<< "POINTLIGHT_ID_COUNTER "
			<< _pointlightIdCounter
			<< endl;
	}

	{
		file
			<< "SPOTLIGHT_ID_COUNTER "
			<< _spotlightIdCounter
			<< endl;
	}

	{
		file
			<< "CAPTOR_ID_COUNTER "
			<< _captorIdCounter
			<< endl;
	}

	{
		file
			<< "SOUND3D_ID_COUNTER "
			<< _sound3dIdCounter
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
		const auto skyId = _fe3d->sky_getSelectedId();

		if(!skyId.empty())
		{
			const auto templateSkyId = _duplicator->getTemplateSkyId(skyId);

			file
				<< "SKY "
				<< skyId
				<< " "
				<< templateSkyId
				<< endl;
		}
	}

	{
		const auto terrainId = _fe3d->terrain_getSelectedId();

		if(!terrainId.empty())
		{
			const auto templateTerrainId = _duplicator->getTemplateTerrainId(terrainId);

			file
				<< "TERRAIN "
				<< terrainId
				<< " "
				<< templateTerrainId
				<< endl;
		}
	}

	{
		const auto waterId = _fe3d->water_getSelectedId();

		if(!waterId.empty())
		{
			const auto templateWaterId = _duplicator->getTemplateWaterId(waterId);
			const auto height = _fe3d->water_getHeight(waterId);

			file
				<< "WATER "
				<< waterId
				<< " "
				<< templateWaterId
				<< " "
				<< height
				<< endl;
		}
	}

	for(const auto & modelId : _loadedModelIds)
	{
		const auto templateModelId = _duplicator->getTemplateModelId(modelId);
		const auto animation3dIds = _fe3d->model_getAnimation3dIds(modelId);
		const auto animation3dCount = animation3dIds.size();
		const auto position = _originalModelPositions.at(modelId);
		const auto rotation = _originalModelRotations.at(modelId);
		const auto size = _originalModelSizes.at(modelId);

		file
			<< "MODEL "
			<< modelId
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
			<< animation3dCount;

		for(const auto & animation3dId : animation3dIds)
		{
			file
				<< " "
				<< animation3dId;
		}

		file << endl;
	}

	for(const auto & quad3dId : _loadedQuad3dIds)
	{
		const auto templateQuad3dId = _duplicator->getTemplateQuad3dId(quad3dId);
		const auto position = _fe3d->quad3d_getPosition(quad3dId);
		const auto rotation = _fe3d->quad3d_getRotation(quad3dId);
		const auto size = _fe3d->quad3d_getSize(quad3dId);

		auto animation2dId = _fe3d->quad3d_getAnimation2dId(quad3dId);

		animation2dId = (animation2dId.empty()) ? "?" : animation2dId;

		file
			<< "QUAD3D "
			<< quad3dId
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

	for(const auto & text3dId : _loadedText3dIds)
	{
		const auto templateText3dId = _duplicator->getTemplateText3dId(text3dId);
		const auto content = _fe3d->text3d_getContent(text3dId);
		const auto position = _fe3d->text3d_getPosition(text3dId);
		const auto rotation = _fe3d->text3d_getRotation(text3dId);
		const auto size = _fe3d->text3d_getSize(text3dId);

		file
			<< "TEXT3D "
			<< text3dId
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

	for(const auto & aabbId : _loadedAabbIds)
	{
		const auto templateAabbId = _duplicator->getTemplateAabbId(aabbId);
		const auto position = _fe3d->aabb_getBasePosition(aabbId);
		const auto size = _fe3d->aabb_getBaseSize(aabbId);

		file
			<< "AABB "
			<< aabbId
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

	for(const auto & pointlightId : _loadedPointlightIds)
	{
		const auto templatePointlightId = _duplicator->getTemplatePointlightId(pointlightId);
		const auto position = _fe3d->pointlight_getPosition(pointlightId);

		file
			<< "POINTLIGHT "
			<< pointlightId
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

	for(const auto & spotlightId : _loadedSpotlightIds)
	{
		const auto templateSpotlightId = _duplicator->getTemplateSpotlightId(spotlightId);
		const auto position = _fe3d->spotlight_getPosition(spotlightId);
		const auto yaw = _fe3d->spotlight_getYaw(spotlightId);
		const auto pitch = _fe3d->spotlight_getPitch(spotlightId);

		file
			<< "SPOTLIGHT "
			<< spotlightId
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

	for(const auto & captorId : _loadedCaptorIds)
	{
		const auto templateCaptorId = _duplicator->getTemplateCaptorId(captorId);
		const auto position = _fe3d->captor_getPosition(captorId);

		auto exceptionId = _fe3d->captor_getExceptionId(captorId);

		exceptionId = (exceptionId.empty()) ? "?" : exceptionId;

		file
			<< "CAPTOR "
			<< captorId
			<< " "
			<< templateCaptorId
			<< " "
			<< exceptionId
			<< " "
			<< position.x
			<< " "
			<< position.y
			<< " "
			<< position.z
			<< endl;
	}

	for(const auto & sound3dId : _loadedSound3dIds)
	{
		const auto templateSound3dId = _duplicator->getTemplateSound3dId(sound3dId);
		const auto position = _fe3d->sound3d_getPosition(sound3dId);

		file
			<< "SOUND3D "
			<< sound3dId
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
		const auto pcfCount = _fe3d->graphics_getShadowPcfCount();
		const auto quality = _fe3d->graphics_getShadowQuality();
		const auto bias = _fe3d->graphics_getShadowBias();

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
			<< pcfCount
			<< " "
			<< quality
			<< " "
			<< bias
			<< endl;
	}

	{
		const auto planarHeight = _fe3d->graphics_getPlanarReflectionHeight();
		const auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_REFLECTIONS "
			<< planarHeight
			<< " "
			<< planarQuality
			<< endl;
	}

	{
		const auto planarHeight = _fe3d->graphics_getPlanarRefractionHeight();
		const auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		file
			<< "GRAPHICS_REFRACTIONS "
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

	Logger::throwInfo("Editor world data saved");

	return true;
}