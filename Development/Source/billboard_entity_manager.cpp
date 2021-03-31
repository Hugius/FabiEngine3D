#include "billboard_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"
#include "mathematics.hpp"

BillboardEntityManager::BillboardEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus, CameraManager& camera) :
	BaseEntityManager(EntityType::BILLBOARD, meshLoader, texLoader, renderBus),
	_camera(camera)
{
	float plane_data[] =
	{
		-0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	_renderBuffer = new RenderBuffer(BufferType::SURFACE, plane_data, sizeof(plane_data) / sizeof(float));
}

shared_ptr<BillboardEntity> BillboardEntityManager::getEntity(const string& ID)
{
	auto result = _getBillboardEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting BILLBOARD entity with ID \"" + ID + "\" requested");
	}

	return result;
}

const unordered_map<string, shared_ptr<BillboardEntity>>& BillboardEntityManager::getEntities()
{
	return _getBillboardEntities();
}

void BillboardEntityManager::addBillboardEntity(const string& ID, Vec3 color, Vec3 T, Vec3 R, Vec3 S, bool facingCameraX, bool facingCameraY)
{
	// Create entity
	_createEntity(ID);
	auto entity = getEntity(ID);
	entity->addRenderBuffer(_renderBuffer, false);

	// Other
	entity->setTranslation(T);
	entity->setRotation(R);
	entity->setInitialRotation(R);
	entity->setScaling(S);
	entity->setCameraFacingX(facingCameraX);
	entity->setCameraFacingY(facingCameraY);
	entity->setColor(color);
}

void BillboardEntityManager::addBillboardEntity
(
	const string& ID, const string& texturePath,
	Vec3 T, Vec3 R, Vec3 S,
	bool transparent, bool facingCameraX, bool facingCameraY
)
{
	addBillboardEntity(ID, Vec3(1.0f), T, R, S, facingCameraX, facingCameraY);

	auto entity = getEntity(ID);
	entity->setDiffuseMap(_textureLoader.getTexture2D(texturePath, false, true, false));
	entity->setDiffuseMapPath(texturePath);
	entity->setTransparent(transparent);
}

void BillboardEntityManager::addBillboardEntity
(
	const string& ID, const string& text,
	const string& fontPath, Vec3 color,
	Vec3 T, Vec3 R, Vec3 S, bool facingCameraX, bool facingCameraY
)
{
	addBillboardEntity(ID, color, T, R, S, facingCameraX, facingCameraY);

	auto entity = getEntity(ID);
	entity->setDiffuseMap(_textureLoader.getText(text, fontPath));
	entity->setTransparent(true);
	entity->setTextContent(text);
	entity->setFontPath(fontPath);
}

void BillboardEntityManager::update()
{
	for (auto& [keyID, entity] : _getBillboardEntities())
	{
		// 3D camera facing
		auto facingX = entity->isCameraFacingX();
		auto facingY = entity->isCameraFacingY();
		Vec3 rotation = entity->getRotation();
		if (facingX || facingY)
		{
			// Calculate direction
			Vec3 direction = entity->getTranslation() - _renderBus.getCameraPosition();

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

		// Calculate model matrix
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