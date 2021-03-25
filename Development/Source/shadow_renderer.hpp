#pragma once

#include "base_entity_renderer.hpp"
#include "model_entity.hpp"
#include "terrain_entity.hpp"

class ShadowRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~ShadowRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const shared_ptr<ModelEntity> entity);
};