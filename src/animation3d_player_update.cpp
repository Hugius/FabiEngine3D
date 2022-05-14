#include "animation3d_player.hpp"
#include "tools.hpp"

#include <set>

using std::set;

void Animation3dPlayer::update()
{
	_updateModelAnimation3dExecution();
}

void Animation3dPlayer::_updateModelAnimation3dExecution()
{
	vector<string> modelAnimationsToStop = {};

	for(auto & [mergedId, startedAnimation] : _startedModelAnimation3ds)
	{
		if(startedAnimation->isPaused())
		{
			continue;
		}

		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);
		const auto animation3d = _animation3dManager->getAnimation3d(splitKey.first);
		const auto model = _modelManager->getModel(splitKey.second);

		int finishedPartCount = 0;
		for(const auto & partId : startedAnimation->getPartIds())
		{
			auto totalMovement = startedAnimation->getTotalMovement(partId);
			auto totalRotation = startedAnimation->getTotalRotation(partId);
			auto totalScaling = startedAnimation->getTotalScaling(partId);
			auto totalSpeed = startedAnimation->getTotalSpeed(partId);

			const auto currentModelSize = model->getBaseSize();
			const auto transformationType = animation3d->getTransformationType(startedAnimation->getFrameIndex(), partId);
			const auto isMovement = (transformationType == TransformationType::MOVEMENT);
			const auto isRotation = (transformationType == TransformationType::ROTATION);
			const auto isScaling = (transformationType == TransformationType::SCALING);
			const auto speedType = animation3d->getSpeedType(startedAnimation->getFrameIndex(), partId);
			const auto rotationOrigin = animation3d->getRotationOrigin(startedAnimation->getFrameIndex(), partId);
			const auto speed = (animation3d->getSpeed(startedAnimation->getFrameIndex(), partId) * startedAnimation->getSpeedMultiplier());
			const auto targetMovement = animation3d->getTargetTransformation(startedAnimation->getFrameIndex(), partId);
			const auto targetRotation = animation3d->getTargetTransformation(startedAnimation->getFrameIndex(), partId);
			const auto targetScaling = animation3d->getTargetTransformation(startedAnimation->getFrameIndex(), partId);
			const auto targetTransformation = (isMovement ? targetMovement : isRotation ? targetRotation : targetScaling);

			if(((isMovement && _hasReachedTarget(totalMovement.x, targetTransformation.x, speed.x)) &&
			   (isMovement && _hasReachedTarget(totalMovement.y, targetTransformation.y, speed.x)) &&
			   (isMovement && _hasReachedTarget(totalMovement.z, targetTransformation.z, speed.x)))
			   ||
			   ((isRotation && _hasReachedTarget(totalRotation.x, targetTransformation.x, speed.y)) &&
			   (isRotation && _hasReachedTarget(totalRotation.y, targetTransformation.y, speed.y)) &&
			   (isRotation && _hasReachedTarget(totalRotation.z, targetTransformation.z, speed.y)))
			   ||
			   ((isScaling && _hasReachedTarget(totalScaling.x, targetTransformation.x, speed.z)) &&
			   (isScaling && _hasReachedTarget(totalScaling.y, targetTransformation.y, speed.z)) &&
			   (isScaling && _hasReachedTarget(totalScaling.z, targetTransformation.z, speed.z))))
			{
				finishedPartCount++;
			}
			else
			{
				if((isMovement && !_hasReachedTarget(totalMovement.x, targetTransformation.x, speed.x)) ||
				   (isRotation && !_hasReachedTarget(totalRotation.x, targetTransformation.x, speed.x)) ||
				   (isScaling && !_hasReachedTarget(totalScaling.x, targetTransformation.x, speed.x)))
				{
					float finalSpeed = speed.x;

					if(transformationType == TransformationType::MOVEMENT)
					{
						if(speedType == SpeedType::INSTANTLY)
						{
							finalSpeed = (targetTransformation.x - totalMovement.x);
						}

						totalMovement.x += finalSpeed;
					}
					else if(transformationType == TransformationType::ROTATION)
					{
						if(speedType == SpeedType::INSTANTLY)
						{
							finalSpeed = (targetTransformation.x - totalRotation.x);
						}

						totalRotation.x += finalSpeed;
					}
					else if(transformationType == TransformationType::SCALING)
					{
						if(speedType == SpeedType::INSTANTLY)
						{
							finalSpeed = (targetTransformation.x - totalScaling.x);
						}

						totalScaling.x += finalSpeed;
					}

					if(speedType == SpeedType::EXPONENTIAL)
					{
						totalSpeed.x += (speed.x / 100.0f);
					}

					float difference = 0.0f;
					if((isMovement && _hasReachedTarget(totalMovement.x, targetTransformation.x, speed.x)) ||
					   (isRotation && _hasReachedTarget(totalRotation.x, targetTransformation.x, speed.x)) ||
					   (isScaling && _hasReachedTarget(totalScaling.x, targetTransformation.x, speed.x)))
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

				if((isMovement && !_hasReachedTarget(totalMovement.y, targetTransformation.y, speed.y)) ||
				   (isRotation && !_hasReachedTarget(totalRotation.y, targetTransformation.y, speed.y)) ||
				   (isScaling && !_hasReachedTarget(totalScaling.y, targetTransformation.y, speed.y)))
				{
					float finalSpeed = speed.y;

					if(transformationType == TransformationType::MOVEMENT)
					{
						if(speedType == SpeedType::INSTANTLY)
						{
							finalSpeed = (targetTransformation.y - totalMovement.y);
						}

						totalMovement.y += finalSpeed;
					}
					else if(transformationType == TransformationType::ROTATION)
					{
						if(speedType == SpeedType::INSTANTLY)
						{
							finalSpeed = (targetTransformation.y - totalRotation.y);
						}

						totalRotation.y += finalSpeed;
					}
					else if(transformationType == TransformationType::SCALING)
					{
						if(speedType == SpeedType::INSTANTLY)
						{
							finalSpeed = (targetTransformation.y - totalScaling.y);
						}

						totalScaling.y += finalSpeed;
					}

					if(speedType == SpeedType::EXPONENTIAL)
					{
						totalSpeed.y += (speed.y / 100.0f);
					}

					float difference = 0.0f;
					if((isMovement && _hasReachedTarget(totalMovement.y, targetTransformation.y, speed.y)) ||
					   (isRotation && _hasReachedTarget(totalRotation.y, targetTransformation.y, speed.y)) ||
					   (isScaling && _hasReachedTarget(totalScaling.y, targetTransformation.y, speed.y)))
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

				if((isMovement && !_hasReachedTarget(totalMovement.z, targetTransformation.z, speed.z)) ||
				   (isRotation && !_hasReachedTarget(totalRotation.z, targetTransformation.z, speed.z)) ||
				   (isScaling && !_hasReachedTarget(totalScaling.z, targetTransformation.z, speed.z)))
				{
					float finalSpeed = speed.z;

					if(transformationType == TransformationType::MOVEMENT)
					{
						if(speedType == SpeedType::INSTANTLY)
						{
							finalSpeed = (targetTransformation.z - totalMovement.z);
						}

						totalMovement.z += finalSpeed;
					}
					else if(transformationType == TransformationType::ROTATION)
					{
						if(speedType == SpeedType::INSTANTLY)
						{
							finalSpeed = (targetTransformation.z - totalRotation.z);
						}

						totalRotation.z += finalSpeed;
					}
					else if(transformationType == TransformationType::SCALING)
					{
						if(speedType == SpeedType::INSTANTLY)
						{
							finalSpeed = (targetTransformation.z - totalScaling.z);
						}

						totalScaling.z += finalSpeed;
					}

					if(speedType == SpeedType::EXPONENTIAL)
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

			if(startedAnimation->getFrameIndex() == (animation3d->getFrameCount() - 1))
			{
				startedAnimation->setFrameIndex(0);

				for(const auto & partId : startedAnimation->getPartIds())
				{
					startedAnimation->setTotalMovement(partId, fvec3(0.0f));
					startedAnimation->setTotalRotation(partId, fvec3(0.0f));
					startedAnimation->setTotalScaling(partId, fvec3(0.0f));
					startedAnimation->setTotalSpeed(partId, fvec3(0.0f));
				}

				if(startedAnimation->getPlayCount() != -1)
				{
					startedAnimation->setPlayCount(startedAnimation->getPlayCount() - 1);

					if(startedAnimation->getPlayCount() == 0)
					{
						modelAnimationsToStop.push_back(mergedId);
					}
				}
			}
			else
			{
				startedAnimation->setFrameIndex(startedAnimation->getFrameIndex() + 1);
			}
		}
	}

	for(const auto & mergedId : modelAnimationsToStop)
	{
		_startedModelAnimation3ds.erase(mergedId);
	}
}