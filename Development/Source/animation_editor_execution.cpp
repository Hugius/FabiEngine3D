#include "animation_editor.hpp"

#include <set>

void AnimationEditor::_updateAnimationExecution()
{
	if (!_fe3d.engine_isPaused())
	{
		// Remove all animations that ended
		for (const auto& idPair : _animationsToStop)
		{
			// Reset all rotation origins
			for (auto partName : _playingAnimations.at(idPair).partNames)
			{
				_fe3d.gameEntity_setRotationOrigin(_playingAnimations.at(idPair).animatedModelID, Vec3(0.0f), partName);
			}

			stopAnimation(idPair.first, idPair.second);
		}
		_animationsToStop.clear();

		// Start all animations that play endlessly
		for (const auto& idPair : _animationsToStart)
		{
			startAnimation(idPair.first, idPair.second, -1);
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

			// Retrieve model size
			auto modelSize = _fe3d.gameEntity_getSize(animation.animatedModelID);

			// Retrieve current frame
			auto& frame = animation.frames[animation.frameIndex];

			// For every model part in this frame
			unsigned int finishedPartsAmount = 0;
			for (auto partName : animation.partNames)
			{
				// Check if model has part
				if (!_fe3d.gameEntity_hasPart(animation.animatedModelID, partName) && !partName.empty())
				{
					finishedPartsAmount++;
					continue;
				}

				// Immutable values
				const auto& transformationType = frame.transformationTypes[partName];
				const auto& targetTransformation = frame.targetTransformations[partName];
				const auto& speedType = frame.speedTypes[partName];
				const auto& rotationOrigin = frame.rotationOrigins[partName];
				const auto& isTranslation = (transformationType == TransformationType::TRANSLATION);
				const auto& isRotation = (transformationType == TransformationType::ROTATION);
				const auto& isScaling = (transformationType == TransformationType::SCALING);
				const auto& speed = frame.speeds[partName] * animation.speedMultiplier;

				// Mutable values
				auto& totalTranslation = animation.totalTranslations[partName];
				auto& totalRotation = animation.totalRotations[partName];
				auto& totalScaling = animation.totalScalings[partName];
				auto& baseSpeed = frame.speeds[partName];

				// Check if reached transformation of current frame
				if (((isTranslation && _hasReachedFloat(totalTranslation.x, targetTransformation.x, speed)) &&
					(isTranslation && _hasReachedFloat(totalTranslation.y, targetTransformation.y, speed)) &&
					(isTranslation && _hasReachedFloat(totalTranslation.z, targetTransformation.z, speed))) ||
					((isRotation && _hasReachedFloat(totalRotation.x, targetTransformation.x, speed)) &&
						(isRotation && _hasReachedFloat(totalRotation.y, targetTransformation.y, speed)) &&
						(isRotation && _hasReachedFloat(totalRotation.z, targetTransformation.z, speed))) ||
					((isScaling && _hasReachedFloat(totalScaling.x, targetTransformation.x, speed)) &&
						(isScaling && _hasReachedFloat(totalScaling.y, targetTransformation.y, speed)) &&
						(isScaling && _hasReachedFloat(totalScaling.z, targetTransformation.z, speed))))
				{
					finishedPartsAmount++;
				}
				else
				{
					// X transformation
					if ((isTranslation && !_hasReachedFloat(totalTranslation.x, targetTransformation.x, speed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.x, targetTransformation.x, speed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.x, targetTransformation.x, speed)))
					{
						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							totalTranslation.x += speed;
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							totalRotation.x += speed;
						}
						else if (transformationType == TransformationType::SCALING)
						{
							totalScaling.x += speed;
						}

						// Increase speed if exponential
						if (speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed += (baseSpeed / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isTranslation && _hasReachedFloat(totalTranslation.x, targetTransformation.x, speed)) ||
							(isRotation && _hasReachedFloat(totalRotation.x, targetTransformation.x, speed)) ||
							(isScaling && _hasReachedFloat(totalScaling.x, targetTransformation.x, speed)))
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
							_fe3d.gameEntity_move(animation.animatedModelID, Vec3(speed + (-difference), 0.0f, 0.0f), partName);
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							_fe3d.gameEntity_setRotationOrigin(animation.animatedModelID, modelSize * rotationOrigin, partName);
							_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(speed + (-difference), 0.0f, 0.0f), partName);
						}
						else if (transformationType == TransformationType::SCALING)
						{
							_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(speed + (-difference), 0.0f, 0.0f), partName);
						}
					}

					// Y transformation
					if ((isTranslation && !_hasReachedFloat(totalTranslation.y, targetTransformation.y, speed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.y, targetTransformation.y, speed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.y, targetTransformation.y, speed)))
					{
						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							totalTranslation.y += speed;
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							totalRotation.y += speed;
						}
						else if (transformationType == TransformationType::SCALING)
						{
							totalScaling.y += speed;
						}

						// Increase speed if exponential
						if (speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed += (baseSpeed / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isTranslation && _hasReachedFloat(totalTranslation.y, targetTransformation.y, speed)) |
							(isRotation && _hasReachedFloat(totalRotation.y, targetTransformation.y, speed)) |
							(isScaling && _hasReachedFloat(totalScaling.y, targetTransformation.y, speed)))
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
							_fe3d.gameEntity_move(animation.animatedModelID, Vec3(0.0f, speed + (-difference), 0.0f), partName);
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							_fe3d.gameEntity_setRotationOrigin(animation.animatedModelID, modelSize * rotationOrigin, partName);
							_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, speed + (-difference), 0.0f), partName);
						}
						else if (transformationType == TransformationType::SCALING)
						{
							_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(0.0f, speed + (-difference), 0.0f), partName);
						}
					}

					// Z transformation
					if ((isTranslation && !_hasReachedFloat(totalTranslation.z, targetTransformation.z, speed)) ||
						(isRotation && !_hasReachedFloat(totalRotation.z, targetTransformation.z, speed)) ||
						(isScaling && !_hasReachedFloat(totalScaling.z, targetTransformation.z, speed)))
					{
						// Determine transformation type
						if (transformationType == TransformationType::TRANSLATION)
						{
							totalTranslation.z += speed;
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							totalRotation.z += speed;
						}
						else if (transformationType == TransformationType::SCALING)
						{
							totalScaling.z += speed;
						}

						// Increase speed if exponential
						if (speedType == AnimationSpeedType::EXPONENTIAL)
						{
							baseSpeed += (baseSpeed / 100.0f);
						}

						// Check if animation reached transformation now
						float difference = 0.0f;
						if ((isTranslation && _hasReachedFloat(totalTranslation.z, targetTransformation.z, speed)) ||
							(isRotation && _hasReachedFloat(totalRotation.z, targetTransformation.z, speed)) ||
							(isScaling && _hasReachedFloat(totalScaling.z, targetTransformation.z, speed)))
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
							_fe3d.gameEntity_move(animation.animatedModelID, Vec3(0.0f, 0.0f, speed + (-difference)), partName);
						}
						else if (transformationType == TransformationType::ROTATION)
						{
							_fe3d.gameEntity_setRotationOrigin(animation.animatedModelID, modelSize * rotationOrigin, partName);
							_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, 0.0f, speed + (-difference)), partName);
						}
						else if (transformationType == TransformationType::SCALING)
						{
							_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(0.0f, 0.0f, speed + (-difference)), partName);
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
					_animationsToStop.push_back(idPair);
				}
				else
				{
					// Next frame or reset animation
					if (animation.frameIndex >= animation.frames.size() - 1)
					{
						// Playing endlessly
						if (animation.timesToPlay == -1)
						{
							_animationsToStop.push_back(idPair);
							_animationsToStart.push_back(idPair);
							continue;
						}

						// Played animation once
						animation.timesToPlay--;

						// Check if animation has ended
						if (animation.timesToPlay == 0)
						{
							_animationsToStop.push_back(idPair);
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