#include "lens_flare_renderer.hpp"
#include "render_bus.hpp"

void LensFlareRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_depthMap", 0);
	_shader.uploadUniform("u_sceneMap", 1);
	_shader.uploadUniform("u_flareMap", 2);
	_shader.uploadUniform("u_nearDistance", _renderBus.getNearDistance());
	_shader.uploadUniform("u_farDistance", _renderBus.getFarDistance());
	_shader.uploadUniform("u_lensFlareTransparency", _renderBus.getLensFlareTransparency());
	_shader.uploadUniform("u_lensFlareIntensity", _renderBus.getLensFlareIntensity());
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());
	_shader.uploadUniform("u_flareSourcePosition", _renderBus.getFlareSourcePosition());
	_shader.uploadUniform("u_flareSourceUv", _renderBus.getFlareSourceUv());
	_shader.uploadUniform("u_isLensFlareEnabled", _renderBus.isLensFlareEnabled());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getDepthMap()->getTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getFinalSceneMap()->getTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getLensFlareMap()->getTexture());
}

void LensFlareRenderer::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	_shader.unbind();
}

void LensFlareRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getVertexBuffer();

	glBindVertexArray(buffer->getVAO());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}