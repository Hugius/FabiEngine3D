#pragma once

#include "mesh_loader.hpp"
#include "texture_loader.hpp"
#include "render_bus.hpp"
#include "base_entity.hpp"
#include "sky_entity.hpp"
#include "terrain_entity.hpp"
#include "water_entity.hpp"
#include "model_entity.hpp"
#include "billboard_entity.hpp"
#include "aabb_entity.hpp"
#include "light_entity.hpp"
#include "image_entity.hpp"
#include "text_entity.hpp"
#include "entity_type.hpp"

#include <memory>
#include <unordered_map>

using std::make_pair;
using std::shared_ptr;
using std::unordered_map;

class BaseEntityManager
{
public:
	BaseEntityManager(EntityType type, MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	void deleteEntity(const string& ID);
	void deleteAllEntities();

	bool isExisting(const string& ID);

	virtual void update() = 0;

protected:
	EntityType	   _type;
	MeshLoader&    _meshLoader;
	TextureLoader& _textureLoader;
	RenderBus&     _renderBus;

	void _createEntity(const string& ID);

	unordered_map<string, shared_ptr<AabbEntity>>&		_getAabbEntities();
	unordered_map<string, shared_ptr<BillboardEntity>>& _getBillboardEntities();
	unordered_map<string, shared_ptr<ModelEntity>>&		_getModelEntities();
	unordered_map<string, shared_ptr<ImageEntity>>&		_getImageEntities();
	unordered_map<string, shared_ptr<LightEntity>>&		_getLightEntities();
	unordered_map<string, shared_ptr<SkyEntity>>&		_getSkyEntities();
	unordered_map<string, shared_ptr<TerrainEntity>>&	_getTerrainEntities();
	unordered_map<string, shared_ptr<TextEntity>>&		_getTextEntities();
	unordered_map<string, shared_ptr<WaterEntity>>&		_getWaterEntities();
	
	shared_ptr<AabbEntity>		_getAabbEntity(const string& ID);
	shared_ptr<BillboardEntity> _getBillboardEntity(const string& ID);
	shared_ptr<ModelEntity>		_getModelEntity(const string& ID);
	shared_ptr<ImageEntity>		_getImageEntity(const string& ID);
	shared_ptr<LightEntity>		_getLightEntity(const string& ID);
	shared_ptr<SkyEntity>		_getSkyEntity(const string& ID);
	shared_ptr<TerrainEntity>	_getTerrainEntity(const string& ID);
	shared_ptr<TextEntity>		_getTextEntity(const string& ID);
	shared_ptr<WaterEntity>		_getWaterEntity(const string& ID);

private:
	unordered_map<string, shared_ptr<AabbEntity>>	   _aabbEntities;
	unordered_map<string, shared_ptr<BillboardEntity>> _billboardEntities;
	unordered_map<string, shared_ptr<ModelEntity>>	   _modelEntities;
	unordered_map<string, shared_ptr<ImageEntity>>	   _imageEntities;
	unordered_map<string, shared_ptr<LightEntity>>	   _lightEntities;
	unordered_map<string, shared_ptr<SkyEntity>>	   _skyEntities;
	unordered_map<string, shared_ptr<TerrainEntity>>   _terrainEntities;
	unordered_map<string, shared_ptr<TextEntity>>	   _textEntities;
	unordered_map<string, shared_ptr<WaterEntity>>	   _waterEntities;

	static inline unsigned int _guiDepth = 0;
};