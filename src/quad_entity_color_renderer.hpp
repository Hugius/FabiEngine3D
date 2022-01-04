#pragma once

#include "quad_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class QuadEntityColorRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<QuadEntity> entity);
};