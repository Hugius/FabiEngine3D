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
	_shader.uploadUniform("u_cameraFront", _renderBus.getCameraFront());
	_shader.uploadUniform("u_ambientLightingColor", _renderBus.getAmbientLightingColor());
	_shader.uploadUniform("u_ambientLightingIntensity", _renderBus.getAmbientLightingIntensity());
	_shader.uploadUniform("u_directionalLightColor", _renderBus.getDirectionalLightingColor());
	_shader.uploadUniform("u_directionalLightPosition", _renderBus.getDirectionalLightingPosition());
	_shader.uploadUniform("u_directionalLightingIntensity", _renderBus.getDirectionalLightingIntensity());
	_shader.uploadUniform("u_spotLightingColor", _renderBus.getSpotLightingColor());
	_shader.uploadUniform("u_spotLightingIntensity", _renderBus.getSpotLightingIntensity());
	_shader.uploadUniform("u_maxSpotLightingDistance", _renderBus.getMaxSpotLightingDistance());
	_shader.uploadUniform("u_maxSpotLightingAngle", cosf(Math::convertToRadians(_renderBus.getMaxSpotLightingAngle())));
	_shader.uploadUniform("u_fogMinDistance", _renderBus.getFogMinDistance());
	_shader.uploadUniform("u_fogMaxDistance", _renderBus.getFogMaxDistance());
	_shader.uploadUniform("u_fogThickness", _renderBus.getFogThickness());
	_shader.uploadUniform("u_fogColor", _renderBus.getFogColor());
	_shader.uploadUniform("u_isFogEnabled", _renderBus.isFogEnabled());
	_shader.uploadUniform("u_isAmbientLightingEnabled", _renderBus.isAmbientLightingEnabled());
	_shader.uploadUniform("u_isDirectionalLightingEnabled", _renderBus.isDirectionalLightingEnabled());
	_shader.uploadUniform("u_isSpotLightingEnabled", _renderBus.isSpotLightingEnabled());
	_shader.uploadUniform("u_isReflectionsEnabled", _renderBus.isReflectionsEnabled());
	_shader.uploadUniform("u_shadowAreaSize", _renderBus.getShadowAreaSize());
	_shader.uploadUniform("u_shadowAreaCenter", _renderBus.getShadowAreaCenter());
	_shader.uploadUniform("u_shadowLightness", _renderBus.getShadowLightness());
	_shader.uploadUniform("u_isShadowsEnabled", _renderBus.isShadowsEnabled());
	_shader.uploadUniform("u_isShadowFrameRenderEnabled", _renderBus.isShadowFrameRenderingEnabled());
	_shader.uploadUniform("u_cubeReflectionMap", 0);
	_shader.uploadUniform("u_planarReflectionMap", 1);
	_shader.uploadUniform("u_shadowMap", 2);
	_shader.uploadUniform("u_diffuseMap", 3);
	_shader.uploadUniform("u_emissionMap", 4);
	_shader.uploadUniform("u_reflectionMap", 5);
	_shader.uploadUniform("u_normalMap", 6);

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
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getPlanarReflectionMap());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getShadowMap());
}

void ModelEntityColorRenderer::unbind()
{
	// Unbind textures
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
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

void ModelEntityColorRenderer::processLightEntities(const unordered_map<string, shared_ptr<LightEntity>>& entities)
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
		_shader.uploadUniform("u_lightPositions[" + to_string(index) + "]", entity->getPosition());
		_shader.uploadUniform("u_lightColors[" + to_string(index) + "]", entity->getColor());
		_shader.uploadUniform("u_lightIntensities[" + to_string(index) + "]", entity->getIntensity());
		_shader.uploadUniform("u_lightRadiuses[" + to_string(index) + "]", entity->getRadius());
		_shader.uploadUniform("u_lightShapes[" + to_string(index) + "]", static_cast<int>(entity->getShape()));

		index++;
	}

	// Upload count
	_shader.uploadUniform("u_lightCount", static_cast<int>(visibleEntities.size()));
}

