#include "aabb_manager.hpp"
#include "render_storage.hpp"
#include "tools.hpp"

using std::make_shared;

constexpr float centeredBufferData[] =
{
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f
};

constexpr float standingBufferData[] =
{
	-0.5f, 1.0f, -0.5f,
	0.5f, 1.0f, -0.5f,
	0.5f, 0.0f, -0.5f,
	-0.5f, 0.0f, -0.5f,
	-0.5f, 1.0f, -0.5f,
	-0.5f, 1.0f, 0.5f,
	0.5f, 1.0f, 0.5f,
	0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, 0.5f,
	-0.5f, 1.0f, 0.5f,
	0.5f, 1.0f, 0.5f,
	0.5f, 1.0f, -0.5f,
	0.5f, 0.0f, -0.5f,
	0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, -0.5f
};

constexpr int centeredBufferDataCount = static_cast<int>(sizeof(centeredBufferData) / sizeof(float));
constexpr int standingBufferDataCount = static_cast<int>(sizeof(centeredBufferData) / sizeof(float));

AabbManager::AabbManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS, centeredBufferData, centeredBufferDataCount)),
	_standingVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS, standingBufferData, standingBufferDataCount))
{

}

void AabbManager::inject(shared_ptr<ModelManager> modelManager)
{
	_modelManager = modelManager;
}

void AabbManager::inject(shared_ptr<Quad3dManager> quad3dManager)
{
	_quad3dManager = quad3dManager;
}

void AabbManager::inject(shared_ptr<Text3dManager> text3dManager)
{
	_text3dManager = text3dManager;
}

