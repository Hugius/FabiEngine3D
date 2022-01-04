#include "bloom_renderer.hpp"
#include "render_bus.hpp"

void BloomRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_sceneMap", 0);
	shader->uploadUniform("u_bloomMap", 1);
	shader->uploadUniform("u_isBloomEnabled", renderBus.isBloomEnabled());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderBus.getFinalSceneMap()->getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, renderBus.getBloomMap()->getID());
}

void BloomRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->unbind();
}

void BloomRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getMesh();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}