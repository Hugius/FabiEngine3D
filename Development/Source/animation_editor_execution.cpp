#include "animation_editor.hpp"

void AnimationEditor::_updateAnimationExecution()
{
	if (!_fe3d.application_isPaused())
	{
		// Update all playing animations
		for (auto& [idPair, animation] : _startedAnimations)
		{
			// Skip paused animations
			if (animation.isPaused)
			{
				continue;
			}

			// Showing frame index
			if (_isEditorLoaded)
			{
				auto textID = _gui.getGlobalScreen()->getTextfield("selectedAnimationFrame")->getEntityID();
				_fe3d.textEntity_setTextContent(textID, "Frame: " + to_string(animation.frameIndex + 1), 0.025f);
			}

			// Retrieve current frame
			auto& frame = animation.frames[animation.frameIndex];

			// For every model part in this frame
			unsigned int finishedPartsAmount = 0;
			for (auto partID : animation.partIDs)
			{
				// Check if model still exists
				if (!_fe3d.modelEntity_isExisting(animation.animatedModelID))
				{
					break;
				}

				// Immutable values
				const auto& currentModelSize = _fe3d.modelEntity_getSize(animation.animatedModelID);
				const auto& transformationType = frame.transformationTypes[partID];
				const auto& isMovement = (transformationType == TransformationType::MOVEMENT);
				const auto& isRotation = (transformationType == TransformationType::ROTATION);
				const auto& isScaling = (transformationType == TransformationType::SCALING);
				const auto& speedMultiplier = (partID.empty() || (isMovement || isScaling)) ? animation.initialSize : Vec3(1.0f);
				const auto& speedType = frame.speedTypes[partID];
				const auto& rotationOrigin = frame.rotationOrigins[partID];
				const auto& speed = frame.speeds[partID] * animation.speedMultiplier;
				const auto& xSpeed = (!isRotation ? (speedMultiplier.x * speed.x) : speed.x);
				const auto& ySpeed = (!isRotation ? (speedMultiplier.y * speed.y) : speed.y);
				const auto& zSpeed = (!isRotation ? (speedMultiplier.z * speed.z) : speed.z);

				// Movement is relative to initial size
				// Rotation is always relative to real-time size
				// Scaling is relative to initial size
				const auto& targetTransformation =
					isMovement ? (animation.initialSize * frame.targetTransformations[partID]) :
					isRotation ? frame.targetTransformations[partID] :
					((partID.empty() ? animation.initialSize : Vec3(1.0f)) * frame.targetTransformations[partID]);

				// Mutable values
				auto& totalMovement = animation.totalMovements[partID];
				auto& totalRotation = animation.totalRotations[partID];
				auto& totalScaling = animation.totalScalings[partID];
				auto& baseSpeed = frame.speeds[partID];
				
				// Check if reached transformation of current frame
				if (((isMovement && _hasReachedFloat(totalMovement.x, targetTransformation.x, xSpeed)) &&
					(isMovement && _hasReachedFloat(totalMovement.y, targetTransformation.y, xSpeed)) &&
					(isMovement && _hasReachedFloat(totalMovement.z, targetTransformation.z, xSpeed))) ||
					((isRotation && _hasReachedFloat(totalRotation.x, targetTransformation.x, ySpeed)) &&
						(isRotation && _hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) &&
						(isRotation && _hasReachedFloat(totalRotation.z, targetTransformation.z, ySpeed))) ||
					((isScaling && _hasReachedFloat(totalScaling.x, targetTransformation.x, zSpeed)) &&
						(isScaling && _hasReachedFloat(totalScaling.y, targetTransformation.y, zSpeed)) &&
						(isScaling && _hasReachedFloat(totalScaling.z, targetTransformation.z, zSpeed))))
				{
					finishedPartsAmount++;
				}
				else
				{
					// X transformation
					if ((isMovement && !_hasReachedFloat(totalMovement.x, targetTransformation.x, xSpeed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.x, targetTransformation.x, xSpeed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.x, targetTransformation.x, xSpeed)))
					{
						// Final transformation speed
						float finalSpeed = xSpeed;

						// Determine transformation type
						if (transformationType == TransformationType::MOVEMENT)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalMovement.x);
							}

							totalMovement.x += finalSpeed;
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalRotation.x);
							}

							totalRotation.x += finalSpeed;
						}
						else if (transformationType == TransformationType::SCALING)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalScaling.x);
							}

							totalScaling.x += finalSpeed;
						}

						// Increase speed if exponential
						if (speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed.x += (baseSpeed.x / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isMovement && _hasReachedFloat(totalMovement.x, targetTransformation.x, xSpeed)) ||
							(isRotation && _hasReachedFloat(totalRotation.x, targetTransformation.x, xSpeed)) ||
							(isScaling && _hasReachedFloat(totalScaling.x, targetTransformation.x, xSpeed)))
						{
							// Determine transformation type
							if (transformationType == TransformationType::MOVEMENT)
							{
								difference = (totalMovement.x - targetTransformation.x);
								totalMovement.x += (-difference);
							}
							else if (transformationType == TransformationType::ROTATION)
							{
								difference = (totalRotation.x - targetTransformation.x);
								totalRotation.x += (-difference);
							}
							else if (transformationType == TransformationType::SCALING)
							{
								difference = (totalScaling.x - targetTransformation.x);
								totalScaling.x += (-difference);
							}
						}

						// Transform the model
						if (transformationType == TransformationType::MOVEMENT)
						{
							_fe3d.modelEntity_move(animation.animatedModelID, Vec3(finalSpeed + (-difference), 0.0f, 0.0f), partID);
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							_fe3d.modelEntity_setRotationOrigin(animation.animatedModelID, currentModelSize * rotationOrigin, partID);
							_fe3d.modelEntity_rotate(animation.animatedModelID, Vec3(finalSpeed + (-difference), 0.0f, 0.0f), partID);
						}
						else if (transformationType == TransformationType::SCALING)
						{
							_fe3d.modelEntity_scale(animation.animatedModelID, Vec3(finalSpeed + (-difference), 0.0f, 0.0f), partID);
						}
					}

					// Y transformation
					if ((isMovement && !_hasReachedFloat(totalMovement.y, targetTransformation.y, ySpeed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.y, targetTransformation.y, ySpeed)))
					{
						// Final transformation speed
						float finalSpeed = ySpeed;

						// Determine transformation type
						if (transformationType == TransformationType::MOVEMENT)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalMovement.y);
							}

							totalMovement.y += finalSpeed;
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalRotation.y);
							}

							totalRotation.y += finalSpeed;
						}
						else if (transformationType == TransformationType::SCALING)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalScaling.y);
							}

							totalScaling.y += finalSpeed;
						}

						// Increase speed if exponential
						if (speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed.y += (baseSpeed.y / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isMovement && _hasReachedFloat(totalMovement.y, targetTransformation.y, ySpeed)) ||
							(isRotation && _hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) ||
							(isScaling && _hasReachedFloat(totalScaling.y, targetTransformation.y, ySpeed)))
						{
							// Determine transformation type
							if (transformationType == TransformationType::MOVEMENT)
							{
								difference = (totalMovement.y - targetTransformation.y);
								totalMovement.y += (-difference);
							}
							else if (transformationType == TransformationType::ROTATION)
							{
								difference = (totalRotation.y - targetTransformation.y);
								totalRotation.y += (-difference);
							}
							else if (transformationType == TransformationType::SCALING)
							{
								difference = (totalScaling.y - targetTransformation.y);
								totalScaling.y += (-difference);
							}
						}

						// Transform the model
						if (transformationType == TransformationType::MOVEMENT)
						{
							_fe3d.modelEntity_move(animation.animatedModelID, Vec3(0.0f, finalSpeed + (-difference), 0.0f), partID);
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							_fe3d.modelEntity_setRotationOrigin(animation.animatedModelID, currentModelSize * rotationOrigin, partID);
							_fe3d.modelEntity_rotate(animation.animatedModelID, Vec3(0.0f, finalSpeed + (-difference), 0.0f), partID);
						}
						else if (transformationType == TransformationType::SCALING)
						{
							_fe3d.modelEntity_scale(animation.animatedModelID, Vec3(0.0f, finalSpeed + (-difference), 0.0f), partID);
						}
					}

					// Z transformation
					if ((isMovement && !_hasReachedFloat(totalMovement.z, targetTransformation.z, zSpeed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.z, targetTransformation.z, zSpeed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.z, targetTransformation.z, zSpeed)))
					{
						// Final transformation speed
						float finalSpeed = zSpeed;

						// Determine transformation type
						if (transformationType == TransformationType::MOVEMENT)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalMovement.z);
							}

							totalMovement.z += finalSpeed;
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalRotation.z);
							}

							totalRotation.z += finalSpeed;
						}
						else if (transformationType == TransformationType::SCALING)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalScaling.z);
							}

							totalScaling.z += finalSpeed;
						}

						// Increase speed if exponential
						if (speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed.z += (baseSpeed.z / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isMovement && _hasReachedFloat(totalMovement.z, targetTransformation.z, finalSpeed)) ||
							(isRotation && _hasReachedFloat(totalRotation.z, targetTransformation.z, finalSpeed)) ||
							(isScaling && _hasReachedFloat(totalScaling.z, targetTransformation.z, finalSpeed)))
						{
							// Determine transformation type
							if (transformationType == TransformationType::MOVEMENT)
							{
								difference = (totalMovement.z - targetTransformation.z);
								totalMovement.z += (-difference);
							}
							else if (transformationType == TransformationType::ROTATION)
							{
								difference = (totalRotation.z - targetTransformation.z);
								totalRotation.z += (-difference);
							}
							else if (transformationType == TransformationType::SCALING)
							{
								difference = (totalScaling.z - targetTransformation.z);
								totalScaling.z += (-difference);
							}
						}

						// Transform the model
						if (transformationType == TransformationType::MOVEMENT)
						{
							_fe3d.modelEntity_move(animation.animatedModelID, Vec3(0.0f, 0.0f, finalSpeed + (-difference)), partID);
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							_fe3d.modelEntity_setRotationOrigin(animation.animatedModelID, currentModelSize * rotationOrigin, partID);
							_fe3d.modelEntity_rotate(animation.animatedModelID, Vec3(0.0f, 0.0f, finalSpeed + (-difference)), partID);
						}
						else if (transformationType == TransformationType::SCALING)
						{
							_fe3d.modelEntity_scale(animation.animatedModelID, Vec3(0.0f, 0.0f, finalSpeed + (-difference)), partID);
						}
					}
				}
			}

			// Check if animation needs to be faded
			if (animation.fadeFramestep != -1 && animation.fadeFrameIndex == -1)
			{
				if (animation.fadeFramestep == 1)
				{
					if ((animation.frameIndex % 2) != 0)
					{
						animation.fadeFrameIndex = animation.frameIndex + 1;
					}
					else
					{
						animation.fadeFrameIndex = animation.frameIndex;
					}
				}
				else
				{
					if ((animation.frameIndex % animation.fadeFramestep) == 0)
					{
						animation.fadeFrameIndex = animation.frameIndex + 1;
					}
					else
					{
						animation.fadeFrameIndex = animation.frameIndex;
					}
				}
			}

			// Check if current frame is finished
			if (finishedPartsAmount == animation.partIDs.size())
			{
				if (animation.frameIndex == animation.fadeFrameIndex) // Animation faded to its end
				{
					_animationsToStop.insert(idPair);
				}
				else if (animation.frameIndex == (static_cast<unsigned int>(animation.frames.size()) - 1)) // Animation finished normally
				{
					// Check if animation is endless
					if (animation.timesToPlay == -1)
					{
						_animationsToStop.insert(idPair);
						_animationsToStartAgain.insert(idPair);
					}
					else
					{
						// Animation finished current play
						animation.timesToPlay--;

						// Check if animation must stop
						if (animation.timesToPlay == 0)
						{
							_animationsToStop.insert(idPair);
						}
						else
						{
							animation.frameIndex = 0;
						}
					}
				}
				else // Animation not finished yet
				{
					// Auto-pause if allowed (skip default frame)
					if (animation.isAutoPaused && animation.frameIndex != 0)
					{
						animation.isPaused = true;
					}

					// Next frame
					animation.frameIndex++;
				}
			}
		}

		// Remove all animations that ended
		for (const auto& idPair : _animationsToStop)
		{
			// Check if animation is still playing
			if (isAnimationStarted(idPair.first, idPair.second))
			{
				// Stop animation
				stopAnimation(idPair.first, idPair.second);
			}
		}
		_animationsToStop.clear();

		// Start all endless animations again
		for (const auto& idPair : _animationsToStartAgain)
		{
			// Check if animation is not already playing
			if (!isAnimationStarted(idPair.first, idPair.second))
			{
				// Start animation
				startAnimation(idPair.first, idPair.second, -1);
			}
		}
		_animationsToStartAgain.clear();
	}
}