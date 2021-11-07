#include "anti_aliasing_renderer.hpp"
#include "configuration.hpp"
#include "text_entity.hpp"

void AntiAliasingRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_sceneMap", 0);

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalSceneMap());
}

void AntiAliasingRenderer::unbind()
{
	// Unbind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unbind shader
	_shader.unbind();
}

void AntiAliasingRenderer::render(const shared_ptr<ImageEntity> entity)
{
	// Temporary values
	const auto buffer = entity->getRenderBuffer();

	// Bind buffer
	glBindVertexArray(buffer->getVAO());

	// Render
	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	// Unbind buffer
	glBindVertexArray(0);
}