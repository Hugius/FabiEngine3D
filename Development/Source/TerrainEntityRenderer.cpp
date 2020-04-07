#include <WE3D/TerrainEntityRenderer.hpp>
#include <WE3D/Configuration.hpp>

void TerrainEntityRenderer::bind()
{
	// Bind shader
	p_shader.bind();
	
	// Vertex shader uniforms
	p_shader.uploadUniform("u_viewMatrix",    p_shaderBus.getViewMatrix());
	p_shader.uploadUniform("u_projMatrix",    p_shaderBus.getProjectionMatrix());
	p_shader.uploadUniform("u_shadowMatrix",  p_shaderBus.getShadowMatrix());
	p_shader.uploadUniform("u_clippingPlane", vec4(0.0f, 1.0f, 0.0f, -(p_shaderBus.getSSRHeight()) + 1.0f));
													   
	// Fragment shader uniforms						   
	p_shader.uploadUniform("u_cameraPos",              p_shaderBus.getCameraPos());
	p_shader.uploadUniform("u_dirLightPos",            p_shaderBus.getDirLightPos());
	p_shader.uploadUniform("u_ambientStrength",        p_shaderBus.getAmbLightStrength());
	p_shader.uploadUniform("u_dirLightStrength",       p_shaderBus.getDirLightStrength());
	p_shader.uploadUniform("u_fogMinDistance",         p_shaderBus.getFogMinDistance());
	p_shader.uploadUniform("u_ambientLightingEnabled", p_shaderBus.isAmbLightingEnabled());
	p_shader.uploadUniform("u_dirLightingEnabled",     p_shaderBus.isDirLightingEnabled());
	p_shader.uploadUniform("u_pointLightingEnabled",   p_shaderBus.isPointLightingEnabled());
	p_shader.uploadUniform("u_fogEnabled",             p_shaderBus.isFogEnabled());
	p_shader.uploadUniform("u_shadowsEnabled",         p_shaderBus.isShadowsEnabled());
	p_shader.uploadUniform("u_shadowMapSize",          Config::getInst().getShadowQuality());

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	p_shader.unbind();
	p_lightCounter = 0;
}

void TerrainEntityRenderer::placeLightEntity(const LightEntity * light)
{
	if (light != nullptr)
	{
		if (light->isEnabled())
		{
			p_shader.uploadUniform("u_pointLightsPos[" + std::to_string(p_lightCounter) + "]", light->getPosition());
			p_shader.uploadUniform("u_pointLightsColor[" + std::to_string(p_lightCounter) + "]", light->getColor());
			p_shader.uploadUniform("u_pointLightsStrength[" + std::to_string(p_lightCounter) + "]", light->getStrength());
			p_lightCounter++;
		}
	}
}

void TerrainEntityRenderer::render(const TerrainEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Faceculling
			glEnable(GL_CULL_FACE);

			// Shader uniforms
			p_shader.uploadUniform("u_blendmappingEnabled", entity->isBlendMapped());
			p_shader.uploadUniform("u_blendmapRepeat",      entity->getBlendRepeat());
			p_shader.uploadUniform("u_blendmapRepeatR",     entity->getBlendRepeatR());
			p_shader.uploadUniform("u_blendmapRepeatG",     entity->getBlendRepeatG());
			p_shader.uploadUniform("u_blendmapRepeatB",     entity->getBlendRepeatB());

			// Texture uniforms
			p_shader.uploadUniform("u_sampler_diffuseMap", 0);
			p_shader.uploadUniform("u_sampler_blendMap",   1);
			p_shader.uploadUniform("u_sampler_blendMapR",  2);
			p_shader.uploadUniform("u_sampler_blendMapG",  3);
			p_shader.uploadUniform("u_sampler_blendMapB",  4);
			p_shader.uploadUniform("u_sampler_shadowMap",  5);

			// Texture binding
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, entity->getBlendMap());
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, entity->getBlendMapR());
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, entity->getBlendMapG());
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getBlendMapB());
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, p_shaderBus.getShadowMap());

			// Bind
			glBindVertexArray(entity->getOglBuffer()->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);

			// Face culling
			glDisable(GL_CULL_FACE);
		}
	}
}