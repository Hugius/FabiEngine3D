#include "model_entity_shadow_renderer.hpp"
#include "render_bus.hpp"

void ModelEntityShadowRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_lightSpaceMatrix", _renderBus->getShadowMatrix());
	_shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void ModelEntityShadowRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	_shader->unbind();
}

void ModelEntityShadowRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if(entity->isVisible() && entity->isShadowed())
	{
		_shader->uploadUniform("u_minHeight", entity->getMinHeight());
		_shader->uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader->uploadUniform("u_minTextureOpacity", MIN_TEXTURE_OPACITY);

		for(const auto& partID : entity->getPartIDs())
		{
			_shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix(partID));
			_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat(partID));

			if(entity->isFaceCulled(partID))
			{
				glEnable(GL_CULL_FACE);
			}

			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID)->getId());
			}

			glBindVertexArray(entity->getMesh(partID)->getVaoID());

			glDrawArrays(GL_TRIANGLES, 0, entity->getMesh(partID)->getVertexCount());

			glBindVertexArray(0);

			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if(entity->isFaceCulled(partID))
			{
				glDisable(GL_CULL_FACE);
			}
		}
	}
}