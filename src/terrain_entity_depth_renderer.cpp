#include "terrain_entity_depth_renderer.hpp"
#include "render_bus.hpp"

void TerrainEntityDepthRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityDepthRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);

	_shader.unbind();
}

void TerrainEntityDepthRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if(entity->isVisible())
	{
		const auto buffer = entity->getVertexBuffer();

		glEnable(GL_CULL_FACE);

		glBindVertexArray(buffer->getVaoId());

		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

		glBindVertexArray(0);

		glDisable(GL_CULL_FACE);
	}
}