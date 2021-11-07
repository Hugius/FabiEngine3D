#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> ModelEditor::getAllMeshPathsFromFile() const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::getAllMeshPathsFromFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `model.fe3d` missing!");
		return {};
	}

	// Load model file
	ifstream file(filePath);

	// Read model data
	vector<string> meshPaths;
	string line;
	while(getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Read type from file
		string lineType;
		iss >> lineType;

		// Determine line type
		if(lineType == "MODEL")
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

const vector<string> ModelEditor::getAllTexturePathsFromFile() const
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::getAllTexturePathsFromFile");
	}

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `model.fe3d` missing!");
		return {};
	}

	// Load model file
	ifstream file(filePath);

	// Read model data
	vector<string> texturePaths;
	string line;
	while(getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Read type from file
		string lineType;
		iss >> lineType;

		// Determine line type
		if(lineType == "MODEL")
		{
			// Data placeholders
			string modelID, meshPath, lodEntityID;
			unsigned int rotationOrder;
			bool isInstanced, isFaceCulled;
			Vec3 size;

			// Read data from file
			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				lodEntityID >>
				isInstanced >>
				isFaceCulled >>
				rotationOrder;

			// Read part data
			while(true)
			{
				// Check if file has any part data left
				string partID;
				iss >> partID;
				if(partID.empty())
				{
					break;
				}

				// Data placeholders
				string diffuseMapPath, emissionMapPath, specularMapPath, reflectionMapPath, normalMapPath;
				Vec3 color;
				float textureRepeat, specularShininess, specularIntensity, reflectivity, lightness;
				unsigned int reflectionType;
				bool isSpecular, isReflective;

				// Read data from file
				iss >>
					diffuseMapPath >>
					emissionMapPath >>
					specularMapPath >>
					reflectionMapPath >>
					normalMapPath >>
					reflectionType >>
					isSpecular >>
					isReflective >>
					specularShininess >>
					specularIntensity >>
					reflectivity >>
					lightness >>
					color.r >>
					color.g >>
					color.b >>
					textureRepeat;

				// Perform empty string & space conversions
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
				if(!diffuseMapPath.empty())
				{
					texturePaths.push_back(diffuseMapPath);
				}

				// Emission map
				if(!emissionMapPath.empty())
				{
					texturePaths.push_back(emissionMapPath);
				}

				// Specular map
				if(!specularMapPath.empty())
				{
					texturePaths.push_back(specularMapPath);
				}

				// Reflection map
				if(!reflectionMapPath.empty())
				{
					texturePaths.push_back(reflectionMapPath);
				}

				// Normal map
				if(!normalMapPath.empty())
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

const bool ModelEditor::loadModelEntitiesFromFile()
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::loadModelEntitiesFromFile::1");
	}

	// Clear IDs from previous loads
	_loadedModelIDs.clear();

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\model.fe3d";

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `model.fe3d` missing!");
		return false;
	}

	// Load model file
	ifstream file(filePath);

	// Read model data
	string line;
	while(getline(file, line))
	{
		// For file extraction
		istringstream iss(line);

		// Read type from file
		string lineType;
		iss >> lineType;

		// Determine line type
		if(lineType == "MODEL")
		{
			// Data placeholders
			string modelID, meshPath, lodEntityID;
			unsigned int rotationOrder;
			bool isInstanced, isFaceCulled;
			Vec3 size;

			// Read data from file
			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				lodEntityID >>
				isInstanced >>
				isFaceCulled >>
				rotationOrder;

			// Perform empty string & space conversions
			meshPath = (meshPath == "?") ? "" : meshPath;
			lodEntityID = (lodEntityID == "?") ? "" : lodEntityID;
			replace(meshPath.begin(), meshPath.end(), '?', ' ');
			replace(lodEntityID.begin(), lodEntityID.end(), '?', ' ');

			// Create model
			_fe3d.modelEntity_create(modelID, meshPath);

			// Check if model creation went well
			if(_fe3d.modelEntity_isExisting(modelID))
			{
				// Add model ID
				_loadedModelIDs.push_back(modelID);

				// Set instancing
				if(isInstanced)
				{
					_fe3d.modelEntity_enableInstancing(modelID, { Vec3(0.0f) });
				}

				// Set properties
				_fe3d.modelEntity_setVisible(modelID, false);
				_fe3d.modelEntity_setBaseSize(modelID, size);
				_fe3d.modelEntity_setLevelOfDetailEntity(modelID, lodEntityID);
				_fe3d.modelEntity_setFaceCulled(modelID, isFaceCulled);
				_fe3d.modelEntity_setRotationOrder(modelID, DirectionOrder(rotationOrder));

				// Read part data
				while(true)
				{
					// Check if file has any part data left
					string partID;
					iss >> partID;
					if(partID.empty())
					{
						break;
					}

					// Data placeholders
					string diffuseMapPath, emissionMapPath, specularMapPath, reflectionMapPath, normalMapPath;
					float textureRepeat, specularShininess, specularIntensity, reflectivity, lightness;
					unsigned int reflectionType;
					bool isSpecular, isReflective;
					Vec3 color;

					// Read data from file
					iss >>
						diffuseMapPath >>
						emissionMapPath >>
						specularMapPath >>
						reflectionMapPath >>
						normalMapPath >>
						reflectionType >>
						isSpecular >>
						isReflective >>
						specularShininess >>
						specularIntensity >>
						reflectivity >>
						lightness >>
						color.r >>
						color.g >>
						color.b >>
						textureRepeat;

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

					// Set diffuse map
					if(!diffuseMapPath.empty())
					{
						_fe3d.modelEntity_setDiffuseMap(modelID, partID, diffuseMapPath);
					}

					// Set specular map
					if(!specularMapPath.empty())
					{
						_fe3d.modelEntity_setSpecularMap(modelID, partID, specularMapPath);
					}

					// Set emission map
					if(!emissionMapPath.empty())
					{
						_fe3d.modelEntity_setEmissionMap(modelID, partID, emissionMapPath);
					}

					// Set reflection map
					if(!reflectionMapPath.empty())
					{
						_fe3d.modelEntity_setReflectionMap(modelID, partID, reflectionMapPath);
					}

					// Set normal map
					if(!normalMapPath.empty())
					{
						_fe3d.modelEntity_setNormalMap(modelID, partID, normalMapPath);
					}

					// Set properties
					_fe3d.modelEntity_setColor(modelID, partID, color);
					_fe3d.modelEntity_setSpecular(modelID, partID, isSpecular);
					_fe3d.modelEntity_setSpecularShininess(modelID, partID, specularShininess);
					_fe3d.modelEntity_setSpecularIntensity(modelID, partID, specularIntensity);
					_fe3d.modelEntity_setReflectivity(modelID, partID, reflectivity);
					_fe3d.modelEntity_setLightness(modelID, partID, lightness);
					_fe3d.modelEntity_setTextureRepeat(modelID, partID, textureRepeat);
					_fe3d.modelEntity_setReflective(modelID, partID, isReflective);
					_fe3d.modelEntity_setReflectionType(modelID, partID, ReflectionType(reflectionType));
				}
			}
		}
		else if(lineType == "AABB")
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
			Logger::throwError("ModelEditor::loadModelEntitiesFromFile::2");
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Model data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}