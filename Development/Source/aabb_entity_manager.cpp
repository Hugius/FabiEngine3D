#include "aabb_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp" 
#include "tools.hpp"


AabbEntityManager::AabbEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::AABB, meshLoader, texLoader, renderBus)
{
	float box_data[] =
	{
		-0.5f,  1.0f, -0.5f,
		 0.5f,  1.0f, -0.5f,
		 0.5f,  0.0f, -0.5f,
		-0.5f,  0.0f, -0.5f,
		-0.5f,  1.0f, -0.5f,
		-0.5f,  1.0f,  0.5f,
		 0.5f,  1.0f,  0.5f,
		 0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f,  0.5f,
		-0.5f,  1.0f,  0.5f,
		 0.5f,  1.0f,  0.5f,
		 0.5f,  1.0f, -0.5f,
		 0.5f,  0.0f, -0.5f,
		 0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f, -0.5f
	};

	_renderBuffer = new RenderBuffer(BufferType::AABB, box_data, sizeof(box_data) / sizeof(float));
}

shared_ptr<AabbEntity> AabbEntityManager::getEntity(const string& ID)
{
	auto result = _getAabbEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Non-existing AABB entity with ID \"" + ID + "\" requested");
	}

	return result;
}

const unordered_map<string, shared_ptr<AabbEntity>>& AabbEntityManager::getEntities()
{
	return _getAabbEntities();
}

void AabbEntityManager::addAabbEntity(const string& ID, Vec3 position, Vec3 size, bool raycastResponsive, bool collisionResponsive)
{
	// Create entity
	_createEntity(ID);
	auto entity = getEntity(ID);
	entity->addRenderBuffer(_renderBuffer, false);

	// Miscellaneous
	entity->setLocalTranslation(position);
	entity->setLocalScaling(size);
	entity->setTranslation(position);
	entity->setScaling(size);
	entity->setRaycastResponsive(raycastResponsive);
	entity->setCollisionResponsive(collisionResponsive);
}

void AabbEntityManager::bindAabbEntity(const string& ID, const string& parentID, AabbParentType parentType, 
	Vec3 position, Vec3 size, bool raycastResponsive, bool collisionResponsive)
{
	addAabbEntity(ID, position, size, raycastResponsive, collisionResponsive);
	getEntity(ID)->setParent(parentID, parentType);
}

