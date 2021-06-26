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

			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					// Stop animation if playing
					if (isAnimationStarted(_currentAnimationID, currentAnimation->previewModelID))
					{
						stopAnimation(_currentAnimationID, currentAnimation->previewModelID);
					}

					// Reset preview model transformation
					if (_fe3d.modelEntity_isExisting(currentAnimation->previewModelID))
					{
						// For every model part
						for (const auto& partID : currentAnimation->partIDs)
						{
							_fe3d.modelEntity_setPosition(currentAnimation->previewModelID, Vec3(0.0f), partID);
							_fe3d.modelEntity_setRotationOrigin(currentAnimation->previewModelID, Vec3(0.0f), partID);
							_fe3d.modelEntity_setRotation(currentAnimation->previewModelID, Vec3(0.0f), partID);
							
							// Only whole model size must be original
							if (partID.empty())
							{
								_fe3d.modelEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partID);
							}
							else
							{
								_fe3d.modelEntity_setSize(currentAnimation->previewModelID, Vec3(1.0f), partID);
							}
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
						_fe3d.modelEntity_hide(currentAnimation->previewModelID);
					}
				}
				else if (screen->getButton("preview")->isHovered())
				{
					auto modelIDs = _modelEditor.getLoadedModelIDs();
					for (auto& ID : modelIDs) { ID = ID.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("models", "Select model", Vec2(-0.4f, 0.1f), modelIDs);
				}
				else if (screen->getButton("play")->isHovered())
				{
					// Reset preview model transformation
					for (const auto& partID : currentAnimation->partIDs)
					{
						_fe3d.modelEntity_setPosition(currentAnimation->previewModelID, Vec3(0.0f), partID);
						_fe3d.modelEntity_setRotationOrigin(currentAnimation->previewModelID, Vec3(0.0f), partID);
						_fe3d.modelEntity_setRotation(currentAnimation->previewModelID, Vec3(0.0f), partID);

						// Only whole model size must be original
						if (partID.empty())
						{
							_fe3d.modelEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partID);
						}
						else
						{
							_fe3d.modelEntity_setSize(currentAnimation->previewModelID, Vec3(1.0f), partID);
						}
					}

					// Start animation
					startAnimation(_currentAnimationID, currentAnimation->previewModelID, 0);
				}
				else if (screen->getButton("stop")->isHovered())
				{
					// Stop animation
					stopAnimation(_currentAnimationID, currentAnimation->previewModelID);

					// Reset preview model transformation
					_fe3d.modelEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, "");
					for (const auto& partID : currentAnimation->partIDs)
					{
						_fe3d.modelEntity_setPosition(currentAnimation->previewModelID, Vec3(0.0f), partID);
						_fe3d.modelEntity_setRotationOrigin(currentAnimation->previewModelID, Vec3(0.0f), partID);
						_fe3d.modelEntity_setRotation(currentAnimation->previewModelID, Vec3(0.0f), partID);
						
						// Only whole model size must be original
						if (partID.empty())
						{
							_fe3d.modelEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partID);
						}
						else
						{
							_fe3d.modelEntity_setSize(currentAnimation->previewModelID, Vec3(1.0f), partID);
						}
					}
				}
				else if (screen->getButton("addFrame")->isHovered())
				{
					// Retrieve last (or default) frame
					auto lastFrameCopy = currentAnimation->frames.back();

					// Check if model has multiple parts
					if (!currentAnimation->previewModelID.empty() && _fe3d.modelEntity_isMultiParted(currentAnimation->previewModelID))
					{
						// Check if last frame is the default frame
						if (currentAnimation->frames.size() == 1)
						{
							// Clear empty partID
							lastFrameCopy.targetTransformations.clear();
							lastFrameCopy.rotationOrigins.clear();
							lastFrameCopy.speeds.clear();
							lastFrameCopy.speedTypes.clear();
							lastFrameCopy.transformationTypes.clear();

							// Add empty data for every model part
							for (auto partID : currentAnimation->partIDs)
							{
								lastFrameCopy.targetTransformations.insert(make_pair(partID, Vec3(0.0f)));
								lastFrameCopy.rotationOrigins.insert(make_pair(partID, Vec3(0.0f)));
								lastFrameCopy.speeds.insert(make_pair(partID, Vec3(0.0f)));
								lastFrameCopy.speedTypes.insert(make_pair(partID, AnimationSpeedType::LINEAR));
								lastFrameCopy.transformationTypes.insert(make_pair(partID, TransformationType::TRANSLATION));
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
					if (isAnimationStarted(_currentAnimationID, currentAnimation->previewModelID))
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
			bool isPlaying = (isAnimationExisting(_currentAnimationID) && isAnimationStarted(_currentAnimationID, currentAnimation->previewModelID));
			bool hasPreviewModel = !currentAnimation->previewModelID.empty();
			screen->getButton("preview")->setHoverable(!isPlaying);
			screen->getButton("play")->setHoverable(!isPlaying && hasPreviewModel && currentAnimation->frames.size() > 1);
			screen->getButton("stop")->setHoverable(isPlaying&& hasPreviewModel);
			screen->getButton("addFrame")->setHoverable(currentAnimation->frames.size() < MAX_FRAME_COUNT && !isPlaying && hasPreviewModel);
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
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					// Compose selected model ID
					string selectedModelID = "@" + selectedButtonID;

					// Check if parts are present
					bool hasAllParts = true;
					for (const auto& partID : currentAnimation->partIDs)
					{
						// Part cannot be empty
						if (!partID.empty())
						{
							hasAllParts = hasAllParts && _fe3d.modelEntity_hasPart(selectedModelID, partID);
						}
					}

					// Throw warning
					if (!hasAllParts)
					{
						_fe3d.logger_throwWarning("Preview model does not have required animation parts!");
						return;
					}

					// Hide old model
					if (hasPreviewModel)
					{
						if (!currentAnimation->previewModelID.empty())
						{
							_fe3d.modelEntity_hide(currentAnimation->previewModelID);
						}
					}

					// Show new model
					_fe3d.modelEntity_show(selectedModelID);

					// Change values
					currentAnimation->previewModelID = selectedModelID;
					currentAnimation->initialScaling = _fe3d.modelEntity_getSize(currentAnimation->previewModelID);
					currentAnimation->initialColor = _fe3d.modelEntity_getColor(currentAnimation->previewModelID);

					// First time choosing preview model, add all partIDs for this animation
					if (currentAnimation->frames.size() == 1)
					{
						// Retrieve partIDs from model
						for (auto partID : _fe3d.modelEntity_getPartIDs(currentAnimation->previewModelID))
						{
							// Cannot add whole-model partID again
							if (!partID.empty())
							{
								currentAnimation->partIDs.push_back(partID);

								// Also add total transformation for each partID
								currentAnimation->totalTranslations.insert(make_pair(partID, Vec3(0.0f)));
								currentAnimation->totalRotations.insert(make_pair(partID, Vec3(0.0f)));
								currentAnimation->totalScalings.insert(make_pair(partID, Vec3(0.0f)));
							}
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