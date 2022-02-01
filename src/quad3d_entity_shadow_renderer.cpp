#include "quad3d_entity_shadow_renderer.hpp"

using std::min;
using std::max;

void Quad3dEntityShadowRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_shadowMatrix", (_renderBus->getShadowProjection() * _renderBus->getShadowView()));
	_shader->uploadUniform("u_diffuseMap", 0);

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

	_shader->unbind();
}

void Quad3dEntityShadowRenderer::render(const shared_ptr<Quad3dEntity> entity)
{
	if(!entity->isVisible() || !entity->isShadowed())
	{
		return;
	}

	_shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
	_shader->uploadUniform("u_minX", _renderBus->getMinPosition().x);
	_shader->uploadUniform("u_maxX", _renderBus->getMaxPosition().x);
	_shader->uploadUniform("u_minY", max(_renderBus->getMinPosition().y, entity->getMinHeight()));
	_shader->uploadUniform("u_maxY", min(_renderBus->getMaxPosition().y, entity->getMaxHeight()));
	_shader->uploadUniform("u_minZ", _renderBus->getMinPosition().z);
	_shader->uploadUniform("u_maxZ", _renderBus->getMaxPosition().z);
	_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
	_shader->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
	_shader->uploadUniform("u_uvOffset", entity->getUvOffset());
	_shader->uploadUniform("u_minTextureAlpha", entity->getMinTextureAlpha());

	if(entity->getDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getId());
	}

	glBindVertexArray(entity->getMesh()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getMesh()->getVertexCount());

	glBindVertexArray(0);

	if(entity->getDiffuseMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}