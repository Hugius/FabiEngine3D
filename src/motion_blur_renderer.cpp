#include "motion_blur_renderer.hpp"
#include "render_bus.hpp"

void MotionBlurRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_sceneMap", 0);
	_shader.uploadUniform("u_motionBlurMap", 1);
	_shader.uploadUniform("u_mixValue", _renderBus.getMotionBlurMixValue());
	_shader.uploadUniform("u_isMotionBlurEnabled", _renderBus.isMotionBlurEnabled());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalSceneMap());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getMotionBlurMap());
}

void MotionBlurRenderer::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	_shader.unbind();
}

void MotionBlurRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getRenderBuffer();

	glBindVertexArray(buffer->getVAO());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}