#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

const vector<string> ModelEditor::getAllTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("No current project loaded --> ModelEditor::preLoadModelEntitiesFromFile()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Check if model file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Temporary values
		std::ifstream file(filePath);
		string line;
		vector<string> meshPaths;
		vector<string> texturePaths;

		// Read model data
		while (std::getline(file, line))
		{
			// Temporary values
			string modelID, meshPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath;
			std::istringstream iss(line);

			// Extract data
			iss >> modelID >> meshPath >> diffuseMapPath >> lightMapPath >> reflectionMapPath >> normalMapPath;

			// Perform empty string & space conversions
			meshPath = (meshPath == "?") ? "" : meshPath;
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			lightMapPath = (lightMapPath == "?") ? "" : lightMapPath;
			reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
			normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
			std::replace(meshPath.begin(), meshPath.end(), '?', ' ');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			std::replace(lightMapPath.begin(), lightMapPath.end(), '?', ' ');
			std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
			std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

			// Save file paths
			meshPaths.push_back(meshPath);
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

		// Cache mesh files
		vector<string> meshTexturePaths;
		_fe3d.misc_cacheMeshesMultiThreaded(meshPaths, meshTexturePaths);

		// Add to texture paths
		texturePaths.insert(texturePaths.end(), meshTexturePaths.begin(), meshTexturePaths.end());

		// Return
		return texturePaths;
	}
	else
	{
		Logger::throwError("Project \"" + _currentProjectID + "\" corrupted: \"model.fe3d\" missing!");
	}

	return {};
}

void ModelEditor::loadModelEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("No current project loaded --> ModelEditor::loadModelEntitiesFromFile()");
	}

	// Clear names list from previous loads
	_loadedModelIDs.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Check if model file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Temporary values
		std::ifstream file(filePath);
		string line;
		vector<string> meshPaths;
		vector<string> texturePaths;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string modelID, meshPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, lodEntityID;
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
				meshPath >>
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
			meshPath = (meshPath == "?") ? "" : meshPath;
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			lightMapPath = (lightMapPath == "?") ? "" : lightMapPath;
			reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
			normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
			lodEntityID = (lodEntityID == "?") ? "" : lodEntityID;
			std::replace(meshPath.begin(), meshPath.end(), '?', ' ');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			std::replace(lightMapPath.begin(), lightMapPath.end(), '?', ' ');
			std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
			std::replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
			std::replace(lodEntityID.begin(), lodEntityID.end(), '?', ' ');

			// Add new model
			_addModel(modelID, meshPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, modelSize, isFaceCulled, isShadowed,
				isTransparent, isSpecular, reflectionType, specularFactor, specularIntensity, lightness,
				Vec3(color.r, color.g, color.b), uvRepeat, lodEntityID, isInstanced, aabbNames, aabbPositions, aabbSizes);
		}

		// Close file
		file.close();

		// Logging
		Logger::throwInfo("Model data from project \"" + _currentProjectID + "\" loaded!");
	}
	else
	{
		Logger::throwError("Project \"" + _currentProjectID + "\" corrupted: \"model.fe3d\" missing!");
	}
}