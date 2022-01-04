#pragma once

#include "terrain_entity.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class TerrainEntityDepthRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void render(shared_ptr<ShaderBuffer> shader, const shared_ptr<TerrainEntity> entity);
};