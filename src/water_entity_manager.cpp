#include "water_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<WaterEntity> WaterEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
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
	if(_entities.empty() || _selectedID.empty())
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
	if(isEntityExisting(ID) || ID.empty())
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
	loadMesh(ID);
}

void WaterEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("WaterEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void WaterEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool WaterEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}

void WaterEntityManager::loadMesh(const string& ID)
{
	auto entity = getEntity(ID);
	float size = entity->getSize();
	float halfSize = (size / 2.0f);
	vector<float> highQualityBufferData;

	if(size > 1024)
	{
		Logger::throwError("WaterEntityManager::loadMesh");
	}

	highQualityBufferData.reserve(size_t(size) * size_t(size) * 30);

	for(float x = -halfSize; x < halfSize; x++) // X direction
	{
		for(float z = -halfSize; z < halfSize; z++) // Z direction
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

	entity->setHighQualityRenderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX_UV, &highQualityBufferData[0], static_cast<unsigned int>(highQualityBufferData.size())));

	float lowQualityBufferData[] =
	{
		-halfSize, 0.0f, halfSize, 0.0f, 1.0f,
		-halfSize, 0.0f, -halfSize, 0.0f, 0.0f,
		halfSize, 0.0f, -halfSize, 1.0f, 0.0f,
		halfSize, 0.0f, -halfSize, 1.0f, 0.0f,
		halfSize, 0.0f, halfSize, 1.0f, 1.0f,
		-halfSize, 0.0f, halfSize, 0.0f, 1.0f
	};

	entity->setLowQualityRenderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX_UV, lowQualityBufferData, static_cast<unsigned int>(sizeof(lowQualityBufferData) / sizeof(float))));
}

void WaterEntityManager::update()
{
	for(const auto& [keyID, entity] : _entities)
	{
		// Update water if visible
		if(entity->isVisible())
		{
			// Update ripple offset
			fvec2 newOffset = entity->getRippleOffset();
			newOffset.x += entity->getSpeed().x;
			newOffset.y -= entity->getSpeed().y;
			newOffset = fvec2(fmodf(newOffset.x, 1.0f), fmodf(newOffset.y, 1.0f));
			entity->setRippleOffset(newOffset);

			// Update wave offset
			entity->setWaveOffset(entity->getWaveOffset() + (entity->getSpeed() * 500.0f));
		}
	}
}