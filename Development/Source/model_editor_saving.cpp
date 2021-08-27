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
		// Check if a 3D entity for this model is existing
		if (_fe3d.modelEntity_isExisting(modelID))
		{
			// General data
			auto isMultiParted = _fe3d.modelEntity_isMultiParted(modelID);
			auto meshPath = _fe3d.modelEntity_getMeshPath(modelID);
			auto diffuseMapPath = isMultiParted ? "" : _fe3d.modelEntity_getDiffuseMapPath(modelID);
			auto emissionMapPath = isMultiParted ? "" : _fe3d.modelEntity_getEmissionMapPath(modelID);
			auto normalMapPath = isMultiParted ? "" : _fe3d.modelEntity_getNormalMapPath(modelID);
			auto reflectionMapPath = isMultiParted ? "" : _fe3d.modelEntity_getReflectionMapPath(modelID);
			auto modelSize = _fe3d.modelEntity_getSize(modelID);
			auto isFaceCulled = _fe3d.modelEntity_isFaceCulled(modelID);
			auto isTransparent = _fe3d.modelEntity_isTransparent(modelID);
			auto isSpecular = _fe3d.modelEntity_isSpecularLighted(modelID);
			auto specularFactor = _fe3d.modelEntity_getSpecularFactor(modelID);
			auto specularIntensity = _fe3d.modelEntity_getSpecularIntensity(modelID);
			auto reflectivity = _fe3d.modelEntity_getReflectivity(modelID);
			auto lightness = _fe3d.modelEntity_getLightness(modelID);
			auto color = _fe3d.modelEntity_getColor(modelID);
			auto uvRepeat = _fe3d.modelEntity_getUvRepeat(modelID);
			auto lodEntityID = _fe3d.modelEntity_getLevelOfDetailEntityID(modelID);
			auto isInstanced = _fe3d.modelEntity_isInstanced(modelID);
			auto isBright = _fe3d.modelEntity_isBright(modelID);
			auto reflectionType = static_cast<unsigned int>(_fe3d.modelEntity_getReflectionType(modelID));

			// AABB data
			vector<string> aabbIDs;
			vector<Vec3> aabbPositions;
			vector<Vec3> aabbSizes;
			if (!isInstanced)
			{
				for (const auto& aabbID : _fe3d.aabbEntity_getBoundIDs(modelID, true, false))
				{
					aabbIDs.push_back(aabbID.substr(string(modelID + "_").size()));
					aabbPositions.push_back(_fe3d.aabbEntity_getPosition(aabbID));
					aabbSizes.push_back(_fe3d.aabbEntity_getSize(aabbID));
				}
			}

			// Perform empty string & space conversions
			meshPath = (meshPath.empty()) ? "?" : meshPath;
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
			reflectionMapPath = (reflectionMapPath.empty()) ? "?" : reflectionMapPath;
			normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;
			lodEntityID = (lodEntityID.empty()) ? "?" : lodEntityID;
			replace(meshPath.begin(), meshPath.end(), ' ', '?');
			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
			replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
			replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
			replace(lodEntityID.begin(), lodEntityID.end(), ' ', '?');

			// Write general data
			file <<
				modelID << " " <<
				meshPath << " " <<
				diffuseMapPath << " " <<
				emissionMapPath << " " <<
				reflectionMapPath << " " <<
				normalMapPath << " " <<
				modelSize.x << " " <<
				modelSize.y << " " <<
				modelSize.z << " " <<
				isFaceCulled << " " <<
				isTransparent << " " <<
				reflectionType << " " <<
				isSpecular << " " <<
				specularFactor << " " <<
				specularIntensity << " " <<
				reflectivity << " " <<
				lightness << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				uvRepeat << " " <<
				lodEntityID << " " <<
				isInstanced << " " <<
				isBright;

			// Add space
			if (!aabbIDs.empty())
			{
				file << " ";
			}

			// Write AABB data
			for (size_t i = 0; i < aabbIDs.size(); i++)
			{
				file <<
					aabbIDs[i] << " " <<
					aabbPositions[i].x << " " <<
					aabbPositions[i].y << " " <<
					aabbPositions[i].z << " " <<
					aabbSizes[i].x << " " <<
					aabbSizes[i].y << " " <<
					aabbSizes[i].z;

				// Add space
				if (i != (aabbIDs.size() - 1))
				{
					file << " ";
				}
			}

			// Add newline
			file << endl;
		}
		else
		{
			file << modelID << " ? ? ? ? ? 0.0 0.0 0.0 0 0 0 0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 ? 0\n";
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Model data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}