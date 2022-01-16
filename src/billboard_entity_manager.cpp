#include "billboard_entity_manager.hpp"
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

BillboardEntityManager::BillboardEntityManager()
	:
	_centeredMesh(make_shared<VertexBuffer>(VertexBufferType::POS_UV, centeredBufferData, centeredBufferDataCount)),
	_standingMesh(make_shared<VertexBuffer>(VertexBufferType::POS_UV, standingBufferData, standingBufferDataCount))
{

}

void BillboardEntityManager::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
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
	auto entity = make_shared<BillboardEntity>(ID);

	_entities.insert(make_pair(ID, entity));

	entity->setMesh(isCentered ? _centeredMesh : _standingMesh);
	entity->setCentered(isCentered);
}

void BillboardEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();

		if(entity->isVisible())
		{
			const auto facingX = entity->isFacingCameraX();
			const auto facingY = entity->isFacingCameraY();

			if(facingX || facingY)
			{
				auto position = (entity->getPosition() + fvec3(0.0f, (entity->getSize().y / 2.0f), 0.0f));
				auto direction = (position - _renderBus->getCameraPosition());

				auto degreesX = Math::convertToDegrees(atan2f(direction.y, fabsf(direction.x) + fabsf(direction.z)));
				auto degreesY = Math::convertToDegrees(atan2f(direction.z, direction.x));

				auto rotation = entity->getRotation();
				rotation.x = (degreesX) * static_cast<float>(facingX);
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

const bool BillboardEntityManager::isEntityExisting(const string& ID) const
{
	return (_entities.find(ID) != _entities.end());
}