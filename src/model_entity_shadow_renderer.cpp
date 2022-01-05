#include "model_entity_shadow_renderer.hpp"
#include "render_bus.hpp"

void ModelEntityShadowRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_lightSpaceMatrix", renderBus->getShadowMatrix());
	shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void ModelEntityShadowRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	shader->unbind();
}

void ModelEntityShadowRenderer::render(shared_ptr<ShaderBuffer> shader, const shared_ptr<ModelEntity> entity)
{
	if(entity->isVisible() && entity->isShadowed())
	{
		if(entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		shader->uploadUniform("u_minHeight", entity->getMinHeight());
		shader->uploadUniform("u_maxHeight", entity->getMaxHeight());
		shader->uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		for(const auto& partID : entity->getPartIDs())
		{
			const auto buffer = entity->getMesh(partID);

			shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix(partID));
			shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat(partID));

			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID)->getID());
			}

			glBindVertexArray(buffer->getVaoID());

			glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

			glBindVertexArray(0);

			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		if(entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}