const shared_ptr<Aabb> AabbManager::getAabb(const string & aabbId) const
{
	const auto iterator = _aabbs.find(aabbId);

	if(iterator == _aabbs.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Aabb>> & AabbManager::getAabbs() const
{
	return _aabbs;
}

void AabbManager::createAabb(const string & aabbId, bool isCentered)
{
	if(isAabbExisting(aabbId))
	{
		abort();
	}

	const auto aabb = make_shared<Aabb>(aabbId);

	aabb->setVertexBuffer(isCentered ? _centeredVertexBuffer : _standingVertexBuffer);
	aabb->setCentered(isCentered);

	_aabbs.insert({aabbId, aabb});
}

void AabbManager::update()
{
	for(const auto & [aabbId, aabb] : _aabbs)
	{
		aabb->updateTarget();

		if(!aabb->getParentId().empty())
		{
			switch(aabb->getParentType())
			{
				case AabbParentType::MODEL:
				{
					auto foundPair = _modelManager->getModels().find(aabb->getParentId());

					if(foundPair == _modelManager->getModels().end())
					{
						abort();
					}

					const auto parentModel = foundPair->second;
					const auto newAabbSize = (aabb->getLocalSize() * parentModel->getBaseSize());
					const auto parentRotation = parentModel->getBaseRotation();

					float rotation;
					DirectionType rotationDirection;

					if((parentRotation.x > parentRotation.y) && (parentRotation.x > parentRotation.z))
					{
						rotation = parentRotation.x;
						rotationDirection = DirectionType::X;
					}
					else if((parentRotation.y > parentRotation.x) && (parentRotation.y > parentRotation.z))
					{
						rotation = parentRotation.y;
						rotationDirection = DirectionType::Y;
					}
					else if((parentRotation.z > parentRotation.x) && (parentRotation.z > parentRotation.y))
					{
						rotation = parentRotation.z;
						rotationDirection = DirectionType::Z;
					}
					else
					{
						rotation = 0.0f;
					}

					const auto is90Degrees = ((rotation > 45.0f) && (rotation < 135.0f));
					const auto is180Degrees = ((rotation >= 135.0f) && (rotation <= 225.0f));
					const auto is270Degrees = ((rotation > 225.0f) && (rotation < 315.0f));
					const auto roundedRotation = (is90Degrees ? 90.0f : is180Degrees ? 180.0f : is270Degrees ? 270.0f : 0.0f);

					if(is90Degrees || is270Degrees)
					{
						switch(rotationDirection)
						{
							case DirectionType::X:
							{
								aabb->setBaseSize(fvec3(newAabbSize.x, newAabbSize.z, newAabbSize.y));

								break;
							}
							case DirectionType::Y:
							{
								aabb->setBaseSize(fvec3(newAabbSize.z, newAabbSize.y, newAabbSize.x));

								break;
							}
							case DirectionType::Z:
							{
								aabb->setBaseSize(fvec3(newAabbSize.y, newAabbSize.x, newAabbSize.z));

								break;
							}
						}
					}
					else
					{
						aabb->setBaseSize(newAabbSize);
					}

					if((roundedRotation == 0.0f) || aabb->isCentered())
					{
						const auto localPosition = (aabb->getLocalPosition() * parentModel->getBaseSize());

						aabb->setBasePosition(parentModel->getBasePosition() + localPosition);
					}
					else
					{
						fvec3 localPosition;

						if(rotationDirection == DirectionType::Y)
						{
							localPosition = (aabb->getLocalPosition() * parentModel->getBaseSize());
						}
						else
						{
							const auto offset = fvec3(0.0f, (aabb->getLocalSize().y * 0.5f), 0.0f);

							localPosition = (aabb->getLocalPosition() + offset) * parentModel->getBaseSize();
						}

						mat44 rotationMatrix;
						fvec3 rotationOffset;

						if(rotationDirection == DirectionType::X)
						{
							rotationMatrix = Mathematics::createRotationMatrixX(Mathematics::convertToRadians(roundedRotation));
							rotationOffset = fvec3(0.0f, -((is180Degrees ? newAabbSize.y : newAabbSize.z) * 0.5f), 0.0f);
						}
						else if(rotationDirection == DirectionType::Y)
						{
							rotationMatrix = Mathematics::createRotationMatrixY(Mathematics::convertToRadians(roundedRotation));
							rotationOffset = fvec3(0.0f);
						}
						else if(rotationDirection == DirectionType::Z)
						{
							rotationMatrix = Mathematics::createRotationMatrixZ(Mathematics::convertToRadians(roundedRotation));
							rotationOffset = fvec3(0.0f, -((is180Degrees ? newAabbSize.y : newAabbSize.x) * 0.5f), 0.0f);
						}

						auto rotatedLocalPosition = (rotationMatrix * fvec4(localPosition.x, localPosition.y, localPosition.z, 1.0f));

						rotatedLocalPosition += rotationOffset;

						aabb->setBasePosition(parentModel->getBasePosition() + rotatedLocalPosition);
					}

					if(!parentModel->isVisible())
					{
						aabb->setVisible(false);
						aabb->setCollisionResponsive(false);
						aabb->setRaycastResponsive(false);
					}

					if(!parentModel->getLevelOfDetailId().empty())
					{
						aabb->setCollisionResponsive(!parentModel->isLevelOfDetailed());
						aabb->setRaycastResponsive(!parentModel->isLevelOfDetailed());
					}

					break;
				}
				case AabbParentType::QUAD3D:
				{
					auto foundPair = _quad3dManager->getQuad3ds().find(aabb->getParentId());

					if(foundPair == _quad3dManager->getQuad3ds().end())
					{
						abort();
					}

					const auto parentQuad3d = foundPair->second;
					const auto parentPosition = parentQuad3d->getPosition();
					const auto parentRotation = parentQuad3d->getRotation();
					const auto parentSize = parentQuad3d->getSize();

					auto refRotationX = Mathematics::calculateReferenceAngle(parentRotation.x);
					auto refRotationY = Mathematics::calculateReferenceAngle(parentRotation.y);
					auto refRotationZ = Mathematics::calculateReferenceAngle(parentRotation.z);

					refRotationX = ((refRotationX <= 45.0f) ? refRotationX : (refRotationX == 90.0f) ? 90.0f : (90.0f - refRotationX));
					refRotationY = ((refRotationY <= 45.0f) ? refRotationY : (refRotationY == 90.0f) ? 90.0f : (90.0f - refRotationY));
					refRotationZ = ((refRotationZ <= 45.0f) ? refRotationZ : (refRotationZ == 90.0f) ? 90.0f : (90.0f - refRotationZ));

					fvec3 newAabbSize;

					if(refRotationX > refRotationY && refRotationX > refRotationZ)
					{
						const auto xSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.x)));
						const auto xCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.x)));

						newAabbSize.x = max(MIN_SIZE, parentSize.x);
						newAabbSize.y = max(MIN_SIZE, (xCosRotation * parentSize.y));
						newAabbSize.z = max(MIN_SIZE, (xSinRotation * parentSize.y));
					}
					else if(refRotationY > refRotationX && refRotationY > refRotationZ)
					{
						const auto ySinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.y)));
						const auto yCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.y)));

						newAabbSize.x = max(MIN_SIZE, (yCosRotation * parentSize.x));
						newAabbSize.y = max(MIN_SIZE, parentSize.y);
						newAabbSize.z = max(MIN_SIZE, (ySinRotation * parentSize.x));
					}
					else if(refRotationZ > refRotationX && refRotationZ > refRotationY)
					{
						const auto zSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.z)));
						const auto zCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.z)));

						newAabbSize.x = max(MIN_SIZE, ((zCosRotation * parentSize.x) + (zSinRotation * parentSize.y)));
						newAabbSize.y = max(MIN_SIZE, ((zSinRotation * parentSize.x) + (zCosRotation * parentSize.y)));
						newAabbSize.z = MIN_SIZE;
					}
					else
					{
						newAabbSize.x = max(MIN_SIZE, parentSize.x);
						newAabbSize.y = max(MIN_SIZE, parentSize.y);
						newAabbSize.z = MIN_SIZE;
					}

					auto newAabbPosition = (parentPosition + aabb->getLocalPosition());

					if(!aabb->isCentered())
					{
						newAabbPosition.y -= ((newAabbSize.y - parentSize.y) * 0.5f);
					}

					aabb->setBasePosition(newAabbPosition);
					aabb->setBaseSize(newAabbSize);

					if(!parentQuad3d->isVisible())
					{
						aabb->setVisible(false);
						aabb->setCollisionResponsive(false);
						aabb->setRaycastResponsive(false);
					}

					break;
				}
				case AabbParentType::TEXT3D:
				{
					auto foundPair = _text3dManager->getText3ds().find(aabb->getParentId());

					if(foundPair == _text3dManager->getText3ds().end())
					{
						abort();
					}

					const auto parentText3d = foundPair->second;
					const auto parentPosition = parentText3d->getPosition();
					const auto parentRotation = parentText3d->getRotation();
					const auto parentSize = parentText3d->getSize();

					float refRotationX = Mathematics::calculateReferenceAngle(parentRotation.x);
					float refRotationY = Mathematics::calculateReferenceAngle(parentRotation.y);
					float refRotationZ = Mathematics::calculateReferenceAngle(parentRotation.z);

					refRotationX = ((refRotationX <= 45.0f) ? refRotationX : (refRotationX == 90.0f) ? 90.0f : (90.0f - refRotationX));
					refRotationY = ((refRotationY <= 45.0f) ? refRotationY : (refRotationY == 90.0f) ? 90.0f : (90.0f - refRotationY));
					refRotationZ = ((refRotationZ <= 45.0f) ? refRotationZ : (refRotationZ == 90.0f) ? 90.0f : (90.0f - refRotationZ));

					fvec3 newAabbSize;

					if(refRotationX > refRotationY && refRotationX > refRotationZ)
					{
						const auto xSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.x)));
						const auto xCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.x)));

						newAabbSize.x = max(MIN_SIZE, parentSize.x);
						newAabbSize.y = max(MIN_SIZE, (xCosRotation * parentSize.y));
						newAabbSize.z = max(MIN_SIZE, (xSinRotation * parentSize.y));
					}
					else if(refRotationY > refRotationX && refRotationY > refRotationZ)
					{
						const auto ySinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.y)));
						const auto yCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.y)));

						newAabbSize.x = max(MIN_SIZE, (yCosRotation * parentSize.x));
						newAabbSize.y = max(MIN_SIZE, parentSize.y);
						newAabbSize.z = max(MIN_SIZE, (ySinRotation * parentSize.x));
					}
					else if(refRotationZ > refRotationX && refRotationZ > refRotationY)
					{
						const auto zSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.z)));
						const auto zCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.z)));

						newAabbSize.x = max(MIN_SIZE, ((zCosRotation * parentSize.x) + (zSinRotation * parentSize.y)));
						newAabbSize.y = max(MIN_SIZE, ((zSinRotation * parentSize.x) + (zCosRotation * parentSize.y)));
						newAabbSize.z = MIN_SIZE;
					}
					else
					{
						newAabbSize.x = max(MIN_SIZE, parentSize.x);
						newAabbSize.y = max(MIN_SIZE, parentSize.y);
						newAabbSize.z = MIN_SIZE;
					}

					auto newAabbPosition = (parentPosition + aabb->getLocalPosition());

					if(!aabb->isCentered())
					{
						newAabbPosition.y -= ((newAabbSize.y - parentSize.y) * 0.5f);
					}

					aabb->setBasePosition(newAabbPosition);
					aabb->setBaseSize(newAabbSize);

					if(!parentText3d->isVisible())
					{
						aabb->setVisible(false);
						aabb->setCollisionResponsive(false);
						aabb->setRaycastResponsive(false);
					}

					break;
				}
			}
		}

		if(aabb->isVisible())
		{
			aabb->updateTransformation();
		}
	}
}

void AabbManager::deleteAabb(const string & aabbId)
{
	if(!isAabbExisting(aabbId))
	{
		abort();
	}

	_aabbs.erase(aabbId);
}

void AabbManager::deleteAabbs()
{
	_aabbs.clear();
}

const bool AabbManager::isAabbExisting(const string & aabbId) const
{
	return (_aabbs.find(aabbId) != _aabbs.end());
}

const bool AabbManager::isAabbsExisting() const
{
	return !_aabbs.empty();
}