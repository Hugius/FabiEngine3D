#include "anti_aliasing_renderer.hpp"
#include "configuration.hpp"
#include "text_entity.hpp"

void AntiAliasingRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_sceneMap", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus->getFinalSceneMap()->getID());
}

void AntiAliasingRenderer::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	_shader->unbind();
}

void AntiAliasingRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getMesh();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}