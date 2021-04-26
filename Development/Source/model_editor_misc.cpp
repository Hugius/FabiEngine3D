#include "model_editor.hpp"

#include <filesystem>

void ModelEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		// Lock toggling if GUI focused or cursor not in 3D viewport
		_fe3d.input_setKeyTogglingLocked(_gui.getGlobalScreen()->isFocused() || !_fe3d.misc_isCursorInsideViewport());

		// Update reference model visibility
		if (_fe3d.input_getKeyToggled(InputType::KEY_R))
		{
			_fe3d.modelEntity_hide("@@cube");
		}
		else
		{
			_fe3d.modelEntity_show("@@cube");
		}

		// Debug rendering
		if (_fe3d.input_getKeyToggled(InputType::KEY_H))
		{
			_fe3d.misc_enableDebugRendering();
		}
		else
		{
			_fe3d.misc_disableDebugRendering();
		}

		// Wireframed model rendering
		string modelID = _currentModelID.empty() ? _hoveredModelID : _currentModelID;
		if (!modelID.empty() && _fe3d.modelEntity_isExisting(modelID))
		{
			if (_fe3d.input_getKeyToggled(InputType::KEY_F))
			{
				_fe3d.modelEntity_setWireframed(modelID, true);
			}
			else
			{
				_fe3d.modelEntity_setWireframed(modelID, false);
			}
		}
	}
}

void ModelEditor::_loadMeshFileNames()
{
	// Remove potential previous filenames
	if (!_meshFileNames.empty())
	{
		_meshFileNames.clear();
	}

	// Determine full mesh directory
	string meshDirectoryPath = _fe3d.misc_getRootDirectory() + "game_assets\\meshes\\";
	unsigned int endOfNameIndex = 0;

	// Get all filenames
	for (const auto& entry : std::filesystem::directory_iterator(meshDirectoryPath))
	{
		string meshPath = string(entry.path().u8string());
		meshPath.erase(0, meshDirectoryPath.size());

		// Loop over file path
		for (size_t i = 0; i < meshPath.size(); i++)
		{
			// End of file name
			if (meshPath[i] == '.')
			{
				endOfNameIndex = static_cast<unsigned int>(i);
			}
		}

		_meshFileNames.push_back(meshPath.substr(0, endOfNameIndex));
	}
}

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
					for (auto& path : _fe3d.modelEntity_getDiffuseMapPaths(_currentModelID))
					{
						_fe3d.misc_clearTextureCache2D(path);
					}
					for (auto& path : _fe3d.modelEntity_getLightMapPaths(_currentModelID))
					{
						_fe3d.misc_clearTextureCache2D(path);
					}
					for (auto& path : _fe3d.modelEntity_getReflectionMapPaths(_currentModelID))
					{
						_fe3d.misc_clearTextureCache2D(path);
					}
					for (auto& path : _fe3d.modelEntity_getNormalMapPaths(_currentModelID))
					{
						_fe3d.misc_clearTextureCache2D(path);
					}
				}

				// Reload model
				_fe3d.modelEntity_loadModel(_currentModelID, newFilePath);
			}
			else
			{
				// Create new entity
				_fe3d.modelEntity_add(_currentModelID, newFilePath, Vec3(0.0f), Vec3(0.0f), Vec3(1.0f));
			}
		}
		else
		{
			_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
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
			_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadLightMap()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\light_maps\\");
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
			_fe3d.modelEntity_setLightMap(_currentModelID, newFilePath);
			_fe3d.modelEntity_setLightMapped(_currentModelID, true);
		}
		else
		{
			_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
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
			_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
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
			_fe3d.modelEntity_setNormalMapped(_currentModelID, true);
		}
		else
		{
			_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::setCurrentProjectID(const string& projectName)
{
	_currentProjectID = projectName;
}

bool ModelEditor::isLoaded()
{
	return _isEditorLoaded;
}

const vector<string>& ModelEditor::getAllMeshFileNames()
{
	return _meshFileNames;
}

const vector<string>& ModelEditor::getLoadedModelIDs()
{
	std::sort(_loadedModelIDs.begin(), _loadedModelIDs.end());
	return _loadedModelIDs;
}

bool ModelEditor::_addModel(const string& modelName, string meshPath, string diffuseMapPath, string lightMapPath, string reflectionMapPath, string normalMapPath,
	Vec3 size, bool isFaceCulled, bool isShadowed, bool isTransparent, bool isSpecular, int reflectionType,
	float specularFactor, float specularIntensity, float lightness, Vec3 color, float uvRepeat, string lodEntityID, bool isInstanced,
	vector<string> aabbNames, vector<Vec3> aabbPositions, vector<Vec3> aabbSizes)
{
	// If model name not existing yet
	if (std::find(_loadedModelIDs.begin(), _loadedModelIDs.end(), modelName) == _loadedModelIDs.end())
	{
		// Add model name
		_loadedModelIDs.push_back(modelName);

		// Add 3D model
		if (meshPath != "")
		{
			_fe3d.modelEntity_add(modelName, meshPath, Vec3(0.0f, 0.01f, 0.0f), Vec3(0.0f), size, false);

			// Add AABBs
			for (unsigned int i = 0; i < aabbNames.size(); i++)
			{
				_fe3d.aabbEntity_bindToModelEntity(modelName, aabbPositions[i], aabbSizes[i], true, true, modelName + "@" + aabbNames[i]);
			}

			// Diffuse map
			if (diffuseMapPath != "")
			{
				_fe3d.modelEntity_setDiffuseMap(modelName, diffuseMapPath);
			}

			// Light map
			if (lightMapPath != "")
			{
				_fe3d.modelEntity_setLightMap(modelName, lightMapPath);
				_fe3d.modelEntity_setLightMapped(modelName, true);
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
				_fe3d.modelEntity_setNormalMapped(modelName, true);
			}

			// Set boolean options
			_fe3d.modelEntity_setFaceCulled(modelName, isFaceCulled);
			_fe3d.modelEntity_setShadowed(modelName, isShadowed);
			_fe3d.modelEntity_setTransparent(modelName, isTransparent);
			_fe3d.modelEntity_setSpecularLighted(modelName, isSpecular);
			_fe3d.modelEntity_setInstanced(modelName, isInstanced, { Vec3(0.0f) });
			
			// Set other options
			_fe3d.modelEntity_setSpecularFactor(modelName, specularFactor);
			_fe3d.modelEntity_setSpecularIntensity(modelName, specularIntensity);
			_fe3d.modelEntity_setLightness(modelName, lightness);
			_fe3d.modelEntity_setColor(modelName, color); 
			_fe3d.modelEntity_setUvRepeat(modelName, uvRepeat);
			_fe3d.modelEntity_setLevelOfDetailEntity(modelName, lodEntityID);

			// Reflection type
			if (reflectionType == 1)
			{
				_fe3d.modelEntity_setSkyReflective(modelName, true);
			}
			else if (reflectionType == 2)
			{
				_fe3d.modelEntity_setSceneReflective(modelName, true);
			}
		}

		return true;
	}
	else
	{
		_fe3d.logger_throwWarning("Model name \"" + modelName.substr(1) + "\" already exists!");

		return false;
	}
}