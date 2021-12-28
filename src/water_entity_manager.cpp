#include "water_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<WaterEntity> WaterEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if (iterator == _entities.end())
	{
		Logger::throwError("WaterEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

shared_ptr<WaterEntity> WaterEntityManager::getSelectedWater()
{
	if (_entities.empty() || _selectedID.empty())
	{
		return nullptr;
	}
	else
	{
		return getEntity(_selectedID);
	}
}

const unordered_map<string, shared_ptr<WaterEntity>>& WaterEntityManager::getEntities()
{
	return _entities;
}

void WaterEntityManager::selectWater(const string& ID)
{
	if (isEntityExisting(ID) || ID.empty())
	{
		_selectedID = ID;
	}
	else
	{
		Logger::throwError("WaterEntityManager::selectWater");
	}
}

void WaterEntityManager::createEntity(const string& ID)
{
	_entities.insert(make_pair(ID, make_shared<WaterEntity>(ID)));

	_loadMesh(getEntity(ID), 0.0f);
}

void WaterEntityManager::deleteEntity(const string& ID)
{
	if (!isEntityExisting(ID))
	{
		Logger::throwError("WaterEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void WaterEntityManager::deleteEntities()
{
	_entities.clear();
}

void WaterEntityManager::loadMesh(const string& ID)
{
	_loadMesh(getEntity(ID), getEntity(ID)->getSize());
}

const bool WaterEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}

void WaterEntityManager::_loadMesh(shared_ptr<WaterEntity> entity, float size)
{
	const float halfSize = (size / 2.0f);

	if (size > MAX_SIZE)
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
	for (float x = -halfSize; x < halfSize; x++)
	{
		for (float z = -halfSize; z < halfSize; z++)
		{
			float firstVertexX = x;
			float firstVertexY = 0.0f;
			float firstVertexZ = z + 1;
			float firstUvX = ((x + halfSize) / size);
			float firstUvY = (((z + halfSize) / size) + (1.0f / size));

			float secondVertexX = x + 1;
			float secondVertexY = 0.0f;
			float secondVertexZ = z + 1;
			float secondUvX = (((x + halfSize) / size) + (1.0f / size));
			float secondUvY = (((z + halfSize) / size) + (1.0f / size));

			float thirdVertexX = x + 1;
			float thirdVertexY = 0.0f;
			float thirdVertexZ = z;
			float thirdUvX = (((x + halfSize) / size) + (1.0f / size));
			float thirdUvY = ((z + halfSize) / size);

			float fourthVertexX = x;
			float fourthVertexY = 0.0f;
			float fourthVertexZ = z;
			float fourthUvX = ((x + halfSize) / size);
			float fourthUvY = ((z + halfSize) / size);

			highQualityBufferData.push_back(firstVertexX);
			highQualityBufferData.push_back(firstVertexY);
			highQualityBufferData.push_back(firstVertexZ);
			highQualityBufferData.push_back(firstUvX);
			highQualityBufferData.push_back(firstUvY);

			highQualityBufferData.push_back(secondVertexX);
			highQualityBufferData.push_back(secondVertexY);
			highQualityBufferData.push_back(secondVertexZ);
			highQualityBufferData.push_back(secondUvX);
			highQualityBufferData.push_back(secondUvY);

			highQualityBufferData.push_back(thirdVertexX);
			highQualityBufferData.push_back(thirdVertexY);
			highQualityBufferData.push_back(thirdVertexZ);
			highQualityBufferData.push_back(thirdUvX);
			highQualityBufferData.push_back(thirdUvY);

			highQualityBufferData.push_back(thirdVertexX);
			highQualityBufferData.push_back(thirdVertexY);
			highQualityBufferData.push_back(thirdVertexZ);
			highQualityBufferData.push_back(thirdUvX);
			highQualityBufferData.push_back(thirdUvY);

			highQualityBufferData.push_back(fourthVertexX);
			highQualityBufferData.push_back(fourthVertexY);
			highQualityBufferData.push_back(fourthVertexZ);
			highQualityBufferData.push_back(fourthUvX);
			highQualityBufferData.push_back(fourthUvY);

			highQualityBufferData.push_back(firstVertexX);
			highQualityBufferData.push_back(firstVertexY);
			highQualityBufferData.push_back(firstVertexZ);
			highQualityBufferData.push_back(firstUvX);
			highQualityBufferData.push_back(firstUvY);
		}
	}

	auto lowQualityBufferDataCount = static_cast<unsigned int>(sizeof(lowQualityBufferData) / sizeof(float));
	auto highQualityBufferDataCount = static_cast<unsigned int>(highQualityBufferData.size());

	entity->setLowQualityRenderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX_UV, &lowQualityBufferData[0], lowQualityBufferDataCount));
	entity->setHighQualityRenderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX_UV, &highQualityBufferData[0], highQualityBufferDataCount));
}

void WaterEntityManager::update()
{
	for (const auto& [key, entity] : _entities)
	{
		if (entity->isVisible())
		{
			fvec2 newOffset = entity->getRippleOffset();
			newOffset.x += entity->getSpeed().x;
			newOffset.y -= entity->getSpeed().y;
			newOffset = fvec2(fmodf(newOffset.x, 1.0f), fmodf(newOffset.y, 1.0f));
			entity->setRippleOffset(newOffset);

			entity->setWaveOffset(entity->getWaveOffset() + (entity->getSpeed() * 500.0f));
		}
	}
}