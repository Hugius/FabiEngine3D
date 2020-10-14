#include "model_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

void ModelEditor::loadModels()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	// Clear names list from previous loads
	_modelNames.clear();

	// Compose full folder path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\model.fe3d";

	// Check if model file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string modelName, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, lodEntityID;
			float uvRepeat, specularFactor, specularIntensity, lightness;
			bool isFaceCulled, isShadowed, isTransparent, isSpecular, isReflective, isInstanced;
			vec3 modelSize, color;
			vector<string> aabbNames;
			vector<vec3> aabbPositions;
			vector<vec3> aabbSizes;

			// For file extraction
			std::istringstream iss(line);

			// Extract general data from file
			iss >>
				modelName >>
				objPath >>
				diffuseMapPath >>
				lightMapPath >>
				reflectionMapPath >>
				normalMapPath >>
				modelSize.x >>
				modelSize.y >>
				modelSize.z >>
				isFaceCulled >>
				isShadowed >>
				isTransparent >>
				isReflective >>
				isSpecular >>
				specularFactor >>
				specularIntensity >>
				lightness >>
				color.r >>
				color.g >>
				color.b >>
				uvRepeat >>
				lodEntityID >>
				isInstanced;

			// Extract AABB data from file
			while (true)
			{
				// Check if file has AABB data left
				string name;
				vec3 position, size;
				iss >> name;
				if (name == "")
				{
					break;
				}
				else
				{
					iss >> position.x >> position.y >> position.z >> size.x >> size.y >> size.z;
					aabbNames.push_back(name);
					aabbPositions.push_back(position);
					aabbSizes.push_back(size);
				}
			}

			// Perform empty string & space conversions
			objPath = (objPath == "?") ? "" : objPath;
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			lightMapPath = (lightMapPath == "?") ? "" : lightMapPath;
			reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
			normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
			lodEntityID = (lodEntityID == "?") ? "" : lodEntityID;
			std::replace(objPath.begin(), objPath.end(), '?', ' ');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			std::replace(lightMapPath.begin(), lightMapPath.end(), '?', ' ');
			std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
			std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			std::replace(lodEntityID.begin(), lodEntityID.end(), '?', ' ');

			// Add new model
			_addModel(modelName, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, modelSize, isFaceCulled, isShadowed,
				isTransparent, isReflective, isSpecular, specularFactor, specularIntensity, lightness,
				vec3(color.r, color.g, color.b), uvRepeat, lodEntityID, isInstanced, aabbNames, aabbPositions, aabbSizes);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Model data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void ModelEditor::save()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite models file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\model.fe3d");

		// Write model data into file
		for (auto& modelName : _modelNames)
		{
			// Check if a 3D entity for this model is existing
			if (_fe3d.gameEntity_isExisting(modelName))
			{
				// General data
				auto objPath = _fe3d.gameEntity_getObjPath(modelName);
				auto diffuseMapPath = _fe3d.gameEntity_getDiffuseMapPath(modelName);
				auto lightMapPath = _fe3d.gameEntity_getLightMapPath(modelName);
				auto reflectionMapPath = _fe3d.gameEntity_getReflectionMapPath(modelName);
				auto normalMapPath = _fe3d.gameEntity_getNormalMapPath(modelName);
				auto modelSize = _fe3d.gameEntity_getSize(modelName);
				auto isFaceCulled = _fe3d.gameEntity_isFaceCulled(modelName);
				auto isShadowed = _fe3d.gameEntity_isShadowed(modelName);
				auto isTransparent = _fe3d.gameEntity_isTransparent(modelName);
				auto isReflective = _fe3d.gameEntity_isSceneReflective(modelName);
				auto isSpecular = _fe3d.gameEntity_isSpecularLighted(modelName);
				auto specularFactor = _fe3d.gameEntity_getSpecularFactor(modelName);
				auto specularStrength = _fe3d.gameEntity_getSpecularIntensity(modelName);
				auto lightness = _fe3d.gameEntity_getLightness(modelName);
				auto color = _fe3d.gameEntity_getColor(modelName);
				auto uvRepeat = _fe3d.gameEntity_getUvRepeat(modelName);
				auto lodEntityID = _fe3d.gameEntity_getLevelOfDetailEntityID(modelName);
				auto isInstanced = _fe3d.gameEntity_isInstanced(modelName);

				// AABB data
				vector<string> aabbNames;
				vector<vec3> aabbPositions;
				vector<vec3> aabbSizes;
				for (auto& aabbID : _fe3d.aabbEntity_getBoundIDs(modelName, true, false))
				{
					aabbNames.push_back(aabbID.substr(string(modelName + "_").size()));
					aabbPositions.push_back(_fe3d.aabbEntity_getPosition(aabbID));
					aabbSizes.push_back(_fe3d.aabbEntity_getSize(aabbID));
				}
				
				// Perform empty string & space conversions
				objPath = (objPath == "") ? "?" : objPath;
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				lightMapPath = (lightMapPath == "") ? "?" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "") ? "?" : reflectionMapPath;
				normalMapPath = (normalMapPath == "") ? "?" : normalMapPath;
				lodEntityID = (lodEntityID == "") ? "?" : lodEntityID;
				std::replace(objPath.begin(), objPath.end(), ' ', '?');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
				std::replace(lightMapPath.begin(), lightMapPath.end(), ' ', '?');
				std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
				std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
				std::replace(lodEntityID.begin(), lodEntityID.end(), ' ', '?');

				// NOTE: 1 model -> 1 line in file

				// Write general data
				file <<
					modelName << " " <<
					objPath << " " <<
					diffuseMapPath << " " <<
					lightMapPath << " " <<
					reflectionMapPath << " " <<
					normalMapPath << " " <<
					modelSize.x << " " <<
					modelSize.y << " " <<
					modelSize.z << " " <<
					isFaceCulled << " " <<
					isShadowed << " " <<
					isTransparent << " " <<
					isReflective << " " <<
					isSpecular << " " <<
					specularFactor << " " <<
					specularStrength << " " <<
					lightness << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << " " <<
					uvRepeat << " " <<
					lodEntityID << " " <<
					isInstanced << " ";

				// Write AABB data
				for (unsigned int i = 0; i < aabbNames.size(); i++)
				{
					file << 
						aabbNames[i] << " " << 
						aabbPositions[i].x << " " << 
						aabbPositions[i].y << " " <<
						aabbPositions[i].z << " " << 
						aabbSizes[i].x << " " <<
						aabbSizes[i].y << " " <<
						aabbSizes[i].z;
					
					// Add space
					if (i != (aabbNames.size() - 1))
					{
						file << " ";
					}
				}
					
				file << std::endl;
			}
			else
			{
				file << modelName << " ? ? ? ? ? 0.0 0.0 0.0 0 0 0 0 0.0 0.0 0.0 0.0 0 ?\n";
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Model data from project \"" + _currentProjectName + "\" saved!");
	}
}