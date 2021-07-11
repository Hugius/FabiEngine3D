#include "blur_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void BlurRenderer::loadFramebuffers(unsigned int dofDivider, unsigned int motionBlurDivider, unsigned int bloomDivider)
{
	_firstPassFramebuffers.push_back(new RenderFramebuffer());
	_secondPassFramebuffers.push_back(new RenderFramebuffer());
	_firstPassFramebuffers.back()->createColorTexture(Ivec2(0), Config::getInst().getVpSize() / dofDivider, 1, true);
	_secondPassFramebuffers.back()->createColorTexture(Ivec2(0), Config::getInst().getVpSize() / dofDivider, 1, true);
	_firstPassFramebuffers.push_back(new RenderFramebuffer());
	_secondPassFramebuffers.push_back(new RenderFramebuffer());
	_firstPassFramebuffers.back()->createColorTexture(Ivec2(0), Config::getInst().getVpSize() / motionBlurDivider, 1, true);
	_secondPassFramebuffers.back()->createColorTexture(Ivec2(0), Config::getInst().getVpSize() / motionBlurDivider, 1, true);
	_firstPassFramebuffers.push_back(new RenderFramebuffer());
	_secondPassFramebuffers.push_back(new RenderFramebuffer());
	_firstPassFramebuffers.back()->createColorTexture(Ivec2(0), Config::getInst().getVpSize() / 4, 1, true);
	_secondPassFramebuffers.back()->createColorTexture(Ivec2(0), Config::getInst().getVpSize() / 4, 1, true);
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

GLuint BlurRenderer::blurTexture(const shared_ptr<ImageEntity> entity, GLuint texture, unsigned int blurCount, float intensity, BlurDirection direction, BlurType type)
{
	// Variables
	bool isFirstTime = true;
	bool isFirstPass = true;
	bool mustOverrideHorizontal = (direction == BlurDirection::HORIZONTAL);
	bool mustOverrideVertical = (direction == BlurDirection::VERTICAL);
	const unsigned int framebufferIndex = static_cast<unsigned int>(type);

	// Shader uniforms
	_shader.uploadUniform("u_intensity", intensity);

	// Blur the texture
	for (unsigned int i = 0; i < blurCount; i++)
	{
		// Bind framebuffer
		if (isFirstPass) { _firstPassFramebuffers[framebufferIndex]->bind(); }
		else { _secondPassFramebuffers[framebufferIndex]->bind(); }

		// Upload uniforms
		_shader.uploadUniform("u_horizontal", (mustOverrideHorizontal ? true : (mustOverrideVertical ? false : isFirstPass)));

		// First time use normal texture
		if (isFirstTime)
		{
			_render(entity, texture);
			isFirstTime = false;
		}
		else // Use blurred texture from last time
		{
			texture = isFirstPass ? _secondPassFramebuffers[framebufferIndex]->getTexture(0) : _firstPassFramebuffers[framebufferIndex]->getTexture(0);
			_render(entity, texture);
		}

		// Unbind framebuffer
		if (isFirstPass) { _firstPassFramebuffers[framebufferIndex]->unbind(); }
		else { _secondPassFramebuffers[framebufferIndex]->unbind(); }

		// Swap direction
		isFirstPass = !isFirstPass;
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