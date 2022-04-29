#include "sky_entity_manager.hpp"
#include "render_storage.hpp"

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

constexpr int bufferDataCount = static_cast<int>(sizeof(bufferData) / sizeof(float));

SkyManager::SkyManager()
	:
	_vertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS, bufferData, bufferDataCount))
{

}

void SkyManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

const shared_ptr<SkyEntity> SkyManager::getEntity(const string & skyId) const
{
	auto iterator = _entities.find(skyId);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<SkyEntity> SkyManager::getSelectedEntity() const
{
	if(_entities.empty() || _selectedEntityId.empty())
	{
		return nullptr;
	}

	return getEntity(_selectedEntityId);
}

const unordered_map<string, shared_ptr<SkyEntity>> & SkyManager::getEntities() const
{
	return _entities;
}

void SkyManager::selectEntity(const string & skyId)
{
	if(!isEntityExisting(skyId) && !skyId.empty())
	{
		abort();
	}

	_selectedEntityId = skyId;
}

void SkyManager::createEntity(const string & skyId)
{
	if(isEntityExisting(skyId))
	{
		abort();
	}

	auto entity = make_shared<SkyEntity>(skyId);

	entity->setVertexBuffer(_vertexBuffer);

	_entities.insert({skyId, entity});
}

void SkyManager::update()
{
	auto entity = getSelectedEntity();

	if(entity != nullptr)
	{
		entity->updateTarget();

		if(entity->isVisible())
		{
			entity->updateTransformation();
		}
	}
}

void SkyManager::deleteEntity(const string & skyId)
{
	if(!isEntityExisting(skyId))
	{
		abort();
	}

	_entities.erase(skyId);

	if(skyId == _selectedEntityId)
	{
		selectEntity("");
	}
}

void SkyManager::deleteEntities()
{
	_entities.clear();

	selectEntity("");
}

const bool SkyManager::isEntityExisting(const string & skyId) const
{
	return (_entities.find(skyId) != _entities.end());
}

const bool SkyManager::isEntitiesExisting() const
{
	return !_entities.empty();
}