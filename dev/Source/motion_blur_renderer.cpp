#include "motion_blur_renderer.hpp"
#include "render_bus.hpp"

void MotionBlurRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_sceneMap", 0);
	_shader.uploadUniform("u_motionBlurMap", 1);
	_shader.uploadUniform("u_mixValue", _renderBus.getMotionBlurMixValue());
	_shader.uploadUniform("u_isMotionBlurEnabled", _renderBus.isMotionBlurEnabled());

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalSceneMap());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getMotionBlurMap());
}

void MotionBlurRenderer::unbind()
{
	// Unbind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unbind shader
	_shader.unbind();
}

void MotionBlurRenderer::render(const shared_ptr<ImageEntity> entity)
{
	// Temporary values
	const auto buffer = entity->getRenderBuffer();

	// Bind buffer
	glBindVertexArray(buffer->getVAO());

	// Render
	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	// Unbind buffer
	glBindVertexArray(0);
}