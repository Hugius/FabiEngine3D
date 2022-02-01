#include "lens_flare_renderer.hpp"
#include "render_bus.hpp"

void LensFlareRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_depthMap", 0);
	_shader->uploadUniform("u_sceneMap", 1);
	_shader->uploadUniform("u_flareMap", 2);
	_shader->uploadUniform("u_nearDistance", _renderBus->getCameraNearDistance());
	_shader->uploadUniform("u_farDistance", _renderBus->getFarDistance());
	_shader->uploadUniform("u_lensFlareOpacity", _renderBus->getLensFlareOpacity());
	_shader->uploadUniform("u_lensFlareIntensity", _renderBus->getLensFlareIntensity());
	_shader->uploadUniform("u_cameraPosition", _renderBus->getCameraPosition());
	_shader->uploadUniform("u_flareSourcePosition", _renderBus->getFlareSourcePosition());
	_shader->uploadUniform("u_flareSourceUv", _renderBus->getFlareSourceUv());
	_shader->uploadUniform("u_isLensFlareEnabled", _renderBus->isLensFlareEnabled());

	if(_renderBus->getDepthMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getDepthMap()->getId());
	}
	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getFinalSceneMap()->getId());
	}
	if(_renderBus->getLensFlareMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getLensFlareMap()->getId());
	}
}

void LensFlareRenderer::unbind()
{
	if(_renderBus->getDepthMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderBus->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderBus->getLensFlareMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shader->unbind();
}

void LensFlareRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	glBindVertexArray(entity->getMesh()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getMesh()->getVertexCount());

	glBindVertexArray(0);
}