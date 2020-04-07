#pragma once

#include "EntityRenderer.hpp"
#include "GuiEntity.hpp"
#include "Framebuffer.hpp"

enum BlurDirections
{
	BLUR_DIR_HORIZONTAL,
	BLUR_DIR_VERTICAL,
	BLUR_DIR_BOTH
};

class BlurRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~BlurRenderer() = default;

	void addFramebuffer(int index, bool textureClamp);
	void bind()   override;
	void unbind() override;

	GLuint blurTexture(const GuiEntity * entity, GLuint texture, int index, int size, float intensity, int direction);

private:
	void _render(const GuiEntity * entity, GLuint texture);

	vector<Framebuffer*> _horizontalFramebuffers;
	vector<Framebuffer*> _verticalFramebuffers;
};

