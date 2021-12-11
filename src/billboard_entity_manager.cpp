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

BillboardEntityManager::BillboardEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus, Camera& camera)
	:
	BaseEntityManager(EntityType::BILLBOARD, meshLoader, textureLoader, renderBus),
	_camera(camera),
	_renderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX_UV, bufferData, static_cast<unsigned int>(sizeof(bufferData) / sizeof(float))))
{

}

shared_ptr<BillboardEntity> BillboardEntityManager::getEntity(const string& ID)
{
	auto result = _getBillboardEntity(ID);

	if(result == nullptr)
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
	for(const auto& [keyID, entity] : _getBillboardEntities())
	{
		// Update transformation
		entity->updateTransformation();

		// Update billboard if visible
		if(entity->isVisible())
		{
			// 3D camera facing
			auto facingX = entity->isFacingCameraX();
			auto facingY = entity->isFacingCameraY();
			fvec3 rotation = entity->getRotation();
			if(facingX || facingY)
			{
				// Calculate center of billboard
				fvec3 position = (entity->getPosition() + fvec3(0.0f, (entity->getSize().y / 2.0f), 0.0f));

				// Calculate direction
				fvec3 direction = (position - _renderBus.getCameraPosition());

				// Calculate angles
				float degreesZ = atan2f(direction.y, fabsf(direction.x) + fabsf(direction.z));
				float degreesY = atan2f(direction.z, direction.x);

				// Convert to degrees
				degreesZ = Math::convertToDegrees(degreesZ);
				degreesY = Math::convertToDegrees(degreesY);

				// Apply rotation angles
				rotation.z = (degreesZ) * static_cast<float>(facingX);
				rotation.y = (-degreesY - 90.0f) * static_cast<float>(facingY);

				// Update rotation
				entity->setRotation(rotation);
			}

			// Update transformation matrix
			entity->updateTransformationMatrix();
		}
	}
}