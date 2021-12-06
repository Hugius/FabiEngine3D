#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> ModelEditor::getAllMeshPathsFromFile() const
{
	// Error checking
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::getAllMeshPathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\model.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `model.fe3d` missing!");
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

			// Convert empty string
			meshPath = (meshPath == "?") ? "" : meshPath;

			// Convert spaces
			replace(meshPath.begin(), meshPath.end(), '?', ' ');

			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				meshPath = string("projects\\" + _currentProjectID + "\\" + meshPath);
			}

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
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::getAllTexturePathsFromFile");
	}

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\model.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `model.fe3d` missing!");
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
			string modelID, meshPath, levelOfDetailEntityID;
			float levelOfDetailDistance;
			unsigned int rotationOrder;
			bool isInstanced, isFaceCulled;
			fvec3 size;

			// Read data from file
			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				levelOfDetailEntityID >>
				levelOfDetailDistance >>
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
				fvec3 color;
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

				// Convert empty string
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
				specularMapPath = (specularMapPath == "?") ? "" : specularMapPath;
				reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
				normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;

				// Convert spaces
				replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
				replace(specularMapPath.begin(), specularMapPath.end(), '?', ' ');
				replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
				replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

				// Diffuse map
				if(!diffuseMapPath.empty())
				{
					// Convert to long path
					if(!Config::getInst().isApplicationExported())
					{
						diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
					}

					// Save path
					texturePaths.push_back(diffuseMapPath);
				}

				// Emission map
				if(!emissionMapPath.empty())
				{
					// Convert to long path
					if(!Config::getInst().isApplicationExported())
					{
						emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
					}

					// Save path
					texturePaths.push_back(emissionMapPath);
				}

				// Specular map
				if(!specularMapPath.empty())
				{
					// Convert to long path
					if(!Config::getInst().isApplicationExported())
					{
						specularMapPath = string("projects\\" + _currentProjectID + "\\" + specularMapPath);
					}
					
					// Save path
					texturePaths.push_back(specularMapPath);
				}

				// Reflection map
				if(!reflectionMapPath.empty())
				{
					// Convert to long path
					if(!Config::getInst().isApplicationExported())
					{
						reflectionMapPath = string("projects\\" + _currentProjectID + "\\" + reflectionMapPath);
					}

					// Save path
					texturePaths.push_back(reflectionMapPath);
				}

				// Normal map
				if(!normalMapPath.empty())
				{
					// Convert to long path
					if(!Config::getInst().isApplicationExported())
					{
						normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
					}

					// Save path
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
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("ModelEditor::loadModelEntitiesFromFile::1");
	}

	// Clear IDs from previous loads
	_loadedModelIDs.clear();

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\model.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `model.fe3d` missing!");
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
			string modelID, meshPath, levelOfDetailEntityID;
			float levelOfDetailDistance;
			unsigned int rotationOrder;
			bool isInstanced, isFaceCulled;
			fvec3 size;

			// Read data from file
			iss >>
				modelID >>
				meshPath >>
				size.x >>
				size.y >>
				size.z >>
				levelOfDetailEntityID >>
				levelOfDetailDistance >>
				isInstanced >>
				isFaceCulled >>
				rotationOrder;

			// Convert empty string
			meshPath = (meshPath == "?") ? "" : meshPath;
			levelOfDetailEntityID = (levelOfDetailEntityID == "?") ? "" : levelOfDetailEntityID;

			// Convert spaces
			replace(meshPath.begin(), meshPath.end(), '?', ' ');
			replace(levelOfDetailEntityID.begin(), levelOfDetailEntityID.end(), '?', ' ');

			// Convert to long path
			if(!Config::getInst().isApplicationExported())
			{
				meshPath = string("projects\\" + _currentProjectID + "\\" + meshPath);
			}

			// Create model
			_fe3d.model_create(modelID, meshPath);

			// Check if model creation went well
			if(_fe3d.model_isExisting(modelID))
			{
				// Add model ID
				_loadedModelIDs.push_back(modelID);

				// Set instancing
				if(isInstanced)
				{
					_fe3d.model_enableInstancing(modelID, {fvec3(0.0f)});
				}

				// Set properties
				_fe3d.model_setVisible(modelID, false);
				_fe3d.model_setBaseSize(modelID, size);
				_fe3d.model_setLevelOfDetailEntityID(modelID, levelOfDetailEntityID);
				_fe3d.model_setLevelOfDetailDistance(modelID, levelOfDetailDistance);
				_fe3d.model_setFaceCulled(modelID, isFaceCulled);
				_fe3d.model_setRotationOrder(modelID, DirectionOrder(rotationOrder));

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
					fvec3 color;

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

					// Convert empty string
					partID = (partID == "?") ? "" : partID;
					diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
					emissionMapPath = (emissionMapPath == "?") ? "" : emissionMapPath;
					specularMapPath = (specularMapPath == "?") ? "" : specularMapPath;
					reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
					normalMapPath = (normalMapPath == "?") ? "" : normalMapPath;

					// Convert spaces
					replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
					replace(emissionMapPath.begin(), emissionMapPath.end(), '?', ' ');
					replace(specularMapPath.begin(), specularMapPath.end(), '?', ' ');
					replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');
					replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');

					// Diffuse map
					if(!diffuseMapPath.empty())
					{
						// Convert to long path
						if(!Config::getInst().isApplicationExported())
						{
							diffuseMapPath = string("projects\\" + _currentProjectID + "\\" + diffuseMapPath);
						}

						// Set path
						_fe3d.model_setDiffuseMap(modelID, partID, diffuseMapPath);
					}

					// Specular map
					if(!specularMapPath.empty())
					{
						// Convert to long path
						if(!Config::getInst().isApplicationExported())
						{
							specularMapPath = string("projects\\" + _currentProjectID + "\\" + specularMapPath);
						}

						// Set path
						_fe3d.model_setSpecularMap(modelID, partID, specularMapPath);
					}

					// Emission map
					if(!emissionMapPath.empty())
					{
						// Convert to long path
						if(!Config::getInst().isApplicationExported())
						{
							emissionMapPath = string("projects\\" + _currentProjectID + "\\" + emissionMapPath);
						}

						// Set path
						_fe3d.model_setEmissionMap(modelID, partID, emissionMapPath);
					}

					// Reflection map
					if(!reflectionMapPath.empty())
					{
						// Convert to long path
						if(!Config::getInst().isApplicationExported())
						{
							reflectionMapPath = string("projects\\" + _currentProjectID + "\\" + reflectionMapPath);
						}

						// Set path
						_fe3d.model_setReflectionMap(modelID, partID, reflectionMapPath);
					}

					// Normal map
					if(!normalMapPath.empty())
					{
						// Convert to long path
						if(!Config::getInst().isApplicationExported())
						{
							normalMapPath = string("projects\\" + _currentProjectID + "\\" + normalMapPath);
						}

						// Set path
						_fe3d.model_setNormalMap(modelID, partID, normalMapPath);
					}

					// Set properties
					_fe3d.model_setColor(modelID, partID, color);
					_fe3d.model_setSpecular(modelID, partID, isSpecular);
					_fe3d.model_setSpecularShininess(modelID, partID, specularShininess);
					_fe3d.model_setSpecularIntensity(modelID, partID, specularIntensity);
					_fe3d.model_setReflectivity(modelID, partID, reflectivity);
					_fe3d.model_setLightness(modelID, partID, lightness);
					_fe3d.model_setTextureRepeat(modelID, partID, textureRepeat);
					_fe3d.model_setReflective(modelID, partID, isReflective);
					_fe3d.model_setReflectionType(modelID, partID, ReflectionType(reflectionType));
				}
			}
		}
		else if(lineType == "AABB")
		{
			// Data placeholders
			string aabbID, modelID;
			fvec3 position, size;

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
			_fe3d.aabb_create(aabbID);

			// Set properties
			_fe3d.aabb_setParentEntityID(aabbID, modelID);
			_fe3d.aabb_setParentEntityType(aabbID, AabbParentEntityType::MODEL);
			_fe3d.aabb_setLocalPosition(aabbID, position);
			_fe3d.aabb_setLocalSize(aabbID, size);
		}
		else
		{
			Logger::throwError("ModelEditor::loadModelEntitiesFromFile::2");
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Model data loaded!");

	// Return
	return true;
}