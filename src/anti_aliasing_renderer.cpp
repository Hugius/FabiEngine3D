#include "anti_aliasing_renderer.hpp"
#include "configuration.hpp"
#include "text2d.hpp"

void AntiAliasingRenderer::bind()
{
	_shaderBuffer->bind();
	_shaderBuffer->uploadUniform("u_sceneMap", 0);

	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, _renderStorage->getFinalSceneTextureBuffer()->getTboId());
	}
}

void AntiAliasingRenderer::unbind()
{
	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void AntiAliasingRenderer::render(const shared_ptr<Quad2d> quad2d)
{
	glBindVertexArray(quad2d->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, quad2d->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);
}