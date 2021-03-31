#pragma once

#include "base_entity_renderer.hpp"
#include "gui_entity.hpp"
#include "render_framebuffer.hpp"
#include "blur_direction.hpp"

class BlurRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~BlurRenderer() = default;

	void addFramebuffer(int index, bool textureClamp);
	void bind()   override;
	void unbind() override;

	GLuint blurTexture(const shared_ptr<GuiEntity> entity, GLuint texture, int index, int size, float intensity, BlurDirection direction);

private:
	void _render(const shared_ptr<GuiEntity> entity, GLuint texture);

	vector<RenderFramebuffer*> _horizontalFramebuffers;
	vector<RenderFramebuffer*> _verticalFramebuffers;
};

