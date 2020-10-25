#pragma once

#include "base_entity_renderer.hpp"
#include "gui_entity.hpp"
#include "opengl_framebuffer.hpp"
#include "blur_direction.hpp"

class BlurRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~BlurRenderer() = default;

	void addFramebuffer(int index, bool textureClamp);
	void bind()   override;
	void unbind() override;

	GLuint blurTexture(const GuiEntity * entity, GLuint texture, int index, int size, float intensity, BlurDirection direction);

private:
	void _render(const GuiEntity * entity, GLuint texture);

	vector<OpenGLFramebuffer*> _horizontalFramebuffers;
	vector<OpenGLFramebuffer*> _verticalFramebuffers;
};

