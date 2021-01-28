#include "water_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

WaterEntityManager::WaterEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::WATER, meshLoader, texLoader, renderBus)
{

}

shared_ptr<WaterEntity> WaterEntityManager::getEntity(const string& ID)
{
	auto result = _getWaterEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting WATER entity with ID \"" + ID + "\" requested");
	}

	return result;
}

shared_ptr<WaterEntity> WaterEntityManager::getSelectedWater()
{
	if (_getWaterEntities().empty() || _selectedID == "")
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
	_selectedID = ID;
}

void WaterEntityManager::addWaterEntity(const string& ID)
{
	_createEntity(ID);
}

void WaterEntityManager::generateModel(const string& ID)
{
	// Variables
	auto entity = getEntity(ID);
	float size = entity->getSize();
	float halfSize = size / 2.0f;
	vector<float> waterVertices;

	// Try to fill the vector
	try
	{
		// Reserving memory for the vertices
		waterVertices.reserve(size_t(size) * size_t(size) * 30);

		// Creating flat tiled water surface
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

				waterVertices.push_back(firstVertexX);
				waterVertices.push_back(firstVertexY);
				waterVertices.push_back(firstVertexZ);
				waterVertices.push_back(firstUvX);
				waterVertices.push_back(firstUvY);

				waterVertices.push_back(secondVertexX);
				waterVertices.push_back(secondVertexY);
				waterVertices.push_back(secondVertexZ);
				waterVertices.push_back(secondUvX);
				waterVertices.push_back(secondUvY);
				
				waterVertices.push_back(thirdVertexX);
				waterVertices.push_back(thirdVertexY);
				waterVertices.push_back(thirdVertexZ);
				waterVertices.push_back(thirdUvX);
				waterVertices.push_back(thirdUvY);
				
				waterVertices.push_back(thirdVertexX);
				waterVertices.push_back(thirdVertexY);
				waterVertices.push_back(thirdVertexZ);
				waterVertices.push_back(thirdUvX);
				waterVertices.push_back(thirdUvY);
				
				waterVertices.push_back(fourthVertexX);
				waterVertices.push_back(fourthVertexY);
				waterVertices.push_back(fourthVertexZ);
				waterVertices.push_back(fourthUvX);
				waterVertices.push_back(fourthUvY);
				
				waterVertices.push_back(firstVertexX);
				waterVertices.push_back(firstVertexY);
				waterVertices.push_back(firstVertexZ);
				waterVertices.push_back(firstUvX);
				waterVertices.push_back(firstUvY);
			}
		}
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "Bad allocation: " << ba.what();
	}
	
	// Fill entity
	entity->clearOglBuffers();
	entity->addOglBuffer(new OpenGLBuffer(BufferType::SURFACE, &waterVertices[0], waterVertices.size()));

	// Load mesh
	float simplified_data[] =
	{
		-halfSize,  0.0f,  halfSize, 0.0f, 1.0f,
		-halfSize,  0.0f, -halfSize, 0.0f, 0.0f,
		 halfSize,  0.0f, -halfSize, 1.0f, 0.0f,
		 halfSize,  0.0f, -halfSize, 1.0f, 0.0f,
		 halfSize,  0.0f,  halfSize, 1.0f, 1.0f,
		-halfSize,  0.0f,  halfSize, 0.0f, 1.0f
	};

	// Add simplified water plane
	entity->setSimplifiedOglBuffer(new OpenGLBuffer(BufferType::SURFACE, simplified_data, sizeof(simplified_data) / sizeof(float)));
}

void WaterEntityManager::update()
{
	// Update reflection height
	if ((_renderBus.isWaterEffectsEnabled() && getSelectedWater() != nullptr) && 
		(getSelectedWater()->isReflective() || getSelectedWater()->isRefractive()))
	{
		_renderBus.setSceneReflectionHeight(getSelectedWater()->getTranslation().y);
		_renderBus.setSceneReflectionOffset(1.0f);
	}

	// Update all water entities
	for (auto& [keyID, entity] : _getWaterEntities())
	{
		// Update water animations (rippling & waving)
		if (entity->isVisible() && _renderBus.isWaterEffectsEnabled())
		{
			// Update ripple speed
			Vec2 newOffset = entity->getRippleOffset() + entity->getSpeed();
			newOffset = Vec2(fmod(newOffset.x, 1.0f), fmod(newOffset.y, 1.0f));
			entity->setRippleOffset(newOffset);

			// Update waving speed (must be 25% slower)
			entity->setWaveOffset(entity->getWaveOffset() + (entity->getSpeed() * 0.25f));
		}
	}
}