void ModelEntityColorRenderer::render(const shared_ptr<ModelEntity> entity, const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities)
{
	if (entity->isVisible())
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

		// Choose reflection entity
		string closestReflectionEntityID = "";
		float closestDistance = 0.0f;
		for (const auto& [keyID, reflectionEntity] : reflectionEntities)
		{
			if (reflectionEntity->isVisible())
			{
				auto absoluteDistance = Math::calculateAbsoluteDistance(entity->getPosition(), reflectionEntity->getPosition());
				if ((absoluteDistance < closestDistance) || closestReflectionEntityID.empty())
				{
					closestReflectionEntityID = reflectionEntity->getID();
					closestDistance = absoluteDistance;
				}
			}
		}

		// Shader uniforms
		_shader.uploadUniform("u_specularLightingFactor", entity->getSpecularFactor());
		_shader.uploadUniform("u_specularLightingIntensity", entity->getSpecularIntensity());
		_shader.uploadUniform("u_isWireFramed", (entity->isWireFramed() || _renderBus.isWireFrameRenderingEnabled()));
		_shader.uploadUniform("u_isTransparent", entity->isTransparent());
		_shader.uploadUniform("u_isPlanarReflective", (entity->getReflectionType() == ReflectionType::PLANAR));
		_shader.uploadUniform("u_isCubeReflective", (entity->getReflectionType() == ReflectionType::CUBE));
		_shader.uploadUniform("u_isSpecularLighted", entity->isSpecularLighted());
		_shader.uploadUniform("u_lightness", entity->getLightness());
		_shader.uploadUniform("u_positionY", entity->getPosition().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_alpha", entity->getAlpha());
		_shader.uploadUniform("u_isBright", entity->isBright());
		_shader.uploadUniform("u_uvRepeat", entity->getUvRepeat());
		_shader.uploadUniform("u_viewMatrix", (entity->isCameraStatic() ? Matrix44(Matrix33(_renderBus.getViewMatrix())) : _renderBus.getViewMatrix()));
		_shader.uploadUniform("u_minDiffuseMapAlpha", MIN_DIFFUSE_MAP_ALPHA);

		// Bind reflection map
		glActiveTexture(GL_TEXTURE0);
		if (!closestReflectionEntityID.empty())
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionEntities.at(closestReflectionEntityID)->getCubeMap());
		}
		else
		{
			std::cout << entity->hasReflectionMap() << std::endl;
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

		// Iterate through parts
		for (const auto& partID : entity->getPartIDs())
		{
			// Temporary values
			const auto buffer = entity->getRenderBuffer(partID);

			// Model matrices
			const auto& transformationMatrix = entity->getTransformationMatrix(partID);
			Matrix33 normalTransformationMatrix = Matrix33(transformationMatrix);
			normalTransformationMatrix.invert();
			normalTransformationMatrix.transpose();

			// Shader uniforms
			_shader.uploadUniform("u_color", entity->getColor(partID));
			_shader.uploadUniform("u_inversion", entity->getInversion(partID));
			_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap(partID));
			_shader.uploadUniform("u_hasEmissionMap", entity->hasEmissionMap(partID));
			_shader.uploadUniform("u_hasReflectionMap", entity->hasReflectionMap(partID));
			_shader.uploadUniform("u_hasNormalMap", entity->hasNormalMap(partID));
			_shader.uploadUniform("u_transformationMatrix", transformationMatrix);
			_shader.uploadUniform("u_normalTransformationMatrix", normalTransformationMatrix);
			_shader.uploadUniform("u_isInstanced", buffer->isInstanced());

			// Bind textures
			if (entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID));
			}
			if (entity->hasEmissionMap(partID))
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, entity->getEmissionMap(partID));
			}
			if (entity->hasReflectionMap(partID))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, entity->getReflectionMap(partID));
			}
			if (entity->hasNormalMap(partID))
			{
				glActiveTexture(GL_TEXTURE6);
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
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasEmissionMap(partID))
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasReflectionMap(partID))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if (entity->hasNormalMap(partID))
			{
				glActiveTexture(GL_TEXTURE6);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			// Unbind buffer
			glBindVertexArray(0);
		}

		// Unbind reflection map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

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