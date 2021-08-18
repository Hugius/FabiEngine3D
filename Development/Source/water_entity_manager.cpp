#include "water_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

using std::make_shared;

WaterEntityManager::WaterEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::WATER, meshLoader, texLoader, renderBus)
{

}

shared_ptr<WaterEntity> WaterEntityManager::getEntity(const string& ID)
{
	auto result = _getWaterEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("WaterEntityManager::getEntity");
	}

	return result;
}

shared_ptr<WaterEntity> WaterEntityManager::getSelectedWater()
{
	if (_getWaterEntities().empty() || _selectedID.empty())
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
	return _getWaterEntities();
}

void WaterEntityManager::selectWater(const string& ID)
{
	if (isExisting(ID) || ID.empty())
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
	_createEntity(ID);
	loadMesh(ID);
}

void WaterEntityManager::loadMesh(const string& ID)
{
	// Temporary values
	auto entity = getEntity(ID);
	float size = entity->getSize();
	float halfSize = (size / 2.0f);
	vector<float> highQualityBufferData;

	// Check if size is too large
	if (size > 1024)
	{
		Logger::throwError("WaterEntityManager::loadMesh");
	}

	// Reserving memory for the vertices
	highQualityBufferData.reserve(size_t(size) * size_t(size) * 30);

	for (float x = -halfSize; x < halfSize; x++) // X direction
	{
		for (float z = -halfSize; z < halfSize; z++) // Z direction
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
	
	// Create high quality render buffer
	entity->setHighQualityRenderBuffer(make_shared<RenderBuffer>(BufferType::VERTEX_UV, &highQualityBufferData[0], static_cast<unsigned int>(highQualityBufferData.size())));

	// Compose low quality buffer data
	float lowQualityBufferData[] =
	{
		-halfSize,  0.0f,  halfSize, 0.0f, 1.0f,
		-halfSize,  0.0f, -halfSize, 0.0f, 0.0f,
		 halfSize,  0.0f, -halfSize, 1.0f, 0.0f,
		 halfSize,  0.0f, -halfSize, 1.0f, 0.0f,
		 halfSize,  0.0f,  halfSize, 1.0f, 1.0f,
		-halfSize,  0.0f,  halfSize, 0.0f, 1.0f
	};

	// Create low quality render buffer
	entity->setLowQualityRenderBuffer(make_shared<RenderBuffer>(BufferType::VERTEX_UV, lowQualityBufferData, static_cast<unsigned int>(sizeof(lowQualityBufferData) / sizeof(float))));
}

void WaterEntityManager::update()
{
	// Update all water entities
	for (const auto& [keyID, entity] : _getWaterEntities())
	{
		// Update water animations (rippling & waving)
		if (entity->isVisible())
		{
			// Update ripple speed
			Vec2 newOffset = entity->getRippleOffset() + entity->getSpeed();
			newOffset = Vec2(fmodf(newOffset.x, 1.0f), fmodf(newOffset.y, 1.0f));
			entity->setRippleOffset(newOffset);

			// Update waving speed (must be 25% slower)
			entity->setWaveOffset(entity->getWaveOffset() + (entity->getSpeed() * 0.25f));
		}
	}
}