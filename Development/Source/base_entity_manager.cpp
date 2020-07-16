#include "base_entity_manager.hpp"
#include "logger.hpp"

BaseEntityManager::BaseEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	_objLoader(objLoader),
	_texLoader(texLoader),
	_shaderBus(shaderBus)
{
	
}

// Free dynamic memory
BaseEntityManager::~BaseEntityManager()
{
	for (size_t i = 0; i < _entities.size(); i++)
	{
		delete _entities[i];
		_entities.erase(_entities.begin() + i);
	}
}

// Deleting entity
void BaseEntityManager::deleteEntity(const string & ID, EntityType type)
{
	for (size_t i = 0; i < _entities.size(); i++)
	{
		if (_entities[i]->getID() == ID)
		{
			delete _entities[i];
			_entities.erase(_entities.begin() + i);
			return;
		}
	}

	// Temporary entity type map
	std::map<EntityType, string> temp;
	temp[EntityType::SKY] = "SKY"; temp[EntityType::TERRAIN] = "TERRAIN"; temp[EntityType::WATER] = "WATER";
	temp[EntityType::GAME] = "GAME"; temp[EntityType::BILLBOARD] = "BILLBOARD"; temp[EntityType::AABB] = "AABB";
	temp[EntityType::LIGHT] = "LIGHT"; temp[EntityType::GUI] = "GUI"; temp[EntityType::TEXT] = "TEXT";

	// Error logging
	Logger::getInst().throwError("Nonexisting " + temp[type] + " entity with ID " + ID + " requested for removal");
}

void BaseEntityManager::deleteEntities()
{
	_entities.clear();
}

// Checking if entity exists
bool BaseEntityManager::isExisting(const string & ID)
{
	for (size_t i = 0; i < _entities.size(); i++)
	{
		if (_entities[i]->getID() == ID)
		{
			return true;
		}
	}

	return false;
}

// Finding and returning entity
BaseEntity * BaseEntityManager::_getBaseEntity(const string & ID, EntityType type)
{
	for (auto & entity : _entities)
	{
		if (entity->getID() == ID)
		{
			return entity;
		}
	}

	// Temporary entity type map
	std::map<EntityType, string> temp;
	temp[EntityType::SKY] = "SKY"; temp[EntityType::TERRAIN] = "TERRAIN"; temp[EntityType::WATER] = "WATER";
	temp[EntityType::GAME] = "GAME"; temp[EntityType::BILLBOARD] = "BILLBOARD"; temp[EntityType::AABB] = "AABB";
	temp[EntityType::LIGHT] = "LIGHT"; temp[EntityType::GUI] = "GUI"; temp[EntityType::TEXT] = "TEXT";

	// Error logging
	Logger::getInst().throwError("Nonexisting " + temp[type] + " entity with ID " + ID + " requested");
}

vector<BaseEntity*> & BaseEntityManager::_getBaseEntities()
{
	return _entities;
}

BaseEntity * BaseEntityManager::_createEntity(EntityType type, const string & ID)
{
	for (auto & entity : _entities)
	{
		if (entity->getID() == ID)
		{
			switch (type)
			{
			case(EntityType::SKY):
				Logger::getInst().throwError("Could not create SKY entity: \"" + ID + "\" already exists!");
				break;
			case(EntityType::TERRAIN):
				Logger::getInst().throwError("Could not create TERRAIN entity: \"" + ID + "\" already exists!");
				break;
			case(EntityType::WATER):
				Logger::getInst().throwError("Could not create WATER entity: \"" + ID + "\" already exists!");
				break;
			case(EntityType::GAME):
				Logger::getInst().throwError("Could not create GAME entity: \"" + ID + "\" already exists!");
				break;
			case(EntityType::BILLBOARD):
				Logger::getInst().throwError("Could not create BILLBOARD entity: \"" + ID + "\" already exists!");
				break;
			case(EntityType::AABB):
				Logger::getInst().throwError("Could not create AABB entity: \"" + ID + "\" already exists!");
				break;
			case(EntityType::LIGHT):
				Logger::getInst().throwError("Could not create LIGHT entity: \"" + ID + "\" already exists!");
				break;
			case(EntityType::GUI):
				Logger::getInst().throwError("Could not create GUI entity: \"" + ID + "\" already exists!");
				break;
			case(EntityType::TEXT):
				Logger::getInst().throwError("Could not create TEXT entity: \"" + ID + "\" already exists!");
				break;
			}
		}
	}

	switch (type)
	{
		case(EntityType::SKY):
		{
			_entities.push_back(new SkyEntity());
			return dynamic_cast<SkyEntity*>(_entities.back());
			break;
		}

		case(EntityType::TERRAIN):
		{
			_entities.push_back(new TerrainEntity());
			return dynamic_cast<TerrainEntity*>(_entities.back());
			break;
		}

		case(EntityType::WATER):
		{
			_entities.push_back(new WaterEntity());
			return dynamic_cast<WaterEntity*>(_entities.back());
			break;
		}

		case(EntityType::GAME):
		{
			_entities.push_back(new GameEntity());
			return dynamic_cast<GameEntity*>(_entities.back());
			break;
		}

		case(EntityType::BILLBOARD):
		{
			_entities.push_back(new BillboardEntity());
			return dynamic_cast<BillboardEntity*>(_entities.back());
			break;
		}

		case(EntityType::AABB):
		{
			_entities.push_back(new AabbEntity());
			return dynamic_cast<AabbEntity*>(_entities.back());
			break;
		}

		case(EntityType::LIGHT):
		{
			_entities.push_back(new LightEntity());
			return dynamic_cast<LightEntity*>(_entities.back());
			break;
		}

		case(EntityType::GUI):
		{
			_entities.push_back(new GuiEntity());
			return dynamic_cast<GuiEntity*>(_entities.back());
			break;
		}

		case(EntityType::TEXT):
		{
			_entities.push_back(new TextEntity());
			return dynamic_cast<TextEntity*>(_entities.back());
			break;
		}
	}

	return nullptr;
}