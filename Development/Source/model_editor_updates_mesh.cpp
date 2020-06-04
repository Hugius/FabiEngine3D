#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateModelEditing()
{
	if (_modelEditingEnabled && _currentModelName != "")
	{
		static bool firstTime = true;
		auto screen = _window->getScreen("modelEditingMain");

		if (firstTime)
		{
			firstTime = false;
			_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID(), "Model: " + _currentModelName, 0.025f);
			_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID());
			_window->setActiveScreen("modelEditingMain");
		}
		
		// GUI management
		if (_window->getActiveScreen()->getID() == "modelEditingMain")
		{
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

					firstTime = true;
					_modelEditingEnabled = false;
					_currentModelName = "";
					_window->setActiveScreen("modelManagement");
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
			screen->getButton("options")->setHoverable(hoverable);
			screen->getButton("size")->setHoverable(hoverable);
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

		// Update camera
		_updateModelEditingCamera();
	}
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

	// Check if OBJ exists
	bool existing = _fe3d.gameEntity_isExisting(_currentModelName);
	bool hoverable = false;
	if (existing)
	{
		hoverable = existing && !_fe3d.gameEntity_isMultiTextured(_currentModelName);
	}

	// Editing buttons hoverability
	screen->getButton("loadDiffuseMap")->setHoverable(hoverable);
	screen->getButton("loadLightMap")->setHoverable(hoverable);
	screen->getButton("loadReflectionMap")->setHoverable(hoverable);
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
			scollSpeed += float(-_fe3d.input_getMouseWheelY() / _scrollWheelDivider);
		}
		scollSpeed *= 0.975f;
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
}