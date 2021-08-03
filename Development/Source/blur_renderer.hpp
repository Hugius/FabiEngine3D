#pragma once

#include "base_renderer.hpp"
#include "image_entity.hpp"
#include "render_framebuffer.hpp"
#include "blur_direction.hpp"
#include "blur_type.hpp"

class BlurRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void loadFramebuffers(BlurType type, unsigned int blurSize);
	void bind() override;
	void unbind() override;

	TextureID blurTexture(const shared_ptr<ImageEntity> entity, TextureID texture, unsigned int blurCount, float intensity, BlurDirection direction);

private:
	void _render(const shared_ptr<ImageEntity> entity, TextureID texture);

	BlurType _type;

	RenderFramebuffer _blurFramebuffer;
};

