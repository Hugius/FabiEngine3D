#include "sky_color_renderer.hpp"

void SkyColorRenderer::bind()
{
	_shaderBuffer->bind();
	_shaderBuffer->uploadUniform("u_cameraView", mat44(fmat33(_camera->getView())));
	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shaderBuffer->uploadUniform("u_cubeMap", 0);
}

void SkyColorRenderer::unbind()
{
	_shaderBuffer->unbind();
}

void SkyColorRenderer::render(shared_ptr<Sky> sky)
{
	if(sky->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	_shaderBuffer->uploadUniform("u_isWireframed", sky->isWireframed());
	_shaderBuffer->uploadUniform("u_transformation", sky->getTransformation());
	_shaderBuffer->uploadUniform("u_lightness", (sky->getLightness() + (_renderStorage->isSkyExposureEnabled() ? _renderStorage->getSkyExposureLightness() : 0.0f)));
	_shaderBuffer->uploadUniform("u_color", sky->getColor());
	_shaderBuffer->uploadUniform("u_wireframeColor", sky->getWireframeColor());
	_shaderBuffer->uploadUniform("u_hasCubeMap", (sky->getCubeTextureBuffer() != nullptr));

	if(sky->getCubeTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, sky->getCubeTextureBuffer()->getTboId());
	}

	glBindVertexArray(sky->getVertexBuffer()->getVaoId());
	glDrawArrays(GL_TRIANGLES, 0, sky->getVertexBuffer()->getVertexCount());
	glBindVertexArray(0);

	if(sky->getCubeTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	if(sky->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	_renderStorage->increaseTriangleCount(sky->getVertexBuffer()->getVertexCount() / 3);
}