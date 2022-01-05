#include "terrain_entity_depth_renderer.hpp"
#include "render_bus.hpp"

void TerrainEntityDepthRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_viewMatrix", renderBus->getViewMatrix());
	shader->uploadUniform("u_projectionMatrix", renderBus->getProjectionMatrix());

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityDepthRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glDisable(GL_DEPTH_TEST);

	shader->unbind();
}

void TerrainEntityDepthRenderer::render(shared_ptr<ShaderBuffer> shader, const shared_ptr<TerrainEntity> entity)
{
	if(entity->isVisible())
	{
		const auto buffer = entity->getMesh();

		glEnable(GL_CULL_FACE);

		glBindVertexArray(buffer->getVaoID());

		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

		glBindVertexArray(0);

		glDisable(GL_CULL_FACE);
	}
}