#include "motion_blur_renderer.hpp"
#include "render_bus.hpp"

void MotionBlurRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_sceneMap", 0);
	_shader->uploadUniform("u_motionBlurMap", 1);
	_shader->uploadUniform("u_mixValue", _renderBus->getMotionBlurMixValue());
	_shader->uploadUniform("u_isMotionBlurEnabled", _renderBus->isMotionBlurEnabled());

	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getFinalSceneMap()->getId());
	}
	if(_renderBus->getMotionBlurMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getMotionBlurMap()->getId());
	}
}

void MotionBlurRenderer::unbind()
{
	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderBus->getMotionBlurMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shader->unbind();
}

void MotionBlurRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	glBindVertexArray(entity->getMesh()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getMesh()->getVertexCount());

	glBindVertexArray(0);
}