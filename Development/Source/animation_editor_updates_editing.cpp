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
					auto modelIDs = _fe3d.gameEntity_getAllIDs();
					for (auto& ID : modelIDs) { ID = ID.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("models", "Select model", Vec2(-0.4f, 0.1f), modelIDs);
				}
				else if (screen->getButton("play")->isHovered())
				{

				}
				else if (screen->getButton("stop")->isHovered())
				{

				}
				else if (screen->getButton("addFrame")->isHovered())
				{
					auto lastFrameCopy = _getAnimation(_currentAnimationID)->frames.back();
					_getAnimation(_currentAnimationID)->frames.push_back(lastFrameCopy);
					_currentFrameIndex++;
				}
				else if (screen->getButton("editFrame")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuFrame");
				}
				else if (screen->getButton("deleteFrame")->isHovered())
				{
					_getAnimation(_currentAnimationID)->frames.erase(_getAnimation(_currentAnimationID)->frames.begin() + _currentFrameIndex);

					// Correct index
					if (_currentFrameIndex == _getAnimation(_currentAnimationID)->frames.size())
					{
						_currentFrameIndex--;
					}
				}
				else if (screen->getButton("prev")->isHovered())
				{
					_currentFrameIndex--;
				}
				else if (screen->getButton("next")->isHovered())
				{
					_currentFrameIndex++;
				}
			}

			// Showing frame index
			auto textID = _gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID();
			_fe3d.textEntity_setTextContent(textID, "Frame: " + to_string(_currentFrameIndex + 1), 0.025f);

			// Button hoverabilities
			screen->getButton("play")->setHoverable(false);
			screen->getButton("stop")->setHoverable(false);
			screen->getButton("addFrame")->setHoverable(_getAnimation(_currentAnimationID)->frames.size() < _maxFrameCount);
			screen->getButton("deleteFrame")->setHoverable(_getAnimation(_currentAnimationID)->frames.size() > 1);
			screen->getButton("prev")->setHoverable(_currentFrameIndex > 0);
			screen->getButton("next")->setHoverable(_currentFrameIndex < (_getAnimation(_currentAnimationID)->frames.size() - 1));

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
					_getAnimation(_currentAnimationID)->modelID = "@" + selectedButtonID;
					_fe3d.gameEntity_show("@" + selectedButtonID);
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

void AnimationEditor::_updateFrameScreen()
{
	if (_isLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "animationEditorMenuFrame")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuChoice");
				}
				else if (screen->getButton("translation")->isHovered())
				{
					auto translation = _getAnimation(_currentAnimationID)->frames[_currentFrameIndex].translation;
					_gui.getGlobalScreen()->addValueForm("translationX", "X", translation.x, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("translationY", "Y", translation.y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("translationZ", "Z", translation.z, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("rotation")->isHovered())
				{
					auto rotation = _getAnimation(_currentAnimationID)->frames[_currentFrameIndex].rotation;
					_gui.getGlobalScreen()->addValueForm("rotationX", "X", rotation.x, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("rotationY", "Y", rotation.y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("rotationZ", "Z", rotation.z, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("scaling")->isHovered())
				{
					auto scaling = _getAnimation(_currentAnimationID)->frames[_currentFrameIndex].scaling;
					_gui.getGlobalScreen()->addValueForm("scalingX", "X", scaling.x, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("scalingY", "Y", scaling.y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("scalingZ", "Z", scaling.z, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("speed")->isHovered())
				{
					auto speed = _getAnimation(_currentAnimationID)->frames[_currentFrameIndex].speed;
					_gui.getGlobalScreen()->addValueForm("translationSpeed", "X", speed.x, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("rotationSpeed", "Y", speed.y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("scalingSpeed", "Z", speed.z, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
				}
			}


		}
	}
}