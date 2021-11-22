#pragma once

#include "base_renderer.hpp"
#include "terrain_entity.hpp"

class TerrainEntityDepthRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	// VOID
	void bind() override;
	void unbind() override;
	void render(const shared_ptr<TerrainEntity> entity);
};