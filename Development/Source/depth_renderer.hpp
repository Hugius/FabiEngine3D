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
	void render(const TerrainEntity * entity);
	void render(const WaterEntity* entity);
	void render(const GameEntity* entity);
	void render(const BillboardEntity* entity);
	void render(const AabbEntity* entity);
};