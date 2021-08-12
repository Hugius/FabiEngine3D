#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> ModelEditor::getAllTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::getAllTexturePathsFromFile");
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
	ifstream file(filePath);

	// Read model data
	vector<string> meshPaths;
	vector<string> texturePaths;
	string line;
	while (getline(file, line))
	{
		// Temporary values
		string modelID, meshPath, diffuseMapPath, emissionMapPath, reflectionMapPath, normalMapPath;
		istringstream iss(line);

		// Extract data
		iss >> modelID >> meshPath >> diffuseMapPath >> emissionMapPath >> reflectionMapPath >> normalMapPath;

		// Perform empty string & space conversions
		meshPath = (meshPath == "?") ? "" : meshPath;
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
		reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
		normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
		replace(meshPath.begin(), meshPath.end(), '?', ' ');
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
		replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

		// Save file paths
		meshPaths.push_back(meshPath);
		if (!diffuseMapPath.empty())
		{
			texturePaths.push_back(diffuseMapPath);
		}
		if (!emissionMapPath.empty())
		{
			texturePaths.push_back(emissionMapPath);
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
	if (_currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::loadModelEntitiesFromFile");
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
	ifstream file(filePath);

	// Read model data
	vector<string> meshPaths;
	vector<string> texturePaths;
	string line;
	while (getline(file, line))
	{
		// Placeholder variables
		string modelID, meshPath, diffuseMapPath, emissionMapPath, reflectionMapPath, normalMapPath, lodEntityID;
		float uvRepeat, specularFactor, specularIntensity, lightness;
		unsigned int reflectionType;
		bool isFaceCulled, isTransparent, isSpecular, isInstanced, isBright;
		Vec3 size, color;
		vector<string> aabbIDs;
		vector<Vec3> aabbPositions;
		vector<Vec3> aabbSizes;

		// For file extraction
		istringstream iss(line);

		// Extract general data from file
		iss >>
			modelID >>
			meshPath >>
			diffuseMapPath >>
			emissionMapPath >>
			reflectionMapPath >>
			normalMapPath >>
			size.x >>
			size.y >>
			size.z >>
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
			string aabbID;
			Vec3 position, size;
			iss >> aabbID;
			if (aabbID.empty())
			{
				break;
			}
			else
			{
				iss >> position.x >> position.y >> position.z >> size.x >> size.y >> size.z;
				aabbIDs.push_back(aabbID);
				aabbPositions.push_back(position);
				aabbSizes.push_back(size);
			}
		}

		// Perform empty string & space conversions
		meshPath = (meshPath == "?") ? "" : meshPath;
		diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
		emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
		reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
		normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
		lodEntityID = (lodEntityID == "?") ? "" : lodEntityID;
		replace(meshPath.begin(), meshPath.end(), '?', ' ');
		replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
		replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
		replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(lodEntityID.begin(), lodEntityID.end(), '?', ' ');

		// Create model
		_fe3d.modelEntity_create(modelID, meshPath);

		// Check if model creation went well
		if (_fe3d.modelEntity_isExisting(modelID))
		{
			// Add model ID
			_loadedModelIDs.push_back(modelID);

			// Bind AABBs
			for (size_t i = 0; i < aabbIDs.size(); i++)
			{
				const string newAabbID = (modelID + "@" + aabbIDs[i]);
				_fe3d.aabbEntity_create(newAabbID);
				_fe3d.aabbEntity_bindToModelEntity(newAabbID, modelID);
				_fe3d.aabbEntity_setPosition(newAabbID, aabbPositions[i]);
				_fe3d.aabbEntity_setSize(newAabbID, aabbSizes[i]);
			}

			// Diffuse map
			if (diffuseMapPath != "")
			{
				_fe3d.modelEntity_setDiffuseMap(modelID, diffuseMapPath);
			}

			// Emission map
			if (emissionMapPath != "")
			{
				_fe3d.modelEntity_setEmissionMap(modelID, emissionMapPath);
			}

			// Reflection map
			if (reflectionMapPath != "")
			{
				_fe3d.modelEntity_setReflectionMap(modelID, reflectionMapPath);
			}

			// Normal map
			if (normalMapPath != "")
			{
				_fe3d.modelEntity_setNormalMap(modelID, normalMapPath);
			}

			// Instancing
			if (isInstanced)
			{
				_fe3d.modelEntity_enableInstancing(modelID, { Vec3(0.0f) });
			}

			// Set properties
			_fe3d.modelEntity_setVisible(modelID, false);
			_fe3d.modelEntity_setSize(modelID, size);
			_fe3d.modelEntity_setFaceCulled(modelID, isFaceCulled);
			_fe3d.modelEntity_setTransparent(modelID, isTransparent);
			_fe3d.modelEntity_setSpecularLighted(modelID, isSpecular);
			_fe3d.modelEntity_setBright(modelID, isBright);
			_fe3d.modelEntity_setSpecularFactor(modelID, specularFactor);
			_fe3d.modelEntity_setSpecularIntensity(modelID, specularIntensity);
			_fe3d.modelEntity_setLightness(modelID, lightness);
			_fe3d.modelEntity_setColor(modelID, color);
			_fe3d.modelEntity_setUvRepeat(modelID, uvRepeat);
			_fe3d.modelEntity_setLevelOfDetailEntity(modelID, lodEntityID);
			_fe3d.modelEntity_setReflectionType(modelID, ReflectionType(reflectionType));
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Model data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}