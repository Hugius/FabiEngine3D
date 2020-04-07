#pragma once
#include "SkyEntity.hpp"
#include "TerrainEntity.hpp"
#include "WaterEntity.hpp"
#include "GameEntity.hpp"
#include "BillboardEntity.hpp"
#include "AabbEntity.hpp"
#include "LightEntity.hpp"
#include "GuiEntity.hpp"
#include "TextEntity.hpp"

class EntityBus final
{
public:
	EntityBus
	(
		const SkyEntity     * skyEntity,
		const TerrainEntity * terrainEntity,
		const WaterEntity   * waterEntity,
		const vector<GameEntity*>      & gameEntities,
		const vector<BillboardEntity*> & billboardEntities,
		const vector<AabbEntity*>      & aabbEntities,
		const vector<LightEntity*>     & lightEntities,
		const vector<GuiEntity*>       & guiEntities,
		const vector<TextEntity*>      & textEntities
	);

	const SkyEntity     * getSkyEntity()     const;
	const TerrainEntity * getTerrainEntity() const;
	const WaterEntity   * getWaterEntity()   const;

	const vector<GameEntity*>      & getGameEntities()      const;
	const vector<BillboardEntity*> & getBillboardEntities() const;
	const vector<AabbEntity*>      & getAabbEntities()      const;
	const vector<LightEntity*>     & getLightEntities()     const;
	const vector<GuiEntity*>       & getGuiEntities()       const;
	const vector<TextEntity*>      & getTextEntities()      const;

private:
	const SkyEntity     * p_skyEntity     = nullptr;
	const TerrainEntity * p_terrainEntity = nullptr;
	const WaterEntity   * p_waterEntity   = nullptr;
	
	const vector<GameEntity*>      p_gameEntities;
	const vector<BillboardEntity*> p_billboardEntities;
	const vector<AabbEntity*>      p_aabbEntities;
	const vector<LightEntity*>     p_lightEntities;
	const vector<GuiEntity*>       p_guiEntities;
	const vector<TextEntity*>      p_textEntities;
};