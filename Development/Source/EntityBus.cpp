#include <WE3D/EntityBus.hpp>

EntityBus::EntityBus
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
) :
	p_skyEntity(skyEntity),
	p_terrainEntity(terrainEntity),
	p_waterEntity(waterEntity),
	p_gameEntities(gameEntities),
	p_billboardEntities(billboardEntities),
	p_aabbEntities(aabbEntities),
	p_lightEntities(lightEntities),
	p_guiEntities(guiEntities),
	p_textEntities(textEntities)
{
	
}

const vector<GameEntity*> & EntityBus::getGameEntities() const
{
	return p_gameEntities;
}

const vector<BillboardEntity*> & EntityBus::getBillboardEntities() const
{
	return p_billboardEntities;
}

const vector<AabbEntity*>& EntityBus::getAabbEntities() const
{
	return p_aabbEntities;
}

const vector<GuiEntity*> & EntityBus::getGuiEntities() const
{
	return p_guiEntities;
}

const vector<TextEntity*> & EntityBus::getTextEntities() const
{
	return p_textEntities;
}

const vector<LightEntity*> & EntityBus::getLightEntities() const
{
	return p_lightEntities;
}

const SkyEntity * EntityBus::getSkyEntity() const
{
	return p_skyEntity;
}

const TerrainEntity * EntityBus::getTerrainEntity() const
{
	return p_terrainEntity;
}

const WaterEntity * EntityBus::getWaterEntity() const
{
	return p_waterEntity;
}