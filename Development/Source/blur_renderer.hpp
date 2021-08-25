#pragma once

#include "base_renderer.hpp"
#include "image_entity.hpp"
#include "capture_buffer.hpp"
#include "blur_direction.hpp"

class BlurRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void loadCaptureBuffer(Ivec2 bufferSize);
	void bind() override;
	void unbind() override;

	TextureID blurTexture(const shared_ptr<ImageEntity> entity, TextureID texture, unsigned int blurCount, float intensity, BlurDirection direction);

private:
	void _render(const shared_ptr<ImageEntity> entity, TextureID texture);

	CaptureBuffer _blurCaptureBuffer;
};

