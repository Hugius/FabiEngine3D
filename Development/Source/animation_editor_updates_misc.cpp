#include "animation_editor.hpp"

void AnimationEditor::_updateCamera()
{
	if (_isEditorLoaded)
	{
		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Update moving up
			if (_fe3d.input_isKeyDown(InputType::KEY_SPACE))
			{
				_cameraLookatPosition.y += LOOKAT_MOVEMENT_SPEED;
			}

			// Update moving down
			if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT))
			{
				_cameraLookatPosition.y -= LOOKAT_MOVEMENT_SPEED;
				_cameraLookatPosition.y = std::max(0.0f, _cameraLookatPosition.y);
			}
		}

		// Check if third person view is enabled
		if (_fe3d.camera_isThirdPersonViewEnabled())
		{
			// Disable third person view
			_fe3d.camera_disableThirdPersonView();

			// Show cursor
			_fe3d.imageEntity_setVisible("@@cursor", true);

			// Disable shadows
			if (_fe3d.gfx_isShadowsEnabled())
			{
				_fe3d.gfx_disableShadows();
			}

			// Enable shadows
			const auto distance = _fe3d.camera_getThirdPersonDistance();
			_fe3d.gfx_enableShadows(Vec3(_cameraLookatPosition + Vec3(distance * 2.0f)),
				_cameraLookatPosition, distance * 4.0f, distance * 8.0f, 0.5f, false, false, 0);
		}

		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Check if RMB pressed
			if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				// Update lookat
				_fe3d.camera_setThirdPersonLookat(_cameraLookatPosition);

				// Enable third person view
				_fe3d.camera_enableThirdPersonView(
					_fe3d.camera_getThirdPersonYaw(),
					_fe3d.camera_getThirdPersonPitch(),
					_fe3d.camera_getThirdPersonDistance());

				// Hide cursor
				_fe3d.imageEntity_setVisible("@@cursor", false);
			}
		}
	}
}

void AnimationEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		// Lock toggling if GUI focused or cursor not in 3D viewport
		_fe3d.input_setKeyTogglingLocked(_gui.getGlobalScreen()->isFocused() || !_fe3d.misc_isCursorInsideViewport());

		// Update reference model visibility
		if (_fe3d.input_isKeyToggled(InputType::KEY_R))
		{
			_fe3d.modelEntity_setVisible("@@cube", false);
		}
		else
		{
			_fe3d.modelEntity_setVisible("@@cube", true);
		}

		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Update debug rendering
			if (_fe3d.input_isKeyPressed(InputType::KEY_H))
			{
				if (_fe3d.misc_isDebugRenderingEnabled())
				{
					_fe3d.misc_disableDebugRendering();
				}
				else
				{
					_fe3d.misc_enableDebugRendering();
				}
			}
		}

		// Wireframed model rendering
		if (!_currentAnimationID.empty())
		{
			string modelID = _getAnimation(_currentAnimationID)->previewModelID;

			if (!modelID.empty() && _fe3d.modelEntity_isExisting(modelID))
			{
				if (_fe3d.input_isKeyToggled(InputType::KEY_F))
				{
					_fe3d.modelEntity_setWireframed(modelID, true);
				}
				else
				{
					_fe3d.modelEntity_setWireframed(modelID, false);
				}
			}
		}

		// Check if animation loaded in editor
		if (!_currentAnimationID.empty())
		{
			// Retrieve current animation
			auto currentAnimation = _getAnimation(_currentAnimationID);

			// Check if animation is not started
			if (!isAnimationStarted(_currentAnimationID, currentAnimation->previewModelID))
			{
				// Check if animation has a preview model
				if (!currentAnimation->previewModelID.empty())
				{
					// Default transformation
					for (auto partID : currentAnimation->partIDs)
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

					// Set transformation of current frame
					if (_currentFrameIndex > 0)
					{
						// For every frame until current frame
						for (unsigned int frameIndex = 1; frameIndex <= _currentFrameIndex; frameIndex++)
						{
							// Retrieve frame
							auto frame = currentAnimation->frames[frameIndex];

							// For every part of frame
							for (auto partID : currentAnimation->partIDs)
							{
								// Check if model has part
								if (_fe3d.modelEntity_hasPart(currentAnimation->previewModelID, partID) || partID.empty())
								{
									// Determine type of transformation
									if (frame.transformationTypes[partID] == TransformationType::TRANSLATION)
									{
										// Translation
										_fe3d.modelEntity_setPosition(currentAnimation->previewModelID,
											(currentAnimation->initialScaling * frame.targetTransformations[partID]), partID);
									}
									else if (frame.transformationTypes[partID] == TransformationType::ROTATION)
									{
										// Retrieve current model size
										const auto& currentModelSize = _fe3d.modelEntity_getSize(currentAnimation->previewModelID);

										// Origin
										_fe3d.modelEntity_setRotationOrigin(currentAnimation->previewModelID,
											(currentModelSize * frame.rotationOrigins[partID]), partID);

										// Rotation
										_fe3d.modelEntity_setRotation(currentAnimation->previewModelID,
											frame.targetTransformations[partID], partID);
									}
									else if (frame.transformationTypes[partID] == TransformationType::SCALING)
									{
										// Retrieve model size (or part default size)
										const auto& modelSize = partID.empty() ? currentAnimation->initialScaling : Vec3(1.0f);

										// Scaling
										_fe3d.modelEntity_setSize(currentAnimation->previewModelID,
											modelSize + (modelSize * frame.targetTransformations[partID]), partID);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}