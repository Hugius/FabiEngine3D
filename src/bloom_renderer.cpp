#include "bloom_renderer.hpp"
#include "render_bus.hpp"

void BloomRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_worldMap", 0);
	_shader.uploadUniform("u_bloomMap", 1);
	_shader.uploadUniform("u_isBloomEnabled", _renderBus.isBloomEnabled());

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalWorldMap());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getBloomMap());
}

void BloomRenderer::unbind()
{
	// Unbind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unbind shader
	_shader.unbind();
}

void BloomRenderer::render(const shared_ptr<ImageEntity> entity)
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