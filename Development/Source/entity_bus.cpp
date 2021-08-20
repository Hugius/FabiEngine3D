#include "entity_bus.hpp"

EntityBus::EntityBus
(
	const shared_ptr<SkyEntity> mainSkyEntity,
	const shared_ptr<SkyEntity> mixSkyEntity,
	const shared_ptr<TerrainEntity> terrainEntity,
	const shared_ptr<WaterEntity> waterEntity,
	const unordered_map<string, shared_ptr<ModelEntity>>& modelEntities,
	const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities,
	const unordered_map<string, shared_ptr<AabbEntity>>& aabbEntities,
	const unordered_map<string, shared_ptr<LightEntity>>& lightEntities,
	const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities,
	const unordered_map<string, shared_ptr<ImageEntity>>& imageEntities,
	const unordered_map<string, shared_ptr<TextEntity>>& textEntities
)
	:
	_mainSkyEntity(mainSkyEntity),
	_mixSkyEntity(mixSkyEntity),
	_terrainEntity(terrainEntity),
	_waterEntity(waterEntity),
	_modelEntities(modelEntities),
	_billboardEntities(billboardEntities),
	_aabbEntities(aabbEntities),
	_lightEntities(lightEntities),
	_reflectionEntities(reflectionEntities),
	_imageEntities(imageEntities),
	_textEntities(textEntities)
{

}

const shared_ptr<SkyEntity> EntityBus::getMainSkyEntity()
{
	return _mainSkyEntity;
}

const shared_ptr<SkyEntity> EntityBus::getMixSkyEntity()
{
	return _mixSkyEntity;
}

const shared_ptr<TerrainEntity> EntityBus::getTerrainEntity()
{
	return _terrainEntity;
}

const shared_ptr<WaterEntity> EntityBus::getWaterEntity()
{
	return _waterEntity;
}

const unordered_map<string, shared_ptr<ModelEntity>>& EntityBus::getModelEntities()
{
	return _modelEntities;
}

const unordered_map<string, shared_ptr<BillboardEntity>>& EntityBus::getBillboardEntities()
{
	return _billboardEntities;
}

const unordered_map<string, shared_ptr<AabbEntity>>& EntityBus::getAabbEntities()
{
	return _aabbEntities;
}

const unordered_map<string, shared_ptr<LightEntity>>& EntityBus::getLightEntities()
{
	return _lightEntities;
}

const unordered_map<string, shared_ptr<ReflectionEntity>>& EntityBus::getReflectionEntities()
{
	return _reflectionEntities;
}

const unordered_map<string, shared_ptr<ImageEntity>>& EntityBus::getImageEntities()
{
	return _imageEntities;
}

const unordered_map<string, shared_ptr<TextEntity>>& EntityBus::getTextEntities()
{
	return _textEntities;
}