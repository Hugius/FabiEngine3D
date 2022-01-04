#include "motion_blur_renderer.hpp"
#include "render_bus.hpp"

void MotionBlurRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_sceneMap", 0);
	shader->uploadUniform("u_motionBlurMap", 1);
	shader->uploadUniform("u_mixValue", renderBus.getMotionBlurMixValue());
	shader->uploadUniform("u_isMotionBlurEnabled", renderBus.isMotionBlurEnabled());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderBus.getFinalSceneMap()->getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, renderBus.getMotionBlurMap()->getID());
}

void MotionBlurRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->unbind();
}

void MotionBlurRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getMesh();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}