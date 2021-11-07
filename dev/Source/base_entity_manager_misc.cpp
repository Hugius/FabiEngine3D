#include "base_entity_manager.hpp"
#include "logger.hpp"

const bool BaseEntityManager::isExisting(const string& ID)
{
	switch(_type)
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
		case(EntityType::MODEL):
		{
			return (_getModelEntity(ID) != nullptr);
		}
		case(EntityType::BILLBOARD):
		{
			return (_getBillboardEntity(ID) != nullptr);
		}
		case(EntityType::AABB):
		{
			return (_getAabbEntity(ID) != nullptr);
		}
		case(EntityType::POINTLIGHT):
		{
			return (_getPointlightEntity(ID) != nullptr);
		}
		case(EntityType::SPOTLIGHT):
		{
			return (_getSpotlightEntity(ID) != nullptr);
		}
		case(EntityType::REFLECTION):
		{
			return (_getReflectionEntity(ID) != nullptr);
		}
		case(EntityType::IMAGE):
		{
			return (_getImageEntity(ID) != nullptr);
		}
		case(EntityType::TEXT):
		{
			return (_getTextEntity(ID) != nullptr);
		}
	}

	return false;
}

unordered_map<string, shared_ptr<SkyEntity>>& BaseEntityManager::_getSkyEntities()
{
	return _skyEntities;
}

unordered_map<string, shared_ptr<TerrainEntity>>& BaseEntityManager::_getTerrainEntities()
{
	return _terrainEntities;
}

unordered_map<string, shared_ptr<WaterEntity>>& BaseEntityManager::_getWaterEntities()
{
	return _waterEntities;
}

unordered_map<string, shared_ptr<ModelEntity>>& BaseEntityManager::_getModelEntities()
{
	return _modelEntities;
}

unordered_map<string, shared_ptr<BillboardEntity>>& BaseEntityManager::_getBillboardEntities()
{
	return _billboardEntities;
}

unordered_map<string, shared_ptr<AabbEntity>>& BaseEntityManager::_getAabbEntities()
{
	return _aabbEntities;
}

unordered_map<string, shared_ptr<PointlightEntity>>& BaseEntityManager::_getPointlightEntities()
{
	return _pointlightEntities;
}

unordered_map<string, shared_ptr<SpotlightEntity>>& BaseEntityManager::_getSpotlightEntities()
{
	return _spotlightEntities;
}

unordered_map<string, shared_ptr<ReflectionEntity>>& BaseEntityManager::_getReflectionEntities()
{
	return _reflectionEntities;
}

unordered_map<string, shared_ptr<ImageEntity>>& BaseEntityManager::_getImageEntities()
{
	return _imageEntities;
}

unordered_map<string, shared_ptr<TextEntity>>& BaseEntityManager::_getTextEntities()
{
	return _textEntities;
}

shared_ptr<SkyEntity> BaseEntityManager::_getSkyEntity(const string& ID)
{
	auto it = _skyEntities.find(ID);

	if(it == _skyEntities.end())
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

	if(it == _terrainEntities.end())
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

	if(it == _waterEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<ModelEntity> BaseEntityManager::_getModelEntity(const string& ID)
{
	auto it = _modelEntities.find(ID);

	if(it == _modelEntities.end())
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

	if(it == _billboardEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<AabbEntity> BaseEntityManager::_getAabbEntity(const string& ID)
{
	auto it = _aabbEntities.find(ID);

	if(it == _aabbEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<PointlightEntity> BaseEntityManager::_getPointlightEntity(const string& ID)
{
	auto it = _pointlightEntities.find(ID);

	if(it == _pointlightEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<SpotlightEntity> BaseEntityManager::_getSpotlightEntity(const string& ID)
{
	auto it = _spotlightEntities.find(ID);

	if(it == _spotlightEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<ReflectionEntity> BaseEntityManager::_getReflectionEntity(const string& ID)
{
	auto it = _reflectionEntities.find(ID);

	if(it == _reflectionEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

shared_ptr<ImageEntity> BaseEntityManager::_getImageEntity(const string& ID)
{
	auto it = _imageEntities.find(ID);

	if(it == _imageEntities.end())
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

	if(it == _textEntities.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}