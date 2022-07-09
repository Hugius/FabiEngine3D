#pragma once

#include "base_renderer.hpp"
#include "terrain.hpp"

class TerrainDepthRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(shared_ptr<Terrain> terrain);
};