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
	_shader.uploadUniform("u_directionalLightingColor", _renderBus.getDirectionalLightingColor());
	_shader.uploadUniform("u_directionalLightPosition", _renderBus.getDirectionalLightingPosition());
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());
	_shader.uploadUniform("u_fogMinDistance", _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance", _renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogThickness", _renderBus.getFogThickness());
	_shader.uploadUniform("u_fogColor", _renderBus.getFogColor());
	_shader.uploadUniform("u_isFogEnabled", _renderBus.isFogEnabled());
	_shader.uploadUniform("u_nearDistance", _renderBus.getNearDistance());
	_shader.uploadUniform("u_farDistance", _renderBus.getFarDistance());
	_shader.uploadUniform("u_isDirectionalLightingEnabled", _renderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_directionalLightingIntensity", _renderBus.getDirectionalLightingIntensity());
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

	// Enable depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void WaterEntityColorRenderer::unbind()
{
	// Disable transparency
	glDisable(GL_BLEND);

	// Disable depth
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

void WaterEntityColorRenderer::processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>>& entities)
{
	// Save visible lights
	vector<shared_ptr<PointlightEntity>> visibleEntities;
	for(const auto& [keyID, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	// Upload lights
	unsigned int index = 0;
	for(unsigned int i = 0; i < visibleEntities.size(); i++)
	{
		_shader.uploadUniform("u_pointlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		_shader.uploadUniform("u_pointlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader.uploadUniform("u_pointlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader.uploadUniform("u_pointlightRadiuses[" + to_string(i) + "]", visibleEntities[i]->getRadius());
		_shader.uploadUniform("u_pointlightShapes[" + to_string(i) + "]", static_cast<int>(visibleEntities[i]->getShape()));
	}

	// Upload pointlight count
	_shader.uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
}

void WaterEntityColorRenderer::processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>>& entities)
{
	// Save visible lights
	vector<shared_ptr<SpotlightEntity>> visibleEntities;
	for(const auto& [keyID, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	// Upload lights
	for(unsigned int i = 0; i < visibleEntities.size(); i++)
	{
		_shader.uploadUniform("u_spotlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		_shader.uploadUniform("u_spotlightFrontVectors[" + to_string(i) + "]", visibleEntities[i]->getFrontVector());
		_shader.uploadUniform("u_spotlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader.uploadUniform("u_spotlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader.uploadUniform("u_spotlightAngles[" + to_string(i) + "]", cosf(Math::convertToRadians(visibleEntities[i]->getAngle())));
		_shader.uploadUniform("u_spotlightDistances[" + to_string(i) + "]", visibleEntities[i]->getDistance());
	}

	// Upload spotlight count
	_shader.uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
}

void WaterEntityColorRenderer::render(const shared_ptr<WaterEntity> entity)
{
	if(entity->hasLowQualityRenderBuffer() && entity->hasHighQualityRenderBuffer() && entity->isVisible())
	{
		// Enable wireframe
		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// Check if camera is underwater
		bool isUnderWater = (_renderBus.getCameraPosition().y < (entity->getHeight() + entity->getWaveHeight()));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().x > (entity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().x < (entity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().z > (entity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().z < (entity->getSize() / 2.0f));

		// Shader uniforms
		_shader.uploadUniform("u_isWireframed", (entity->isWireframed() || _renderBus.isWireframeRenderingEnabled()));
		_shader.uploadUniform("u_rippleOffset", entity->getRippleOffset());
		_shader.uploadUniform("u_waveOffset", entity->getWaveOffset());
		_shader.uploadUniform("u_waveHeight", entity->getWaveHeight());
		_shader.uploadUniform("u_height", entity->getHeight());
		_shader.uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		_shader.uploadUniform("u_specularShininess", entity->getSpecularShininess());
		_shader.uploadUniform("u_specularIntensity", entity->getSpecularIntensity());
		_shader.uploadUniform("u_transparency", entity->getTransparency());
		_shader.uploadUniform("u_isSpecular", entity->isSpecular());
		_shader.uploadUniform("u_isReflective", entity->isReflective());
		_shader.uploadUniform("u_isRefractive", entity->isRefractive());
		_shader.uploadUniform("u_color", entity->getColor());
		_shader.uploadUniform("u_hasDisplacementMap", entity->hasDisplacementMap());
		_shader.uploadUniform("u_hasDudvMap", entity->hasDudvMap());
		_shader.uploadUniform("u_hasNormalMap", entity->hasNormalMap());
		_shader.uploadUniform("u_isUnderWater", isUnderWater);

		// Bind textures
		if(entity->hasDudvMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, entity->getDudvMap());
		}
		if(entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMap());
		}
		if(entity->hasDisplacementMap())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, entity->getDisplacementMap());
		}

		// Bind buffer
		if(entity->hasDisplacementMap())
		{
			glBindVertexArray(entity->getHighQualityRenderBuffer()->getVAO());
		}
		else
		{
			glBindVertexArray(entity->getLowQualityRenderBuffer()->getVAO());
		}

		// Render
		if(entity->hasDisplacementMap())
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
		if(entity->hasDudvMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasDisplacementMap())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// Disable wireframe
		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}