#include "bloom_renderer.hpp"
#include "render_bus.hpp"

void BloomRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_sceneMap", 0);
	_shader->uploadUniform("u_bloomMap", 1);
	_shader->uploadUniform("u_isBloomEnabled", _renderBus->isBloomEnabled());

	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getFinalSceneMap()->getID());
	}
	if(_renderBus->getBloomMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getBloomMap()->getID());
	}
}

void BloomRenderer::unbind()
{
	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderBus->getBloomMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shader->unbind();
}

void BloomRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	const auto buffer = entity->getMesh();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}