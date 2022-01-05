#pragma once

#include "quad_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class DofRenderer final : BaseRenderer
{
public:
	void bind() override;
	void unbind() override;
	void render(const shared_ptr<QuadEntity> entity);
};