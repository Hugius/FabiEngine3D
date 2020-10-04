#include "model_editor.hpp"

void ModelEditor::_updateModelEditingAabb()
{
	auto screen = _gui->getViewport("left")->getWindow("main")->getScreen("modelEditorMenuAabb");
	vec3 currentSize = _fe3d.gameEntity_getSize(_currentModelID);

	// Buttons hoverability
	bool isHoverable = (_currentAabbID != "");
	screen->getButton("delete")->setHoverable(isHoverable);
	screen->getButton("toggleMove")->setHoverable(isHoverable);
	screen->getButton("toggleResize")->setHoverable(isHoverable);
	screen->getButton("direction")->setHoverable(isHoverable);

	// GUI management 
	if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("add")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("newAabbName", "New AABB name", "", vec2(0.0f), vec2(0.5f, 0.1f));
		}
		else if (screen->getButton("edit")->isHovered())
		{
			// Retrieve all AABB names of this model
			vector<string> aabbNames = _fe3d.aabbEntity_getBoundIDs(_currentModelID, true, false);
			for (auto& name : aabbNames)
			{
				name = name.substr(string(_currentModelID + "_").size());
			}

			// Show choicelist
			_gui->getGlobalScreen()->addChoiceForm("aabbList", "Select AABB", vec2(-0.4f, 0.1f), aabbNames);
		}
		else if (screen->getButton("delete")->isHovered())
		{
			_movingToggled = false;
			_resizingToggled = false;
			_direction = TransformationDirection::X;
			_fe3d.aabbEntity_delete(_currentModelID + "_" + _currentAabbID);
			_currentAabbID = "";
			_fe3d.textEntity_hide(_gui->getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
		}
		else if (screen->getButton("toggleMove")->isHovered())
		{
			_movingToggled = !_movingToggled;

			// Toggle box move
			string newContent = _resizingToggled ? "Box move: ON" : "Box move: OFF";
			_fe3d.textEntity_setTextContent(screen->getButton("toggleMove")->getTextfield()->getEntityID(), newContent);
		}
		else if (screen->getButton("toggleResize")->isHovered())
		{
			_resizingToggled = !_resizingToggled;

			// Toggle box resize
			string newContent = _resizingToggled ? "Box resize: ON" : "Box resize: OFF";
			_fe3d.textEntity_setTextContent(screen->getButton("toggleResize")->getTextfield()->getEntityID(), newContent);
		}
		else if (screen->getButton("direction")->isHovered())
		{
			// Change direction
			_direction = (_direction == TransformationDirection::X) ? TransformationDirection::Y : (_direction == TransformationDirection::Y) ? TransformationDirection::Z : TransformationDirection::X;
		}
		else if (screen->getButton("back")->isHovered())
		{
			_movingToggled = false;
			_resizingToggled = false;
			_direction = TransformationDirection::X;
			_currentAabbID = "";
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			_fe3d.misc_disableAabbFrameRendering();
			_fe3d.textEntity_hide(_gui->getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
		}
	}

	// Update AABB visibility
	for (auto& entityID : _fe3d.aabbEntity_getAllIDs())
	{
		if (entityID == _currentModelID + "_" + _currentAabbID)
		{
			_fe3d.aabbEntity_show(entityID);
		}
		else
		{
			_fe3d.aabbEntity_hide(entityID);
		}
	}

	// Update button contents
	string directions[3] = { "X", "Y", "Z" };
	string newContent = "Direction: " + directions[int(_direction)];
	_fe3d.textEntity_setTextContent(screen->getButton("direction")->getTextfield()->getEntityID(), newContent);
	_fe3d.textEntity_setTextContent(screen->getButton("toggleMove")->getTextfield()->getEntityID(), _movingToggled ? "Box move: ON" : "Box move: OFF");
	_fe3d.textEntity_setTextContent(screen->getButton("toggleResize")->getTextfield()->getEntityID(), _resizingToggled ? "Box resize: ON" : "Box resize: OFF");

	// Create AABB
	string newName;
	if (_gui->getGlobalScreen()->checkValueForm("newAabbName", newName, {}))
	{
		if (_fe3d.aabbEntity_isExisting(_currentModelID + "_" + newName)) // Check if already exists
		{
			_fe3d.logger_throwWarning("New AABB \"" + newName + "\" of model \"" + _currentModelID.substr(1) + "\" already exists!");
		}
		else
		{
			// Add new AABB
			_fe3d.aabbEntity_bindToGameEntity(_currentModelID, vec3(0.0f), vec3(1.0f), true, _currentModelID + "_" + newName);
			_currentAabbID = newName;

			// Reset editing
			_movingToggled = false;
			_resizingToggled = false;
			_direction = TransformationDirection::X;

			// Show AABB title
			_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID(),
				"AABB: " + _currentAabbID, 0.025f);
		}
	}

	// Choose AABB
	if (_gui->getGlobalScreen()->isChoiceFormExisting("aabbList"))
	{
		string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("aabbList");
		string hoveredAabbID = "";

		// Hide every AABB
		for (auto& entityID : _fe3d.aabbEntity_getAllIDs())
		{
			_fe3d.aabbEntity_hide(entityID);
		}

		if (selectedButtonID != "") // Hovered
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // Clicked
			{
				// Set current AABB
				_currentAabbID = selectedButtonID;

				// Reset editing
				_movingToggled = false;
				_resizingToggled = false;
				_direction = TransformationDirection::X;

				// Show AABB title
				_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID(),
					"AABB: " + _currentAabbID, 0.025f);
				_gui->getGlobalScreen()->removeChoiceForm("aabbList");
			}
			else
			{
				hoveredAabbID = selectedButtonID;
			}
		}
		else if (_gui->getGlobalScreen()->isChoiceFormCancelled("aabbList")) // Cancelled choosing
		{
			_gui->getGlobalScreen()->removeChoiceForm("aabbList");
		}

		// Show hovered AABB
		if (hoveredAabbID != "")
		{
			_fe3d.aabbEntity_show(_currentModelID + "_" + hoveredAabbID);
		}
	}

	// Check if currently editing an AABB
	if (_currentAabbID != "")
	{
		// Update moving through cursor
		if (_movingToggled)
		{
			vec3 newPosition = _fe3d.aabbEntity_getPosition(_currentModelID + "_" + _currentAabbID);

			// Update scrolling
			float scrollSpeed = float(_fe3d.input_getMouseWheelY()) * 0.05f;

			switch (_direction)
			{
				case TransformationDirection::X:
					if (newPosition.x == 0.0f)
					{
						newPosition.x += scrollSpeed;
					}
					else
					{
						newPosition.x *= 1.0f + scrollSpeed;
					}
					break;

				case TransformationDirection::Y:
					if (newPosition.y == 0.0f)
					{
						newPosition.y += scrollSpeed;
					}
					else
					{
						newPosition.y *= 1.0f + scrollSpeed;
					}
					break;

				case TransformationDirection::Z:
					if (newPosition.z == 0.0f)
					{
						newPosition.z += scrollSpeed;
					}
					else
					{
						newPosition.z *= 1.0f + scrollSpeed;
					}
					break;
			}

			// Apply new size
			_fe3d.aabbEntity_setPosition(_currentModelID + "_" + _currentAabbID, newPosition);
		}

		// Update resizing through cursor
		if (_resizingToggled)
		{
			float scrollSpeed = float(_fe3d.input_getMouseWheelY()) * 0.05f;
			vec3 newSize = _fe3d.aabbEntity_getSize(_currentModelID + "_" + _currentAabbID);

			switch (_direction)
			{
				case TransformationDirection::X:
					newSize.x *= (1.0f + scrollSpeed);
					break;

				case TransformationDirection::Y:
					newSize.y *= (1.0f + scrollSpeed);
					break;

				case TransformationDirection::Z:
					newSize.z *= (1.0f + scrollSpeed);
					break;
			}

			// Apply new size
			_fe3d.aabbEntity_setSize(_currentModelID + "_" + _currentAabbID, newSize);
		}
	}
}