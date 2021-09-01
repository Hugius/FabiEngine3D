#include "animation_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void AnimationEditor::update()
{
	// Prepare animation values
	for (const auto& animation : _animations)
	{
		animation->updateValueLimits();
	}

	// Animation execution
	_updateAnimationExecution();

	// Editor updates
	if (_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if (_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if (_isEditorLoaded)
	{
		_updateFrameMenu();
	}
	if (_isEditorLoaded)
	{
		_updateAnimationCreating();
	}
	if (_isEditorLoaded)
	{
		_updateAnimationChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateAnimationDeleting();
	}
	if (_isEditorLoaded)
	{
		_updateCamera();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void AnimationEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "animationEditorMenuMain")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
			{
				_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", Vec2(0.0f, 0.25f));
			}
			else if (screen->getButton("create")->isHovered()) // Add animation button
			{
				_gui.getGlobalScreen()->createValueForm("animationCreate", "Create Animation", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				_isCreatingAnimation = true;
			}
			else if (screen->getButton("edit")->isHovered()) // Edit animation button
			{
				_isChoosingAnimation = true;
				_isEditingAnimation = true;
				_gui.getGlobalScreen()->createChoiceForm("animationList", "Edit Animation", Vec2(-0.5f, 0.1f), getAllAnimationIDs());
			}
			else if (screen->getButton("delete")->isHovered()) // Delete animation button
			{
				_isChoosingAnimation = true;
				_isDeletingAnimation = true;
				_gui.getGlobalScreen()->createChoiceForm("animationList", "Delete Animation", Vec2(-0.5f, 0.1f), getAllAnimationIDs());
			}
		}

		// Update answer forms
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveAnimationsToFile();
			unload();
			return;
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void AnimationEditor::_updateAnimationCreating()
{
	if (_isCreatingAnimation)
	{
		// Check if user filled in a new ID
		string newAnimationID = "";
		if (_gui.getGlobalScreen()->checkValueForm("animationCreate", newAnimationID, { _currentAnimationID }))
		{
			// Spaces not allowed
			if (newAnimationID.find(' ') == string::npos)
			{
				// Check if animation already exists
				auto animationIDs = getAllAnimationIDs();
				if (find(animationIDs.begin(), animationIDs.end(), newAnimationID) == animationIDs.end())
				{
					// Go to editor
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuChoice");

					// Select animation
					_currentAnimationID = newAnimationID;

					// Create animation
					_animations.push_back(make_shared<Animation>(newAnimationID));

					// Miscellaneous
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + newAnimationID, 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("animationFrame")->getEntityID(), true);
					_isCreatingAnimation = false;
					_isEditingAnimation = true;

				}
				else // ID already exists
				{
					Logger::throwWarning("Animation ID \"" + newAnimationID + "\" already exists!");
				}
			}
			else
			{
				Logger::throwWarning("Animation ID cannot contain any spaces!");
			}
		}
	}
}

void AnimationEditor::_updateAnimationChoosing()
{
	if (_isChoosingAnimation)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("animationList");

		// Hide last model
		if (_hoveredModelID != "")
		{
			_fe3d.modelEntity_setVisible(_hoveredModelID, false);
		}

		// Check if a animation ID is hovered
		if (!selectedButtonID.empty())
		{
			// Set new hovered model
			_hoveredModelID = _getAnimation(selectedButtonID)->previewModelID;

			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select animation
				_currentAnimationID = selectedButtonID;
				_hoveredModelID = "";

				// Go to editor
				if (_isEditingAnimation)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + selectedButtonID, 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("animationFrame")->getEntityID(), true);
				}

				// Miscellaneous
				if (_fe3d.modelEntity_isExisting(_getAnimation(selectedButtonID)->previewModelID))
				{
					_fe3d.modelEntity_setVisible(_getAnimation(selectedButtonID)->previewModelID, true);
				}
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
				_isChoosingAnimation = false;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("animationList")) // Cancelled choosing
		{
			_isChoosingAnimation = false;
			_isEditingAnimation = false;
			_isDeletingAnimation = false;
			_gui.getGlobalScreen()->deleteChoiceForm("animationList");
		}
		else
		{
			_hoveredModelID = "";
		}

		// Show hovered model
		if (_hoveredModelID != "")
		{
			_fe3d.modelEntity_setVisible(_hoveredModelID, true);
		}
	}
}

void AnimationEditor::_updateAnimationDeleting()
{
	if (_isDeletingAnimation && _currentAnimationID != "")
	{
		// Add answer form
		if (!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
		}

		// Update answer form
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Go to main screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuMain");

			// Delete animation
			_deleteAnimation(_currentAnimationID);
			_currentAnimationID = "";

			// Miscellaneous
			_isDeletingAnimation = false;
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isDeletingAnimation = false;
			_currentAnimationID = "";
		}
	}
}