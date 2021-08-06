#include "water_entity_color_renderer.hpp"
#include "configuration.hpp"

using std::to_string;

void WaterEntityColorRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_directionalLightColor", _renderBus.getDirectionalLightColor());
	_shader.uploadUniform("u_directionalLightPosition", _renderBus.getDirectionalLightPosition());
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());
	_shader.uploadUniform("u_fogMinDistance", _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance", _renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogThickness", _renderBus.getFogThickness());
	_shader.uploadUniform("u_fogColor", _renderBus.getFogColor());
	_shader.uploadUniform("u_isFogEnabled", _renderBus.isFogEnabled());
	_shader.uploadUniform("u_nearZ", _renderBus.getNearZ());
	_shader.uploadUniform("u_farZ", _renderBus.getFarZ());
	_shader.uploadUniform("u_isDirectionalLightEnabled", _renderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_isSpecularLightEnabled", _renderBus.isSpecularLightingEnabled());
	_shader.uploadUniform("u_isPointLightEnabled", _renderBus.isPointLightingEnabled());
	_shader.uploadUniform("u_directionalLightIntensity", _renderBus.getDirectionalLightIntensity());
	_shader.uploadUniform("u_reflectionMap", 0);
	_shader.uploadUniform("u_refractionMap", 1);
	_shader.uploadUniform("u_depthMap", 2);
	_shader.uploadUniform("u_dudvMap", 3);
	_shader.uploadUniform("u_normalMap", 4);
	_shader.uploadUniform("u_displacementMap", 5);

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getWaterReflectionMap());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getWaterRefractionMap());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getDepthMap());

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void WaterEntityColorRenderer::unbind()
{
	// Disable alpha blending
	glDisable(GL_BLEND);

	// Disable depth testing
	glDisable(GL_DEPTH_TEST);

	// Unbind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unbind shader
	_shader.unbind();
}

void WaterEntityColorRenderer::renderLightEntities(const unordered_map<string, shared_ptr<LightEntity>>& entities)
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

			index++;
		}

		// Upload amount
		_shader.uploadUniform("u_pointLightCount", static_cast<int>(visibleEntities.size()));
	}
}

void WaterEntityColorRenderer::render(const shared_ptr<WaterEntity> entity)
{
	if (entity->hasLowQualityRenderBuffer() && entity->hasHighQualityRenderBuffer() && entity->isVisible())
	{
		// Enable wire frame
		if (entity->isWireFramed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// Check if camera is underwater
		bool isUnderWater = (_renderBus.getCameraPosition().y < (entity->getPosition().y + entity->getWaveHeight()));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().x > entity->getPosition().x - (entity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().x < entity->getPosition().x + (entity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().z > entity->getPosition().z - (entity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().z < entity->getPosition().z + (entity->getSize() / 2.0f));

		// Shader uniforms
		_shader.uploadUniform("u_rippleOffset", entity->getRippleOffset());
		_shader.uploadUniform("u_waveOffset", entity->getWaveOffset());
		_shader.uploadUniform("u_waveHeight", entity->getWaveHeight());
		_shader.uploadUniform("u_positionOffset", entity->getPosition());
		_shader.uploadUniform("u_uvRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_specularLightFactor", entity->getSpecularLightingFactor());
		_shader.uploadUniform("u_specularLightIntensity", entity->getSpecularLightingIntensity());
		_shader.uploadUniform("u_transparency", entity->getTransparency());
		_shader.uploadUniform("u_isWaving", entity->isWaving());
		_shader.uploadUniform("u_isRippling", entity->isRippling());
		_shader.uploadUniform("u_isSpecularLighted", entity->isSpecularLighted());
		_shader.uploadUniform("u_isReflective", entity->isReflective());
		_shader.uploadUniform("u_isRefractive", entity->isRefractive());
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_isUnderWater", isUnderWater);
		
		// Bind textures
		if (entity->hasDudvMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, entity->getDudvMap());
		}
		if (entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMap());
		}
		if (entity->hasDisplacementMap())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, entity->getDisplacementMap());
		}

		// Bind buffer
		if (entity->isWaving())
		{
			glBindVertexArray(entity->getHighQualityRenderBuffer()->getVAO());
		}
		else
		{
			glBindVertexArray(entity->getLowQualityRenderBuffer()->getVAO());
		}

		// Render
		if (entity->isWaving())
		{
			glDrawArrays(GL_TRIANGLES, 0, entity->getHighQualityRenderBuffer()->getVertexCount());
			_renderBus.increaseTriangleCount(entity->getHighQualityRenderBuffer()->getVertexCount() / 3);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, entity->getLowQualityRenderBuffer()->getVertexCount());
			_renderBus.increaseTriangleCount(entity->getLowQualityRenderBuffer()->getVertexCount() / 3);
		}

		// Unbind buffer
		glBindVertexArray(0);

		// Unbind textures
		if (entity->hasDudvMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasDisplacementMap())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// Disable wire frame
		if (entity->isWireFramed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}