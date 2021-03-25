#pragma once

#include "sky_entity.hpp"
#include "terrain_entity.hpp"
#include "water_entity.hpp"
#include "model_entity.hpp"
#include "billboard_entity.hpp"
#include "aabb_entity.hpp"
#include "light_entity.hpp"
#include "gui_entity.hpp"
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
		const unordered_map<string, shared_ptr<ModelEntity>>     & modelEntities,
		const unordered_map<string, shared_ptr<BillboardEntity>> & billboardEntities,
		const unordered_map<string, shared_ptr<AabbEntity>>      & aabbEntities,
		const unordered_map<string, shared_ptr<LightEntity>>     & lightEntities,
		const unordered_map<string, shared_ptr<GuiEntity>>       & guiEntities,
		const unordered_map<string, shared_ptr<TextEntity>>      & textEntities
	);

	const shared_ptr<SkyEntity>		getMainSkyEntity() const;
	const shared_ptr<SkyEntity>		getMixSkyEntity()  const;
	const shared_ptr<TerrainEntity> getTerrainEntity() const;
	const shared_ptr<WaterEntity>   getWaterEntity()   const;

	const unordered_map<string, shared_ptr<ModelEntity>>     & getModelEntities()     const;
	const unordered_map<string, shared_ptr<BillboardEntity>> & getBillboardEntities() const;
	const unordered_map<string, shared_ptr<AabbEntity>>      & getAabbEntities()      const;
	const unordered_map<string, shared_ptr<LightEntity>>     & getLightEntities()     const;
	const unordered_map<string, shared_ptr<GuiEntity>>       & getGuiEntities()       const;
	const unordered_map<string, shared_ptr<TextEntity>>      & getTextEntities()      const;

private:
	const shared_ptr<SkyEntity>		_mainSkyEntity = nullptr;
	const shared_ptr<SkyEntity>		_mixSkyEntity  = nullptr;
	const shared_ptr<TerrainEntity> _terrainEntity = nullptr;
	const shared_ptr<WaterEntity>   _waterEntity   = nullptr;
	
	const unordered_map<string, shared_ptr<ModelEntity>>     _modelEntities;
	const unordered_map<string, shared_ptr<BillboardEntity>> _billboardEntities;
	const unordered_map<string, shared_ptr<AabbEntity>>      _aabbEntities;
	const unordered_map<string, shared_ptr<LightEntity>>     _lightEntities;
	const unordered_map<string, shared_ptr<GuiEntity>>       _guiEntities;
	const unordered_map<string, shared_ptr<TextEntity>>      _textEntities;
};