#pragma once

#include "model_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class ModelEntityShadowRenderer final : BaseRenderer
{
public:
	void bind() override;
	void unbind() override;
	void render(const shared_ptr<ModelEntity> entity);

private:
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};