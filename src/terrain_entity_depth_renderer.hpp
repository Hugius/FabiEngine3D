#pragma once

#include "base_renderer.hpp"
#include "terrain_entity.hpp"

class TerrainEntityDepthRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<TerrainEntity> entity);
};