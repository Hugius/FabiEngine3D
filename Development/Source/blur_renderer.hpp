#pragma once

#include "base_entity_renderer.hpp"
#include "gui_entity.hpp"
#include "opengl_framebuffer.hpp"

enum BlurDirections
{
	BLUR_DIR_HORIZONTAL,
	BLUR_DIR_VERTICAL,
	BLUR_DIR_BOTH
};

class BlurRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~BlurRenderer() = default;

	void addFramebuffer(int index, bool textureClamp);
	void bind()   override;
	void unbind() override;

	GLuint blurTexture(const GuiEntity * entity, GLuint texture, int index, int size, float intensity, int direction);

private:
	void _render(const GuiEntity * entity, GLuint texture);

	vector<OpenGLFramebuffer*> _horizontalFramebuffers;
	vector<OpenGLFramebuffer*> _verticalFramebuffers;
};

