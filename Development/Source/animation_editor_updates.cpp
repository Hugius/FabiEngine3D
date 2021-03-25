#include "animation_editor.hpp"

#include <algorithm>

void AnimationEditor::update()
{
	_updateAnimationExecution();
	_updateManagementScreen();
	_updateAnimationCreation();
	_updateAnimationChoice();
	_updateEditingScreen();
	_updateFrameScreen();
	_updateAnimationRemoval();
	_updateCamera();
	_updateMiscellaneous();
}

void AnimationEditor::_updateManagementScreen()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();
		
		// GUI management
		if (screen->getID() == "animationEditorMenuMain")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getGlobalScreen()->addAnswerForm("exitAnimationEditor", "Save changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("addAnimation")->isHovered()) // Add animation button
				{
					_gui.getGlobalScreen()->addValueForm("newAnimationName", "New animation name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
					_isCreatingAnimation = true;
				}
				else if (screen->getButton("editAnimation")->isHovered()) // Edit animation button
				{
					_isChoosingAnimation = true;
					_isEditingAnimation = true;
					_gui.getGlobalScreen()->addChoiceForm("animations", "Select animation", Vec2(0.0f, 0.1f), getLoadedAnimationIDs());
				}
				else if (screen->getButton("deleteAnimation")->isHovered()) // Delete animation button
				{
					_isChoosingAnimation = true;
					_isRemovingAnimation = true;
					_gui.getGlobalScreen()->addChoiceForm("animations", "Select animation", Vec2(0.0f, 0.1f), getLoadedAnimationIDs());
				}
			}

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitAnimationEditor"))
			{
				saveAnimationsToFile();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				unload();
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("exitAnimationEditor"))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				unload();
			}
		}
	}
}

void AnimationEditor::_updateAnimationCreation()
{
	if (_isEditorLoaded)
	{
		if (_isCreatingAnimation)
		{
			string newAnimationName = "";

			// Check if user filled in a new name
			if (_gui.getGlobalScreen()->checkValueForm("newAnimationName", newAnimationName, { _currentAnimationID }))
			{
				// Check if name contains spaces
				if (newAnimationName.find(' ') == string::npos)
				{
					// Check if name already exists
					auto animationIDs = getLoadedAnimationIDs();
					if (std::find(animationIDs.begin(), animationIDs.end(), newAnimationName) == animationIDs.end())
					{
						// Go to editor
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuChoice");

						// Select animation
						_currentAnimationID = newAnimationName;

						// Create animation
						_animations.push_back(make_shared<Animation>(_currentAnimationID));

						// Miscellaneous
						auto textID = _gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID();
						_fe3d.textEntity_setTextContent(textID, "Animation: " + _currentAnimationID, 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID());
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID());
						_isCreatingAnimation = false;
						_isEditingAnimation = true;

					}
					else // Name already exists
					{
						_fe3d.logger_throwWarning("Animation name \"" + newAnimationName + "\" already exists!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning("New animation name cannot contain any spaces!");
				}
			}
		}
	}
}

void AnimationEditor::_updateAnimationChoice()
{
	if (_isEditorLoaded)
	{
		if (_isChoosingAnimation)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("animations");

			// Check if a animation name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select animation
					_currentAnimationID = selectedButtonID;

					// Go to editor
					if (_isEditingAnimation)
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuChoice");

						// Show text
						auto textID = _gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID();
						_fe3d.textEntity_setTextContent(textID, "Animation: " + _currentAnimationID, 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID());
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID());

						// Show preview model
						if (!_getAnimation(_currentAnimationID)->previewModelID.empty())
						{
							_fe3d.modelEntity_show(_getAnimation(_currentAnimationID)->previewModelID);
						}
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("animations");
					_isChoosingAnimation = false;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("animations")) // Cancelled choosing
			{
				_isChoosingAnimation = false;
				_isEditingAnimation = false;
				_isRemovingAnimation = false;
				_gui.getGlobalScreen()->removeChoiceForm("animations");
			}
		}
	}
}

void AnimationEditor::_updateAnimationRemoval()
{
	if (_isEditorLoaded)
	{
		if (_isRemovingAnimation && _currentAnimationID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("removeAnimation", "Are you sure?", Vec2(0.0f, 0.25f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("removeAnimation"))
			{
				// Go to main screen
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuMain");

				// Delete animation
				_deleteAnimation(_currentAnimationID);
				_currentAnimationID = "";

				// Miscellaneous
				_gui.getGlobalScreen()->removeAnswerForm("removeAnimation");
				_isRemovingAnimation = false;
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("removeAnimation"))
			{
				_isRemovingAnimation = false;
				_currentAnimationID = "";
			}
		}
	}
}

void AnimationEditor::_updateCamera()
{
	if (_isEditorLoaded)
	{
		// Update camera speed alteration
		if (_fe3d.input_getKeyPressed(InputType::KEY_UP))
		{
			_cameraSpeed *= 2.0f;
		}
		if (_fe3d.input_getKeyPressed(InputType::KEY_DOWN))
		{
			_cameraSpeed /= 2.0f;
		}

		// Update vertical lookat movement
		if (_fe3d.input_getKeyDown(InputType::KEY_SPACE))
		{
			_cameraLookatPosition.y += (_cameraSpeed / 2.0f);
		}
		if (_fe3d.input_getKeyDown(InputType::KEY_LSHIFT))
		{
			_cameraLookatPosition.y -= (_cameraSpeed / 2.0f);

			// Cannot be negative
			if (_cameraLookatPosition.y < 0.0f)
			{
				_cameraLookatPosition = 0.0f;
			}
		}

		// Update cursor difference
		Vec2 cursorPosition = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition());
		Vec2 cursorDifference = cursorPosition - _lastCursorPos;
		_lastCursorPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition());

		// Update scrolling
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Add to acceleration
			_cameraScrollingAcceleration += (float(-_fe3d.input_getMouseWheelY() / SCROLL_WHEEL_DIVIDER) * _cameraSpeed);
		}
		_cameraScrollingAcceleration *= 0.975f; // Slowing down (smoothing)

		// Adding movement to the 3rd person view
		_cameraDistance += _cameraScrollingAcceleration;

		// Small offset so user cannot zoom inverted
		if (_cameraDistance < 0.1f)
		{
			_cameraDistance = 0.1f;
		}

		// Check if MMB pressed
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
			{
				if (_fe3d.misc_isCursorInsideViewport()) // Only if cursor inside 3d screen
				{
					_cameraAcceleration.x += cursorDifference.x * _cameraSpeed;
					_cameraAcceleration.y += cursorDifference.y * _cameraSpeed;
				}
			}
		}

		// Calculate cursor moving speed
		_cameraAcceleration *= 0.975f;
		_totalCursorDifference += _cameraAcceleration;
		_totalCursorDifference.y = std::clamp(_totalCursorDifference.y, -1.0f, 1.0f);

		// Calculate new camera position
		float x = (_cameraDistance * sin(_totalCursorDifference.x));
		float y = MIN_CAMERA_HEIGHT + (_cameraDistance * _totalCursorDifference.y);
		float z = (_cameraDistance * cos(_totalCursorDifference.x));

		// Update camera position
		_fe3d.camera_setPosition(_cameraLookatPosition + Vec3(x, y, z));
		_fe3d.camera_setLookatPosition(_cameraLookatPosition);

		// Update shadows
		_fe3d.gfx_enableShadows(Vec3(_cameraLookatPosition + Vec3(_cameraDistance * 2.0f)),
			_cameraLookatPosition, _cameraDistance * 4.0f, _cameraDistance * 6.0f, 0.5f, false, true);
	}
}