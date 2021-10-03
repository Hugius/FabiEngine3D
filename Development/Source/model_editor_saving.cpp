#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;

bool ModelEditor::saveModelEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::saveModelEntitiesToFile");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Create or overwrite model file
	ofstream file(filePath);

	// Write model data
	for (const auto& modelID : _loadedModelIDs)
	{
		// Retrieve all values
		auto isMultiParted = _fe3d.modelEntity_isMultiParted(modelID);
		auto meshPath = _fe3d.modelEntity_getMeshPath(modelID);
		auto modelSize = _fe3d.modelEntity_getBaseSize(modelID);
		auto lodEntityID = _fe3d.modelEntity_getLevelOfDetailEntityID(modelID);
		auto isInstanced = _fe3d.modelEntity_isInstanced(modelID);
		auto isFaceCulled = _fe3d.modelEntity_isFaceCulled(modelID);

		// Perform empty string & space conversions
		meshPath = (meshPath.empty()) ? "?" : meshPath;
		lodEntityID = (lodEntityID.empty()) ? "?" : lodEntityID;
		replace(meshPath.begin(), meshPath.end(), ' ', '?');
		replace(lodEntityID.begin(), lodEntityID.end(), ' ', '?');

		// Write data to file
		file << "MODEL " <<
			modelID << " " <<
			meshPath << " " <<
			modelSize.x << " " <<
			modelSize.y << " " <<
			modelSize.z << " " <<
			lodEntityID << " " <<
			isInstanced << " " <<
			isFaceCulled;

		// Write space to file
		file << " ";

		// Write part data
		auto partIDs = _fe3d.modelEntity_getPartIDs(modelID);
		for (size_t i = 0; i < partIDs.size(); i++)
		{
			// Retrieve all values
			auto partID = partIDs[i];
			auto diffuseMapPath = _fe3d.modelEntity_getDiffuseMapPath(modelID, partID);
			auto emissionMapPath = _fe3d.modelEntity_getEmissionMapPath(modelID, partID);
			auto specularMapPath = _fe3d.modelEntity_getSpecularMapPath(modelID, partID);
			auto reflectionMapPath = _fe3d.modelEntity_getReflectionMapPath(modelID, partID);
			auto normalMapPath = _fe3d.modelEntity_getNormalMapPath(modelID, partID);
			auto isSpecular = _fe3d.modelEntity_isSpecular(modelID, partID);
			auto specularShininess = _fe3d.modelEntity_getSpecularShininess(modelID, partID);
			auto specularIntensity = _fe3d.modelEntity_getSpecularIntensity(modelID, partID);
			auto reflectivity = _fe3d.modelEntity_getReflectivity(modelID, partID);
			auto lightness = _fe3d.modelEntity_getLightness(modelID, partID);
			auto color = _fe3d.modelEntity_getColor(modelID, partID);
			auto textureRepeat = _fe3d.modelEntity_getTextureRepeat(modelID, partID);
			auto isReflective = _fe3d.modelEntity_isReflective(modelID, partID);
			auto reflectionType = static_cast<unsigned int>(_fe3d.modelEntity_getReflectionType(modelID, partID));

			// Perform empty string & space conversions
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
			if (i < (partIDs.size() - 1))
			{
				file << " ";
			}
		}

		// Write newline to file
		file << endl;

		// Check if model not instanced
		if (!isInstanced)
		{
			// Write AABB data
			for (const auto& aabbID : _fe3d.aabbEntity_getChildIDs(modelID, AabbParentType::MODEL_ENTITY))
			{
				// Retrieve all values
				auto position = _fe3d.aabbEntity_getPosition(aabbID);
				auto size = _fe3d.aabbEntity_getSize(aabbID);

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
	Logger::throwInfo("Model data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}