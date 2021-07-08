#include "final_renderer.hpp"
#include "render_bus.hpp"

void FinalRenderer::bind()
{
	// Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_mixValue", _renderBus.getMotionBlurMixValue());
	_shader.uploadUniform("u_sceneMap", 0);
	_shader.uploadUniform("u_motionBlurMap", 1);
}

void FinalRenderer::unbind()
{
	glDisable(GL_BLEND);
	_shader.unbind();
}

void FinalRenderer::render(const shared_ptr<ImageEntity> entity, GLuint sceneMap, GLuint motionBlurMap)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty())
	{
		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_isMirroredHorizontally", entity->isMirroredHorizonally());
		_shader.uploadUniform("u_isMirroredVertically", entity->isMirroredVertically());

		// Bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sceneMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, motionBlurMap);

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Unbind buffer
		glBindVertexArray(0);

		// Unbind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}