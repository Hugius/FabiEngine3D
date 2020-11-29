#include "base_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

BaseEntityManager::BaseEntityManager(EntityType type, OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	_type(type),
	_objLoader(objLoader),
	_texLoader(texLoader),
	_renderBus(renderBus)
{
	
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

		case(EntityType::GAME):
		{
			if (_gameEntities.erase(ID))
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
	temp[EntityType::GAME] = "GAME"; temp[EntityType::BILLBOARD] = "BILLBOARD"; temp[EntityType::AABB] = "AABB";
	temp[EntityType::LIGHT] = "LIGHT"; temp[EntityType::GUI] = "GUI"; temp[EntityType::TEXT] = "TEXT";

	// Error logging
	Logger::throwError("Nonexisting " + temp[_type] + " entity with ID \"" + ID + "\" requested for removal!");
}

void BaseEntityManager::deleteAllEntities()
{
	_aabbEntities.clear();
	_billboardEntities.clear();
	_gameEntities.clear();
	_guiEntities.clear();
	_lightEntities.clear();
	_skyEntities.clear();
	_terrainEntities.clear();
	_textEntities.clear();
	_waterEntities.clear();
}

bool BaseEntityManager::isExisting(const string& ID)
{
	switch (_type)
	{
		case(EntityType::SKY):
		{
			return (_getSkyEntity(ID) != nullptr);
		}
		case(EntityType::TERRAIN):
		{
			return (_getTerrainEntity(ID) != nullptr);
		}
		case(EntityType::WATER):
		{
			return (_getWaterEntity(ID) != nullptr);
		}
		case(EntityType::GAME):
		{
			return (_getGameEntity(ID) != nullptr);
		}
		case(EntityType::BILLBOARD):
		{
			return (_getBillboardEntity(ID) != nullptr);
		}
		case(EntityType::AABB):
		{
			return (_getAabbEntity(ID) != nullptr);
		}
		case(EntityType::LIGHT):
		{
			return (_getLightEntity(ID) != nullptr);
		}
		case(EntityType::GUI):
		{
			return (_getGuiEntity(ID) != nullptr);
		}
		case(EntityType::TEXT):
		{
			return (_getTextEntity(ID) != nullptr);
		}
	}

	return false;
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
			if(_getTerrainEntity(ID) != nullptr)
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

		case(EntityType::GAME):
		{
			if (_getGameEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create GAME entity: \"" + ID + "\" already exists!");
			}
			_gameEntities.insert(make_pair(ID, make_shared<GameEntity>(ID)));
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

unordered_map<string, shared_ptr<AabbEntity>>& BaseEntityManager::_getAabbEntities()
{
	return _aabbEntities;
}

unordered_map<string, shared_ptr<BillboardEntity>>& BaseEntityManager::_getBillboardEntities()
{
	return _billboardEntities;
}

unordered_map<string, shared_ptr<GameEntity>>& BaseEntityManager::_getGameEntities()
{
	return _gameEntities;
}

unordered_map<string, shared_ptr<GuiEntity>>& BaseEntityManager::_getGuiEntities()
{
	return _guiEntities;
}

unordered_map<string, shared_ptr<LightEntity>>& BaseEntityManager::_getLightEntities()
{
	return _lightEntities;
}

unordered_map<string, shared_ptr<SkyEntity>>& BaseEntityManager::_getSkyEntities()
{
	return _skyEntities;
}

unordered_map<string, shared_ptr<TerrainEntity>>& BaseEntityManager::_getTerrainEntities()
{
	return _terrainEntities;
}

unordered_map<string, shared_ptr<TextEntity>>& BaseEntityManager::_getTextEntities()
{
	return _textEntities;
}

unordered_map<string, shared_ptr<WaterEntity>>& BaseEntityManager::_getWaterEntities()
{
	return _waterEntities;
}

shared_ptr<AabbEntity> BaseEntityManager::_getAabbEntity(const string& ID)
{
	auto it = _aabbEntities.find(ID);

	if (it == _aabbEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<BillboardEntity> BaseEntityManager::_getBillboardEntity(const string& ID)
{
	auto it = _billboardEntities.find(ID);

	if (it == _billboardEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<GameEntity> BaseEntityManager::_getGameEntity(const string& ID)
{
	auto it = _gameEntities.find(ID);

	if (it == _gameEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<GuiEntity> BaseEntityManager::_getGuiEntity(const string& ID)
{
	auto it = _guiEntities.find(ID);

	if (it == _guiEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<LightEntity> BaseEntityManager::_getLightEntity(const string& ID)
{
	auto it = _lightEntities.find(ID);

	if (it == _lightEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<SkyEntity> BaseEntityManager::_getSkyEntity(const string& ID)
{
	auto it = _skyEntities.find(ID);

	if (it == _skyEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<TerrainEntity> BaseEntityManager::_getTerrainEntity(const string& ID)
{
	auto it = _terrainEntities.find(ID);

	if (it == _terrainEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<TextEntity> BaseEntityManager::_getTextEntity(const string& ID)
{
	auto it = _textEntities.find(ID);

	if (it == _textEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<WaterEntity> BaseEntityManager::_getWaterEntity(const string& ID)
{
	auto it = _waterEntities.find(ID);

	if (it == _waterEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}