#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::update()
{
	if (_isLoaded)
	{
		_fe3d.gfx_enableLightMapping();
		_updateModelManagement();
		_updateModelCreation();
		_updateModelChoosing();
		_updateModelEditing();
		_updateModelRemoval();
		_updateMiscellaneous();
		_updateModelEditingCamera();

	}
}

void ModelEditor::_updateModelManagement()
{
	auto screen = _window->getScreen("modelManagement");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("addModel")->isHovered()) // Add model button
		{
			_gui->getGlobalScreen()->addValueForm("newModelName", "New model name", "", vec2(0.0f), vec2(0.5f, 0.1f));
			_modelCreationEnabled = true;
		}
		else if (screen->getButton("editModel")->isHovered()) // Edit model button
		{
			_modelChoosingEnabled = true;
			_modelEditingEnabled = true;
			for (auto& name : _modelNames) { name = name.substr(1, name.size()); }
			_gui->getGlobalScreen()->addChoiceForm("modelList", "Select mode", vec2(0.0f), _modelNames);
			for (auto& name : _modelNames) { name = "@" + name; }
		}
		else if (screen->getButton("deleteModel")->isHovered()) // Delete model button
		{
			_modelChoosingEnabled = true;
			_modelRemovalEnabled = true;
			for (auto& name : _modelNames) { name = name.substr(1, name.size()); }
			_gui->getGlobalScreen()->addChoiceForm("modelList", "Select mode", vec2(0.0f), _modelNames);
			for (auto& name : _modelNames) { name = "@" + name; }
		}
		else if (screen->getButton("back")->isHovered()) // Back button
		{
			_gui->getGlobalScreen()->addAnswerForm("exitModelEditor", "Save changes?", vec2(0.0f, 0.25f));
		}
	}

	// Check if user wants to save changes
	if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitModelEditor"))
	{
		save();
		_window->setActiveScreen("main");
		unload();
	}
	else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitModelEditor"))
	{
		_window->setActiveScreen("main");
		unload();
	}
}

void ModelEditor::_updateModelCreation()
{
	if (_modelCreationEnabled)
	{
		string newModelName;

		// Create new model
		if (_gui->getGlobalScreen()->checkValueForm("newModelName", newModelName))
		{
			// Add model
			_addModel("@" + newModelName, "", "", "", "", vec3(0.0f), 0, 1, 0, 0, vec3(1.0f), 1.0f, vec3(1.0f));

			// Go to editor screen
			_currentModelName = newModelName;
			_modelCreationEnabled = false;
			_modelEditingEnabled = true;
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelEditingMain");
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	if (_modelChoosingEnabled)
	{
		string clickedButtonID = _gui->getGlobalScreen()->getClickedChoiceFormButtonID("modelList");

		if (clickedButtonID != "")
		{
			_currentModelName = "@" + clickedButtonID;
			_modelChoosingEnabled = false;
		}
		else
		{
			if (_gui->getGlobalScreen()->isChoiceFormCancelled("modelList"))
			{
				_modelChoosingEnabled = false;
				_modelEditingEnabled = false;
				_modelRemovalEnabled = false;
				_gui->getGlobalScreen()->removeChoiceForm("modelList");
			}
		}
	}
}

void ModelEditor::_updateModelRemoval()
{
	if (_modelRemovalEnabled && _currentModelName != "")
	{
		_gui->getGlobalScreen()->addAnswerForm("removeModel", "Are you sure?", vec2(0.0f));

		if (_gui->getGlobalScreen()->isAnswerFormConfirmed("removeModel"))
		{
			if (_fe3d.gameEntity_isExisting(_currentModelName))
			{
				_fe3d.gameEntity_delete(_currentModelName);
			}

			_modelNames.erase(std::remove(_modelNames.begin(), _modelNames.end(), _currentModelName), _modelNames.end());
			_modelRemovalEnabled = false;
			_currentModelName = "";
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("removeModel"))
		{
			_modelChoosingEnabled = true;
			_currentModelName = "";
		}
	}
}

void ModelEditor::_updateModelEditingCamera()
{
	// Update cursor difference
	static vec2 totalCursorDifference = vec2(0.0f);
	static vec2 cameraAcceleration = vec2(0.0f);
	static vec2 lastCursorPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());
	vec2 cursorPosition = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());
	vec2 cursorDifference = cursorPosition - lastCursorPos;
	lastCursorPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());

	// Update scrolling
	static float scollSpeed = 0.0f;
	if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport()) // No GUI focus and cursor must be within viewport
	{
		if (!_meshResizingToggled && !_boxResizingToggled) // No active resizing
		{
			scollSpeed += float(-_fe3d.input_getMouseWheelY() / _scrollWheelDivider); // Add scroll speed
		}
	}
	scollSpeed *= 0.975f; // Slowing down
	scollSpeed = std::clamp(scollSpeed, -1.0f, 1.0f);
	_cameraDistance += scollSpeed;
	_cameraDistance = std::clamp(_cameraDistance, _minCameraDistance, _maxCameraDistance);

	// Check if MMB pressed
	if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport())
	{
		if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_MIDDLE))
		{
			if (_fe3d.misc_isMouseInsideViewport()) // Only if cursor inside 3d screen
			{
				cameraAcceleration.x += cursorDifference.x * _cameraSpeed;
				cameraAcceleration.y += cursorDifference.y * _cameraSpeed;
			}
		}
	}

	// Calculate cursor moving speed
	cameraAcceleration *= 0.975f;
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
		_fe3d.gfx_enableShadows(vec3(distance), vec3(0.0f), distance * 2.0f, distance * 3.0f);
	}
}