#include "aabb_entity_color_renderer.hpp"

void AabbEntityColorRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());

	// Enable depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void AabbEntityColorRenderer::unbind()
{
	// Disable depth
	glDisable(GL_DEPTH_TEST);

	// Unbind shader
	_shader.unbind();
}

void AabbEntityColorRenderer::render(const shared_ptr<AabbEntity> entity)
{
	if(entity->isVisible())
	{
		// Shader uniforms
		_shader.uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		glDrawArrays(GL_LINE_STRIP, 0, entity->getRenderBuffer()->getVertexCount());
		_renderBus.increaseTriangleCount(entity->getRenderBuffer()->getVertexCount() / 3);

		// Unbind buffer
		glBindVertexArray(0);
	}
}