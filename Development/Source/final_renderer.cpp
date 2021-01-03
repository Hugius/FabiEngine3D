#include "final_renderer.hpp"
#include "render_bus.hpp"

void FinalRenderer::bind()
{
	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable shader
	_shader.bind();

	// Uniforms
	_shader.uploadUniform("u_mixValue", _renderBus.getMotionBlurMixValue());
	_shader.uploadUniform("u_sampler_scene", 0);
	_shader.uploadUniform("u_sampler_motionblur", 1);
}

void FinalRenderer::unbind()
{
	// Blending
	glDisable(GL_BLEND);

	// Disable shader
	_shader.unbind();
}

void FinalRenderer::render(const shared_ptr<GuiEntity> entity, GLuint sceneMap, GLuint motionblurMap)
{
	if (entity->isVisible())
	{
		// Uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_mirrorHor", entity->isMirroredHorizonally());
		_shader.uploadUniform("u_mirrorVer", entity->isMirroredVertically());

		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sceneMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, motionblurMap);

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}