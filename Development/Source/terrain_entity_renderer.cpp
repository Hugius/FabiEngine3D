#include "terrain_entity_renderer.hpp"
#include "configuration.hpp"

using std::to_string;

void TerrainEntityRenderer::bind()
{
	// Define clipping plane for scene reflections
	vec4 clippingPlane = vec4(0.0f, 1.0f, 0.0f, -(_renderBus.getSceneReflectionHeight()) + _renderBus.getSceneReflectionOffset());

	// Bind shader
	_shader.bind();
	
	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix",    _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix",    _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_shadowMatrix",  _renderBus.getShadowMatrix());
	_shader.uploadUniform("u_clippingPlane", clippingPlane);
	
	// Fragment shader uniforms
	_shader.uploadUniform("u_cameraPosition",               _renderBus.getCameraPosition());
	_shader.uploadUniform("u_ambientLightingColor",		    _renderBus.getAmbientLightingColor());
	_shader.uploadUniform("u_directionalLightingColor",	    _renderBus.getDirectionalLightingColor());
	_shader.uploadUniform("u_directionalLightingPosition",  _renderBus.getDirectionalLightingPosition());
	_shader.uploadUniform("u_ambientLightingIntensity",     _renderBus.getAmbientLightingIntensity());
	_shader.uploadUniform("u_directionalLightingIntensity", _renderBus.getDirectionalLightingIntensity());
	_shader.uploadUniform("u_fogMinDistance",				_renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance",				_renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogDefaultFactor",				_renderBus.getFogDefaultFactor());
	_shader.uploadUniform("u_fogColor",						_renderBus.getFogColor());
	_shader.uploadUniform("u_fogEnabled",					_renderBus.isFogEnabled());
	_shader.uploadUniform("u_ambientLightingEnabled",		_renderBus.isAmbientLightingEnabled());
	_shader.uploadUniform("u_directionalLightingEnabled",	_renderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_pointLightingEnabled",			_renderBus.isPointLightingEnabled());
	_shader.uploadUniform("u_shadowAreaSize",				_renderBus.getShadowAreaSize());
	_shader.uploadUniform("u_shadowAreaCenter",				_renderBus.getShadowAreaCenter());
	_shader.uploadUniform("u_shadowsEnabled",				_renderBus.isShadowsEnabled());
	_shader.uploadUniform("u_shadowFrameRenderingEnabled",  _renderBus.isShadowFrameRenderingEnabled());
	_shader.uploadUniform("u_shadowMapSize",				_renderBus.getShadowMapSize());

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
		if (entities[i]->isVisible())
		{
			_shader.uploadUniform("u_pointLightPositions[" + to_string(i) + "]", entities[i]->getPosition());
			_shader.uploadUniform("u_pointLightColors[" + to_string(i) + "]", entities[i]->getColor());
			_shader.uploadUniform("u_pointLightIntensities[" + to_string(i) + "]", entities[i]->getIntensity());
			_shader.uploadUniform("u_pointLightDistanceFactors[" + to_string(i) + "]", entities[i]->getDistanceFactor());
		}
		else
		{
			_shader.uploadUniform("u_pointLightPositions[" + to_string(i) + "]", vec3(0.0f));
			_shader.uploadUniform("u_pointLightColors[" + to_string(i) + "]", vec3(0.0f));
			_shader.uploadUniform("u_pointLightIntensities[" + to_string(i) + "]", 0.0f);
			_shader.uploadUniform("u_pointLightDistanceFactors[" + to_string(i) + "]", 0.0f);
		}
	}
}

void TerrainEntityRenderer::render(const TerrainEntity* entity)
{
	if (entity->isVisible())
	{
		// Faceculling
		glEnable(GL_CULL_FACE);

		// Shader uniforms
		_shader.uploadUniform("u_isSpecularLighted", entity->isSpecularLighted());
		_shader.uploadUniform("u_isNormalMapped", entity->isNormalMapped());
		_shader.uploadUniform("u_isBlendMapped", entity->isBlendMapped());
		_shader.uploadUniform("u_blendMapRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_blendMapRepeatR", entity->getBlendRepeatR());
		_shader.uploadUniform("u_blendMapRepeatG", entity->getBlendRepeatG());
		_shader.uploadUniform("u_blendMapRepeatB", entity->getBlendRepeatB());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_specularLightingIntensity", 1.0f);

		// Texture uniforms
		_shader.uploadUniform("u_sampler_diffuseMap", 0);
		_shader.uploadUniform("u_sampler_normalMap", 1);
		_shader.uploadUniform("u_sampler_blendMap", 2);
		_shader.uploadUniform("u_sampler_blendMapR", 3);
		_shader.uploadUniform("u_sampler_blendMapG", 4);
		_shader.uploadUniform("u_sampler_blendMapB", 5);
		_shader.uploadUniform("u_sampler_shadowMap", 6);

		// Texture binding
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalMap());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, entity->getBlendMap());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, entity->getBlendMapR());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, entity->getBlendMapG());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, entity->getBlendMapB());
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getShadowMap());

		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, entity->getOglBuffer()->getVertexCount());
		_renderBus.increaseTriangleCount(entity->getOglBuffer()->getVertexCount() / 3);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);

		// Face culling
		glDisable(GL_CULL_FACE);
	}
}