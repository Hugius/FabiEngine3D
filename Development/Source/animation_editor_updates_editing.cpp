#include "animation_editor.hpp"

void AnimationEditor::_updateEditingScreen()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "animationEditorMenuChoice")
		{
			// Temporary values
			auto currentAnimation = _getAnimation(_currentAnimationID);

			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_isEditingAnimation = false;
					_currentAnimationID = "";
					_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAnimationName")->getEntityID());
					_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID());
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuMain");
					
					// Hide preview model
					if (!currentAnimation->previewModelID.empty())
					{
						_fe3d.gameEntity_hide(currentAnimation->previewModelID);
					}
				}
				else if (screen->getButton("preview")->isHovered())
				{
					auto modelIDs = _fe3d.gameEntity_getAllIDs();
					for (auto& ID : modelIDs) { ID = ID.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("models", "Select model", Vec2(-0.4f, 0.1f), modelIDs);
				}
				else if (screen->getButton("play")->isHovered())
				{
					startAnimation(_currentAnimationID, currentAnimation->previewModelID, 1);
					_fe3d.gameEntity_setPosition(currentAnimation->previewModelID, currentAnimation->initialTranslation);
					_fe3d.gameEntity_setRotation(currentAnimation->previewModelID, currentAnimation->initialRotation);
					_fe3d.gameEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling);
				}
				else if (screen->getButton("stop")->isHovered())
				{
					stopAnimation(_currentAnimationID, currentAnimation->previewModelID);
				}
				else if (screen->getButton("addFrame")->isHovered())
				{
					auto lastFrameCopy = _getAnimation(_currentAnimationID)->frames.back();
					currentAnimation->frames.push_back(lastFrameCopy);
					_currentFrameIndex++;
				}
				else if (screen->getButton("editFrame")->isHovered())
				{
					// First stop animation
					if (isAnimationPlaying(_currentAnimationID, currentAnimation->previewModelID))
					{
						stopAnimation(_currentAnimationID, currentAnimation->previewModelID);
					}

					// Go to editor screen
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuFrame");
				}
				else if (screen->getButton("deleteFrame")->isHovered())
				{
					currentAnimation->frames.erase(currentAnimation->frames.begin() + _currentFrameIndex);

					// Correct index
					if (_currentFrameIndex == currentAnimation->frames.size())
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
				else if (screen->getButton("type")->isHovered())
				{
					if (currentAnimation->transformationType == TransformationType::TRANSLATION)
					{
						currentAnimation->transformationType = TransformationType::ROTATION;
					}
					else if (currentAnimation->transformationType == TransformationType::ROTATION)
					{
						currentAnimation->transformationType = TransformationType::SCALING;
					}
					else if (currentAnimation->transformationType == TransformationType::SCALING)
					{
						currentAnimation->transformationType = TransformationType::TRANSLATION;
					}
				}
			}

			// Showing transformation type
			string newContent = currentAnimation->transformationType == TransformationType::TRANSLATION ? "Type: translation" : 
				currentAnimation->transformationType == TransformationType::ROTATION ? "Type: rotation" : "Type: scaling";
			_fe3d.textEntity_setTextContent(screen->getButton("type")->getTextfield()->getEntityID(), newContent);

			// Showing frame index
			auto textID = _gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID();
			_fe3d.textEntity_setTextContent(textID, "Frame: " + to_string(_currentFrameIndex + 1), 0.025f);

			// Button hoverabilities
			screen->getButton("play")->setHoverable(!isAnimationPlaying(_currentAnimationID, currentAnimation->previewModelID));
			screen->getButton("stop")->setHoverable(isAnimationPlaying(_currentAnimationID, currentAnimation->previewModelID));
			screen->getButton("addFrame")->setHoverable(currentAnimation->frames.size() < _maxFrameCount);
			screen->getButton("editFrame")->setHoverable(_currentFrameIndex > 0);
			screen->getButton("deleteFrame")->setHoverable(currentAnimation->frames.size() > 1 && _currentFrameIndex > 0);
			screen->getButton("prev")->setHoverable(_currentFrameIndex > 0);
			screen->getButton("next")->setHoverable(_currentFrameIndex < (currentAnimation->frames.size() - 1));

			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("models");

			// Check if a animation name is hovered
			if (selectedButtonID != "")
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					// Hide old model
					if (!currentAnimation->previewModelID.empty())
					{
						_fe3d.gameEntity_hide(currentAnimation->previewModelID);
					}

					// Show new model
					currentAnimation->previewModelID = "@" + selectedButtonID;
					_fe3d.gameEntity_show(currentAnimation->previewModelID);
					currentAnimation->initialTranslation = _fe3d.gameEntity_getPosition(currentAnimation->previewModelID);
					currentAnimation->initialRotation = _fe3d.gameEntity_getRotation(currentAnimation->previewModelID);
					currentAnimation->initialScaling = _fe3d.gameEntity_getSize(currentAnimation->previewModelID);
					_gui.getGlobalScreen()->removeChoiceForm("models");
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("models")) // Cancelled choosing
			{
				_gui.getGlobalScreen()->removeChoiceForm("models");
			}
		}
	}
}

void AnimationEditor::_updateFrameScreen()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "animationEditorMenuFrame")
		{
			// Temporary values
			auto currentAnimation = _getAnimation(_currentAnimationID);
			auto& transformation = currentAnimation->frames[_currentFrameIndex].targetTransformation;
			auto& speed = currentAnimation->frames[_currentFrameIndex].speed;

			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuChoice");
				}
				else if (screen->getButton("xTransformation")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("xTransformation", "X", transformation.x, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("yTransformation")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("yTransformation", "Y", transformation.y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("zTransformation")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("zTransformation", "Z", transformation.z, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("speed")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("transformationSpeed", "Transformation speed", speed * 100.0f, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("speedType")->isHovered())
				{
					// Change speed type
					if (currentAnimation->frames[_currentFrameIndex].speedType == AnimationSpeedType::LINEAR)
					{
						currentAnimation->frames[_currentFrameIndex].speedType = AnimationSpeedType::EXPONENTIAL;
					}
					else
					{
						currentAnimation->frames[_currentFrameIndex].speedType = AnimationSpeedType::LINEAR;
					}
				}
			}

			// Showing speed type
			string newContent = (currentAnimation->frames[_currentFrameIndex].speedType == AnimationSpeedType::LINEAR) ? 
				"Type: linear" : "Type: exponential";
			_fe3d.textEntity_setTextContent(screen->getButton("speedType")->getTextfield()->getEntityID(), newContent);

			// Update transformation changes
			_gui.getGlobalScreen()->checkValueForm("xTransformation", transformation.x, { });
			_gui.getGlobalScreen()->checkValueForm("yTransformation", transformation.y, { });
			_gui.getGlobalScreen()->checkValueForm("zTransformation", transformation.z, { });

			// Update speed change
			if (_gui.getGlobalScreen()->checkValueForm("transformationSpeed", speed, { }))
			{
				speed /= 100.0f;
			}
		}
	}
}