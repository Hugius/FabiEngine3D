#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update debug rendering
		if(_fe3d.input_isKeyPressed(InputType::KEY_H))
		{
			if(_fe3d.misc_isDebugRenderingEnabled())
			{
				_fe3d.misc_disableDebugRendering();
			}
			else
			{
				_fe3d.misc_enableDebugRendering();
			}
		}
	}
}

void Animation2dEditor::_updateAnimationCreating()
{
	if(_isCreatingAnimation)
	{
		// Check if user filled in a new ID
		string newAnimationID = "";
		if(_gui.getGlobalScreen()->checkValueForm("animationCreate", newAnimationID, {_currentAnimationID}))
		{
			// @ sign not allowed
			if(newAnimationID.find('@') == string::npos)
			{
				// Spaces not allowed
				if(newAnimationID.find(' ') == string::npos)
				{
					// Check if animation already exists
					auto animationIDs = getAnimationIDs();
					if(find(animationIDs.begin(), animationIDs.end(), newAnimationID) == animationIDs.end())
					{
						// Go to next screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");

						// Create animation
						_animations.push_back(make_shared<Animation2d>(newAnimationID));

						// Select animation
						_currentAnimationID = newAnimationID;

						// Show preview billboard
						_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
						_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

						// Miscellaneous
						_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + newAnimationID, 0.025f);
						_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
						_isCreatingAnimation = false;
					}
					else
					{
						Logger::throwWarning("Animation ID \"" + newAnimationID + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Animation ID cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Animation ID cannot contain '@'!");
			}
		}
	}
}

void Animation2dEditor::_updateAnimationChoosing()
{
	if(_isChoosingAnimation)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("animationList");

		// Check if a animation ID is hovered
		if(!selectedButtonID.empty())
		{
			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select animation
				_currentAnimationID = selectedButtonID;

				// Check if not deleting
				if(!_isDeletingAnimation)
				{
					// Go to next screen
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");

					// Show preview billboard
					_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, _getAnimation(_currentAnimationID)->getPreviewTexturePath());
					_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

					// Miscellaneous
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + selectedButtonID, 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
				_isChoosingAnimation = false;
			}
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("animationList")) // Cancelled choosing
		{
			_isChoosingAnimation = false;
			_isDeletingAnimation = false;
			_gui.getGlobalScreen()->deleteChoiceForm("animationList");
		}
	}
}

void Animation2dEditor::_updateAnimationDeleting()
{
	if(_isDeletingAnimation && !_currentAnimationID.empty())
	{
		// Add answer form
		if(!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Go to main screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("animation2dEditorMenuMain");

			// Hide preview billboard
			_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

			// Delete animation
			_deleteAnimation(_currentAnimationID);
			_currentAnimationID = "";

			// Miscellaneous
			_isDeletingAnimation = false;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isDeletingAnimation = false;
			_currentAnimationID = "";
		}
	}
}