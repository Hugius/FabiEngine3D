#pragma once
#include "EntityRenderer.hpp"
#include "GuiEntity.hpp"

class GuiEntityRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~GuiEntityRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const GuiEntity * entity);
};