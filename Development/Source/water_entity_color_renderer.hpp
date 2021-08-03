#pragma once

#include "base_renderer.hpp"
#include "water_entity.hpp"

class WaterEntityColorRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void bind() override;
	void unbind() override;
	void renderLightEntities(const unordered_map<string, shared_ptr<LightEntity>>& entities);
	void render(const shared_ptr<WaterEntity> entity);
};