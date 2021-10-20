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
	_shader.uploadUniform("u_isReflectionsEnabled", _renderBus.isReflectionsEnabled());
	_shader.uploadUniform("u_shadowAreaSize", _renderBus.getShadowAreaSize());
	_shader.uploadUniform("u_shadowAreaCenter", _renderBus.getShadowCenterPosition());
	_shader.uploadUniform("u_shadowLightness", _renderBus.getShadowLightness());
	_shader.uploadUniform("u_isShadowsEnabled", _renderBus.isShadowsEnabled());
	_shader.uploadUniform("u_isShadowFrameRenderEnabled", _renderBus.isShadowFrameRenderingEnabled());
	_shader.uploadUniform("u_previousCubeReflectionMap", 0);
	_shader.uploadUniform("u_currentCubeReflectionMap", 1);
	_shader.uploadUniform("u_planarReflectionMap", 2);
	_shader.uploadUniform("u_shadowMap", 3);
	_shader.uploadUniform("u_diffuseMap", 4);
	_shader.uploadUniform("u_emissionMap", 5);
	_shader.uploadUniform("u_specularMap", 6);
	_shader.uploadUniform("u_reflectionMap", 7);
	_shader.uploadUniform("u_normalMap", 8);

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
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getPlanarReflectionMap());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getShadowMap());
}

void ModelEntityColorRenderer::unbind()
{
	// Unbind textures
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, 0);

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

void ModelEntityColorRenderer::processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>>& entities)
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

	// Upload light count
	_shader.uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
}

void ModelEntityColorRenderer::processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>>& entities)
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
		_shader.uploadUniform("u_spotlightFronts[" + to_string(i) + "]", visibleEntities[i]->getFront());
		_shader.uploadUniform("u_spotlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader.uploadUniform("u_spotlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader.uploadUniform("u_spotlightAngles[" + to_string(i) + "]", visibleEntities[i]->getAngle());
		_shader.uploadUniform("u_spotlightDistances[" + to_string(i) + "]", visibleEntities[i]->getDistance());
	}

	// Upload light count
	_shader.uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
}

void ModelEntityColorRenderer::render(const shared_ptr<ModelEntity> entity, const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities)
{
	if (entity->isVisible())
	{
		// Shader uniforms
		_shader.uploadUniform("u_isWireFramed", (entity->isWireFramed() || _renderBus.isWireFrameRenderingEnabled()));
		_shader.uploadUniform("u_positionY", entity->getBasePosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_isBright", entity->isBright());
		_shader.uploadUniform("u_cubeReflectionMixValue", entity->getCubeReflectionMixValue());
		_shader.uploadUniform("u_viewMatrix", (entity->isCameraStatic() ? Matrix44(Matrix33(_renderBus.getViewMatrix())) : _renderBus.getViewMatrix()));
		_shader.uploadUniform("u_minTextureAlpha", MIN_TEXTURE_ALPHA);

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

		// Bind textures
		if (!entity->getPreviousReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionEntities.at(entity->getPreviousReflectionEntityID())->getCubeMap());
		}
		if (!entity->getCurrentReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionEntities.at(entity->getCurrentReflectionEntityID())->getCubeMap());
		}

		// Iterate through parts
		for (const auto& partID : entity->getPartIDs())
		{
			// Temporary values
			const auto buffer = entity->getRenderBuffer(partID);

			// Model matrices
			const auto& transformationMatrix = entity->getTransformationMatrix(partID);
			Matrix33 normalTransformationMatrix = Math::transposeMatrix(Math::invertMatrix(Matrix33(transformationMatrix)));

			// Shader uniforms
			_shader.uploadUniform("u_isReflective", entity->isReflective(partID));
			_shader.uploadUniform("u_emissionIntensity", entity->getEmissionIntensity(partID));
			_shader.uploadUniform("u_textureRepeat", entity->getTextureRepeat(partID));
			_shader.uploadUniform("u_alpha", entity->getAlpha(partID));
			_shader.uploadUniform("u_isSpecular", entity->isSpecular(partID));
			_shader.uploadUniform("u_reflectivity", entity->getReflectivity(partID));
			_shader.uploadUniform("u_lightness", entity->getLightness(partID));
			_shader.uploadUniform("u_specularShininess", entity->getSpecularShininess(partID));
			_shader.uploadUniform("u_specularIntensity", entity->getSpecularIntensity(partID));
			_shader.uploadUniform("u_color", entity->getColor(partID));
			_shader.uploadUniform("u_colorInversion", entity->getColorInversion(partID));
			_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap(partID));
			_shader.uploadUniform("u_hasEmissionMap", entity->hasEmissionMap(partID));
			_shader.uploadUniform("u_hasSpecularMap", entity->hasSpecularMap(partID));
			_shader.uploadUniform("u_hasReflectionMap", entity->hasReflectionMap(partID));
			_shader.uploadUniform("u_hasNormalMap", entity->hasNormalMap(partID));
			_shader.uploadUniform("u_transformationMatrix", transformationMatrix);
			_shader.uploadUniform("u_normalTransformationMatrix", normalTransformationMatrix);
			_shader.uploadUniform("u_isInstanced", buffer->isInstanced());
			_shader.uploadUniform("u_reflectionType", static_cast<int>(entity->getReflectionType(partID)));

			// Bind textures
			if (entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID));
			}
			if (entity->hasEmissionMap(partID))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, entity->getEmissionMap(partID));
			}
			if (entity->hasSpecularMap(partID))
			{
				glActiveTexture(GL_TEXTURE6);
				glBindTexture(GL_TEXTURE_2D, entity->getSpecularMap(partID));
			}
			if (entity->hasReflectionMap(partID))
			{
				glActiveTexture(GL_TEXTURE7);
				glBindTexture(GL_TEXTURE_2D, entity->getReflectionMap(partID));
			}
			if (entity->hasNormalMap(partID))
			{
				glActiveTexture(GL_TEXTURE8);
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

			// Unbind buffer
			glBindVertexArray(0);

			// Unbind textures
			if (entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasEmissionMap(partID))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasSpecularMap(partID))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasReflectionMap(partID))
			{
				glActiveTexture(GL_TEXTURE6);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasNormalMap(partID))
			{
				glActiveTexture(GL_TEXTURE7);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		// Unbind textures
		if (entity->getPreviousReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
		if (entity->getCurrentReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
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