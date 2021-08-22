#include "billboard_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

using std::make_shared;

const float bufferData[] =
{
	-0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
	 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, 1.0f, 0.0f, 0.0f, 1.0f
};

BillboardEntityManager::BillboardEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus, Camera& camera)
	:
	BaseEntityManager(EntityType::BILLBOARD, meshLoader, texLoader, renderBus),
	_camera(camera),
	_renderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX_UV, bufferData, static_cast<unsigned int>(sizeof(bufferData) / sizeof(float))))
{

}

shared_ptr<BillboardEntity> BillboardEntityManager::getEntity(const string& ID)
{
	auto result = _getBillboardEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("BillboardEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<BillboardEntity>>& BillboardEntityManager::getEntities()
{
	return _getBillboardEntities();
}

void BillboardEntityManager::createEntity(const string& ID)
{
	_createEntity(ID);
	getEntity(ID)->setRenderBuffer(_renderBuffer);
}

void BillboardEntityManager::update()
{
	for (const auto& [keyID, entity] : _getBillboardEntities())
	{
		// 3D camera facing
		auto facingX = entity->isFacingCameraX();
		auto facingY = entity->isFacingCameraY();
		Vec3 rotation = entity->getRotation();
		if (facingX || facingY)
		{
			// Calculate center of billboard
			Vec3 position = (entity->getPosition() + Vec3(0.0f, (entity->getSize().y / 2.0f), 0.0f));

			// Calculate direction
			Vec3 direction = (position - _renderBus.getCameraPosition());

			// Calculate angles
			float degreesZ = atan2f(direction.y, fabsf(direction.x) + fabsf(direction.z));
			float degreesY = atan2f(direction.z, direction.x);

			// Convert to degrees
			degreesZ = Math::radiansToDegrees(degreesZ);
			degreesY = Math::radiansToDegrees(degreesY);

			// Apply rotation angles
			rotation.z = (degreesZ) * static_cast<float>(facingX);
			rotation.y = (-(degreesY) - 90.0f) * static_cast<float>(facingY);
		}

		// Update rotation
		entity->setRotation(rotation);

		// Update model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}

		// Update sprite animations
		if (entity->isSpriteAnimationStarted() && !entity->isSpriteAnimationPaused() && 
			(entity->getSpriteAnimationLoops() != entity->getMaxSpriteAnimationLoops()))
		{
			if (entity->getPassedSpriteAnimationFrames() >= entity->getMaxSpriteAnimationFramestep()) // Is allowed to update
			{
				entity->resetPassedSpriteAnimationFrames(); // Reset counter

				if (entity->getSpriteAnimationColumnIndex() >= entity->getTotalSpriteAnimationColumns() - 1) // Reached total columns
				{
					entity->setSpriteAnimationColumnIndex(0); // Reset column index

					if (entity->getSpriteAnimationRowIndex() >= entity->getTotalSpriteAnimationRows() - 1) // Reached total rows
					{
						entity->increaseSpriteAnimationLoops();
						entity->setSpriteAnimationRowIndex(0); // Reset row index (animation finished)
					}
					else // Next row
					{
						entity->setSpriteAnimationRowIndex(entity->getSpriteAnimationRowIndex() + 1);
					}
				}
				else // Next column
				{
					entity->setSpriteAnimationColumnIndex(entity->getSpriteAnimationColumnIndex() + 1);
				}
			}
			else // Increase counter
			{
				entity->increasePassedSpriteAnimationFrames();
			}
		}
	}
}