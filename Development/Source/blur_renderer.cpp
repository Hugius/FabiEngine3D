#include "blur_renderer.hpp"
#include "shader_bus.hpp"
#include "configuration.hpp"

void BlurRenderer::addFramebuffer(int index, bool textureClamp)
{
	_horizontalFramebuffers.push_back(new OpenGLFramebuffer());
	_verticalFramebuffers.push_back(new OpenGLFramebuffer());
	_horizontalFramebuffers.back()->createColorTexture(Config::getInst().getVpSize() / 2, 1, textureClamp);
	_verticalFramebuffers.back()->createColorTexture(Config::getInst().getVpSize() / 2, 1, textureClamp);
}

void BlurRenderer::bind()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_shader.bind();
}

void BlurRenderer::unbind()
{
	_shader.unbind();
	glDisable(GL_BLEND);
}

GLuint BlurRenderer::blurTexture(const GuiEntity * entity, GLuint texture, int index, int size, float intensity, int direction)
{
	//GLuint newTexture;
	bool first = true;
	bool horizontal = true;
	_shader.uploadUniform("u_intensity", intensity);

	if (direction == BLUR_DIR_BOTH)
	{
		for (int i = 0; i < size; i++)
		{
			// Bind framebuffer
			if (horizontal) { _horizontalFramebuffers[index]->bind(); }
			else { _verticalFramebuffers[index]->bind(); }

			// Upload uniforms
			_shader.uploadUniform("u_horizontal", horizontal);
			_shader.uploadUniform("u_radius", i * (i / 7.5f));

			// First time use normal texture
			if (first)
			{
				_render(entity, texture);
				first = false;
			}
			else // Use blurred texture from last time
			{
				texture = horizontal ? _verticalFramebuffers[index]->getTexture(0) : _horizontalFramebuffers[index]->getTexture(0);
				_render(entity, texture);
			}

			if (horizontal) { _horizontalFramebuffers[index]->unbind(); }
			else { _verticalFramebuffers[index]->unbind(); }

			horizontal = !horizontal;
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (direction == BLUR_DIR_HORIZONTAL)
			{
				_shader.uploadUniform("u_horizontal", true);
				_shader.uploadUniform("u_radius", i*(i / 7.5f));
				_horizontalFramebuffers[index]->bind();
				
				if (first)
				{
					_render(entity, texture);
					first = false;
				}
				else
				{
					texture = _horizontalFramebuffers[index]->getTexture(0);
					_render(entity, texture);
				}
				
				_horizontalFramebuffers[index]->unbind();
				texture = _horizontalFramebuffers[index]->getTexture(0);
			}
			else if (direction == BLUR_DIR_VERTICAL)
			{
				_shader.uploadUniform("u_horizontal", false);
				_shader.uploadUniform("u_radius", i*(i / 7.5f));
				_verticalFramebuffers[index]->bind();
				
				if (first)
				{
					_render(entity, texture);
					first = false;
				}
				else
				{
					texture = _verticalFramebuffers[index]->getTexture(0);
					_render(entity, texture);
				}

				_verticalFramebuffers[index]->unbind();
				texture = _verticalFramebuffers[index]->getTexture(0);
			}
		}
	}
	
	return texture;
}

void BlurRenderer::_render(const GuiEntity * entity, GLuint texture)
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