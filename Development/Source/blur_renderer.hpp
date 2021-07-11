#pragma once

#include "base_entity_renderer.hpp"
#include "image_entity.hpp"
#include "render_framebuffer.hpp"
#include "blur_direction.hpp"
#include "blur_type.hpp"

class BlurRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;

	void loadFramebuffers(BlurType type, unsigned int blurSize);
	void bind() override;
	void unbind() override;

	GLuint blurTexture(const shared_ptr<ImageEntity> entity, GLuint texture, unsigned int blurCount, float intensity, BlurDirection direction);

private:
	void _render(const shared_ptr<ImageEntity> entity, GLuint texture);

	BlurType _type;

	RenderFramebuffer _blurFramebuffer;
};

