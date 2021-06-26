#include "animation_editor.hpp"

#include <set>

void AnimationEditor::_updateAnimationExecution()
{
	if (!_fe3d.engine_isPaused())
	{
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

		// Start all animations that play endlessly
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
				const auto& isTranslation = (transformationType == TransformationType::TRANSLATION);
				const auto& isRotation = (transformationType == TransformationType::ROTATION);
				const auto& isScaling = (transformationType == TransformationType::SCALING);
				const auto& speedMultiplier = (partID.empty() || (isTranslation || isScaling)) ? animation.initialScaling : Vec3(1.0f);
				const auto& speedType = frame.speedTypes[partID];
				const auto& rotationOrigin = frame.rotationOrigins[partID];
				const auto& speed = frame.speeds[partID] * animation.speedMultiplier;
				const auto& xSpeed = !isRotation ? (speedMultiplier.x * speed.x) : speed.x;
				const auto& ySpeed = !isRotation ? (speedMultiplier.y * speed.y) : speed.y;
				const auto& zSpeed = !isRotation ? (speedMultiplier.z * speed.z) : speed.z;

				// Translation is relative to initial size
				// Rotation is always relative to real-time size
				// Scaling is relative to initial size
				const auto& targetTransformation =
					isTranslation ? (animation.initialScaling * frame.targetTransformations[partID]) :
					isRotation ? frame.targetTransformations[partID] :
					((partID.empty() ? animation.initialScaling : Vec3(1.0f)) * frame.targetTransformations[partID]);

				// Mutable values
				auto& totalTranslation = animation.totalTranslations[partID];
				auto& totalRotation = animation.totalRotations[partID];
				auto& totalScaling = animation.totalScalings[partID];
				auto& baseSpeed = frame.speeds[partID];

				// Check if reached transformation of current frame
				if (((isTranslation && _hasReachedFloat(totalTranslation.x, targetTransformation.x, xSpeed)) &&
					(isTranslation && _hasReachedFloat(totalTranslation.y, targetTransformation.y, xSpeed)) &&
					(isTranslation && _hasReachedFloat(totalTranslation.z, targetTransformation.z, xSpeed))) ||
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
					if ((isTranslation && !_hasReachedFloat(totalTranslation.x, targetTransformation.x, xSpeed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.x, targetTransformation.x, xSpeed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.x, targetTransformation.x, xSpeed)))
					{
						// Final transformation speed
						float finalSpeed = xSpeed;

						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalTranslation.x);
							}

							totalTranslation.x += finalSpeed;
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
							baseSpeed += (baseSpeed / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isTranslation && _hasReachedFloat(totalTranslation.x, targetTransformation.x, xSpeed)) ||
							(isRotation && _hasReachedFloat(totalRotation.x, targetTransformation.x, xSpeed)) ||
							(isScaling && _hasReachedFloat(totalScaling.x, targetTransformation.x, xSpeed)))
						{
							// Determine transformation type
							if (transformationType == TransformationType::TRANSLATION)
							{
								difference = totalTranslation.x - targetTransformation.x;
								totalTranslation.x += (-difference);
							}
							else if (transformationType == TransformationType::ROTATION)
							{
								difference = totalRotation.x - targetTransformation.x;
								totalRotation.x += (-difference);
							}
							else if (transformationType == TransformationType::SCALING)
							{
								difference = totalScaling.x - targetTransformation.x;
								totalScaling.x += (-difference);
							}
						}

						// Transform the model
						if (transformationType == TransformationType::TRANSLATION)
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
					if ((isTranslation && !_hasReachedFloat(totalTranslation.y, targetTransformation.y, ySpeed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.y, targetTransformation.y, ySpeed)))
					{
						// Final transformation speed
						float finalSpeed = ySpeed;

						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalTranslation.y);
							}

							totalTranslation.y += finalSpeed;
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
							baseSpeed += (baseSpeed / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isTranslation && _hasReachedFloat(totalTranslation.y, targetTransformation.y, ySpeed)) ||
							(isRotation && _hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) ||
							(isScaling && _hasReachedFloat(totalScaling.y, targetTransformation.y, ySpeed)))
						{
							// Determine transformation type
							if (transformationType == TransformationType::TRANSLATION)
							{
								difference = (totalTranslation.y - targetTransformation.y);
								totalTranslation.y += (-difference);
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
						if (transformationType == TransformationType::TRANSLATION)
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
					if ((isTranslation && !_hasReachedFloat(totalTranslation.z, targetTransformation.z, zSpeed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.z, targetTransformation.z, zSpeed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.z, targetTransformation.z, zSpeed)))
					{
						// Final transformation speed
						float finalSpeed = zSpeed;

						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							// Instant speed means the whole transformation in one go
							if (speedType == AnimationSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalTranslation.z);
							}

							totalTranslation.z += finalSpeed;
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
							baseSpeed += (baseSpeed / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isTranslation && _hasReachedFloat(totalTranslation.z, targetTransformation.z, finalSpeed)) ||
							(isRotation && _hasReachedFloat(totalRotation.z, targetTransformation.z, finalSpeed)) ||
							(isScaling && _hasReachedFloat(totalScaling.z, targetTransformation.z, finalSpeed)))
						{
							// Determine transformation type
							if (transformationType == TransformationType::TRANSLATION)
							{
								difference = (totalTranslation.z - targetTransformation.z);
								totalTranslation.z += (-difference);
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
						if (transformationType == TransformationType::TRANSLATION)
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
				// Check if animation fading is enabled
				if (animation.fadeFrameIndex != -1)
				{
					// Check if animation faded to its end
					if (animation.frameIndex == animation.fadeFrameIndex)
					{
						_animationsToStop.insert(idPair);
					}
				}
				else
				{
					// Temporary values
					unsigned int lastFrameIndex = (static_cast<unsigned int>(animation.frames.size()) - 1);

					if (!animation.isDirectionReversed && (animation.frameIndex == lastFrameIndex)) // Normal animation finish
					{
						// Check if animation is endless
						if (animation.timesToPlay == -1)
						{
							animation.frameIndex = 0;
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
					else if (animation.isDirectionReversed && (animation.frameIndex == 0)) // Reverse animation finish
					{
						// Check if animation is endless
						if (animation.timesToPlay == -1)
						{
							animation.frameIndex = lastFrameIndex;
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
								animation.frameIndex = lastFrameIndex;
							}
						}
					}
					else // Animation not finished yet
					{
						// Auto-pause if allowed
						if (animation.isAutoPaused)
						{
							// Skip default frame
							if ((!animation.isDirectionReversed && (animation.frameIndex != 0)) ||
								(animation.isDirectionReversed && (animation.frameIndex != lastFrameIndex)))
							{
								animation.isPaused = true;
							}
						}

						// Next frame
						if (animation.isDirectionReversed)
						{
							animation.frameIndex--;
						}
						else
						{
							animation.frameIndex++;
						}
					}
				}
			}
		}
	}
}