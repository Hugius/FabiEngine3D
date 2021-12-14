#pragma once

#include "base_renderer.hpp"
#include "model_entity.hpp"

class ModelEntityShadowRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	// VOID
	void bind() override;
	void unbind() override;
	void render(const shared_ptr<ModelEntity> entity);

private:
	// FLOAT
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};