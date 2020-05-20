#include <filesystem>

#include "model_editor.hpp"

void ModelEditor::_updateMiscellaneous()
{
	// Update reference model visibility
	if (_isLoaded)
	{
		if (!_gui->isFocused())
		{
			if (_fe3d.input_getKeyToggled(Input::KEY_R))
			{
				_fe3d.gameEntity_hide("@cube");
			}
			else
			{
				_fe3d.gameEntity_show("@cube");
			}
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