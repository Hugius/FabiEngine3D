#include "dof_renderer.hpp"
#include "render_bus.hpp"

void DofRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_depthMap", 0);
	_shader->uploadUniform("u_sceneMap", 1);
	_shader->uploadUniform("u_dofMap", 2);
	_shader->uploadUniform("u_nearDistance", _renderBus->getNearDistance());
	_shader->uploadUniform("u_farDistance", _renderBus->getFarDistance());
	_shader->uploadUniform("u_dofDynamicDistance", _renderBus->getDofDynamicDistance());
	_shader->uploadUniform("u_dofBlurDistance", _renderBus->getDofBlurDistance());
	_shader->uploadUniform("u_isDofEnabled", _renderBus->isDofEnabled());
	_shader->uploadUniform("u_isDofDynamic", _renderBus->isDofDynamic());

	if(_renderBus->getDepthMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getDepthMap()->getId());
	}
	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getFinalSceneMap()->getId());
	}
	if(_renderBus->getDofMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getDofMap()->getId());
	}
}

void DofRenderer::unbind()
{
	if(_renderBus->getDepthMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderBus->getDofMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shader->unbind();
}

void DofRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	const auto buffer = entity->getMesh();

	glBindVertexArray(buffer->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}