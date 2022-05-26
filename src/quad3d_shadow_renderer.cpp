#include "quad3d_shadow_renderer.hpp"

void Quad3dShadowRenderer::bind()
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

void Quad3dShadowRenderer::unbind()
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

void Quad3dShadowRenderer::render(const shared_ptr<Quad3d> quad3d)
{
	if(!quad3d->isVisible() || !quad3d->isShadowed())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_transformation", quad3d->getTransformation());
	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, quad3d->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, quad3d->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, quad3d->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, quad3d->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, quad3d->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, quad3d->getMaxClipPosition().z));
	_shaderBuffer->uploadUniform("u_textureRepeat", quad3d->getTextureRepeat());
	_shaderBuffer->uploadUniform("u_uvMultiplier", quad3d->getUvMultiplier());
	_shaderBuffer->uploadUniform("u_uvOffset", quad3d->getUvOffset());
	_shaderBuffer->uploadUniform("u_minAlpha", quad3d->getMinAlpha());
	_shaderBuffer->uploadUniform("u_isHorizontallyFlipped", quad3d->isHorizontallyFlipped());
	_shaderBuffer->uploadUniform("u_isVerticallyFlipped", quad3d->isVerticallyFlipped());

	if(quad3d->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, quad3d->getDiffuseTextureBuffer()->getTboId());
	}

	glBindVertexArray(quad3d->getVertexBuffer()->getVaoId());
	glDrawArrays(GL_TRIANGLES, 0, quad3d->getVertexBuffer()->getVertexCount());
	glBindVertexArray(0);

	if(quad3d->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}