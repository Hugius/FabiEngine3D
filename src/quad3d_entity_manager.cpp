#include "quad3d_entity_manager.hpp"
#include "quad3d_entity_manager.hpp"
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

Quad3dEntityManager::Quad3dEntityManager()
	:
	_centeredMesh(make_shared<VertexBuffer>(VertexBufferType::POS_UV, centeredBufferData, centeredBufferDataCount)),
	_standingMesh(make_shared<VertexBuffer>(VertexBufferType::POS_UV, standingBufferData, standingBufferDataCount))
{

}

void Quad3dEntityManager::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
}

shared_ptr<Quad3dEntity> Quad3dEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("Quad3dEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<Quad3dEntity>>& Quad3dEntityManager::getEntities()
{
	return _entities;
}

void Quad3dEntityManager::createEntity(const string& ID, bool isCentered)
{
	auto entity = make_shared<Quad3dEntity>(ID);

	_entities.insert(make_pair(ID, entity));

	entity->setMesh(isCentered ? _centeredMesh : _standingMesh);
	entity->setCentered(isCentered);
}

void Quad3dEntityManager::update()
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

void Quad3dEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("Quad3dEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void Quad3dEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool Quad3dEntityManager::isEntityExisting(const string& ID) const
{
	return (_entities.find(ID) != _entities.end());
}