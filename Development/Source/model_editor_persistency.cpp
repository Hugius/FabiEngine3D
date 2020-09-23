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

	// Clear modelnames list from previous loads
	_modelNames.clear();

	// Compose full models folder path
	string filePath = _fe3d.misc_getRootDirectory() + "User\\projects\\" + _currentProjectName + "\\data\\models.fe3d";

	// Load models file
	if (_fe3d.misc_isFileExisting(filePath)) // Check if models file exists
	{
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string modelName, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, lodEntityID;
			float uvRepeat, specularFactor, specularIntensity, lightness;
			bool isFaceCulled, isShadowed, isTransparent, isSpecular, isReflective;
			vec3 modelSize, color, boxSize;

			// For file extraction
			std::istringstream iss(line);

			// Extract from file
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
				boxSize.x >>
				boxSize.y >>
				boxSize.z >> 
				lodEntityID;

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
				vec3(color.r, color.g, color.b), uvRepeat, vec3(boxSize.x, boxSize.y, boxSize.z), lodEntityID);
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
		file.open(_fe3d.misc_getRootDirectory() + "User\\projects\\" + _currentProjectName + "\\data\\models.fe3d");

		// Write model data into file
		for (auto& modelName : _modelNames)
		{
			// Check if a 3D entity for this model is existing
			if (_fe3d.gameEntity_isExisting(modelName))
			{
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
				auto boxSize = _fe3d.aabbEntity_getSize(modelName);
				auto lodEntityID = _fe3d.gameEntity_getLevelOfDetailEntityID(modelName);

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

				// 1 model -> 1 line in file
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
					boxSize.x << " " <<
					boxSize.y << " " <<
					boxSize.z << " " <<
					lodEntityID << std::endl;
			}
			else
			{
				file << modelName << " ? ? ? ? ? 0.0 0.0 0.0 0 0 0 0 0.0 0.0 0.0 0.0 0 0.0 0.0 0.0 ?\n";
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Model data from project \"" + _currentProjectName + "\" saved!");
	}
}