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
		string objName = _fe3d.misc_getWinExplorerFilename("User\\Assets\\OBJs\\", "OBJ");
		if (objName != "") // Not cancelled
		{
			// Already exists
			if (_fe3d.gameEntity_isExisting(_currentModelName))
			{
				_fe3d.gameEntity_delete(_currentModelName);
			}

			// Add new game entity
			_fe3d.gameEntity_add(_currentModelName, "User\\Assets\\OBJs\\" + objName, vec3(0.0f), vec3(0.0f), vec3(1.0f));
			_fe3d.aabbEntity_bindToGameEntity(_currentModelName, vec3(1.0f), true);
			_fe3d.gameEntity_setColor(_currentModelName, vec3(0.5f));
		}
	}
}

void ModelEditor::_loadDiffuseMap()
{
	if (!_modelResizingEnabled)
	{
		// Get the loaded filename
		string texName = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\DiffuseMaps\\", "PNG");

		// Check if user chose a filename
		if (texName != "")
		{
			_fe3d.gameEntity_setDiffuseMap(_currentModelName, "User\\Assets\\Textures\\DiffuseMaps\\" + texName);
		}
	}
}

void ModelEditor::_loadLightMap()
{
	if (!_modelResizingEnabled)
	{
		// Get the loaded filename
		string texName = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\LightMaps\\", "PNG");

		// Check if user chose a filename
		if (texName != "")
		{
			_fe3d.gameEntity_setLightMap(_currentModelName, "User\\Assets\\Textures\\LightMaps\\" + texName);
			_fe3d.gameEntity_setLightmapped(_currentModelName, true);
		}
	}
}

void ModelEditor::_loadReflectionMap()
{
	if (!_modelResizingEnabled)
	{
		// Get the loaded filename
		string texName = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\ReflectionMaps\\", "PNG");

		// Check if user chose a filename
		if (texName != "")
		{
			_fe3d.gameEntity_setReflectionMap(_currentModelName, "User\\Assets\\Textures\\ReflectionMaps\\" + texName);
			_fe3d.gameEntity_setSkyReflective(_currentModelName, true);
		}
	}
}

void ModelEditor::setCurrentProjectName(string projectName)
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

bool ModelEditor::_addModel(string modelName, string objName, string diffuseMapName, string lightMapName, string reflectionMapName, vec3 size,
	bool isFaceCulled, bool isShadowed, bool isTransparent, bool isSpecular, float specularIntensity, vec3 color, float uvRepeat, vec3 aabbSize)
{
	// If model name not existing yet
	if (std::find(_modelNames.begin(), _modelNames.end(), modelName) == _modelNames.end())
	{
		// Add model name
		_modelNames.push_back(modelName);

		// Add 3D model
		if (objName != "")
		{
			_fe3d.gameEntity_add(modelName, objName, vec3(0.0f), vec3(0.0f), size, false);
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
				_fe3d.gameEntity_setLightmapped(modelName, true);
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
			_fe3d.gameEntity_setSpecularLighted(modelName, isSpecular);

			// Set other options
			_fe3d.gameEntity_setSpecularIntensity(modelName, specularIntensity);
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