#pragma once

#include "base_renderer.hpp"
#include "pointlight_entity.hpp"
#include "spotlight_entity.hpp"
#include "water_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterEntityColorRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	// VOID
	void bind() override;
	void unbind() override;
	void processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>>& entities);
	void processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>>& entities);
	void render(const shared_ptr<WaterEntity> entity);
};