#include <WE3D/GameEntityRenderer.hpp>
#include <WE3D/Configuration.hpp>

void GameEntityRenderer::bind()
{
	// Define clipping plane for SSR (Screen Space Reflections)
	float offset = 1.0f * float(int(p_shaderBus.isWaterEffectsEnabled()));
	vec4 clippingPlane = vec4(0.0f, 1.0f, 0.0f, -(p_shaderBus.getSSRHeight()) + offset);

	// Bind shader
	p_shader.bind();

	// Vertex shader uniforms
	p_shader.uploadUniform("u_viewMatrix",        p_shaderBus.getViewMatrix());
	p_shader.uploadUniform("u_projMatrix",        p_shaderBus.getProjectionMatrix());
	p_shader.uploadUniform("u_skyRotationMatrix", p_shaderBus.getSkyRotationMatrix());
	p_shader.uploadUniform("u_shadowMatrix",      p_shaderBus.getShadowMatrix());
	p_shader.uploadUniform("u_clippingPlane",     clippingPlane);
	
	// Fragment shader uniforms
	p_shader.uploadUniform("u_cameraPos",                p_shaderBus.getCameraPos());
	p_shader.uploadUniform("u_dirLightPos",              p_shaderBus.getDirLightPos());
	p_shader.uploadUniform("u_ambientStrength",          p_shaderBus.getAmbLightStrength());
	p_shader.uploadUniform("u_dirLightStrength",         p_shaderBus.getDirLightStrength());
	p_shader.uploadUniform("u_specLightStrength",        p_shaderBus.getSpecLightStrength());
	p_shader.uploadUniform("u_fogMinDistance",           p_shaderBus.getFogMinDistance());
	p_shader.uploadUniform("u_ambientLightingEnabled",   p_shaderBus.isAmbLightingEnabled());
	p_shader.uploadUniform("u_dirLightingEnabled",       p_shaderBus.isDirLightingEnabled());
	p_shader.uploadUniform("u_specLightingEnabled",      p_shaderBus.isSpecLightingEnabled());
	p_shader.uploadUniform("u_pointLightingEnabled",     p_shaderBus.isPointLightingEnabled());
	p_shader.uploadUniform("u_lightMappingEnabled",      p_shaderBus.isLightMappingEnabled());
	p_shader.uploadUniform("u_skyReflectionsEnabled",    p_shaderBus.isSkyReflectionsEnabled());
	p_shader.uploadUniform("u_screenReflectionsEnabled", p_shaderBus.isSSREnabled());
	p_shader.uploadUniform("u_fogEnabled",               p_shaderBus.isFogEnabled());
	p_shader.uploadUniform("u_shadowsEnabled",           p_shaderBus.isShadowsEnabled());
	p_shader.uploadUniform("u_skyReflectionMixValue",    p_shaderBus.getSkyReflectionMixValue());
	p_shader.uploadUniform("u_skyReflectionFactor",      p_shaderBus.getSkyReflectionFactor());
	p_shader.uploadUniform("u_screenReflectionFactor",   p_shaderBus.getSSRFactor());
	p_shader.uploadUniform("u_shadowMapSize",            Config::getInst().getShadowQuality());

	// Texture uniforms
	p_shader.uploadUniform("u_sampler_diffuseMap", 0);
	p_shader.uploadUniform("u_sampler_lightMap", 1);
	p_shader.uploadUniform("u_sampler_skyReflectionMap", 2);
	p_shader.uploadUniform("u_sampler_screenReflectionMap", 3);
	p_shader.uploadUniform("u_sampler_shadowMap", 4);
	p_shader.uploadUniform("u_sampler_dayCubeMap", 5);
	p_shader.uploadUniform("u_sampler_nightCubeMap", 6);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Texture binding
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, p_shaderBus.getSSRMap());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, p_shaderBus.getShadowMap());
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, p_shaderBus.getDayReflectionCubeMap());
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, p_shaderBus.getNightReflectionCubeMap());
}

void GameEntityRenderer::unbind()
{
	glDisable(GL_BLEND);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);

	p_shader.unbind();
	p_lightCounter = 0;
}

void GameEntityRenderer::placeLightEntity(const LightEntity * light)
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

void GameEntityRenderer::render(const GameEntity * entity)
{
	if (entity != nullptr)
	{
		if (entity->isEnabled())
		{
			// Faceculling
			if (entity->isFaceCulled())
			{
				glEnable(GL_CULL_FACE);
			}

			// Shader uniforms
			p_shader.uploadUniform("u_modelMatrix",        entity->getModelMatrix());
			p_shader.uploadUniform("u_color",              entity->getColor());
			p_shader.uploadUniform("u_isTransparent",      entity->isTransparent());
			p_shader.uploadUniform("u_isLightmapped",      entity->isLightMapped());
			p_shader.uploadUniform("u_isSkyReflective",    entity->isSkyReflective());
			p_shader.uploadUniform("u_isScreenReflective", entity->isScreenReflective());
			p_shader.uploadUniform("u_isSpecular",         entity->isSpecular());
			p_shader.uploadUniform("u_maxY",               entity->getMaxY());
			p_shader.uploadUniform("u_customAlpha",        entity->getAlpha());
			p_shader.uploadUniform("u_isShadowed",         entity->isShadowed());
			p_shader.uploadUniform("u_uvRepeat",		   entity->getUvRepeat());

			// Bind
			int index = 0;
			for (auto & buffer : entity->getOglBuffers())
			{
				// Diffuse map
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(index));

				// Light map
				if (entity->isLightMapped())
				{
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, entity->getLightMap(index));
				}

				// Reflection map for sky reflections
				if (entity->isSkyReflective())
				{
					glActiveTexture(GL_TEXTURE2);
					glBindTexture(GL_TEXTURE_2D, entity->getReflectionMap(index));
				}

				// Bind
				glBindVertexArray(buffer->getVAO());

				// Render
				if (buffer->isInstanced())
				{
					p_shader.uploadUniform("u_isInstanced", true);
					glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), buffer->getOffsetCount());
				}
				else
				{
					p_shader.uploadUniform("u_isInstanced", false);
					glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
				}

				index++;
			}

			// Unbind
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);

			// Face culling
			if (entity->isFaceCulled())
			{
				glDisable(GL_CULL_FACE);
			}
		}
	}
}