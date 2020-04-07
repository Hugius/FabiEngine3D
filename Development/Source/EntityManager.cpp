#include <WE3D/EntityManager.hpp>
#include <WE3D/Logger.hpp>

EntityManager::EntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	p_objLoader(objLoader),
	p_texLoader(texLoader),
	p_shaderBus(shaderBus)
{
	
}

// Free dynamic memory
EntityManager::~EntityManager()
{
	for (size_t i = 0; i < p_entities.size(); i++)
	{
		delete p_entities[i];
		p_entities.erase(p_entities.begin() + i);
	}
}

// Deleting entity
void EntityManager::deleteEntity(const string & ID)
{
	for (size_t i = 0; i < p_entities.size(); i++)
	{
		if (p_entities[i]->getID() == ID)
		{
			delete p_entities[i];
			p_entities.erase(p_entities.begin() + i);
			return;
		}
	}

	// Error logging
	Logger::getInst().throwError("Nonexisting Entity with ID " + ID + " requested for removal");
}

void EntityManager::deleteEntities()
{
	p_entities.clear();
}

// Checking if entity exists
bool EntityManager::isExisting(const string & ID)
{
	for (size_t i = 0; i < p_entities.size(); i++)
	{
		if (p_entities[i]->getID() == ID)
		{
			return true;
		}
	}

	return false;
}

// Finding and returning entity
Entity * EntityManager::p_getBaseEntity(const string & ID, EntityType type)
{
	for (auto & entity : p_entities)
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

vector<Entity*> & EntityManager::p_getBaseEntities()
{
	return p_entities;
}

Entity * EntityManager::p_createEntity(EntityType type, const string & ID)
{
	for (auto & entity : p_entities)
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
			p_entities.push_back(new SkyEntity());
			return dynamic_cast<SkyEntity*>(p_entities.back());
			break;
		}

		case(EntityType::TERRAIN):
		{
			p_entities.push_back(new TerrainEntity());
			return dynamic_cast<TerrainEntity*>(p_entities.back());
			break;
		}

		case(EntityType::WATER):
		{
			p_entities.push_back(new WaterEntity());
			return dynamic_cast<WaterEntity*>(p_entities.back());
			break;
		}

		case(EntityType::GAME):
		{
			p_entities.push_back(new GameEntity());
			return dynamic_cast<GameEntity*>(p_entities.back());
			break;
		}

		case(EntityType::BILLBOARD):
		{
			p_entities.push_back(new BillboardEntity());
			return dynamic_cast<BillboardEntity*>(p_entities.back());
			break;
		}

		case(EntityType::AABB):
		{
			p_entities.push_back(new AabbEntity());
			return dynamic_cast<AabbEntity*>(p_entities.back());
			break;
		}

		case(EntityType::LIGHT):
		{
			p_entities.push_back(new LightEntity());
			return dynamic_cast<LightEntity*>(p_entities.back());
			break;
		}

		case(EntityType::GUI):
		{
			p_entities.push_back(new GuiEntity());
			return dynamic_cast<GuiEntity*>(p_entities.back());
			break;
		}

		case(EntityType::TEXT):
		{
			p_entities.push_back(new TextEntity());
			return dynamic_cast<TextEntity*>(p_entities.back());
			break;
		}
	}

	return nullptr;
}