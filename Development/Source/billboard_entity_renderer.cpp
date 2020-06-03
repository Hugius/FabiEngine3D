#include "billboard_entity_renderer.hpp"
#include "configuration.hpp"

void BillboardEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix",              _shaderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix",              _shaderBus.getProjectionMatrix());

	// Texture uniforms
	_shader.uploadUniform("u_sampler_diffuseMap", 0);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void BillboardEntityRenderer::unbind()
{
	_shader.unbind();
	glDisable(GL_DEPTH_TEST);
}

void BillboardEntityRenderer::render(const BillboardEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Sprite animation
			vec2 uvMultiplier = vec2(1.0f);
			vec2 uvAdder      = vec2(0.0f);
			if (entity->hasSpriteAnimation())
			{
				uvMultiplier = vec2(1.0f / float(entity->getTotalSpriteColumns()), 1.0f / float(entity->getTotalSpriteRows()));
				uvAdder      = vec2(float(entity->getSpriteColumnIndex()) * uvMultiplier.x, float(entity->getSpriteRowIndex()) * uvMultiplier.y);
			}

			// Shader uniforms
			_shader.uploadUniform("u_modelMatrix",   entity->getModelMatrix());
			_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
			_shader.uploadUniform("u_noTexture",	 entity->getDiffuseMap() == 0);
			_shader.uploadUniform("u_color",         entity->getColor());
			_shader.uploadUniform("u_uvRepeat",		 entity->getUvRepeat());
			_shader.uploadUniform("u_uvAdder",       uvAdder);
			_shader.uploadUniform("u_uvMultiplier",  uvMultiplier);

			// Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
	}
}