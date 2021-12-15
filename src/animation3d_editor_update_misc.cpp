#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::_updateCamera()
{
	// Check if third person view is enabled
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		// Update distance scrolling
		auto scrollOffset = _fe3d.input_getMouseWheelY();
		auto cameraDistance = _fe3d.camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d.camera_setThirdPersonDistance(cameraDistance);

		// Update lookat position
		auto cameraLookat = _fe3d.camera_getThirdPersonLookat();
		if(_fe3d.input_isKeyDown(InputType::KEY_SPACE))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		_fe3d.camera_setThirdPersonLookat(cameraLookat);

		// Hide cursor
		_fe3d.image_setVisible("@@cursor", false);

		// Update shadows
		const auto distance = _fe3d.camera_getThirdPersonDistance();
		_fe3d.gfx_setShadowEyePosition(fvec3(cameraLookat + fvec3(distance * 2.0f)));
		_fe3d.gfx_setShadowCenterPosition(cameraLookat);
		_fe3d.gfx_setShadowAreaSize(distance * 4.0f);
		_fe3d.gfx_setShadowAreaReach(distance * 8.0f);
	}

	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Check if RMB pressed
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check third person view status
			if(_fe3d.camera_isThirdPersonViewEnabled())
			{
				_fe3d.camera_disableThirdPersonView();
			}
			else
			{
				_fe3d.camera_enableThirdPersonView(_fe3d.camera_getThirdPersonYaw(), _fe3d.camera_getThirdPersonPitch());
			}
		}
	}

	// Disable third person view if necessary
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		if(_gui.getGlobalScreen()->isFocused())
		{
			_fe3d.camera_disableThirdPersonView();
		}
	}
}

