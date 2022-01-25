#include "quad3d_entity_shadow_renderer.hpp"

void Quad3dEntityShadowRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_lightSpaceMatrix", _renderBus->getShadowMatrix());
	_shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void Quad3dEntityShadowRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	_shader->unbind();
}

void Quad3dEntityShadowRenderer::render(const shared_ptr<Quad3dEntity> entity)
{
	if(entity->isVisible() && entity->isShadowed())
	{
		const auto buffer = entity->getMesh();

		_shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader->uploadUniform("u_minHeight", entity->getMinHeight());
		_shader->uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		_shader->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
		_shader->uploadUniform("u_uvOffset", entity->getUvOffset());
		_shader->uploadUniform("u_minTextureOpacity", MIN_TEXTURE_OPACITY);

		if(entity->getDiffuseMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getId());
		}

		glBindVertexArray(buffer->getVaoId());

		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

		glBindVertexArray(0);

		if(entity->getDiffuseMap() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}