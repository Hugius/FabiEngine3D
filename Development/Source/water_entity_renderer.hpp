#pragma once

#include "base_entity_renderer.hpp"
#include "water_entity.hpp"

class WaterEntityRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~WaterEntityRenderer() = default;

	void bind() override;
	void unbind() override;
	void render(const WaterEntity * entity);
};