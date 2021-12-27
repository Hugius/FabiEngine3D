#include "aabb_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp" 
#include "tools.hpp"

using std::make_shared;
using std::max;

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

constexpr unsigned int centeredBufferCount = static_cast<unsigned int>(sizeof(centeredBufferData) / sizeof(float));
constexpr unsigned int standingBufferCount = static_cast<unsigned int>(sizeof(centeredBufferData) / sizeof(float));

AabbEntityManager::AabbEntityManager()
	:
	_centeredRenderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX, centeredBufferData, centeredBufferCount)),
	_standingRenderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX, standingBufferData, standingBufferCount))
{

}

shared_ptr<AabbEntity> AabbEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("AabbEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<AabbEntity>>& AabbEntityManager::getEntities()
{
	return _entities;
}

void AabbEntityManager::createEntity(const string& ID, bool isCentered)
{
	_entities.insert(make_pair(ID, make_shared<AabbEntity>(ID)));
	getEntity(ID)->setRenderBuffer(isCentered ? _centeredRenderBuffer : _standingRenderBuffer);
	getEntity(ID)->setCentered(isCentered);
}

void AabbEntityManager::update(const unordered_map<string, shared_ptr<ModelEntity>>& modelEntities, const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities)
{
	for(const auto& [keyID, entity] : _entities)
	{
		if(!entity->hasParent())
		{
			entity->updateTransformation();
			goto SKIP;
		}

		if(entity->getParentEntityType() == AabbParentEntityType::MODEL)
		{
			auto foundPair = modelEntities.find(entity->getParentEntityID());

			if(foundPair == modelEntities.end())
			{
				Logger::throwError("AabbEntityManager::update::1");
			}

			auto parentEntity = foundPair->second;

			if(parentEntity->isLevelOfDetailed())
			{
				goto SKIP;
			}

			if(entity->mustFollowParentEntityTransformation())
			{
				const auto newAabbSize = (entity->getLocalSize() * parentEntity->getBaseSize());
				const auto parentRotation = parentEntity->getBaseRotation();

				Direction rotationDirection;
				float rotation = 0.0f;
				if((parentRotation.x > parentRotation.y) && (parentRotation.x > parentRotation.z))
				{
					rotationDirection = Direction::X;
					rotation = parentRotation.x;
				}
				if((parentRotation.y > parentRotation.x) && (parentRotation.y > parentRotation.z))
				{
					rotationDirection = Direction::Y;
					rotation = parentRotation.y;
				}
				if((parentRotation.z > parentRotation.x) && (parentRotation.z > parentRotation.y))
				{
					rotationDirection = Direction::Z;
					rotation = parentRotation.z;
				}

				const bool is90Degrees = ((rotation > 45.0f) && (rotation < 135.0f));
				const bool is180Degrees = ((rotation >= 135.0f) && (rotation <= 225.0f));
				const bool is270Degrees = ((rotation > 225.0f) && (rotation < 315.0f));
				const float roundedRotation = (is90Degrees ? 90.0f : is180Degrees ? 180.0f : is270Degrees ? 270.0f : 0.0f);

				if(is90Degrees || is270Degrees)
				{
					if(rotationDirection == Direction::X)
					{
						entity->setSize(fvec3(newAabbSize.x, newAabbSize.z, newAabbSize.y));
					}
					else if(rotationDirection == Direction::Y)
					{
						entity->setSize(fvec3(newAabbSize.z, newAabbSize.y, newAabbSize.x));
					}
					else if(rotationDirection == Direction::Z)
					{
						entity->setSize(fvec3(newAabbSize.y, newAabbSize.x, newAabbSize.z));
					}
				}
				else
				{
					entity->setSize(newAabbSize);
				}

				if((roundedRotation == 0.0f) || entity->isCentered())
				{
					const fvec3 localPosition = (entity->getLocalPosition() * parentEntity->getBaseSize());
					entity->setPosition(parentEntity->getBasePosition() + localPosition);
				}
				else
				{
					const fvec3 localOffset = fvec3(0.0f, (entity->getLocalSize().y / 2.0f), 0.0f);
					const fvec3 localPosition = (rotationDirection == Direction::Y) ? localPosition :
						(entity->getLocalPosition() + localOffset) * parentEntity->getBaseSize();

					mat44 rotationMatrix;
					float yOffset;
					if(rotationDirection == Direction::X)
					{
						rotationMatrix = Math::createRotationMatrixX(Math::convertToRadians(roundedRotation));
						yOffset = ((is180Degrees ? newAabbSize.y : newAabbSize.z) / 2.0f);
					}
					else if(rotationDirection == Direction::Y)
					{
						rotationMatrix = Math::createRotationMatrixY(Math::convertToRadians(roundedRotation));
						yOffset = 0.0f;
					}
					else if(rotationDirection == Direction::Z)
					{
						rotationMatrix = Math::createRotationMatrixZ(Math::convertToRadians(roundedRotation));
						yOffset = ((is180Degrees ? newAabbSize.y : newAabbSize.x) / 2.0f);
					}

					auto rotatedLocalPosition = (rotationMatrix * fvec4(localPosition.x, localPosition.y, localPosition.z, 1.0f));
					rotatedLocalPosition.y -= yOffset;
					entity->setPosition(parentEntity->getBasePosition() + rotatedLocalPosition);
				}
			}

			if(entity->mustFollowParentEntityVisibility())
			{
				entity->setVisible(parentEntity->isVisible());
			}

			if(parentEntity->isFrozen())
			{
				entity->setVisible(false);
			}
		}
		else
		{
			auto foundPair = billboardEntities.find(entity->getParentEntityID());
			if(foundPair == billboardEntities.end())
			{
				Logger::throwError("AabbEntityManager::update::2");
			}

			auto parentEntity = foundPair->second;

			if(entity->mustFollowParentEntityTransformation())
			{
				const auto parentPosition = parentEntity->getPosition();
				const auto parentRotation = parentEntity->getRotation();
				const auto parentSize = parentEntity->getSize();

				float refRotationX = Math::calculateReferenceAngle(parentRotation.x);
				float refRotationY = Math::calculateReferenceAngle(parentRotation.y);
				float refRotationZ = Math::calculateReferenceAngle(parentRotation.z);
				refRotationX = ((refRotationX <= 45.0f) ? refRotationX : (refRotationX == 90.0f) ? 90.0f : (90.0f - refRotationX));
				refRotationY = ((refRotationY <= 45.0f) ? refRotationY : (refRotationY == 90.0f) ? 90.0f : (90.0f - refRotationY));
				refRotationZ = ((refRotationZ <= 45.0f) ? refRotationZ : (refRotationZ == 90.0f) ? 90.0f : (90.0f - refRotationZ));

				fvec3 newAabbSize;
				if(refRotationX > refRotationY && refRotationX > refRotationZ)
				{
					const auto xSinRotation = fabsf(sinf(Math::convertToRadians(parentRotation.x)));
					const auto xCosRotation = fabsf(cosf(Math::convertToRadians(parentRotation.x)));
					newAabbSize.x = max(MIN_SIZE, parentSize.x);
					newAabbSize.y = max(MIN_SIZE, (xCosRotation * parentSize.y));
					newAabbSize.z = max(MIN_SIZE, (xSinRotation * parentSize.y));
				}
				else if(refRotationY > refRotationX && refRotationY > refRotationZ)
				{
					const auto ySinRotation = fabsf(sinf(Math::convertToRadians(parentRotation.y)));
					const auto yCosRotation = fabsf(cosf(Math::convertToRadians(parentRotation.y)));
					newAabbSize.x = max(MIN_SIZE, (yCosRotation * parentSize.x));
					newAabbSize.y = max(MIN_SIZE, parentSize.y);
					newAabbSize.z = max(MIN_SIZE, (ySinRotation * parentSize.x));
				}
				else if(refRotationZ > refRotationX && refRotationZ > refRotationY)
				{
					const auto zSinRotation = fabsf(sinf(Math::convertToRadians(parentRotation.z)));
					const auto zCosRotation = fabsf(cosf(Math::convertToRadians(parentRotation.z)));
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

				fvec3 newAabbPosition = (parentPosition + entity->getLocalPosition());
				newAabbPosition.y -= ((newAabbSize.y - parentSize.y) / 2.0f);

				entity->setPosition(newAabbPosition);
				entity->setSize(newAabbSize);
			}

			if(entity->mustFollowParentEntityVisibility())
			{
				entity->setVisible(parentEntity->isVisible());
			}

			if(parentEntity->isFrozen())
			{
				entity->setVisible(false);
			}
		}

		SKIP:;

		if(entity->isVisible())
		{
			entity->updateTransformationMatrix();
		}
	}
}

void AabbEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("AabbEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void AabbEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool AabbEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}