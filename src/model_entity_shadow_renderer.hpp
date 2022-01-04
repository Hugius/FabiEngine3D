#pragma once

#include "model_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class ModelEntityShadowRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void render(shared_ptr<ShaderBuffer> shader, const shared_ptr<ModelEntity> entity);

private:
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;
};