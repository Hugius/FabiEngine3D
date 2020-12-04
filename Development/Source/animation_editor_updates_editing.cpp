#include "animation_editor.hpp"

void AnimationEditor::_updateEditingScreen()
{
	if (_isLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "animationEditorMenuChoice")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_isEditingAnimation = false;
					_currentAnimationID = "";
					_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID());
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuMain");
				}
				else if (screen->getButton("preview")->isHovered())
				{
					_gui.getGlobalScreen()->addChoiceForm("models", "Select model", Vec2(-0.4f, 0.1f), _fe3d.gameEntity_getAllIDs());
				}
				else if (screen->getButton("play")->isHovered())
				{

				}
				else if (screen->getButton("stop")->isHovered())
				{

				}
				else if (screen->getButton("addFrame")->isHovered())
				{

				}
				else if (screen->getButton("editFrame")->isHovered())
				{

				}
				else if (screen->getButton("deleteFrame")->isHovered())
				{

				}
			}

			// Button hoverabilities
			screen->getButton("play")->setHoverable(false);
			screen->getButton("stop")->setHoverable(false);
			screen->getButton("addFrame")->setHoverable(false);
			screen->getButton("editFrame")->setHoverable(false);
			screen->getButton("deleteFrame")->setHoverable(false);

			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("models");

			// Check if a animation name is hovered
			if (selectedButtonID != "")
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					// Hide old model
					if (!_getAnimation(_currentAnimationID)->modelID.empty())
					{
						_fe3d.gameEntity_hide(_getAnimation(_currentAnimationID)->modelID);
					}

					// Show new model
					_getAnimation(_currentAnimationID)->modelID = selectedButtonID;
					_fe3d.gameEntity_show(selectedButtonID);
					_gui.getGlobalScreen()->removeChoiceForm("models");
				}
				else if (_gui.getGlobalScreen()->isChoiceFormCancelled("models")) // Cancelled choosing
				{
					_gui.getGlobalScreen()->removeChoiceForm("models");
				}
			}
		}
	}
}