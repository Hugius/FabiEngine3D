#include "quad3d_entity_shadow_renderer.hpp"

using std::min;
using std::max;

void Quad3dEntityShadowRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_shadowView", _renderStorage->getShadowView());
	_shaderBuffer->uploadUniform("u_shadowProjection", _renderStorage->getShadowProjection());
	_shaderBuffer->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
}

void Quad3dEntityShadowRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);
	glDisable(GL_CLIP_DISTANCE4);
	glDisable(GL_CLIP_DISTANCE5);

	_shaderBuffer->unbind();
}

void Quad3dEntityShadowRenderer::render(const shared_ptr<Quad3dEntity> entity)
{
	if(!entity->isVisible() || !entity->isShadowed())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_transformation", entity->getTransformation());
	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, entity->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, entity->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, entity->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, entity->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, entity->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, entity->getMaxClipPosition().z));
	_shaderBuffer->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
	_shaderBuffer->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
	_shaderBuffer->uploadUniform("u_uvOffset", entity->getUvOffset());
	_shaderBuffer->uploadUniform("u_minTextureAlpha", entity->getMinTextureAlpha());
	_shaderBuffer->uploadUniform("u_isHorizontallyFlipped", entity->isHorizontallyFlipped());
	_shaderBuffer->uploadUniform("u_isVerticallyFlipped", entity->isVerticallyFlipped());

	if(entity->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseTextureBuffer()->getTboId());
	}

	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);

	if(entity->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}