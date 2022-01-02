#include "aabb_entity_color_renderer.hpp"

void AabbEntityColorRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void AabbEntityColorRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);

	_shader.unbind();
}

void AabbEntityColorRenderer::render(const shared_ptr<AabbEntity> entity)
{
	if(entity->isVisible())
	{
		_shader.uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader.uploadUniform("u_color", entity->getColor());

		glBindVertexArray(entity->getVertexBuffer()->getVAO());

		glDrawArrays(GL_LINE_STRIP, 0, entity->getVertexBuffer()->getVertexCount());
		_renderBus.increaseTriangleCount(entity->getVertexBuffer()->getVertexCount() / 3);

		glBindVertexArray(0);
	}
}