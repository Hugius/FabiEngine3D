#pragma once
#include "EntityRenderer.hpp"
#include "GuiEntity.hpp"

class BloomHdrRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~BloomHdrRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const GuiEntity * entity, GLuint sceneMap);
};

