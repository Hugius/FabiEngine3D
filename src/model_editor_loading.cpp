#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
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
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::getMeshPathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\model.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `model.fe3d` missing!");
		return {};
	}

	vector<string> meshPaths;
	string line;
	while(getline(file, line))
	{
		string lineType;

		istringstream iss(line);

		iss >> lineType;

		if(lineType == "MODEL")
		{
			string modelID;
			string meshPath;

			iss >> modelID >> meshPath;

			meshPath = (meshPath == "?") ? "" : meshPath;

			replace(meshPath.begin(), meshPath.end(), '?', ' ');

			if(!Config::getInst().isApplicationExported())
			{
				meshPath = string("projects\\" + _currentProjectID + "\\" + meshPath);
			}

			meshPaths.push_back(meshPath);
		}
	}

	file.close();

	return meshPaths;
}

const vector<string> ModelEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::getImagePathsFromFile");
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\model.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `model.fe3d` missing!");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string lineType;

		istringstream iss(line);

		iss >> lineType;

		if(lineType == "MODEL")
		{
			string modelID;
			string meshPath;
			string levelOfDetailEntityId;
			fvec3 size;
			float levelOfDetailDistance;
			unsigned int rotationOrder;
			bool isShadowed;
			bool isReflected;

			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				levelOfDetailEntityId >>
				levelOfDetailDistance >>
				rotationOrder >>
				isShadowed >>
				isReflected;

			while(true)
			{
				string partId;
				iss >> partId;
				if(partId.empty())
				{
					break;
				}

				string diffuseMapPath;
				string emissionMapPath;
				string specularMapPath;
				string reflectionMapPath;
				string normalMapPath;
				fvec3 color;
				float textureRepeat;
				float specularShininess;
				float specularIntensity;
				float reflectivity;
				float lightness;
				float emissionIntensity;
				float opacity;
				unsigned int reflectionType;
				bool isSpecular;
				bool isReflective;
				bool isFaceCulled;
				bool isBright;

				iss >>
					diffuseMapPath >>
					emissionMapPath >>
					specularMapPath >>
					reflectionMapPath >>
					normalMapPath >>
					reflectionType >>
					isSpecular >>
					isReflective >>
					specularShininess >>
					specularIntensity >>
					reflectivity >>
					lightness >>
					color.r >>
					color.g >>
					color.b >>
					textureRepeat >>
					isFaceCulled >>
					isBright >>
					emissionIntensity >>
					opacity;

				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
				specularMapPath = (specularMapPath == "?") ? "" : specularMapPath;
				reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
				normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;

				replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
				replace(specularMapPath.begin(), specularMapPath.end(), '?', ' ');
				replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
				replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

				if(!diffuseMapPath.empty())
				{
					if(!Config::getInst().isApplicationExported())
					{
						diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
					}

					imagePaths.push_back(diffuseMapPath);
				}

				if(!emissionMapPath.empty())
				{
					if(!Config::getInst().isApplicationExported())
					{
						emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
					}

					imagePaths.push_back(emissionMapPath);
				}

				if(!specularMapPath.empty())
				{
					if(!Config::getInst().isApplicationExported())
					{
						specularMapPath = string("projects\\" + _currentProjectID + "\\" + specularMapPath);
					}

					imagePaths.push_back(specularMapPath);
				}

				if(!reflectionMapPath.empty())
				{
					if(!Config::getInst().isApplicationExported())
					{
						reflectionMapPath = string("projects\\" + _currentProjectID + "\\" + reflectionMapPath);
					}

					imagePaths.push_back(reflectionMapPath);
				}

				if(!normalMapPath.empty())
				{
					if(!Config::getInst().isApplicationExported())
					{
						normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
					}

					imagePaths.push_back(normalMapPath);
				}
			}
		}
	}

	file.close();

	return imagePaths;
}

