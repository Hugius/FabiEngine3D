#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update wireframe rendering
		if(!_currentAnimationID.empty())
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d.billboard_isWireframed(PREVIEW_BILLBOARD_ID))
				{
					_fe3d.billboard_setWireframed(PREVIEW_BILLBOARD_ID, false);
				}
				else
				{
					_fe3d.billboard_setWireframed(PREVIEW_BILLBOARD_ID, true);
				}
			}
		}
	}

	// Check if there is a current animation
	if(!_currentAnimationID.empty())
	{
		// Check if animation not started
		if(!isBillboardAnimationStarted(_currentAnimationID, PREVIEW_BILLBOARD_ID))
		{
			// Reset UV properties
			if(_isEditorLoaded)
			{
				_fe3d.billboard_setMultiplierUV(PREVIEW_BILLBOARD_ID, fvec2(1.0f));
				_fe3d.billboard_setAdderUV(PREVIEW_BILLBOARD_ID, fvec2(0.0f));
			}
		}
	}
}

void Animation2dEditor::_updateAnimationCreating()
{
	if(_isCreatingAnimation)
	{
		// Temporary values
		string newAnimationID = "";

		// Check if user filled in a new ID
		if(_gui.getOverlay()->checkValueForm("animationCreate", newAnimationID, {_currentAnimationID}))
		{
			// Spaces not allowed
			if(newAnimationID.find(' ') != string::npos)
			{
				Logger::throwWarning("Animation ID cannot contain any spaces!");
				return;
			}

			// @ sign not allowed
			if(newAnimationID.find('@') != string::npos)
			{
				Logger::throwWarning("Animation ID cannot contain '@'!");
				return;
			}

			// Check if animation already exists
			auto animationIDs = getAnimationIDs();
			if(find(animationIDs.begin(), animationIDs.end(), newAnimationID) != animationIDs.end())
			{
				Logger::throwWarning("Animation ID \"" + newAnimationID + "\" already exists!");
				return;
			}

			// Go to next screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("animation2dEditorMenuChoice");

			// Create animation
			_animations.push_back(make_shared<Animation2d>(newAnimationID));

			// Select animation
			_currentAnimationID = newAnimationID;

			// Show preview billboard
			_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, true);

			// Miscellaneous
			_fe3d.text_setContent(_gui.getOverlay()->getTextField("animationID")->getEntityID(), "Animation: " + newAnimationID, 0.025f);
			_fe3d.text_setVisible(_gui.getOverlay()->getTextField("animationID")->getEntityID(), true);
			_isCreatingAnimation = false;
		}
	}
}

void Animation2dEditor::_updateAnimationChoosing()
{
	if(_isChoosingAnimation)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("animationList");

		// Check if animation ID is hovered
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
					_fe3d.text_setContent(_gui.getOverlay()->getTextField("animationID")->getEntityID(), "Animation: " + selectedButtonID, 0.025f);
					_fe3d.text_setVisible(_gui.getOverlay()->getTextField("animationID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getOverlay()->deleteChoiceForm("animationList");
				_isChoosingAnimation = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("animationList"))
		{
			_isChoosingAnimation = false;
			_isDeletingAnimation = false;
			_gui.getOverlay()->deleteChoiceForm("animationList");
		}
	}
}

void Animation2dEditor::_updateAnimationDeleting()
{
	if(_isDeletingAnimation && !_currentAnimationID.empty())
	{
		// Add answer form
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
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
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_isDeletingAnimation = false;
			_currentAnimationID = "";
		}
	}
}