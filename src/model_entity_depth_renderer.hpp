#pragma once

#include "base_renderer.hpp"
#include "model_entity.hpp"

class ModelEntityDepthRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void bind() override;
	void unbind() override;
	void render(const shared_ptr<ModelEntity> entity, float clippingY, bool isUnderWater);

private:
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};