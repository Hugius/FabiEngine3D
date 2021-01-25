#include "terrain_entity_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void TerrainEntityRenderer::bind()
{
	// Define clipping plane for scene reflections
	Vec4 clippingPlaneReflection = Vec4(0.0f, 1.0f, 0.0f, -(_renderBus.getSceneReflectionHeight()) + _renderBus.getSceneReflectionOffset());

	// Bind shader
	_shader.bind();
	
	// Vertex shader uniforms
	_shader.uploadUniform("u_viewMatrix",    _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projMatrix",    _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_shadowMatrix",  _renderBus.getShadowMatrix());
	_shader.uploadUniform("u_clippingPlaneReflection", clippingPlaneReflection);
	
	// Fragment shader uniforms
	_shader.uploadUniform("u_cameraPosition",              _renderBus.getCameraPosition());
	_shader.uploadUniform("u_cameraFront",				   _renderBus.getCameraFront());
	_shader.uploadUniform("u_ambientLightColor",		   _renderBus.getAmbientLightColor());
	_shader.uploadUniform("u_directionalLightColor",	   _renderBus.getDirectionalLightColor());
	_shader.uploadUniform("u_directionalLightPosition",    _renderBus.getDirectionalLightPosition());
	_shader.uploadUniform("u_ambientLightIntensity",       _renderBus.getAmbientLightIntensity());
	_shader.uploadUniform("u_directionalLightIntensity",   _renderBus.getDirectionalLightIntensity());
	_shader.uploadUniform("u_spotLightColor",			   _renderBus.getSpotLightColor());
	_shader.uploadUniform("u_spotLightIntensity",	       _renderBus.getSpotLightIntensity());
	_shader.uploadUniform("u_maxSpotLightDistance",		   _renderBus.getMaxSpotLightDistance());
	_shader.uploadUniform("u_maxSpotlightAngle",		   cosf(Math::degreesToRadians(_renderBus.getMaxSpotLightAngle())));
	_shader.uploadUniform("u_fogMinDistance",			   _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance",			   _renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogDefaultFactor",			   _renderBus.getFogDefaultFactor());
	_shader.uploadUniform("u_fogColor",					   _renderBus.getFogColor());
	_shader.uploadUniform("u_isFogEnabled",				   _renderBus.isFogEnabled());
	_shader.uploadUniform("u_isNormalMappingEnabled",	   _renderBus.isNormalMappingEnabled());
	_shader.uploadUniform("u_isAmbientLightEnabled",	   _renderBus.isAmbientLightingEnabled());
	_shader.uploadUniform("u_isDirectionalLightEnabled",   _renderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_isSpecularLightEnabled",	   _renderBus.isSpecularLightingEnabled());
	_shader.uploadUniform("u_isPointLightEnabled",		   _renderBus.isPointLightingEnabled());
	_shader.uploadUniform("u_isSpotLightEnabled",		   _renderBus.isSpotLightingEnabled());
	_shader.uploadUniform("u_shadowAreaSize",			   _renderBus.getShadowAreaSize());
	_shader.uploadUniform("u_shadowAreaCenter",			   _renderBus.getShadowAreaCenter());
	_shader.uploadUniform("u_isShadowsEnabled",			   _renderBus.isShadowsEnabled());
	_shader.uploadUniform("u_isShadowFrameRenderEnabled", _renderBus.isShadowFrameRenderingEnabled());
	_shader.uploadUniform("u_shadowMapSize",			   _renderBus.getShadowMapSize());

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP_NV);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_CLAMP_NV);
	_shader.unbind();
}

void TerrainEntityRenderer::renderLightEntities(const unordered_map<string, shared_ptr<LightEntity>>& entities)
{
	// Compose a map of all visible lights
	unordered_map<string, shared_ptr<LightEntity>> visibleEntities;
	for (auto& [keyID, entity] : entities)
	{
		if (entity->isVisible())
		{
			visibleEntities[keyID] = entity;
		}
	}

	// Render all lights
	unsigned int index = 0;
	for (auto& [keyID, entity] : visibleEntities)
	{
		_shader.uploadUniform("u_pointLightPositions[" + to_string(index) + "]", entity->getPosition());
		_shader.uploadUniform("u_pointLightColors[" + to_string(index) + "]", entity->getColor());
		_shader.uploadUniform("u_pointLightIntensities[" + to_string(index) + "]", entity->getIntensity());
		_shader.uploadUniform("u_pointLightDistanceFactors[" + to_string(index) + "]", 1.0f / entity->getDistanceFactor());

		index++;
	}

	// Upload amount
	_shader.uploadUniform("u_pointLightCount", static_cast<int>(visibleEntities.size()));
}

void TerrainEntityRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if (entity->isVisible())
	{
		// Faceculling
		glEnable(GL_CULL_FACE);

		// Shader uniforms
		_shader.uploadUniform("u_isBlendMapped", entity->isBlendMapped());
		_shader.uploadUniform("u_isNormalMapped", entity->isNormalMapped());
		_shader.uploadUniform("u_isNormalMappedR", entity->isNormalMappedR());
		_shader.uploadUniform("u_isNormalMappedG", entity->isNormalMappedG());
		_shader.uploadUniform("u_isNormalMappedB", entity->isNormalMappedB());
		_shader.uploadUniform("u_isSpecularLighted", entity->isSpecularLighted());
		_shader.uploadUniform("u_diffuseMapRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_diffuseMapRepeatR", entity->getBlendRepeatR());
		_shader.uploadUniform("u_diffuseMapRepeatG", entity->getBlendRepeatG());
		_shader.uploadUniform("u_diffuseMapRepeatB", entity->getBlendRepeatB());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_specularLightFactor", entity->getSpecularLightingFactor());
		_shader.uploadUniform("u_specularLightIntensity", entity->getSpecularLightingIntensity());

		// Texture uniforms
		_shader.uploadUniform("u_sampler_diffuseMap", 0);
		_shader.uploadUniform("u_sampler_normalMap",  1);
		_shader.uploadUniform("u_sampler_blendMap",	  2);
		_shader.uploadUniform("u_sampler_diffuseMapR",  3);
		_shader.uploadUniform("u_sampler_diffuseMapG",  4);
		_shader.uploadUniform("u_sampler_diffuseMapB",  5);
		_shader.uploadUniform("u_sampler_normalMapR",  6);
		_shader.uploadUniform("u_sampler_normalMapG",  7);
		_shader.uploadUniform("u_sampler_normalMapB",  8);
		_shader.uploadUniform("u_sampler_shadowMap",  9);

		// Texture binding
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalMap());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, entity->getBlendMap());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMapR());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMapG());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMapB());
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalMapR());
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalMapG());
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalMapB());
		glActiveTexture(GL_TEXTURE9);
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