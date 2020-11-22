#include "model_editor.hpp"

void ModelEditor::_updateModelEditingAabb()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();
	Vec3 currentSize = _fe3d.gameEntity_getSize(_currentModelID);

	// GUI management
	if(screen->getID() == "modelEditorMenuAabb")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_movingToggled = false;
				_resizingToggled = false;
				_transformationDirection = Direction::X;
				_currentAabbID = "";
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
				_fe3d.misc_disableAabbFrameRendering();
				_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
			}
			else if (screen->getButton("add")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("newAabbName", "New AABB name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
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
				_gui.getGlobalScreen()->addChoiceForm("aabbList", "Select AABB", Vec2(-0.4f, 0.1f), aabbNames);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_movingToggled = false;
				_resizingToggled = false;
				_transformationDirection = Direction::X;
				_fe3d.aabbEntity_delete(_currentModelID + "_" + _currentAabbID);
				_currentAabbID = "";
				_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
			}
			else if (screen->getButton("speed")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("speed", "Transformation speed", _aabbTransformationSpeed * 100.0f, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
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
				_transformationDirection = (_transformationDirection == Direction::X) ? Direction::Y :
					(_transformationDirection == Direction::Y) ? Direction::Z : Direction::X;
			}
		}
	}

	// Buttons hoverability
	bool isHoverable = (_currentAabbID != "");
	screen->getButton("delete")->setHoverable(isHoverable);
	screen->getButton("toggleMove")->setHoverable(isHoverable);
	screen->getButton("toggleResize")->setHoverable(isHoverable);
	screen->getButton("direction")->setHoverable(isHoverable);

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
	string newContent = "Direction: " + directions[int(_transformationDirection)];
	_fe3d.textEntity_setTextContent(screen->getButton("direction")->getTextfield()->getEntityID(), newContent);
	_fe3d.textEntity_setTextContent(screen->getButton("toggleMove")->getTextfield()->getEntityID(), _movingToggled ? "Box move: ON" : "Box move: OFF");
	_fe3d.textEntity_setTextContent(screen->getButton("toggleResize")->getTextfield()->getEntityID(), _resizingToggled ? "Box resize: ON" : "Box resize: OFF");

	// Filling transformation speed
	if (_gui.getGlobalScreen()->checkValueForm("speed", _aabbTransformationSpeed, { }))
	{
		_aabbTransformationSpeed /= 100.0f;
	}

	// Create AABB
	string newName;
	if (_gui.getGlobalScreen()->checkValueForm("newAabbName", newName, {}))
	{
		if (_fe3d.aabbEntity_isExisting(_currentModelID + "_" + newName)) // Check if already exists
		{
			_fe3d.logger_throwWarning("New AABB \"" + newName + "\" of model \"" + _currentModelID.substr(1) + "\" already exists!");
		}
		else
		{
			// Add new AABB
			_fe3d.aabbEntity_bindToGameEntity(_currentModelID, Vec3(0.0f), Vec3(1.0f), true, _currentModelID + "_" + newName);
			_currentAabbID = newName;

			// Reset editing
			_movingToggled = false;
			_resizingToggled = false;
			_transformationDirection = Direction::X;

			// Show AABB title
			_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID(),
				"AABB: " + _currentAabbID, 0.025f);
			_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
		}
	}

	// Choose AABB
	if (_gui.getGlobalScreen()->isChoiceFormExisting("aabbList"))
	{
		string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("aabbList");
		string hoveredAabbID = "";

		// Hide every AABB
		for (auto& entityID : _fe3d.aabbEntity_getAllIDs())
		{
			_fe3d.aabbEntity_hide(entityID);
		}

		// Check if a AABB name is hovered
		if (selectedButtonID != "")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // Clicked
			{
				// Set current AABB
				_currentAabbID = selectedButtonID;

				// Reset editing
				_movingToggled = false;
				_resizingToggled = false;
				_transformationDirection = Direction::X;

				// Show AABB title
				_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID(),
					"AABB: " + _currentAabbID, 0.025f);
				_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
				_gui.getGlobalScreen()->removeChoiceForm("aabbList");
			}
			else
			{
				hoveredAabbID = selectedButtonID;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("aabbList")) // Cancelled choosing
		{
			_gui.getGlobalScreen()->removeChoiceForm("aabbList");
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
			float scrollingDirection = float(_fe3d.input_getMouseWheelY());
			Vec3 newPosition = _fe3d.aabbEntity_getPosition(_currentModelID + "_" + _currentAabbID);

			// Determine direction
			switch (_transformationDirection)
			{
				case Direction::X:
					newPosition.x += _aabbTransformationSpeed * scrollingDirection;
					break;

				case Direction::Y:
					newPosition.y += _aabbTransformationSpeed * scrollingDirection;
					break;

				case Direction::Z:
					newPosition.z += _aabbTransformationSpeed * scrollingDirection;
					break;
			}

			// Apply new size
			_fe3d.aabbEntity_setPosition(_currentModelID + "_" + _currentAabbID, newPosition);
		}

		// Update resizing through cursor
		if (_resizingToggled)
		{
			float scrollingDirection = float(_fe3d.input_getMouseWheelY());
			Vec3 newSize = _fe3d.aabbEntity_getSize(_currentModelID + "_" + _currentAabbID);

			switch (_transformationDirection)
			{
				case Direction::X:
					newSize.x += (_aabbTransformationSpeed * scrollingDirection);
					break;

				case Direction::Y:
					newSize.y += (_aabbTransformationSpeed * scrollingDirection);
					break;

				case Direction::Z:
					newSize.z += (_aabbTransformationSpeed * scrollingDirection);
					break;
			}

			// Apply new size
			_fe3d.aabbEntity_setSize(_currentModelID + "_" + _currentAabbID, newSize);
		}
	}
}