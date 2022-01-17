#include "animation3d_editor.hpp"

void Animation3dEditor::_updateModelAnimationExecution()
{
	if(!_fe3d->application_isPaused())
	{
		for(auto& [key, animation] : _startedModelAnimations)
		{
			if(animation.isPaused())
			{
				continue;
			}

			if(_isEditorLoaded)
			{
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("animationFrame")->getEntityID(), "Frame: " + to_string(animation.getFrameIndex() + 1), 0.025f);
			}

			const auto frameIndex = animation.getFrameIndex();
			auto frame = animation.getFrames()[frameIndex];

			unsigned int finishedPartCount = 0;
			for(const auto& partID : animation.getPartIDs())
			{
				if(!_fe3d->model_isExisting(key.second))
				{
					break;
				}

				auto totalMovement = animation.getTotalMovements().at(partID);
				auto totalRotation = animation.getTotalRotations().at(partID);
				auto totalScaling = animation.getTotalScalings().at(partID);
				auto baseSpeed = frame.getSpeeds().at(partID);

				const auto currentModelSize = _fe3d->model_getBaseSize(key.second);
				const auto transformationType = frame.getTransformationTypes().at(partID);
				const auto isMovement = (transformationType == TransformationType::MOVEMENT);
				const auto isRotation = (transformationType == TransformationType::ROTATION);
				const auto isScaling = (transformationType == TransformationType::SCALING);
				const auto speedMultiplier = (partID.empty() || (isMovement || isScaling)) ? animation.getInitialSize() : fvec3(1.0f);
				const auto speedType = frame.getSpeedTypes().at(partID);
				const auto rotationOrigin = frame.getRotationOrigins().at(partID);
				const auto currentSpeed = (frame.getSpeeds().at(partID) * animation.getSpeed());
				const auto xSpeed = (!isRotation ? (speedMultiplier.x * currentSpeed.x) : currentSpeed.x);
				const auto ySpeed = (!isRotation ? (speedMultiplier.y * currentSpeed.y) : currentSpeed.y);
				const auto zSpeed = (!isRotation ? (speedMultiplier.z * currentSpeed.z) : currentSpeed.z);
				const auto targetMovement = (animation.getInitialSize() * frame.getTargetTransformations().at(partID));
				const auto targetRotation = frame.getTargetTransformations().at(partID);
				const auto targetScaling = ((partID.empty() ? animation.getInitialSize() : fvec3(1.0f)) * frame.getTargetTransformations().at(partID));
				const auto targetTransformation = (isMovement ? targetMovement : isRotation ? targetRotation : targetScaling);

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
					if((isMovement && !_hasReachedFloat(totalMovement.x, targetTransformation.x, xSpeed)) ||
					   (isRotation && !_hasReachedFloat(totalRotation.x, targetTransformation.x, xSpeed)) ||
					   (isScaling && !_hasReachedFloat(totalScaling.x, targetTransformation.x, xSpeed)))
					{
						float finalSpeed = xSpeed;

						if(transformationType == TransformationType::MOVEMENT)
						{
							if(speedType == Animation3dSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalMovement.x);
							}

							totalMovement.x += finalSpeed;
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							if(speedType == Animation3dSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalRotation.x);
							}

							totalRotation.x += finalSpeed;
						}
						else if(transformationType == TransformationType::SCALING)
						{
							if(speedType == Animation3dSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.x - totalScaling.x);
							}

							totalScaling.x += finalSpeed;
						}

						if(speedType == Animation3dSpeedType::EXPONENTIAL)
						{
							baseSpeed.x += (baseSpeed.x / 100.0f);
						}

						float difference = 0.0f;
						if((isMovement && _hasReachedFloat(totalMovement.x, targetTransformation.x, xSpeed)) ||
						   (isRotation && _hasReachedFloat(totalRotation.x, targetTransformation.x, xSpeed)) ||
						   (isScaling && _hasReachedFloat(totalScaling.x, targetTransformation.x, xSpeed)))
						{
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

						if(transformationType == TransformationType::MOVEMENT)
						{
							if(partID.empty())
							{
								_fe3d->model_moveBase(key.second, fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}
							else
							{
								_fe3d->model_movePart(key.second, partID, fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							if(partID.empty())
							{
								_fe3d->model_setBaseRotationOrigin(key.second, (currentModelSize * rotationOrigin));
								_fe3d->model_rotateBase(key.second, fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}
							else
							{
								_fe3d->model_setPartRotationOrigin(key.second, partID, (currentModelSize * rotationOrigin));
								_fe3d->model_rotatePart(key.second, partID, fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}
						}
						else if(transformationType == TransformationType::SCALING)
						{
							if(partID.empty())
							{
								_fe3d->model_scaleBase(key.second, fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}
							else
							{
								_fe3d->model_scalePart(key.second, partID, fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}
						}
					}

					if((isMovement && !_hasReachedFloat(totalMovement.y, targetTransformation.y, ySpeed)) ||
					   (isRotation && !_hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) ||
					   (isScaling && !_hasReachedFloat(totalScaling.y, targetTransformation.y, ySpeed)))
					{
						float finalSpeed = ySpeed;

						if(transformationType == TransformationType::MOVEMENT)
						{
							if(speedType == Animation3dSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalMovement.y);
							}

							totalMovement.y += finalSpeed;
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							if(speedType == Animation3dSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalRotation.y);
							}

							totalRotation.y += finalSpeed;
						}
						else if(transformationType == TransformationType::SCALING)
						{
							if(speedType == Animation3dSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.y - totalScaling.y);
							}

							totalScaling.y += finalSpeed;
						}

						if(speedType == Animation3dSpeedType::EXPONENTIAL)
						{
							baseSpeed.y += (baseSpeed.y / 100.0f);
						}

						float difference = 0.0f;
						if((isMovement && _hasReachedFloat(totalMovement.y, targetTransformation.y, ySpeed)) ||
						   (isRotation && _hasReachedFloat(totalRotation.y, targetTransformation.y, ySpeed)) ||
						   (isScaling && _hasReachedFloat(totalScaling.y, targetTransformation.y, ySpeed)))
						{
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

						if(transformationType == TransformationType::MOVEMENT)
						{
							if(partID.empty())
							{
								_fe3d->model_moveBase(key.second, fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}
							else
							{
								_fe3d->model_movePart(key.second, partID, fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							if(partID.empty())
							{
								_fe3d->model_setBaseRotationOrigin(key.second, (currentModelSize * rotationOrigin));
								_fe3d->model_rotateBase(key.second, fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}
							else
							{
								_fe3d->model_setPartRotationOrigin(key.second, partID, (currentModelSize * rotationOrigin));
								_fe3d->model_rotatePart(key.second, partID, fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}
						}
						else if(transformationType == TransformationType::SCALING)
						{
							if(partID.empty())
							{
								_fe3d->model_scaleBase(key.second, fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}
							else
							{
								_fe3d->model_scalePart(key.second, partID, fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}
						}
					}

					if((isMovement && !_hasReachedFloat(totalMovement.z, targetTransformation.z, zSpeed)) ||
					   (isRotation && !_hasReachedFloat(totalRotation.z, targetTransformation.z, zSpeed)) ||
					   (isScaling && !_hasReachedFloat(totalScaling.z, targetTransformation.z, zSpeed)))
					{
						float finalSpeed = zSpeed;

						if(transformationType == TransformationType::MOVEMENT)
						{
							if(speedType == Animation3dSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalMovement.z);
							}

							totalMovement.z += finalSpeed;
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							if(speedType == Animation3dSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalRotation.z);
							}

							totalRotation.z += finalSpeed;
						}
						else if(transformationType == TransformationType::SCALING)
						{
							if(speedType == Animation3dSpeedType::INSTANTLY)
							{
								finalSpeed = (targetTransformation.z - totalScaling.z);
							}

							totalScaling.z += finalSpeed;
						}

						if(speedType == Animation3dSpeedType::EXPONENTIAL)
						{
							baseSpeed.z += (baseSpeed.z / 100.0f);
						}

						float difference = 0.0f;
						if((isMovement && _hasReachedFloat(totalMovement.z, targetTransformation.z, finalSpeed)) ||
						   (isRotation && _hasReachedFloat(totalRotation.z, targetTransformation.z, finalSpeed)) ||
						   (isScaling && _hasReachedFloat(totalScaling.z, targetTransformation.z, finalSpeed)))
						{
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

						if(transformationType == TransformationType::MOVEMENT)
						{
							if(partID.empty())
							{
								_fe3d->model_moveBase(key.second, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
							else
							{
								_fe3d->model_movePart(key.second, partID, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
						}
						else if(transformationType == TransformationType::ROTATION)
						{
							if(partID.empty())
							{
								_fe3d->model_setBaseRotationOrigin(key.second, (currentModelSize * rotationOrigin));
								_fe3d->model_rotateBase(key.second, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
							else
							{
								_fe3d->model_setPartRotationOrigin(key.second, partID, (currentModelSize * rotationOrigin));
								_fe3d->model_rotatePart(key.second, partID, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
						}
						else if(transformationType == TransformationType::SCALING)
						{
							if(partID.empty())
							{
								_fe3d->model_scaleBase(key.second, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
							else
							{
								_fe3d->model_scalePart(key.second, partID, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}

						}
					}
				}

				animation.setTotalMovement(partID, totalMovement);
				animation.setTotalRotation(partID, totalRotation);
				animation.setTotalScaling(partID, totalScaling);

				frame.setSpeed(partID, baseSpeed);
			}

			animation.setFrame(frameIndex, frame);

			if(finishedPartCount == animation.getPartIDs().size())
			{
				if(animation.isAutopaused())
				{
					animation.setPaused(true);
				}

				if(animation.getFrameIndex() == (static_cast<unsigned int>(animation.getFrames().size()) - 1))
				{
					if(animation.getPlayCount() == -1)
					{
						_modelAnimationsToStop.insert(key);
						_modelAnimationsToStart.insert(key);
					}
					else
					{
						animation.setPlayCount(animation.getPlayCount() - 1);

						if(animation.getPlayCount() == 0)
						{
							_modelAnimationsToStop.insert(key);
						}
						else
						{
							animation.setFrameIndex(0);
						}
					}
				}
				else
				{
					animation.setFrameIndex(animation.getFrameIndex() + 1);
				}
			}
		}

		for(const auto& key : _modelAnimationsToStop)
		{
			if(isModelAnimationStarted(key.first, key.second))
			{
				stopModelAnimation(key.first, key.second);
			}
		}
		_modelAnimationsToStop.clear();

		for(const auto& key : _modelAnimationsToStart)
		{
			if(!isModelAnimationStarted(key.first, key.second))
			{
				startModelAnimation(key.first, key.second, -1);
			}
		}
		_modelAnimationsToStart.clear();
	}
}