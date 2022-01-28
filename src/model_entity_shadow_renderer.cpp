#include "model_entity_shadow_renderer.hpp"
#include "render_bus.hpp"

void ModelEntityShadowRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_shadowMatrix", _renderBus->getShadowMatrix());
	_shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
}

void ModelEntityShadowRenderer::unbind()
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

void ModelEntityShadowRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if(entity->isVisible() && entity->isShadowed())
	{
		_shader->uploadUniform("u_minX", _renderBus->getMinPosition().x);
		_shader->uploadUniform("u_maxX", _renderBus->getMaxPosition().x);
		_shader->uploadUniform("u_minY", _renderBus->getMinPosition().y);
		_shader->uploadUniform("u_maxY", _renderBus->getMaxPosition().y);
		_shader->uploadUniform("u_minZ", _renderBus->getMinPosition().z);
		_shader->uploadUniform("u_maxZ", _renderBus->getMaxPosition().z);
		_shader->uploadUniform("u_minTextureOpacity", MIN_TEXTURE_OPACITY);

		for(const auto& partId : entity->getPartIds())
		{
			_shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix(partId));
			_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat(partId));

			if(entity->isFaceCulled(partId))
			{
				glEnable(GL_CULL_FACE);
			}

			if(entity->getDiffuseMap(partId) != nullptr)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partId)->getId());
			}

			glBindVertexArray(entity->getMesh(partId)->getVaoId());

			glDrawArrays(GL_TRIANGLES, 0, entity->getMesh(partId)->getVertexCount());

			glBindVertexArray(0);

			if(entity->getDiffuseMap(partId) != nullptr)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if(entity->isFaceCulled(partId))
			{
				glDisable(GL_CULL_FACE);
			}
		}
	}
}