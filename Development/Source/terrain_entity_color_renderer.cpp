#include "terrain_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void TerrainEntityColorRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_shadowMatrix", _renderBus.getShadowMatrix());
	_shader.uploadUniform("u_clippingPlane", _renderBus.getClippingPlane());
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());
	_shader.uploadUniform("u_cameraFront", _renderBus.getCameraFront());
	_shader.uploadUniform("u_ambientLightColor", _renderBus.getAmbientLightColor());
	_shader.uploadUniform("u_ambientLightIntensity", _renderBus.getAmbientLightIntensity());
	_shader.uploadUniform("u_directionalLightColor", _renderBus.getDirectionalLightColor());
	_shader.uploadUniform("u_directionalLightPosition", _renderBus.getDirectionalLightPosition());
	_shader.uploadUniform("u_directionalLightIntensity", _renderBus.getDirectionalLightIntensity());
	_shader.uploadUniform("u_spotLightColor", _renderBus.getSpotLightColor());
	_shader.uploadUniform("u_spotLightIntensity", _renderBus.getSpotLightIntensity());
	_shader.uploadUniform("u_maxSpotLightDistance", _renderBus.getMaxSpotLightDistance());
	_shader.uploadUniform("u_maxSpotlightAngle", cosf(Math::degreesToRadians(_renderBus.getMaxSpotLightAngle())));
	_shader.uploadUniform("u_fogMinDistance", _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance", _renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogThickness", _renderBus.getFogThickness());
	_shader.uploadUniform("u_fogColor", _renderBus.getFogColor());
	_shader.uploadUniform("u_isFogEnabled", _renderBus.isFogEnabled());
	_shader.uploadUniform("u_isAmbientLightEnabled", _renderBus.isAmbientLightingEnabled());
	_shader.uploadUniform("u_isDirectionalLightEnabled", _renderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_isSpecularLightEnabled", _renderBus.isSpecularLightingEnabled());
	_shader.uploadUniform("u_isPointLightEnabled", _renderBus.isPointLightingEnabled());
	_shader.uploadUniform("u_isSpotLightEnabled", _renderBus.isSpotLightingEnabled());
	_shader.uploadUniform("u_shadowAreaSize", _renderBus.getShadowAreaSize());
	_shader.uploadUniform("u_shadowAreaCenter", _renderBus.getShadowAreaCenter());
	_shader.uploadUniform("u_shadowLightness", _renderBus.getShadowLightness());
	_shader.uploadUniform("u_isShadowsEnabled", _renderBus.isShadowsEnabled());
	_shader.uploadUniform("u_isShadowFrameRenderEnabled", _renderBus.isShadowFrameRenderingEnabled());
	_shader.uploadUniform("u_isLightedShadowingEnabled", _renderBus.isLightedShadowingEnabled());
	_shader.uploadUniform("u_diffuseMap", 0);
	_shader.uploadUniform("u_normalMap", 1);
	_shader.uploadUniform("u_blendMap", 2);
	_shader.uploadUniform("u_diffuseMapR", 3);
	_shader.uploadUniform("u_diffuseMapG", 4);
	_shader.uploadUniform("u_diffuseMapB", 5);
	_shader.uploadUniform("u_normalMapR", 6);
	_shader.uploadUniform("u_normalMapG", 7);
	_shader.uploadUniform("u_normalMapB", 8);
	_shader.uploadUniform("u_shadowMap", 9);

	// Bind textures
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getShadowMap());

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityColorRenderer::unbind()
{
	// Unbind textures
	glBindTexture(GL_TEXTURE_2D, 0);

	// Disable depth testing
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE9);

	// Unbind shader
	_shader.unbind();
}

void TerrainEntityColorRenderer::renderLightEntities(const unordered_map<string, shared_ptr<LightEntity>>& entities)
{
	if (_renderBus.isPointLightingEnabled())
	{
		// Compose a map of all visible lights
		unordered_map<string, shared_ptr<LightEntity>> visibleEntities;
		for (const auto& [keyID, entity] : entities)
		{
			if (entity->isVisible())
			{
				visibleEntities[keyID] = entity;
			}
		}

		// Render all lights
		unsigned int index = 0;
		for (const auto& [keyID, entity] : visibleEntities)
		{
			_shader.uploadUniform("u_pointLightPositions[" + to_string(index) + "]", entity->getPosition());
			_shader.uploadUniform("u_pointLightColors[" + to_string(index) + "]", entity->getColor());
			_shader.uploadUniform("u_pointLightIntensities[" + to_string(index) + "]", entity->getIntensity());
			_shader.uploadUniform("u_pointLightRadiuses[" + to_string(index) + "]", entity->getRadius());
			_shader.uploadUniform("u_pointLightShapes[" + to_string(index) + "]", static_cast<int>(entity->getShape()));

			index++;
		}

		// Upload amount
		_shader.uploadUniform("u_pointLightCount", static_cast<int>(visibleEntities.size()));
	}
}

void TerrainEntityColorRenderer::render(const shared_ptr<TerrainEntity> entity)
{
	if (entity->isVisible())
	{
		// Enable wire frame
		if (entity->isWireFramed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// Enable face culling
		glEnable(GL_CULL_FACE);

		// Shader uniforms
		_shader.uploadUniform("u_isSpecularLighted", entity->isSpecularLighted());
		_shader.uploadUniform("u_diffuseMapRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_diffuseMapRepeatR", entity->getBlendRepeatR());
		_shader.uploadUniform("u_diffuseMapRepeatG", entity->getBlendRepeatG());
		_shader.uploadUniform("u_diffuseMapRepeatB", entity->getBlendRepeatB());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_specularLightFactor", entity->getSpecularLightingFactor());
		_shader.uploadUniform("u_specularLightIntensity", entity->getSpecularLightingIntensity());
		_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		_shader.uploadUniform("u_hasNormalMap", entity->hasNormalMap());
		_shader.uploadUniform("u_hasBlendMap", entity->hasBlendMap());
		_shader.uploadUniform("u_hasDiffuseMapR", entity->hasDiffuseMapR());
		_shader.uploadUniform("u_hasDiffuseMapG", entity->hasDiffuseMapG());
		_shader.uploadUniform("u_hasDiffuseMapB", entity->hasDiffuseMapB());
		_shader.uploadUniform("u_hasNormalMapR", entity->hasNormalMapR());
		_shader.uploadUniform("u_hasNormalMapG", entity->hasNormalMapG());
		_shader.uploadUniform("u_hasNormalMapB", entity->hasNormalMapB());

		// Bind textures
		if (entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}
		if (entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMap());
		}
		if (entity->hasBlendMap())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, entity->getBlendMap());
		}
		if (entity->hasDiffuseMapR())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMapR());
		}
		if (entity->hasDiffuseMapG())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMapG());
		}
		if (entity->hasDiffuseMapB())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMapB());
		}
		if (entity->hasNormalMapR())
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMapR());
		}
		if (entity->hasNormalMapG())
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMapG());
		}
		if (entity->hasNormalMapB())
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMapB());
		}

		// Bind buffer
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, entity->getRenderBuffer()->getVertexCount());
		_renderBus.increaseTriangleCount(entity->getRenderBuffer()->getVertexCount() / 3);

		// Unbind buffer
		glBindVertexArray(0);

		// Unbind textures
		if (entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasBlendMap())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasDiffuseMapR())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasDiffuseMapG())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasDiffuseMapB())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasNormalMapR())
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasNormalMapG())
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasNormalMapB())
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// Disable face culling
		glDisable(GL_CULL_FACE);

		// Disable wire frame
		if (entity->isWireFramed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}