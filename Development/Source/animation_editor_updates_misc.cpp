#include "animation_editor.hpp"

void AnimationEditor::_updateCamera()
{
	// Check if third person view is enabled
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		// Update distance scrolling
		auto scrollOffset = _fe3d.input_getMouseWheelY();
		auto cameraDistance = _fe3d.camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d.camera_setThirdPersonDistance(cameraDistance);

		// Update lookat position
		auto cameraLookat = _fe3d.camera_getThirdPersonLookat();
		if (_fe3d.input_isKeyDown(InputType::KEY_SPACE))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		_fe3d.camera_setThirdPersonLookat(cameraLookat);

		// Hide cursor
		_fe3d.imageEntity_setVisible("@@cursor", false);

		// Disable shadows
		if (_fe3d.gfx_isShadowsEnabled())
		{
			_fe3d.gfx_disableShadows();
		}

		// Enable shadows
		const auto distance = _fe3d.camera_getThirdPersonDistance();
		_fe3d.gfx_enableShadows(Vec3(cameraLookat + Vec3(distance * 2.0f)),
			cameraLookat, distance * 4.0f, distance * 8.0f, 0.25f, false, 0);
	}

	// Check if allowed by GUI
	if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Check if RMB pressed
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check third person view status
			if (_fe3d.camera_isThirdPersonViewEnabled())
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
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		if (_gui.getGlobalScreen()->isFocused())
		{
			_fe3d.camera_disableThirdPersonView();
		}
	}
}

void AnimationEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update reference model visibility
		if (_fe3d.input_isKeyPressed(InputType::KEY_R))
		{
			if (_fe3d.modelEntity_isVisible("@@cube"))
			{
				_fe3d.modelEntity_setVisible("@@cube", false);
			}
			else
			{
				_fe3d.modelEntity_setVisible("@@cube", true);
			}
		}

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

		// Wire frame model rendering
		if (!_currentAnimationID.empty())
		{
			const auto modelID = _getAnimation(_currentAnimationID)->previewModelID;
			if (_fe3d.modelEntity_isExisting(modelID))
			{
				if (_fe3d.input_isKeyPressed(InputType::KEY_F))
				{
					if (_fe3d.modelEntity_isWireFramed(modelID))
					{
						_fe3d.modelEntity_setWireFramed(modelID, false);
					}
					else
					{
						_fe3d.modelEntity_setWireFramed(modelID, true);
					}
				}
			}
		}
	}

	// Check if allowed to set frame transformation
	if (!_currentAnimationID.empty() && _mustUpdateCurrentFramePreview)
	{
		// Retrieve current animation
		auto currentAnimation = _getAnimation(_currentAnimationID);

		// Check if animation is not started
		if (!isAnimationStarted(_currentAnimationID, currentAnimation->previewModelID))
		{
			// Check if animation has a preview model
			if (_fe3d.modelEntity_isExisting(currentAnimation->previewModelID))
			{
				// For every animation part
				for (auto partID : currentAnimation->partIDs)
				{
					// Default transformation
					_fe3d.modelEntity_setPosition(currentAnimation->previewModelID, Vec3(0.0f), partID);
					_fe3d.modelEntity_setRotationOrigin(currentAnimation->previewModelID, Vec3(0.0f), partID);
					_fe3d.modelEntity_setRotation(currentAnimation->previewModelID, Vec3(0.0f), partID);

					// Only whole model size must be original
					if (partID.empty())
					{
						_fe3d.modelEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialSize, partID);
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
								if (frame.transformationTypes[partID] == TransformationType::MOVEMENT)
								{
									// Movement
									_fe3d.modelEntity_setPosition(currentAnimation->previewModelID,
										(currentAnimation->initialSize * frame.targetTransformations[partID]), partID);
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
									const auto& modelSize = partID.empty() ? currentAnimation->initialSize : Vec3(1.0f);

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

		// Update hovered model part inversion
		auto partID = (_hoveredPartID.empty() ? _currentPartID : _hoveredPartID);
		if (partID.empty())
		{
			_selectedPartInversionDirection = 1; // Reset direction
		}
		else
		{
			// Check if inversion reached minimum
			if (_fe3d.modelEntity_getInversion(currentAnimation->previewModelID, partID) == 0.0f)
			{
				_selectedPartInversionDirection *= -1;
			}

			// Check if inversion reached maximum
			if (_fe3d.modelEntity_getInversion(currentAnimation->previewModelID, partID) == 1.0f)
			{
				_selectedPartInversionDirection *= -1;
			}

			// Set model inversion
			float speed = (PART_BLINKING_SPEED * static_cast<float>(_selectedPartInversionDirection));
			float newInversion = (_fe3d.modelEntity_getInversion(currentAnimation->previewModelID, partID) + speed);
			_fe3d.modelEntity_setInversion(currentAnimation->previewModelID, newInversion, partID);
		}
	}
}