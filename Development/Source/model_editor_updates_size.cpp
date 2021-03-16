#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingSize()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();
	
	if (screen->getID() == "modelEditorMenuSize")
	{
		// Temporary values
		Vec3 currentSize = _fe3d.gameEntity_getSize(_currentModelID);

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_resizingToggled = false;
				_transformationDirection = Direction::X;
				_fe3d.textEntity_setTextContent(screen->getButton("toggleResize")->getTextfield()->getEntityID(), "Mesh resize: OFF");
				_fe3d.textEntity_setTextContent(screen->getButton("direction")->getTextfield()->getEntityID(), "Direction: X");
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("sizeX", "X", currentSize.x * 100.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("sizeY", "Y", currentSize.y * 100.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("sizeZ", "Z", currentSize.z * 100.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("toggleResize")->isHovered())
			{
				_resizingToggled = !_resizingToggled;

				// Toggle resize
				string newContent = _resizingToggled ? "Mesh resize: ON" : "Mesh resize: OFF";
				_fe3d.textEntity_setTextContent(screen->getButton("toggleResize")->getTextfield()->getEntityID(), newContent);
			}
			else if (screen->getButton("direction")->isHovered())
			{
				// Change resize direction
				string directions[3] = { "X", "Y", "Z" };
				_transformationDirection = (_transformationDirection == Direction::X) ? Direction::Y :
					(_transformationDirection == Direction::Y) ? Direction::Z : Direction::X;
				string newContent = "Direction: " + directions[int(_transformationDirection)];
				_fe3d.textEntity_setTextContent(screen->getButton("direction")->getTextfield()->getEntityID(), newContent);
			}
		}

		// Update resizing through cursor
		if (_resizingToggled)
		{
			float scrollSpeed = float(_fe3d.input_getMouseWheelY()) * 0.05f;
			Vec3 newSize = _fe3d.gameEntity_getSize(_currentModelID);

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
			_fe3d.gameEntity_setSize(_currentModelID, newSize);
		}

		// Update size X
		if (_gui.getGlobalScreen()->checkValueForm("sizeX", currentSize.x))
		{
			currentSize.x /= 100.0f;
			_fe3d.gameEntity_setSize(_currentModelID, currentSize);
		}

		// Update size Y
		if (_gui.getGlobalScreen()->checkValueForm("sizeY", currentSize.y))
		{
			currentSize.y /= 100.0f;
			_fe3d.gameEntity_setSize(_currentModelID, currentSize);
		}

		// Update size Z
		if (_gui.getGlobalScreen()->checkValueForm("sizeZ", currentSize.z))
		{
			currentSize.z /= 100.0f;
			_fe3d.gameEntity_setSize(_currentModelID, currentSize);
		}
	}
}