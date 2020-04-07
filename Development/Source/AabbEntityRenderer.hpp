#pragma once
#include "EntityRenderer.hpp"
#include "AabbEntity.hpp"

class AabbEntityRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~AabbEntityRenderer() = default;
	
	void bind()   override;
	void unbind() override;
	void render(const AabbEntity * entity);
};