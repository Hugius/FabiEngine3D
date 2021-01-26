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
				// Reset all rotation origins
				auto animation = _playingAnimations.at(idPair);
				for (auto partName : animation.partNames)
				{
					// Check if model still exists
					if (_fe3d.gameEntity_isExisting(animation.animatedModelID))
					{
						// Check if model has part
						if (_fe3d.gameEntity_hasPart(animation.animatedModelID, partName) || partName.empty())
						{
							_fe3d.gameEntity_setRotationOrigin(animation.animatedModelID, Vec3(0.0f), partName);
						}
					}
				}

				// Stop animation
				stopAnimation(idPair.first, idPair.second);
			}
		}
		_animationsToStop.clear();

		// Start all animations that play endlessly
		for (const auto& idPair : _animationsToStart)
		{
			// Check if animation is not already playing
			if (!isAnimationStarted(idPair.first, idPair.second))
			{
				startAnimation(idPair.first, idPair.second, -1);
			}
		}
		_animationsToStart.clear();

		// Update all playing animations
		for (auto& [idPair, animation] : _playingAnimations)
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
			for (auto partName : animation.partNames)
			{
				// Check if model still exists
				if (!_fe3d.gameEntity_isExisting(animation.animatedModelID))
				{
					break;
				}

				// Immutable values
				const auto& currentModelSize = _fe3d.gameEntity_getSize(animation.animatedModelID);
				const auto& transformationType = frame.transformationTypes[partName];
				const auto& isTranslation = (transformationType == TransformationType::TRANSLATION);
				const auto& isRotation = (transformationType == TransformationType::ROTATION);
				const auto& isScaling = (transformationType == TransformationType::SCALING);
				const auto& speedMultiplier = (partName.empty() || (isTranslation || isScaling)) ? animation.initialScaling : Vec3(1.0f);
				const auto& speedType = frame.speedTypes[partName];
				const auto& rotationOrigin = frame.rotationOrigins[partName];
				const auto& speed = frame.speeds[partName] * animation.speedMultiplier;
				const auto& xSpeed = !isRotation ? (speedMultiplier.x * speed) : speed;
				const auto& ySpeed = !isRotation ? (speedMultiplier.y * speed) : speed;
				const auto& zSpeed = !isRotation ? (speedMultiplier.z * speed) : speed;

				// Translation is relative to initial size
				// Rotation is always relative to real-time size
				// Scaling is relative to initial size
				const auto& targetTransformation =
					isTranslation ? (animation.initialScaling * frame.targetTransformations[partName]) :
					isRotation ? frame.targetTransformations[partName] :
					((partName.empty() ? animation.initialScaling : Vec3(1.0f)) * frame.targetTransformations[partName]);

				// Mutable values
				auto& totalTranslation = animation.totalTranslations[partName];
				auto& totalRotation = animation.totalRotations[partName];
				auto& totalScaling = animation.totalScalings[partName];
				auto& baseSpeed = frame.speeds[partName];

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
						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							totalTranslation.x += xSpeed;
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							totalRotation.x += xSpeed;
						}
						else if (transformationType == TransformationType::SCALING)
						{
							totalScaling.x += xSpeed;
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

						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							_fe3d.gameEntity_move(animation.animatedModelID, Vec3(xSpeed + (-difference), 0.0f, 0.0f), partName);
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							_fe3d.gameEntity_setRotationOrigin(animation.animatedModelID, currentModelSize * rotationOrigin, partName);
							_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(xSpeed + (-difference), 0.0f, 0.0f), partName);
						}
						else if (transformationType == TransformationType::SCALING)
						{
							_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(xSpeed + (-difference), 0.0f, 0.0f), partName);
						}
					}

					// Y transformation
					if ((isTranslation && !_hasReachedFloat(totalTranslation.y, targetTransformation.y, ySpeed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.y, targetTransformation.y, ySpeed)))
					{
						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							totalTranslation.y += ySpeed;
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							totalRotation.y += ySpeed;
						}
						else if (transformationType == TransformationType::SCALING)
						{
							totalScaling.y += ySpeed;
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
								difference = totalTranslation.y - targetTransformation.y;
								totalTranslation.y += (-difference);
							}
							else if (transformationType == TransformationType::ROTATION)
							{
								difference = totalRotation.y - targetTransformation.y;
								totalRotation.y += (-difference);
							}
							else if (transformationType == TransformationType::SCALING)
							{
								difference = totalScaling.y - targetTransformation.y;
								totalScaling.y += (-difference);
							}
						}

						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							_fe3d.gameEntity_move(animation.animatedModelID, Vec3(0.0f, ySpeed + (-difference), 0.0f), partName);
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							_fe3d.gameEntity_setRotationOrigin(animation.animatedModelID, currentModelSize * rotationOrigin, partName);
							_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, ySpeed + (-difference), 0.0f), partName);
						}
						else if (transformationType == TransformationType::SCALING)
						{
							_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(0.0f, ySpeed + (-difference), 0.0f), partName);
						}
					}

					// Z transformation
					if ((isTranslation && !_hasReachedFloat(totalTranslation.z, targetTransformation.z, zSpeed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.z, targetTransformation.z, zSpeed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.z, targetTransformation.z, zSpeed)))
					{
						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							totalTranslation.z += zSpeed;
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							totalRotation.z += zSpeed;
						}
						else if (transformationType == TransformationType::SCALING)
						{
							totalScaling.z += zSpeed;
						}

						// Increase speed if exponential
						if (speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed += (baseSpeed / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isTranslation && _hasReachedFloat(totalTranslation.z, targetTransformation.z, zSpeed)) ||
							(isRotation && _hasReachedFloat(totalRotation.z, targetTransformation.z, zSpeed)) ||
							(isScaling && _hasReachedFloat(totalScaling.z, targetTransformation.z, zSpeed)))
						{
							// Determine transformation type
							if (transformationType == TransformationType::TRANSLATION)
							{
								difference = totalTranslation.z - targetTransformation.z;
								totalTranslation.z += (-difference);
							}
							else if (transformationType == TransformationType::ROTATION)
							{
								difference = totalRotation.z - targetTransformation.z;
								totalRotation.z += (-difference);
							}
							else if (transformationType == TransformationType::SCALING)
							{
								difference = totalScaling.z - targetTransformation.z;
								totalScaling.z += (-difference);
							}
						}

						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							_fe3d.gameEntity_move(animation.animatedModelID, Vec3(0.0f, 0.0f, zSpeed + (-difference)), partName);
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							_fe3d.gameEntity_setRotationOrigin(animation.animatedModelID, currentModelSize * rotationOrigin, partName);
							_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, 0.0f, zSpeed + (-difference)), partName);
						}
						else if (transformationType == TransformationType::SCALING)
						{
							_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(0.0f, 0.0f, zSpeed + (-difference)), partName);
						}
					}
				}
			}

			// Check if animation needs to be faded
			if (animation.fadeFramestep != -1 && animation.maxFrameIndex == -1)
			{
				if (animation.fadeFramestep == 1)
				{
					if ((animation.frameIndex % 2) != 0)
					{
						animation.maxFrameIndex = animation.frameIndex + 1;
					}
					else
					{
						animation.maxFrameIndex = animation.frameIndex;
					}
				}
				else
				{
					if ((animation.frameIndex % animation.fadeFramestep) == 0)
					{
						animation.maxFrameIndex = animation.frameIndex + 1;
					}
					else
					{
						animation.maxFrameIndex = animation.frameIndex;
					}
				}
			}

			// Check if current frame is finished
			if (finishedPartsAmount == animation.partNames.size())
			{
				// Check if animation faded to its end
				if (animation.frameIndex == animation.maxFrameIndex)
				{
					_animationsToStop.insert(idPair);
				}
				else
				{
					// Next frame or reset animation
					if (animation.frameIndex >= animation.frames.size() - 1)
					{
						// Playing endlessly
						if (animation.timesToPlay == -1)
						{
							_animationsToStop.insert(idPair);
							_animationsToStart.insert(idPair);
							continue;
						}

						// Played animation once
						animation.timesToPlay--;

						// Check if animation has ended
						if (animation.timesToPlay == 0)
						{
							_animationsToStop.insert(idPair);
						}
						else
						{
							animation.frameIndex = 0;
						}
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