#include "sky_entity_color_renderer.hpp"

void SkyColorRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_cameraView", mat44(mat33(_camera->getView())));
	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shaderBuffer->uploadUniform("u_cubeMap", 0);
}

void SkyColorRenderer::unbind()
{
	_shaderBuffer->unbind();
}

void SkyColorRenderer::render(const shared_ptr<Sky> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	_shaderBuffer->uploadUniform("u_isWireframed", entity->isWireframed());
	_shaderBuffer->uploadUniform("u_transformation", entity->getTransformation());
	_shaderBuffer->uploadUniform("u_lightness", (entity->getLightness() + (_renderStorage->isSkyExposureEnabled() ? _renderStorage->getSkyExposureLightness() : 0.0f)));
	_shaderBuffer->uploadUniform("u_color", entity->getColor());
	_shaderBuffer->uploadUniform("u_wireframeColor", entity->getWireframeColor());
	_shaderBuffer->uploadUniform("u_hasCubeMap", (entity->getCubeTextureBuffer() != nullptr));

	if(entity->getCubeTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, entity->getCubeTextureBuffer()->getTboId());
	}

	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());
	_renderStorage->increaseTriangleCount(entity->getVertexBuffer()->getVertexCount() / 3);

	glBindVertexArray(0);

	if(entity->getCubeTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}