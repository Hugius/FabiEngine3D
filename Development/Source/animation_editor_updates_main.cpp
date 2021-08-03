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
		_updateChoiceMenu();
		_updateFrameMenu();
		_updateAnimationCreating();
		_updateAnimationChoosing();
		_updateAnimationDeleting();
		_updateCamera();
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
				_gui.getGlobalScreen()->createAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
			}
			else if (screen->getButton("add")->isHovered()) // Add animation button
			{
				_gui.getGlobalScreen()->createValueForm("animationCreate", "New Animation Name", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				_isCreatingAnimation = true;
			}
			else if (screen->getButton("edit")->isHovered()) // Edit animation button
			{
				_isChoosingAnimation = true;
				_isEditingAnimation = true;
				_gui.getGlobalScreen()->createChoiceForm("animationList", "Select Animation", Vec2(-0.5f, 0.1f), getAllAnimationIDs());
			}
			else if (screen->getButton("delete")->isHovered()) // Delete animation button
			{
				_isChoosingAnimation = true;
				_isDeletingAnimation = true;
				_gui.getGlobalScreen()->createChoiceForm("animationList", "Select Animation", Vec2(-0.5f, 0.1f), getAllAnimationIDs());
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
		{
			saveAnimationsToFile();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
		}
	}
}

void AnimationEditor::_updateAnimationCreating()
{
	if (_isCreatingAnimation)
	{
		string newAnimationName = "";

		// Check if user filled in a new name
		if (_gui.getGlobalScreen()->checkValueForm("animationCreate", newAnimationName, { _currentAnimationID }))
		{
			// Check if name contains spaces
			if (newAnimationName.find(' ') == string::npos)
			{
				// Check if name already exists
				auto animationIDs = getAllAnimationIDs();
				if (find(animationIDs.begin(), animationIDs.end(), newAnimationName) == animationIDs.end())
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
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID(), true);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID(), true);
					_isCreatingAnimation = false;
					_isEditingAnimation = true;

				}
				else // Name already exists
				{
					Logger::throwWarning("Animation name \"" + newAnimationName + "\" already exists!");
				}
			}
			else
			{
				Logger::throwWarning("Animation name cannot contain any spaces!");
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

		// Check if a animation name is hovered
		if (selectedButtonID != "")
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
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
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID(), true);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID(), true);

					// Show preview model
					if (_fe3d.modelEntity_isExisting(_getAnimation(_currentAnimationID)->previewModelID))
					{
						_fe3d.modelEntity_setVisible(_getAnimation(_currentAnimationID)->previewModelID, true);
					}
				}

				// Miscellaneous
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

		// Check if form is answered
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
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isDeletingAnimation = false;
			_currentAnimationID = "";
		}
	}
}