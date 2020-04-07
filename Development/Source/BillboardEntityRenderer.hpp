#pragma once
#include "EntityRenderer.hpp"
#include "BillboardEntity.hpp"

class BillboardEntityRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~BillboardEntityRenderer() = default;
	
	void bind()   override;
	void unbind() override;
	void render(const BillboardEntity * entity);
};