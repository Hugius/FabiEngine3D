#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void ModelEditor::_loadMesh()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\meshes\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "OBJ");

	// Check if not cancelled
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());

			// Delete existing entity
			if (_fe3d.modelEntity_isExisting(_currentModelID))
			{
				// Clear mesh cache
				_fe3d.misc_clearMeshCache(newFilePath);

				// Check if multiparted entity
				if (_fe3d.modelEntity_isMultiParted(_currentModelID))
				{
					// Clear texture cache
					for (const auto& partID : _fe3d.modelEntity_getPartIDs(_currentModelID))
					{
						// Diffuse map
						if (_fe3d.modelEntity_hasDiffuseMap(partID))
						{
							_fe3d.misc_clearTextureCache2D(_fe3d.modelEntity_getDiffuseMapPath(partID));
						}

						// Emission map
						if (_fe3d.modelEntity_hasEmissionMap(partID))
						{
							_fe3d.misc_clearTextureCache2D(_fe3d.modelEntity_getEmissionMapPath(partID));
						}

						// Reflection map
						if (_fe3d.modelEntity_hasReflectionMap(partID))
						{
							_fe3d.misc_clearTextureCache2D(_fe3d.modelEntity_getReflectionMapPath(partID));
						}

						// Normal map
						if (_fe3d.modelEntity_hasNormalMap(partID))
						{
							_fe3d.misc_clearTextureCache2D(_fe3d.modelEntity_getNormalMapPath(partID));
						}
					}
				}

				// Reload model
				//_fe3d.modelEntity_loadMesh(_currentModelID, newFilePath);
			}
			else
			{
				// Create new entity
				//_fe3d.modelEntity_create(_currentModelID, newFilePath, Vec3(0.0f), Vec3(0.0f), Vec3(1.0f));
			}
		}
		else
		{
			Logger::throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadDiffuseMap()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.modelEntity_setDiffuseMap(_currentModelID, newFilePath);
		}
		else
		{
			Logger::throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadEmissionMap()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\emission_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.modelEntity_setEmissionMap(_currentModelID, newFilePath);
		}
		else
		{
			Logger::throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadReflectionMap()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\reflection_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.modelEntity_setReflectionMap(_currentModelID, newFilePath);
		}
		else
		{
			Logger::throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadNormalMap()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\normal_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.modelEntity_setNormalMap(_currentModelID, newFilePath);
		}
		else
		{
			Logger::throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool ModelEditor::isLoaded()
{
	return _isEditorLoaded;
}

const vector<string>& ModelEditor::getLoadedModelIDs()
{
	std::sort(_loadedModelIDs.begin(), _loadedModelIDs.end());
	return _loadedModelIDs;
}

bool ModelEditor::_createModel(const string& modelName, string meshPath, string diffuseMapPath, string emissionMapPath, string reflectionMapPath, string normalMapPath, Vec3 size, bool isFaceCulled, bool isTransparent, bool isSpecular, ReflectionType reflectionType, float specularFactor, float specularIntensity, float lightness, Vec3 color, float uvRepeat, string lodEntityID, bool isInstanced, bool isBright, vector<string> aabbNames, vector<Vec3> aabbPositions, vector<Vec3> aabbSizes)
{
	// If model name not existing yet
	if (find(_loadedModelIDs.begin(), _loadedModelIDs.end(), modelName) == _loadedModelIDs.end())
	{
		// Add model ID
		_loadedModelIDs.push_back(modelName);

		// Check if model has mesh
		if (meshPath != "")
		{
			// Create model
			_fe3d.modelEntity_create(modelName, meshPath);
			_fe3d.modelEntity_setPosition(modelName, Vec3(0.0f, MODEL_Y_OFFSET, 0.0f));
			_fe3d.modelEntity_setSize(modelName, size);
			_fe3d.modelEntity_setVisible(modelName, false);

			// Bind AABBs
			for (size_t i = 0; i < aabbNames.size(); i++)
			{
				const string newAabbID = modelName + "@" + aabbNames[i];
				_fe3d.aabbEntity_create(newAabbID);
				_fe3d.aabbEntity_bindToModelEntity(newAabbID, modelName);
				_fe3d.aabbEntity_setPosition(newAabbID, aabbPositions[i]);
				_fe3d.aabbEntity_setSize(newAabbID, aabbSizes[i]);
			}

			// Diffuse map
			if (diffuseMapPath != "")
			{
				_fe3d.modelEntity_setDiffuseMap(modelName, diffuseMapPath);
			}

			// Emission map
			if (emissionMapPath != "")
			{
				_fe3d.modelEntity_setEmissionMap(modelName, emissionMapPath);
			}

			// Reflection map
			if (reflectionMapPath != "")
			{
				_fe3d.modelEntity_setReflectionMap(modelName, reflectionMapPath);
			}

			// Normal map
			if (normalMapPath != "")
			{
				_fe3d.modelEntity_setNormalMap(modelName, normalMapPath);
			}

			// Instancing
			if (isInstanced)
			{
				_fe3d.modelEntity_enableInstancing(modelName, { Vec3(0.0f) });
			}

			// Set properties
			_fe3d.modelEntity_setFaceCulled(modelName, isFaceCulled);
			_fe3d.modelEntity_setTransparent(modelName, isTransparent);
			_fe3d.modelEntity_setSpecularLighted(modelName, isSpecular);
			_fe3d.modelEntity_setBright(modelName, isBright);
			_fe3d.modelEntity_setSpecularFactor(modelName, specularFactor);
			_fe3d.modelEntity_setSpecularIntensity(modelName, specularIntensity);
			_fe3d.modelEntity_setLightness(modelName, lightness);
			_fe3d.modelEntity_setColor(modelName, color); 
			_fe3d.modelEntity_setUvRepeat(modelName, uvRepeat);
			_fe3d.modelEntity_setLevelOfDetailEntity(modelName, lodEntityID);
			_fe3d.modelEntity_setReflectionType(modelName, reflectionType);
		}

		return true;
	}
	else
	{
		Logger::throwWarning("Model name \"" + modelName.substr(1) + "\" already exists!");

		return false;
	}
}