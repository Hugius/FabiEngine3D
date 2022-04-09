#include "quad3d_entity_manager.hpp"
#include "render_storage.hpp"
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
	_centeredVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, centeredBufferData, centeredBufferDataCount)),
	_standingVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, standingBufferData, standingBufferDataCount))
{

}

void Quad3dEntityManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Quad3dEntityManager::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

const shared_ptr<Quad3dEntity> Quad3dEntityManager::getEntity(const string & id) const
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Quad3dEntity>> & Quad3dEntityManager::getEntities() const
{
	return _entities;
}

void Quad3dEntityManager::createEntity(const string & id, bool isCentered)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto entity = make_shared<Quad3dEntity>(id);

	entity->setVertexBuffer(isCentered ? _centeredVertexBuffer : _standingVertexBuffer);
	entity->setCentered(isCentered);

	_entities.insert({id, entity});
}

void Quad3dEntityManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();

		if(!entity->isVisible())
		{
			continue;
		}

		const auto isFacingCameraHorizontally = entity->isFacingCameraHorizontally();
		const auto isFacingCameraVertically = entity->isFacingCameraVertically();

		if(isFacingCameraHorizontally || isFacingCameraVertically)
		{
			auto position = (entity->getPosition() + fvec3(0.0f, (entity->getSize().y * 0.5f), 0.0f));
			auto direction = (position - _camera->getPosition());

			auto degreesX = Mathematics::convertToDegrees(atan2f(direction.y, fabsf(direction.x) + fabsf(direction.z)));
			auto degreesY = Mathematics::convertToDegrees(atan2f(direction.z, direction.x));

			auto rotation = entity->getRotation();
			rotation.x = (degreesX * static_cast<float>(isFacingCameraHorizontally));
			rotation.y = ((-degreesY - 90.0f) * static_cast<float>(isFacingCameraVertically));

			entity->setRotation(rotation);
		}

		entity->updateTransformation();
	}
}

void Quad3dEntityManager::deleteEntity(const string & id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void Quad3dEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool Quad3dEntityManager::isEntityExisting(const string & id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool Quad3dEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}