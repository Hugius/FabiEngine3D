#include "model_editor.hpp"

#include <filesystem>

void ModelEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		_fe3d.input_setKeyTogglingLocked(_gui->getGlobalScreen()->isFocused() || !_fe3d.misc_isMouseInsideViewport());

		// Update reference model visibility
		if (_fe3d.input_getKeyToggled(Input::KEY_R))
		{
			_fe3d.gameEntity_hide("@@cube");
		}
		else
		{
			_fe3d.gameEntity_show("@@cube");
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
	string objDirectoryPath = _fe3d.misc_getRootDirectory() + "User\\Assets\\OBJs\\";
	int endOfNameIndex = 0;

	// Get all filenames
	for (const auto& entry : std::filesystem::directory_iterator(objDirectoryPath))
	{
		string objPath = string(entry.path().u8string());
		objPath.erase(0, objDirectoryPath.size());

		// Loop over file path
		for (unsigned int i = 0; i < objPath.size(); i++)
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
	if (!_modelResizingEnabled)
	{
		// Get the loaded filename
		string filePath = _fe3d.misc_getWinExplorerFilename("User\\Assets\\OBJs\\", "OBJ");

		// Not cancelled
		if (filePath != "")
		{
			// Delete existing entity
			if (_fe3d.gameEntity_isExisting(_currentModelName))
			{
				_fe3d.gameEntity_delete(_currentModelName);
			}

			// Clear OBJ cache
			_fe3d.misc_clearOBJCache(filePath);

			// Add new game entity
			_fe3d.gameEntity_add(_currentModelName, filePath, vec3(0.0f), vec3(0.0f), vec3(1.0f));
			_fe3d.aabbEntity_bindToGameEntity(_currentModelName, vec3(1.0f), true);
			_fe3d.gameEntity_setColor(_currentModelName, vec3(1.0f));
		}
	}
}

void ModelEditor::_loadDiffuseMap()
{
	if (!_modelResizingEnabled)
	{
		// Get the loaded filename
		string filePath = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\DiffuseMaps\\" , "PNG");

		// Check if user chose a filename
		if (filePath != "")
		{
			_fe3d.misc_clearTextureCache(filePath);
			_fe3d.gameEntity_setDiffuseMap(_currentModelName, filePath);
		}
	}
}

void ModelEditor::_loadLightMap()
{
	if (!_modelResizingEnabled)
	{
		// Get the loaded filename
		string filePath = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\LightMaps\\", "PNG");

		// Check if user chose a filename
		if (filePath != "")
		{
			_fe3d.misc_clearTextureCache(filePath);
			_fe3d.gameEntity_setLightMap(_currentModelName, filePath);
			_fe3d.gameEntity_setLightMapped(_currentModelName, true);
		}
	}
}

void ModelEditor::_loadReflectionMap()
{
	if (!_modelResizingEnabled)
	{
		// Get the loaded filename
		string filePath = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\ReflectionMaps\\", "PNG");

		// Check if user chose a filename
		if (filePath != "")
		{
			_fe3d.misc_clearTextureCache(filePath);
			_fe3d.gameEntity_setReflectionMap(_currentModelName, filePath);
			_fe3d.gameEntity_setSkyReflective(_currentModelName, true);
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
	return _modelNames;
}

bool ModelEditor::_addModel(const string& modelName, string objName, string diffuseMapName, string lightMapName, string reflectionMapName,
	vec3 size, bool isFaceCulled, bool isShadowed, bool isTransparent, bool isReflective, bool isSpecular,
	float specularFactor, float specularIntensity, float lightness, vec3 color, float uvRepeat, vec3 aabbSize)
{
	// If model name not existing yet
	if (std::find(_modelNames.begin(), _modelNames.end(), modelName) == _modelNames.end())
	{
		// Add model name
		_modelNames.push_back(modelName);

		// Add 3D model
		if (objName != "")
		{
			_fe3d.gameEntity_add(modelName, objName, vec3(0.0f, 0.01f, 0.0f), vec3(0.0f), size, false);
			_fe3d.aabbEntity_bindToGameEntity(modelName, aabbSize, true);
			_fe3d.aabbEntity_hide(modelName);

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

			// Set boolean options
			_fe3d.gameEntity_setFaceCulled(modelName, isFaceCulled);
			_fe3d.gameEntity_setShadowed(modelName, isShadowed);
			_fe3d.gameEntity_setTransparent(modelName, isTransparent);
			_fe3d.gameEntity_setSceneReflective(modelName, isReflective);
			_fe3d.gameEntity_setSpecularLighted(modelName, isSpecular);

			// Set other options
			_fe3d.gameEntity_setSpecularFactor(modelName, specularFactor);
			_fe3d.gameEntity_setSpecularIntensity(modelName, specularIntensity);
			_fe3d.gameEntity_setOriginalLightness(modelName, lightness);
			_fe3d.gameEntity_setLightness(modelName, lightness);
			_fe3d.gameEntity_setColor(modelName, color); 
			_fe3d.gameEntity_setUvRepeat(modelName, uvRepeat);
		}

		return true;
	}
	else
	{
		_fe3d.logger_throwWarning("Modelname \"" + modelName.substr(1, modelName.size() - 1) + "\" is already in use!");

		return false;
	}
}