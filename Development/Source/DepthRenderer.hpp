#pragma once
#include "EntityRenderer.hpp"
#include "TerrainEntity.hpp"
#include "WaterEntity.hpp"
#include "GameEntity.hpp"
#include "BillboardEntity.hpp"
#include "AabbEntity.hpp"

class DepthRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~DepthRenderer() = default;
	
	void bind()   override;
	void unbind() override;
	void renderTerrainEntity(const TerrainEntity * entity);
	void renderGameEntity(const GameEntity * entity);
	void renderBillboardEntity(const BillboardEntity * entity);
	void renderAabbEntity(const AabbEntity * entity);
	void renderWaterEntity(const WaterEntity * entity);
};