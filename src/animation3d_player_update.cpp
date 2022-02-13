#include "animation3d_player.hpp"

#include <set>

using std::set;

void Animation3dPlayer::update()
{
	_updateModelAnimationExecution();
}

void Animation3dPlayer::_updateModelAnimationExecution()
{
	set<pair<string, string>> modelAnimationsToStop;

	for(auto& [key, startedAnimation] : _startedModelAnimations)
	{
		if(startedAnimation->isPaused())
		{
			continue;
		}

		const auto animation = _animation3dManager->getAnimation(key.first);
		const auto model = _modelEntityManager->getEntity(key.second);

		unsigned int finishedPartCount = 0;
		for(const auto& partId : startedAnimation->getPartIds())
		{
			auto totalMovement = startedAnimation->getTotalMovement(partId);
			auto totalRotation = startedAnimation->getTotalRotation(partId);
			auto totalScaling = startedAnimation->getTotalScaling(partId);
			auto totalSpeed = startedAnimation->getTotalSpeed(partId);

			const auto currentModelSize = model->getBaseSize();
			const auto transformationType = animation->getTransformationType(startedAnimation->getFrameIndex(), partId);
			const auto isMovement = (transformationType == TransformationType::MOVEMENT);
			const auto isRotation = (transformationType == TransformationType::ROTATION);
			const auto isScaling = (transformationType == TransformationType::SCALING);
			const auto speedMultiplier = (partId.empty() || (isMovement || isScaling)) ? startedAnimation->getInitialSize() : fvec3(1.0f);
			const auto speedType = animation->getSpeedType(startedAnimation->getFrameIndex(), partId);
			const auto rotationOrigin = animation->getRotationOrigin(startedAnimation->getFrameIndex(), partId);
			const auto speed = (animation->getSpeed(startedAnimation->getFrameIndex(), partId) * startedAnimation->getSpeedMultiplier());
			const auto xSpeed = (!isRotation ? (speedMultiplier.x * speed.x) : speed.x);
			const auto ySpeed = (!isRotation ? (speedMultiplier.y * speed.y) : speed.y);
			const auto zSpeed = (!isRotation ? (speedMultiplier.z * speed.z) : speed.z);
			const auto targetMovement = (startedAnimation->getInitialSize() * animation->getTargetTransformation(startedAnimation->getFrameIndex(), partId));
			const auto targetRotation = animation->getTargetTransformation(startedAnimation->getFrameIndex(), partId);
			const auto targetScaling = ((partId.empty() ? startedAnimation->getInitialSize() : fvec3(1.0f)) * animation->getTargetTransformation(startedAnimation->getFrameIndex(), partId));
			const auto targetTransformation = (isMovement ? targetMovement : isRotation ? targetRotation : targetScaling);

			if(((isMovement && _hasReachedTarget(totalMovement.x, targetTransformation.x, xSpeed)) &&
			   (isMovement && _hasReachedTarget(totalMovement.y, targetTransformation.y, xSpeed)) &&
			   (isMovement && _hasReachedTarget(totalMovement.z, targetTransformation.z, xSpeed)))
			   ||
			   ((isRotation && _hasReachedTarget(totalRotation.x, targetTransformation.x, ySpeed)) &&
			   (isRotation && _hasReachedTarget(totalRotation.y, targetTransformation.y, ySpeed)) &&
			   (isRotation && _hasReachedTarget(totalRotation.z, targetTransformation.z, ySpeed)))
			   ||
			   ((isScaling && _hasReachedTarget(totalScaling.x, targetTransformation.x, zSpeed)) &&
			   (isScaling && _hasReachedTarget(totalScaling.y, targetTransformation.y, zSpeed)) &&
			   (isScaling && _hasReachedTarget(totalScaling.z, targetTransformation.z, zSpeed))))
			{
				finishedPartCount++;
			}
			else
			{
				if((isMovement && !_hasReachedTarget(totalMovement.x, targetTransformation.x, xSpeed)) ||
				   (isRotation && !_hasReachedTarget(totalRotation.x, targetTransformation.x, xSpeed)) ||
				   (isScaling && !_hasReachedTarget(totalScaling.x, targetTransformation.x, xSpeed)))
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
						totalSpeed.x += (speed.x / 100.0f);
					}

					float difference = 0.0f;
					if((isMovement && _hasReachedTarget(totalMovement.x, targetTransformation.x, xSpeed)) ||
					   (isRotation && _hasReachedTarget(totalRotation.x, targetTransformation.x, xSpeed)) ||
					   (isScaling && _hasReachedTarget(totalScaling.x, targetTransformation.x, xSpeed)))
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
						if(partId.empty())
						{
							model->moveBase(fvec3((finalSpeed - difference), 0.0f, 0.0f));
						}
						else
						{
							model->movePart(partId, fvec3((finalSpeed - difference), 0.0f, 0.0f));
						}
					}
					else if(transformationType == TransformationType::ROTATION)
					{
						if(partId.empty())
						{
							model->setBaseRotationOrigin(currentModelSize * rotationOrigin);
							model->rotateBase(fvec3((finalSpeed - difference), 0.0f, 0.0f));
						}
						else
						{
							model->setPartRotationOrigin(partId, (currentModelSize * rotationOrigin));
							model->rotatePart(partId, fvec3((finalSpeed - difference), 0.0f, 0.0f));
						}
					}
					else if(transformationType == TransformationType::SCALING)
					{
						if(partId.empty())
						{
							model->scaleBase(fvec3((finalSpeed - difference), 0.0f, 0.0f));
						}
						else
						{
							model->scalePart(partId, fvec3((finalSpeed - difference), 0.0f, 0.0f));
						}
					}
				}

				if((isMovement && !_hasReachedTarget(totalMovement.y, targetTransformation.y, ySpeed)) ||
				   (isRotation && !_hasReachedTarget(totalRotation.y, targetTransformation.y, ySpeed)) ||
				   (isScaling && !_hasReachedTarget(totalScaling.y, targetTransformation.y, ySpeed)))
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
						totalSpeed.y += (speed.y / 100.0f);
					}

					float difference = 0.0f;
					if((isMovement && _hasReachedTarget(totalMovement.y, targetTransformation.y, ySpeed)) ||
					   (isRotation && _hasReachedTarget(totalRotation.y, targetTransformation.y, ySpeed)) ||
					   (isScaling && _hasReachedTarget(totalScaling.y, targetTransformation.y, ySpeed)))
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
						if(partId.empty())
						{
							model->moveBase(fvec3(0.0f, (finalSpeed - difference), 0.0f));
						}
						else
						{
							model->movePart(partId, fvec3(0.0f, (finalSpeed - difference), 0.0f));
						}
					}
					else if(transformationType == TransformationType::ROTATION)
					{
						if(partId.empty())
						{
							model->setBaseRotationOrigin((currentModelSize * rotationOrigin));
							model->rotateBase(fvec3(0.0f, (finalSpeed - difference), 0.0f));
						}
						else
						{
							model->setPartRotationOrigin(partId, (currentModelSize * rotationOrigin));
							model->rotatePart(partId, fvec3(0.0f, (finalSpeed - difference), 0.0f));
						}
					}
					else if(transformationType == TransformationType::SCALING)
					{
						if(partId.empty())
						{
							model->scaleBase(fvec3(0.0f, (finalSpeed - difference), 0.0f));
						}
						else
						{
							model->scalePart(partId, fvec3(0.0f, (finalSpeed - difference), 0.0f));
						}
					}
				}

				if((isMovement && !_hasReachedTarget(totalMovement.z, targetTransformation.z, zSpeed)) ||
				   (isRotation && !_hasReachedTarget(totalRotation.z, targetTransformation.z, zSpeed)) ||
				   (isScaling && !_hasReachedTarget(totalScaling.z, targetTransformation.z, zSpeed)))
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
						totalSpeed.z += (speed.z / 100.0f);
					}

					float difference = 0.0f;
					if((isMovement && _hasReachedTarget(totalMovement.z, targetTransformation.z, finalSpeed)) ||
					   (isRotation && _hasReachedTarget(totalRotation.z, targetTransformation.z, finalSpeed)) ||
					   (isScaling && _hasReachedTarget(totalScaling.z, targetTransformation.z, finalSpeed)))
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
						if(partId.empty())
						{
							model->moveBase(fvec3(0.0f, 0.0f, (finalSpeed - difference)));
						}
						else
						{
							model->movePart(partId, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
						}
					}
					else if(transformationType == TransformationType::ROTATION)
					{
						if(partId.empty())
						{
							model->setBaseRotationOrigin((currentModelSize * rotationOrigin));
							model->rotateBase(fvec3(0.0f, 0.0f, (finalSpeed - difference)));
						}
						else
						{
							model->setPartRotationOrigin(partId, (currentModelSize * rotationOrigin));
							model->rotatePart(partId, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
						}
					}
					else if(transformationType == TransformationType::SCALING)
					{
						if(partId.empty())
						{
							model->scaleBase(fvec3(0.0f, 0.0f, (finalSpeed - difference)));
						}
						else
						{
							model->scalePart(partId, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
						}

					}
				}
			}

			startedAnimation->setTotalMovement(partId, totalMovement);
			startedAnimation->setTotalRotation(partId, totalRotation);
			startedAnimation->setTotalScaling(partId, totalScaling);
			startedAnimation->setTotalSpeed(partId, totalSpeed);
		}

		if(finishedPartCount == startedAnimation->getPartIds().size())
		{
			if(startedAnimation->isAutopaused())
			{
				startedAnimation->setPaused(true);
			}

			if(startedAnimation->getFrameIndex() == (static_cast<unsigned int>(animation->getFrameCount()) - 1))
			{
				startedAnimation->setFrameIndex(0);

				if(startedAnimation->getPlayCount() != -1)
				{
					startedAnimation->setPlayCount(startedAnimation->getPlayCount() - 1);

					if(startedAnimation->getPlayCount() == 0)
					{
						modelAnimationsToStop.insert(key);
					}
				}
			}
			else
			{
				startedAnimation->setFrameIndex(startedAnimation->getFrameIndex() + 1);
			}
		}
	}

	for(const auto& key : modelAnimationsToStop)
	{
		_startedModelAnimations.erase(make_pair(key.first, key.second));
	}
}