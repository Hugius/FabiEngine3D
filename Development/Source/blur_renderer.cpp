#include "blur_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void BlurRenderer::addFramebuffer(int index, bool textureClamp)
{
	_horizontalFramebuffers.push_back(new OpenGLFramebuffer());
	_verticalFramebuffers.push_back(new OpenGLFramebuffer());
	_horizontalFramebuffers.back()->createColorTexture(ivec2(0), Config::getInst().getVpSize(), 1, textureClamp);
	_verticalFramebuffers.back()->createColorTexture(ivec2(0), Config::getInst().getVpSize(), 1, textureClamp);
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

GLuint BlurRenderer::blurTexture(const GuiEntity* entity, GLuint texture, int index, int size, float intensity, BlurDirection direction)
{
	// Variables
	bool firstTime = true;
	bool currentDirection = true;
	bool overrideHorizontal = (direction == BlurDirection::HORIZONTAL);
	bool overrideVertical = (direction == BlurDirection::VERTICAL);

	// Uniforms
	_shader.uploadUniform("u_intensity", intensity);

	// Blur the texture
	for (int i = 0; i < size; i++)
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

void BlurRenderer::_render(const GuiEntity* entity, GLuint texture)
{
	if (entity->isVisible())
	{
		// Uniforms
		_shader.uploadUniform("u_sampler_diffuse", 0);

		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}