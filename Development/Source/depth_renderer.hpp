#pragma once

#include "base_entity_renderer.hpp"
#include "terrain_entity.hpp"
#include "water_entity.hpp"
#include "model_entity.hpp"
#include "billboard_entity.hpp"
#include "aabb_entity.hpp"

class DepthRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~DepthRenderer() = default;
	
	void bind()   override;
	void unbind() override;
	void render(const shared_ptr<TerrainEntity> entity);
	void render(const shared_ptr<WaterEntity> entity);
	void render(const shared_ptr<ModelEntity> entity, float clippingY, bool isUnderWater);
	void render(const shared_ptr<BillboardEntity> entity, float clippingY, bool isUnderWater);
	void render(const shared_ptr<AabbEntity> entity, float clippingY, bool isUnderWater);
};