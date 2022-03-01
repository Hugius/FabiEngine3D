#include "lens_flare_renderer.hpp"
#include "render_storage.hpp"

void LensFlareRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_depthMap", 0);
	_shaderBuffer->uploadUniform("u_sceneMap", 1);
	_shaderBuffer->uploadUniform("u_flareMap", 2);
	_shaderBuffer->uploadUniform("u_cameraNear", _camera->getNear());
	_shaderBuffer->uploadUniform("u_cameraFar", _camera->getFar());
	_shaderBuffer->uploadUniform("u_lensFlareOpacity", _renderStorage->getLensFlareOpacity());
	_shaderBuffer->uploadUniform("u_lensFlareIntensity", _renderStorage->getLensFlareIntensity());
	_shaderBuffer->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shaderBuffer->uploadUniform("u_flareSourcePosition", _renderStorage->getFlareSourcePosition());
	_shaderBuffer->uploadUniform("u_flareSourceUv", _renderStorage->getFlareSourceUv());
	_shaderBuffer->uploadUniform("u_isLensFlareEnabled", _renderStorage->isLensFlareEnabled());

	if(_renderStorage->getDepthTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getDepthTextureBuffer()->getId());
	}
	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getFinalSceneTextureBuffer()->getId());
	}
	if(_renderStorage->getLensFlareTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getLensFlareTextureBuffer()->getId());
	}
}

void LensFlareRenderer::unbind()
{
	if(_renderStorage->getDepthTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getFinalSceneTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getLensFlareTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void LensFlareRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);
}