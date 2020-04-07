#pragma once
#include "EntityRenderer.hpp"
#include "SkyEntity.hpp"

class SkyEntityRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~SkyEntityRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const SkyEntity * entity);
};