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

using std::shared_ptr;

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

	vector<shared_ptr<AabbEntity>>& _getAabbEntities();
	vector<shared_ptr<BillboardEntity>>& _getBillboardEntities();
	vector<shared_ptr<GameEntity>>& _getGameEntities();
	vector<shared_ptr<GuiEntity>>& _getGuiEntities();
	vector<shared_ptr<LightEntity>>& _getLightEntities();
	vector<shared_ptr<SkyEntity>>& _getSkyEntities();
	vector<shared_ptr<TerrainEntity>>& _getTerrainEntities();
	vector<shared_ptr<TextEntity>>& _getTextEntities();
	vector<shared_ptr<WaterEntity>>& _getWaterEntities();
	
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
	vector<shared_ptr<AabbEntity>> _aabbEntities;
	vector<shared_ptr<BillboardEntity>> _billboardEntities;
	vector<shared_ptr<GameEntity>> _gameEntities;
	vector<shared_ptr<GuiEntity>> _guiEntities;
	vector<shared_ptr<LightEntity>> _lightEntities;
	vector<shared_ptr<SkyEntity>> _skyEntities;
	vector<shared_ptr<TerrainEntity>> _terrainEntities;
	vector<shared_ptr<TextEntity>> _textEntities;
	vector<shared_ptr<WaterEntity>> _waterEntities;
};