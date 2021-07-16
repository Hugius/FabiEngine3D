#include "blur_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void BlurRenderer::loadFramebuffers(BlurType type, unsigned int blurSize)
{
	_type = type;
	_blurFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize() / blurSize, 1, true);
}

void BlurRenderer::bind()
{
	_shader.bind();
}

void BlurRenderer::unbind()
{
	_shader.unbind();
}

GLuint BlurRenderer::blurTexture(const shared_ptr<ImageEntity> entity, GLuint texture, unsigned int blurCount, float intensity, BlurDirection direction)
{
	// Shader uniforms
	_shader.uploadUniform("u_intensity", intensity);

	// Blur the texture horizontally
	if ((direction == BlurDirection::HORIZONTAL) || (direction == BlurDirection::BOTH))
	{
		// Shader uniforms
		_shader.uploadUniform("u_isHorizontal", true);

		// Blur multiple times
		for (unsigned int i = 0; i < blurCount; i++)
		{
			_blurFramebuffer.bind();
			_render(entity, texture);
			_blurFramebuffer.unbind();
			texture = _blurFramebuffer.getDiffuseMap(0);
		}
	}

	// Blur the texture vertically
	if ((direction == BlurDirection::VERTICAL) || (direction == BlurDirection::BOTH))
	{
		// Shader uniforms
		_shader.uploadUniform("u_isHorizontal", false);

		// Blur multiple times
		for (unsigned int i = 0; i < blurCount; i++)
		{
			_blurFramebuffer.bind();
			_render(entity, texture);
			_blurFramebuffer.unbind();
			texture = _blurFramebuffer.getDiffuseMap(0);
		}
	}

	return texture;
}

void BlurRenderer::_render(const shared_ptr<ImageEntity> entity, GLuint texture)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty())
	{
		// Shader uniforms
		_shader.uploadUniform("u_diffuseMap", 0);

		// Bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Unbind buffer
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}