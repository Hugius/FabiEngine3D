#include "model_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> ModelEditor::getMeshPathsFromFile() const
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\model.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `model.fe3d` does not exist");

		return {};
	}

	vector<string> meshPaths = {};
	string line;

	while(getline(file, line))
	{
		string lineType;

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "MODEL")
		{
			string modelId;
			string meshPath;

			iss
				>> modelId
				>> meshPath;

			meshPath = (meshPath == "?") ? "" : meshPath;

			replace(meshPath.begin(), meshPath.end(), '?', ' ');

			if(!Configuration::getInst().isApplicationExported())
			{
				meshPath = ("projects\\" + getCurrentProjectId() + "\\" + meshPath);
			}

			meshPaths.push_back(meshPath);
		}
	}

	file.close();

	return meshPaths;
}

const vector<string> ModelEditor::getImagePathsFromFile() const
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\model.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `model.fe3d` does not exist");

		return {};
	}

	vector<string> imagePaths = {};
	string line;

	while(getline(file, line))
	{
		string lineType;

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "PART")
		{
			string modelId;
			string partId;
			string diffuseMapPath;
			string emissionMapPath;
			string specularMapPath;
			string reflectionMapPath;
			string refractionMapPath;
			string normalMapPath;

			iss
				>> modelId
				>> partId
				>> diffuseMapPath
				>> emissionMapPath
				>> specularMapPath
				>> reflectionMapPath
				>> refractionMapPath
				>> normalMapPath;

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

			if(!diffuseMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					diffuseMapPath = ("projects\\" + getCurrentProjectId() + "\\" + diffuseMapPath);
				}

				imagePaths.push_back(diffuseMapPath);
			}

			if(!emissionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					emissionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + emissionMapPath);
				}

				imagePaths.push_back(emissionMapPath);
			}

			if(!specularMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					specularMapPath = ("projects\\" + getCurrentProjectId() + "\\" + specularMapPath);
				}

				imagePaths.push_back(specularMapPath);
			}

			if(!reflectionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					reflectionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + reflectionMapPath);
				}

				imagePaths.push_back(reflectionMapPath);
			}

			if(!refractionMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					refractionMapPath = ("projects\\" + getCurrentProjectId() + "\\" + refractionMapPath);
				}

				imagePaths.push_back(refractionMapPath);
			}

			if(!normalMapPath.empty())
			{
				if(!Configuration::getInst().isApplicationExported())
				{
					normalMapPath = ("projects\\" + getCurrentProjectId() + "\\" + normalMapPath);
				}

				imagePaths.push_back(normalMapPath);
			}
		}
	}

	file.close();

	return imagePaths;
}

const bool ModelEditor::loadModelsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\model.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `model.fe3d` does not exist");

		return false;
	}

	string line;

	while(getline(file, line))
	{
		string lineType;

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "MODEL")
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
			replace(levelOfDetailId.begin(), levelOfDetailId.end(), '?', ' ');

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

				sort(_loadedModelIds.begin(), _loadedModelIds.end());
			}
		}
		else if(lineType == "PART")
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
			float minTextureAlpha;
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
				>> minTextureAlpha;

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
			_fe3d->model_setMinTextureAlpha(modelId, partId, minTextureAlpha);

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
		else if(lineType == "AABB")
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
		else
		{
			abort();
		}
	}

	file.close();

	Logger::throwInfo("Model editor data loaded");

	return true;
}