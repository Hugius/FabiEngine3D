#pragma once

#include "sky_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class SkyEntityColorRenderer final : BaseRenderer
{
public:
	void bind() override;
	void unbind() override;
	void render(const shared_ptr<SkyEntity> first, const shared_ptr<SkyEntity> second);
};