#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> ModelEditor::getAllMeshPathsFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::getAllMeshPathsFromFile");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `model.fe3d` missing!");
		return {};
	}

	// Load model file
	ifstream file(filePath);

	// Read model data
	vector<string> meshPaths;
	string line;
	while (getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Read type from file
		string lineType;
		iss >> lineType;

		// Determine line type
		if (lineType == "MODEL")
		{
			// Data placeholders
			string modelID, meshPath;

			// Read data from file
			iss >> modelID >> meshPath;

			// Perform empty string & space conversions
			meshPath = (meshPath == "?") ? "" : meshPath;
			replace(meshPath.begin(), meshPath.end(), '?', ' ');

			// Save mesh path
			meshPaths.push_back(meshPath);
		}
	}

	// Close file
	file.close();

	// Return
	return meshPaths;
}

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
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `model.fe3d` missing!");
		return {};
	}

	// Load model file
	ifstream file(filePath);

	// Read model data
	vector<string> texturePaths;
	string line;
	while (getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Read type from file
		string lineType;
		iss >> lineType;

		// Determine line type
		if (lineType == "MODEL")
		{
			// Data placeholders
			string modelID, meshPath, lodEntityID;
			float uvRepeat, specularShininess, specularIntensity, reflectivity, lightness;
			unsigned int reflectionType;
			bool isFaceCulled, isSpecular, isInstanced;
			Vec3 size, color;

			// Read data from file
			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				isFaceCulled >>
				reflectionType >>
				isSpecular >>
				specularShininess >>
				specularIntensity >>
				reflectivity >>
				lightness >>
				color.r >>
				color.g >>
				color.b >>
				uvRepeat >>
				lodEntityID >>
				isInstanced;

			// Read part data
			while (true)
			{
				// Check if file has any part data left
				string partID;
				iss >> partID;
				if (partID.empty())
				{
					break;
				}

				// Data placeholders
				string diffuseMapPath, emissionMapPath, reflectionMapPath, normalMapPath;

				// Read data from file
				iss >>
					diffuseMapPath >>
					emissionMapPath >>
					reflectionMapPath >>
					normalMapPath;

				// Perform empty string & space conversions
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
				reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
				normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
				replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
				replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
				replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

				// Diffuse map
				if (!diffuseMapPath.empty())
				{
					texturePaths.push_back(diffuseMapPath);
				}

				// Emission map
				if (!emissionMapPath.empty())
				{
					texturePaths.push_back(emissionMapPath);
				}

				// Reflection map
				if (!reflectionMapPath.empty())
				{
					texturePaths.push_back(reflectionMapPath);
				}

				// Normal map
				if (!normalMapPath.empty())
				{
					texturePaths.push_back(normalMapPath);
				}
			}
		}
	}

	// Close file
	file.close();

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
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `model.fe3d` missing!");
		return false;
	}

	// Load model file
	ifstream file(filePath);

	// Read model data
	string line;
	while (getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Read type from file
		string lineType;
		iss >> lineType;

		// Determine line type
		if (lineType == "MODEL")
		{
			// Data placeholders
			string modelID, meshPath, lodEntityID;
			float uvRepeat, specularShininess, specularIntensity, reflectivity, lightness;
			unsigned int reflectionType;
			bool isFaceCulled, isSpecular, isInstanced;
			Vec3 size, color;

			// Read data from file
			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				isFaceCulled >>
				reflectionType >>
				isSpecular >>
				specularShininess >>
				specularIntensity >>
				reflectivity >>
				lightness >>
				color.r >>
				color.g >>
				color.b >>
				uvRepeat >>
				lodEntityID >>
				isInstanced;

			// Perform empty string & space conversions
			meshPath = (meshPath == "?") ? "" : meshPath;
			lodEntityID = (lodEntityID == "?") ? "" : lodEntityID;
			replace(meshPath.begin(), meshPath.end(), '?', ' ');
			replace(lodEntityID.begin(), lodEntityID.end(), '?', ' ');

			// Create model
			_fe3d.modelEntity_create(modelID, meshPath);

			// Check if model creation went well
			if (_fe3d.modelEntity_isExisting(modelID))
			{
				// Add model ID
				_loadedModelIDs.push_back(modelID);

				// Instancing
				if (isInstanced)
				{
					_fe3d.modelEntity_enableInstancing(modelID, { Vec3(0.0f) });
				}

				// Set properties
				_fe3d.modelEntity_setVisible(modelID, false);
				_fe3d.modelEntity_setSize(modelID, "", size);
				_fe3d.modelEntity_setColor(modelID, "", color);
				_fe3d.modelEntity_setFaceCulled(modelID, isFaceCulled);
				_fe3d.modelEntity_setSpecularLighted(modelID, isSpecular);
				_fe3d.modelEntity_setSpecularShininess(modelID, specularShininess);
				_fe3d.modelEntity_setSpecularIntensity(modelID, specularIntensity);
				_fe3d.modelEntity_setReflectivity(modelID, reflectivity);
				_fe3d.modelEntity_setLightness(modelID, lightness);
				_fe3d.modelEntity_setUvRepeat(modelID, uvRepeat);
				_fe3d.modelEntity_setLevelOfDetailEntity(modelID, lodEntityID);
				_fe3d.modelEntity_setReflectionType(modelID, ReflectionType(reflectionType));

				// Read part data
				while (true)
				{
					// Check if file has any part data left
					string partID;
					iss >> partID;
					if (partID.empty())
					{
						break;
					}

					// Data placeholders
					string diffuseMapPath, emissionMapPath, specularMapPath, reflectionMapPath, normalMapPath;

					// Read data from file
					iss >>
						diffuseMapPath >>
						emissionMapPath >>
						specularMapPath >>
						reflectionMapPath >>
						normalMapPath;

					// Perform empty string & space conversions
					partID = (partID == "?") ? "" : partID;
					diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
					emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
					specularMapPath = (specularMapPath == "?") ? "" : specularMapPath;
					reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
					normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;
					replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
					replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
					replace(specularMapPath.begin(), specularMapPath.end(), '?', ' ');
					replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
					replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

					// Diffuse map
					if (!diffuseMapPath.empty())
					{
						_fe3d.modelEntity_setDiffuseMap(modelID, partID, diffuseMapPath);
					}

					// Specular map
					if (!specularMapPath.empty())
					{
						_fe3d.modelEntity_setSpecularMap(modelID, partID, specularMapPath);
					}

					// Emission map
					if (!emissionMapPath.empty())
					{
						_fe3d.modelEntity_setEmissionMap(modelID, partID, emissionMapPath);
					}

					// Reflection map
					if (!reflectionMapPath.empty())
					{
						_fe3d.modelEntity_setReflectionMap(modelID, partID, reflectionMapPath);
					}

					// Normal map
					if (!normalMapPath.empty())
					{
						_fe3d.modelEntity_setNormalMap(modelID, partID, normalMapPath);
					}
				}
			}
		}
		else if (lineType == "AABB")
		{
			// Data placeholders
			string aabbID, modelID;
			Vec3 position, size;

			// Read data from file
			iss >>
				aabbID >>
				modelID >>
				position.x >>
				position.y >>
				position.z >>
				size.x >>
				size.y >>
				size.z;

			// Create AABB
			_fe3d.aabbEntity_create(aabbID);

			// Set properties
			_fe3d.aabbEntity_setParent(aabbID, modelID, AabbParentType::MODEL_ENTITY);
			_fe3d.aabbEntity_setLocalPosition(aabbID, position);
			_fe3d.aabbEntity_setLocalSize(aabbID, size);
		}
		else
		{
			Logger::throwError("ModelEditor::loadModelEntitiesFromFile");
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Model data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}