#pragma once

#include "base_entity_renderer.hpp"
#include "gui_entity.hpp"

class GuiEntityRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~GuiEntityRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const GuiEntity * entity);
};