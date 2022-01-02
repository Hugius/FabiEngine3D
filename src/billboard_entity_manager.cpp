#include "billboard_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

using std::make_shared;

constexpr float centeredBufferData[] =
{
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};

constexpr float standingBufferData[] =
{
	-0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, 1.0f, 0.0f, 0.0f, 1.0f
};

constexpr unsigned int centeredBufferDataCount = static_cast<unsigned int>(sizeof(centeredBufferData) / sizeof(float));
constexpr unsigned int standingBufferDataCount = static_cast<unsigned int>(sizeof(standingBufferData) / sizeof(float));

BillboardEntityManager::BillboardEntityManager(RenderBus& renderBus, Camera& camera)
	:
	_renderBus(renderBus),
	_camera(camera),
	_centeredVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, centeredBufferData, centeredBufferDataCount)),
	_standingVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, standingBufferData, standingBufferDataCount))
{

}

shared_ptr<BillboardEntity> BillboardEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("BillboardEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<BillboardEntity>>& BillboardEntityManager::getEntities()
{
	return _entities;
}

void BillboardEntityManager::createEntity(const string& ID, bool isCentered)
{
	_entities.insert(make_pair(ID, make_shared<BillboardEntity>(ID)));
	getEntity(ID)->setVertexBuffer(isCentered ? _centeredVertexBuffer : _standingVertexBuffer);
	getEntity(ID)->setCentered(isCentered);
}

void BillboardEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();

		if(entity->isVisible())
		{
			auto facingX = entity->isFacingCameraX();
			auto facingY = entity->isFacingCameraY();
			fvec3 rotation = entity->getRotation();
			if(facingX || facingY)
			{
				fvec3 position = (entity->getPosition() + fvec3(0.0f, (entity->getSize().y / 2.0f), 0.0f));

				fvec3 direction = (position - _renderBus.getCameraPosition());

				float degreesZ = atan2f(direction.y, fabsf(direction.x) + fabsf(direction.z));
				float degreesY = atan2f(direction.z, direction.x);

				degreesZ = Math::convertToDegrees(degreesZ);
				degreesY = Math::convertToDegrees(degreesY);

				rotation.z = (degreesZ) * static_cast<float>(facingX);
				rotation.y = (-degreesY - 90.0f) * static_cast<float>(facingY);

				entity->setRotation(rotation);
			}

			entity->updateTransformationMatrix();
		}
	}
}

void BillboardEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("BillboardEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void BillboardEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool BillboardEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}