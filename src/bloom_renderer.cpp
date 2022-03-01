#include "bloom_renderer.hpp"
#include "render_storage.hpp"

void BloomRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_sceneMap", 0);
	_shader->uploadUniform("u_bloomMap", 1);
	_shader->uploadUniform("u_isBloomEnabled", _renderStorage->isBloomEnabled());

	if(_renderStorage->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getFinalSceneMap()->getId());
	}
	if(_renderStorage->getBloomMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getBloomMap()->getId());
	}
}

void BloomRenderer::unbind()
{
	if(_renderStorage->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getBloomMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shader->unbind();
}

void BloomRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);
}