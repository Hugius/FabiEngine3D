#include "entity_bus.hpp"

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
	_skyEntity(skyEntity),
	_terrainEntity(terrainEntity),
	_waterEntity(waterEntity),
	_gameEntities(gameEntities),
	_billboardEntities(billboardEntities),
	_aabbEntities(aabbEntities),
	_lightEntities(lightEntities),
	_guiEntities(guiEntities),
	_textEntities(textEntities)
{
	
}

const vector<GameEntity*> & EntityBus::getGameEntities() const
{
	return _gameEntities;
}

const vector<BillboardEntity*> & EntityBus::getBillboardEntities() const
{
	return _billboardEntities;
}

const vector<AabbEntity*>& EntityBus::getAabbEntities() const
{
	return _aabbEntities;
}

const vector<GuiEntity*> & EntityBus::getGuiEntities() const
{
	return _guiEntities;
}

const vector<TextEntity*> & EntityBus::getTextEntities() const
{
	return _textEntities;
}

const vector<LightEntity*> & EntityBus::getLightEntities() const
{
	return _lightEntities;
}

const SkyEntity * EntityBus::getSkyEntity() const
{
	return _skyEntity;
}

const TerrainEntity * EntityBus::getTerrainEntity() const
{
	return _terrainEntity;
}

const WaterEntity * EntityBus::getWaterEntity() const
{
	return _waterEntity;
}