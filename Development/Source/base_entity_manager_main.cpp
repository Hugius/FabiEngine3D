#include "base_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

BaseEntityManager::BaseEntityManager(EntityType type, MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	_type(type),
	_meshLoader(meshLoader),
	_textureLoader(texLoader),
	_renderBus(renderBus)
{
	
}

void BaseEntityManager::_createEntity(const string& ID)
{
	// Check for uniqueness of ID & create new entity
	switch (_type)
	{
		case(EntityType::SKY):
		{
			if (_getSkyEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create SKY entity: \"" + ID + "\" already exists!");
			}
			_skyEntities.insert(make_pair(ID, make_shared<SkyEntity>(ID)));
			return;
		}

		case(EntityType::TERRAIN):
		{
			if (_getTerrainEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create TERRAIN entity: \"" + ID + "\" already exists!");
			}
			_terrainEntities.insert(make_pair(ID, make_shared<TerrainEntity>(ID)));
			return;
		}

		case(EntityType::WATER):
		{
			if (_getWaterEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create WATER entity: \"" + ID + "\" already exists!");
			}
			_waterEntities.insert(make_pair(ID, make_shared<WaterEntity>(ID)));
			return;
		}

		case(EntityType::MODEL):
		{
			if (_getModelEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create MODEL entity: \"" + ID + "\" already exists!");
			}
			_modelEntities.insert(make_pair(ID, make_shared<ModelEntity>(ID)));
			return;
		}

		case(EntityType::BILLBOARD):
		{
			if (_getBillboardEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create BILLBOARD entity: \"" + ID + "\" already exists!");
			}
			_billboardEntities.insert(make_pair(ID, make_shared<BillboardEntity>(ID)));
			return;
		}

		case(EntityType::AABB):
		{
			if (_getAabbEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create AABB entity: \"" + ID + "\" already exists!");
			}
			_aabbEntities.insert(make_pair(ID, make_shared<AabbEntity>(ID)));
			return;
		}

		case(EntityType::LIGHT):
		{
			if (_getLightEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create LIGHT entity: \"" + ID + "\" already exists!");
			}
			_lightEntities.insert(make_pair(ID, make_shared<LightEntity>(ID)));
			return;
		}

		case(EntityType::GUI):
		{
			if (_getGuiEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create GUI entity: \"" + ID + "\" already exists!");
			}
			_guiEntities.insert(make_pair(ID, make_shared<GuiEntity>(ID)));
			_getGuiEntity(ID)->setDepth(_guiDepth);
			_guiDepth++;
			return;
		}

		case(EntityType::TEXT):
		{
			if (_getTextEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create TEXT entity: \"" + ID + "\" already exists!");
			}
			_textEntities.insert(make_pair(ID, make_shared<TextEntity>(ID)));
			_getTextEntity(ID)->setDepth(_guiDepth);
			_guiDepth++;
			return;
		}
	}
}

void BaseEntityManager::deleteEntity(const string& ID)
{
	switch (_type)
	{
		case(EntityType::SKY):
		{
			if (_skyEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::TERRAIN):
		{
			if (_terrainEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::WATER):
		{
			if (_waterEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::MODEL):
		{
			if (_modelEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::BILLBOARD):
		{
			if (_billboardEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::AABB):
		{
			if (_aabbEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::LIGHT):
		{
			if (_lightEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::GUI):
		{
			if (_guiEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::TEXT):
		{
			if (_textEntities.erase(ID))
			{
				return;
			}

			break;
		}
	}

	// Temporary type2string map
	std::map<EntityType, string> temp;
	temp[EntityType::SKY] = "SKY"; temp[EntityType::TERRAIN] = "TERRAIN"; temp[EntityType::WATER] = "WATER";
	temp[EntityType::MODEL] = "MODEL"; temp[EntityType::BILLBOARD] = "BILLBOARD"; temp[EntityType::AABB] = "AABB";
	temp[EntityType::LIGHT] = "LIGHT"; temp[EntityType::GUI] = "GUI"; temp[EntityType::TEXT] = "TEXT";

	// Error logging
	Logger::throwError("Nonexisting " + temp[_type] + " entity with ID \"" + ID + "\" requested for removal!");
}

void BaseEntityManager::deleteAllEntities()
{
	_aabbEntities.clear();
	_billboardEntities.clear();
	_modelEntities.clear();
	_guiEntities.clear();
	_lightEntities.clear();
	_skyEntities.clear();
	_terrainEntities.clear();
	_textEntities.clear();
	_waterEntities.clear();
}