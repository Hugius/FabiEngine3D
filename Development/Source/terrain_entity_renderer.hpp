#pragma once

#include "base_entity_renderer.hpp"
#include "terrain_entity.hpp"

class TerrainEntityRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	
	void bind()    override;
	void unbind()  override;
	void renderLightEntities(const unordered_map<string, shared_ptr<LightEntity>>& entities);
	void render(const shared_ptr<TerrainEntity> entity);
};