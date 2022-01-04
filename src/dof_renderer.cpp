#include "dof_renderer.hpp"
#include "render_bus.hpp"

void DofRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_depthMap", 0);
	shader->uploadUniform("u_sceneMap", 1);
	shader->uploadUniform("u_dofMap", 2);
	shader->uploadUniform("u_nearDistance", renderBus.getNearDistance());
	shader->uploadUniform("u_farDistance", renderBus.getFarDistance());
	shader->uploadUniform("u_dofDynamicDistance", renderBus.getDofDynamicDistance());
	shader->uploadUniform("u_dofBlurDistance", renderBus.getDofBlurDistance());
	shader->uploadUniform("u_isDofEnabled", renderBus.isDofEnabled());
	shader->uploadUniform("u_isDofDynamic", renderBus.isDofDynamic());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderBus.getDepthMap()->getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, renderBus.getFinalSceneMap()->getID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, renderBus.getDofMap()->getID());
}

void DofRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->unbind();
}

void DofRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getMesh();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}