#pragma once

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

#include <unordered_map>

using std::unordered_map;

class EntityBus final
{
public:
	EntityBus
	(
		const shared_ptr<SkyEntity> mainSkyEntity,
		const shared_ptr<SkyEntity> mixSkyEntity,
		const shared_ptr<TerrainEntity> terrainEntity,
		const shared_ptr<WaterEntity> waterEntity,
		const unordered_map<string, shared_ptr<ModelEntity>>& modelEntities,
		const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities,
		const unordered_map<string, shared_ptr<AabbEntity>>& aabbEntities,
		const unordered_map<string, shared_ptr<PointlightEntity>>& pointlightEntities,
		const unordered_map<string, shared_ptr<SpotlightEntity>>& spotlightEntities,
		const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities,
		const unordered_map<string, shared_ptr<ImageEntity>>& imageEntities,
		const unordered_map<string, shared_ptr<TextEntity>>& textEntities
	);

	// Miscellaneous
	const shared_ptr<SkyEntity>	getMainSkyEntity();
	const shared_ptr<SkyEntity> getMixSkyEntity();
	const shared_ptr<TerrainEntity> getTerrainEntity();
	const shared_ptr<WaterEntity> getWaterEntity();
	const unordered_map<string, shared_ptr<ModelEntity>>& getModelEntities();
	const unordered_map<string, shared_ptr<BillboardEntity>>& getBillboardEntities();
	const unordered_map<string, shared_ptr<AabbEntity>>& getAabbEntities();
	const unordered_map<string, shared_ptr<PointlightEntity>>& getPointLightEntities();
	const unordered_map<string, shared_ptr<SpotlightEntity>>& getSpotlightEntities();
	const unordered_map<string, shared_ptr<ReflectionEntity>>& getReflectionEntities();
	const unordered_map<string, shared_ptr<ImageEntity>>& getImageEntities();
	const unordered_map<string, shared_ptr<TextEntity>>& getTextEntities();

private:
	// Miscellaneous
	const shared_ptr<SkyEntity>	_mainSkyEntity = nullptr;
	const shared_ptr<SkyEntity>	_mixSkyEntity = nullptr;
	const shared_ptr<TerrainEntity> _terrainEntity = nullptr;
	const shared_ptr<WaterEntity> _waterEntity = nullptr;
	const unordered_map<string, shared_ptr<ModelEntity>> _modelEntities;
	const unordered_map<string, shared_ptr<BillboardEntity>> _billboardEntities;
	const unordered_map<string, shared_ptr<AabbEntity>> _aabbEntities;
	const unordered_map<string, shared_ptr<PointlightEntity>> _pointlightEntities;
	const unordered_map<string, shared_ptr<SpotlightEntity>> _spotlightEntities;
	const unordered_map<string, shared_ptr<ReflectionEntity>> _reflectionEntities;
	const unordered_map<string, shared_ptr<ImageEntity>> _imageEntities;
	const unordered_map<string, shared_ptr<TextEntity>> _textEntities;
};