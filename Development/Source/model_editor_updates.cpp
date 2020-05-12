#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::update(float delta)
{
	_updateModelManagement();
	_updateModelCreation();
	_updateModelChoosing();
	_updateModelEditing();
	_updateModelRemoval();
	_updateMiscellaneous();
}

void ModelEditor::_updateModelManagement()
{
	auto managementScreen = _window->getScreen("modelManagement");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (managementScreen->getButton("addModel")->isHovered()) // Add model button
		{
			_gui->getGlobalScreen()->addTextfield("newModelName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter model name:", vec3(1.0f));
			_gui->getGlobalScreen()->addWriteField("newModelName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 0, 1, 0);
			_gui->getGlobalScreen()->getWriteField("newModelName")->setActive(true);
			_gui->setFocus(true);
			_modelCreationEnabled = true;
		}
		else if (managementScreen->getButton("editModel")->isHovered()) // Edit model button
		{
			_modelEditingEnabled = true;
			_window->setActiveScreen("modelChoice");
		}
		else if (managementScreen->getButton("deleteModel")->isHovered()) // Deelete model button
		{
			_modelRemovalEnabled = true;
			_window->setActiveScreen("modelChoice");
		}
		else if (managementScreen->getButton("back")->isHovered()) // Back button
		{
			_window->setActiveScreen("main");
			unloadEnvironment();
		}
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
				// Add model
				addModel(modelName, "", "", "", "", vec3(0.0f));

				// Go to editor screen
				_currentModelName = modelName;
				_modelEditingEnabled = true;
				_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelEditingMain");
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
	auto choiceScreen = _window->getScreen("modelChoice");

	// Check if LMB is pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		// Check which model has been chosen
		for (auto& modelName : _modelNames)
		{
			if (choiceScreen->getScrollingList("modelList")->getButton(modelName)->isHovered())
			{
				// Set new current model name
				_currentModelName = modelName;

				// Send user to editing screen
				if (_modelEditingEnabled)
				{
					// Show model name
					_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID(), "Model: " + modelName, 0.025f);
					_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID());

					// Go to editing screen
					_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelEditingMain");
				}
				else if (_modelRemovalEnabled) // Add confirmation choice
				{
					_gui->getGlobalScreen()->addTextfield("areYouSure", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Are you sure?", vec3(1.0f));
					_gui->getGlobalScreen()->addButton("yes", vec2(-0.1f, -0.1f), vec2(0.1f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Yes", vec3(1.0f), vec3(0.0f));
					_gui->getGlobalScreen()->addButton("no", vec2(0.1f, -0.1f), vec2(0.1f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "No", vec3(1.0f), vec3(0.0f));
				}
			}
		}

		// Back button
		if (choiceScreen->getButton("back")->isHovered())
		{
			_modelEditingEnabled = false;
			_modelRemovalEnabled = false;
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelManagement");
		}
	}
}

void ModelEditor::_updateModelEditing()
{
	if (_modelEditingEnabled)
	{
		if (_window->getActiveScreen()->getID() == "modelEditingMain")
		{
			_updateModelEditingMain();
		}
		else if (_window->getActiveScreen()->getID() == "modelEditingMesh")
		{
			_updateModelEditingMesh();
		}
		else if (_window->getActiveScreen()->getID() == "modelEditingOptions")
		{
			_updateModelEditingOptions();
		}
	}

	// Update cursor difference
	static vec2 totalCursorDifference = vec2(0.0f);
	static vec2 cameraAcceleration = vec2(0.0f);
	static vec2 lastCursorPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());
	vec2 cursorPosition = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());
	vec2 cursorDifference = cursorPosition - lastCursorPos;
	lastCursorPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());

	// Update scrolling
	static float scollSpeed = 0.0f;
	if (_fe3d.misc_isMouseInsideViewport() && !_fe3d.input_getKeyDown(Input::KEY_S)) // Only if cursor inside 3d screen and 'S' not pressed
	{
		scollSpeed += float(-_fe3d.input_getMouseWheelY() / 100.0f);
	}
	scollSpeed *= 0.995f;
	scollSpeed = std::clamp(scollSpeed, -1.0f, 1.0f);
	_cameraDistance += scollSpeed;
	_cameraDistance = std::clamp(_cameraDistance, _minCameraDistance, _maxCameraDistance);

	// Check if MMB pressed
	if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_MIDDLE))
	{
		if (_fe3d.misc_isMouseInsideViewport()) // Only if cursor inside 3d screen
		{
			cameraAcceleration.x += cursorDifference.x * _cameraSpeed;
			cameraAcceleration.y += cursorDifference.y * _cameraSpeed;
		}
	}

	// Calculate cursor moving speed
	cameraAcceleration *= 0.99f;
	totalCursorDifference += cameraAcceleration;
	totalCursorDifference.y = std::clamp(totalCursorDifference.y, 0.0f, 1.0f);

	// Calculate new camera position
	float x = (_cameraDistance * sin(totalCursorDifference.x));
	float y = _minCameraHeight + (_cameraDistance * totalCursorDifference.y);
	float z = (_cameraDistance * cos(totalCursorDifference.x));

	// Update camera position
	_fe3d.camera_setPosition(vec3(x, y, z));

	// Update shadow caster position
	static int frameCounter = 0;
	frameCounter++;
	if ((frameCounter % 250) == 0)
	{
		float distance = max(min(_cameraDistance * 2.0f, 50.0f), 10.0f);
		_fe3d.gfx_addShadows(vec3(distance), vec3(0.0f), distance * 2.0f, distance * 3.0f);
	}
}

