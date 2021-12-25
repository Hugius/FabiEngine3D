#pragma once

#include "base_renderer.hpp"
#include "aabb_entity.hpp"

class AabbEntityColorRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void bind() override;
	void unbind() override;
	void render(const shared_ptr<AabbEntity> entity);
};