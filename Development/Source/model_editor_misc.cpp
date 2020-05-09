#include <filesystem>

#include "model_editor.hpp"

ModelEditor::ModelEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{
	// Load all OBJ filenames from assets folder
	_loadObjFileNames();
}

void ModelEditor::load()
{
	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 1000.0f, vec3(_startingCameraPos), -90.0f, 0.0f);
	_fe3d.camera_enableLookat(vec3(0.0f));

	// Graphics
	_fe3d.gfx_addAmbientLighting(0.25f);
	_fe3d.gfx_addDirectionalLighting(vec3(1000.0f), 0.5f);
	_fe3d.gfx_addLightMapping();
	_fe3d.gfx_addSkyReflections(0.25f);
	_fe3d.gfx_addBloom(1.0f, 0.0f, 10);
	_fe3d.gfx_setSkyBrightness(0.75f);

	// 3D Environment
	_fe3d.gameEntity_add("modelEditorGrid", "Engine\\OBJs\\plane", vec3(0.0f), vec3(0.0f), vec3(100.0f, 1.0f, 100.0f));
	_fe3d.gameEntity_setDiffuseMap("modelEditorGrid", "Engine\\Textures\\grass");
	_fe3d.gameEntity_setUvRepeat("modelEditorGrid", 10.0f);
	_fe3d.skyEntity_add("modelEditorSky", 0.1f, "Engine\\Textures\\Skybox\\");
	_fe3d.skyEntity_select("modelEditorSky");

	// Other
	_gui->getGlobalScreen()->addTextfield("currentModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_modelNameTextfieldEntityID = _gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID();
	_loaded = true;
}

void ModelEditor::unload()
{
	// Graphics
	_fe3d.gfx_removeAmbientLighting();
	_fe3d.gfx_removeDirectionalLighting();
	_fe3d.gfx_removeLightMapping();
	_fe3d.gfx_removeSkyReflections();
	_fe3d.gfx_removeBloom();

	// 3D environment
	_fe3d.gameEntity_delete("modelEditorGrid");
	_fe3d.skyEntity_delete("modelEditorSky");

	// Delete models
	for (auto& modelName : _modelNames)
	{
		if (_fe3d.gameEntity_isExisting(modelName))
		{
			_fe3d.gameEntity_delete(modelName);
		}
	}
	_modelNames.clear();

	// Delete model name textfield & scrolling list buttons
	_gui->getGlobalScreen()->deleteTextfield("currentModelName");
	_gui->getViewport("left")->getWindow("main")->getScreen("modelChoice")->getScrollingList("modelList")->deleteButtons();

	// Other
	_modelCreationEnabled = false;
	_modelChoosingEnabled = false;
	_modelEditingEnabled = false;
	_modelResizingEnabled = false;
	_modelRemovalEnabled = false;
	_loaded = false;
	_cameraDistance = 5.0f;
	_modelNameTextfieldEntityID = "";
	_currentModelName = "";
}

void ModelEditor::_loadObjFileNames()
{
	// Remove potential previous filenames
	if (!_totalObjFileNames.empty())
	{
		_totalObjFileNames.clear();
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
		_totalObjFileNames.push_back(objPath.substr(0, endOfNameIndex));
	}
}

void ModelEditor::addModel(string modelName)
{
	// If modelname not existing yet
	if (std::find(_modelNames.begin(), _modelNames.end(), modelName) == _modelNames.end())
	{
		// Add model name
		_modelNames.push_back(modelName);

		// Add scrolling list button
		_gui->getViewport("left")->getWindow("main")->getScreen("modelChoice")->getScrollingList("modelList")->addButton(modelName, modelName);
	}
	else
	{
		_fe3d.logger_throwWarning("Modelname \"" + modelName + "\" is already in use!");
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
			_fe3d.gameEntity_add(_currentModelName, "User\\Assets\\OBJs\\" + objName.substr(0, objName.size() - 4), vec3(0.0f), vec3(0.0f), vec3(1.0f));
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
			_fe3d.gameEntity_setDiffuseMap(_currentModelName, "User\\Assets\\Textures\\DiffuseMaps\\" + texName.substr(0, texName.size() - 4));
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
			_fe3d.gameEntity_setLightMap(_currentModelName, "User\\Assets\\Textures\\LightMaps\\" + texName.substr(0, texName.size() - 4));
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
			_fe3d.gameEntity_setReflectionMap(_currentModelName, "User\\Assets\\Textures\\ReflectionMaps\\" + texName.substr(0, texName.size() - 4));
			_fe3d.gameEntity_setSkyReflective(_currentModelName, true);
		}
	}
}

bool ModelEditor::isLoaded()
{
	return _loaded;
}

vector<string>& ModelEditor::getTotalObjFileNames()
{
	return _totalObjFileNames;
}

vector<string>& ModelEditor::getModelNames()
{
	return _modelNames;
}