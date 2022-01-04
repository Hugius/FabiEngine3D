#pragma once

#include "quad_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class MotionBlurRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void render(const shared_ptr<QuadEntity> entity);
};