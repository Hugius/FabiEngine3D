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

					// Reset preview model transformation
					if (_fe3d.gameEntity_isExisting(currentAnimation->previewModelID))
					{
						// For every model part
						for (auto& partName : currentAnimation->partNames)
						{
							_fe3d.gameEntity_setPosition(currentAnimation->previewModelID, currentAnimation->initialTranslation, partName);
							_fe3d.gameEntity_setRotationOrigin(currentAnimation->previewModelID, currentAnimation->initialRotationOrigin, partName);
							_fe3d.gameEntity_setRotation(currentAnimation->previewModelID, currentAnimation->initialRotation, partName);
							_fe3d.gameEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partName);
						}
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
					// Reset preview model transformation
					for (auto& partName : currentAnimation->partNames)
					{
						_fe3d.gameEntity_setPosition(currentAnimation->previewModelID, currentAnimation->initialTranslation, partName);
						_fe3d.gameEntity_setRotationOrigin(currentAnimation->previewModelID, currentAnimation->initialRotationOrigin, partName);
						_fe3d.gameEntity_setRotation(currentAnimation->previewModelID, currentAnimation->initialRotation, partName);
						_fe3d.gameEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partName);
					}

					// Start animation
					startAnimation(_currentAnimationID, currentAnimation->previewModelID, 1);
				}
				else if (screen->getButton("stop")->isHovered())
				{
					// Stop animation
					stopAnimation(_currentAnimationID, currentAnimation->previewModelID);

					// Reset preview model transformation
					for (auto& partName : currentAnimation->partNames)
					{
						_fe3d.gameEntity_setPosition(currentAnimation->previewModelID, currentAnimation->initialTranslation, partName);
						_fe3d.gameEntity_setRotationOrigin(currentAnimation->previewModelID, currentAnimation->initialRotationOrigin, partName);
						_fe3d.gameEntity_setRotation(currentAnimation->previewModelID, currentAnimation->initialRotation, partName);
						_fe3d.gameEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partName);
					}
				}
				else if (screen->getButton("addFrame")->isHovered())
				{
					// Retrieve last (or default) frame
					auto lastFrameCopy = currentAnimation->frames.back();

					// Check if model has multiple parts
					if (!currentAnimation->previewModelID.empty() && _fe3d.gameEntity_isMultiParted(currentAnimation->previewModelID))
					{
						// Check if last frame is the default frame
						if (currentAnimation->frames.size() == 1)
						{
							// Clear empty partname
							lastFrameCopy.targetTransformations.clear();
							lastFrameCopy.rotationOrigins.clear();
							lastFrameCopy.speeds.clear();
							lastFrameCopy.speedTypes.clear();
							lastFrameCopy.transformationTypes.clear();

							// Add empty data for every model part
							for (auto partName : currentAnimation->partNames)
							{
								lastFrameCopy.targetTransformations.insert(make_pair(partName, Vec3(0.0f)));
								lastFrameCopy.rotationOrigins.insert(make_pair(partName, Vec3(0.0f)));
								lastFrameCopy.speeds.insert(make_pair(partName, 0.0f));
								lastFrameCopy.speedTypes.insert(make_pair(partName, AnimationSpeedType::LINEAR));
								lastFrameCopy.transformationTypes.insert(make_pair(partName, TransformationType::TRANSLATION));
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
			}

			// Button hoverabilities
			bool isPlaying = (_isAnimationExisting(_currentAnimationID) && isAnimationPlaying(_currentAnimationID, currentAnimation->previewModelID));
			bool hasPreviewModel = !currentAnimation->previewModelID.empty();
			screen->getButton("preview")->setHoverable(!isPlaying);
			screen->getButton("play")->setHoverable(!isPlaying && hasPreviewModel && currentAnimation->frames.size() > 1);
			screen->getButton("stop")->setHoverable(isPlaying&& hasPreviewModel);
			screen->getButton("addFrame")->setHoverable(currentAnimation->frames.size() < _maxFrameCount && !isPlaying && hasPreviewModel);
			screen->getButton("editFrame")->setHoverable(_currentFrameIndex > 0 && !isPlaying);
			screen->getButton("deleteFrame")->setHoverable(currentAnimation->frames.size() > 1 && _currentFrameIndex > 0 && !isPlaying && hasPreviewModel);
			screen->getButton("prev")->setHoverable(_currentFrameIndex > 0 && !isPlaying);
			screen->getButton("next")->setHoverable(_currentFrameIndex < (currentAnimation->frames.size() - 1) && !isPlaying && hasPreviewModel);

			// Showing frame index
			if (!isPlaying)
			{
				auto textID = _gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID();
				_fe3d.textEntity_setTextContent(textID, "Frame: " + to_string(_currentFrameIndex + 1), 0.025f);
			}

			// Check if a animation name is clicked
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("models");
			if (selectedButtonID != "")
			{
				// Check if LMB is pressed
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					// Compose selected model ID
					string selectedModelID = "@" + selectedButtonID;

					// Hide old model
					if (hasPreviewModel)
					{
						if (!currentAnimation->previewModelID.empty())
						{
							_fe3d.gameEntity_hide(currentAnimation->previewModelID);
						}
					}

					// Show new model
					_fe3d.gameEntity_show(selectedModelID);

					// Change values
					currentAnimation->previewModelID = selectedModelID;
					currentAnimation->initialTranslation = _fe3d.gameEntity_getPosition(currentAnimation->previewModelID);
					currentAnimation->initialRotationOrigin = _fe3d.gameEntity_getRotationOrigin(currentAnimation->previewModelID);
					currentAnimation->initialRotation = _fe3d.gameEntity_getRotation(currentAnimation->previewModelID);
					currentAnimation->initialScaling = _fe3d.gameEntity_getSize(currentAnimation->previewModelID);
					currentAnimation->initialColor = _fe3d.gameEntity_getColor(currentAnimation->previewModelID);

					// First time choosing preview model, add all partnames for this animation
					if (currentAnimation->frames.size() == 1)
					{
						// Retrieve partnames from model
						for (auto partName : _fe3d.gameEntity_getPartNames(currentAnimation->previewModelID))
						{
							currentAnimation->partNames.push_back(partName);

							// Also add total transformation for each partname
							currentAnimation->totalTranslations.insert(make_pair(partName, Vec3(0.0f)));
							currentAnimation->totalRotations.insert(make_pair(partName, Vec3(0.0f)));
							currentAnimation->totalScalings.insert(make_pair(partName, Vec3(0.0f)));
						}
					}

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
			auto& rotationOrigin = currentAnimation->frames[_currentFrameIndex].rotationOrigins[_currentPartName];
			auto& speed = currentAnimation->frames[_currentFrameIndex].speeds[_currentPartName];
			auto& speedType = currentAnimation->frames[_currentFrameIndex].speedTypes[_currentPartName];
			auto& transType = currentAnimation->frames[_currentFrameIndex].transformationTypes[_currentPartName];

			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_currentPartName = "";
					_fe3d.gameEntity_setColor(currentAnimation->previewModelID, currentAnimation->initialColor, "");
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuChoice");
				}
				else if (screen->getButton("transformation")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("xTransformation", "X", transformation.x, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("yTransformation", "Y", transformation.y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("zTransformation", "Z", transformation.z, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("rotationOrigin")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("xRotationOrigin", "X", rotationOrigin.x * 1000.0f, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("yRotationOrigin", "Y", rotationOrigin.y * 1000.0f, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("zRotationOrigin", "Z", rotationOrigin.z * 1000.0f, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("speed")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("transformationSpeed", "Transformation speed", speed * 100.0f, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("speedType")->isHovered())
				{
					// Change speed type
					if (speedType == AnimationSpeedType::LINEAR)
					{
						speedType = AnimationSpeedType::EXPONENTIAL;
					}
					else
					{
						speedType = AnimationSpeedType::LINEAR;
					}
				}
				else if (screen->getButton("transType")->isHovered())
				{
					// Change transformation type
					if (transType == TransformationType::TRANSLATION)
					{
						transType = TransformationType::ROTATION;
					}
					else if (transType == TransformationType::ROTATION)
					{
						transType = TransformationType::SCALING;
					}
					else if (transType == TransformationType::SCALING)
					{
						transType = TransformationType::TRANSLATION;
					}
				}
				else if (screen->getButton("part")->isHovered())
				{
					// Choosing part of preview model
					auto modelParts = currentAnimation->partNames;
					modelParts.erase(modelParts.begin());
					_gui.getGlobalScreen()->addChoiceForm("parts", "Select part", Vec2(-0.4f, 0.1f), modelParts);
				}
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

			// Update transformation vector changes
			_gui.getGlobalScreen()->checkValueForm("xTransformation", transformation.x, { });
			_gui.getGlobalScreen()->checkValueForm("yTransformation", transformation.y, { });
			_gui.getGlobalScreen()->checkValueForm("zTransformation", transformation.z, { });

			// Update rotation origin X change
			if (_gui.getGlobalScreen()->checkValueForm("xRotationOrigin", rotationOrigin.x, { }))
			{
				rotationOrigin.x /= 1000.0f;
			}

			// Update rotation origin Y change
			if (_gui.getGlobalScreen()->checkValueForm("yRotationOrigin", rotationOrigin.y, { }))
			{
				rotationOrigin.y /= 1000.0f;
			}

			// Update rotation origin Z change
			if (_gui.getGlobalScreen()->checkValueForm("zRotationOrigin", rotationOrigin.z, { }))
			{
				rotationOrigin.z /= 1000.0f;
			}

			// Update speed change
			if (_gui.getGlobalScreen()->checkValueForm("transformationSpeed", speed, { }))
			{
				speed /= 100.0f;
			}

			// Showing speed type
			string newTextContent = (currentAnimation->frames[_currentFrameIndex].speedTypes[_currentPartName] == AnimationSpeedType::LINEAR) ?
				"Speed: linear" : "Speed: exponential";
			_fe3d.textEntity_setTextContent(screen->getButton("speedType")->getTextfield()->getEntityID(), newTextContent);

			// Showing transformation type
			newTextContent = transType == TransformationType::TRANSLATION ? "Type: translation" :
				transType == TransformationType::ROTATION ? "Type: rotation" : "Type: scaling";
			_fe3d.textEntity_setTextContent(screen->getButton("transType")->getTextfield()->getEntityID(), newTextContent);

			// Check if a animation partname is clicked
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("parts");
			if (selectedButtonID != "")
			{
				// Check if LMB pressed
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					// Check if selected part exists on preview model
					if (_fe3d.gameEntity_hasPart(currentAnimation->previewModelID, selectedButtonID))
					{
						_currentPartName = selectedButtonID;
						_gui.getGlobalScreen()->removeChoiceForm("parts");
					}
					else
					{
						_fe3d.logger_throwWarning("Part does not exist on current preview model!");
					}
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("parts")) // Cancelled choosing
			{
				_gui.getGlobalScreen()->removeChoiceForm("parts");
			}
		}
	}
}