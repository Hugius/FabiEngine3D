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

	string line;

	while(getline(file, line))
	{
		string lineType;

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "SKY")
		{
			array<string, 6> cubeMapPaths{};
			string skyId;
			fvec3 color;
			fvec3 rotation;
			float lightness;
			int rotationOrder;

			auto iss = istringstream(line);

			iss
				>> skyId
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
				>> rotationOrder;

			for(auto & cubeMapPath : cubeMapPaths)
			{
				cubeMapPath = (cubeMapPath == "?") ? "" : cubeMapPath;

				replace(cubeMapPath.begin(), cubeMapPath.end(), '?', ' ');

				if(!cubeMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						cubeMapPath = ("projects\\" + getCurrentProjectId() + "\\" + cubeMapPath);
					}
				}
			}

			_fe3d->sky_create(skyId);
			_fe3d->sky_setCubeMaps(skyId, cubeMapPaths);
			_fe3d->sky_setLightness(skyId, lightness);
			_fe3d->sky_setRotation(skyId, rotation);
			_fe3d->sky_setColor(skyId, color);
			_fe3d->sky_setRotationOrder(skyId, DirectionOrderType(rotationOrder));

			_loadedSkyIds.push_back(skyId);
		}
		else if(lineType == "TERRAIN")
		{
			string terrainId;
			string heightMapPath;
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
			float maxHeight;
			float lightness;
			float specularShininess;
			float specularIntensity;
			int textureRepeat;
			int redTextureRepeat;
			int greenTextureRepeat;
			int blueTextureRepeat;
			bool isSpecular;

			auto iss = istringstream(line);

			iss
				>> terrainId
				>> heightMapPath
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
				>> specularIntensity;

			heightMapPath = (heightMapPath == "?") ? "" : heightMapPath;
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
			redNormalMapPath = (redNormalMapPath == "?") ? "" : redNormalMapPath;
			greenNormalMapPath = (greenNormalMapPath == "?") ? "" : greenNormalMapPath;
			blueNormalMapPath = (blueNormalMapPath == "?") ? "" : blueNormalMapPath;
			blendMapPath = (blendMapPath == "?") ? "" : blendMapPath;
			redDiffuseMapPath = (redDiffuseMapPath == "?") ? "" : redDiffuseMapPath;
			greenDiffuseMapPath = (greenDiffuseMapPath == "?") ? "" : greenDiffuseMapPath;
			blueDiffuseMapPath = (blueDiffuseMapPath == "?") ? "" : blueDiffuseMapPath;

			replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');
			replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			replace(redNormalMapPath.begin(), redNormalMapPath.end(), '?', ' ');
			replace(greenNormalMapPath.begin(), greenNormalMapPath.end(), '?', ' ');
			replace(blueNormalMapPath.begin(), blueNormalMapPath.end(), '?', ' ');
			replace(blendMapPath.begin(), blendMapPath.end(), '?', ' ');
			replace(redDiffuseMapPath.begin(), redDiffuseMapPath.end(), '?', ' ');
			replace(greenDiffuseMapPath.begin(), greenDiffuseMapPath.end(), '?', ' ');
			replace(blueDiffuseMapPath.begin(), blueDiffuseMapPath.end(), '?', ' ');

			if(!Configuration::getInst().isApplicationExported())
			{
				heightMapPath = ("projects\\" + getCurrentProjectId() + "\\" + heightMapPath);
			}

			_fe3d->terrain_create(terrainId, heightMapPath);

			if(_fe3d->terrain_isExisting(terrainId))
			{
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

				if(!diffuseMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
					}

					_fe3d->terrain_setDiffuseMap(terrainId, diffuseMapPath);
				}

				if(!normalMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						normalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
					}

					_fe3d->terrain_setNormalMap(terrainId, normalMapPath);
				}

				if(!redNormalMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						redNormalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + redNormalMapPath);
					}

					_fe3d->terrain_setRedNormalMap(terrainId, redNormalMapPath);
				}

				if(!greenNormalMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						greenNormalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + greenNormalMapPath);
					}

					_fe3d->terrain_setGreenNormalMap(terrainId, greenNormalMapPath);
				}

				if(!blueNormalMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						blueNormalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + blueNormalMapPath);
					}

					_fe3d->terrain_setBlueNormalMap(terrainId, blueNormalMapPath);
				}

				if(!blendMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						blendMapPath = ("projects\\" + getCurrentProjectId() + "\\" + blendMapPath);
					}

					_fe3d->terrain_setBlendMap(terrainId, blendMapPath);
				}

				if(!redDiffuseMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						redDiffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + redDiffuseMapPath);
					}

					_fe3d->terrain_setRedDiffuseMap(terrainId, redDiffuseMapPath);
				}

				if(!greenDiffuseMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						greenDiffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + greenDiffuseMapPath);
					}

					_fe3d->terrain_setGreenDiffuseMap(terrainId, greenDiffuseMapPath);
				}

				if(!blueDiffuseMapPath.empty())
				{
					if(!Configuration::getInst().isApplicationExported())
					{
						blueDiffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + blueDiffuseMapPath);
					}

					_fe3d->terrain_setBlueDiffuseMap(terrainId, blueDiffuseMapPath);
				}

				_loadedTerrainIds.push_back(terrainId);
			}
		}
		else if(lineType == "WATER")
		{
			string waterId;
			string dudvMapPath;
			string normalMapPath;
			string heightMapPath;
			fvec3 color;
			fvec2 rippleSpeed;
			fvec2 waveSpeed;
			float size;
			float waveHeight;
			float specularShininess;
			float specularIntensity;
			float maxDepth;
			int textureRepeat;
			bool isSpecular;
			bool isReflective;
			bool isRefractive;
			bool isEdged;

			auto iss = istringstream(line);

			iss
				>> waterId
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
				>> maxDepth;

			dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
			normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
			heightMapPath = (heightMapPath == "?" ? "" : heightMapPath);

			replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
			replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			replace(heightMapPath.begin(), heightMapPath.end(), '?', ' ');

			_fe3d->water_create(waterId);
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

			if(!dudvMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					dudvMapPath = ("projects\\" + getCurrentProjectId() + "\\" + dudvMapPath);
				}

				_fe3d->water_setDudvMap(waterId, dudvMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					normalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
				}

				_fe3d->water_setNormalMap(waterId, normalMapPath);
			}

			if(!heightMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					heightMapPath = ("projects\\" + getCurrentProjectId() + "\\" + heightMapPath);
				}

				_fe3d->water_setHeightMap(waterId, heightMapPath);
			}

			_loadedWaterIds.push_back(waterId);
		}
		else if(lineType == "MODEL")
		{
			string modelId;
			string meshPath;
			string levelOfDetailId;
			fvec3 size;
			float levelOfDetailDistance;
			int rotationOrder;
			bool isShadowed;
			bool isReflected;
			bool isRefracted;

			iss
				>> modelId
				>> meshPath
				>> size.x
				>> size.y
				>> size.z
				>> levelOfDetailId
				>> levelOfDetailDistance
				>> rotationOrder
				>> isShadowed
				>> isReflected
				>> isRefracted;

			meshPath = (meshPath == "?") ? "" : meshPath;
			levelOfDetailId = (levelOfDetailId == "?") ? "" : levelOfDetailId;

			replace(meshPath.begin(), meshPath.end(), '?', ' ');

			if(!Configuration::getInst().isApplicationExported())
			{
				meshPath = ("projects\\" + getCurrentProjectId() + "\\" + meshPath);
			}

			_fe3d->model_create(modelId, meshPath);

			if(_fe3d->model_isExisting(modelId))
			{
				_fe3d->model_setVisible(modelId, false);
				_fe3d->model_setBaseSize(modelId, size);
				_fe3d->model_setLevelOfDetailId(modelId, levelOfDetailId);
				_fe3d->model_setLevelOfDetailDistance(modelId, levelOfDetailDistance);
				_fe3d->model_setRotationOrder(modelId, DirectionOrderType(rotationOrder));

				_loadedModelIds.push_back(modelId);
			}
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
				>> minAlpha;

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

			if(!diffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				_fe3d->model_setDiffuseMap(modelId, partId, diffuseMapPath);
			}

			if(!specularMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					specularMapPath = ("projects\\" + getCurrentProjectId() + "\\" + specularMapPath);
				}

				_fe3d->model_setSpecularMap(modelId, partId, specularMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					emissionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + emissionMapPath);
				}

				_fe3d->model_setEmissionMap(modelId, partId, emissionMapPath);
			}

			if(!reflectionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					reflectionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + reflectionMapPath);
				}

				_fe3d->model_setReflectionMap(modelId, partId, reflectionMapPath);
			}

			if(!refractionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					refractionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + refractionMapPath);
				}

				_fe3d->model_setRefractionMap(modelId, partId, refractionMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					normalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
				}

				_fe3d->model_setNormalMap(modelId, partId, normalMapPath);
			}
		}
		else if(lineType == "MODEL_AABB")
		{
			string modelId;
			string aabbId;
			fvec3 position;
			fvec3 size;

			iss
				>> modelId
				>> aabbId
				>> position.x
				>> position.y
				>> position.z
				>> size.x
				>> size.y
				>> size.z;

			if(!_fe3d->model_isExisting(modelId))
			{
				continue;
			}

			_fe3d->aabb_create(aabbId, false);
			_fe3d->aabb_setVisible(aabbId, false);
			_fe3d->aabb_setParentId(aabbId, modelId);
			_fe3d->aabb_setParentType(aabbId, AabbParentType::MODEL);
			_fe3d->aabb_setLocalPosition(aabbId, position);
			_fe3d->aabb_setLocalSize(aabbId, size);
		}
		else if(lineType == "MODEL_ANIMATION3D")
		{

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

			auto iss = istringstream(line);

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
					diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				_fe3d->quad3d_setDiffuseMap(quad3dId, diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					emissionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + emissionMapPath);
				}

				_fe3d->quad3d_setEmissionMap(quad3dId, emissionMapPath);
			}

			_loadedQuad3dIds.push_back(quad3dId);
		}
		else if(lineType == "QUAD3D_AABB")
		{
			string quad3dId;

			auto iss = istringstream(line);

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

			auto iss = istringstream(line);

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
				fontMapPath = ("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
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

			auto iss = istringstream(line);

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

			auto iss = istringstream(line);

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

			auto iss = istringstream(line);

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

			auto iss = istringstream(line);

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

		}
		else if(lineType == "CAPTOR")
		{

		}
		else if(lineType == "GRAPHICS_AMBIENT_LIGHTING")
		{

		}
		else if(lineType == "GRAPHICS_DIRECTIONAL_LIGHTING")
		{

		}
		else if(lineType == "GRAPHICS_SHADOWS")
		{

		}
		else if(lineType == "GRAPHICS_REFLECTIONS")
		{

		}
		else if(lineType == "GRAPHICS_REFRACTIONS")
		{

		}
		else if(lineType == "GRAPHICS_DOF")
		{

		}
		else if(lineType == "GRAPHICS_FOG")
		{

		}
		else if(lineType == "GRAPHICS_LENS_FLARE")
		{

		}
		else if(lineType == "GRAPHICS_SKY_EXPOSURE")
		{

		}
		else if(lineType == "GRAPHICS_BLOOM")
		{

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