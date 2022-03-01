#include "quad3d_entity_color_renderer.hpp"
#include "configuration.hpp"

using std::min;
using std::max;

void Quad3dEntityColorRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shaderBuffer->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shaderBuffer->uploadUniform("u_minFogDistance", _renderStorage->getMinFogDistance());
	_shaderBuffer->uploadUniform("u_maxFogDistance", _renderStorage->getMaxFogDistance());
	_shaderBuffer->uploadUniform("u_fogThickness", _renderStorage->getFogThickness());
	_shaderBuffer->uploadUniform("u_fogColor", _renderStorage->getFogColor());
	_shaderBuffer->uploadUniform("u_isFogEnabled", _renderStorage->isFogEnabled());
	_shaderBuffer->uploadUniform("u_diffuseMap", 0);
	_shaderBuffer->uploadUniform("u_emissionMap", 1);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void Quad3dEntityColorRenderer::unbind()
{
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);
	glDisable(GL_CLIP_DISTANCE4);
	glDisable(GL_CLIP_DISTANCE5);

	_shaderBuffer->unbind();
}

void Quad3dEntityColorRenderer::render(const shared_ptr<Quad3dEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	_shaderBuffer->uploadUniform("u_cameraView", (entity->isFrozen() ? mat44(mat33(_camera->getView())) : _camera->getView()));
	_shaderBuffer->uploadUniform("u_isWireframed", entity->isWireframed());
	_shaderBuffer->uploadUniform("u_transformation", entity->getTransformation());
	_shaderBuffer->uploadUniform("u_hasDiffuseMap", (entity->getDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasEmissionMap", (entity->getEmissionTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_color", entity->getColor());
	_shaderBuffer->uploadUniform("u_wireframeColor", entity->getWireframeColor());
	_shaderBuffer->uploadUniform("u_lightness", entity->getLightness());
	_shaderBuffer->uploadUniform("u_minX", _renderStorage->getMinPosition().x);
	_shaderBuffer->uploadUniform("u_maxX", _renderStorage->getMaxPosition().x);
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinPosition().y, entity->getMinHeight()));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxPosition().y, entity->getMaxHeight()));
	_shaderBuffer->uploadUniform("u_minZ", _renderStorage->getMinPosition().z);
	_shaderBuffer->uploadUniform("u_maxZ", _renderStorage->getMaxPosition().z);
	_shaderBuffer->uploadUniform("u_opacity", entity->getOpacity());
	_shaderBuffer->uploadUniform("u_isBright", entity->isBright());
	_shaderBuffer->uploadUniform("u_emissionIntensity", entity->getEmissionIntensity());
	_shaderBuffer->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
	_shaderBuffer->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
	_shaderBuffer->uploadUniform("u_uvOffset", entity->getUvOffset());
	_shaderBuffer->uploadUniform("u_minTextureAlpha", entity->getMinTextureAlpha());

	if(entity->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseTextureBuffer()->getId());
	}
	if(entity->getEmissionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, entity->getEmissionTextureBuffer()->getId());
	}

	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());
	_renderStorage->increaseTriangleCount(entity->getVertexBuffer()->getVertexCount() / 3);

	glBindVertexArray(0);

	if(entity->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getEmissionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}