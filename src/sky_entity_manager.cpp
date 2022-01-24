#include "sky_entity_manager.hpp"
#include "render_bus.hpp"
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
	_mesh(make_shared<VertexBuffer>(VertexBufferType::POS, bufferData, bufferDataCount))
{

}

void SkyEntityManager::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
}

shared_ptr<SkyEntity> SkyEntityManager::getEntity(const string& id)
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		Logger::throwError("SkyEntityManager::getEntity");
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
		Logger::throwError("SkyEntityManager::selectEntity");
	}

	_selectedEntityId = id;

	if(_selectedEntityId.empty())
	{

	}
}

void SkyEntityManager::createEntity(const string& id)
{
	auto entity = make_shared<SkyEntity>(id);

	_entities.insert(make_pair(id, entity));

	entity->setMesh(_mesh);
}

void SkyEntityManager::update()
{
	auto entity = getSelectedEntity();

	if(entity != nullptr)
	{
		if(entity->isVisible())
		{
			entity->updateRotationMatrix();
		}
	}
}

void SkyEntityManager::deleteEntity(const string& id)
{
	if(!isEntityExisting(id))
	{
		Logger::throwError("SkyEntityManager::deleteEntity");
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