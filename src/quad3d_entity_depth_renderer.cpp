#include "quad3d_entity_depth_renderer.hpp"

void Quad3dEntityDepthRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_viewMatrix", _renderBus->getViewMatrix());
	_shader->uploadUniform("u_projectionMatrix", _renderBus->getProjectionMatrix());
	_shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void Quad3dEntityDepthRenderer::unbind()
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

void Quad3dEntityDepthRenderer::render(const shared_ptr<Quad3dEntity> entity, float clippingY, bool isUnderWater)
{
	if(entity->isVisible())
	{
		const auto buffer = entity->getMesh();

		_shader->uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(_renderBus->getViewMatrix())) : _renderBus->getViewMatrix()));
		_shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader->uploadUniform("u_minX", _renderBus->getMinPosition().x);
		_shader->uploadUniform("u_maxX", _renderBus->getMaxPosition().x);
		_shader->uploadUniform("u_minY", _renderBus->getMinPosition().y);
		_shader->uploadUniform("u_maxY", _renderBus->getMaxPosition().y);
		_shader->uploadUniform("u_minZ", _renderBus->getMinPosition().z);
		_shader->uploadUniform("u_maxZ", _renderBus->getMaxPosition().z);
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