#include "sky_entity_manager.hpp"
#include "render_storage.hpp"
#include "logger.hpp"

using std::make_shared;
using std::min;

constexpr float bufferData[] =
{
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

constexpr unsigned int bufferDataCount = static_cast<unsigned int>(sizeof(bufferData) / sizeof(float));

SkyEntityManager::SkyEntityManager()
	:
	_vertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS, bufferData, bufferDataCount))
{

}

void SkyEntityManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

shared_ptr<SkyEntity> SkyEntityManager::getEntity(const string& id)
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

shared_ptr<SkyEntity> SkyEntityManager::getSelectedEntity()
{
	if(_entities.empty() || _selectedEntityId.empty())
	{
		return nullptr;
	}

	return getEntity(_selectedEntityId);
}

const unordered_map<string, shared_ptr<SkyEntity>>& SkyEntityManager::getEntities()
{
	return _entities;
}

void SkyEntityManager::selectEntity(const string& id)
{
	if(!isEntityExisting(id) && !id.empty())
	{
		abort();
	}

	_selectedEntityId = id;
}

void SkyEntityManager::createEntity(const string& id)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto entity = make_shared<SkyEntity>(id);

	entity->setVertexBuffer(_vertexBuffer);

	_entities.insert({id, entity});
}

void SkyEntityManager::update()
{
	auto entity = getSelectedEntity();

	if(entity != nullptr)
	{
		if(entity->isVisible())
		{
			entity->updateTransformation();
		}
	}
}

void SkyEntityManager::deleteEntity(const string& id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);

	if(id == _selectedEntityId)
	{
		selectEntity("");
	}
}

void SkyEntityManager::deleteEntities()
{
	_entities.clear();

	selectEntity("");
}

const bool SkyEntityManager::isEntityExisting(const string& id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool SkyEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}