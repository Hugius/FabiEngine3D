#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

const bool ModelEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + _currentProjectID + "\\data\\model.fe3d");

	for(const auto& modelID : _loadedModelIDs)
	{
		auto isMultiParted = _fe3d->model_isMultiParted(modelID);
		auto meshPath = _fe3d->model_getMeshPath(modelID);
		auto modelSize = _fe3d->model_getBaseSize(modelID);
		auto levelOfDetailEntityID = _fe3d->model_getLevelOfDetailEntityID(modelID);
		auto levelOfDetailDistance = _fe3d->model_getLevelOfDetailDistance(modelID);
		auto rotationOrder = static_cast<unsigned int>(_fe3d->model_getRotationOrder(modelID));

		meshPath = string(meshPath.empty() ? "" : meshPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		meshPath = (meshPath.empty()) ? "?" : meshPath;
		levelOfDetailEntityID = (levelOfDetailEntityID.empty()) ? "?" : levelOfDetailEntityID;

		replace(meshPath.begin(), meshPath.end(), ' ', '?');
		replace(levelOfDetailEntityID.begin(), levelOfDetailEntityID.end(), ' ', '?');

		file << "MODEL " <<
			modelID << " " <<
			meshPath << " " <<
			modelSize.x << " " <<
			modelSize.y << " " <<
			modelSize.z << " " <<
			levelOfDetailEntityID << " " <<
			levelOfDetailDistance << " " <<
			rotationOrder;

		file << " ";

		auto partIDs = _fe3d->model_getPartIDs(modelID);
		for(size_t i = 0; i < partIDs.size(); i++)
		{
			auto partID = partIDs[i];
			auto diffuseMapPath = _fe3d->model_getDiffuseMapPath(modelID, partID);
			auto emissionMapPath = _fe3d->model_getEmissionMapPath(modelID, partID);
			auto specularMapPath = _fe3d->model_getSpecularMapPath(modelID, partID);
			auto reflectionMapPath = _fe3d->model_getReflectionMapPath(modelID, partID);
			auto normalMapPath = _fe3d->model_getNormalMapPath(modelID, partID);
			auto isSpecular = _fe3d->model_isSpecular(modelID, partID);
			auto specularShininess = _fe3d->model_getSpecularShininess(modelID, partID);
			auto specularIntensity = _fe3d->model_getSpecularIntensity(modelID, partID);
			auto reflectivity = _fe3d->model_getReflectivity(modelID, partID);
			auto lightness = _fe3d->model_getLightness(modelID, partID);
			auto color = _fe3d->model_getColor(modelID, partID);
			auto textureRepeat = _fe3d->model_getTextureRepeat(modelID, partID);
			auto isReflective = _fe3d->model_isReflective(modelID, partID);
			auto reflectionType = static_cast<unsigned int>(_fe3d->model_getReflectionType(modelID, partID));
			auto isFaceCulled = _fe3d->model_isFaceCulled(modelID, partID);

			diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
			emissionMapPath = string(emissionMapPath.empty() ? "" : emissionMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
			specularMapPath = string(specularMapPath.empty() ? "" : specularMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
			reflectionMapPath = string(reflectionMapPath.empty() ? "" : reflectionMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
			normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

			partID = (partID.empty()) ? "?" : partID;
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
			specularMapPath = (specularMapPath.empty()) ? "?" : specularMapPath;
			reflectionMapPath = (reflectionMapPath.empty()) ? "?" : reflectionMapPath;
			normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
			replace(specularMapPath.begin(), specularMapPath.end(), ' ', '?');
			replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
			replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');

			file <<
				partID << " " <<
				diffuseMapPath << " " <<
				emissionMapPath << " " <<
				specularMapPath << " " <<
				reflectionMapPath << " " <<
				normalMapPath << " " <<
				reflectionType << " " <<
				isSpecular << " " <<
				isReflective << " " <<
				specularShininess << " " <<
				specularIntensity << " " <<
				reflectivity << " " <<
				lightness << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				textureRepeat << " " <<
				isFaceCulled;

			if(i < (partIDs.size() - 1))
			{
				file << " ";
			}
		}

		file << endl;

		for(const auto& aabbID : _fe3d->aabb_getChildIDs(modelID, AabbParentEntityType::MODEL))
		{
			auto position = _fe3d->aabb_getPosition(aabbID);
			auto size = _fe3d->aabb_getSize(aabbID);

			file << "AABB " <<
				aabbID << " " <<
				modelID << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				size.x << " " <<
				size.y << " " <<
				size.z << endl;
		}
	}

	file.close();

	Logger::throwInfo("Model editor data saved!");

	return true;
}