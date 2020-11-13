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
			for (size_t i = 0; i < _skyEntities.size(); i++)
			{
				if (_skyEntities[i]->getID() == ID)
				{
					_skyEntities.erase(_skyEntities.begin() + i);
					return;
				}
			}
			break;
		}

		case(EntityType::TERRAIN):
		{
			for (size_t i = 0; i < _terrainEntities.size(); i++)
			{
				if (_terrainEntities[i]->getID() == ID)
				{
					_terrainEntities.erase(_terrainEntities.begin() + i);
					return;
				}
			}
			break;
		}

		case(EntityType::WATER):
		{
			for (size_t i = 0; i < _waterEntities.size(); i++)
			{
				if (_waterEntities[i]->getID() == ID)
				{
					_waterEntities.erase(_waterEntities.begin() + i);
					return;
				}
			}
			break;
		}

		case(EntityType::GAME):
		{
			for (size_t i = 0; i < _gameEntities.size(); i++)
			{
				if (_gameEntities[i]->getID() == ID)
				{
					_gameEntities.erase(_gameEntities.begin() + i);
					return;
				}
			}
			break;
		}

		case(EntityType::BILLBOARD):
		{
			for (size_t i = 0; i < _billboardEntities.size(); i++)
			{
				if (_billboardEntities[i]->getID() == ID)
				{
					_billboardEntities.erase(_billboardEntities.begin() + i);
					return;
				}
			}
			break;
		}

		case(EntityType::AABB):
		{
			for (size_t i = 0; i < _aabbEntities.size(); i++)
			{
				if (_aabbEntities[i]->getID() == ID)
				{
					_aabbEntities.erase(_aabbEntities.begin() + i);
					return;
				}
			}
			break;
		}

		case(EntityType::LIGHT):
		{
			for (size_t i = 0; i < _lightEntities.size(); i++)
			{
				if (_lightEntities[i]->getID() == ID)
				{
					_lightEntities.erase(_lightEntities.begin() + i);
					return;
				}
			}
			break;
		}

		case(EntityType::GUI):
		{
			for (size_t i = 0; i < _guiEntities.size(); i++)
			{
				if (_guiEntities[i]->getID() == ID)
				{
					_guiEntities.erase(_guiEntities.begin() + i);
					return;
				}
			}
			break;
		}

		case(EntityType::TEXT):
		{
			for (size_t i = 0; i < _textEntities.size(); i++)
			{
				if (_textEntities[i]->getID() == ID)
				{
					_textEntities.erase(_textEntities.begin() + i);
					return;
				}
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
	Logger::throwError("Nonexisting " + temp[_type] + " entity with ID " + ID + " requested for removal!");
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
			_skyEntities.push_back(make_shared<SkyEntity>(ID));
			return;
		}

		case(EntityType::TERRAIN):
		{
			if(_getTerrainEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create TERRAIN entity: \"" + ID + "\" already exists!");
			}
			_terrainEntities.push_back(make_shared<TerrainEntity>(ID));
			return;
		}

		case(EntityType::WATER):
		{
			if (_getWaterEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create WATER entity: \"" + ID + "\" already exists!");
			}
			_waterEntities.push_back(make_shared<WaterEntity>(ID));
			return;
		}

		case(EntityType::GAME):
		{
			if (_getGameEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create GAME entity: \"" + ID + "\" already exists!");
			}
			_gameEntities.push_back(make_shared<GameEntity>(ID));
			return;
		}

		case(EntityType::BILLBOARD):
		{
			if (_getBillboardEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create BILLBOARD entity: \"" + ID + "\" already exists!");
			}
			_billboardEntities.push_back(make_shared<BillboardEntity>(ID));
			return;
		}

		case(EntityType::AABB):
		{
			if (_getAabbEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create AABB entity: \"" + ID + "\" already exists!");
			}
			_aabbEntities.push_back(make_shared<AabbEntity>(ID));
			return;
		}

		case(EntityType::LIGHT):
		{
			if (_getLightEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create LIGHT entity: \"" + ID + "\" already exists!");
			}
			_lightEntities.push_back(make_shared<LightEntity>(ID));
			return;
		}

		case(EntityType::GUI):
		{
			if (_getGuiEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create GUI entity: \"" + ID + "\" already exists!");
			}
			_guiEntities.push_back(make_shared<GuiEntity>(ID));
			return;
		}

		case(EntityType::TEXT):
		{
			if (_getTextEntity(ID) != nullptr)
			{
				Logger::throwError("Could not create TEXT entity: \"" + ID + "\" already exists!");
			}
			_textEntities.push_back(make_shared<TextEntity>(ID));
			return;
		}
	}
}

vector<shared_ptr<AabbEntity>>& BaseEntityManager::_getAabbEntities()
{
	return _aabbEntities;
}

vector<shared_ptr<BillboardEntity>>& BaseEntityManager::_getBillboardEntities()
{
	return _billboardEntities;
}

vector<shared_ptr<GameEntity>>& BaseEntityManager::_getGameEntities()
{
	return _gameEntities;
}

vector<shared_ptr<GuiEntity>>& BaseEntityManager::_getGuiEntities()
{
	return _guiEntities;
}

vector<shared_ptr<LightEntity>>& BaseEntityManager::_getLightEntities()
{
	return _lightEntities;
}

vector<shared_ptr<SkyEntity>>& BaseEntityManager::_getSkyEntities()
{
	return _skyEntities;
}

vector<shared_ptr<TerrainEntity>>& BaseEntityManager::_getTerrainEntities()
{
	return _terrainEntities;
}

vector<shared_ptr<TextEntity>>& BaseEntityManager::_getTextEntities()
{
	return _textEntities;
}

vector<shared_ptr<WaterEntity>>& BaseEntityManager::_getWaterEntities()
{
	return _waterEntities;
}

shared_ptr<AabbEntity> BaseEntityManager::_getAabbEntity(const string& ID)
{
	for (auto& entity : _aabbEntities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	return nullptr;
}

shared_ptr<BillboardEntity> BaseEntityManager::_getBillboardEntity(const string& ID)
{
	for (auto& entity : _billboardEntities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	return nullptr;
}

shared_ptr<GameEntity> BaseEntityManager::_getGameEntity(const string& ID)
{
	for (auto& entity : _gameEntities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	return nullptr;
}

shared_ptr<GuiEntity> BaseEntityManager::_getGuiEntity(const string& ID)
{
	for (auto& entity : _guiEntities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	return nullptr;
}

shared_ptr<LightEntity> BaseEntityManager::_getLightEntity(const string& ID)
{
	for (auto& entity : _lightEntities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	return nullptr;
}

shared_ptr<SkyEntity> BaseEntityManager::_getSkyEntity(const string& ID)
{
	for (auto& entity : _skyEntities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	return nullptr;
}

shared_ptr<TerrainEntity> BaseEntityManager::_getTerrainEntity(const string& ID)
{
	for (auto& entity : _terrainEntities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	return nullptr;
}

shared_ptr<TextEntity> BaseEntityManager::_getTextEntity(const string& ID)
{
	for (auto& entity : _textEntities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	return nullptr;
}

shared_ptr<WaterEntity> BaseEntityManager::_getWaterEntity(const string& ID)
{
	for (auto& entity : _waterEntities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	return nullptr;
}