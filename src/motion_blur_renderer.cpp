#include "motion_blur_renderer.hpp"
#include "render_storage.hpp"

void MotionBlurRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_sceneMap", 0);
	_shaderBuffer->uploadUniform("u_motionBlurMap", 1);
	_shaderBuffer->uploadUniform("u_mixValue", _renderStorage->getMotionBlurMixValue());
	_shaderBuffer->uploadUniform("u_isMotionBlurEnabled", _renderStorage->isMotionBlurEnabled());

	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getFinalSceneTextureBuffer()->getId());
	}
	if(_renderStorage->getMotionBlurTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getMotionBlurTextureBuffer()->getId());
	}
}

void MotionBlurRenderer::unbind()
{
	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getMotionBlurTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void MotionBlurRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);
}