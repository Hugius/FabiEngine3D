#include "bloom_renderer.hpp"
#include "render_bus.hpp"

void BloomRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_sceneMap", 0);
	_shader.uploadUniform("u_bloomMap", 1);
	_shader.uploadUniform("u_isBloomEnabled", _renderBus.isBloomEnabled());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalSceneMap()->getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getBloomMap()->getID());
}

void BloomRenderer::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	_shader.unbind();
}

void BloomRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getVertexBuffer();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}