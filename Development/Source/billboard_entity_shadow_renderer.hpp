#pragma once

#include "base_renderer.hpp"
#include "billboard_entity.hpp"

class BillboardEntityShadowRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void bind()   override;
	void unbind() override;
	void render(const shared_ptr<BillboardEntity> entity);
};