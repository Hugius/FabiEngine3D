#include "custom_world_builder.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "logger.hpp"

#include <sstream>

using std::istringstream;

const bool CustomWorldBuilder::loadWorldFromFile(const string & fileName)
{
	if(!Configuration::getInst().isApplicationExported() && _currentProjectId.empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "worlds\\custom\\" + fileName + ".fe3d");

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

		if(lineType == "SKY")
		{
			array<string, 6> cubeMapPaths{};
			string placedSkyId;
			string templateSkyId;
			fvec3 color;
			fvec3 rotation;
			fvec3 wireframeColor;
			float lightness;
			int rotationOrder;
			bool isWireframed;
			bool isSelected;

			iss
				>> placedSkyId
				>> templateSkyId
				>> cubeMapPaths[0]
				>> cubeMapPaths[1]
				>> cubeMapPaths[2]
				>> cubeMapPaths[3]
				>> cubeMapPaths[4]
				>> cubeMapPaths[5]
				>> rotation.x
				>> rotation.y
				>> rotation.z
				>> lightness
				>> color.r
				>> color.g
				>> color.b
				>> rotationOrder
				>> isWireframed
				>> wireframeColor.r
				>> wireframeColor.g
				>> wireframeColor.b
				>> isSelected;

			for(auto & cubeMapPath : cubeMapPaths)
			{
				cubeMapPath = (cubeMapPath == "?") ? "" : cubeMapPath;

				replace(cubeMapPath.begin(), cubeMapPath.end(), '?', ' ');

				if(!cubeMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						cubeMapPath = ("projects\\" + _currentProjectId + "\\" + cubeMapPath);
					}
				}
			}

			if(!_fe3d->sky_isExisting(templateSkyId))
			{
				continue;
			}

			_duplicator->copyTemplateSky(placedSkyId, templateSkyId);

			_fe3d->sky_setCubeMaps(placedSkyId, cubeMapPaths);
			_fe3d->sky_setLightness(placedSkyId, lightness);
			_fe3d->sky_setRotation(placedSkyId, rotation);
			_fe3d->sky_setColor(placedSkyId, color);
			_fe3d->sky_setRotationOrder(placedSkyId, DirectionOrderType(rotationOrder));
			_fe3d->sky_setWireframed(placedSkyId, isWireframed);
			_fe3d->sky_setWireframeColor(placedSkyId, wireframeColor);

			_loadedSkyIds.push_back(placedSkyId);

			if(isSelected)
			{
				_fe3d->sky_select(placedSkyId);
			}
		}
		else if(lineType == "TERRAIN")
		{
			string placedTerrainId;
			string templateTerrainId;
			string diffuseMapPath;
			string normalMapPath;
			string redNormalMapPath;
			string greenNormalMapPath;
			string blueNormalMapPath;
			string blendMapPath;
			string redDiffuseMapPath;
			string greenDiffuseMapPath;
			string blueDiffuseMapPath;
			fvec3 color;
			fvec3 wireframeColor;
			fvec3 minClipPosition;
			fvec3 maxClipPosition;
			float maxHeight;
			float lightness;
			float specularShininess;
			float specularIntensity;
			int textureRepeat;
			int redTextureRepeat;
			int greenTextureRepeat;
			int blueTextureRepeat;
			bool isSpecular;
			bool isWireframed;
			bool isSelected;

			iss
				>> placedTerrainId
				>> templateTerrainId
				>> diffuseMapPath
				>> blendMapPath
				>> redDiffuseMapPath
				>> greenDiffuseMapPath
				>> blueDiffuseMapPath
				>> normalMapPath
				>> redNormalMapPath
				>> greenNormalMapPath
				>> blueNormalMapPath
				>> maxHeight
				>> textureRepeat
				>> lightness
				>> color.r
				>> color.g
				>> color.b
				>> redTextureRepeat
				>> greenTextureRepeat
				>> blueTextureRepeat
				>> isSpecular
				>> specularShininess
				>> specularIntensity
				>> isWireframed
				>> wireframeColor.r
				>> wireframeColor.g
				>> wireframeColor.b
				>> minClipPosition.x
				>> minClipPosition.y
				>> minClipPosition.z
				>> maxClipPosition.x
				>> maxClipPosition.y
				>> maxClipPosition.z
				>> isSelected;

			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
			redNormalMapPath = (redNormalMapPath == "?") ? "" : redNormalMapPath;
			greenNormalMapPath = (greenNormalMapPath == "?") ? "" : greenNormalMapPath;
			blueNormalMapPath = (blueNormalMapPath == "?") ? "" : blueNormalMapPath;
			blendMapPath = (blendMapPath == "?") ? "" : blendMapPath;
			redDiffuseMapPath = (redDiffuseMapPath == "?") ? "" : redDiffuseMapPath;
			greenDiffuseMapPath = (greenDiffuseMapPath == "?") ? "" : greenDiffuseMapPath;
			blueDiffuseMapPath = (blueDiffuseMapPath == "?") ? "" : blueDiffuseMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			replace(redNormalMapPath.begin(), redNormalMapPath.end(), '?', ' ');
			replace(greenNormalMapPath.begin(), greenNormalMapPath.end(), '?', ' ');
			replace(blueNormalMapPath.begin(), blueNormalMapPath.end(), '?', ' ');
			replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
			replace(redDiffuseMapPath.begin(), redDiffuseMapPath.end(), '?', ' ');
			replace(greenDiffuseMapPath.begin(), greenDiffuseMapPath.end(), '?', ' ');
			replace(blueDiffuseMapPath.begin(), blueDiffuseMapPath.end(), '?', ' ');

			if(!_fe3d->terrain_isExisting(templateTerrainId))
			{
				continue;
			}

			_duplicator->copyTemplateTerrain(placedTerrainId, templateTerrainId);

			_fe3d->terrain_setMaxHeight(placedTerrainId, maxHeight);
			_fe3d->terrain_setTextureRepeat(placedTerrainId, textureRepeat);
			_fe3d->terrain_setLightness(placedTerrainId, lightness);
			_fe3d->terrain_setColor(placedTerrainId, color);
			_fe3d->terrain_setRedTextureRepeat(placedTerrainId, redTextureRepeat);
			_fe3d->terrain_setGreenTextureRepeat(placedTerrainId, greenTextureRepeat);
			_fe3d->terrain_setBlueTextureRepeat(placedTerrainId, blueTextureRepeat);
			_fe3d->terrain_setSpecular(placedTerrainId, isSpecular);
			_fe3d->terrain_setSpecularShininess(placedTerrainId, specularShininess);
			_fe3d->terrain_setWireframed(placedTerrainId, isWireframed);
			_fe3d->terrain_setWireframeColor(placedTerrainId, wireframeColor);
			_fe3d->terrain_setMinClipPosition(placedTerrainId, minClipPosition);
			_fe3d->terrain_setMaxClipPosition(placedTerrainId, maxClipPosition);

			if(!diffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + _currentProjectId + "\\" + diffuseMapPath);
				}

				_fe3d->terrain_setDiffuseMap(placedTerrainId, diffuseMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					normalMapPath = ("projects\\" + _currentProjectId + "\\" + normalMapPath);
				}

				_fe3d->terrain_setNormalMap(placedTerrainId, normalMapPath);
			}

			if(!redNormalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					redNormalMapPath = ("projects\\" + _currentProjectId + "\\" + redNormalMapPath);
				}

				_fe3d->terrain_setRedNormalMap(placedTerrainId, redNormalMapPath);
			}

			if(!greenNormalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					greenNormalMapPath = ("projects\\" + _currentProjectId + "\\" + greenNormalMapPath);
				}

				_fe3d->terrain_setGreenNormalMap(placedTerrainId, greenNormalMapPath);
			}

			if(!blueNormalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					blueNormalMapPath = ("projects\\" + _currentProjectId + "\\" + blueNormalMapPath);
				}

				_fe3d->terrain_setBlueNormalMap(placedTerrainId, blueNormalMapPath);
			}

			if(!blendMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					blendMapPath = ("projects\\" + _currentProjectId + "\\" + blendMapPath);
				}

				_fe3d->terrain_setBlendMap(placedTerrainId, blendMapPath);
			}

			if(!redDiffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					redDiffuseMapPath = ("projects\\" + _currentProjectId + "\\" + redDiffuseMapPath);
				}

				_fe3d->terrain_setRedDiffuseMap(placedTerrainId, redDiffuseMapPath);
			}

			if(!greenDiffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					greenDiffuseMapPath = ("projects\\" + _currentProjectId + "\\" + greenDiffuseMapPath);
				}

				_fe3d->terrain_setGreenDiffuseMap(placedTerrainId, greenDiffuseMapPath);
			}

			if(!blueDiffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					blueDiffuseMapPath = ("projects\\" + _currentProjectId + "\\" + blueDiffuseMapPath);
				}

				_fe3d->terrain_setBlueDiffuseMap(placedTerrainId, blueDiffuseMapPath);
			}

			_loadedTerrainIds.push_back(placedTerrainId);

			if(isSelected)
			{
				_fe3d->terrain_select(placedTerrainId);
			}
		}
		else if(lineType == "WATER")
		{
			string placedWaterId;
			string templateWaterId;
			string dudvMapPath;
			string normalMapPath;
			string heightMapPath;
			fvec3 color;
			fvec3 wireframeColor;
			fvec3 minClipPosition;
			fvec3 maxClipPosition;
			fvec2 rippleSpeed;
			fvec2 waveSpeed;
			float size;
			float waveHeight;
			float specularShininess;
			float specularIntensity;
			float maxDepth;
			float height;
			int textureRepeat;
			bool isSpecular;
			bool isReflective;
			bool isRefractive;
			bool isEdged;
			bool isWireframed;
			bool isSelected;

			iss
				>> placedWaterId
				>> templateWaterId
				>> dudvMapPath
				>> normalMapPath
				>> heightMapPath
				>> isSpecular
				>> isReflective
				>> isRefractive
				>> color.r
				>> color.g
				>> color.b
				>> size
				>> textureRepeat
				>> waveHeight
				>> rippleSpeed.x
				>> rippleSpeed.y
				>> waveSpeed.x
				>> waveSpeed.y
				>> isEdged
				>> specularShininess
				>> specularIntensity
				>> maxDepth
				>> height
				>> isWireframed
				>> wireframeColor.r
				>> wireframeColor.g
				>> wireframeColor.b
				>> minClipPosition.x
				>> minClipPosition.y
				>> minClipPosition.z
				>> maxClipPosition.x
				>> maxClipPosition.y
				>> maxClipPosition.z
				>> isSelected;

			dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
			normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
			heightMapPath = (heightMapPath == "?" ? "" : heightMapPath);

			replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
			replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');

			if(!_fe3d->water_isExisting(templateWaterId))
			{
				continue;
			}

			_duplicator->copyTemplateWater(placedWaterId, templateWaterId);

			_fe3d->water_setSize(placedWaterId, size);
			_fe3d->water_setSpecular(placedWaterId, isSpecular);
			_fe3d->water_setReflective(placedWaterId, isReflective);
			_fe3d->water_setRefractive(placedWaterId, isRefractive);
			_fe3d->water_setWaveHeight(placedWaterId, waveHeight);
			_fe3d->water_setSpecularShininess(placedWaterId, specularShininess);
			_fe3d->water_setSpecularIntensity(placedWaterId, specularIntensity);
			_fe3d->water_setEdged(placedWaterId, isEdged);
			_fe3d->water_setColor(placedWaterId, color);
			_fe3d->water_setTextureRepeat(placedWaterId, textureRepeat);
			_fe3d->water_setRippleSpeed(placedWaterId, rippleSpeed);
			_fe3d->water_setWaveSpeed(placedWaterId, waveSpeed);
			_fe3d->water_setMaxDepth(placedWaterId, maxDepth);
			_fe3d->water_setHeight(placedWaterId, height);
			_fe3d->water_setWireframed(placedWaterId, isWireframed);
			_fe3d->water_setWireframeColor(placedWaterId, wireframeColor);
			_fe3d->water_setMinClipPosition(placedWaterId, minClipPosition);
			_fe3d->water_setMaxClipPosition(placedWaterId, maxClipPosition);

			if(isSelected)
			{
				_fe3d->water_select(placedWaterId);
			}

			if(!dudvMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					dudvMapPath = ("projects\\" + _currentProjectId + "\\" + dudvMapPath);
				}

				_fe3d->water_setDudvMap(placedWaterId, dudvMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					normalMapPath = ("projects\\" + _currentProjectId + "\\" + normalMapPath);
				}

				_fe3d->water_setNormalMap(placedWaterId, normalMapPath);
			}

			if(!heightMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					heightMapPath = ("projects\\" + _currentProjectId + "\\" + heightMapPath);
				}

				_fe3d->water_setHeightMap(placedWaterId, heightMapPath);
			}

			_loadedWaterIds.push_back(placedWaterId);
		}
		else if(lineType == "MODEL")
		{
			string placedModelId;
			string templateModelId;
			string levelOfDetailId;
			fvec3 position;
			fvec3 rotation;
			fvec3 rotationOrigin;
			fvec3 size;
			fvec3 minClipPosition;
			fvec3 maxClipPosition;
			float levelOfDetailDistance;
			int rotationOrder;
			bool isShadowed;
			bool isReflected;
			bool isRefracted;
			bool isVisible;
			bool isFrozen;

			iss
				>> placedModelId
				>> templateModelId
				>> levelOfDetailId
				>> levelOfDetailDistance
				>> rotationOrder
				>> isShadowed
				>> isReflected
				>> isRefracted
				>> isVisible
				>> position.x
				>> position.y
				>> position.z
				>> rotation.x
				>> rotation.y
				>> rotation.z
				>> rotationOrigin.x
				>> rotationOrigin.y
				>> rotationOrigin.z
				>> size.x
				>> size.y
				>> size.z
				>> isFrozen
				>> minClipPosition.x
				>> minClipPosition.y
				>> minClipPosition.z
				>> maxClipPosition.x
				>> maxClipPosition.y
				>> maxClipPosition.z;

			levelOfDetailId = (levelOfDetailId == "?") ? "" : levelOfDetailId;

			if(!_fe3d->model_isExisting(templateModelId))
			{
				continue;
			}

			_duplicator->copyTemplateModel(placedModelId, templateModelId);

			_fe3d->model_setVisible(placedModelId, isVisible);
			_fe3d->model_setBasePosition(placedModelId, position);
			_fe3d->model_setBaseRotation(placedModelId, rotation);
			_fe3d->model_setBaseRotationOrigin(placedModelId, rotationOrigin);
			_fe3d->model_setBaseSize(placedModelId, size);
			_fe3d->model_setLevelOfDetailId(placedModelId, levelOfDetailId);
			_fe3d->model_setLevelOfDetailDistance(placedModelId, levelOfDetailDistance);
			_fe3d->model_setRotationOrder(placedModelId, DirectionOrderType(rotationOrder));
			_fe3d->model_setShadowed(placedModelId, isShadowed);
			_fe3d->model_setReflected(placedModelId, isReflected);
			_fe3d->model_setRefracted(placedModelId, isRefracted);
			_fe3d->model_setMinClipPosition(placedModelId, minClipPosition);
			_fe3d->model_setMaxClipPosition(placedModelId, maxClipPosition);
			_fe3d->model_setFrozen(placedModelId, isFrozen);

			_loadedModelIds.push_back(placedModelId);
		}
		else if(lineType == "MODEL_PART")
		{
			string placedModelId;
			string partId;
			string diffuseMapPath;
			string emissionMapPath;
			string specularMapPath;
			string reflectionMapPath;
			string refractionMapPath;
			string normalMapPath;
			fvec3 color;
			fvec3 position;
			fvec3 rotation;
			fvec3 rotationOrigin;
			fvec3 size;
			fvec3 wireframeColor;
			float specularShininess;
			float specularIntensity;
			float reflectivity;
			float refractivity;
			float lightness;
			float emissionIntensity;
			float opacity;
			float minAlpha;
			int reflectionType;
			int refractionType;
			int textureRepeat;
			bool isSpecular;
			bool isReflective;
			bool isRefractive;
			bool isFaceCulled;
			bool isBright;
			bool isWireframed;

			iss
				>> placedModelId
				>> partId
				>> diffuseMapPath
				>> emissionMapPath
				>> specularMapPath
				>> reflectionMapPath
				>> refractionMapPath
				>> normalMapPath
				>> reflectionType
				>> refractionType
				>> isSpecular
				>> isReflective
				>> isRefractive
				>> specularShininess
				>> specularIntensity
				>> reflectivity
				>> refractivity
				>> lightness
				>> color.r
				>> color.g
				>> color.b
				>> textureRepeat
				>> isFaceCulled
				>> isBright
				>> emissionIntensity
				>> opacity
				>> minAlpha
				>> position.x
				>> position.y
				>> position.z
				>> rotation.x
				>> rotation.y
				>> rotation.z
				>> rotationOrigin.x
				>> rotationOrigin.y
				>> rotationOrigin.z
				>> size.x
				>> size.y
				>> size.z
				>> isWireframed
				>> wireframeColor.r
				>> wireframeColor.g
				>> wireframeColor.b;

			partId = (partId == "?") ? "" : partId;
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
			specularMapPath = (specularMapPath == "?") ? "" : specularMapPath;
			reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
			refractionMapPath = (refractionMapPath == "?") ? "" : refractionMapPath;
			normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
			replace(specularMapPath.begin(), specularMapPath.end(), '?', ' ');
			replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
			replace(refractionMapPath.begin(), refractionMapPath.end(), '?', ' ');
			replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

			if(!_fe3d->model_isExisting(placedModelId))
			{
				continue;
			}

			if(!_fe3d->model_hasPart(placedModelId, partId))
			{
				continue;
			}

			_fe3d->model_setPartPosition(placedModelId, partId, position);
			_fe3d->model_setPartRotation(placedModelId, partId, rotation);
			_fe3d->model_setPartRotationOrigin(placedModelId, partId, rotationOrigin);
			_fe3d->model_setPartSize(placedModelId, partId, size);
			_fe3d->model_setColor(placedModelId, partId, color);
			_fe3d->model_setSpecular(placedModelId, partId, isSpecular);
			_fe3d->model_setSpecularShininess(placedModelId, partId, specularShininess);
			_fe3d->model_setSpecularIntensity(placedModelId, partId, specularIntensity);
			_fe3d->model_setReflectivity(placedModelId, partId, reflectivity);
			_fe3d->model_setRefractivity(placedModelId, partId, refractivity);
			_fe3d->model_setLightness(placedModelId, partId, lightness);
			_fe3d->model_setTextureRepeat(placedModelId, partId, textureRepeat);
			_fe3d->model_setReflective(placedModelId, partId, isReflective);
			_fe3d->model_setRefractive(placedModelId, partId, isRefractive);
			_fe3d->model_setReflectionType(placedModelId, partId, ReflectionType(reflectionType));
			_fe3d->model_setRefractionType(placedModelId, partId, RefractionType(refractionType));
			_fe3d->model_setFaceCulled(placedModelId, partId, isFaceCulled);
			_fe3d->model_setBright(placedModelId, partId, isBright);
			_fe3d->model_setEmissionIntensity(placedModelId, partId, emissionIntensity);
			_fe3d->model_setOpacity(placedModelId, partId, opacity);
			_fe3d->model_setMinAlpha(placedModelId, partId, minAlpha);
			_fe3d->model_setWireframed(placedModelId, partId, isWireframed);
			_fe3d->model_setWireframeColor(placedModelId, partId, wireframeColor);

			if(!diffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + _currentProjectId + "\\" + diffuseMapPath);
				}

				_fe3d->model_setDiffuseMap(placedModelId, partId, diffuseMapPath);
			}

			if(!specularMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					specularMapPath = ("projects\\" + _currentProjectId + "\\" + specularMapPath);
				}

				_fe3d->model_setSpecularMap(placedModelId, partId, specularMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					emissionMapPath = ("projects\\" + _currentProjectId + "\\" + emissionMapPath);
				}

				_fe3d->model_setEmissionMap(placedModelId, partId, emissionMapPath);
			}

			if(!reflectionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					reflectionMapPath = ("projects\\" + _currentProjectId + "\\" + reflectionMapPath);
				}

				_fe3d->model_setReflectionMap(placedModelId, partId, reflectionMapPath);
			}

			if(!refractionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					refractionMapPath = ("projects\\" + _currentProjectId + "\\" + refractionMapPath);
				}

				_fe3d->model_setRefractionMap(placedModelId, partId, refractionMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					normalMapPath = ("projects\\" + _currentProjectId + "\\" + normalMapPath);
				}

				_fe3d->model_setNormalMap(placedModelId, partId, normalMapPath);
			}
		}
		else if(lineType == "MODEL_AABB")
		{
			string placedModelId;
			string aabbId;
			fvec3 position;
			fvec3 size;
			bool isRaycastResponsive;
			bool isCollisionResponsive;
			bool isVisible;

			iss
				>> placedModelId
				>> aabbId
				>> position.x
				>> position.y
				>> position.z
				>> size.x
				>> size.y
				>> size.z
				>> isRaycastResponsive
				>> isCollisionResponsive
				>> isVisible;

			if(!_fe3d->model_isExisting(placedModelId))
			{
				continue;
			}

			_fe3d->aabb_create(aabbId, false);
			_fe3d->aabb_setVisible(aabbId, false);
			_fe3d->aabb_setParentId(aabbId, placedModelId);
			_fe3d->aabb_setParentType(aabbId, AabbParentType::MODEL);
			_fe3d->aabb_setLocalPosition(aabbId, position);
			_fe3d->aabb_setLocalSize(aabbId, size);
			_fe3d->aabb_setRaycastResponsive(aabbId, isRaycastResponsive);
			_fe3d->aabb_setCollisionResponsive(aabbId, isCollisionResponsive);
			_fe3d->aabb_setVisible(aabbId, isVisible);
		}
		else if(lineType == "MODEL_ANIMATION3D")
		{
			float speedMultiplier;
			int playCount;
			int frameIndex;
			int partCount;
			bool isPaused;
			bool isAutoPaused;

			iss
				>> isPaused
				>> isAutoPaused
				>> playCount
				>> frameIndex
				>> speedMultiplier
				>> partCount;



			for(int index = 0; index < partCount; index++)
			{
				string partId;
				fvec3 totalMovement;
				fvec3 totalRotation;
				fvec3 totalScaling;
				fvec3 totalSpeed;


			}
		}
		else if(lineType == "QUAD3D")
		{
			string quad3dId;
			string diffuseMapPath;
			string emissionMapPath;
			fvec2 size;
			fvec3 color;
			float lightness;
			float opacity;
			float minAlpha;
			float emissionIntensity;
			int textureRepeat;
			int rotationOrder;
			bool isFacingCameraHorizontally;
			bool isFacingCameraVertically;
			bool isHorizontallyFlipped;
			bool isVerticallyFlipped;
			bool isReflected;
			bool isRefracted;
			bool isShadowed;
			bool isBright;

			iss
				>> quad3dId
				>> diffuseMapPath
				>> emissionMapPath
				>> size.x
				>> size.y
				>> color.r
				>> color.g
				>> color.b
				>> isFacingCameraHorizontally
				>> isFacingCameraVertically
				>> isHorizontallyFlipped
				>> isVerticallyFlipped
				>> isReflected
				>> isRefracted
				>> isShadowed
				>> lightness
				>> textureRepeat
				>> isBright
				>> emissionIntensity
				>> opacity
				>> minAlpha
				>> rotationOrder;

			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

			_fe3d->quad3d_create(quad3dId, false);
			_fe3d->quad3d_setVisible(quad3dId, false);
			_fe3d->quad3d_setSize(quad3dId, size);
			_fe3d->quad3d_setColor(quad3dId, color);
			_fe3d->quad3d_setLightness(quad3dId, lightness);
			_fe3d->quad3d_setFacingCameraHorizontally(quad3dId, isFacingCameraHorizontally);
			_fe3d->quad3d_setFacingCameraVertically(quad3dId, isFacingCameraVertically);
			_fe3d->quad3d_setHorizontallyFlipped(quad3dId, isHorizontallyFlipped);
			_fe3d->quad3d_setVerticallyFlipped(quad3dId, isVerticallyFlipped);
			_fe3d->quad3d_setShadowed(quad3dId, isShadowed);
			_fe3d->quad3d_setReflected(quad3dId, isReflected);
			_fe3d->quad3d_setRefracted(quad3dId, isRefracted);
			_fe3d->quad3d_setTextureRepeat(quad3dId, textureRepeat);
			_fe3d->quad3d_setBright(quad3dId, isBright);
			_fe3d->quad3d_setOpacity(quad3dId, opacity);
			_fe3d->quad3d_setEmissionIntensity(quad3dId, emissionIntensity);
			_fe3d->quad3d_setMinAlpha(quad3dId, minAlpha);
			_fe3d->quad3d_setRotationOrder(quad3dId, DirectionOrderType(rotationOrder));

			if(!diffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + _currentProjectId + "\\" + diffuseMapPath);
				}

				_fe3d->quad3d_setDiffuseMap(quad3dId, diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					emissionMapPath = ("projects\\" + _currentProjectId + "\\" + emissionMapPath);
				}

				_fe3d->quad3d_setEmissionMap(quad3dId, emissionMapPath);
			}

			_loadedQuad3dIds.push_back(quad3dId);
		}
		else if(lineType == "QUAD3D_AABB")
		{
			string quad3dId;

			iss >> quad3dId;

			_fe3d->aabb_create(quad3dId, false);
			_fe3d->aabb_setVisible(quad3dId, false);
			_fe3d->aabb_setParentId(quad3dId, quad3dId);
			_fe3d->aabb_setParentType(quad3dId, AabbParentType::QUAD3D);
		}
		else if(lineType == "QUAD3D_ANIMATION2D")
		{

		}
		else if(lineType == "TEXT3D")
		{
			string text3dId;
			string fontMapPath;
			fvec2 size;
			fvec3 color;
			float lightness;
			float opacity;
			float minAlpha;
			int rotationOrder;
			bool isFacingCameraHorizontally;
			bool isFacingCameraVertically;
			bool isHorizontallyFlipped;
			bool isVerticallyFlipped;
			bool isReflected;
			bool isRefracted;
			bool isShadowed;
			bool isBright;
			bool hasAabb;

			iss
				>> text3dId
				>> fontMapPath
				>> size.x
				>> size.y
				>> color.r
				>> color.g
				>> color.b
				>> isFacingCameraHorizontally
				>> isFacingCameraVertically
				>> isHorizontallyFlipped
				>> isVerticallyFlipped
				>> isReflected
				>> isRefracted
				>> isShadowed
				>> lightness
				>> isBright
				>> opacity
				>> minAlpha
				>> rotationOrder
				>> hasAabb;

			fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

			replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

			if(!Configuration::getInst().isApplicationExported())
			{
				fontMapPath = ("projects\\" + _currentProjectId + "\\" + fontMapPath);
			}

			_fe3d->text3d_create(text3dId, fontMapPath, false);

			if(_fe3d->text3d_isExisting(text3dId))
			{
				_fe3d->text3d_setVisible(text3dId, false);
				_fe3d->text3d_setSize(text3dId, size);
				_fe3d->text3d_setColor(text3dId, color);
				_fe3d->text3d_setLightness(text3dId, lightness);
				_fe3d->text3d_setFacingCameraHorizontally(text3dId, isFacingCameraHorizontally);
				_fe3d->text3d_setFacingCameraVertically(text3dId, isFacingCameraVertically);
				_fe3d->text3d_setHorizontallyFlipped(text3dId, isHorizontallyFlipped);
				_fe3d->text3d_setVerticallyFlipped(text3dId, isVerticallyFlipped);
				_fe3d->text3d_setShadowed(text3dId, isShadowed);
				_fe3d->text3d_setReflected(text3dId, isReflected);
				_fe3d->text3d_setRefracted(text3dId, isRefracted);
				_fe3d->text3d_setBright(text3dId, isBright);
				_fe3d->text3d_setOpacity(text3dId, opacity);
				_fe3d->text3d_setMinAlpha(text3dId, minAlpha);
				_fe3d->text3d_setRotationOrder(text3dId, DirectionOrderType(rotationOrder));

				if(hasAabb)
				{
					_fe3d->aabb_create(text3dId, false);
					_fe3d->aabb_setVisible(text3dId, false);
					_fe3d->aabb_setParentId(text3dId, text3dId);
					_fe3d->aabb_setParentType(text3dId, AabbParentType::TEXT3D);
				}

				_loadedText3dIds.push_back(text3dId);
			}
		}
		else if(lineType == "TEXT3D_AABB")
		{
			string text3dId;

			iss >> text3dId;

			_fe3d->aabb_create(text3dId, false);
			_fe3d->aabb_setVisible(text3dId, false);
			_fe3d->aabb_setParentId(text3dId, text3dId);
			_fe3d->aabb_setParentType(text3dId, AabbParentType::TEXT3D);
		}
		else if(lineType == "AABB")
		{
			string aabbId;
			fvec3 size;
			fvec3 color;

			iss
				>> aabbId
				>> size.x
				>> size.y
				>> size.z
				>> color.r
				>> color.g
				>> color.b;

			_fe3d->aabb_create(aabbId, false);
			_fe3d->aabb_setVisible(aabbId, false);
			_fe3d->aabb_setBaseSize(aabbId, size);
			_fe3d->aabb_setColor(aabbId, color);

			_loadedAabbIds.push_back(aabbId);
		}
		else if(lineType == "POINTLIGHT")
		{
			string pointlightId;
			fvec3 radius;
			fvec3 color;
			float intensity;
			int shape;

			iss
				>> pointlightId
				>> radius.x
				>> radius.y
				>> radius.z
				>> color.r
				>> color.g
				>> color.b
				>> intensity
				>> shape;

			_fe3d->pointlight_create(pointlightId);
			_fe3d->pointlight_setVisible(pointlightId, false);
			_fe3d->pointlight_setPosition(pointlightId, POINTLIGHT_POSITION);
			_fe3d->pointlight_setRadius(pointlightId, radius);
			_fe3d->pointlight_setColor(pointlightId, color);
			_fe3d->pointlight_setIntensity(pointlightId, intensity);
			_fe3d->pointlight_setShape(pointlightId, PointlightShapeType(shape));

			_loadedPointlightIds.push_back(pointlightId);
		}
		else if(lineType == "SPOTLIGHT")
		{
			string spotlightId;
			fvec3 color;
			float intensity;
			float angle;
			float distance;

			iss
				>> spotlightId
				>> color.r
				>> color.g
				>> color.b
				>> intensity
				>> angle
				>> distance;

			_fe3d->spotlight_create(spotlightId);
			_fe3d->spotlight_setVisible(spotlightId, false);
			_fe3d->spotlight_setPosition(spotlightId, SPOTLIGHT_POSITION);
			_fe3d->spotlight_setPitch(spotlightId, -90.0f);
			_fe3d->spotlight_setColor(spotlightId, color);
			_fe3d->spotlight_setIntensity(spotlightId, intensity);
			_fe3d->spotlight_setAngle(spotlightId, angle);
			_fe3d->spotlight_setDistance(spotlightId, distance);

			_loadedSpotlightIds.push_back(spotlightId);

			sort(_loadedSpotlightIds.begin(), _loadedSpotlightIds.end());
		}
		else if(lineType == "SOUND3D")
		{
			string sound3dId;
			string audioPath;
			float maxVolume;
			float maxDistance;

			iss
				>> sound3dId
				>> audioPath
				>> maxVolume
				>> maxDistance;

			audioPath = (audioPath == "?") ? "" : audioPath;

			replace(audioPath.begin(), audioPath.end(), '?', ' ');

			if(!Configuration::getInst().isApplicationExported())
			{
				audioPath = ("projects\\" + _currentProjectId + "\\" + audioPath);
			}

			_fe3d->sound3d_create(sound3dId, audioPath);

			if(_fe3d->sound3d_isExisting(sound3dId))
			{
				_fe3d->sound3d_setPosition(sound3dId, SOUND3D_POSITION);
				_fe3d->sound3d_setMaxVolume(sound3dId, maxVolume);
				_fe3d->sound3d_setMaxDistance(sound3dId, maxDistance);

				_loadedSound3dIds.push_back(sound3dId);

				sort(_loadedSound3dIds.begin(), _loadedSound3dIds.end());
			}
		}
		else if(lineType == "CAPTOR")
		{
			string captorId;
			string exceptionId;
			fvec3 position;

			iss
				>> captorId
				>> exceptionId
				>> position.x
				>> position.y
				>> position.z;
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
				flareMapPath = ("projects\\" + _currentProjectId + "\\" + flareMapPath);
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

	Logger::throwInfo("Custom world data loaded");

	return true;
}