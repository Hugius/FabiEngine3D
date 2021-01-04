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
		// Uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isMirroredHorizontally",   entity->isMirroredHorizonally());
		_shader.uploadUniform("u_isMirroredVertically",   entity->isMirroredVertically());
		_shader.uploadUniform("u_sampler_diffuse", 0);

		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sceneMap);

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}