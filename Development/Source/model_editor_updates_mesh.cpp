#include <algorithm>

#include "model_editor.hpp"

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
		else if (_window->getActiveScreen()->getID() == "modelEditingSize")
		{
			_updateModelEditingSize();
		}
	}

	// Update camera
	_updateModelEditingCamera();
}

void ModelEditor::_updateModelEditingCamera()
{
	// Check if the GUI is not focused
	if (!_gui->getGlobalScreen()->isFocused())
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
		if (_fe3d.misc_isMouseInsideViewport() && !_meshResizingToggled && !_boxResizingToggled) // Only if cursor inside 3d screen and not resizing
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
			_fe3d.gfx_enableShadows(vec3(distance), vec3(0.0f), distance * 2.0f, distance * 3.0f);
		}
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
		else if (screen->getButton("size")->isHovered())
		{
			if (_fe3d.gameEntity_isExisting(_currentModelName))
			{
				_window->setActiveScreen("modelEditingSize");
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