void AabbEntityManager::update(
	const unordered_map<string, shared_ptr<ModelEntity>>& modelEntities, 
	const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities)
{
	for (const auto& [keyID, entity] : _getAabbEntities())
	{
		// Check if AABB has parent
		if (entity->hasParent())
		{
			// Determine parent type
			if (entity->getParentType() == AabbParentType::MODEL_ENTITY)
			{
				// Try to find the parent entity
				auto foundPair = modelEntities.find(entity->getParentID());
				if(foundPair != modelEntities.end())
				{
					// Retrieve parent entity
					auto parentEntity = foundPair->second;

					// Model entity must not be LODded
					if (!parentEntity->isLevelOfDetailed())
					{
						// Retrieve maximum rotation & direction (based on parent rotation)
						Direction rotationDirection = Direction();
						Vec3 parentRotation = parentEntity->getRotation();
						float rotation = 0.0f;
						if (fabsf(parentRotation.x) > fabsf(parentRotation.y) && fabsf(parentRotation.x) > fabsf(parentRotation.z))
						{
							rotationDirection = Direction::X;
							rotation = parentRotation.x;
						}
						else if (fabsf(parentRotation.y) > fabsf(parentRotation.x) && fabsf(parentRotation.y) > fabsf(parentRotation.z))
						{
							rotationDirection = Direction::Y;
							rotation = parentRotation.y;
						}
						else if (fabsf(parentRotation.z) > fabsf(parentRotation.x) && fabsf(parentRotation.z) > fabsf(parentRotation.y))
						{
							rotationDirection = Direction::Z;
							rotation = parentRotation.z;
						}

						// Update scaling (based on parent scaling & AABB rotation)
						Vec3 localScaling = (entity->getLocalScaling() * parentEntity->getScaling());
						entity->setScaling(localScaling);
						if ((fabsf(rotation) > 45.0f && fabsf(rotation) < 135.0f) || (fabsf(rotation) > 225.0f && fabsf(rotation) < 315.0f))
						{
							// Determine rotation direction
							if (rotationDirection == Direction::X)
							{
								entity->setScaling(Vec3(localScaling.y, localScaling.x, localScaling.z));
							}
							else if (rotationDirection == Direction::Y)
							{
								entity->setScaling(Vec3(localScaling.z, localScaling.y, localScaling.x));
							}
							else if (rotationDirection == Direction::Z)
							{
								entity->setScaling(Vec3(localScaling.x, localScaling.z, localScaling.y));
							}
						}

						// Update translation (based on parent translation + rotation + scaling)
						Vec3 localTranslation = (entity->getLocalTranslation() * parentEntity->getScaling());
						float roundedRotation = 
							(rotation > 45.0f && rotation < 135.0f) ? 90.0f : // 90 degrees rounded
							(rotation >= 135.0f && rotation <= 225.0f) ? 180.0f : // 180 degrees rounded
							(rotation > 225.0f && rotation < 315.0f) ? 270.0f : // 270 degrees rounded
							(rotation < -45.0f && rotation > -135.0f) ? -90.0f : // -90 degrees rounded
							(rotation <= -135.0f && rotation >= -225.0f) ? -180.0f : // -180 degrees rounded
							(rotation < -225.0f && rotation > -315.0f) ? -270.0f : // -270 degrees rounded
							0.0f; // No rotation
						if (roundedRotation != 0.0f)
						{
							/* Note:
								X & Z directions are different, because the model is rotated around Vec3(0.0f) but is standing on Y 0.0f (local).
								The AABB is ALSO standing on Y 0.0f (local), so it needs a negative Y offset after the rotation.
							*/

							// Temporary values
							Matrix44 rotationMatrix = Matrix44(1.0f);
							Vec3 localOffset = Vec3(0.0f, (entity->getLocalScaling().y / 2.0f), 0.0f);
							bool isMirrored = (roundedRotation == -180.0f || roundedRotation == 180.0f);
							localTranslation = (rotationDirection == Direction::Y) ? localTranslation : 
								(entity->getLocalTranslation() + localOffset) * parentEntity->getScaling();
							float yOffset = (rotationDirection == Direction::Y) ? 0.0f : 
								-((isMirrored ? localScaling.y : localScaling.x) / 2.0f);

							// Determine rotation direction
							if (rotationDirection == Direction::X)
							{
								rotationMatrix = Matrix44::createRotationX(Math::degreesToRadians(roundedRotation));
							}
							else if (rotationDirection == Direction::Y)
							{
								rotationMatrix = Matrix44::createRotationY(Math::degreesToRadians(roundedRotation));
							}
							else if (rotationDirection == Direction::Z)
							{
								rotationMatrix = Matrix44::createRotationZ(Math::degreesToRadians(roundedRotation));
							}

							// Apply rotation
							Vec4 result = rotationMatrix * Vec4(localTranslation.x, localTranslation.y, localTranslation.z, 1.0f);
							entity->setTranslation(parentEntity->getTranslation() + Vec3(result.x, result.y + yOffset, result.z));
						}
						else // No rotation
						{
							entity->setTranslation(parentEntity->getTranslation() + localTranslation);
						}

						// Update visibility
						entity->setVisible(parentEntity->isVisible());
					}
				}
				else
				{
					Logger::throwError("AABB entity with ID \"" + entity->getID() + "\" bound to non-existing model entity with ID \"" + entity->getParentID() + "\"");
				}
			}
			else
			{
				// Try to find the parent entity
				auto foundPair = billboardEntities.find(entity->getParentID());
				if (foundPair != billboardEntities.end())
				{
					// Temporary values
					auto parentEntity = foundPair->second;
					const auto parentSize = parentEntity->getScaling();
					auto newAabbSize = Vec3(parentSize.x, parentSize.y, 0.0f);

					// Retrieve absolute rotations
					const float rotationX = fabsf(parentEntity->getRotation().x);
					const float rotationY = fabsf(parentEntity->getRotation().y);
					const float rotationZ = fabsf(parentEntity->getRotation().z);

					// Calculate reference rotation & convert it to 0-45 range
					float refRotationX = Math::calculateReferenceAngle(rotationX);
					float refRotationY = Math::calculateReferenceAngle(rotationY);
					float refRotationZ = Math::calculateReferenceAngle(rotationZ);
					refRotationX = ((refRotationX <= 45.0f) ? refRotationX : (refRotationX == 90.0f) ? 90.0f : (90.0f - refRotationX));
					refRotationY = ((refRotationY <= 45.0f) ? refRotationY : (refRotationY == 90.0f) ? 90.0f : (90.0f - refRotationY));
					refRotationZ = ((refRotationZ <= 45.0f) ? refRotationZ : (refRotationZ == 90.0f) ? 90.0f : (90.0f - refRotationZ));
					
					// Determine direction to use
					if (refRotationX > refRotationY && refRotationX > refRotationZ)
					{
						const auto xSinRotation = fabsf(sinf(Math::degreesToRadians(rotationX)));
						const auto xCosRotation = fabsf(cosf(Math::degreesToRadians(rotationX)));
						newAabbSize.x = (xCosRotation * parentSize.x) + (xSinRotation * parentSize.y);
						newAabbSize.y = (xSinRotation * parentSize.x) + (xCosRotation * parentSize.y);
					}
					else if (refRotationY > refRotationX && refRotationY > refRotationZ)
					{
						const auto ySinRotation = fabsf(sinf(Math::degreesToRadians(rotationY)));
						const auto yCosRotation = fabsf(cosf(Math::degreesToRadians(rotationY)));
						newAabbSize.x = (yCosRotation * parentSize.x);
						newAabbSize.z = (ySinRotation * parentSize.x);
					}
					else if (refRotationZ > refRotationX && refRotationZ > refRotationY)
					{
						const auto zSinRotation = fabsf(sinf(Math::degreesToRadians(rotationZ)));
						const auto zCosRotation = fabsf(cosf(Math::degreesToRadians(rotationZ)));
						newAabbSize.y = (zCosRotation * parentSize.y);
						newAabbSize.z = (zSinRotation * parentSize.y);
					}

					// AABB must still be a box (cannot be flat)
					newAabbSize.x = std::max(newAabbSize.x, 0.1f);
					newAabbSize.y = std::max(newAabbSize.y, 0.1f);
					newAabbSize.z = std::max(newAabbSize.z, 0.1f);

					// Calculate Y offset, because rotation is around center while billboard is not centered
					float yOffset = -((newAabbSize.y - parentSize.y) / 2.0f);

					// Update scaling (based on parent rotation)
					entity->setScaling(newAabbSize);

					// Update translation (based on parent translation + scaling)
					entity->setTranslation(parentEntity->getTranslation() + entity->getLocalTranslation() + Vec3(0.0f, yOffset, 0.0f));

					// Update visibility
					entity->setVisible(parentEntity->isVisible());
				}
			}
		}

		// Calculate model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}
	}
}