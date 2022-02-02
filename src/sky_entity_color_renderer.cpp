#include "sky_entity_color_renderer.hpp"

void SkyEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_cameraView", mat44(mat33(_renderBus->getCameraView())));
	_shader->uploadUniform("u_cameraProjection", _renderBus->getCameraProjection());
	_shader->uploadUniform("u_cubeMap", 0);
}

void SkyEntityColorRenderer::unbind()
{
	_shader->unbind();
}

void SkyEntityColorRenderer::render(const shared_ptr<SkyEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	_shader->uploadUniform("u_isWireframed", entity->isWireframed());
	_shader->uploadUniform("u_transformation", entity->getTransformation());
	_shader->uploadUniform("u_lightness", (entity->getLightness() + (_renderBus->isSkyExposureEnabled() ? _renderBus->getSkyExposureLightness() : 0.0f)));
	_shader->uploadUniform("u_color", entity->getColor());
	_shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());
	_shader->uploadUniform("u_hasCubeMap", (entity->getCubeMap() != nullptr));

	if(entity->getCubeMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, entity->getCubeMap()->getId());
	}

	glBindVertexArray(entity->getMesh()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getMesh()->getVertexCount());
	_renderBus->increaseTriangleCount(entity->getMesh()->getVertexCount() / 3);

	glBindVertexArray(0);

	if(entity->getCubeMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}