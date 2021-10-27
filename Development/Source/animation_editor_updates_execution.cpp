#include "animation_editor.hpp"

void AnimationEditor::_updateAnimationExecution()
{
	if(!_fe3d.application_isPaused())
	{
		// Update all playing animations
		for(auto& [idPair, animation] : _startedAnimations)
		{
			// Skip paused animations
			if(animation.isPaused())
			{
				continue;
			}

			// Showing frame index
			if(_isEditorLoaded)
			{
				_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("animationFrame")->getEntityID(), "Frame: " + to_string(animation.getFrameIndex() + 1), 0.025f);
			}

			// Retrieve current frame
			const auto frameIndex = animation.getFrameIndex();
			auto frame = animation.getFrames()[frameIndex];

			// For every model part in this frame
			unsigned int finishedPartCount = 0;
			for(auto partID : animation.getPartIDs())
			{
				// Check if model still exists
				if(!_fe3d.modelEntity_isExisting(animation.getAnimatedModelID()))
				{
					break;
				}

				// Mutable values
				auto totalMovement = animation.getTotalMovements().at(partID);
				auto totalRotation = animation.getTotalRotations().at(partID);
				auto totalScaling = animation.getTotalScalings().at(partID);
				auto baseSpeed = frame.getSpeeds().at(partID);

				// Immutable values
				const auto currentModelSize = _fe3d.modelEntity_getBaseSize(animation.getAnimatedModelID());
				const auto transformationType = frame.getTransformationTypes().at(partID);
				const auto isMovement = (transformationType == TransformationType::MOVEMENT);
				const auto isRotation = (transformationType == TransformationType::ROTATION);
				const auto isScaling = (transformationType == TransformationType::SCALING);
				const auto speedMultiplier = (partID.empty() || (isMovement || isScaling)) ? animation.getInitialSize() : Vec3(1.0f);
				const auto speedType = frame.getSpeedTypes().at(partID);
				const auto rotationOrigin = frame.getRotationOrigins().at(partID);
				const auto currentSpeed = (frame.getSpeeds().at(partID) * animation.getSpeedMultiplier());
				const auto xSpeed = (!isRotation ? (speedMultiplier.x * currentSpeed.x) : currentSpeed.x);
				const auto ySpeed = (!isRotation ? (speedMultiplier.y * currentSpeed.y) : currentSpeed.y);
				const auto zSpeed = (!isRotation ? (speedMultiplier.z * currentSpeed.z) : currentSpeed.z);
				const auto targetMovement = (animation.getInitialSize() * frame.getTargetTransformations().at(partID));
				const auto targetRotation = frame.getTargetTransformations().at(partID);
				const auto targetScaling = ((partID.empty() ? animation.getInitialSize() : Vec3(1.0f)) * frame.getTargetTransformations().at(partID));
				const auto targetTransformation = (isMovement ? targetMovement : isRotation ? targetRotation : targetScaling);

				// Check if reached transformation of current frame
				if(((isMovement && _hasReachedFloat(totalMovement.x, targetTransformation.x, xSpeed)) &&
				   (isMovement && _hasReachedFloat(totalMovement.y, targetTransformation.y, xSpeed)) &&
				   (isMovement && _hasReachedFloat(totalMovement.z, targetTransformation.z, xSpeed)))
				   ||
				   ((isRotation && _hasReachedFloat(totalRotation.x, targetTransformation.x, ySpeed)) &&
				   (isRotation && _hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) &&
				   (isRotation && _hasReachedFloat(totalRotation.z, targetTransformation.z, ySpeed)))
				   ||
				   ((isScaling && _hasReachedFloat(totalScaling.x, targetTransformation.x, zSpeed)) &&
				   (isScaling && _hasReachedFloat(totalScaling.y, targetTransformation.y, zSpeed)) &&
				   (isScaling && _hasReachedFloat(totalScaling.z, targetTransformation.z, zSpeed))))
				{
					finishedPartCount++;
				}
				else
				{
					// X transformation
					if((isMovement && !_hasReachedFloat(totalMovement.x, targetTransformation.x, xSpeed)) ||
					   (isRotation && !_hasReachedFloat(totalRotation.x, targetTransformation.x, xSpeed)) ||
					   (isScaling && !_hasReachedFloat(totalScaling.x, targetTransformation.x, xSpeed)))
					{
						// Final transformation speed
						float finalSpeed = xSpeed;

						// Determine transformation type
						if(transformationType == TransformationType::MOVEMENT)
						{
							// Instant speed means the whole transformation in one go
							if(speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalMovement.x);
							}

							totalMovement.x += finalSpeed;
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							// Instant speed means the whole transformation in one go
							if(speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalRotation.x);
							}

							totalRotation.x += finalSpeed;
						}
						else if(transformationType == TransformationType::SCALING)
						{
							// Instant speed means the whole transformation in one go
							if(speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalScaling.x);
							}

							totalScaling.x += finalSpeed;
						}

						// Increase speed if exponential
						if(speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed.x += (baseSpeed.x / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if((isMovement && _hasReachedFloat(totalMovement.x, targetTransformation.x, xSpeed)) ||
						   (isRotation && _hasReachedFloat(totalRotation.x, targetTransformation.x, xSpeed)) ||
						   (isScaling && _hasReachedFloat(totalScaling.x, targetTransformation.x, xSpeed)))
						{
							// Determine transformation type
							if(transformationType == TransformationType::MOVEMENT)
							{
								difference = (totalMovement.x - targetTransformation.x);
								totalMovement.x -= difference;
							}
							else if(transformationType == TransformationType::ROTATION)
							{
								difference = (totalRotation.x - targetTransformation.x);
								totalRotation.x -= difference;
							}
							else if(transformationType == TransformationType::SCALING)
							{
								difference = (totalScaling.x - targetTransformation.x);
								totalScaling.x -= difference;
							}
						}

						// Transform the model
						if(transformationType == TransformationType::MOVEMENT)
						{
							if(partID.empty()) // Base position
							{
								_fe3d.modelEntity_moveBase(animation.getAnimatedModelID(), Vec3((finalSpeed - difference), 0.0f, 0.0f));
							}
							else // Part position
							{
								_fe3d.modelEntity_movePart(animation.getAnimatedModelID(), partID, Vec3((finalSpeed - difference), 0.0f, 0.0f));
							}
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							if(partID.empty()) // Base rotation
							{
								_fe3d.modelEntity_setBaseRotationOrigin(animation.getAnimatedModelID(), (currentModelSize * rotationOrigin));
								_fe3d.modelEntity_rotateBase(animation.getAnimatedModelID(), Vec3((finalSpeed - difference), 0.0f, 0.0f));
							}
							else // Part rotation
							{
								_fe3d.modelEntity_setPartRotationOrigin(animation.getAnimatedModelID(), partID, (currentModelSize * rotationOrigin));
								_fe3d.modelEntity_rotatePart(animation.getAnimatedModelID(), partID, Vec3((finalSpeed - difference), 0.0f, 0.0f));
							}
						}
						else if(transformationType == TransformationType::SCALING)
						{
							if(partID.empty()) // Base size
							{
								_fe3d.modelEntity_scaleBase(animation.getAnimatedModelID(), Vec3((finalSpeed - difference), 0.0f, 0.0f));
							}
							else // Part size
							{
								_fe3d.modelEntity_scalePart(animation.getAnimatedModelID(), partID, Vec3((finalSpeed - difference), 0.0f, 0.0f));
							}
						}
					}

					// Y transformation
					if((isMovement && !_hasReachedFloat(totalMovement.y, targetTransformation.y, ySpeed)) ||
					   (isRotation && !_hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) ||
					   (isScaling && !_hasReachedFloat(totalScaling.y, targetTransformation.y, ySpeed)))
					{
						// Final transformation speed
						float finalSpeed = ySpeed;

						// Determine transformation type
						if(transformationType == TransformationType::MOVEMENT)
						{
							// Instant speed means the whole transformation in one go
							if(speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalMovement.y);
							}

							totalMovement.y += finalSpeed;
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							// Instant speed means the whole transformation in one go
							if(speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalRotation.y);
							}

							totalRotation.y += finalSpeed;
						}
						else if(transformationType == TransformationType::SCALING)
						{
							// Instant speed means the whole transformation in one go
							if(speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalScaling.y);
							}

							totalScaling.y += finalSpeed;
						}

						// Increase speed if exponential
						if(speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed.y += (baseSpeed.y / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if((isMovement && _hasReachedFloat(totalMovement.y, targetTransformation.y, ySpeed)) ||
						   (isRotation && _hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) ||
						   (isScaling && _hasReachedFloat(totalScaling.y, targetTransformation.y, ySpeed)))
						{
							// Determine transformation type
							if(transformationType == TransformationType::MOVEMENT)
							{
								difference = (totalMovement.y - targetTransformation.y);
								totalMovement.y -= difference;
							}
							else if(transformationType == TransformationType::ROTATION)
							{
								difference = (totalRotation.y - targetTransformation.y);
								totalRotation.y -= difference;
							}
							else if(transformationType == TransformationType::SCALING)
							{
								difference = (totalScaling.y - targetTransformation.y);
								totalScaling.y -= difference;
							}
						}

						// Transform the model
						if(transformationType == TransformationType::MOVEMENT)
						{
							if(partID.empty()) // Base position
							{
								_fe3d.modelEntity_moveBase(animation.getAnimatedModelID(), Vec3(0.0f, (finalSpeed - difference), 0.0f));
							}
							else // Part position
							{
								_fe3d.modelEntity_movePart(animation.getAnimatedModelID(), partID, Vec3(0.0f, (finalSpeed - difference), 0.0f));
							}
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							if(partID.empty()) // Base rotation
							{
								_fe3d.modelEntity_setBaseRotationOrigin(animation.getAnimatedModelID(), (currentModelSize * rotationOrigin));
								_fe3d.modelEntity_rotateBase(animation.getAnimatedModelID(), Vec3(0.0f, (finalSpeed - difference), 0.0f));
							}
							else // Part rotation
							{
								_fe3d.modelEntity_setPartRotationOrigin(animation.getAnimatedModelID(), partID, (currentModelSize * rotationOrigin));
								_fe3d.modelEntity_rotatePart(animation.getAnimatedModelID(), partID, Vec3(0.0f, (finalSpeed - difference), 0.0f));
							}
						}
						else if(transformationType == TransformationType::SCALING)
						{
							if(partID.empty()) // Base size
							{
								_fe3d.modelEntity_scaleBase(animation.getAnimatedModelID(), Vec3(0.0f, (finalSpeed - difference), 0.0f));
							}
							else // Part size
							{
								_fe3d.modelEntity_scalePart(animation.getAnimatedModelID(), partID, Vec3(0.0f, (finalSpeed - difference), 0.0f));
							}
						}
					}

					// Z transformation
					if((isMovement && !_hasReachedFloat(totalMovement.z, targetTransformation.z, zSpeed)) ||
					   (isRotation && !_hasReachedFloat(totalRotation.z, targetTransformation.z, zSpeed)) ||
					   (isScaling && !_hasReachedFloat(totalScaling.z, targetTransformation.z, zSpeed)))
					{
						// Final transformation speed
						float finalSpeed = zSpeed;

						// Determine transformation type
						if(transformationType == TransformationType::MOVEMENT)
						{
							// Instant speed means the whole transformation in one go
							if(speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalMovement.z);
							}

							totalMovement.z += finalSpeed;
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							// Instant speed means the whole transformation in one go
							if(speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalRotation.z);
							}

							totalRotation.z += finalSpeed;
						}
						else if(transformationType == TransformationType::SCALING)
						{
							// Instant speed means the whole transformation in one go
							if(speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalScaling.z);
							}

							totalScaling.z += finalSpeed;
						}

						// Increase speed if exponential
						if(speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed.z += (baseSpeed.z / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if((isMovement && _hasReachedFloat(totalMovement.z, targetTransformation.z, finalSpeed)) ||
						   (isRotation && _hasReachedFloat(totalRotation.z, targetTransformation.z, finalSpeed)) ||
						   (isScaling && _hasReachedFloat(totalScaling.z, targetTransformation.z, finalSpeed)))
						{
							// Determine transformation type
							if(transformationType == TransformationType::MOVEMENT)
							{
								difference = (totalMovement.z - targetTransformation.z);
								totalMovement.z -= difference;
							}
							else if(transformationType == TransformationType::ROTATION)
							{
								difference = (totalRotation.z - targetTransformation.z);
								totalRotation.z -= difference;
							}
							else if(transformationType == TransformationType::SCALING)
							{
								difference = (totalScaling.z - targetTransformation.z);
								totalScaling.z -= difference;
							}
						}

						// Transform the model
						if(transformationType == TransformationType::MOVEMENT)
						{
							if(partID.empty()) // Base position
							{
								_fe3d.modelEntity_moveBase(animation.getAnimatedModelID(), Vec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
							else // Part position
							{
								_fe3d.modelEntity_movePart(animation.getAnimatedModelID(), partID, Vec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							if(partID.empty()) // Base rotation
							{
								_fe3d.modelEntity_setBaseRotationOrigin(animation.getAnimatedModelID(), (currentModelSize * rotationOrigin));
								_fe3d.modelEntity_rotateBase(animation.getAnimatedModelID(), Vec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
							else // Part rotation
							{
								_fe3d.modelEntity_setPartRotationOrigin(animation.getAnimatedModelID(), partID, (currentModelSize * rotationOrigin));
								_fe3d.modelEntity_rotatePart(animation.getAnimatedModelID(), partID, Vec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
						}
						else if(transformationType == TransformationType::SCALING)
						{
							if(partID.empty()) // Base size
							{
								_fe3d.modelEntity_scaleBase(animation.getAnimatedModelID(), Vec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
							else // Part size
							{
								_fe3d.modelEntity_scalePart(animation.getAnimatedModelID(), partID, Vec3(0.0f, 0.0f, (finalSpeed - difference)));
							}

						}
					}
				}

				// Update animation values
				animation.setTotalMovement(partID, totalMovement);
				animation.setTotalRotation(partID, totalRotation);
				animation.setTotalScaling(partID, totalScaling);

				// Update frame values
				frame.setSpeed(partID, baseSpeed);
			}

			// Update frame
			animation.setFrame(frameIndex, frame);

			// Check if animation needs to be faded
			if(animation.getFadeFramestep() != -1 && animation.getFadeFrameIndex() == -1)
			{
				if(animation.getFadeFramestep() == 1)
				{
					if((animation.getFrameIndex() % 2) != 0)
					{
						animation.setFadeFrameIndex(animation.getFrameIndex() + 1);
					}
					else
					{
						animation.setFadeFrameIndex(animation.getFrameIndex());
					}
				}
				else
				{
					if((animation.getFrameIndex() % animation.getFadeFramestep()) == 0)
					{
						animation.setFadeFrameIndex(animation.getFrameIndex() + 1);
					}
					else
					{
						animation.setFadeFrameIndex(animation.getFrameIndex());
					}
				}
			}

			// Check if current frame is finished
			if(finishedPartCount == animation.getPartIDs().size())
			{
				if(animation.getFrameIndex() == animation.getFadeFrameIndex()) // Animation faded to its end
				{
					_animationsToStop.insert(idPair);
				}
				else if(animation.getFrameIndex() == (static_cast<unsigned int>(animation.getFrames().size()) - 1)) // Animation finished
				{
					// Check if animation is endless
					if(animation.getTimesToPlay() == -1)
					{
						_animationsToStop.insert(idPair);
						_animationsToStartAgain.insert(idPair);
					}
					else
					{
						// Animation finished current play
						animation.setTimesToPlay(animation.getTimesToPlay() - 1);

						// Check if animation must stop
						if(animation.getTimesToPlay() == 0)
						{
							_animationsToStop.insert(idPair);
						}
						else
						{
							animation.setFrameIndex(0);
						}
					}
				}
				else // Animation not finished yet
				{
					// Auto-pause if allowed (skip default frame)
					if(animation.isAutoPaused() && animation.getFrameIndex() != 0)
					{
						animation.setPaused(true);
					}

					// Next frame
					animation.setFrameIndex(animation.getFrameIndex() + 1);
				}
			}
		}

		// Remove all animations that ended
		for(const auto& idPair : _animationsToStop)
		{
			// Check if animation is still playing
			if(isAnimationStarted(idPair.first, idPair.second))
			{
				// Stop animation
				stopAnimation(idPair.first, idPair.second);
			}
		}
		_animationsToStop.clear();

		// Start all endless animations again
		for(const auto& idPair : _animationsToStartAgain)
		{
			// Check if animation is not already playing
			if(!isAnimationStarted(idPair.first, idPair.second))
			{
				// Start animation
				startAnimation(idPair.first, idPair.second, -1);
			}
		}
		_animationsToStartAgain.clear();
	}
}