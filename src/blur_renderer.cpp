#include "blur_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void BlurRenderer::loadCaptureBuffer(ivec2 bufferSize)
{
	_captureBuffer.createColorTexture(ivec2(0), bufferSize, 1, true);
}

void BlurRenderer::resetCaptureBuffer()
{
	_captureBuffer.reset();
}

void BlurRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_diffuseMap", 0);
}

void BlurRenderer::unbind()
{
	_shader.unbind();
}

const TextureID BlurRenderer::blurTexture(const shared_ptr<ImageEntity> entity, TextureID texture, unsigned int blurCount, float intensity, BlurDirection direction)
{
	_shader.uploadUniform("u_intensity", intensity);

	if((direction == BlurDirection::HORIZONTAL) || (direction == BlurDirection::BOTH))
	{
		// Shader uniforms
		_shader.uploadUniform("u_isHorizontal", true);

		// Blur multiple times
		for(unsigned int i = 0; i < blurCount; i++)
		{
			_captureBuffer.bind();
			_render(entity, texture);
			_captureBuffer.unbind();
			texture = _captureBuffer.getTexture(0);
		}
	}

	if((direction == BlurDirection::VERTICAL) || (direction == BlurDirection::BOTH))
	{
		// Shader uniforms
		_shader.uploadUniform("u_isHorizontal", false);

		// Blur multiple times
		for(unsigned int i = 0; i < blurCount; i++)
		{
			_captureBuffer.bind();
			_render(entity, texture);
			_captureBuffer.unbind();
			texture = _captureBuffer.getTexture(0);
		}
	}

	return texture;
}

void BlurRenderer::_render(const shared_ptr<ImageEntity> entity, TextureID texture)
{
	const auto buffer = entity->getRenderBuffer();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(buffer->getVAO());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}