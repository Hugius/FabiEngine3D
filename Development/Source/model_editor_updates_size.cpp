#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateSizeMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "modelEditorMenuSize")
	{
		// Temporary values
		const string directions[3] = { "X", "Y", "Z" };
		auto size = _fe3d.modelEntity_getSize(_currentModelID, "");

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_isResizingToggled = false;
			_transformationDirection = Direction::X;
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("sizeX", "X", (size.x * 100.0f), Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("sizeY", "Y", (size.y * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("sizeZ", "Z", (size.z * 100.0f), Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("toggleResize")->isHovered())
		{
			_isResizingToggled = !_isResizingToggled;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("direction")->isHovered())
		{
			if (_transformationDirection == Direction::X)
			{
				_transformationDirection = Direction::Y;
			}
			else if (_transformationDirection == Direction::Y)
			{
				_transformationDirection = Direction::Z;
			}
			else
			{
				_transformationDirection = Direction::X;
			}
		}

		// Update resizing through cursor
		if (_isResizingToggled)
		{
			// Temporary values
			float scrollSpeed = static_cast<float>(_fe3d.input_getMouseWheelY()) * 0.05f;

			// Check if user scrolled
			if (scrollSpeed != 0.0f)
			{
				// Check if able to scroll
				if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
				{
					switch (_transformationDirection)
					{
					case Direction::X:
					{
						size.x *= (1.0f + scrollSpeed);
						break;
					}

					case Direction::Y:
					{
						size.y *= (1.0f + scrollSpeed);
						break;
					}

					case Direction::Z:
					{
						size.z *= (1.0f + scrollSpeed);
						break;
					}
					}
				}

				// Apply new size
				_fe3d.modelEntity_setSize(_currentModelID, "", size);
			}
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("sizeX", size.x))
		{
			size.x /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, "", size);
		}
		if (_gui.getGlobalScreen()->checkValueForm("sizeY", size.y))
		{
			size.y /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, "", size);
		}
		if (_gui.getGlobalScreen()->checkValueForm("sizeZ", size.z))
		{
			size.z /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, "", size);
		}

		// Update button text contents
		screen->getButton("toggleResize")->changeTextContent(_isResizingToggled ? "Resize: ON" : "Resize: OFF");
		screen->getButton("direction")->changeTextContent("Direction: " + directions[static_cast<int>(_transformationDirection)]);
	}
}