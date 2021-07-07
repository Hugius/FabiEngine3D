#include "blur_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void BlurRenderer::addFramebuffer(unsigned int index, bool textureClamp)
{
	_horizontalFramebuffers.push_back(new RenderFramebuffer());
	_verticalFramebuffers.push_back(new RenderFramebuffer());
	_horizontalFramebuffers.back()->createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, textureClamp);
	_verticalFramebuffers.back()->createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, textureClamp);
}

void BlurRenderer::bind()
{
	_shader.bind();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BlurRenderer::unbind()
{
	glDisable(GL_BLEND);
	_shader.unbind();
}

GLuint BlurRenderer::blurTexture(const shared_ptr<ImageEntity> entity, GLuint texture, unsigned int index, unsigned int blurCount, float intensity, BlurDirection direction)
{
	// Variables
	bool firstTime = true;
	bool currentDirection = true;
	bool overrideHorizontal = (direction == BlurDirection::HORIZONTAL);
	bool overrideVertical = (direction == BlurDirection::VERTICAL);
	const unsigned int totalBlurCount = (blurCount * 2);

	// Shader uniforms
	_shader.uploadUniform("u_intensity", intensity);

	// Blur the texture
	for (int i = 0; i < totalBlurCount; i++)
	{
		// Bind framebuffer
		if (currentDirection) { _horizontalFramebuffers[index]->bind(); }
		else { _verticalFramebuffers[index]->bind(); }

		// Upload uniforms
		bool isHorizontal = overrideHorizontal ? true : (overrideVertical ? false : currentDirection);
		_shader.uploadUniform("u_horizontal", isHorizontal);
		_shader.uploadUniform("u_radius", i * (i / 7.5f));

		// First time use normal texture
		if (firstTime)
		{
			_render(entity, texture);
			firstTime = false;
		}
		else // Use blurred texture from last time
		{
			texture = currentDirection ? _verticalFramebuffers[index]->getTexture(0) : _horizontalFramebuffers[index]->getTexture(0);
			_render(entity, texture);
		}

		if (currentDirection) { _horizontalFramebuffers[index]->unbind(); }
		else { _verticalFramebuffers[index]->unbind(); }

		currentDirection = !currentDirection;
	}

	return texture;
}

void BlurRenderer::_render(const shared_ptr<ImageEntity> entity, GLuint texture)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty())
	{
		// Shader uniforms
		_shader.uploadUniform("u_sampler_diffuse", 0);

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