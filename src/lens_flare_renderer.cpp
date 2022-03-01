#include "lens_flare_renderer.hpp"
#include "render_storage.hpp"

void LensFlareRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_depthMap", 0);
	_shader->uploadUniform("u_sceneMap", 1);
	_shader->uploadUniform("u_flareMap", 2);
	_shader->uploadUniform("u_cameraNear", _camera->getNear());
	_shader->uploadUniform("u_cameraFar", _camera->getFar());
	_shader->uploadUniform("u_lensFlareOpacity", _renderStorage->getLensFlareOpacity());
	_shader->uploadUniform("u_lensFlareIntensity", _renderStorage->getLensFlareIntensity());
	_shader->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shader->uploadUniform("u_flareSourcePosition", _renderStorage->getFlareSourcePosition());
	_shader->uploadUniform("u_flareSourceUv", _renderStorage->getFlareSourceUv());
	_shader->uploadUniform("u_isLensFlareEnabled", _renderStorage->isLensFlareEnabled());

	if(_renderStorage->getDepthMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getDepthMap()->getId());
	}
	if(_renderStorage->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getFinalSceneMap()->getId());
	}
	if(_renderStorage->getLensFlareMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getLensFlareMap()->getId());
	}
}

void LensFlareRenderer::unbind()
{
	if(_renderStorage->getDepthMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getFinalSceneMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getLensFlareMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shader->unbind();
}

void LensFlareRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);
}