#include "terrain_entity_depth_renderer.hpp"
#include "render_bus.hpp"

void TerrainEntityDepthRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityDepthRenderer::unbind()
{
	// Disable depth testing
	glDisable(GL_DEPTH_TEST);

	// Unbind shader
	_shader.unbind();
}

void TerrainEntityDepthRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if (entity->isVisible())
	{
		// Temporary values
		const auto buffer = entity->getRenderBuffer();

		// Enable face culling
		glEnable(GL_CULL_FACE);

		// Bind buffer
		glBindVertexArray(buffer->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

		// Unbind buffer
		glBindVertexArray(0);

		// Disable face culling
		glDisable(GL_CULL_FACE);
	}
}