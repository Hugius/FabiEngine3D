#pragma once

#include "quad_entity.hpp"
#include "capture_buffer.hpp"
#include "blur_direction.hpp"
#include "shader_buffer.hpp"
#include "render_bus.hpp"

class BlurRenderer final
{
public:
	void bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus);
	void unbind(shared_ptr<ShaderBuffer> shader);
	void loadCaptureBuffer(ivec2 bufferSize);

	const shared_ptr<TextureBuffer> blurTexture(shared_ptr<ShaderBuffer> shader, const shared_ptr<QuadEntity> entity,
												shared_ptr<TextureBuffer> texture, unsigned int blurCount,
												float intensity, BlurDirection direction);

private:
	void _render(const shared_ptr<QuadEntity> entity, shared_ptr<TextureBuffer> texture);

	shared_ptr<CaptureBuffer> _captor = nullptr;
};