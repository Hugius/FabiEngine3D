#include "model_editor.hpp"

#include <filesystem>

void ModelEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		// Lock toggling if GUI focused or cursor not in 3D viewport
		_fe3d.input_setKeyTogglingLocked(_gui.getGlobalScreen()->isFocused() || !_fe3d.misc_isCursorInsideViewport());

		// Update reference model visibility
		if (_fe3d.input_getKeyToggled(InputType::KEY_R))
		{
			_fe3d.gameEntity_hide("@@cube");
		}
		else
		{
			_fe3d.gameEntity_show("@@cube");
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
	}
}

void ModelEditor::_loadObjFileNames()
{
	// Remove potential previous filenames
	if (!_objFileNamesList.empty())
	{
		_objFileNamesList.clear();
	}

	// Determine full OBJ directory
	string objDirectoryPath = _fe3d.misc_getRootDirectory() + "user\\assets\\models\\";
	int endOfNameIndex = 0;

	// Get all filenames
	for (const auto& entry : std::filesystem::directory_iterator(objDirectoryPath))
	{
		string objPath = string(entry.path().u8string());
		objPath.erase(0, objDirectoryPath.size());

		// Loop over file path
		for (size_t i = 0; i < objPath.size(); i++)
		{
			// End of file name
			if (objPath[i] == '.')
			{
				endOfNameIndex = i;
			}
		}

		_objFileNamesList.push_back(objPath.substr(0, endOfNameIndex));
	}
}

void ModelEditor::_loadOBJ()
{
	// Get the loaded filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("user\\assets\\models\\");
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
			if (_fe3d.gameEntity_isExisting(_currentModelID))
			{
				// Clear OBJ cache
				_fe3d.misc_clearOBJCache(newFilePath);

				// Check if multiparted entity
				if (_fe3d.gameEntity_isMultiTextured(_currentModelID))
				{
					// Clear texture cache
					for (auto& path : _fe3d.gameEntity_getDiffuseMapPaths(_currentModelID))
					{
						_fe3d.misc_clearTextureCache(path);
					}
					for (auto& path : _fe3d.gameEntity_getLightMapPaths(_currentModelID))
					{
						_fe3d.misc_clearTextureCache(path);
					}
					for (auto& path : _fe3d.gameEntity_getReflectionMapPaths(_currentModelID))
					{
						_fe3d.misc_clearTextureCache(path);
					}
					for (auto& path : _fe3d.gameEntity_getNormalMapPaths(_currentModelID))
					{
						_fe3d.misc_clearTextureCache(path);
					}
				}

				// Reload model
				_fe3d.gameEntity_loadModel(_currentModelID, newFilePath);
			}
			else
			{
				// Create new entity
				_fe3d.gameEntity_add(_currentModelID, newFilePath, Vec3(0.0f), Vec3(0.0f), Vec3(1.0f));
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
	// Get the loaded filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("user\\assets\\textures\\diffuse_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache(newFilePath);
			_fe3d.gameEntity_setDiffuseMap(_currentModelID, newFilePath);
		}
		else
		{
			_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadLightMap()
{
	// Get the loaded filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("user\\assets\\textures\\light_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache(newFilePath);
			_fe3d.gameEntity_setLightMap(_currentModelID, newFilePath);
			_fe3d.gameEntity_setLightMapped(_currentModelID, true);
		}
		else
		{
			_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadReflectionMap()
{
	// Get the loaded filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("user\\assets\\textures\\reflection_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache(newFilePath);
			_fe3d.gameEntity_setReflectionMap(_currentModelID, newFilePath);
			_fe3d.gameEntity_setSkyReflective(_currentModelID, true);
		}
		else
		{
			_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadNormalMap()
{
	// Get the loaded filename
		const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("user\\assets\\textures\\normal_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache(newFilePath);
			_fe3d.gameEntity_setNormalMap(_currentModelID, newFilePath);
			_fe3d.gameEntity_setNormalMapped(_currentModelID, true);
		}
		else
		{
			_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool ModelEditor::isLoaded()
{
	return _isLoaded;
}

vector<string>& ModelEditor::getTotalObjFileNames()
{
	return _objFileNamesList;
}

vector<string>& ModelEditor::getModelNames()
{
	return _modelIDs;
}

bool ModelEditor::_addModel(const string& modelName, string objName, string diffuseMapName, string lightMapName, string reflectionMapName, string normalMapName,
	Vec3 size, bool isFaceCulled, bool isShadowed, bool isTransparent, bool isReflective, bool isSpecular,
	float specularFactor, float specularIntensity, float lightness, Vec3 color, float uvRepeat, string lodEntityID, bool isInstanced,
	vector<string> aabbNames, vector<Vec3> aabbPositions, vector<Vec3> aabbSizes)
{
	// If model name not existing yet
	if (std::find(_modelIDs.begin(), _modelIDs.end(), modelName) == _modelIDs.end())
	{
		// Add model name
		_modelIDs.push_back(modelName);

		// Add 3D model
		if (objName != "")
		{
			_fe3d.gameEntity_add(modelName, objName, Vec3(0.0f, 0.01f, 0.0f), Vec3(0.0f), size, false);

			// Add AABBs
			for (unsigned int i = 0; i < aabbNames.size(); i++)
			{
				_fe3d.aabbEntity_bindToGameEntity(modelName, aabbPositions[i], aabbSizes[i], true, modelName + "_" + aabbNames[i]);
			}

			// Diffuse map
			if (diffuseMapName != "")
			{
				_fe3d.gameEntity_setDiffuseMap(modelName, diffuseMapName);
			}

			// Light map
			if (lightMapName != "")
			{
				_fe3d.gameEntity_setLightMap(modelName, lightMapName);
				_fe3d.gameEntity_setLightMapped(modelName, true);
			}

			// Reflection map
			if (reflectionMapName != "")
			{
				_fe3d.gameEntity_setReflectionMap(modelName, reflectionMapName);
				_fe3d.gameEntity_setSkyReflective(modelName, true);
			}

			// Normal map
			if (normalMapName != "")
			{
				_fe3d.gameEntity_setNormalMap(modelName, normalMapName);
				_fe3d.gameEntity_setNormalMapped(modelName, true);
			}

			// Set boolean options
			_fe3d.gameEntity_setFaceCulled(modelName, isFaceCulled);
			_fe3d.gameEntity_setShadowed(modelName, isShadowed);
			_fe3d.gameEntity_setTransparent(modelName, isTransparent);
			_fe3d.gameEntity_setSceneReflective(modelName, isReflective);
			_fe3d.gameEntity_setSpecularLighted(modelName, isSpecular);
			_fe3d.gameEntity_setInstanced(modelName, isInstanced, { Vec3(0.0f) });

			// Set other options
			_fe3d.gameEntity_setSpecularFactor(modelName, specularFactor);
			_fe3d.gameEntity_setSpecularIntensity(modelName, specularIntensity);
			_fe3d.gameEntity_setOriginalLightness(modelName, lightness);
			_fe3d.gameEntity_setLightness(modelName, lightness);
			_fe3d.gameEntity_setColor(modelName, color); 
			_fe3d.gameEntity_setUvRepeat(modelName, uvRepeat);
			_fe3d.gameEntity_setLevelOfDetailEntity(modelName, lodEntityID);
		}

		return true;
	}
	else
	{
		_fe3d.logger_throwWarning("Model name \"" + modelName.substr(1) + "\" already exists!");

		return false;
	}
}