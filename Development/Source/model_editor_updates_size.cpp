#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingSize()
{
	auto screen = _leftWindow->getScreen("modelEditorMenuSize");
	vec3 currentSize = _fe3d.gameEntity_getSize(_currentModelName);
	
	// GUI management 
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("setSize")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("sizeX", "X", currentSize.x * 100.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
			_gui->getGlobalScreen()->addValueForm("sizeY", "Y", currentSize.y * 100.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
			_gui->getGlobalScreen()->addValueForm("sizeZ", "Z", currentSize.z * 100.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("toggleResizeMesh")->isHovered())
		{
			_meshResizingToggled = !_meshResizingToggled;

			// Toggle resize
			string newContent = _meshResizingToggled ? "Mesh resize: ON" : "Mesh resize: OFF";
			_fe3d.textEntity_setTextContent(screen->getButton("toggleResizeMesh")->getTextfield()->getEntityID(), newContent);
		}
		else if (screen->getButton("toggleBoxView")->isHovered())
		{
			_aabbRenderingEnabled = !_aabbRenderingEnabled;

			// Toggle view
			_aabbRenderingEnabled ? _fe3d.misc_enableAabbFrameRendering() : _fe3d.misc_disableAabbFrameRendering();
			_aabbRenderingEnabled ? _fe3d.aabbEntity_show(_currentModelName) : _fe3d.aabbEntity_hide(_currentModelName);
			string newContent = _aabbRenderingEnabled ? "Hitbox: ON" : "Hitbox: OFF";
			_fe3d.textEntity_setTextContent(screen->getButton("toggleBoxView")->getTextfield()->getEntityID(), newContent);
		}
		else if (screen->getButton("toggleResizeBox")->isHovered())
		{
			_boxResizingToggled = !_boxResizingToggled;

			// Toggle box resize
			string newContent = _boxResizingToggled ? "Box resize: ON" : "Box resize: OFF";
			_fe3d.textEntity_setTextContent(screen->getButton("toggleResizeBox")->getTextfield()->getEntityID(), newContent);
		}
		else if (screen->getButton("resizeBoxDir")->isHovered())
		{
			// Change resize direction
			string directions[3] = { "X", "Y", "Z" };
			_modelResizeDirection = (_modelResizeDirection == Direction::X) ? Direction::Y : (_modelResizeDirection == Direction::Y) ? Direction::Z : Direction::X;
			string newContent = "Direction: " + directions[int(_modelResizeDirection)];
			_fe3d.textEntity_setTextContent(screen->getButton("resizeBoxDir")->getTextfield()->getEntityID(), newContent);
		}
		else if (screen->getButton("back")->isHovered())
		{
			_meshResizingToggled = false;
			_aabbRenderingEnabled = false;
			_boxResizingToggled = false;
			_fe3d.aabbEntity_hide(_currentModelName);
			_fe3d.textEntity_setTextContent(screen->getButton("toggleResizeMesh")->getTextfield()->getEntityID(), "Mesh resize: OFF");
			_fe3d.textEntity_setTextContent(screen->getButton("toggleResizeBox")->getTextfield()->getEntityID(), "Box resize: OFF");
			_fe3d.textEntity_setTextContent(screen->getButton("toggleBoxView")->getTextfield()->getEntityID(), "Hitbox: OFF");
			_fe3d.misc_disableAabbFrameRendering();
			_leftWindow->setActiveScreen("modelEditorMenuChoice");
		}
	}

	// Update AABB resizing through cursor
	if (_boxResizingToggled)
	{
		float scrollSpeed = float(_fe3d.input_getMouseWheelY()) * 0.05f;
		vec3 newSize = _fe3d.aabbEntity_getSize(_currentModelName);

		switch (_modelResizeDirection)
		{
		case Direction::X:
			newSize.x *= (1.0f + scrollSpeed);
			break;

		case Direction::Y:
			newSize.y *= (1.0f + scrollSpeed);
			break;

		case Direction::Z:
			newSize.z *= (1.0f + scrollSpeed);
			break;
		}

		// Apply new size
		_fe3d.aabbEntity_setSize(_currentModelName, newSize);
	}

	// Update model resizing through cursor
	if (_meshResizingToggled)
	{
		float scrollSpeed = float(_fe3d.input_getMouseWheelY()) * 0.05f;
		_fe3d.gameEntity_setSize(_currentModelName, _fe3d.gameEntity_getSize(_currentModelName) * vec3(1.0f + scrollSpeed));
	}

	// Update model size X
	if (_gui->getGlobalScreen()->checkValueForm("sizeX", currentSize.x))
	{
		currentSize.x /= 100.0f;
		_fe3d.gameEntity_setSize(_currentModelName, currentSize);
	}

	// Update model size Y
	if (_gui->getGlobalScreen()->checkValueForm("sizeY", currentSize.y))
	{
		currentSize.y /= 100.0f;
		_fe3d.gameEntity_setSize(_currentModelName, currentSize);
	}

	// Update model size Z
	if (_gui->getGlobalScreen()->checkValueForm("sizeZ", currentSize.z))
	{
		currentSize.z /= 100.0f;
		_fe3d.gameEntity_setSize(_currentModelName, currentSize);
	}
}