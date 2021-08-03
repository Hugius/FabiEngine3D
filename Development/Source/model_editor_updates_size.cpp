#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateSizeMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();
	
	// GUI management
	if (screen->getID() == "modelEditorMenuSize")
	{
		// Temporary values
		const string directions[3] = { "X", "Y", "Z" };
		Vec3 currentSize = _fe3d.modelEntity_getSize(_currentModelID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_isResizingToggled = false;
				_transformationDirection = Direction::X;
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("sizeX", "X", currentSize.x * 100.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("sizeY", "Y", currentSize.y * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("sizeZ", "Z", currentSize.z * 100.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("toggleResize")->isHovered())
			{
				_isResizingToggled = !_isResizingToggled;
			}
			else if (screen->getButton("direction")->isHovered())
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
		}

		// Update resizing through cursor
		if (_isResizingToggled)
		{
			// Temporary values
			float scrollSpeed = static_cast<float>(_fe3d.input_getMouseWheelY()) * 0.05f;
			Vec3 newSize = _fe3d.modelEntity_getSize(_currentModelID);

			// Check if able to scroll
			if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
			{
				switch (_transformationDirection)
				{
					case Direction::X:
					{
						newSize.x *= (1.0f + scrollSpeed);
						break;
					}

					case Direction::Y:
					{
						newSize.y *= (1.0f + scrollSpeed);
						break;
					}

					case Direction::Z:
					{
						newSize.z *= (1.0f + scrollSpeed);
						break;
					}
				}
			}

			// Apply new size
			_fe3d.modelEntity_setSize(_currentModelID, newSize);
		}

		// Update size X
		if (_gui.getGlobalScreen()->checkValueForm("sizeX", currentSize.x))
		{
			currentSize.x /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, currentSize);
		}

		// Update size Y
		if (_gui.getGlobalScreen()->checkValueForm("sizeY", currentSize.y))
		{
			currentSize.y /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, currentSize);
		}

		// Update size Z
		if (_gui.getGlobalScreen()->checkValueForm("sizeZ", currentSize.z))
		{
			currentSize.z /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, currentSize);
		}

		// Button text contents
		screen->getButton("toggleResize")->changeTextContent(_isResizingToggled ? "Resize: ON" : "Resize: OFF");
		screen->getButton("direction")->changeTextContent("Direction: " + directions[static_cast<int>(_transformationDirection)]);
	}
}