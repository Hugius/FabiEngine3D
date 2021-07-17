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
		Logger::throwError("ModelEditor::getAllTexturePathsFromFile() ---> no current project loaded!");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"model.fe3d\" file missing!");
		return {};
	}

	// Load model file
	std::ifstream file(filePath);

	// Read model data
	vector<string> meshPaths;
	vector<string> texturePaths;
	string line;
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

bool ModelEditor::loadModelEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("ModelEditor::loadModelEntitiesFromFile() ---> no current project loaded!");
	}

	// Clear IDs from previous loads
	_loadedModelIDs.clear();

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"model.fe3d\" file missing!");
		return false;
	}

	// Load model file
	std::ifstream file(filePath);

	// Read model data
	vector<string> meshPaths;
	vector<string> texturePaths;
	string line;
	while (std::getline(file, line))
	{
		// Placeholder variables
		string modelID, meshPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, lodEntityID;
		float uvRepeat, specularFactor, specularIntensity, lightness;
		unsigned int reflectionType;
		bool isFaceCulled, isTransparent, isSpecular, isInstanced, isBright;
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
			isInstanced >>
			isBright;

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
		_addModel(modelID, meshPath, diffuseMapPath, lightMapPath, reflectionMapPath, normalMapPath, modelSize, isFaceCulled,
			isTransparent, isSpecular, ReflectionType(reflectionType), specularFactor, specularIntensity, lightness,
			Vec3(color.r, color.g, color.b), uvRepeat, lodEntityID, isInstanced, isBright, aabbNames, aabbPositions, aabbSizes);
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Model data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}