void ModelEditor::_updateModelEditingMain()
{
	auto screen = _window->getScreen("modelEditingMain");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("mesh")->isHovered())
		{
			_window->setActiveScreen("modelEditingMesh");
		}
		else if (screen->getButton("options")->isHovered())
		{
			if (_fe3d.gameEntity_isExisting(_currentModelName))
			{
				_window->setActiveScreen("modelEditingOptions");
			}
		}
		else if (screen->getButton("back")->isHovered())
		{
			// Hide game entity
			if (_fe3d.gameEntity_isExisting(_currentModelName))
			{
				_fe3d.gameEntity_hide(_currentModelName);
			}

			_currentModelName = "";
			_modelEditingEnabled = false;
			_window->setActiveScreen("modelChoice");
			_fe3d.textEntity_hide(_gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID());
		}
	}

	// Check if OBJ exists
	bool existing = _fe3d.gameEntity_isExisting(_currentModelName);
	bool hoverable = false;
	if (existing)
	{
		hoverable = existing && !_fe3d.gameEntity_isMultiTextured(_currentModelName);

		// Show OBJ model
		_fe3d.gameEntity_show(_currentModelName);
	}

	// Editing buttons hoverability
	_gui->getViewport("left")->getWindow("main")->getScreen("modelEditingMesh")->getButton("loadDiffuseMap")->setHoverable(hoverable);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelEditingMesh")->getButton("loadLightMap")->setHoverable(hoverable);
	_gui->getViewport("left")->getWindow("main")->getScreen("modelEditingMesh")->getButton("loadReflectionMap")->setHoverable(hoverable);
}

void ModelEditor::_updateModelEditingMesh()
{
	auto screen = _window->getScreen("modelEditingMesh");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("loadOBJ")->isHovered())
		{
			_loadOBJ();
		}
		else if (screen->getButton("loadDiffuseMap")->isHovered())
		{
			_loadDiffuseMap();
		}
		else if (screen->getButton("loadLightMap")->isHovered())
		{
			_loadLightMap();
		}
		else if (screen->getButton("loadReflectionMap")->isHovered())
		{
			_loadReflectionMap();
		}
		else if (screen->getButton("back")->isHovered())
		{
			_window->setActiveScreen("modelEditingMain");
		}
	}
}

