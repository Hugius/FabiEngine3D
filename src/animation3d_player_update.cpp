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
	vector<string> modelAnimation3dsToStop = {};

	for(auto & [mergedId, startedAnimation3d] : _startedModelAnimation3ds)
	{
		if(startedAnimation3d->isPaused())
		{
			continue;
		}

		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);
		const auto animation3d = _animation3dManager->getAnimation3d(splitKey.first);
		const auto model = _modelManager->getModel(splitKey.second);

		int finishedPartCount = 0;

		for(const auto & partId : startedAnimation3d->getPartIds())
		{
			auto totalMovement = startedAnimation3d->getTotalMovement(partId);
			auto totalRotation = startedAnimation3d->getTotalRotation(partId);
			auto totalScaling = startedAnimation3d->getTotalScaling(partId);
			auto totalSpeed = startedAnimation3d->getTotalSpeed(partId);

			const auto currentModelSize = model->getBaseSize();
			const auto transformationType = animation3d->getTransformationType(startedAnimation3d->getFrameIndex(), partId);
			const auto isMovement = (transformationType == TransformationType::MOVEMENT);
			const auto isRotation = (transformationType == TransformationType::ROTATION);
			const auto isScaling = (transformationType == TransformationType::SCALING);
			const auto speedType = animation3d->getSpeedType(startedAnimation3d->getFrameIndex(), partId);
			const auto rotationOrigin = animation3d->getRotationOrigin(startedAnimation3d->getFrameIndex(), partId);
			const auto speed = (animation3d->getSpeed(startedAnimation3d->getFrameIndex(), partId) * startedAnimation3d->getSpeedMultiplier());
			const auto targetMovement = animation3d->getTargetTransformation(startedAnimation3d->getFrameIndex(), partId);
			const auto targetRotation = animation3d->getTargetTransformation(startedAnimation3d->getFrameIndex(), partId);
			const auto targetScaling = animation3d->getTargetTransformation(startedAnimation3d->getFrameIndex(), partId);

			if(((isMovement && _hasReachedTarget(totalMovement.x, targetMovement.x, speed.x)) &&
			   (isMovement && _hasReachedTarget(totalMovement.y, targetMovement.y, speed.x)) &&
			   (isMovement && _hasReachedTarget(totalMovement.z, targetMovement.z, speed.x)))
			   ||
			   ((isRotation && _hasReachedTarget(totalRotation.x, targetRotation.x, speed.y)) &&
			   (isRotation && _hasReachedTarget(totalRotation.y, targetRotation.y, speed.y)) &&
			   (isRotation && _hasReachedTarget(totalRotation.z, targetRotation.z, speed.y)))
			   ||
			   ((isScaling && _hasReachedTarget(totalScaling.x, targetScaling.x, speed.z)) &&
			   (isScaling && _hasReachedTarget(totalScaling.y, targetScaling.y, speed.z)) &&
			   (isScaling && _hasReachedTarget(totalScaling.z, targetScaling.z, speed.z))))
			{
				finishedPartCount++;
			}
			else
			{
				if((isMovement && !_hasReachedTarget(totalMovement.x, targetMovement.x, speed.x)) ||
				   (isRotation && !_hasReachedTarget(totalRotation.x, targetRotation.x, speed.x)) ||
				   (isScaling && !_hasReachedTarget(totalScaling.x, targetScaling.x, speed.x)))
				{
					auto finalSpeed = speed.x;

					switch(transformationType)
					{
						case TransformationType::MOVEMENT:
						{
							if(speedType == SpeedType::INSTANTLY)
							{
								finalSpeed = (targetMovement.x - totalMovement.x);
							}

							totalMovement.x += finalSpeed;

							break;
						}
						case TransformationType::ROTATION:
						{
							if(speedType == SpeedType::INSTANTLY)
							{
								finalSpeed = (targetRotation.x - totalRotation.x);
							}

							totalRotation.x += finalSpeed;

							break;
						}
						case TransformationType::SCALING:
						{
							if(speedType == SpeedType::INSTANTLY)
							{
								finalSpeed = (targetScaling.x - totalScaling.x);
							}

							totalScaling.x += finalSpeed;

							break;
						}
					}

					if(speedType == SpeedType::EXPONENTIAL)
					{
						totalSpeed.x += (speed.x / 100.0f);
					}

					float difference = 0.0f;

					if((isMovement && _hasReachedTarget(totalMovement.x, targetMovement.x, speed.x)) ||
					   (isRotation && _hasReachedTarget(totalRotation.x, targetRotation.x, speed.x)) ||
					   (isScaling && _hasReachedTarget(totalScaling.x, targetScaling.x, speed.x)))
					{
						switch(transformationType)
						{
							case TransformationType::MOVEMENT:
							{
								difference = (totalMovement.x - targetMovement.x);
								totalMovement.x -= difference;

								break;
							}
							case TransformationType::ROTATION:
							{
								difference = (totalRotation.x - targetRotation.x);
								totalRotation.x -= difference;

								break;
							}
							case TransformationType::SCALING:
							{
								difference = (totalScaling.x - targetScaling.x);
								totalScaling.x -= difference;

								break;
							}
						}
					}

					switch(transformationType)
					{
						case TransformationType::MOVEMENT:
						{
							if(partId.empty())
							{
								model->moveBase(fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}
							else
							{
								model->movePart(partId, fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}

							break;
						}
						case TransformationType::ROTATION:
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

							break;
						}
						case TransformationType::SCALING:
						{
							if(partId.empty())
							{
								model->scaleBase(fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}
							else
							{
								model->scalePart(partId, fvec3((finalSpeed - difference), 0.0f, 0.0f));
							}

							break;
						}
					}
				}

				if((isMovement && !_hasReachedTarget(totalMovement.y, targetMovement.y, speed.y)) ||
				   (isRotation && !_hasReachedTarget(totalRotation.y, targetRotation.y, speed.y)) ||
				   (isScaling && !_hasReachedTarget(totalScaling.y, targetScaling.y, speed.y)))
				{
					auto finalSpeed = speed.y;

					switch(transformationType)
					{
						case TransformationType::MOVEMENT:
						{
							if(speedType == SpeedType::INSTANTLY)
							{
								finalSpeed = (targetMovement.y - totalMovement.y);
							}

							totalMovement.y += finalSpeed;

							break;
						}
						case TransformationType::ROTATION:
						{
							if(speedType == SpeedType::INSTANTLY)
							{
								finalSpeed = (targetRotation.y - totalRotation.y);
							}

							totalRotation.y += finalSpeed;

							break;
						}
						case TransformationType::SCALING:
						{
							if(speedType == SpeedType::INSTANTLY)
							{
								finalSpeed = (targetScaling.y - totalScaling.y);
							}

							totalScaling.y += finalSpeed;

							break;
						}
					}

					if(speedType == SpeedType::EXPONENTIAL)
					{
						totalSpeed.y += (speed.y / 100.0f);
					}

					float difference = 0.0f;

					if((isMovement && _hasReachedTarget(totalMovement.y, targetMovement.y, speed.y)) ||
					   (isRotation && _hasReachedTarget(totalRotation.y, targetRotation.y, speed.y)) ||
					   (isScaling && _hasReachedTarget(totalScaling.y, targetScaling.y, speed.y)))
					{
						switch(transformationType)
						{
							case TransformationType::MOVEMENT:
							{
								difference = (totalMovement.y - targetMovement.y);
								totalMovement.y -= difference;

								break;
							}
							case TransformationType::ROTATION:
							{
								difference = (totalRotation.y - targetRotation.y);
								totalRotation.y -= difference;

								break;
							}
							case TransformationType::SCALING:
							{
								difference = (totalScaling.y - targetScaling.y);
								totalScaling.y -= difference;

								break;
							}
						}
					}

					switch(transformationType)
					{
						case TransformationType::MOVEMENT:
						{
							if(partId.empty())
							{
								model->moveBase(fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}
							else
							{
								model->movePart(partId, fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}

							break;
						}
						case TransformationType::ROTATION:
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

							break;
						}
						case TransformationType::SCALING:
						{
							if(partId.empty())
							{
								model->scaleBase(fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}
							else
							{
								model->scalePart(partId, fvec3(0.0f, (finalSpeed - difference), 0.0f));
							}

							break;
						}
					}
				}

				if((isMovement && !_hasReachedTarget(totalMovement.z, targetMovement.z, speed.z)) ||
				   (isRotation && !_hasReachedTarget(totalRotation.z, targetRotation.z, speed.z)) ||
				   (isScaling && !_hasReachedTarget(totalScaling.z, targetScaling.z, speed.z)))
				{
					auto finalSpeed = speed.z;

					switch(transformationType)
					{
						case TransformationType::MOVEMENT:
						{
							if(speedType == SpeedType::INSTANTLY)
							{
								finalSpeed = (targetMovement.z - totalMovement.z);
							}

							totalMovement.z += finalSpeed;

							break;
						}
						case TransformationType::ROTATION:
						{
							if(speedType == SpeedType::INSTANTLY)
							{
								finalSpeed = (targetRotation.z - totalRotation.z);
							}

							totalRotation.z += finalSpeed;

							break;
						}
						case TransformationType::SCALING:
						{
							if(speedType == SpeedType::INSTANTLY)
							{
								finalSpeed = (targetScaling.z - totalScaling.z);
							}

							totalScaling.z += finalSpeed;

							break;
						}
					}

					if(speedType == SpeedType::EXPONENTIAL)
					{
						totalSpeed.z += (speed.z / 100.0f);
					}

					float difference = 0.0f;

					if((isMovement && _hasReachedTarget(totalMovement.z, targetMovement.z, finalSpeed)) ||
					   (isRotation && _hasReachedTarget(totalRotation.z, targetRotation.z, finalSpeed)) ||
					   (isScaling && _hasReachedTarget(totalScaling.z, targetScaling.z, finalSpeed)))
					{
						switch(transformationType)
						{
							case TransformationType::MOVEMENT:
							{
								difference = (totalMovement.z - targetMovement.z);
								totalMovement.z -= difference;

								break;
							}
							case TransformationType::ROTATION:
							{
								difference = (totalRotation.z - targetRotation.z);
								totalRotation.z -= difference;

								break;
							}
							case TransformationType::SCALING:
							{
								difference = (totalScaling.z - targetScaling.z);
								totalScaling.z -= difference;

								break;
							}
						}
					}

					switch(transformationType)
					{
						case TransformationType::MOVEMENT:
						{
							if(partId.empty())
							{
								model->moveBase(fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
							else
							{
								model->movePart(partId, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}

							break;
						}
						case TransformationType::ROTATION:
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

							break;
						}
						case TransformationType::SCALING:
						{
							if(partId.empty())
							{
								model->scaleBase(fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}
							else
							{
								model->scalePart(partId, fvec3(0.0f, 0.0f, (finalSpeed - difference)));
							}

							break;
						}
					}
				}
			}

			startedAnimation3d->setTotalMovement(partId, totalMovement);
			startedAnimation3d->setTotalRotation(partId, totalRotation);
			startedAnimation3d->setTotalScaling(partId, totalScaling);
			startedAnimation3d->setTotalSpeed(partId, totalSpeed);
		}

		if(finishedPartCount == startedAnimation3d->getPartIds().size())
		{
			if(startedAnimation3d->isAutopaused())
			{
				startedAnimation3d->setPaused(true);
			}

			if(startedAnimation3d->getFrameIndex() == (animation3d->getFrameCount() - 1))
			{
				startedAnimation3d->setFrameIndex(0);

				for(const auto & partId : startedAnimation3d->getPartIds())
				{
					startedAnimation3d->setTotalMovement(partId, fvec3(0.0f));
					startedAnimation3d->setTotalRotation(partId, fvec3(0.0f));
					startedAnimation3d->setTotalScaling(partId, fvec3(0.0f));
					startedAnimation3d->setTotalSpeed(partId, fvec3(0.0f));
				}

				if(startedAnimation3d->getPlayCount() != -1)
				{
					startedAnimation3d->setPlayCount(startedAnimation3d->getPlayCount() - 1);

					if(startedAnimation3d->getPlayCount() == 0)
					{
						modelAnimation3dsToStop.push_back(mergedId);
					}
				}
			}
			else
			{
				startedAnimation3d->setFrameIndex(startedAnimation3d->getFrameIndex() + 1);
			}
		}
	}

	for(const auto & mergedId : modelAnimation3dsToStop)
	{
		_startedModelAnimation3ds.erase(mergedId);
	}
}