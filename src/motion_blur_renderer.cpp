#include "motion_blur_renderer.hpp"
#include "render_storage.hpp"

void MotionBlurRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_sceneMap", 0);
	_shader->uploadUniform("u_motionBlurMap", 1);
	_shader->uploadUniform("u_mixValue", _renderStorage->getMotionBlurMixValue());
	_shader->uploadUniform("u_isMotionBlurEnabled", _renderStorage->isMotionBlurEnabled());

	if(_renderStorage->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getFinalSceneMap()->getId());
	}
	if(_renderStorage->getMotionBlurMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getMotionBlurMap()->getId());
	}
}

void MotionBlurRenderer::unbind()
{
	if(_renderStorage->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getMotionBlurMap() != nullptr)
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