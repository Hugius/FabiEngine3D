#include "quad3d_color_renderer.hpp"
#include "tools.hpp"

void Quad3dColorRenderer::bind()
{
	_shaderBuffer->bind();
	_shaderBuffer->uploadUniform("u_cameraView", _camera->getView());
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

void Quad3dColorRenderer::unbind()
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

void Quad3dColorRenderer::render(const shared_ptr<Quad3d> quad3d)
{
	if(!quad3d->isVisible())
	{
		return;
	}

	if(quad3d->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	_shaderBuffer->uploadUniform("u_isWireframed", quad3d->isWireframed());
	_shaderBuffer->uploadUniform("u_transformation", quad3d->getTransformation());
	_shaderBuffer->uploadUniform("u_hasDiffuseMap", (quad3d->getDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasEmissionMap", (quad3d->getEmissionTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_color", quad3d->getColor());
	_shaderBuffer->uploadUniform("u_wireframeColor", quad3d->getWireframeColor());
	_shaderBuffer->uploadUniform("u_lightness", quad3d->getLightness());
	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, quad3d->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, quad3d->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, quad3d->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, quad3d->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, quad3d->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, quad3d->getMaxClipPosition().z));
	_shaderBuffer->uploadUniform("u_opacity", quad3d->getOpacity());
	_shaderBuffer->uploadUniform("u_isBright", quad3d->isBright());
	_shaderBuffer->uploadUniform("u_emissionIntensity", quad3d->getEmissionIntensity());
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

	if(quad3d->getEmissionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, quad3d->getEmissionTextureBuffer()->getTboId());
	}

	glBindVertexArray(quad3d->getVertexBuffer()->getVaoId());
	glDrawArrays(GL_TRIANGLES, 0, quad3d->getVertexBuffer()->getVertexCount());
	glBindVertexArray(0);

	if(quad3d->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(quad3d->getEmissionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(quad3d->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	_renderStorage->increaseTriangleCount(quad3d->getVertexBuffer()->getVertexCount() / 3);
}