#pragma once

#include "base_renderer.hpp"
#include "image_entity.hpp"
#include "capture_buffer.hpp"
#include "blur_direction.hpp"

class BlurRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	// Voids
	void bind() override;
	void unbind() override;
	void loadCaptureBuffer(Ivec2 bufferSize);
	void resetCaptureBuffer();

	// Miscellaneous
	TextureID blurTexture(const shared_ptr<ImageEntity> entity, TextureID texture, unsigned int blurCount, float intensity, BlurDirection direction);

private:
	// Voids
	void _render(const shared_ptr<ImageEntity> entity, TextureID texture);

	// Miscellaneous
	CaptureBuffer _captureBuffer;
};

