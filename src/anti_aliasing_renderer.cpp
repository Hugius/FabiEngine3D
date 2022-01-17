#include "anti_aliasing_renderer.hpp"
#include "configuration.hpp"
#include "text2d_entity.hpp"

void AntiAliasingRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_sceneMap", 0);

	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getFinalSceneMap()->getID());
	}
}

void AntiAliasingRenderer::unbind()
{
	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shader->unbind();
}

void AntiAliasingRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	const auto buffer = entity->getMesh();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}