#include "final_renderer.hpp"
#include "render_bus.hpp"

void FinalRenderer::bind()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_shader.bind();
}

void FinalRenderer::unbind()
{
	glDisable(GL_BLEND);
	_shader.unbind();
}

void FinalRenderer::render(const shared_ptr<GuiEntity> entity, GLuint sceneMap)
{
	if (entity->isVisible())
	{
		// Uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_mirrorHor", entity->isMirroredHorizonally());
		_shader.uploadUniform("u_mirrorVer", entity->isMirroredVertically());
		_shader.uploadUniform("u_sampler_scene", 0);

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