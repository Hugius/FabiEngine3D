#include "bloom_hdr_renderer.hpp"
#include "render_bus.hpp"

void BloomHdrRenderer::bind()
{
	_shader.bind();
	_shader.uploadUniform("u_bloomBrightnessTreshold", _renderBus.getBloomBrightnessTreshold());
}

void BloomHdrRenderer::unbind()
{
	_shader.unbind();
}

void BloomHdrRenderer::render(const shared_ptr<GuiEntity> entity, GLuint sceneMap)
{
	if (entity->isVisible())
	{
		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isMirroredHorizontally",   entity->isMirroredHorizonally());
		_shader.uploadUniform("u_isMirroredVertically",   entity->isMirroredVertically());
		_shader.uploadUniform("u_sampler_diffuse", 0);

		// Bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sceneMap);

		// Check if entity has a render buffer
		if (!entity->getRenderBuffers().empty())
		{
			// Bind buffer
			glBindVertexArray(entity->getRenderBuffer()->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Unbind buffer
			glBindVertexArray(0);
		}

		// Unbind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}