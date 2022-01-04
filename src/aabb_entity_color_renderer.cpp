#include "aabb_entity_color_renderer.hpp"

void AabbEntityColorRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_viewMatrix", renderBus.getViewMatrix());
	shader->uploadUniform("u_projectionMatrix", renderBus.getProjectionMatrix());

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void AabbEntityColorRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glDisable(GL_DEPTH_TEST);

	shader->unbind();
}

void AabbEntityColorRenderer::render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<AabbEntity> entity)
{
	if(entity->isVisible())
	{
		shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		shader->uploadUniform("u_color", entity->getColor());

		glBindVertexArray(entity->getMesh()->getVaoID());

		glDrawArrays(GL_LINE_STRIP, 0, entity->getMesh()->getVertexCount());
		renderBus.increaseTriangleCount(entity->getMesh()->getVertexCount() / 3);

		glBindVertexArray(0);
	}
}