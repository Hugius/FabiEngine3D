#include <filesystem>
#include <fstream>
#include <sstream>

#include "ModelEditorr.hpp"

ModelEditorr::ModelEditorr(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{
	// Load all OBJ filenames from assets folder
	_loadObjFileNames();

	// Current model name textfield
	_gui->getGlobalScreen()->addTextfield("currentModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_modelNameTextfieldEntityID = _gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID();
}

void ModelEditorr::update(float delta)
{
	// Variables
	_activeScreenID = _gui->getViewport("leftViewport")->getWindow("mainWindow")->getActiveScreen()->getID();
	_hoveredItemID = _gui->getViewport("leftViewport")->getWindow("mainWindow")->getActiveScreen()->getHoveredItemID();

	// Check if LMB pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (_activeScreenID == "mainScreen") // Main screen
		{
			if (_hoveredItemID == "modelEditor")
			{
				_initializeEditor();
			}
		}
		else if (_activeScreenID == "modelManagementScreen") // Model management screen
		{
			if (_hoveredItemID == "addModel")
			{
				_gui->getGlobalScreen()->addTextfield("newModelName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter model name:", vec3(1.0f));
				_gui->getGlobalScreen()->addWritefield("newModelName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f));
				_gui->getGlobalScreen()->getWritefield("newModelName")->setActive(true);
				_gui->setFocus(true);
				_modelCreationEnabled = true;
			}
			else if (_hoveredItemID == "editModel")
			{
				_modelEditingEnabled = true;
			}
			else if (_hoveredItemID == "deleteModel")
			{
				_modelRemovalEnabled = true;
			}
			else if (_hoveredItemID == "back")
			{
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
			}
		}
		else if (_activeScreenID == "modelEditingScreen") // Model editing screen
		{
			if (_hoveredItemID == "loadOBJ")
			{
				_loadOBJ();
			}
			else if (_hoveredItemID == "loadDiffuseMap")
			{
				_loadDiffuseMap();
			}
			else if (_hoveredItemID == "loadLightMap")
			{
				_loadLightMap();
			}
			else if (_hoveredItemID == "loadReflectionMap")
			{
				_loadReflectionMap();
			}
			else if (_hoveredItemID == "back")
			{
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
				_fe3d.textEntity_hide(_modelNameTextfieldEntityID);
			}
		}
	}

	// Update all processes
	_updateModelCreation();
	_updateModelEditing();
	_updateModelRemoval();
}

void ModelEditorr::_updateModelCreation()
{
	if (_modelCreationEnabled)
	{
		// Check if pressed ESCAPE or ENTER
		if (_gui->getGlobalScreen()->getWritefield("newModelName")->cancelledInput() ||
			_gui->getGlobalScreen()->getWritefield("newModelName")->confirmedInput())
		{
			// Extract new name
			string modelName = _gui->getGlobalScreen()->getWritefield("newModelName")->getTextContent();

			// Create new project
			if (_gui->getGlobalScreen()->getWritefield("newModelName")->confirmedInput())
			{
				// If modelname not existing yet
				if (std::find(_modelNames.begin(), _modelNames.end(), modelName) == _modelNames.end())
				{
					// Add model name
					_modelNames.push_back(modelName);
					_currentModelName = modelName;
					_modelEditingEnabled = true;

					// Show model name
					_fe3d.textEntity_setTextContent(_modelNameTextfieldEntityID, "Model: " + modelName, 0.025f);
					_fe3d.textEntity_show(_modelNameTextfieldEntityID);

					// Disable texturing buttons
					_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->getButton("loadDiffuseMap")->setHoverable(false);
					_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->getButton("loadLightMap")->setHoverable(false);
					_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->getButton("loadReflectionMap")->setHoverable(false);

					// Go to editor screen
					_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelEditingScreen");
				}
				else
				{
					_fe3d.logger_throwWarning("This modelname is already in use!");
				}
			}

			// Cleanup
			_modelCreationEnabled = false;
			_gui->setFocus(false);
			_gui->getGlobalScreen()->deleteTextfield("newModelName");
			_gui->getGlobalScreen()->deleteWritefield("newModelName");
		}
	}
}

void ModelEditorr::_updateModelEditing()
{
	if (_modelEditingEnabled)
	{

	}
}

void ModelEditorr::_updateModelRemoval()
{
	if (_modelRemovalEnabled)
	{

	}
}

void ModelEditorr::_loadOBJ()
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

		// Enable texturing if not pre-multitextured
		if (_fe3d.gameEntity_isMultiTextured(_currentModelName))
		{
			_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->getButton("loadDiffuseMap")->setHoverable(false);
			_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->getButton("loadLightMap")->setHoverable(false);
			_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->getButton("loadReflectionMap")->setHoverable(false);
		}
		else
		{
			_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->getButton("loadDiffuseMap")->setHoverable(true);
			_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->getButton("loadLightMap")->setHoverable(true);
			_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->getButton("loadReflectionMap")->setHoverable(true);
		}
	}
}

void ModelEditorr::_loadDiffuseMap()
{
	// Get the loaded filename
	string texName = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\DiffuseMaps\\", "PNG");
	_fe3d.gameEntity_setDiffuseMap(_currentModelName, "User\\Assets\\Textures\\DiffuseMaps\\" + texName.substr(0, texName.size() - 4));
}

void ModelEditorr::_loadLightMap()
{

}

void ModelEditorr::_loadReflectionMap()
{

}

void ModelEditorr::_loadObjFileNames()
{
	// Remove potential previous filenames
	if (!_totalObjFileNames.empty())
	{
		_totalObjFileNames.clear();
	}

	string path = "../User/Assets/OBJs/";
	int endOfNameIndex = 0;

	// Get all filenames
	for (const auto & entry : std::filesystem::directory_iterator(path))
	{
		string path = string(entry.path().u8string());
		path.erase(0, 13);

		// Loop over file path
		for (unsigned int i = 0; i < path.size(); i++)
		{
			// End of file name
			if (path[i] == '.')
			{
				endOfNameIndex = i;
			}
		}
		_totalObjFileNames.push_back(path.substr(0, endOfNameIndex));
	}
}

void ModelEditorr::_initializeEditor()
{
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
	_fe3d.camera_load(90.0f, 0.1f, 1000.0f, vec3(0.0f, 2.5f, 5.0f), -90.0f, 0.0f);
	_fe3d.gfx_addAmbientLighting(0.5f);
	_fe3d.gfx_addDirectionalLighting(vec3(1000.0f), 1.0f);
	_fe3d.gameEntity_add("grid", "Engine\\OBJs\\plane", vec3(0.0f), vec3(0.0f), vec3(100.0f, 1.0f, 100.0f));
	_fe3d.gameEntity_setDiffuseMap("grid", "Engine\\Textures\\grass");
	_fe3d.gameEntity_setUvRepeat("grid", 10.0f);
}

vector<string>& ModelEditorr::getTotalObjFileNames()
{
	return _totalObjFileNames;
}