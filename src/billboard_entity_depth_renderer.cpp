#include "billboard_entity_depth_renderer.hpp"

void BillboardEntityDepthRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void BillboardEntityDepthRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);

	_shader.unbind();
}

void BillboardEntityDepthRenderer::render(const shared_ptr<BillboardEntity> entity, float clippingY, bool isUnderWater)
{
	if(entity->isVisible())
	{
		const auto buffer = entity->getVertexBuffer();

		_shader.uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(_renderBus.getViewMatrix())) : _renderBus.getViewMatrix()));
		_shader.uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_clippingY", clippingY);
		_shader.uploadUniform("u_isUnderWater", isUnderWater);
		_shader.uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		_shader.uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
		_shader.uploadUniform("u_uvOffset", entity->getUvOffset());
		_shader.uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getID());
		}

		glBindVertexArray(buffer->getVaoID());

		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

		glBindVertexArray(0);

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}