void ModelEditor::_updateModelEditingOptions()
{
	auto screen = _window->getScreen("modelEditingOptions");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getScrollingList("optionsList")->getButton("setSize")->isHovered())
		{
			_modelResizingEnabled = true;

			// Add textfields and writefields
			_gui->getGlobalScreen()->addTextfield("modelSizeX", vec2(-0.3f, 0.1f), vec2(0.05f, 0.1f), "X", vec3(1.0f));
			_gui->getGlobalScreen()->addTextfield("modelSizeY", vec2(0.0f, 0.1f), vec2(0.05f, 0.1f), "Y", vec3(1.0f));
			_gui->getGlobalScreen()->addTextfield("modelSizeZ", vec2(0.3f, 0.1f), vec2(0.05f, 0.1f), "Z", vec3(1.0f));
			_gui->getGlobalScreen()->addWriteField("modelSizeX", vec2(-0.3f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
			_gui->getGlobalScreen()->addWriteField("modelSizeY", vec2(0.0f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
			_gui->getGlobalScreen()->addWriteField("modelSizeZ", vec2(0.3f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f)), 0, 1, 1, 1;
			_gui->getGlobalScreen()->addButton("done", vec2(0.0f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));

			// Set default model size
			vec3 currentSize = _fe3d.gameEntity_getSize(_currentModelName);
			_gui->getGlobalScreen()->getWriteField("modelSizeX")->setTextContent(std::to_string(int(currentSize.x * 10.0f)));
			_gui->getGlobalScreen()->getWriteField("modelSizeY")->setTextContent(std::to_string(int(currentSize.y * 10.0f)));
			_gui->getGlobalScreen()->getWriteField("modelSizeZ")->setTextContent(std::to_string(int(currentSize.z * 10.0f)));
		}
		else if (screen->getButton("back")->isHovered())
		{
			_window->setActiveScreen("modelEditingMain");
		}
	}

	// Update model resizing through cursor
	if (_fe3d.input_getKeyDown(Input::KEY_S))
	{
		float scrollSpeed = float(_fe3d.input_getMouseWheelY());
		_fe3d.gameEntity_setSize(_currentModelName, _fe3d.gameEntity_getSize(_currentModelName) * (1.0f + (scrollSpeed)));
	}

	// Update model resizing through buttons
	if (_modelResizingEnabled)
	{
		// Current model size
		vec3 newSize = _fe3d.gameEntity_getSize(_currentModelName);

		// X
		if (_gui->getGlobalScreen()->getWriteField("modelSizeX")->getTextContent() != "")
		{
			newSize.x = float(stoi(_gui->getGlobalScreen()->getWriteField("modelSizeX")->getTextContent())) / 10.0f;
		}

		// Y
		if (_gui->getGlobalScreen()->getWriteField("modelSizeY")->getTextContent() != "")
		{
			newSize.y = float(stoi(_gui->getGlobalScreen()->getWriteField("modelSizeY")->getTextContent())) / 10.0f;
		}

		// Z
		if (_gui->getGlobalScreen()->getWriteField("modelSizeZ")->getTextContent() != "")
		{
			newSize.z = float(stoi(_gui->getGlobalScreen()->getWriteField("modelSizeZ")->getTextContent())) / 10.0f;
		}

		// Set new model size
		_fe3d.gameEntity_setSize(_currentModelName, newSize);

		// Done button
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (_gui->getGlobalScreen()->getButton("done")->isHovered())
			{
				_modelResizingEnabled = false;
				_gui->getGlobalScreen()->deleteTextfield("modelSizeX");
				_gui->getGlobalScreen()->deleteWriteField("modelSizeX");
				_gui->getGlobalScreen()->deleteTextfield("modelSizeY");
				_gui->getGlobalScreen()->deleteWriteField("modelSizeY");
				_gui->getGlobalScreen()->deleteTextfield("modelSizeZ");
				_gui->getGlobalScreen()->deleteWriteField("modelSizeZ");
				_gui->getGlobalScreen()->deleteButton("done");
			}
		}
	}
}

void ModelEditor::_updateModelRemoval()
{
	if (_modelRemovalEnabled)
	{
		if (_currentModelName != "")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (_gui->getGlobalScreen()->getButton("yes")->isHovered()) // Confirmed
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
					_gui->getViewport("left")->getWindow("main")->getScreen("modelChoice")->getScrollingList("modelList")->deleteButton(_currentModelName);
					_currentModelName = "";

					// Delete confirmation GUI
					_gui->getGlobalScreen()->deleteTextfield("areYouSure");
					_gui->getGlobalScreen()->deleteButton("yes");
					_gui->getGlobalScreen()->deleteButton("no");
				}
				else if (_gui->getGlobalScreen()->getButton("no")->isHovered()) // Cancelled
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
}