#include "lens_flare_renderer.hpp"
#include "render_bus.hpp"

void LensFlareRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_depthMap", 0);
	shader->uploadUniform("u_sceneMap", 1);
	shader->uploadUniform("u_flareMap", 2);
	shader->uploadUniform("u_nearDistance", renderBus.getNearDistance());
	shader->uploadUniform("u_farDistance", renderBus.getFarDistance());
	shader->uploadUniform("u_lensFlareTransparency", renderBus.getLensFlareTransparency());
	shader->uploadUniform("u_lensFlareIntensity", renderBus.getLensFlareIntensity());
	shader->uploadUniform("u_cameraPosition", renderBus.getCameraPosition());
	shader->uploadUniform("u_flareSourcePosition", renderBus.getFlareSourcePosition());
	shader->uploadUniform("u_flareSourceUv", renderBus.getFlareSourceUv());
	shader->uploadUniform("u_isLensFlareEnabled", renderBus.isLensFlareEnabled());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderBus.getDepthMap()->getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, renderBus.getFinalSceneMap()->getID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, renderBus.getLensFlareMap()->getID());
}

void LensFlareRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->unbind();
}

void LensFlareRenderer::render(const shared_ptr<QuadEntity> entity)
{
	const auto buffer = entity->getMesh();

	glBindVertexArray(buffer->getVaoID());

	glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

	glBindVertexArray(0);
}