#include "dof_renderer.hpp"
#include "render_storage.hpp"

void DofRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_depthMap", 0);
	_shaderBuffer->uploadUniform("u_sceneMap", 1);
	_shaderBuffer->uploadUniform("u_dofMap", 2);
	_shaderBuffer->uploadUniform("u_cameraNear", _camera->getNear());
	_shaderBuffer->uploadUniform("u_cameraFar", _camera->getFar());
	_shaderBuffer->uploadUniform("u_dofDynamicDistance", _renderStorage->getDofDynamicDistance());
	_shaderBuffer->uploadUniform("u_dofBlurDistance", _renderStorage->getDofBlurDistance());
	_shaderBuffer->uploadUniform("u_isDofEnabled", _renderStorage->isDofEnabled());
	_shaderBuffer->uploadUniform("u_isDofDynamic", _renderStorage->isDofDynamic());

	if(_renderStorage->getDepthTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getDepthTextureBuffer()->getTboId());
	}
	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getFinalSceneTextureBuffer()->getTboId());
	}
	if(_renderStorage->getDofTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getDofTextureBuffer()->getTboId());
	}
}

void DofRenderer::unbind()
{
	if(_renderStorage->getDepthTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getDofTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void DofRenderer::render(const shared_ptr<Quad2d> quad2d)
{
	glBindVertexArray(quad2d->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, quad2d->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);
}