const bool ModelEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::loadFromFile::1");
	}

	_loadedModelIDs.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\model.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `model.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string lineType;

		istringstream iss(line);

		iss >> lineType;

		if(lineType == "MODEL")
		{
			string modelID;
			string meshPath;
			string levelOfDetailEntityId;
			fvec3 size;
			float levelOfDetailDistance;
			unsigned int rotationOrder;
			bool isShadowed;
			bool isReflected;

			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				levelOfDetailEntityId >>
				levelOfDetailDistance >>
				rotationOrder >>
				isShadowed >>
				isReflected;

			meshPath = (meshPath == "?") ? "" : meshPath;
			levelOfDetailEntityId = (levelOfDetailEntityId == "?") ? "" : levelOfDetailEntityId;

			replace(meshPath.begin(), meshPath.end(), '?', ' ');
			replace(levelOfDetailEntityId.begin(), levelOfDetailEntityId.end(), '?', ' ');

			if(!Config::getInst().isApplicationExported())
			{
				meshPath = string("projects\\" + _currentProjectID + "\\" + meshPath);
			}

			_fe3d->model_create(modelID, meshPath);

			if(_fe3d->model_isExisting(modelID))
			{
				_loadedModelIDs.push_back(modelID);

				_fe3d->model_setVisible(modelID, false);
				_fe3d->model_setBaseSize(modelID, size);
				_fe3d->model_setLevelOfDetailEntityId(modelID, levelOfDetailEntityId);
				_fe3d->model_setLevelOfDetailDistance(modelID, levelOfDetailDistance);
				_fe3d->model_setRotationOrder(modelID, DirectionOrder(rotationOrder));

				while(true)
				{
					string partId;
					iss >> partId;

					if(partId.empty())
					{
						break;
					}

					string diffuseMapPath;
					string emissionMapPath;
					string specularMapPath;
					string reflectionMapPath;
					string normalMapPath;
					fvec3 color;
					float textureRepeat;
					float specularShininess;
					float specularIntensity;
					float reflectivity;
					float lightness;
					float emissionIntensity;
					float opacity;
					unsigned int reflectionType;
					bool isSpecular;
					bool isReflective;
					bool isFaceCulled;
					bool isBright;

					iss >>
						diffuseMapPath >>
						emissionMapPath >>
						specularMapPath >>
						reflectionMapPath >>
						normalMapPath >>
						reflectionType >>
						isSpecular >>
						isReflective >>
						specularShininess >>
						specularIntensity >>
						reflectivity >>
						lightness >>
						color.r >>
						color.g >>
						color.b >>
						textureRepeat >>
						isFaceCulled >>
						isBright >>
						emissionIntensity >>
						opacity;

					partId = (partId == "?") ? "" : partId;
					diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
					emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
					specularMapPath = (specularMapPath == "?") ? "" : specularMapPath;
					reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
					normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;

					replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
					replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
					replace(specularMapPath.begin(), specularMapPath.end(), '?', ' ');
					replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
					replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

					_fe3d->model_setColor(modelID, partId, color);
					_fe3d->model_setSpecular(modelID, partId, isSpecular);
					_fe3d->model_setSpecularShininess(modelID, partId, specularShininess);
					_fe3d->model_setSpecularIntensity(modelID, partId, specularIntensity);
					_fe3d->model_setReflectivity(modelID, partId, reflectivity);
					_fe3d->model_setLightness(modelID, partId, lightness);
					_fe3d->model_setTextureRepeat(modelID, partId, textureRepeat);
					_fe3d->model_setReflective(modelID, partId, isReflective);
					_fe3d->model_setReflectionType(modelID, partId, ReflectionType(reflectionType));
					_fe3d->model_setFaceCulled(modelID, partId, isFaceCulled);
					_fe3d->model_setBright(modelID, partId, isBright);
					_fe3d->model_setEmissionIntensity(modelID, partId, emissionIntensity);
					_fe3d->model_setOpacity(modelID, partId, opacity);

					if(!diffuseMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
						}

						_fe3d->model_setDiffuseMap(modelID, partId, diffuseMapPath);
					}

					if(!specularMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							specularMapPath = string("projects\\" + _currentProjectID + "\\" + specularMapPath);
						}

						_fe3d->model_setSpecularMap(modelID, partId, specularMapPath);
					}

					if(!emissionMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
						}

						_fe3d->model_setEmissionMap(modelID, partId, emissionMapPath);
					}

					if(!reflectionMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							reflectionMapPath = string("projects\\" + _currentProjectID + "\\" + reflectionMapPath);
						}

						_fe3d->model_setReflectionMap(modelID, partId, reflectionMapPath);
					}

					if(!normalMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
						}

						_fe3d->model_setNormalMap(modelID, partId, normalMapPath);
					}
				}
			}
		}
		else if(lineType == "AABB")
		{
			string aabbID;
			string modelID;
			fvec3 position;
			fvec3 size;

			iss >>
				aabbID >>
				modelID >>
				position.x >>
				position.y >>
				position.z >>
				size.x >>
				size.y >>
				size.z;

			_fe3d->aabb_create(aabbID, false);

			if(_fe3d->aabb_isExisting(aabbID))
			{
				_fe3d->aabb_setVisible(aabbID, false);
				_fe3d->aabb_setFollowParentVisibility(aabbID, false);
				_fe3d->aabb_setParentEntityId(aabbID, modelID);
				_fe3d->aabb_setParentEntityType(aabbID, AabbParentEntityType::MODEL);
				_fe3d->aabb_setLocalPosition(aabbID, position);
				_fe3d->aabb_setLocalSize(aabbID, size);
			}
		}
		else
		{
			Logger::throwError("ModelEditor::loadFromFile::2");
		}
	}

	file.close();

	Logger::throwInfo("Model editor data loaded!");

	return true;
}