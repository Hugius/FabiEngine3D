#include "terrain_entity_renderer.hpp"
#include "configuration.hpp"

void TerrainEntityRenderer::bind()
{
	// Bind shader
	_shader.bind();
	
	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix",    _shaderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix",    _shaderBus.getProjectionMatrix());
	_shader.uploadUniform("u_shadowMatrix",  _shaderBus.getShadowMatrix());
	_shader.uploadUniform("u_clippingPlane", vec4(0.0f, 1.0f, 0.0f, -(_shaderBus.getSceneReflectionHeight()) + 1.0f));
													   
	// Fragment shader uniforms						   
	_shader.uploadUniform("u_cameraPosition",             _shaderBus.getCameraPos());
	_shader.uploadUniform("u_ambientLightColor",		  _shaderBus.getAmbientLightColor());
	_shader.uploadUniform("u_directionalLightColor",	  _shaderBus.getDirectionalLightColor());
	_shader.uploadUniform("u_directionalLightPos",		  _shaderBus.getDirectionalLightPos());
	_shader.uploadUniform("u_ambientLightIntensity",       _shaderBus.getAmbientLightIntensity());
	_shader.uploadUniform("u_directionalLightIntensity",   _shaderBus.getDirectionalLightIntensity());
	_shader.uploadUniform("u_fogMinDistance",			  _shaderBus.getFogMinDistance());
	_shader.uploadUniform("u_ambientLightingEnabled",	  _shaderBus.isAmbientLightingEnabled());
	_shader.uploadUniform("u_directionalLightingEnabled", _shaderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_pointLightingEnabled",		  _shaderBus.isPointLightingEnabled());
	_shader.uploadUniform("u_fogEnabled",				  _shaderBus.isFogEnabled());
	_shader.uploadUniform("u_shadowsEnabled",			  _shaderBus.isShadowsEnabled());
	_shader.uploadUniform("u_shadowMapSize",			  Config::getInst().getShadowQuality());

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	_shader.unbind();
}

void TerrainEntityRenderer::renderLightEntities(const vector<LightEntity*>& entities)
{
	// Upload
	_shader.uploadUniform("u_pointLightCount", static_cast<int>(entities.size()));

	// Render all lights
	for (size_t i = 0; i < entities.size(); i++) 
	{
		if (entities[i]->isEnabled())
		{
			_shader.uploadUniform("u_pointLightPositions[" + std::to_string(i) + "]", entities[i]->getPosition());
			_shader.uploadUniform("u_pointLightColors[" + std::to_string(i) + "]", entities[i]->getColor());
			_shader.uploadUniform("u_pointLightIntensities[" + std::to_string(i) + "]", entities[i]->getIntensity());
		}
		else
		{
			_shader.uploadUniform("u_pointLightPositions[" + std::to_string(i) + "]", vec3(0.0f));
			_shader.uploadUniform("u_pointLightColors[" + std::to_string(i) + "]", vec3(0.0f));
			_shader.uploadUniform("u_pointLightIntensities[" + std::to_string(i) + "]", 0.0f);
		}
	}
}

void TerrainEntityRenderer::render(const TerrainEntity* entity)
{
	if (entity->isEnabled())
	{
		// Faceculling
		glEnable(GL_CULL_FACE);

		// Shader uniforms
		_shader.uploadUniform("u_blendmappingEnabled", entity->isBlendMapped());
		_shader.uploadUniform("u_blendmapRepeat", entity->getBlendRepeat());
		_shader.uploadUniform("u_blendmapRepeatR", entity->getBlendRepeatR());
		_shader.uploadUniform("u_blendmapRepeatG", entity->getBlendRepeatG());
		_shader.uploadUniform("u_blendmapRepeatB", entity->getBlendRepeatB());
		_shader.uploadUniform("u_lightness", entity->getLightness());

		// Texture uniforms
		_shader.uploadUniform("u_sampler_diffuseMap", 0);
		_shader.uploadUniform("u_sampler_blendMap", 1);
		_shader.uploadUniform("u_sampler_blendMapR", 2);
		_shader.uploadUniform("u_sampler_blendMapG", 3);
		_shader.uploadUniform("u_sampler_blendMapB", 4);
		_shader.uploadUniform("u_sampler_shadowMap", 5);

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
		glBindTexture(GL_TEXTURE_2D, _shaderBus.getShadowMap());

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