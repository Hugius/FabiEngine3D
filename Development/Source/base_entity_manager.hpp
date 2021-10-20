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
#include "pointlight_entity.hpp"
#include "spotlight_entity.hpp"
#include "reflection_entity.hpp"
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
	BaseEntityManager(EntityType type, MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// Voids
	virtual void update() = 0;
	void deleteEntity(const string& ID);
	void deleteAllEntities();

	// Booleans
	bool isExisting(const string& ID);

protected:
	// Voids
	void _createEntity(const string& ID);

	// Instances
	unordered_map<string, shared_ptr<WaterEntity>>& _getWaterEntities();
	unordered_map<string, shared_ptr<SkyEntity>>& _getSkyEntities();
	unordered_map<string, shared_ptr<TerrainEntity>>& _getTerrainEntities();
	unordered_map<string, shared_ptr<ModelEntity>>& _getModelEntities();
	unordered_map<string, shared_ptr<BillboardEntity>>& _getBillboardEntities();
	unordered_map<string, shared_ptr<AabbEntity>>& _getAabbEntities();
	unordered_map<string, shared_ptr<ReflectionEntity>>& _getReflectionEntities();
	unordered_map<string, shared_ptr<PointlightEntity>>& _getPointlightEntities();
	unordered_map<string, shared_ptr<SpotlightEntity>>& _getSpotlightEntities();
	unordered_map<string, shared_ptr<ImageEntity>>& _getImageEntities();
	unordered_map<string, shared_ptr<TextEntity>>& _getTextEntities();
	shared_ptr<SkyEntity> _getSkyEntity(const string& ID);
	shared_ptr<TerrainEntity> _getTerrainEntity(const string& ID);
	shared_ptr<WaterEntity> _getWaterEntity(const string& ID);
	shared_ptr<ModelEntity> _getModelEntity(const string& ID);
	shared_ptr<BillboardEntity> _getBillboardEntity(const string& ID);
	shared_ptr<AabbEntity> _getAabbEntity(const string& ID);
	shared_ptr<PointlightEntity> _getPointlightEntity(const string& ID);
	shared_ptr<SpotlightEntity> _getSpotlightEntity(const string& ID);
	shared_ptr<ReflectionEntity> _getReflectionEntity(const string& ID);
	shared_ptr<ImageEntity>	_getImageEntity(const string& ID);
	shared_ptr<TextEntity> _getTextEntity(const string& ID);

	// Instances
	EntityType _type;
	MeshLoader& _meshLoader;
	TextureLoader& _textureLoader;
	RenderBus& _renderBus;

private:
	// Instances
	unordered_map<string, shared_ptr<SkyEntity>> _skyEntities;
	unordered_map<string, shared_ptr<TerrainEntity>> _terrainEntities;
	unordered_map<string, shared_ptr<WaterEntity>> _waterEntities;
	unordered_map<string, shared_ptr<ModelEntity>> _modelEntities;
	unordered_map<string, shared_ptr<BillboardEntity>> _billboardEntities;
	unordered_map<string, shared_ptr<AabbEntity>> _aabbEntities;
	unordered_map<string, shared_ptr<PointlightEntity>> _pointlightEntities;
	unordered_map<string, shared_ptr<SpotlightEntity>> _spotlightEntities;
	unordered_map<string, shared_ptr<ReflectionEntity>> _reflectionEntities;
	unordered_map<string, shared_ptr<ImageEntity>> _imageEntities;
	unordered_map<string, shared_ptr<TextEntity>> _textEntities;

	// Integers
	static inline unsigned int _guiDepth = 0;
};