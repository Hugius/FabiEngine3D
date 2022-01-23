#pragma once

#include "base_renderer.hpp"
#include "model_entity.hpp"

class ModelEntityShadowRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<ModelEntity> entity);

private:
	static inline constexpr float MIN_TEXTURE_OPACITY = 0.25f;
};