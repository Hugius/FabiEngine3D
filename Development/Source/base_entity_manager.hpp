#pragma once

#include "obj_loader.hpp"
#include "texture_loader.hpp"
#include "render_bus.hpp"
#include "base_entity.hpp"
#include "sky_entity.hpp"
#include "terrain_entity.hpp"
#include "water_entity.hpp"
#include "game_entity.hpp"
#include "billboard_entity.hpp"
#include "aabb_entity.hpp"
#include "light_entity.hpp"
#include "gui_entity.hpp"
#include "text_entity.hpp"
#include "entity_type.hpp"

#include <memory>
#include <unordered_map>

using std::shared_ptr;
using std::unordered_map;
using std::make_pair;

class BaseEntityManager
{
public:
	BaseEntityManager(EntityType type, OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~BaseEntityManager() = default;

	void deleteEntity(const string& ID);
	void deleteAllEntities();

	bool isExisting(const string& ID);

	virtual void update() = 0;

protected:
	EntityType	   _type;
	OBJLoader&     _objLoader;
	TextureLoader& _texLoader;
	RenderBus&     _renderBus;

	void _createEntity(const string& ID);

	unordered_map<string, shared_ptr<AabbEntity>>& _getAabbEntities();
	unordered_map<string, shared_ptr<BillboardEntity>>& _getBillboardEntities();
	unordered_map<string, shared_ptr<GameEntity>>& _getGameEntities();
	unordered_map<string, shared_ptr<GuiEntity>>& _getGuiEntities();
	unordered_map<string, shared_ptr<LightEntity>>& _getLightEntities();
	unordered_map<string, shared_ptr<SkyEntity>>& _getSkyEntities();
	unordered_map<string, shared_ptr<TerrainEntity>>& _getTerrainEntities();
	unordered_map<string, shared_ptr<TextEntity>>& _getTextEntities();
	unordered_map<string, shared_ptr<WaterEntity>>& _getWaterEntities();
	
	shared_ptr<AabbEntity> _getAabbEntity(const string& ID);
	shared_ptr<BillboardEntity> _getBillboardEntity(const string& ID);
	shared_ptr<GameEntity> _getGameEntity(const string& ID);
	shared_ptr<GuiEntity> _getGuiEntity(const string& ID);
	shared_ptr<LightEntity> _getLightEntity(const string& ID);
	shared_ptr<SkyEntity> _getSkyEntity(const string& ID);
	shared_ptr<TerrainEntity> _getTerrainEntity(const string& ID);
	shared_ptr<TextEntity> _getTextEntity(const string& ID);
	shared_ptr<WaterEntity> _getWaterEntity(const string& ID);

private:
	unordered_map<string, shared_ptr<AabbEntity>> _aabbEntities;
	unordered_map<string, shared_ptr<BillboardEntity>> _billboardEntities;
	unordered_map<string, shared_ptr<GameEntity>> _gameEntities;
	unordered_map<string, shared_ptr<GuiEntity>> _guiEntities;
	unordered_map<string, shared_ptr<LightEntity>> _lightEntities;
	unordered_map<string, shared_ptr<SkyEntity>> _skyEntities;
	unordered_map<string, shared_ptr<TerrainEntity>> _terrainEntities;
	unordered_map<string, shared_ptr<TextEntity>> _textEntities;
	unordered_map<string, shared_ptr<WaterEntity>> _waterEntities;

	unsigned int _guiDepth = 0;
};