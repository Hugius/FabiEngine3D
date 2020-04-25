#include <filesystem>

#include "model_editor.hpp"

void ModelEditor::update(float delta)
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
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
			}
		}
		else if (_activeScreenID == "modelManagementScreen") // Model management screen
		{
			if (_hoveredItemID == "addModel")
			{
				_gui->getGlobalScreen()->addTextfield("newModelName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter model name:", vec3(1.0f));
				_gui->getGlobalScreen()->addWriteField("newModelName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f));
				_gui->getGlobalScreen()->getWriteField("newModelName")->setActive(true);
				_gui->setFocus(true);
				_modelCreationEnabled = true;
			}
			else if (_hoveredItemID == "editModel")
			{
				_modelChoosingEnabled = true;
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelChoiceScreen");
			}
			else if (_hoveredItemID == "deleteModel")
			{
				_modelRemovalEnabled = true;
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelChoiceScreen");
			}
			else if (_hoveredItemID == "back")
			{
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
				_fe3d.gameEntity_delete("grid");
				_fe3d.skyEntity_delete("modelEditorSky");
			}
		}
		else if (_activeScreenID == "modelChoiceScreen") // Model choice screen
		{
			if (std::find(_modelNames.begin(), _modelNames.end(), _hoveredItemID) != _modelNames.end()) // Check if model selected
			{
				if (_modelChoosingEnabled)
				{
					// Show game entity
					if (_fe3d.gameEntity_isExisting(_hoveredItemID))
					{
						_fe3d.gameEntity_show(_hoveredItemID);
					}

					// Set new current model name
					_currentModelName = _hoveredItemID;
					_modelEditingEnabled = true;
					_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelEditingScreen");
				}
				else if (_modelRemovalEnabled)
				{
					// Remove game entity
					if (_fe3d.gameEntity_isExisting(_hoveredItemID))
					{
						_fe3d.gameEntity_delete(_hoveredItemID);
					}

					// Delete from model names vector
					for (size_t i = 0; i < _modelNames.size(); i++)
					{
						if (_modelNames[i] == _hoveredItemID)
						{
							_modelNames.erase(_modelNames.begin() + i);
						}
					}

					// Delete choice button and go back to management screen
					_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->deleteButton(_hoveredItemID);
					_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
					_currentModelName = "";
					_modelRemovalEnabled = false;
				}
			}
			else if (_hoveredItemID == "back")
			{
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
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
				// Hide game entity
				if (_fe3d.gameEntity_isExisting(_currentModelName))
				{
					_fe3d.gameEntity_hide(_currentModelName);
				}

				_currentModelName = "";
				_modelEditingEnabled = false;
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

void ModelEditor::_updateModelCreation()
{
	if (_modelCreationEnabled)
	{
		// Check if pressed ESCAPE or ENTER
		if (_gui->getGlobalScreen()->getWriteField("newModelName")->cancelledInput() ||
			_gui->getGlobalScreen()->getWriteField("newModelName")->confirmedInput())
		{
			// Extract new name
			string modelName = _gui->getGlobalScreen()->getWriteField("newModelName")->getTextContent();

			// Create new project
			if (_gui->getGlobalScreen()->getWriteField("newModelName")->confirmedInput())
			{
				// If modelname not existing yet
				if (std::find(_modelNames.begin(), _modelNames.end(), modelName) == _modelNames.end())
				{
					// Add model name
					_modelNames.push_back(modelName);
					_currentModelName = modelName;
					_modelEditingEnabled = true;

					// Add scrolling list button
					_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton(modelName, modelName);

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
			_gui->getGlobalScreen()->deleteWriteField("newModelName");
		}
	}
}

void ModelEditor::_updateModelEditing()
{
	if (_modelEditingEnabled)
	{
		// Update cursor difference
		static vec2 totalCursorDifference = vec2(0.0f);
		static vec2 oldPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());
		vec2 currentPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());;
		vec2 difference = currentPos - oldPos;
		oldPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());

		// Update scrolling
		static float scollSpeed = 0.0f;
		if (_fe3d.misc_isMouseInsideViewport()) // Only if cursor inside 3d screen
		{
			scollSpeed += float(-_fe3d.input_getMouseWheelY() / 100.0f);
		}
		scollSpeed *= 0.995f;
		scollSpeed = std::clamp(scollSpeed, -1.0f, 1.0f);
		_cameraDistance += scollSpeed;
		_cameraDistance = std::clamp(_cameraDistance, _minCameraDistance, _maxCameraDistance);

		// Check if LMB pressed
		if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_MIDDLE))
		{
			if (_fe3d.misc_isMouseInsideViewport()) // Only if cursor inside 3d screen
			{
				totalCursorDifference.x += difference.x * _cameraSpeed;
				totalCursorDifference.y += difference.y * _cameraSpeed;
				totalCursorDifference.y = std::clamp(totalCursorDifference.y, 0.0f, 1.0f);
			}
		}

		// Calculate new camera position
		float x = (_cameraDistance * sin(totalCursorDifference.x));
		float y = _minCameraHeight + (_cameraDistance * totalCursorDifference.y);
		float z = (_cameraDistance * cos(totalCursorDifference.x));

		// Update camera position
		_fe3d.camera_setPosition(vec3(x, y, z));
	}
}

void ModelEditor::_updateModelRemoval()
{
	if (_modelRemovalEnabled)
	{

	}
}

void ModelEditor::_loadOBJ()
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

void ModelEditor::_loadDiffuseMap()
{
	// Get the loaded filename
	string texName = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\DiffuseMaps\\", "PNG");

	// Check if user chose a filename
	if (texName != "")
	{
		_fe3d.gameEntity_setDiffuseMap(_currentModelName, "User\\Assets\\Textures\\DiffuseMaps\\" + texName.substr(0, texName.size() - 4));
	}
}

void ModelEditor::_loadLightMap()
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

void ModelEditor::_loadReflectionMap()
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