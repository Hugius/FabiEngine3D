#include "water_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<WaterEntity> WaterEntityManager::getEntity(const string& id)
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		Logger::throwError("WaterEntityManager::getEntity");
	}

	return iterator->second;
}

shared_ptr<WaterEntity> WaterEntityManager::getSelectedEntity()
{
	if(_entities.empty() || _selectedEntityId.empty())
	{
		return nullptr;
	}

	return getEntity(_selectedEntityId);
}

const unordered_map<string, shared_ptr<WaterEntity>>& WaterEntityManager::getEntities()
{
	return _entities;
}

void WaterEntityManager::selectEntity(const string& id)
{
	if(!isEntityExisting(id) && !id.empty())
	{
		Logger::throwError("WaterEntityManager::selectWater");
	}

	_selectedEntityId = id;
}

void WaterEntityManager::createEntity(const string& id)
{
	auto entity = make_shared<WaterEntity>(id);

	_entities.insert(make_pair(id, entity));

	loadMesh(id);
}

void WaterEntityManager::deleteEntity(const string& id)
{
	if(!isEntityExisting(id))
	{
		Logger::throwError("WaterEntityManager::deleteEntity");
	}

	_entities.erase(id);

	if(id == _selectedEntityId)
	{
		selectEntity("");
	}
}

void WaterEntityManager::deleteEntities()
{
	_entities.clear();

	selectEntity("");
}

void WaterEntityManager::loadMesh(const string& id)
{
	_loadMesh(getEntity(id), getEntity(id)->getSize());
}

const bool WaterEntityManager::isEntityExisting(const string& id) const
{
	return (_entities.find(id) != _entities.end());
}

void WaterEntityManager::_loadMesh(shared_ptr<WaterEntity> entity, float size)
{
	const float halfSize = (size * 0.5f);

	if(size > MAX_SIZE)
	{
		Logger::throwError("WaterEntityManager::loadMesh");
	}

	const float lowQualityBufferData[] =
	{
		-halfSize, 0.0f, halfSize, 0.0f, 1.0f,
		-halfSize, 0.0f, -halfSize, 0.0f, 0.0f,
		halfSize, 0.0f, -halfSize, 1.0f, 0.0f,
		halfSize, 0.0f, -halfSize, 1.0f, 0.0f,
		halfSize, 0.0f, halfSize, 1.0f, 1.0f,
		-halfSize, 0.0f, halfSize, 0.0f, 1.0f
	};

	vector<float> highQualityBufferData;
	for(float x = -halfSize; x < halfSize; x++)
	{
		for(float z = -halfSize; z < halfSize; z++)
		{
			float firstPositionX = x;
			float firstPositionY = 0.0f;
			float firstPositionZ = z + 1;
			float firstUvX = ((x + halfSize) / size);
			float firstUvY = (((z + halfSize) / size) + (1.0f / size));

			float secondPositionX = x + 1;
			float secondPositionY = 0.0f;
			float secondPositionZ = z + 1;
			float secondUvX = (((x + halfSize) / size) + (1.0f / size));
			float secondUvY = (((z + halfSize) / size) + (1.0f / size));

			float thirdPositionX = x + 1;
			float thirdPositionY = 0.0f;
			float thirdPositionZ = z;
			float thirdUvX = (((x + halfSize) / size) + (1.0f / size));
			float thirdUvY = ((z + halfSize) / size);

			float fourthPositionX = x;
			float fourthPositionY = 0.0f;
			float fourthPositionZ = z;
			float fourthUvX = ((x + halfSize) / size);
			float fourthUvY = ((z + halfSize) / size);

			highQualityBufferData.push_back(firstPositionX);
			highQualityBufferData.push_back(firstPositionY);
			highQualityBufferData.push_back(firstPositionZ);
			highQualityBufferData.push_back(firstUvX);
			highQualityBufferData.push_back(firstUvY);

			highQualityBufferData.push_back(secondPositionX);
			highQualityBufferData.push_back(secondPositionY);
			highQualityBufferData.push_back(secondPositionZ);
			highQualityBufferData.push_back(secondUvX);
			highQualityBufferData.push_back(secondUvY);

			highQualityBufferData.push_back(thirdPositionX);
			highQualityBufferData.push_back(thirdPositionY);
			highQualityBufferData.push_back(thirdPositionZ);
			highQualityBufferData.push_back(thirdUvX);
			highQualityBufferData.push_back(thirdUvY);

			highQualityBufferData.push_back(thirdPositionX);
			highQualityBufferData.push_back(thirdPositionY);
			highQualityBufferData.push_back(thirdPositionZ);
			highQualityBufferData.push_back(thirdUvX);
			highQualityBufferData.push_back(thirdUvY);

			highQualityBufferData.push_back(fourthPositionX);
			highQualityBufferData.push_back(fourthPositionY);
			highQualityBufferData.push_back(fourthPositionZ);
			highQualityBufferData.push_back(fourthUvX);
			highQualityBufferData.push_back(fourthUvY);

			highQualityBufferData.push_back(firstPositionX);
			highQualityBufferData.push_back(firstPositionY);
			highQualityBufferData.push_back(firstPositionZ);
			highQualityBufferData.push_back(firstUvX);
			highQualityBufferData.push_back(firstUvY);
		}
	}

	auto lowQualityBufferDataCount = static_cast<unsigned int>(sizeof(lowQualityBufferData) / sizeof(float));
	auto highQualityBufferDataCount = static_cast<unsigned int>(highQualityBufferData.size());

	entity->setLowQualityMesh(make_shared<VertexBuffer>(VertexBufferType::POS_UV, &lowQualityBufferData[0], lowQualityBufferDataCount));
	entity->setHighQualityMesh(make_shared<VertexBuffer>(VertexBufferType::POS_UV, &highQualityBufferData[0], highQualityBufferDataCount));
}

void WaterEntityManager::update()
{
	auto entity = getSelectedEntity();

	if(entity == nullptr)
	{
		return;
	}

	if(!entity->isVisible())
	{
		return;
	}

	entity->setRippleOffset(fvec2(fmodf((entity->getRippleOffset().x + entity->getRippleSpeed().x), 1.0f), fmodf((entity->getRippleOffset().y - entity->getRippleSpeed().y), 1.0f)));

	entity->setWaveOffset(entity->getWaveOffset() + (entity->getWaveSpeed()));
}