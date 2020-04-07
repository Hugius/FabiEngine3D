#include <WE3D/BlurRenderer.hpp>
#include <WE3D/ShaderBus.hpp>
#include <WE3D/Configuration.hpp>

void BlurRenderer::addFramebuffer(int index, bool textureClamp)
{
	p_horizontalFramebuffers.push_back(new Framebuffer());
	p_verticalFramebuffers.push_back(new Framebuffer());
	p_horizontalFramebuffers.back()->createColorTexture(Config::getInst().getWindowSize() / 2, 1, textureClamp);
	p_verticalFramebuffers.back()->createColorTexture(Config::getInst().getWindowSize() / 2, 1, textureClamp);
}

void BlurRenderer::bind()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	p_shader.bind();
}

void BlurRenderer::unbind()
{
	p_shader.unbind();
	glDisable(GL_BLEND);
}

GLuint BlurRenderer::blurTexture(const GuiEntity * entity, GLuint texture, int index, int size, float intensity, int direction)
{
	//GLuint newTexture;
	bool first = true;
	bool horizontal = true;
	p_shader.uploadUniform("u_intensity", intensity);

	if (direction == BLUR_DIR_BOTH)
	{
		for (int i = 0; i < size; i++)
		{
			// Bind framebuffer
			if (horizontal) { p_horizontalFramebuffers[index]->bind(); }
			else { p_verticalFramebuffers[index]->bind(); }

			// Upload uniforms
			p_shader.uploadUniform("u_horizontal", horizontal);
			p_shader.uploadUniform("u_radius", i * (i / 7.5f));

			// First time use normal texture
			if (first)
			{
				p_render(entity, texture);
				first = false;
			}
			else // Use blurred texture from last time
			{
				texture = horizontal ? p_verticalFramebuffers[index]->getTexture(0) : p_horizontalFramebuffers[index]->getTexture(0);
				p_render(entity, texture);
			}

			if (horizontal) { p_horizontalFramebuffers[index]->unbind(); }
			else { p_verticalFramebuffers[index]->unbind(); }

			horizontal = !horizontal;
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (direction == BLUR_DIR_HORIZONTAL)
			{
				p_shader.uploadUniform("u_horizontal", true);
				p_shader.uploadUniform("u_radius", i*(i / 7.5f));
				p_horizontalFramebuffers[index]->bind();
				
				if (first)
				{
					p_render(entity, texture);
					first = false;
				}
				else
				{
					texture = p_horizontalFramebuffers[index]->getTexture(0);
					p_render(entity, texture);
				}
				
				p_horizontalFramebuffers[index]->unbind();
				texture = p_horizontalFramebuffers[index]->getTexture(0);
			}
			else if (direction == BLUR_DIR_VERTICAL)
			{
				p_shader.uploadUniform("u_horizontal", false);
				p_shader.uploadUniform("u_radius", i*(i / 7.5f));
				p_verticalFramebuffers[index]->bind();
				
				if (first)
				{
					p_render(entity, texture);
					first = false;
				}
				else
				{
					texture = p_verticalFramebuffers[index]->getTexture(0);
					p_render(entity, texture);
				}

				p_verticalFramebuffers[index]->unbind();
				texture = p_verticalFramebuffers[index]->getTexture(0);
			}
		}
	}
	
	return texture;
}

void BlurRenderer::p_render(const GuiEntity * entity, GLuint texture)
{
	// Uniforms
	p_shader.uploadUniform("u_sampler_diffuse", 0);

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