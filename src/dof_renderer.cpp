#include "dof_renderer.hpp"
#include "render_storage.hpp"

void DofRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_depthMap", 0);
	_shader->uploadUniform("u_sceneMap", 1);
	_shader->uploadUniform("u_dofMap", 2);
	_shader->uploadUniform("u_cameraNear", _camera->getNear());
	_shader->uploadUniform("u_cameraFar", _camera->getFar());
	_shader->uploadUniform("u_dofDynamicDistance", _renderStorage->getDofDynamicDistance());
	_shader->uploadUniform("u_dofBlurDistance", _renderStorage->getDofBlurDistance());
	_shader->uploadUniform("u_isDofEnabled", _renderStorage->isDofEnabled());
	_shader->uploadUniform("u_isDofDynamic", _renderStorage->isDofDynamic());

	if(_renderStorage->getDepthMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getDepthMap()->getId());
	}
	if(_renderStorage->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getFinalSceneMap()->getId());
	}
	if(_renderStorage->getDofMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getDofMap()->getId());
	}
}

void DofRenderer::unbind()
{
	if(_renderStorage->getDepthMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getDofMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shader->unbind();
}

void DofRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);
}