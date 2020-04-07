#pragma once
#include "EntityRenderer.hpp"
#include "WaterEntity.hpp"

class WaterEntityRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~WaterEntityRenderer() = default;

	void bind() override;
	void unbind() override;
	void render(const WaterEntity * entity);
};