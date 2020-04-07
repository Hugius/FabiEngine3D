#pragma once
#include "EntityRenderer.hpp"
#include "GuiEntity.hpp"

class FinalRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~FinalRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const GuiEntity * entity, GLuint sceneMap);
};

