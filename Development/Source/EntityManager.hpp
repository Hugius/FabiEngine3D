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
	OBJLoader&     _objLoader;
	TextureLoader& _texLoader;
	ShaderBus&     _shaderBus;

	Entity * _createEntity(EntityType type, const string & ID);

	vector<Entity*> & _getBaseEntities();
	
	Entity * _getBaseEntity(const string & ID, EntityType type);

private:
	vector<Entity*> _entities;
};