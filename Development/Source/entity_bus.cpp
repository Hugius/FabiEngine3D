#include "entity_bus.hpp"

EntityBus::EntityBus
(
	const shared_ptr<SkyEntity> skyEntity,
	const shared_ptr<TerrainEntity> terrainEntity,
	const shared_ptr<WaterEntity> waterEntity,
	const unordered_map<string, shared_ptr<GameEntity>>      & gameEntities,
	const unordered_map<string, shared_ptr<BillboardEntity>> & billboardEntities,
	const unordered_map<string, shared_ptr<AabbEntity>>      & aabbEntities,
	const unordered_map<string, shared_ptr<LightEntity>>     & lightEntities,
	const unordered_map<string, shared_ptr<GuiEntity>>       & guiEntities,
	const unordered_map<string, shared_ptr<TextEntity>>      & textEntities
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

const unordered_map<string, shared_ptr<GameEntity>> & EntityBus::getGameEntities() const
{
	return _gameEntities;
}

const unordered_map<string, shared_ptr<BillboardEntity>> & EntityBus::getBillboardEntities() const
{
	return _billboardEntities;
}

const unordered_map<string, shared_ptr<AabbEntity>>& EntityBus::getAabbEntities() const
{
	return _aabbEntities;
}

const unordered_map<string, shared_ptr<GuiEntity>> & EntityBus::getGuiEntities() const
{
	return _guiEntities;
}

const unordered_map<string, shared_ptr<TextEntity>> & EntityBus::getTextEntities() const
{
	return _textEntities;
}

const unordered_map<string, shared_ptr<LightEntity>> & EntityBus::getLightEntities() const
{
	return _lightEntities;
}

const shared_ptr<SkyEntity> EntityBus::getSkyEntity() const
{
	return _skyEntity;
}

const shared_ptr<TerrainEntity> EntityBus::getTerrainEntity() const
{
	return _terrainEntity;
}

const shared_ptr<WaterEntity> EntityBus::getWaterEntity() const
{
	return _waterEntity;
}