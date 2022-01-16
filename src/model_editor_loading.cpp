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
		istringstream iss(line);

		string lineType;
		iss >> lineType;

		if(lineType == "MODEL")
		{
			string modelID, meshPath;

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

	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		istringstream iss(line);

		string lineType;
		iss >> lineType;

		if(lineType == "MODEL")
		{
			string modelID, meshPath, levelOfDetailEntityID;
			float levelOfDetailDistance;
			unsigned int rotationOrder;
			fvec3 size;

			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				levelOfDetailEntityID >>
				levelOfDetailDistance >>
				rotationOrder;

			while(true)
			{
				string partID;
				iss >> partID;
				if(partID.empty())
				{
					break;
				}

				string diffuseMapPath, emissionMapPath, specularMapPath, reflectionMapPath, normalMapPath;
				fvec3 color;
				float textureRepeat, specularShininess, specularIntensity, reflectivity, lightness;
				unsigned int reflectionType;
				bool isSpecular, isReflective, isFaceCulled;

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
					isFaceCulled;

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

					texturePaths.push_back(diffuseMapPath);
				}

				if(!emissionMapPath.empty())
				{
					if(!Config::getInst().isApplicationExported())
					{
						emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
					}

					texturePaths.push_back(emissionMapPath);
				}

				if(!specularMapPath.empty())
				{
					if(!Config::getInst().isApplicationExported())
					{
						specularMapPath = string("projects\\" + _currentProjectID + "\\" + specularMapPath);
					}

					texturePaths.push_back(specularMapPath);
				}

				if(!reflectionMapPath.empty())
				{
					if(!Config::getInst().isApplicationExported())
					{
						reflectionMapPath = string("projects\\" + _currentProjectID + "\\" + reflectionMapPath);
					}

					texturePaths.push_back(reflectionMapPath);
				}

				if(!normalMapPath.empty())
				{
					if(!Config::getInst().isApplicationExported())
					{
						normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
					}

					texturePaths.push_back(normalMapPath);
				}
			}
		}
	}

	file.close();

	return texturePaths;
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
		istringstream iss(line);

		string lineType;
		iss >> lineType;

		if(lineType == "MODEL")
		{
			string modelID, meshPath, levelOfDetailEntityID;
			float levelOfDetailDistance;
			unsigned int rotationOrder;
			fvec3 size;

			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				levelOfDetailEntityID >>
				levelOfDetailDistance >>
				rotationOrder;

			meshPath = (meshPath == "?") ? "" : meshPath;
			levelOfDetailEntityID = (levelOfDetailEntityID == "?") ? "" : levelOfDetailEntityID;

			replace(meshPath.begin(), meshPath.end(), '?', ' ');
			replace(levelOfDetailEntityID.begin(), levelOfDetailEntityID.end(), '?', ' ');

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
				_fe3d->model_setLevelOfDetailEntityID(modelID, levelOfDetailEntityID);
				_fe3d->model_setLevelOfDetailDistance(modelID, levelOfDetailDistance);
				_fe3d->model_setRotationOrder(modelID, DirectionOrder(rotationOrder));

				while(true)
				{
					string partID;
					iss >> partID;

					if(partID.empty())
					{
						break;
					}

					if(!_fe3d->model_hasPart(modelID, partID))
					{
						continue;
					}

					string diffuseMapPath, emissionMapPath, specularMapPath, reflectionMapPath, normalMapPath;
					fvec3 color;
					float textureRepeat, specularShininess, specularIntensity, reflectivity, lightness;
					unsigned int reflectionType;
					bool isSpecular, isReflective, isFaceCulled;

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
						isFaceCulled;

					partID = (partID == "?") ? "" : partID;
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

					_fe3d->model_setColor(modelID, partID, color);
					_fe3d->model_setSpecular(modelID, partID, isSpecular);
					_fe3d->model_setSpecularShininess(modelID, partID, specularShininess);
					_fe3d->model_setSpecularIntensity(modelID, partID, specularIntensity);
					_fe3d->model_setReflectivity(modelID, partID, reflectivity);
					_fe3d->model_setLightness(modelID, partID, lightness);
					_fe3d->model_setTextureRepeat(modelID, partID, textureRepeat);
					_fe3d->model_setReflective(modelID, partID, isReflective);
					_fe3d->model_setReflectionType(modelID, partID, ReflectionType(reflectionType));
					_fe3d->model_setFaceCulled(modelID, partID, isFaceCulled);

					if(!diffuseMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
						}

						_fe3d->model_setDiffuseMap(modelID, partID, diffuseMapPath);
					}

					if(!specularMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							specularMapPath = string("projects\\" + _currentProjectID + "\\" + specularMapPath);
						}

						_fe3d->model_setSpecularMap(modelID, partID, specularMapPath);
					}

					if(!emissionMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
						}

						_fe3d->model_setEmissionMap(modelID, partID, emissionMapPath);
					}

					if(!reflectionMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							reflectionMapPath = string("projects\\" + _currentProjectID + "\\" + reflectionMapPath);
						}

						_fe3d->model_setReflectionMap(modelID, partID, reflectionMapPath);
					}

					if(!normalMapPath.empty())
					{
						if(!Config::getInst().isApplicationExported())
						{
							normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
						}

						_fe3d->model_setNormalMap(modelID, partID, normalMapPath);
					}
				}
			}
		}
		else if(lineType == "AABB")
		{
			string aabbID, modelID;
			fvec3 position, size;

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

			_fe3d->aabb_setParentEntityID(aabbID, modelID);
			_fe3d->aabb_setParentEntityType(aabbID, AabbParentEntityType::MODEL);
			_fe3d->aabb_setLocalPosition(aabbID, position);
			_fe3d->aabb_setLocalSize(aabbID, size);
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