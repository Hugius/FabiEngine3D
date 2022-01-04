#pragma once

#include "aabb_entity.hpp"
#include "render_bus.hpp"
#include "shader_buffer.hpp"

class AabbEntityColorRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<AabbEntity> entity);
};