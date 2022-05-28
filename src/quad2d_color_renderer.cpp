#include "quad2d_color_renderer.hpp"
#include "configuration.hpp"
#include "text2d.hpp"

void Quad2dColorRenderer::bind()
{
	_shaderBuffer->bind();
	_shaderBuffer->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_BLEND);
}

void Quad2dColorRenderer::unbind()
{
	glDisable(GL_BLEND);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);

	_shaderBuffer->unbind();
}

void Quad2dColorRenderer::render(const shared_ptr<Quad2d> quad2d)
{
	if(!quad2d->isVisible())
	{
		return;
	}

	if(quad2d->isCentered())
	{
		if(((quad2d->getPosition().x - (quad2d->getSize().x * 0.5f)) > quad2d->getMaxClipPosition().x) ||
		   ((quad2d->getPosition().x + (quad2d->getSize().x * 0.5f)) < quad2d->getMinClipPosition().x) ||
		   ((quad2d->getPosition().y - (quad2d->getSize().y * 0.5f)) > quad2d->getMaxClipPosition().y) ||
		   ((quad2d->getPosition().y + (quad2d->getSize().y * 0.5f)) < quad2d->getMinClipPosition().y))
		{
			return;
		}
	}
	else
	{
		if((quad2d->getPosition().x > quad2d->getMaxClipPosition().x) ||
		   ((quad2d->getPosition().x + quad2d->getSize().x) < quad2d->getMinClipPosition().x) ||
		   (quad2d->getPosition().y > quad2d->getMaxClipPosition().y) ||
		   ((quad2d->getPosition().y + quad2d->getSize().y) < quad2d->getMinClipPosition().y))
		{
			return;
		}
	}

	_shaderBuffer->uploadUniform("u_minX", quad2d->getMinClipPosition().x);
	_shaderBuffer->uploadUniform("u_minY", quad2d->getMinClipPosition().y);
	_shaderBuffer->uploadUniform("u_maxX", quad2d->getMaxClipPosition().x);
	_shaderBuffer->uploadUniform("u_maxY", quad2d->getMaxClipPosition().y);
	_shaderBuffer->uploadUniform("u_uvMultiplier", quad2d->getUvMultiplier());
	_shaderBuffer->uploadUniform("u_uvOffset", quad2d->getUvOffset());
	_shaderBuffer->uploadUniform("u_transformation", quad2d->getTransformation());
	_shaderBuffer->uploadUniform("u_isHorizontallyFlipped", quad2d->isHorizontallyFlipped());
	_shaderBuffer->uploadUniform("u_isVerticallyFlipped", quad2d->isVerticallyFlipped());
	_shaderBuffer->uploadUniform("u_color", quad2d->getColor());
	_shaderBuffer->uploadUniform("u_opacity", quad2d->getOpacity());
	_shaderBuffer->uploadUniform("u_lightness", quad2d->getLightness());
	_shaderBuffer->uploadUniform("u_textureRepeat", quad2d->getTextureRepeat());
	_shaderBuffer->uploadUniform("u_hasDiffuseMap", (quad2d->getDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_wireframeColor", quad2d->getWireframeColor());
	_shaderBuffer->uploadUniform("u_isWireframed", quad2d->isWireframed());

	if(quad2d->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, quad2d->getDiffuseTextureBuffer()->getTboId());
	}

	glBindVertexArray(quad2d->getVertexBuffer()->getVaoId());
	glDrawArrays(GL_TRIANGLES, 0, quad2d->getVertexBuffer()->getVertexCount());
	glBindVertexArray(0);

	if(quad2d->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_renderStorage->increaseTriangleCount(quad2d->getVertexBuffer()->getVertexCount() / 3);
}