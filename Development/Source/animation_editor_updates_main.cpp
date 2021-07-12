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

	// GUI
	_updateAnimationExecution();
	_updateManagementScreen();
	_updateEditingScreen();
	_updateFrameScreen();

	// Animation lifecycle
	_updateAnimationCreation();
	_updateAnimationChoice();
	_updateAnimationRemoval();

	// Miscellaneous
	_updateCamera();
	_updateMiscellaneous();
}

void AnimationEditor::_updateManagementScreen()
{
	if (_isEditorLoaded)
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
					_gui.getGlobalScreen()->addAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("addAnimation")->isHovered()) // Add animation button
				{
					_gui.getGlobalScreen()->addValueForm("animationCreate", "New Animation Name", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
					_isCreatingAnimation = true;
				}
				else if (screen->getButton("editAnimation")->isHovered()) // Edit animation button
				{
					_isChoosingAnimation = true;
					_isEditingAnimation = true;
					_gui.getGlobalScreen()->addChoiceForm("animationList", "Select Animation", Vec2(-0.5f, 0.1f), getAllAnimationIDs());
				}
				else if (screen->getButton("deleteAnimation")->isHovered()) // Delete animation button
				{
					_isChoosingAnimation = true;
					_isRemovingAnimation = true;
					_gui.getGlobalScreen()->addChoiceForm("animationList", "Select Animation", Vec2(-0.5f, 0.1f), getAllAnimationIDs());
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
}

void AnimationEditor::_updateAnimationCreation()
{
	if (_isEditorLoaded)
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
}

void AnimationEditor::_updateAnimationChoice()
{
	if (_isEditorLoaded)
	{
		if (_isChoosingAnimation)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("animationList");

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
						if (!_getAnimation(_currentAnimationID)->previewModelID.empty())
						{
							_fe3d.modelEntity_setVisible(_getAnimation(_currentAnimationID)->previewModelID, true);
						}
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("animationList");
					_isChoosingAnimation = false;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("animationList")) // Cancelled choosing
			{
				_isChoosingAnimation = false;
				_isEditingAnimation = false;
				_isRemovingAnimation = false;
				_gui.getGlobalScreen()->removeChoiceForm("animationList");
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