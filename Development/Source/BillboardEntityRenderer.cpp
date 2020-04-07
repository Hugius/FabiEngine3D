#include <WE3D/BillboardEntityRenderer.hpp>
#include <WE3D/Configuration.hpp>

void BillboardEntityRenderer::bind()
{
	// Bind shader
	p_shader.bind();

	// Vertex shader uniforms
	p_shader.uploadUniform("u_viewMatrix",              p_shaderBus.getViewMatrix());
	p_shader.uploadUniform("u_projMatrix",              p_shaderBus.getProjectionMatrix());

	// Texture uniforms
	p_shader.uploadUniform("u_sampler_diffuseMap", 0);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void BillboardEntityRenderer::unbind()
{
	p_shader.unbind();
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
			p_shader.uploadUniform("u_modelMatrix",   entity->getModelMatrix());
			p_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
			p_shader.uploadUniform("u_color",         entity->getColor());
			p_shader.uploadUniform("u_uvAdder",       uvAdder);
			p_shader.uploadUniform("u_uvMultiplier",  uvMultiplier);

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