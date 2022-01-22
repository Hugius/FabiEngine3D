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

shared_ptr<SkyEntity> SkyEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("SkyEntityManager::getEntity");
	}

	return iterator->second;
}

shared_ptr<SkyEntity> SkyEntityManager::getSelectedEntity()
{
	if(_entities.empty() || _selectedEntityID.empty())
	{
		return nullptr;
	}

	return getEntity(_selectedEntityID);
}

const unordered_map<string, shared_ptr<SkyEntity>>& SkyEntityManager::getEntities()
{
	return _entities;
}

void SkyEntityManager::selectEntity(const string& ID)
{
	if(!isEntityExisting(ID) && !ID.empty())
	{
		Logger::throwError("SkyEntityManager::selectEntity");
	}

	_selectedEntityID = ID;

	if(_selectedEntityID.empty())
	{

	}
}

void SkyEntityManager::createEntity(const string& ID)
{
	auto entity = make_shared<SkyEntity>(ID);

	_entities.insert(make_pair(ID, entity));

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

void SkyEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("SkyEntityManager::deleteEntity");
	}

	_entities.erase(ID);

	if(ID == _selectedEntityID)
	{
		selectEntity("");
	}
}

void SkyEntityManager::deleteEntities()
{
	_entities.clear();

	selectEntity("");
}

const bool SkyEntityManager::isEntityExisting(const string& ID) const
{
	return (_entities.find(ID) != _entities.end());
}