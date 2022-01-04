#include "anti_aliasing_renderer.hpp"
#include "configuration.hpp"
#include "text_entity.hpp"

void AntiAliasingRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_sceneMap", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderBus.getFinalSceneMap()->getID());
}

void AntiAliasingRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->unbind();
}

void AntiAliasingRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getMesh();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}