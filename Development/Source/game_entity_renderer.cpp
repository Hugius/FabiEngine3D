#include "game_entity_renderer.hpp"
#include "configuration.hpp"

void GameEntityRenderer::bind()
{
	// Define clipping plane for scene reflections
	vec4 clippingPlane = vec4(0.0f, 1.0f, 0.0f, -(_shaderBus.getSceneReflectionHeight() + _shaderBus.getSceneReflectionOffset()));

	// Bind shader
	_shader.bind();

	// Vertex shader uniforms
	_shader.uploadUniform("u_projMatrix",        _shaderBus.getProjectionMatrix());
	_shader.uploadUniform("u_skyRotationMatrix", _shaderBus.getSkyRotationMatrix());
	_shader.uploadUniform("u_shadowMatrix",      _shaderBus.getShadowMatrix());
	_shader.uploadUniform("u_clippingPlane",	 clippingPlane);
	
	// Fragment shader uniforms u_specularLightStrength
	_shader.uploadUniform("u_cameraPosition",				_shaderBus.getCameraPos());
	_shader.uploadUniform("u_ambientLightingEnabled",		_shaderBus.isAmbientLightingEnabled());
	_shader.uploadUniform("u_ambientLightingColor",			_shaderBus.getAmbientLightingColor());
	_shader.uploadUniform("u_ambientLightingIntensity",		_shaderBus.getAmbientLightingIntensity());
	_shader.uploadUniform("u_directionalLightingEnabled",	_shaderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_directionalLightingColor",		_shaderBus.getDirectionalLightingColor());
	_shader.uploadUniform("u_directionalLightingPosition",	_shaderBus.getDirectionalLightingPosition());
	_shader.uploadUniform("u_directionalLightingIntensity", _shaderBus.getDirectionalLightingIntensity());
	_shader.uploadUniform("u_fogMinDistance",				_shaderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogColor",						_shaderBus.getFogColor());
	_shader.uploadUniform("u_specularLightingEnabled",		_shaderBus.isSpecularLightingEnabled());
	_shader.uploadUniform("u_pointLightingEnabled",			_shaderBus.isPointLightingEnabled());
	_shader.uploadUniform("u_lightMappingEnabled",			_shaderBus.isLightMappingEnabled());
	_shader.uploadUniform("u_skyReflectionsEnabled",		_shaderBus.isSkyReflectionsEnabled());
	_shader.uploadUniform("u_sceneReflectionsEnabled",		_shaderBus.isSceneReflectionsEnabled());
	_shader.uploadUniform("u_fogEnabled",					_shaderBus.isFogEnabled());
	_shader.uploadUniform("u_shadowAreaSize",				_shaderBus.getShadowAreaSize());
	_shader.uploadUniform("u_shadowAreaCenter",				_shaderBus.getShadowAreaCenter());
	_shader.uploadUniform("u_shadowsEnabled",				_shaderBus.isShadowsEnabled());
	_shader.uploadUniform("u_shadowFrameRenderingEnabled",  _shaderBus.isShadowFrameRenderingEnabled());
	_shader.uploadUniform("u_skyReflectionFactor",			_shaderBus.getSkyReflectionFactor());
	_shader.uploadUniform("u_sceneReflectionFactor",		_shaderBus.getSceneReflectionFactor());
	_shader.uploadUniform("u_shadowMapSize",				Config::getInst().getShadowQuality());
	
	// Texture uniforms
	_shader.uploadUniform("u_sampler_diffuseMap", 0);
	_shader.uploadUniform("u_sampler_lightMap", 1);
	_shader.uploadUniform("u_sampler_skyReflectionMap", 2);
	_shader.uploadUniform("u_sampler_sceneReflectionMap", 3);
	_shader.uploadUniform("u_sampler_shadowMap", 4);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Texture binding
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _shaderBus.getSceneRefractionMap());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _shaderBus.getShadowMap());
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _shaderBus.getSkyReflectionCubeMap());
}

void GameEntityRenderer::unbind()
{
	glDisable(GL_BLEND);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);

	_shader.unbind();
}

void GameEntityRenderer::renderLightEntities(const vector<LightEntity*>& entities)
{
	_shader.uploadUniform("u_pointLightCount", static_cast<int>(entities.size()));

	// Render all lights
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->isVisible())
		{
			_shader.uploadUniform("u_pointLightPositions[" + std::to_string(i) + "]", entities[i]->getPosition());
			_shader.uploadUniform("u_pointLightColors[" + std::to_string(i) + "]", entities[i]->getColor());
			_shader.uploadUniform("u_pointLightIntensities[" + std::to_string(i) + "]", entities[i]->getIntensity());
			_shader.uploadUniform("u_pointLightDistanceFactors[" + std::to_string(i) + "]", entities[i]->getDistanceFactor());
		}
		else
		{
			_shader.uploadUniform("u_pointLightPositions[" + std::to_string(i) + "]", vec3(0.0f));
			_shader.uploadUniform("u_pointLightColors[" + std::to_string(i) + "]", vec3(0.0f));
			_shader.uploadUniform("u_pointLightIntensities[" + std::to_string(i) + "]", 0.0f);
			_shader.uploadUniform("u_pointLightDistanceFactors[" + std::to_string(i) + "]", 0.0f);
		}
	}
}

void GameEntityRenderer::render(const GameEntity* entity)
{
	if (entity->isVisible())
	{
		// Faceculling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Shader uniforms
		_shader.uploadUniform("u_normalModelMatrix", mat3(glm::inverse(glm::transpose(entity->getModelMatrix()))));
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_specularLightingFactor", entity->getSpecularFactor());
		_shader.uploadUniform("u_specularLightingIntensity", entity->getSpecularIntensity());
		_shader.uploadUniform("u_isTransparent", entity->isTransparent());
		_shader.uploadUniform("u_isLightMapped", entity->isLightMapped());
		_shader.uploadUniform("u_isSkyReflective", entity->isSkyReflective());
		_shader.uploadUniform("u_isSceneReflective", entity->isSceneReflective());
		_shader.uploadUniform("u_isSpecular", entity->isSpecularLighted());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_maxY", entity->getMaxY());
		_shader.uploadUniform("u_customAlpha", entity->getAlpha());
		_shader.uploadUniform("u_isShadowed", entity->isShadowed());
		_shader.uploadUniform("u_uvRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		
		// Check if entity is static to the camera view
		if (entity->isCameraStatic())
		{
			_shader.uploadUniform("u_viewMatrix", mat4(mat3(_shaderBus.getViewMatrix())));
		}
		else
		{
			_shader.uploadUniform("u_viewMatrix", _shaderBus.getViewMatrix());
		}

		// Bind & render
		int index = 0;
		for (auto& buffer : entity->getOglBuffers())
		{
			// Diffuse map
			if (entity->hasDiffuseMap())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(index));
			}

			// Light map
			if (entity->hasLightMap())
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, entity->getLightMap(index));
			}

			// Reflection map for sky reflections
			if (entity->hasReflectionMap())
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