#include "model_entity_shadow_renderer.hpp"
#include "render_bus.hpp"

void ModelEntityShadowRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_lightSpaceMatrix", _renderBus.getShadowMatrix());
	_shader.uploadUniform("u_diffuseMap", 0);

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

	_shader.unbind();
}

void ModelEntityShadowRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if(entity->isVisible() && entity->isShadowed())
	{
		// Enable face culling
		if(entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Shader uniforms
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		// Iterate through parts
		for(const auto& partID : entity->getPartIDs())
		{
			// Temporary values
			const auto buffer = entity->getRenderBuffer(partID);

			// Shader uniforms
			_shader.uploadUniform("u_transformationMatrix", entity->getTransformationMatrix(partID));

			// Bind textures
			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID));
			}

			// Bind buffer
			glBindVertexArray(buffer->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

			// Unbind buffer
			glBindVertexArray(0);

			// Unbind textures
			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		// Disable face culling
		if(entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}