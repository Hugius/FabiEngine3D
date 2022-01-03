#include "dof_renderer.hpp"
#include "render_bus.hpp"

void DofRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_depthMap", 0);
	_shader.uploadUniform("u_sceneMap", 1);
	_shader.uploadUniform("u_dofMap", 2);
	_shader.uploadUniform("u_nearDistance", _renderBus.getNearDistance());
	_shader.uploadUniform("u_farDistance", _renderBus.getFarDistance());
	_shader.uploadUniform("u_dofDynamicDistance", _renderBus.getDofDynamicDistance());
	_shader.uploadUniform("u_dofBlurDistance", _renderBus.getDofBlurDistance());
	_shader.uploadUniform("u_isDofEnabled", _renderBus.isDofEnabled());
	_shader.uploadUniform("u_isDofDynamic", _renderBus.isDofDynamic());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getDepthMap()->getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalSceneMap()->getID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getDofMap()->getID());
}

void DofRenderer::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	_shader.unbind();
}

void DofRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getVertexBuffer();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}