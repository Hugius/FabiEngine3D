#pragma once

#include "terrain_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class TerrainEntityDepthRenderer final : BaseRenderer
{
public:
	void bind() override;
	void unbind() override;
	void render(const shared_ptr<TerrainEntity> entity);
};