#include "bloom_renderer.hpp"
#include "render_storage.hpp"

void BloomRenderer::bind()
{
	_shaderBuffer->bind();
	_shaderBuffer->uploadUniform("u_sceneMap", 0);
	_shaderBuffer->uploadUniform("u_bloomMap", 1);
	_shaderBuffer->uploadUniform("u_isBloomEnabled", _renderStorage->isBloomEnabled());

	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getFinalSceneTextureBuffer()->getTboId());
	}

	if(_renderStorage->getBloomTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getBloomTextureBuffer()->getTboId());
	}
}

void BloomRenderer::unbind()
{
	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(_renderStorage->getBloomTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void BloomRenderer::render(const shared_ptr<Quad2d> quad2d)
{
	glBindVertexArray(quad2d->getVertexBuffer()->getVaoId());
	glDrawArrays(GL_TRIANGLES, 0, quad2d->getVertexBuffer()->getVertexCount());
	glBindVertexArray(0);
}