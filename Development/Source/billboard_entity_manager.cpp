#include "billboard_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

const float vertex_data[] =
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
	_renderBuffer(std::make_shared<RenderBuffer>(BufferType::VERTEX_UV, vertex_data, static_cast<unsigned int>(sizeof(vertex_data) / sizeof(float))))
{

}

shared_ptr<BillboardEntity> BillboardEntityManager::getEntity(const string& ID)
{
	auto result = _getBillboardEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Non-existing billboard entity with ID \"" + ID + "\" requested!");
	}

	return result;
}

const unordered_map<string, shared_ptr<BillboardEntity>>& BillboardEntityManager::getEntities()
{
	return _getBillboardEntities();
}

void BillboardEntityManager::createEntity(const string& ID, Vec3 color, Vec3 position, Vec3 rotation, Vec3 size,
	bool facingCameraX, bool facingCameraY)
{
	// Create entity
	_createEntity(ID);	

	// Set properties
	auto entity = getEntity(ID);
	entity->setRenderBuffer(_renderBuffer);
	entity->setPosition(position);
	entity->setRotation(rotation);
	entity->setInitialRotation(rotation);
	entity->setSize(size);
	entity->setCameraFacingX(facingCameraX);
	entity->setCameraFacingY(facingCameraY);
	entity->setColor(color);
}

void BillboardEntityManager::createEntity
(
	const string& ID, const string& diffuseMapPath,
	Vec3 position, Vec3 rotation, Vec3 size,
	bool transparent, bool facingCameraX, bool facingCameraY
)
{
	// Create entity
	createEntity(ID, Vec3(1.0f), position, rotation, size, facingCameraX, facingCameraY);

	// Set properties
	auto entity = getEntity(ID);
	entity->setDiffuseMap(_textureLoader.getTexture2D(diffuseMapPath, true, true));
	entity->setDiffuseMapPath(diffuseMapPath);
	entity->setTransparent(transparent);
}

void BillboardEntityManager::createEntity
(
	const string& ID, const string& textContent,
	const string& fontPath, Vec3 color,
	Vec3 position, Vec3 rotation, Vec3 size, bool facingCameraX, bool facingCameraY
)
{
	// Create entity
	createEntity(ID, color, position, rotation, size, facingCameraX, facingCameraY);

	// Set properties
	auto entity = getEntity(ID);
	entity->setDiffuseMap(_textureLoader.getText(textContent, fontPath));
	entity->setTransparent(true);
	entity->setTextContent(textContent);
	entity->setFontPath(fontPath);
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