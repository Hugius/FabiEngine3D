#pragma once

#include "base_entity_renderer.hpp"
#include "aabb_entity.hpp"

class AabbEntityRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~AabbEntityRenderer() = default;
	
	void bind()   override;
	void unbind() override;
	void render(const AabbEntity * entity);
};