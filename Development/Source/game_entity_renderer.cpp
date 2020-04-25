#include "game_entity_renderer.hpp"
#include "configuration.hpp"

void GameEntityRenderer::bind()
{
	// Define clipping plane for scene reflections
	float offset = 1.0f * float(int(_shaderBus.isWaterEffectsEnabled()));
	vec4 clippingPlane = vec4(0.0f, 1.0f, 0.0f, -(_shaderBus.getSceneReflectionHeight()) + offset);

	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix",        _shaderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix",        _shaderBus.getProjectionMatrix());
	_shader.uploadUniform("u_skyRotationMatrix", _shaderBus.getSkyRotationMatrix());
	_shader.uploadUniform("u_shadowMatrix",      _shaderBus.getShadowMatrix());
	_shader.uploadUniform("u_clippingPlane",     clippingPlane);
	
	// Fragment shader uniforms
	_shader.uploadUniform("u_cameraPos",               _shaderBus.getCameraPos());
	_shader.uploadUniform("u_dirLightPos",             _shaderBus.getDirLightPos());
	_shader.uploadUniform("u_ambientStrength",         _shaderBus.getAmbLightStrength());
	_shader.uploadUniform("u_dirLightStrength",        _shaderBus.getDirLightStrength());
	_shader.uploadUniform("u_specLightStrength",       _shaderBus.getSpecLightStrength());
	_shader.uploadUniform("u_fogMinDistance",          _shaderBus.getFogMinDistance());
	_shader.uploadUniform("u_ambientLightingEnabled",  _shaderBus.isAmbLightingEnabled());
	_shader.uploadUniform("u_dirLightingEnabled",      _shaderBus.isDirLightingEnabled());
	_shader.uploadUniform("u_specLightingEnabled",     _shaderBus.isSpecLightingEnabled());
	_shader.uploadUniform("u_pointLightingEnabled",    _shaderBus.isPointLightingEnabled());
	_shader.uploadUniform("u_lightMappingEnabled",     _shaderBus.isLightMappingEnabled());
	_shader.uploadUniform("u_skyReflectionsEnabled",   _shaderBus.isSkyReflectionsEnabled());
	_shader.uploadUniform("u_sceneReflectionsEnabled", _shaderBus.isSceneReflectionsEnabled());
	_shader.uploadUniform("u_fogEnabled",              _shaderBus.isFogEnabled());
	_shader.uploadUniform("u_shadowsEnabled",          _shaderBus.isShadowsEnabled());
	_shader.uploadUniform("u_skyReflectionMixValue",   _shaderBus.getSkyReflectionMixValue());
	_shader.uploadUniform("u_skyReflectionFactor",     _shaderBus.getSkyReflectionFactor());
	_shader.uploadUniform("u_sceneReflectionFactor",   _shaderBus.getSceneReflectionFactor());
	_shader.uploadUniform("u_shadowMapSize",           Config::getInst().getShadowQuality());

	// Texture uniforms
	_shader.uploadUniform("u_sampler_diffuseMap", 0);
	_shader.uploadUniform("u_sampler_lightMap", 1);
	_shader.uploadUniform("u_sampler_skyReflectionMap", 2);
	_shader.uploadUniform("u_sampler_sceneReflectionMap", 3);
	_shader.uploadUniform("u_sampler_shadowMap", 4);
	_shader.uploadUniform("u_sampler_dayCubeMap", 5);
	_shader.uploadUniform("u_sampler_nightCubeMap", 6);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Texture binding
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _shaderBus.getSceneReflectionMap());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _shaderBus.getShadowMap());
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _shaderBus.getSkyReflectionCubeMapDay());
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _shaderBus.getSceneReflectionCubeMapNight());
}

void GameEntityRenderer::unbind()
{
	glDisable(GL_BLEND);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);

	_shader.unbind();
	_lightCounter = 0;
}

void GameEntityRenderer::placeLightEntity(const LightEntity * light)
{
	if (light != nullptr)
	{
		if (light->isEnabled())
		{
			_shader.uploadUniform("u_pointLightsPos[" + std::to_string(_lightCounter) + "]", light->getPosition());
			_shader.uploadUniform("u_pointLightsColor[" + std::to_string(_lightCounter) + "]", light->getColor());
			_shader.uploadUniform("u_pointLightsStrength[" + std::to_string(_lightCounter) + "]", light->getStrength());
			_lightCounter++;
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
			_shader.uploadUniform("u_modelMatrix",       entity->getModelMatrix());
			_shader.uploadUniform("u_color",             entity->getColor());
			_shader.uploadUniform("u_isTransparent",     entity->isTransparent());
			_shader.uploadUniform("u_isLightmapped",     entity->isLightMapped());
			_shader.uploadUniform("u_isSkyReflective",   entity->isSkyReflective());
			_shader.uploadUniform("u_isSceneReflective", entity->isSceneReflective());
			_shader.uploadUniform("u_isSpecular",        entity->isSpecular());
			_shader.uploadUniform("u_maxY",              entity->getMaxY());
			_shader.uploadUniform("u_customAlpha",       entity->getAlpha());
			_shader.uploadUniform("u_isShadowed",        entity->isShadowed());
			_shader.uploadUniform("u_uvRepeat",		     entity->getUvRepeat());
			_shader.uploadUniform("u_hasDiffuseMap",	 entity->hasTexture());

			// Bind
			int index = 0;
			for (auto & buffer : entity->getOglBuffers())
			{
				// Diffuse map
				if (entity->hasTexture())
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(index));
				}

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
					_shader.uploadUniform("u_isInstanced", true);
					glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), buffer->getOffsetCount());
				}
				else
				{
					_shader.uploadUniform("u_isInstanced", false);
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