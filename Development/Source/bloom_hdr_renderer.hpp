#pragma once

#include "base_entity_renderer.hpp"
#include "gui_entity.hpp"

class BloomHdrRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~BloomHdrRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const GuiEntity * entity, GLuint sceneMap);
};

