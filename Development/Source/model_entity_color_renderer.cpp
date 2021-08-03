#include "model_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void ModelEntityColorRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_skyRotationMatrix", _renderBus.getSkyRotationMatrix());
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
	_shader.uploadUniform("u_isSpotLightEnabled", _renderBus.isSpotLightingEnabled());
	_shader.uploadUniform("u_isSpecularLightEnabled", _renderBus.isSpecularLightingEnabled());
	_shader.uploadUniform("u_isPointLightEnabled", _renderBus.isPointLightingEnabled());
	_shader.uploadUniform("u_shadowAreaSize", _renderBus.getShadowAreaSize());
	_shader.uploadUniform("u_shadowAreaCenter", _renderBus.getShadowAreaCenter());
	_shader.uploadUniform("u_shadowLightness", _renderBus.getShadowLightness());
	_shader.uploadUniform("u_isShadowsEnabled", _renderBus.isShadowsEnabled());
	_shader.uploadUniform("u_isShadowFrameRenderEnabled", _renderBus.isShadowFrameRenderingEnabled());
	_shader.uploadUniform("u_isLightedShadowingEnabled", _renderBus.isLightedShadowingEnabled());
	_shader.uploadUniform("u_skyMixValue", _renderBus.getSkyMixValue());
	_shader.uploadUniform("u_mainSkyLightness", _renderBus.getMainSkyLightness());
	_shader.uploadUniform("u_mixSkyLightness", _renderBus.getMixSkyLightness());
	_shader.uploadUniform("u_mainSkyColor", _renderBus.getMainSkyColor());
	_shader.uploadUniform("u_mixSkyColor", _renderBus.getMixSkyColor());
	_shader.uploadUniform("u_diffuseMap", 0);
	_shader.uploadUniform("u_emissionMap", 1);
	_shader.uploadUniform("u_reflectionMap", 2);
	_shader.uploadUniform("u_normalMap", 3);
	_shader.uploadUniform("u_sceneReflectionMap", 4);
	_shader.uploadUniform("u_shadowMap", 5);
	_shader.uploadUniform("u_mainSkyMap", 6);
	_shader.uploadUniform("u_mixSkyMap", 7);

	// Enable clipping
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind textures
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getSceneReflectionMap());
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getShadowMap());
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _renderBus.getMainSkyReflectionCubeMap());
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _renderBus.getMixSkyReflectionCubeMap());
}

void ModelEntityColorRenderer::unbind()
{
	// Unbind textures
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Disable alpha blending
	glDisable(GL_BLEND);

	// Disable depth testing
	glDisable(GL_DEPTH_TEST);

	// Disable clipping
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	// Unbind shader
	_shader.unbind();
}

void ModelEntityColorRenderer::renderLightEntities(const unordered_map<string, shared_ptr<LightEntity>>& entities)
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

void ModelEntityColorRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if (entity->hasRenderBuffer() && entity->isVisible())
	{
		// Enable wire frame
		if (entity->isWireFramed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// Enable face culling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// View matrix
		auto viewMatrix = (entity->isCameraStatic() ? Matrix44(Matrix33(_renderBus.getViewMatrix())) : _renderBus.getViewMatrix());

		// Shader uniforms
		_shader.uploadUniform("u_specularLightFactor", entity->getSpecularFactor());
		_shader.uploadUniform("u_specularLightIntensity", entity->getSpecularIntensity());
		_shader.uploadUniform("u_isTransparent", entity->isTransparent());
		_shader.uploadUniform("u_isSkyReflective", (entity->getReflectionType() == ReflectionType::SKY));
		_shader.uploadUniform("u_isSceneReflective", (entity->getReflectionType() == ReflectionType::SCENE));
		_shader.uploadUniform("u_isSpecularLighted", entity->isSpecularLighted());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_currentY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_alpha", entity->getAlpha());
		_shader.uploadUniform("u_minDiffuseMapAlpha", MIN_DIFFUSE_MAP_ALPHA);
		_shader.uploadUniform("u_isBright", entity->isBright());
		_shader.uploadUniform("u_uvRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_viewMatrix", viewMatrix);

		// Iterate through parts
		for (const auto& partID : entity->getPartIDs())
		{
			// Temporary values
			const auto buffer = entity->getRenderBuffer(partID);

			// Model matrices
			const auto& modelMatrix = entity->getModelMatrix(partID);
			Matrix33 normalModelMatrix = Matrix33(modelMatrix);
			normalModelMatrix.invert();
			normalModelMatrix.transpose();

			// Shader uniforms
			_shader.uploadUniform("u_color", entity->getColor(partID));
			_shader.uploadUniform("u_inversion", entity->getInversion(partID));
			_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap(partID));
			_shader.uploadUniform("u_hasEmissionMap", entity->hasEmissionMap(partID));
			_shader.uploadUniform("u_hasReflectionMap", entity->hasReflectionMap(partID));
			_shader.uploadUniform("u_hasNormalMap", entity->hasNormalMap(partID));
			_shader.uploadUniform("u_modelMatrix", modelMatrix);
			_shader.uploadUniform("u_normalModelMatrix", normalModelMatrix);
			_shader.uploadUniform("u_isInstanced", buffer->isInstanced());

			// Bind textures
			if (entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID));
			}
			if (entity->hasEmissionMap(partID))
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, entity->getEmissionMap(partID));
			}
			if (entity->hasReflectionMap(partID))
			{
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, entity->getReflectionMap(partID));
			}
			if (entity->hasNormalMap(partID))
			{
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, entity->getNormalMap(partID));
			}

			// Bind buffer
			glBindVertexArray(buffer->getVAO());

			// Render
			if (buffer->isInstanced())
			{
				const auto offsetCount = static_cast<unsigned int>(buffer->getInstancedOffsets().size());
				glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), offsetCount);
				_renderBus.increaseTriangleCount((offsetCount * buffer->getVertexCount()) / 3);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
				_renderBus.increaseTriangleCount(buffer->getVertexCount() / 3);
			}

			// Unbind textures
			if (entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasEmissionMap(partID))
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasReflectionMap(partID))
			{
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasNormalMap(partID))
			{
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			// Unbind buffer
			glBindVertexArray(0);
		}

		// Disable face culling
		if (entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}

		// Disable wire frame
		if (entity->isWireFramed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}