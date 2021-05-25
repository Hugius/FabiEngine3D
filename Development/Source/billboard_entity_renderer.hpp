#pragma once

#include "base_entity_renderer.hpp"
#include "billboard_entity.hpp"

class BillboardEntityRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	
	void bind()   override;
	void unbind() override;
	void render(const shared_ptr<BillboardEntity> entity);
};