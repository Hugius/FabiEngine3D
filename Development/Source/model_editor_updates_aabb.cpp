#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void ModelEditor::_updateAabbMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuAabb")
	{
		// Temporary values
		const string directions[3] = { "X", "Y", "Z" };
		Vec3 currentSize = _fe3d.modelEntity_getSize(_currentModelID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_isMovingToggled = false;
				_isResizingToggled = false;
				_transformationDirection = Direction::X;
				_currentAabbID = "";
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
				_fe3d.misc_disableAabbFrameRendering();
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAabbID")->getEntityID(), false);
				return;
			}
			else if (screen->getButton("add")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("aabbCreate", "Create AABB", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				// Retrieve all AABB names of this model
				vector<string> IDs = _fe3d.aabbEntity_getBoundIDs(_currentModelID, true, false);
				for (auto& ID : IDs)
				{
					ID = ID.substr(string(_currentModelID + "@").size());
				}
				sort(IDs.begin(), IDs.end());

				// Show choicelist
				_gui.getGlobalScreen()->createChoiceForm("aabbList", "Edit AABB", Vec2(-0.5f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_isMovingToggled = false;
				_isResizingToggled = false;
				_transformationDirection = Direction::X;
				_fe3d.aabbEntity_delete(_currentModelID + "@" + _currentAabbID);
				_currentAabbID = "";
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAabbID")->getEntityID(), false);
			}
			else if (screen->getButton("speed")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("speed", "Transformation Speed", _aabbTransformationSpeed * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("toggleMove")->isHovered())
			{
				_isMovingToggled = !_isMovingToggled;
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

		// Button hoverabilities
		screen->getButton("delete")->setHoverable(_currentAabbID != "");
		screen->getButton("toggleMove")->setHoverable(_currentAabbID != "");
		screen->getButton("toggleResize")->setHoverable(_currentAabbID != "");
		screen->getButton("direction")->setHoverable(_currentAabbID != "");

		// Button text contents
		screen->getButton("direction")->changeTextContent("Direction: " + directions[static_cast<int>(_transformationDirection)]);
		screen->getButton("toggleMove")->changeTextContent(_isMovingToggled ? "Move: ON" : "Move: OFF");
		screen->getButton("toggleResize")->changeTextContent(_isResizingToggled ? "Resize: ON" : "Resize: OFF");

		// Update AABB visibility
		for (const auto& entityID : _fe3d.aabbEntity_getAllIDs())
		{
			if (entityID == (_currentModelID + "@" + _currentAabbID))
			{
				_fe3d.aabbEntity_setVisible(entityID, true);
			}
			else
			{
				_fe3d.aabbEntity_setVisible(entityID, false);
			}
		}

		// Filling transformation speed
		if (_gui.getGlobalScreen()->checkValueForm("speed", _aabbTransformationSpeed, { }))
		{
			_aabbTransformationSpeed /= 100.0f;
		}

		// Create AABB
		string newAabbID;
		if (_gui.getGlobalScreen()->checkValueForm("aabbCreate", newAabbID, {}))
		{
			if (_fe3d.aabbEntity_isExisting(_currentModelID + "@" + newAabbID)) // Check if already exists
			{
				Logger::throwWarning("AABB ID \"" + newAabbID + "\" of model with ID \"" + _currentModelID.substr(1) + "\" already exists!");
			}
			else
			{
				// @ sign not allowed
				if (newAabbID.find('@') == string::npos)
				{
					// Spaces not allowed
					if (newAabbID.find(' ') == string::npos)
					{
						// Bind AABB
						_fe3d.aabbEntity_create(_currentModelID + "@" + newAabbID);
						_fe3d.aabbEntity_bindToModelEntity((_currentModelID + "@" + newAabbID), _currentModelID);
						_currentAabbID = newAabbID;

						// Reset editing
						_isMovingToggled = false;
						_isResizingToggled = false;
						_transformationDirection = Direction::X;

						// Show AABB title
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedAabbID")->getEntityID(),
							"AABB: " + _currentAabbID, 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAabbID")->getEntityID(), true);
					}
					else
					{
						Logger::throwWarning("AABB ID cannot contain any spaces!");
					}
				}
				else
				{
					Logger::throwWarning("AABB ID cannot contain '@'!");
				}
			}
		}

		// Choose AABB
		if (_gui.getGlobalScreen()->isChoiceFormExisting("aabbList"))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("aabbList");
			string hoveredAabbID = "";

			// Hide every AABB
			for (const auto& entityID : _fe3d.aabbEntity_getAllIDs())
			{
				_fe3d.aabbEntity_setVisible(entityID, false);
			}

			// Check if a AABB ID is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // Clicked
				{
					// Set current AABB
					_currentAabbID = selectedButtonID;

					// Reset editing
					_isMovingToggled = false;
					_isResizingToggled = false;
					_transformationDirection = Direction::X;

					// Show AABB title
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedAabbID")->getEntityID(),
						"AABB: " + _currentAabbID, 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAabbID")->getEntityID(), true);
					_gui.getGlobalScreen()->deleteChoiceForm("aabbList");
				}
				else
				{
					hoveredAabbID = selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("aabbList")) // Cancelled choosing
			{
				_gui.getGlobalScreen()->deleteChoiceForm("aabbList");
			}

			// Show hovered AABB
			if (hoveredAabbID != "")
			{
				_fe3d.aabbEntity_setVisible(_currentModelID + "@" + hoveredAabbID, true);
			}
		}

		// Check if currently editing an AABB
		if (_currentAabbID != "" && !_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Update moving through cursor
			if (_isMovingToggled)
			{
				float scrollingDirection = static_cast<float>(_fe3d.input_getMouseWheelY());
				Vec3 newPosition = _fe3d.aabbEntity_getPosition(_currentModelID + "@" + _currentAabbID);

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
				_fe3d.aabbEntity_setPosition(_currentModelID + "@" + _currentAabbID, newPosition);
			}

			// Update resizing through cursor
			if (_isResizingToggled)
			{
				float scrollingDirection = static_cast<float>(_fe3d.input_getMouseWheelY());
				Vec3 newSize = _fe3d.aabbEntity_getSize(_currentModelID + "@" + _currentAabbID);

				// Check if able to scroll
				if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
				{
					switch (_transformationDirection)
					{
					case Direction::X:
					{
						newSize.x += (_aabbTransformationSpeed * scrollingDirection);
						break;
					}

					case Direction::Y:
					{
						newSize.y += (_aabbTransformationSpeed * scrollingDirection);
						break;
					}

					case Direction::Z:
					{
						newSize.z += (_aabbTransformationSpeed * scrollingDirection);
						break;
					}
					}
				}

				// Apply new size
				_fe3d.aabbEntity_setSize(_currentModelID + "@" + _currentAabbID, newSize);
			}
		}
	}
}