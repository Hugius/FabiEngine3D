#include "model_editor.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

const vector<string> ModelEditor::getAllTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded --> ModelEditor::preLoadGameEntitiesFromFile()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\model.fe3d";

	// Check if model file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Temporary values
		std::ifstream file(filePath);
		string line;
		vector<string> objPaths;
		vector<string> texturePaths;

		// Read model data
		while (std::getline(file, line))
		{
			// Temporary values
			string modelID, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath;
			std::istringstream iss(line);

			// Extract data
			iss >> modelID >> objPath >> diffuseMapPath >> lightMapPath >> reflectionMapPath >> normalMapPath;

			// Perform empty string & space conversions
			objPath = (objPath == "?") ? "" : objPath;
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			lightMapPath = (lightMapPath == "?") ? "" : lightMapPath;
			reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
			normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
			std::replace(objPath.begin(), objPath.end(), '?', ' ');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			std::replace(lightMapPath.begin(), lightMapPath.end(), '?', ' ');
			std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
			std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

			// Save file paths
			objPaths.push_back(objPath);
			if (!diffuseMapPath.empty())
			{
				texturePaths.push_back(diffuseMapPath);
			}
			if (!lightMapPath.empty())
			{
				texturePaths.push_back(lightMapPath);
			}
			if (!reflectionMapPath.empty())
			{
				texturePaths.push_back(reflectionMapPath);
			}
			if (!normalMapPath.empty())
			{
				texturePaths.push_back(normalMapPath);
			}
		}

		// Close file
		file.close();

		// Cache OBJ files
		vector<string> objTexturePaths;
		_fe3d.misc_cacheOBJsMultiThreaded(objPaths, objTexturePaths);

		// Add to texture paths
		texturePaths.insert(texturePaths.end(), objTexturePaths.begin(), objTexturePaths.end());

		// Return
		return texturePaths;
	}
}

void ModelEditor::loadGameEntitiesFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded --> ModelEditor::loadGameEntitiesFromFile()");
	}

	// Clear names list from previous loads
	_modelIDs.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\model.fe3d";

	// Check if model file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Temporary values
		std::ifstream file(filePath);
		string line;
		vector<string> objPaths;
		vector<string> texturePaths;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string modelID, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, lodEntityID;
			float uvRepeat, specularFactor, specularIntensity, lightness;
			int reflectionType;
			bool isFaceCulled, isShadowed, isTransparent, isSpecular, isInstanced;
			Vec3 modelSize, color;
			vector<string> aabbNames;
			vector<Vec3> aabbPositions;
			vector<Vec3> aabbSizes;

			// For file extraction
			std::istringstream iss(line);

			// Extract general data from file
			iss >>
				modelID >>
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
				reflectionType >>
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
				Vec3 position, size;
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
			_addModel(modelID, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, modelSize, isFaceCulled, isShadowed,
				isTransparent, isSpecular, reflectionType, specularFactor, specularIntensity, lightness,
				Vec3(color.r, color.g, color.b), uvRepeat, lodEntityID, isInstanced, aabbNames, aabbPositions, aabbSizes);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Model data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void ModelEditor::saveGameEntitiesToFile()
{
	if (_isEditorLoaded)
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
		for (auto& modelID : _modelIDs)
		{
			// Check if a 3D entity for this model is existing
			if (_fe3d.gameEntity_isExisting(modelID))
			{
				// General data
				auto objPath = _fe3d.gameEntity_getObjPath(modelID);
				auto diffuseMapPath = _fe3d.gameEntity_getDiffuseMapPath(modelID);
				auto lightMapPath = _fe3d.gameEntity_getLightMapPath(modelID);
				auto reflectionMapPath = _fe3d.gameEntity_getReflectionMapPath(modelID);
				auto normalMapPath = _fe3d.gameEntity_getNormalMapPath(modelID);
				auto modelSize = _fe3d.gameEntity_getSize(modelID);
				auto isFaceCulled = _fe3d.gameEntity_isFaceCulled(modelID);
				auto isShadowed = _fe3d.gameEntity_isShadowed(modelID);
				auto isTransparent = _fe3d.gameEntity_isTransparent(modelID);
				auto isSpecular = _fe3d.gameEntity_isSpecularLighted(modelID);
				auto specularFactor = _fe3d.gameEntity_getSpecularFactor(modelID);
				auto specularStrength = _fe3d.gameEntity_getSpecularIntensity(modelID);
				auto lightness = _fe3d.gameEntity_getLightness(modelID);
				auto color = _fe3d.gameEntity_getColor(modelID);
				auto uvRepeat = _fe3d.gameEntity_getUvRepeat(modelID);
				auto lodEntityID = _fe3d.gameEntity_getLevelOfDetailEntityID(modelID);
				auto isInstanced = _fe3d.gameEntity_isInstanced(modelID);

				// Reflection type
				int reflectionType;
				if (_fe3d.gameEntity_isSceneReflective(modelID))
				{
					reflectionType = 2;
				}
				else if (_fe3d.gameEntity_isSkyReflective(modelID))
				{
					reflectionType = 1;
				}
				else
				{
					reflectionType = 0;
				}

				// AABB data
				vector<string> aabbNames;
				vector<Vec3> aabbPositions;
				vector<Vec3> aabbSizes;
				for (auto& aabbID : _fe3d.aabbEntity_getBoundIDs(modelID, true, false))
				{
					aabbNames.push_back(aabbID.substr(string(modelID + "_").size()));
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
					modelID << " " <<
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
					reflectionType << " " <<
					isSpecular << " " <<
					specularFactor << " " <<
					specularStrength << " " <<
					lightness << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << " " <<
					uvRepeat << " " <<
					lodEntityID << " " <<
					isInstanced;

				// Add space
				if (!aabbNames.empty())
				{
					file << " ";
				}

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
				
				// Add newline
				file << std::endl;
			}
			else
			{
				file << modelID << " ? ? ? ? ? 0.0 0.0 0.0 0 0 0 0 0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 ? 0\n";
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Model data from project \"" + _currentProjectName + "\" saved!");
	}
}