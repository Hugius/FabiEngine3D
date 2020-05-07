#include <filesystem>

#include "model_editor.hpp"

void ModelEditor::update(float delta)
{
	auto window = _gui->getViewport("leftViewport")->getWindow("mainWindow");
	auto mainScreen = window->getScreen("mainScreen");
	
	// Check if LMB pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (mainScreen->getButton("modelEditor")->isHovered()) // Model editor button
		{
			_loadEnvironment();
			window->setActiveScreen("modelManagementScreen");
		}
	}

	// Update all processes
	_updateModelManagement();
	_updateModelCreation();
	_updateModelChoosing();
	_updateModelEditing();
	_updateModelRemoval();
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

void ModelEditor::_updateModelManagement()
{
	auto window = _gui->getViewport("leftViewport")->getWindow("mainWindow");
	auto managementScreen = window->getScreen("modelManagementScreen");

	// GUI management
	if (managementScreen->getButton("addModel")->isHovered()) // Add model button
	{
		_gui->getGlobalScreen()->addTextfield("newModelName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter model name:", vec3(1.0f));
		_gui->getGlobalScreen()->addWriteField("newModelName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f));
		_gui->getGlobalScreen()->getWriteField("newModelName")->setActive(true);
		_gui->setFocus(true);
		_modelCreationEnabled = true;
	}
	else if (managementScreen->getButton("editModel")->isHovered()) // Edit model button
	{
		_modelEditingEnabled = true;
		window->setActiveScreen("modelChoiceScreen");
	}
	else if (managementScreen->getButton("deleteModel")->isHovered()) // Deelete model button
	{
		_modelRemovalEnabled = true;
		window->setActiveScreen("modelChoiceScreen");
	}
	else if (managementScreen->getButton("back")->isHovered()) // Back button
	{
		window->setActiveScreen("mainScreen");
		_unloadEnvironment();
	}
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

void ModelEditor::_updateModelChoosing()
{
	auto window = _gui->getViewport("leftViewport")->getWindow("mainWindow");
	auto choiceScreen = window->getScreen("modelChoiceScreen");

	for (auto& modelName : _modelNames)
	{
		if (choiceScreen->getScrollingList("modelList")->getButton(modelName)->isHovered())
		{
			// Set new current model name
			_currentModelName = modelName;

			// Send user to editing screen
			if (_modelEditingEnabled)
			{
				// Show game entity
				if (_fe3d.gameEntity_isExisting(modelName))
				{
					_fe3d.gameEntity_show(modelName);
				}

				// Go to editing screen
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelEditingScreen");
			}
			else if (_modelRemovalEnabled) // Add confirmation choice
			{
				_gui->getGlobalScreen()->addTextfield("areYouSure", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Are you sure?", vec3(1.0f));
				_gui->getGlobalScreen()->addButton("yes", vec2(-0.1f, -0.1f), vec2(0.1f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Yes", vec3(1.0f), vec3(0.0f));
				_gui->getGlobalScreen()->addButton("no", vec2(0.1f, -0.1f), vec2(0.1f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "No", vec3(1.0f), vec3(0.0f));
			}
		}
		else if (choiceScreen->getButton("back")->isHovered())
		{
			_modelRemovalEnabled = false;
			_modelEditingEnabled = false;
			_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
		}
	}
}

void ModelEditor::_updateModelEditing()
{
	if (_modelEditingEnabled)
	{
		auto window = _gui->getViewport("leftViewport")->getWindow("mainWindow");
		auto editingScreen = window->getScreen("modelEditingScreen");

		// GUI management
		if (editingScreen->getButton("loadOBJ")->isHovered())
		{
			_loadOBJ();
		}
		else if (editingScreen->getButton("loadDiffuseMap")->isHovered())
		{
			_loadDiffuseMap();
		}
		else if (editingScreen->getButton("loadLightMap")->isHovered())
		{
			_loadLightMap();
		}
		else if (editingScreen->getButton("loadReflectionMap")->isHovered())
		{
			_loadReflectionMap();
		}
		else if (editingScreen->getButton("back")->isHovered())
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
		if (_currentModelName != "")
		{
			if (_gui->getGlobalScreen()->getButton("yes")->isHovered() && _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT)) // Confirmed
			{
				// Remove game entity
				if (_fe3d.gameEntity_isExisting(_currentModelName))
				{
					_fe3d.gameEntity_delete(_currentModelName);
				}

				// Delete from model names vector
				for (size_t i = 0; i < _modelNames.size(); i++)
				{
					if (_modelNames[i] == _currentModelName)
					{
						_modelNames.erase(_modelNames.begin() + i);
					}
				}

				// Delete choice button and go back to management screen
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->deleteButton(_currentModelName);
				_currentModelName = "";

				// Delete confirmation GUI
				_gui->getGlobalScreen()->deleteTextfield("areYouSure");
				_gui->getGlobalScreen()->deleteButton("yes");
				_gui->getGlobalScreen()->deleteButton("no");
			}
			else if (_gui->getGlobalScreen()->getButton("no")->isHovered() && _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT)) // Cancelled
			{
				_currentModelName = "";

				// Delete confirmation GUI
				_gui->getGlobalScreen()->deleteTextfield("areYouSure");
				_gui->getGlobalScreen()->deleteButton("yes");
				_gui->getGlobalScreen()->deleteButton("no");
			}
		}
	}
}