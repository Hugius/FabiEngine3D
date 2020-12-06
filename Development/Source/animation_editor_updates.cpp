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
	if (_isLoaded)
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
					_gui.getGlobalScreen()->addChoiceForm("animations", "Select animation", Vec2(-0.4f, 0.1f), _getAnimationIDs());
				}
				else if (screen->getButton("deleteAnimation")->isHovered()) // Delete animation button
				{
					_isChoosingAnimation = true;
					_isRemovingAnimation = true;
					_gui.getGlobalScreen()->addChoiceForm("animations", "Select animation", Vec2(-0.4f, 0.1f), _getAnimationIDs());
				}
			}

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitAnimationEditor"))
			{
				saveAnimationsToFile();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				unload();
			}
			else if (_gui.getGlobalScreen()->isAnswerFormCancelled("exitAnimationEditor"))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				unload();
			}
		}
	}
}

void AnimationEditor::_updateAnimationCreation()
{
	if (_isLoaded)
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
					auto animationIDs = _getAnimationIDs();
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
						_fe3d.textEntity_setTextContent(textID, "Animation: " + _currentAnimationID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID());
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID());
						_isCreatingAnimation = false;
						_isEditingAnimation = true;

					}
					else // Name already exists
					{
						_fe3d.logger_throwWarning("Animation name \"" + newAnimationName.substr(1) + "\" already exists!");
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
	if (_isLoaded)
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
						_fe3d.textEntity_setTextContent(textID, "Animation: " + _currentAnimationID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID());
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID());

						// Show preview model
						if (!_getAnimation(_currentAnimationID)->previewModelID.empty())
						{
							_fe3d.gameEntity_show(_getAnimation(_currentAnimationID)->previewModelID);
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
	if (_isLoaded)
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
			else if (_gui.getGlobalScreen()->isAnswerFormCancelled("removeAnimation"))
			{
				_isRemovingAnimation = false;
				_currentAnimationID = "";
			}
		}
	}
}

void AnimationEditor::_updateCamera()
{
	if (_isLoaded)
	{
		// Update cursor difference
		Vec2 cursorPosition = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition());
		Vec2 cursorDifference = cursorPosition - _lastCursorPos;
		_lastCursorPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition());

		// Update scrolling
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport()) // No GUI focus and cursor must be within viewport
		{
			_cameraScrollingAcceleration += float(-_fe3d.input_getMouseWheelY() / _scrollWheelDivider); // Add to acceleration
		}
		_cameraScrollingAcceleration *= 0.975f; // Slowing down (smoothing)
		_cameraScrollingAcceleration = std::clamp(_cameraScrollingAcceleration, -1.0f, 1.0f);

		// Adding movement to the 3rd person view & making sure you cannot zoom inverted
		_cameraDistance += _cameraScrollingAcceleration;
		if (_cameraDistance < 0.0f)
		{
			_cameraDistance = 0.0f;
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
		float y = _minCameraHeight + (_cameraDistance * _totalCursorDifference.y);
		float z = (_cameraDistance * cos(_totalCursorDifference.x));

		// Update camera position
		_fe3d.camera_setPosition(Vec3(x, y, z));
	}
}