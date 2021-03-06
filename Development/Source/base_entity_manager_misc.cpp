#include "base_entity_manager.hpp"
#include "logger.hpp"

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