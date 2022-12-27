#include "custom_world_builder.hpp"
#include "tools.hpp"
#include "logger.hpp"

#include <sstream>

using std::istringstream;

const bool CustomWorldBuilder::loadWorldFromFile(const string & fileName)
{
	if(!Tools::isApplicationExported() && _currentProjectId.empty())
	{
		abort();
	}

	const auto isExported = Tools::isApplicationExported();
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
			string skyId;
			string editorSkyId;
			fvec3 color;
			fvec3 rotation;
			fvec3 wireframeColor;
			float lightness;
			int rotationOrder;
			bool isWireframed;
			bool isSelected;

			iss
				>> skyId
				>> editorSkyId
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
					if(!isExported)
					{
						cubeMapPath = ("projects\\" + _currentProjectId + "\\" + cubeMapPath);
					}
				}
			}

			if(!_fe3d->sky_isExisting(editorSkyId))
			{
				continue;
			}

			_duplicator->copyEditorSky(skyId, editorSkyId);

			_fe3d->sky_setCubeMaps(skyId, cubeMapPaths);
			_fe3d->sky_setLightness(skyId, lightness);
			_fe3d->sky_setRotation(skyId, rotation);
			_fe3d->sky_setColor(skyId, color);
			_fe3d->sky_setRotationOrder(skyId, DirectionOrderType(rotationOrder));
			_fe3d->sky_setWireframed(skyId, isWireframed);
			_fe3d->sky_setWireframeColor(skyId, wireframeColor);

			_loadedSkyIds.push_back(skyId);

			if(isSelected)
			{
				_fe3d->sky_select(skyId);
			}
		}
		else if(lineType == "TERRAIN")
		{
			string terrainId;
			string editorTerrainId;
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
			bool isShadowed;
			bool isSelected;

			iss
				>> terrainId
				>> editorTerrainId
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
				>> isShadowed
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

			if(!_fe3d->terrain_isExisting(editorTerrainId))
			{
				continue;
			}

			_duplicator->copyEditorTerrain(terrainId, editorTerrainId);

			_fe3d->terrain_setMaxHeight(terrainId, maxHeight);
			_fe3d->terrain_setTextureRepeat(terrainId, textureRepeat);
			_fe3d->terrain_setLightness(terrainId, lightness);
			_fe3d->terrain_setColor(terrainId, color);
			_fe3d->terrain_setRedTextureRepeat(terrainId, redTextureRepeat);
			_fe3d->terrain_setGreenTextureRepeat(terrainId, greenTextureRepeat);
			_fe3d->terrain_setBlueTextureRepeat(terrainId, blueTextureRepeat);
			_fe3d->terrain_setSpecular(terrainId, isSpecular);
			_fe3d->terrain_setSpecularShininess(terrainId, specularShininess);
			_fe3d->terrain_setSpecularIntensity(terrainId, specularIntensity);
			_fe3d->terrain_setWireframed(terrainId, isWireframed);
			_fe3d->terrain_setShadowed(terrainId, isShadowed);
			_fe3d->terrain_setWireframeColor(terrainId, wireframeColor);
			_fe3d->terrain_setMinClipPosition(terrainId, minClipPosition);
			_fe3d->terrain_setMaxClipPosition(terrainId, maxClipPosition);

			if(!diffuseMapPath.empty())
			{
				if(!isExported)
				{
					diffuseMapPath = ("projects\\" + _currentProjectId + "\\" + diffuseMapPath);
				}

				_fe3d->terrain_setDiffuseMap(terrainId, diffuseMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!isExported)
				{
					normalMapPath = ("projects\\" + _currentProjectId + "\\" + normalMapPath);
				}

				_fe3d->terrain_setNormalMap(terrainId, normalMapPath);
			}

			if(!redNormalMapPath.empty())
			{
				if(!isExported)
				{
					redNormalMapPath = ("projects\\" + _currentProjectId + "\\" + redNormalMapPath);
				}

				_fe3d->terrain_setRedNormalMap(terrainId, redNormalMapPath);
			}

			if(!greenNormalMapPath.empty())
			{
				if(!isExported)
				{
					greenNormalMapPath = ("projects\\" + _currentProjectId + "\\" + greenNormalMapPath);
				}

				_fe3d->terrain_setGreenNormalMap(terrainId, greenNormalMapPath);
			}

			if(!blueNormalMapPath.empty())
			{
				if(!isExported)
				{
					blueNormalMapPath = ("projects\\" + _currentProjectId + "\\" + blueNormalMapPath);
				}

				_fe3d->terrain_setBlueNormalMap(terrainId, blueNormalMapPath);
			}

			if(!blendMapPath.empty())
			{
				if(!isExported)
				{
					blendMapPath = ("projects\\" + _currentProjectId + "\\" + blendMapPath);
				}

				_fe3d->terrain_setBlendMap(terrainId, blendMapPath);
			}

			if(!redDiffuseMapPath.empty())
			{
				if(!isExported)
				{
					redDiffuseMapPath = ("projects\\" + _currentProjectId + "\\" + redDiffuseMapPath);
				}

				_fe3d->terrain_setRedDiffuseMap(terrainId, redDiffuseMapPath);
			}

			if(!greenDiffuseMapPath.empty())
			{
				if(!isExported)
				{
					greenDiffuseMapPath = ("projects\\" + _currentProjectId + "\\" + greenDiffuseMapPath);
				}

				_fe3d->terrain_setGreenDiffuseMap(terrainId, greenDiffuseMapPath);
			}

			if(!blueDiffuseMapPath.empty())
			{
				if(!isExported)
				{
					blueDiffuseMapPath = ("projects\\" + _currentProjectId + "\\" + blueDiffuseMapPath);
				}

				_fe3d->terrain_setBlueDiffuseMap(terrainId, blueDiffuseMapPath);
			}

			_loadedTerrainIds.push_back(terrainId);

			if(isSelected)
			{
				_fe3d->terrain_select(terrainId);
			}
		}
		else if(lineType == "WATER")
		{
			string waterId;
			string editorWaterId;
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
			float lightness;
			float distortionSize;
			float distortionFactor;
			float captureOffset;
			int textureRepeat;
			bool isSpecular;
			bool isReflective;
			bool isRefractive;
			bool isEdged;
			bool isWireframed;
			bool isCapturingSky;
			bool isCapturingTerrain;
			bool isCapturingModels;
			bool isCapturingQuad3ds;
			bool isCapturingText3ds;
			bool isCapturingAabbs;
			bool isSelected;

			iss
				>> waterId
				>> editorWaterId
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
				>> lightness
				>> distortionSize
				>> distortionFactor
				>> captureOffset
				>> isCapturingSky
				>> isCapturingTerrain
				>> isCapturingModels
				>> isCapturingQuad3ds
				>> isCapturingText3ds
				>> isCapturingAabbs
				>> isSelected;

			dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
			normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
			heightMapPath = (heightMapPath == "?" ? "" : heightMapPath);

			replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
			replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');

			if(!_fe3d->water_isExisting(editorWaterId))
			{
				continue;
			}

			_duplicator->copyEditorWater(waterId, editorWaterId);

			_fe3d->water_setSize(waterId, size);
			_fe3d->water_setSpecular(waterId, isSpecular);
			_fe3d->water_setReflective(waterId, isReflective);
			_fe3d->water_setRefractive(waterId, isRefractive);
			_fe3d->water_setWaveHeight(waterId, waveHeight);
			_fe3d->water_setSpecularShininess(waterId, specularShininess);
			_fe3d->water_setSpecularIntensity(waterId, specularIntensity);
			_fe3d->water_setEdged(waterId, isEdged);
			_fe3d->water_setColor(waterId, color);
			_fe3d->water_setTextureRepeat(waterId, textureRepeat);
			_fe3d->water_setRippleSpeed(waterId, rippleSpeed);
			_fe3d->water_setWaveSpeed(waterId, waveSpeed);
			_fe3d->water_setMaxDepth(waterId, maxDepth);
			_fe3d->water_setHeight(waterId, height);
			_fe3d->water_setWireframed(waterId, isWireframed);
			_fe3d->water_setWireframeColor(waterId, wireframeColor);
			_fe3d->water_setMinClipPosition(waterId, minClipPosition);
			_fe3d->water_setMaxClipPosition(waterId, maxClipPosition);
			_fe3d->water_setLightness(waterId, lightness);
			_fe3d->water_setDistortionSize(waterId, distortionSize);
			_fe3d->water_setDistortionFactor(waterId, distortionFactor);
			_fe3d->water_setCaptureOffset(waterId, captureOffset);
			_fe3d->water_setCapturingSky(waterId, isCapturingSky);
			_fe3d->water_setCapturingTerrain(waterId, isCapturingTerrain);
			_fe3d->water_setCapturingModels(waterId, isCapturingModels);
			_fe3d->water_setCapturingQuad3ds(waterId, isCapturingQuad3ds);
			_fe3d->water_setCapturingText3ds(waterId, isCapturingText3ds);
			_fe3d->water_setCapturingAabbs(waterId, isCapturingAabbs);

			if(!dudvMapPath.empty())
			{
				if(!isExported)
				{
					dudvMapPath = ("projects\\" + _currentProjectId + "\\" + dudvMapPath);
				}

				_fe3d->water_setDudvMap(waterId, dudvMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!isExported)
				{
					normalMapPath = ("projects\\" + _currentProjectId + "\\" + normalMapPath);
				}

				_fe3d->water_setNormalMap(waterId, normalMapPath);
			}

			if(!heightMapPath.empty())
			{
				if(!isExported)
				{
					heightMapPath = ("projects\\" + _currentProjectId + "\\" + heightMapPath);
				}

				_fe3d->water_setHeightMap(waterId, heightMapPath);
			}

			_loadedWaterIds.push_back(waterId);

			if(isSelected)
			{
				_fe3d->water_select(waterId);
			}
		}
		else if(lineType == "MODEL")
		{
			string modelId;
			string editorModelId;
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

			iss
				>> modelId
				>> editorModelId
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
				>> minClipPosition.x
				>> minClipPosition.y
				>> minClipPosition.z
				>> maxClipPosition.x
				>> maxClipPosition.y
				>> maxClipPosition.z;

			levelOfDetailId = (levelOfDetailId == "?") ? "" : levelOfDetailId;

			if(!_fe3d->model_isExisting(editorModelId))
			{
				continue;
			}

			_duplicator->copyEditorModel(modelId, editorModelId);

			_fe3d->model_setVisible(modelId, isVisible);
			_fe3d->model_setBasePosition(modelId, position);
			_fe3d->model_setBaseRotation(modelId, rotation);
			_fe3d->model_setBaseRotationOrigin(modelId, rotationOrigin);
			_fe3d->model_setBaseSize(modelId, size);
			_fe3d->model_setLevelOfDetailId(modelId, levelOfDetailId);
			_fe3d->model_setLevelOfDetailDistance(modelId, levelOfDetailDistance);
			_fe3d->model_setRotationOrder(modelId, DirectionOrderType(rotationOrder));
			_fe3d->model_setShadowed(modelId, isShadowed);
			_fe3d->model_setReflected(modelId, isReflected);
			_fe3d->model_setRefracted(modelId, isRefracted);
			_fe3d->model_setMinClipPosition(modelId, minClipPosition);
			_fe3d->model_setMaxClipPosition(modelId, maxClipPosition);

			_loadedModelIds.push_back(modelId);
		}
		else if(lineType == "MODEL_PART")
		{
			string modelId;
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
				>> modelId
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

			if(!_fe3d->model_isExisting(modelId))
			{
				continue;
			}

			if(!_fe3d->model_hasPart(modelId, partId))
			{
				continue;
			}

			_fe3d->model_setPartPosition(modelId, partId, position);
			_fe3d->model_setPartRotation(modelId, partId, rotation);
			_fe3d->model_setPartRotationOrigin(modelId, partId, rotationOrigin);
			_fe3d->model_setPartSize(modelId, partId, size);
			_fe3d->model_setColor(modelId, partId, color);
			_fe3d->model_setSpecular(modelId, partId, isSpecular);
			_fe3d->model_setSpecularShininess(modelId, partId, specularShininess);
			_fe3d->model_setSpecularIntensity(modelId, partId, specularIntensity);
			_fe3d->model_setReflectivity(modelId, partId, reflectivity);
			_fe3d->model_setRefractivity(modelId, partId, refractivity);
			_fe3d->model_setLightness(modelId, partId, lightness);
			_fe3d->model_setTextureRepeat(modelId, partId, textureRepeat);
			_fe3d->model_setReflective(modelId, partId, isReflective);
			_fe3d->model_setRefractive(modelId, partId, isRefractive);
			_fe3d->model_setReflectionType(modelId, partId, ReflectionType(reflectionType));
			_fe3d->model_setRefractionType(modelId, partId, RefractionType(refractionType));
			_fe3d->model_setFaceCulled(modelId, partId, isFaceCulled);
			_fe3d->model_setBright(modelId, partId, isBright);
			_fe3d->model_setEmissionIntensity(modelId, partId, emissionIntensity);
			_fe3d->model_setOpacity(modelId, partId, opacity);
			_fe3d->model_setMinAlpha(modelId, partId, minAlpha);
			_fe3d->model_setWireframed(modelId, partId, isWireframed);
			_fe3d->model_setWireframeColor(modelId, partId, wireframeColor);

			if(!diffuseMapPath.empty())
			{
				if(!isExported)
				{
					diffuseMapPath = ("projects\\" + _currentProjectId + "\\" + diffuseMapPath);
				}

				_fe3d->model_setDiffuseMap(modelId, partId, diffuseMapPath);
			}

			if(!specularMapPath.empty())
			{
				if(!isExported)
				{
					specularMapPath = ("projects\\" + _currentProjectId + "\\" + specularMapPath);
				}

				_fe3d->model_setSpecularMap(modelId, partId, specularMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!isExported)
				{
					emissionMapPath = ("projects\\" + _currentProjectId + "\\" + emissionMapPath);
				}

				_fe3d->model_setEmissionMap(modelId, partId, emissionMapPath);
			}

			if(!reflectionMapPath.empty())
			{
				if(!isExported)
				{
					reflectionMapPath = ("projects\\" + _currentProjectId + "\\" + reflectionMapPath);
				}

				_fe3d->model_setReflectionMap(modelId, partId, reflectionMapPath);
			}

			if(!refractionMapPath.empty())
			{
				if(!isExported)
				{
					refractionMapPath = ("projects\\" + _currentProjectId + "\\" + refractionMapPath);
				}

				_fe3d->model_setRefractionMap(modelId, partId, refractionMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!isExported)
				{
					normalMapPath = ("projects\\" + _currentProjectId + "\\" + normalMapPath);
				}

				_fe3d->model_setNormalMap(modelId, partId, normalMapPath);
			}
		}
		else if(lineType == "MODEL_AABB")
		{
			string modelId;
			string aabbId;
			bool isVisible;

			iss
				>> modelId
				>> aabbId
				>> isVisible;

			if(!_fe3d->model_isExisting(modelId))
			{
				continue;
			}

			if(!_fe3d->aabb_isExisting(aabbId))
			{
				continue;
			}

			_fe3d->aabb_setVisible(aabbId, isVisible);
		}
		else if(lineType == "MODEL_ANIMATION3D")
		{
			string modelId;
			string animation3dId;
			float speedMultiplier;
			int playCount;
			int frameIndex;
			int partCount;
			bool isPaused;
			bool isAutoPaused;

			iss
				>> modelId
				>> animation3dId
				>> isPaused
				>> isAutoPaused
				>> playCount
				>> frameIndex
				>> speedMultiplier
				>> partCount;

			if(!_fe3d->model_isExisting(modelId))
			{
				continue;
			}

			if(!_fe3d->animation3d_isExisting(animation3dId))
			{
				continue;
			}

			bool hasAllParts = true;

			for(const auto & partId : _fe3d->animation3d_getPartIds(animation3dId))
			{
				if(!partId.empty() && !_fe3d->model_hasPart(modelId, partId))
				{
					hasAllParts = false;
				}
			}

			if(!hasAllParts)
			{
				continue;
			}

			_fe3d->model_startAnimation3d(modelId, animation3dId, playCount);
			_fe3d->model_setAnimation3dFrameIndex(modelId, animation3dId, frameIndex);
			_fe3d->model_setAnimation3dSpeedMultiplier(modelId, animation3dId, speedMultiplier);

			if(isPaused)
			{
				_fe3d->model_pauseAnimation3d(modelId, animation3dId);
			}

			if(isAutoPaused)
			{
				_fe3d->model_autopauseAnimation3d(modelId, animation3dId);
			}

			for(int index = 0; index < partCount; index++)
			{
				string partId;
				fvec3 totalMovement;
				fvec3 totalRotation;
				fvec3 totalScaling;
				fvec3 totalSpeed;

				iss
					>> partId
					>> totalMovement.x
					>> totalMovement.y
					>> totalMovement.z
					>> totalRotation.x
					>> totalRotation.y
					>> totalRotation.z
					>> totalScaling.x
					>> totalScaling.y
					>> totalScaling.z
					>> totalSpeed.x
					>> totalSpeed.y
					>> totalSpeed.z;

				if(!_fe3d->animation3d_hasPart(animation3dId, partId))
				{
					_fe3d->model_stopAnimation3d(modelId, animation3dId);

					break;
				}

				_fe3d->model_setAnimation3dTotalMovement(modelId, partId, animation3dId, totalMovement);
				_fe3d->model_setAnimation3dTotalRotation(modelId, partId, animation3dId, totalRotation);
				_fe3d->model_setAnimation3dTotalScaling(modelId, partId, animation3dId, totalScaling);
				_fe3d->model_setAnimation3dTotalSpeed(modelId, partId, animation3dId, totalSpeed);
			}
		}
		else if(lineType == "QUAD3D")
		{
			string quad3dId;
			string editorQuad3dId;
			string diffuseMapPath;
			string emissionMapPath;
			fvec3 color;
			fvec3 wireframeColor;
			fvec3 minClipPosition;
			fvec3 maxClipPosition;
			fvec3 position;
			fvec3 rotation;
			fvec2 size;
			fvec2 uvMultiplier;
			fvec2 uvOffset;
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
			bool isVisible;
			bool isWireframed;

			iss
				>> quad3dId
				>> editorQuad3dId
				>> diffuseMapPath
				>> emissionMapPath
				>> position.x
				>> position.y
				>> position.z
				>> rotation.x
				>> rotation.y
				>> rotation.z
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
				>> rotationOrder
				>> isVisible
				>> isWireframed
				>> wireframeColor.r
				>> wireframeColor.g
				>> wireframeColor.b
				>> uvMultiplier.x
				>> uvMultiplier.y
				>> uvOffset.x
				>> uvOffset.y
				>> minClipPosition.x
				>> minClipPosition.y
				>> minClipPosition.z
				>> maxClipPosition.x
				>> maxClipPosition.y
				>> maxClipPosition.z;

			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');

			if(!_fe3d->quad3d_isExisting(editorQuad3dId))
			{
				continue;
			}

			_duplicator->copyEditorQuad3d(quad3dId, editorQuad3dId);

			_fe3d->quad3d_setVisible(quad3dId, isVisible);
			_fe3d->quad3d_setPosition(quad3dId, position);
			_fe3d->quad3d_setRotation(quad3dId, rotation);
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
			_fe3d->quad3d_setMinClipPosition(quad3dId, minClipPosition);
			_fe3d->quad3d_setMaxClipPosition(quad3dId, maxClipPosition);
			_fe3d->quad3d_setWireframed(quad3dId, isWireframed);
			_fe3d->quad3d_setWireframeColor(quad3dId, wireframeColor);
			_fe3d->quad3d_setUvMultiplier(quad3dId, uvMultiplier);
			_fe3d->quad3d_setUvOffset(quad3dId, uvOffset);

			if(!diffuseMapPath.empty())
			{
				if(!isExported)
				{
					diffuseMapPath = ("projects\\" + _currentProjectId + "\\" + diffuseMapPath);
				}

				_fe3d->quad3d_setDiffuseMap(quad3dId, diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!isExported)
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
			string aabbId;
			bool isVisible;

			iss
				>> quad3dId
				>> aabbId
				>> isVisible;

			if(!_fe3d->quad3d_isExisting(quad3dId))
			{
				continue;
			}

			if(!_fe3d->aabb_isExisting(aabbId))
			{
				continue;
			}

			_fe3d->aabb_setVisible(aabbId, isVisible);
		}
		else if(lineType == "QUAD3D_ANIMATION2D")
		{
			string quad3dId;
			string animation2dId;
			int playCount;
			int rowIndex;
			int columnIndex;
			int intervalMultiplier;
			int intervalDivider;
			int updateCount;
			bool isPaused;
			bool isAutoPaused;

			iss
				>> quad3dId
				>> animation2dId
				>> isPaused
				>> isAutoPaused
				>> playCount
				>> rowIndex
				>> columnIndex
				>> intervalMultiplier
				>> intervalDivider
				>> updateCount;

			if(!_fe3d->quad3d_isExisting(quad3dId))
			{
				continue;
			}

			if(!_fe3d->animation2d_isExisting(animation2dId))
			{
				continue;
			}

			_fe3d->quad3d_startAnimation2d(quad3dId, animation2dId, playCount);
			_fe3d->quad3d_setAnimation2dRowIndex(quad3dId, animation2dId, rowIndex);
			_fe3d->quad3d_setAnimation2dColumnIndex(quad3dId, animation2dId, columnIndex);
			_fe3d->quad3d_setAnimation2dIntervalMultiplier(quad3dId, animation2dId, intervalMultiplier);
			_fe3d->quad3d_setAnimation2dIntervalDivider(quad3dId, animation2dId, intervalDivider);
			_fe3d->quad3d_setAnimation2dUpdateCount(quad3dId, animation2dId, updateCount);

			if(isPaused)
			{
				_fe3d->quad3d_pauseAnimation2d(quad3dId, animation2dId);
			}

			if(isAutoPaused)
			{
				_fe3d->quad3d_autopauseAnimation2d(quad3dId, animation2dId);
			}
		}
		else if(lineType == "TEXT3D")
		{
			string text3dId;
			string editorText3dId;
			string content;
			fvec3 color;
			fvec3 position;
			fvec3 rotation;
			fvec3 wireframeColor;
			fvec3 minClipPosition;
			fvec3 maxClipPosition;
			fvec2 size;
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
			bool isVisible;
			bool isWireframed;

			iss
				>> text3dId
				>> editorText3dId
				>> position.x
				>> position.y
				>> position.z
				>> rotation.x
				>> rotation.y
				>> rotation.z
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
				>> isVisible
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
				>> content;

			if(!_fe3d->text3d_isExisting(editorText3dId))
			{
				continue;
			}

			_duplicator->copyEditorText3d(text3dId, editorText3dId);

			_fe3d->text3d_setVisible(text3dId, isVisible);
			_fe3d->text3d_setPosition(text3dId, position);
			_fe3d->text3d_setRotation(text3dId, rotation);
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
			_fe3d->text3d_setMinClipPosition(text3dId, minClipPosition);
			_fe3d->text3d_setMaxClipPosition(text3dId, maxClipPosition);
			_fe3d->text3d_setWireframed(text3dId, isWireframed);
			_fe3d->text3d_setWireframeColor(text3dId, wireframeColor);
			_fe3d->text3d_setContent(text3dId, content);

			_loadedText3dIds.push_back(text3dId);
		}
		else if(lineType == "TEXT3D_AABB")
		{
			string text3dId;
			string aabbId;
			bool isVisible;

			iss
				>> text3dId
				>> isVisible;

			if(!_fe3d->text3d_isExisting(text3dId))
			{
				continue;
			}

			if(!_fe3d->aabb_isExisting(aabbId))
			{
				continue;
			}

			_fe3d->aabb_setVisible(aabbId, isVisible);
		}
		else if(lineType == "AABB")
		{
			string aabbId;
			string editorAabbId;
			fvec3 position;
			fvec3 size;
			fvec3 color;
			fvec3 minClipPosition;
			fvec3 maxClipPosition;
			bool isRaycastResponsive;
			bool isCollisionResponsive;
			bool isVisible;

			iss
				>> aabbId
				>> editorAabbId
				>> position.x
				>> position.y
				>> position.z
				>> size.x
				>> size.y
				>> size.z
				>> color.r
				>> color.g
				>> color.b
				>> isRaycastResponsive
				>> isCollisionResponsive
				>> isVisible
				>> minClipPosition.x
				>> minClipPosition.y
				>> minClipPosition.z
				>> maxClipPosition.x
				>> maxClipPosition.y
				>> maxClipPosition.z;

			if(!_fe3d->aabb_isExisting(editorAabbId))
			{
				continue;
			}

			_duplicator->copyEditorAabb(aabbId, editorAabbId);

			_fe3d->aabb_setVisible(aabbId, isVisible);
			_fe3d->aabb_setBasePosition(aabbId, position);
			_fe3d->aabb_setBaseSize(aabbId, size);
			_fe3d->aabb_setColor(aabbId, color);
			_fe3d->aabb_setMinClipPosition(aabbId, minClipPosition);
			_fe3d->aabb_setMaxClipPosition(aabbId, maxClipPosition);
			_fe3d->aabb_setRaycastResponsive(aabbId, isRaycastResponsive);
			_fe3d->aabb_setCollisionResponsive(aabbId, isCollisionResponsive);

			_loadedAabbIds.push_back(aabbId);
		}
		else if(lineType == "POINTLIGHT")
		{
			string pointlightId;
			string editorPointlightId;
			fvec3 position;
			fvec3 radius;
			fvec3 color;
			float intensity;
			int shape;
			bool isVisible;

			iss
				>> pointlightId
				>> editorPointlightId
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
				>> shape
				>> isVisible;

			if(!_fe3d->pointlight_isExisting(editorPointlightId))
			{
				continue;
			}

			_duplicator->copyEditorPointlight(pointlightId, editorPointlightId);

			_fe3d->pointlight_setVisible(pointlightId, isVisible);
			_fe3d->pointlight_setPosition(pointlightId, position);
			_fe3d->pointlight_setRadius(pointlightId, radius);
			_fe3d->pointlight_setColor(pointlightId, color);
			_fe3d->pointlight_setIntensity(pointlightId, intensity);
			_fe3d->pointlight_setShape(pointlightId, PointlightShapeType(shape));

			_loadedPointlightIds.push_back(pointlightId);
		}
		else if(lineType == "SPOTLIGHT")
		{
			string spotlightId;
			string editorSpotlightId;
			fvec3 color;
			fvec3 position;
			float yaw;
			float pitch;
			float intensity;
			float angle;
			float distance;
			bool isVisible;

			iss
				>> spotlightId
				>> editorSpotlightId
				>> position.x
				>> position.y
				>> position.z
				>> yaw
				>> pitch
				>> color.r
				>> color.g
				>> color.b
				>> intensity
				>> angle
				>> distance
				>> isVisible;

			if(!_fe3d->spotlight_isExisting(editorSpotlightId))
			{
				continue;
			}

			_duplicator->copyEditorSpotlight(spotlightId, editorSpotlightId);

			_fe3d->spotlight_setVisible(spotlightId, isVisible);
			_fe3d->spotlight_setPosition(spotlightId, position);
			_fe3d->spotlight_setYaw(spotlightId, yaw);
			_fe3d->spotlight_setPitch(spotlightId, pitch);
			_fe3d->spotlight_setColor(spotlightId, color);
			_fe3d->spotlight_setIntensity(spotlightId, intensity);
			_fe3d->spotlight_setAngle(spotlightId, angle);
			_fe3d->spotlight_setDistance(spotlightId, distance);

			_loadedSpotlightIds.push_back(spotlightId);
		}
		else if(lineType == "CAPTOR")
		{
			string captorId;
			string editorCaptorId;
			string exceptionId;
			fvec3 position;

			iss
				>> captorId
				>> editorCaptorId
				>> exceptionId
				>> position.x
				>> position.y
				>> position.z;

			exceptionId = (exceptionId == "?") ? "" : exceptionId;

			if(!_fe3d->captor_isExisting(editorCaptorId))
			{
				continue;
			}

			_duplicator->copyEditorCaptor(captorId, editorCaptorId);

			_fe3d->captor_setExceptionId(captorId, (_fe3d->model_isExisting(exceptionId) ? exceptionId : ""));
			_fe3d->captor_setPosition(captorId, position);
			_fe3d->captor_capture(captorId);

			_loadedCaptorIds.push_back(captorId);
		}
		else if(lineType == "SOUND3D")
		{
			string sound3dId;
			string editorSound3dId;
			fvec3 position;
			float maxVolume;
			float maxDistance;
			int startedCount;

			iss
				>> sound3dId
				>> editorSound3dId
				>> position.x
				>> position.y
				>> position.z
				>> maxVolume
				>> maxDistance
				>> startedCount;

			if(!_fe3d->sound3d_isExisting(editorSound3dId))
			{
				continue;
			}

			_duplicator->copyEditorSound3d(sound3dId, editorSound3dId);

			_fe3d->sound3d_setPosition(sound3dId, position);
			_fe3d->sound3d_setMaxVolume(sound3dId, maxVolume);
			_fe3d->sound3d_setMaxDistance(sound3dId, maxDistance);

			for(int index = 0; index < startedCount; index++)
			{
				float currentTime;
				int playCount;
				bool isStarted;
				bool isPaused;

				iss
					>> isStarted
					>> isPaused
					>> playCount
					>> currentTime;

				if(isStarted)
				{
					_fe3d->sound3d_start(sound3dId, playCount, currentTime);
				}

				if(isPaused)
				{
					_fe3d->sound3d_pause(sound3dId, index);
				}
			}

			_loadedSound3dIds.push_back(sound3dId);
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
			fvec3 position;
			fvec3 center;
			float size;
			float lightness;
			float bias;
			int interval;
			int pcfCount;
			int quality;
			bool isFollowingCameraX;
			bool isFollowingCameraY;
			bool isFollowingCameraZ;

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
				>> pcfCount
				>> quality
				>> bias;

			_fe3d->graphics_setShadowsEnabled(true);
			_fe3d->graphics_setShadowPositionOffset(position);
			_fe3d->graphics_setShadowLookatOffset(center);
			_fe3d->graphics_setShadowSize(size);
			_fe3d->graphics_setShadowLightness(lightness);
			_fe3d->graphics_setShadowFollowingCameraX(isFollowingCameraX);
			_fe3d->graphics_setShadowFollowingCameraY(isFollowingCameraY);
			_fe3d->graphics_setShadowFollowingCameraZ(isFollowingCameraZ);
			_fe3d->graphics_setShadowInterval(interval);
			_fe3d->graphics_setShadowPcfCount(pcfCount);
			_fe3d->graphics_setShadowQuality(quality);
			_fe3d->graphics_setShadowBias(bias);
		}
		else if(lineType == "GRAPHICS_PLANAR_REFLECTIONS")
		{
			float height;
			int quality;

			iss
				>> height
				>> quality;

			_fe3d->graphics_setPlanarReflectionHeight(height);
			_fe3d->graphics_setPlanarReflectionQuality(quality);
		}
		else if(lineType == "GRAPHICS_PLANAR_REFRACTIONS")
		{
			float height;
			int quality;

			iss
				>> height
				>> quality;

			_fe3d->graphics_setPlanarRefractionHeight(height);
			_fe3d->graphics_setPlanarRefractionQuality(quality);
		}
		else if(lineType == "GRAPHICS_DOF")
		{
			float blurDistance;
			float maxDistance;
			int quality;
			bool isDynamic;

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
			fvec3 color;
			float minDistance;
			float maxDistance;
			float thickness;

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

			if(!isExported)
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