void Animation3dEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update reference model visibility
		if(_fe3d.input_isKeyPressed(InputType::KEY_R))
		{
			if(_fe3d.model_isVisible("@@box"))
			{
				_fe3d.model_setVisible("@@box", false);
			}
			else
			{
				_fe3d.model_setVisible("@@box", true);
			}
		}

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

		// Update wireframe model rendering
		if(!_currentAnimationID.empty())
		{
			// Temporary values
			const auto currentAnimation = _getAnimation(_currentAnimationID);

			// Check if animation has preview model
			if(_fe3d.model_isExisting(currentAnimation->getPreviewModelID()))
			{
				// Check if F is pressed
				if(_fe3d.input_isKeyPressed(InputType::KEY_F))
				{
					// Iterate through model parts
					for(const auto& partID : currentAnimation->getPartIDs())
					{
						if(!partID.empty() || (currentAnimation->getPartIDs().size() == 1))
						{
							if(_fe3d.model_isWireframed(currentAnimation->getPreviewModelID(), partID))
							{
								_fe3d.model_setWireframed(currentAnimation->getPreviewModelID(), partID, false);
							}
							else
							{
								_fe3d.model_setWireframed(currentAnimation->getPreviewModelID(), partID, true);
							}
						}
					}
				}
			}
		}
	}

	// Check if current animation active
	if(!_currentAnimationID.empty())
	{
		// Retrieve current animation
		auto currentAnimation = _getAnimation(_currentAnimationID);

		// Check if allowed to set frame transformation
		if(_mustUpdateCurrentFramePreview)
		{
			// Check if animation is not started
			if(!isAnimationStarted(_currentAnimationID, currentAnimation->getPreviewModelID()))
			{
				// Check if animation has a preview model
				if(_fe3d.model_isExisting(currentAnimation->getPreviewModelID()))
				{
					// Iterate through animation parts
					for(const auto& partID : currentAnimation->getPartIDs())
					{
						if(partID.empty()) // Base transformation
						{
							_fe3d.model_setBasePosition(currentAnimation->getPreviewModelID(), fvec3(0.0f));
							_fe3d.model_setBaseRotationOrigin(currentAnimation->getPreviewModelID(), fvec3(0.0f));
							_fe3d.model_setBaseRotation(currentAnimation->getPreviewModelID(), fvec3(0.0f));
							_fe3d.model_setBaseSize(currentAnimation->getPreviewModelID(), currentAnimation->getInitialSize());
						}
						else // Part transformation
						{
							_fe3d.model_setPartPosition(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
							_fe3d.model_setPartRotationOrigin(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
							_fe3d.model_setPartRotation(currentAnimation->getPreviewModelID(), partID, fvec3(0.0f));
							_fe3d.model_setPartSize(currentAnimation->getPreviewModelID(), partID, fvec3(1.0f));
						}
					}

					// Set transformation of current frame
					if(_currentFrameIndex > 0)
					{
						// Iterate through frames
						for(unsigned int frameIndex = 1; frameIndex <= _currentFrameIndex; frameIndex++)
						{
							// Retrieve frame
							auto frame = currentAnimation->getFrames()[frameIndex];

							// Iterate through animation parts
							for(const auto& partID : currentAnimation->getPartIDs())
							{
								// Check if model has part
								if(_fe3d.model_hasPart(currentAnimation->getPreviewModelID(), partID) || partID.empty())
								{
									// Determine type of transformation
									if(frame.getTransformationTypes().at(partID) == TransformationType::MOVEMENT)
									{
										// Position
										auto newPosition = (currentAnimation->getInitialSize() * frame.getTargetTransformations().at(partID));
										if(partID.empty())
										{
											_fe3d.model_setBasePosition(currentAnimation->getPreviewModelID(), newPosition);
										}
										else
										{
											_fe3d.model_setPartPosition(currentAnimation->getPreviewModelID(), partID, newPosition);
										}
									}
									else if(frame.getTransformationTypes().at(partID) == TransformationType::ROTATION)
									{
										// Origin
										auto currentModelSize = _fe3d.model_getBaseSize(currentAnimation->getPreviewModelID());
										auto newOrigin = (currentModelSize * frame.getRotationOrigins().at(partID));
										if(partID.empty())
										{
											_fe3d.model_setBaseRotationOrigin(currentAnimation->getPreviewModelID(), newOrigin);
										}
										else
										{
											_fe3d.model_setPartRotationOrigin(currentAnimation->getPreviewModelID(), partID, newOrigin);
										}

										// Rotation
										auto newRotation = frame.getTargetTransformations().at(partID);
										if(partID.empty())
										{
											_fe3d.model_setBaseRotation(currentAnimation->getPreviewModelID(), newRotation);
										}
										else
										{
											_fe3d.model_setPartRotation(currentAnimation->getPreviewModelID(), partID, newRotation);
										}
									}
									else if(frame.getTransformationTypes().at(partID) == TransformationType::SCALING)
									{
										// Size
										auto modelSize = (partID.empty() ? currentAnimation->getInitialSize() : fvec3(1.0f));
										auto newSize = (modelSize + (modelSize * frame.getTargetTransformations().at(partID)));
										if(partID.empty())
										{
											_fe3d.model_setBaseSize(currentAnimation->getPreviewModelID(), newSize);
										}
										else
										{
											_fe3d.model_setPartSize(currentAnimation->getPreviewModelID(), partID, newSize);
										}
									}
								}
							}
						}
					}
				}
			}
		}

		// Update model part highlighting
		auto partID = (_hoveredPartID.empty() ? _currentPartID : _hoveredPartID);
		if(partID.empty())
		{
			_selectedPartHighlightDirection = 1; // Reset direction
		}
		else
		{
			// Check if wireframe color reached minimum
			if(_fe3d.model_getWireframeColor(currentAnimation->getPreviewModelID(), partID) == 0.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			// Check if wireframe color reached maximum
			if(_fe3d.model_getWireframeColor(currentAnimation->getPreviewModelID(), partID) == 1.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			// Set wireframe color
			const auto color = _fe3d.model_getWireframeColor(currentAnimation->getPreviewModelID(), partID);
			const float speed = (PART_HIGHLIGHT_SPEED * static_cast<float>(_selectedPartHighlightDirection));
			_fe3d.model_setWireframeColor(currentAnimation->getPreviewModelID(), partID, (color + speed));
		}
	}
}

void Animation3dEditor::_updateAnimationCreating()
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
					auto animationIDs = getAllAnimationIDs();
					if(find(animationIDs.begin(), animationIDs.end(), newAnimationID) == animationIDs.end())
					{
						// Go to next screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

						// Create animation
						_animations.push_back(make_shared<Animation3d>(newAnimationID));

						// Select animation
						_currentAnimationID = newAnimationID;

						// Miscellaneous
						_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + newAnimationID, 0.025f);
						_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
						_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationFrame")->getEntityID(), true);
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

void Animation3dEditor::_updateAnimationChoosing()
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
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("animation3dEditorMenuChoice");

					// Show preview model
					if(_fe3d.model_isExisting(_getAnimation(selectedButtonID)->getPreviewModelID()))
					{
						_fe3d.model_setVisible(_getAnimation(selectedButtonID)->getPreviewModelID(), true);
					}

					// Miscellaneous
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + selectedButtonID, 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationFrame")->getEntityID(), true);
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

void Animation3dEditor::_updateAnimationDeleting()
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
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("animation3dEditorMenuMain");

			// Delete animation
			if(!_getAnimation(_currentAnimationID)->getPreviewModelID().empty())
			{
				_fe3d.model_setVisible(_getAnimation(_currentAnimationID)->getPreviewModelID(), false);
			}
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