#include "base_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

BaseEntityManager::BaseEntityManager(EntityType type, MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus)
	:
	_type(type),
	_meshLoader(meshLoader),
	_textureLoader(textureLoader),
	_renderBus(renderBus)
{

}

void BaseEntityManager::_createEntity(const string& ID)
{
	// Check for uniqueness of ID & create new entity
	switch(_type)
	{
		case(EntityType::SKY):
		{
			if(_getSkyEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::1");
			}
			else
			{
				_skyEntities.insert(make_pair(ID, make_shared<SkyEntity>(ID)));
			}

			break;
		}

		case(EntityType::TERRAIN):
		{
			if(_getTerrainEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::2");
			}
			else
			{
				_terrainEntities.insert(make_pair(ID, make_shared<TerrainEntity>(ID)));
			}

			break;
		}

		case(EntityType::WATER):
		{
			if(_getWaterEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::3");
			}
			else
			{
				_waterEntities.insert(make_pair(ID, make_shared<WaterEntity>(ID)));
			}

			break;
		}

		case(EntityType::MODEL):
		{
			if(_getModelEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::4");
			}
			else
			{
				_modelEntities.insert(make_pair(ID, make_shared<ModelEntity>(ID)));
			}

			break;
		}

		case(EntityType::BILLBOARD):
		{
			if(_getBillboardEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::5");
			}
			else
			{
				_billboardEntities.insert(make_pair(ID, make_shared<BillboardEntity>(ID)));
			}

			break;
		}

		case(EntityType::AABB):
		{
			if(_getAabbEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::6");
			}
			else
			{
				_aabbEntities.insert(make_pair(ID, make_shared<AabbEntity>(ID)));
			}

			break;
		}

		case(EntityType::POINTLIGHT):
		{
			if(_getPointlightEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::7");
			}
			else
			{
				_pointlightEntities.insert(make_pair(ID, make_shared<PointlightEntity>(ID)));
			}

			break;
		}

		case(EntityType::SPOTLIGHT):
		{
			if(_getSpotlightEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::8");
			}
			else
			{
				_spotlightEntities.insert(make_pair(ID, make_shared<SpotlightEntity>(ID)));
			}

			break;
		}

		case(EntityType::REFLECTION):
		{
			if(_getReflectionEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::9");
			}
			else
			{
				_reflectionEntities.insert(make_pair(ID, make_shared<ReflectionEntity>(ID)));
			}

			break;
		}

		case(EntityType::IMAGE):
		{
			if(_getImageEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::10");
			}
			else
			{
				_imageEntities.insert(make_pair(ID, make_shared<ImageEntity>(ID)));
				_getImageEntity(ID)->setDepth(_guiDepth);
				_guiDepth++;
			}

			break;
		}

		case(EntityType::TEXT):
		{
			if(_getTextEntity(ID) != nullptr)
			{
				Logger::throwError("BaseEntityManager::_createEntity::11");
			}
			else
			{
				_textEntities.insert(make_pair(ID, make_shared<TextEntity>(ID)));
				_getTextEntity(ID)->setDepth(_guiDepth);
				_guiDepth++;
			}

			break;
		}
	}
}

void BaseEntityManager::deleteEntity(const string& ID)
{
	switch(_type)
	{
		case(EntityType::SKY):
		{
			if(_skyEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::TERRAIN):
		{
			if(_terrainEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::WATER):
		{
			if(_waterEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::MODEL):
		{
			if(_modelEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::BILLBOARD):
		{
			if(_billboardEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::AABB):
		{
			if(_aabbEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::POINTLIGHT):
		{
			if(_pointlightEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::SPOTLIGHT):
		{
			if(_spotlightEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::REFLECTION):
		{
			if(_reflectionEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::IMAGE):
		{
			if(_imageEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::TEXT):
		{
			if(_textEntities.erase(ID))
			{
				return;
			}

			break;
		}
	}

	// Error logging
	Logger::throwError("BaseEntityManager::deleteEntity");
}

void BaseEntityManager::deleteAllEntities()
{
	_skyEntities.clear();
	_terrainEntities.clear();
	_waterEntities.clear();
	_modelEntities.clear();
	_billboardEntities.clear();
	_aabbEntities.clear();
	_pointlightEntities.clear();
	_spotlightEntities.clear();
	_reflectionEntities.clear();
	_imageEntities.clear();
	_textEntities.clear();
}