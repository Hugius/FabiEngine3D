#pragma once

#include "base_renderer.hpp"
#include "pointlight_entity.hpp"
#include "spotlight_entity.hpp"
#include "terrain_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class TerrainEntityColorRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	// Voids
	void bind() override;
	void unbind() override;
	void processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>>& entities);
	void processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>>& entities);
	void render(const shared_ptr<TerrainEntity> entity);
};