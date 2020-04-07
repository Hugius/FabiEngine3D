#pragma once

#include "OBJLoader.hpp"
#include "TextureLoader.hpp"
#include "ShaderBus.hpp"
#include "Entity.hpp"
#include "SkyEntity.hpp"
#include "TerrainEntity.hpp"
#include "WaterEntity.hpp"
#include "GameEntity.hpp"
#include "BillboardEntity.hpp"
#include "AabbEntity.hpp"
#include "LightEntity.hpp"
#include "GuiEntity.hpp"
#include "TextEntity.hpp"

enum class EntityType
{
	SKY,
	TERRAIN,
	WATER,
	GAME,
	BILLBOARD,
	AABB,
	LIGHT,
	GUI,
	TEXT
};

class EntityManager
{
public:
	EntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	virtual ~EntityManager();

	void deleteEntity(const string & ID);
	void deleteEntities();

	bool isExisting(const string & ID);

	virtual Entity * getEntity(const string & ID) = 0;

	virtual void update(float delta) = 0;

protected:
	OBJLoader&     p_objLoader;
	TextureLoader& p_texLoader;
	ShaderBus&     p_shaderBus;

	Entity * p_createEntity(EntityType type, const string & ID);

	vector<Entity*> & p_getBaseEntities();
	
	Entity * p_getBaseEntity(const string & ID, EntityType type);

private:
	vector<Entity*> p_entities;
};