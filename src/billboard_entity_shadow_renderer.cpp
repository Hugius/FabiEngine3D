#include "billboard_entity_shadow_renderer.hpp"

void BillboardEntityShadowRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_lightSpaceMatrix", _renderBus.getShadowMatrix());
	_shader.uploadUniform("u_diffuseMap", 0);

	// Enable clipping
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	// Enable depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void BillboardEntityShadowRenderer::unbind()
{
	// Disable depth
	glDisable(GL_DEPTH_TEST);

	// Disable clipping
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	// Unbind shader
	_shader.unbind();
}

void BillboardEntityShadowRenderer::render(const shared_ptr<BillboardEntity> entity)
{
	if(entity->isVisible() && entity->isShadowed())
	{
		// Temporary values
		const auto buffer = entity->getRenderBuffer();

		// Shader uniforms
		_shader.uploadUniform("u_transformationMatrix", entity->getTransformationMatrix());
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		_shader.uploadUniform("u_multiplierUV", entity->getMultiplierUV());
		_shader.uploadUniform("u_adderUV", entity->getAdderUV());
		_shader.uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		// Bind textures
		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}

		// Bind buffer
		glBindVertexArray(buffer->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

		// Unbind buffer
		glBindVertexArray(0);

		// Unbind textures
		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}