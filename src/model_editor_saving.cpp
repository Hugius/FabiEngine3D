#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

const bool ModelEditor::saveModelEntitiesToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::saveModelEntitiesToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\model.fe3d");

	// Write model data
	for(const auto& modelID : _loadedModelIDs)
	{
		// Retrieve all values
		auto isMultiParted = _fe3d.model_isMultiParted(modelID);
		auto meshPath = _fe3d.model_getMeshPath(modelID);
		auto modelSize = _fe3d.model_getBaseSize(modelID);
		auto levelOfDetailEntityID = _fe3d.model_getLevelOfDetailID(modelID);
		auto isInstanced = _fe3d.model_isInstanced(modelID);
		auto isFaceCulled = _fe3d.model_isFaceCulled(modelID);
		auto rotationOrder = static_cast<unsigned int>(_fe3d.model_getRotationOrder(modelID));

		// Convert to short path
		meshPath = string(meshPath.empty() ? "" : meshPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

		// Convert empty string
		meshPath = (meshPath.empty()) ? "?" : meshPath;
		levelOfDetailEntityID = (levelOfDetailEntityID.empty()) ? "?" : levelOfDetailEntityID;

		// Convert spaces
		replace(meshPath.begin(), meshPath.end(), ' ', '?');
		replace(levelOfDetailEntityID.begin(), levelOfDetailEntityID.end(), ' ', '?');

		// Write data to file
		file << "MODEL " <<
			modelID << " " <<
			meshPath << " " <<
			modelSize.x << " " <<
			modelSize.y << " " <<
			modelSize.z << " " <<
			levelOfDetailEntityID << " " <<
			isInstanced << " " <<
			isFaceCulled << " " <<
			rotationOrder;

		// Write space to file
		file << " ";

		// Write part data
		auto partIDs = _fe3d.model_getPartIDs(modelID);
		for(size_t i = 0; i < partIDs.size(); i++)
		{
			// Retrieve all values
			auto partID = partIDs[i];
			auto diffuseMapPath = _fe3d.model_getDiffuseMapPath(modelID, partID);
			auto emissionMapPath = _fe3d.model_getEmissionMapPath(modelID, partID);
			auto specularMapPath = _fe3d.model_getSpecularMapPath(modelID, partID);
			auto reflectionMapPath = _fe3d.model_getReflectionMapPath(modelID, partID);
			auto normalMapPath = _fe3d.model_getNormalMapPath(modelID, partID);
			auto isSpecular = _fe3d.model_isSpecular(modelID, partID);
			auto specularShininess = _fe3d.model_getSpecularShininess(modelID, partID);
			auto specularIntensity = _fe3d.model_getSpecularIntensity(modelID, partID);
			auto reflectivity = _fe3d.model_getReflectivity(modelID, partID);
			auto lightness = _fe3d.model_getLightness(modelID, partID);
			auto color = _fe3d.model_getColor(modelID, partID);
			auto textureRepeat = _fe3d.model_getTextureRepeat(modelID, partID);
			auto isReflective = _fe3d.model_isReflective(modelID, partID);
			auto reflectionType = static_cast<unsigned int>(_fe3d.model_getReflectionType(modelID, partID));

			// Convert to short path
			diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
			emissionMapPath = string(emissionMapPath.empty() ? "" : emissionMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
			specularMapPath = string(specularMapPath.empty() ? "" : specularMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
			reflectionMapPath = string(reflectionMapPath.empty() ? "" : reflectionMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));
			normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

			// Convert empty string
			partID = (partID.empty()) ? "?" : partID;
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
			specularMapPath = (specularMapPath.empty()) ? "?" : specularMapPath;
			reflectionMapPath = (reflectionMapPath.empty()) ? "?" : reflectionMapPath;
			normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;

			// Convert spaces
			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
			replace(specularMapPath.begin(), specularMapPath.end(), ' ', '?');
			replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
			replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');

			// Write data to file
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
				textureRepeat;

			// Write space to file
			if(i < (partIDs.size() - 1))
			{
				file << " ";
			}
		}

		// Write newline to file
		file << endl;

		// Check if model not instanced
		if(!isInstanced)
		{
			// Write AABB data
			for(const auto& aabbID : _fe3d.aabb_getChildIDs(modelID, AabbParentEntityType::MODEL))
			{
				// Retrieve all values
				auto position = _fe3d.aabb_getPosition(aabbID);
				auto size = _fe3d.aabb_getSize(aabbID);

				// Write data to file
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
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Model data saved!");

	// Return
	return true;
}