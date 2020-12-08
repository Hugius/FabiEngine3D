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
					// Stop animation if playing
					if (isAnimationPlaying(_currentAnimationID, currentAnimation->previewModelID))
					{
						stopAnimation(_currentAnimationID, currentAnimation->previewModelID);
					}

					// Reset some values
					_isEditingAnimation = false;
					_currentAnimationID = "";
					_currentFrameIndex = 0;
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
					// Retrieve last (or default) frame
					auto lastFrameCopy = currentAnimation->frames.back();

					// Check if model has multiple parts
					if (!currentAnimation->previewModelID.empty() && _fe3d.gameEntity_isMultiParted(currentAnimation->previewModelID))
					{
						// Check if last frame is default
						if (lastFrameCopy.partNames.size() == 1)
						{
							// Add empty data for every model part
							for (auto& partName : _fe3d.gameEntity_getPartNames(currentAnimation->previewModelID))
							{
								lastFrameCopy.partNames.push_back(partName);
								lastFrameCopy.targetTransformations.insert(make_pair(partName, Vec3(0.0f)));
								lastFrameCopy.totalTransformations.insert(make_pair(partName, Vec3(0.0f)));
								lastFrameCopy.speeds.insert(make_pair(partName, 0.0f));
								lastFrameCopy.speedTypes.insert(make_pair(partName, AnimationSpeedType::LINEAR));
							}
						}
					}

					// Add copied frame
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
			bool isPlaying = isAnimationPlaying(_currentAnimationID, currentAnimation->previewModelID);
			screen->getButton("play")->setHoverable(!isPlaying);
			screen->getButton("stop")->setHoverable(isPlaying);
			screen->getButton("addFrame")->setHoverable(currentAnimation->frames.size() < _maxFrameCount && !isPlaying);
			screen->getButton("editFrame")->setHoverable(_currentFrameIndex > 0 && !isPlaying);
			screen->getButton("deleteFrame")->setHoverable(currentAnimation->frames.size() > 1 && _currentFrameIndex > 0 && !isPlaying);
			screen->getButton("prev")->setHoverable(_currentFrameIndex > 0 && !isPlaying);
			screen->getButton("next")->setHoverable(_currentFrameIndex < (currentAnimation->frames.size() - 1) && !isPlaying);
			screen->getButton("type")->setHoverable(!isPlaying);

			// Check if a animation name is clicked
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("models");
			if (selectedButtonID != "")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					// Hide old model
					if (!currentAnimation->previewModelID.empty())
					{
						_fe3d.gameEntity_hide(currentAnimation->previewModelID);
					}

					// Show new model
					_fe3d.gameEntity_show(currentAnimation->previewModelID);

					// Set new values
					currentAnimation->previewModelID = "@" + selectedButtonID;
					currentAnimation->initialTranslation = _fe3d.gameEntity_getPosition(currentAnimation->previewModelID);
					currentAnimation->initialRotation = _fe3d.gameEntity_getRotation(currentAnimation->previewModelID);
					currentAnimation->initialScaling = _fe3d.gameEntity_getSize(currentAnimation->previewModelID);
					currentAnimation->initialColor = _fe3d.gameEntity_getColor(currentAnimation->previewModelID);

					// Miscellaneous
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
			auto& transformation = currentAnimation->frames[_currentFrameIndex].targetTransformations[_currentPartName];
			auto& speed = currentAnimation->frames[_currentFrameIndex].speeds[_currentPartName];

			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_currentPartName = "";
					_fe3d.gameEntity_setColor(currentAnimation->previewModelID, currentAnimation->initialColor, "");
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
					if (currentAnimation->frames[_currentFrameIndex].speedTypes[_currentPartName] == AnimationSpeedType::LINEAR)
					{
						currentAnimation->frames[_currentFrameIndex].speedTypes[_currentPartName] = AnimationSpeedType::EXPONENTIAL;
					}
					else
					{
						currentAnimation->frames[_currentFrameIndex].speedTypes[_currentPartName] = AnimationSpeedType::LINEAR;
					}
				}
				else if (screen->getButton("part")->isHovered())
				{
					_gui.getGlobalScreen()->addChoiceForm("parts", "Select part", Vec2(-0.4f, 0.1f),
						_fe3d.gameEntity_getPartNames(currentAnimation->previewModelID));
					std::cout << _fe3d.gameEntity_getPartNames(currentAnimation->previewModelID).size();

				}
			}

			// Check if a animation partname is clicked
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("parts");
			if (selectedButtonID != "")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					_currentPartName = selectedButtonID;
					_gui.getGlobalScreen()->removeChoiceForm("parts");
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("parts")) // Cancelled choosing
			{
				_gui.getGlobalScreen()->removeChoiceForm("parts");
			}

			// Emphasize selected model part
			if (!_currentPartName.empty())
			{
				_fe3d.gameEntity_setColor(currentAnimation->previewModelID, currentAnimation->initialColor, "");
				_fe3d.gameEntity_setColor(currentAnimation->previewModelID, currentAnimation->initialColor * _partColorStrength, _currentPartName);
			}

			// Update color strength
			_partColorIncreasing = (_partColorStrength >= 1.0f) ? false : (_partColorStrength <= 0.0f) ? true : _partColorIncreasing;
			_partColorStrength += ((_partColorIncreasing ? 1.0f : -1.0f) * _colorChangingSpeed);

			// Showing speed type
			string newContent = (currentAnimation->frames[_currentFrameIndex].speedTypes[_currentPartName] == AnimationSpeedType::LINEAR) ?
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