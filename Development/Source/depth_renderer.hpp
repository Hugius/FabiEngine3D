#pragma once

#include "base_entity_renderer.hpp"
#include "terrain_entity.hpp"
#include "water_entity.hpp"
#include "game_entity.hpp"
#include "billboard_entity.hpp"
#include "aabb_entity.hpp"

class DepthRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~DepthRenderer() = default;
	
	void bind()   override;
	void unbind() override;
	void renderTerrainEntity(const TerrainEntity * entity);
	void renderGameEntity(const GameEntity * entity);
	void renderBillboardEntity(const BillboardEntity * entity);
	void renderAabbEntity(const AabbEntity * entity);
	void renderWaterEntity(const WaterEntity * entity);
};