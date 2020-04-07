#pragma once
#include "EntityRenderer.hpp"
#include "GuiEntity.hpp"

class PostRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~PostRenderer() = default;

	void bind()   override;
	void unbind() override;
	void render(const GuiEntity * entity, GLuint sceneMap, GLuint bloomMap, GLuint dofMap, GLuint blurMap);
};