#pragma once

#include "base_entity_renderer.hpp"
#include "gui_entity.hpp"

class PostRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~PostRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const shared_ptr<GuiEntity> entity);
};