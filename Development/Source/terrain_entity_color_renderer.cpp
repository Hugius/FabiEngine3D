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
	_shader.uploadUniform("u_ambientLightingColor", _renderBus.getAmbientLightingColor());
	_shader.uploadUniform("u_ambientLightingIntensity", _renderBus.getAmbientLightingIntensity());
	_shader.uploadUniform("u_directionalLightingColor", _renderBus.getDirectionalLightingColor());
	_shader.uploadUniform("u_directionalLightPosition", _renderBus.getDirectionalLightingPosition());
	_shader.uploadUniform("u_directionalLightingIntensity", _renderBus.getDirectionalLightingIntensity());
	_shader.uploadUniform("u_fogMinDistance", _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance", _renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogThickness", _renderBus.getFogThickness());
	_shader.uploadUniform("u_fogColor", _renderBus.getFogColor());
	_shader.uploadUniform("u_isFogEnabled", _renderBus.isFogEnabled());
	_shader.uploadUniform("u_isAmbientLightingEnabled", _renderBus.isAmbientLightingEnabled());
	_shader.uploadUniform("u_isDirectionalLightingEnabled", _renderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_shadowAreaSize", _renderBus.getShadowAreaSize());
	_shader.uploadUniform("u_shadowAreaCenter", _renderBus.getShadowCenterPosition());
	_shader.uploadUniform("u_shadowLightness", _renderBus.getShadowLightness());
	_shader.uploadUniform("u_isShadowsEnabled", _renderBus.isShadowsEnabled());
	_shader.uploadUniform("u_isShadowFrameRenderEnabled", _renderBus.isShadowFrameRenderingEnabled());
	_shader.uploadUniform("u_shadowMap", 0);
	_shader.uploadUniform("u_diffuseMap", 1);
	_shader.uploadUniform("u_normalMap", 2);
	_shader.uploadUniform("u_blendMap", 3);
	_shader.uploadUniform("u_diffuseMapR", 4);
	_shader.uploadUniform("u_diffuseMapG", 5);
	_shader.uploadUniform("u_diffuseMapB", 6);
	_shader.uploadUniform("u_normalMapR", 7);
	_shader.uploadUniform("u_normalMapG", 8);
	_shader.uploadUniform("u_normalMapB", 9);

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getShadowMap());

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityColorRenderer::unbind()
{
	// Unbind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Disable depth testing
	glDisable(GL_DEPTH_TEST);

	// Unbind shader
	_shader.unbind();
}

void TerrainEntityColorRenderer::processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>>& entities)
{
	// Save visible lights
	vector<shared_ptr<PointlightEntity>> visibleEntities;
	for (const auto& [keyID, entity] : entities)
	{
		if (entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	// Upload lights
	for (unsigned int i = 0; i < visibleEntities.size(); i++)
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

void TerrainEntityColorRenderer::processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>>& entities)
{
	// Save visible lights
	vector<shared_ptr<SpotlightEntity>> visibleEntities;
	for (const auto& [keyID, entity] : entities)
	{
		if (entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	// Upload lights
	for (unsigned int i = 0; i < visibleEntities.size(); i++)
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
		_shader.uploadUniform("u_isWireFramed", (entity->isWireFramed() || _renderBus.isWireFrameRenderingEnabled()));
		_shader.uploadUniform("u_isSpecular", entity->isSpecular());
		_shader.uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		_shader.uploadUniform("u_redRepeat", entity->getRedRepeat());
		_shader.uploadUniform("u_greenRepeat", entity->getGreenRepeat());
		_shader.uploadUniform("u_blueRepeat", entity->getBlueRepeat());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_specularShininess", entity->getSpecularShininess());
		_shader.uploadUniform("u_specularIntensity", entity->getSpecularIntensity());
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
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}
		if (entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMap());
		}
		if (entity->hasBlendMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, entity->getBlendMap());
		}
		if (entity->hasDiffuseMapR())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMapR());
		}
		if (entity->hasDiffuseMapG())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMapG());
		}
		if (entity->hasDiffuseMapB())
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMapB());
		}
		if (entity->hasNormalMapR())
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMapR());
		}
		if (entity->hasNormalMapG())
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMapG());
		}
		if (entity->hasNormalMapB())
		{
			glActiveTexture(GL_TEXTURE9);
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
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasBlendMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasDiffuseMapR())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasDiffuseMapG())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasDiffuseMapB())
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasNormalMapR())
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasNormalMapG())
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (entity->hasNormalMapB())
		{
			glActiveTexture(GL_TEXTURE9);
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