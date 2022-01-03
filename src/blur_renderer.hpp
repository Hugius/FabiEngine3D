#pragma once

#include "base_renderer.hpp"
#include "quad_entity.hpp"
#include "capture_buffer.hpp"
#include "blur_direction.hpp"

class BlurRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void bind() override;
	void unbind() override;
	void loadCaptureBuffer(ivec2 bufferSize);

	const shared_ptr<TextureBuffer> blurTexture(const shared_ptr<QuadEntity> entity, shared_ptr<TextureBuffer> texture,
												unsigned int blurCount, float intensity, BlurDirection direction);

private:
	void _render(const shared_ptr<QuadEntity> entity, shared_ptr<TextureBuffer> texture);

	shared_ptr<CaptureBuffer> _captureBuffer = nullptr;
};