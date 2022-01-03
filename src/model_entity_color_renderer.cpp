#include "model_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void ModelEntityColorRenderer::bind()
{
	_shader.bind();

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
	_shader.uploadUniform("u_shadowSize", _renderBus.getShadowSize());
	_shader.uploadUniform("u_shadowCenter", _renderBus.getShadowCenterPosition());
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

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getPlanarReflectionMap()->getTexture());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _renderBus.getShadowMap()->getTexture());
}

void ModelEntityColorRenderer::unbind()
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	_shader.unbind();
}

void ModelEntityColorRenderer::processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>>& entities)
{
	vector<shared_ptr<PointlightEntity>> visibleEntities;
	for(const auto& [key, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	for(size_t i = 0; i < visibleEntities.size(); i++)
	{
		_shader.uploadUniform("u_pointlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		_shader.uploadUniform("u_pointlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader.uploadUniform("u_pointlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader.uploadUniform("u_pointlightRadiuses[" + to_string(i) + "]", visibleEntities[i]->getRadius());
		_shader.uploadUniform("u_pointlightShapes[" + to_string(i) + "]", static_cast<int>(visibleEntities[i]->getShape()));
	}

	_shader.uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
}

void ModelEntityColorRenderer::processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>>& entities)
{
	vector<shared_ptr<SpotlightEntity>> visibleEntities;
	for(const auto& [key, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	for(size_t i = 0; i < visibleEntities.size(); i++)
	{
		_shader.uploadUniform("u_spotlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		_shader.uploadUniform("u_spotlightFrontVectors[" + to_string(i) + "]", visibleEntities[i]->getFrontVector());
		_shader.uploadUniform("u_spotlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader.uploadUniform("u_spotlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader.uploadUniform("u_spotlightAngles[" + to_string(i) + "]", cosf(Math::convertToRadians(visibleEntities[i]->getAngle())));
		_shader.uploadUniform("u_spotlightDistances[" + to_string(i) + "]", visibleEntities[i]->getDistance());
	}

	_shader.uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
}

void ModelEntityColorRenderer::render(const shared_ptr<ModelEntity> entity, const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities)
{
	if(entity->isVisible())
	{
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_isBright", entity->isBright());
		_shader.uploadUniform("u_cubeReflectionMixValue", entity->getCubeReflectionMixValue());
		_shader.uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(_renderBus.getViewMatrix())) : _renderBus.getViewMatrix()));
		_shader.uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		if(entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		if(!entity->getPreviousReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionEntities.at(entity->getPreviousReflectionEntityID())->getCubeMap()->getTexture());
		}
		if(!entity->getCurrentReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionEntities.at(entity->getCurrentReflectionEntityID())->getCubeMap()->getTexture());
		}

		for(const auto& partID : entity->getPartIDs())
		{
			const auto buffer = entity->getVertexBuffer(partID);

			const auto& transformationMatrix = entity->getTransformationMatrix(partID);
			mat33 normalTransformationMatrix = Math::transposeMatrix(Math::invertMatrix(mat33(transformationMatrix)));

			_shader.uploadUniform("u_isReflective", entity->isReflective(partID));
			_shader.uploadUniform("u_emissionIntensity", entity->getEmissionIntensity(partID));
			_shader.uploadUniform("u_textureRepeat", entity->getTextureRepeat(partID));
			_shader.uploadUniform("u_transparency", entity->getTransparency(partID));
			_shader.uploadUniform("u_isSpecular", entity->isSpecular(partID));
			_shader.uploadUniform("u_reflectivity", entity->getReflectivity(partID));
			_shader.uploadUniform("u_lightness", entity->getLightness(partID));
			_shader.uploadUniform("u_specularShininess", entity->getSpecularShininess(partID));
			_shader.uploadUniform("u_specularIntensity", entity->getSpecularIntensity(partID));
			_shader.uploadUniform("u_color", entity->getColor(partID));
			_shader.uploadUniform("u_wireframeColor", entity->getWireframeColor(partID));
			_shader.uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap(partID));
			_shader.uploadUniform("u_hasEmissionMap", entity->hasEmissionMap(partID));
			_shader.uploadUniform("u_hasSpecularMap", entity->hasSpecularMap(partID));
			_shader.uploadUniform("u_hasReflectionMap", entity->hasReflectionMap(partID));
			_shader.uploadUniform("u_hasNormalMap", entity->hasNormalMap(partID));
			_shader.uploadUniform("u_transformationMatrix", transformationMatrix);
			_shader.uploadUniform("u_normalTransformationMatrix", normalTransformationMatrix);
			_shader.uploadUniform("u_reflectionType", static_cast<int>(entity->getReflectionType(partID)));
			_shader.uploadUniform("u_isWireframed", (entity->isWireframed(partID) || _renderBus.isWireframeRenderingEnabled()));

			if(entity->isWireframed(partID))
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}

			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID)->getTexture());
			}
			if(entity->hasEmissionMap(partID))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, entity->getEmissionMap(partID)->getTexture());
			}
			if(entity->hasSpecularMap(partID))
			{
				glActiveTexture(GL_TEXTURE6);
				glBindTexture(GL_TEXTURE_2D, entity->getSpecularMap(partID)->getTexture());
			}
			if(entity->hasReflectionMap(partID))
			{
				glActiveTexture(GL_TEXTURE7);
				glBindTexture(GL_TEXTURE_2D, entity->getReflectionMap(partID)->getTexture());
			}
			if(entity->hasNormalMap(partID))
			{
				glActiveTexture(GL_TEXTURE8);
				glBindTexture(GL_TEXTURE_2D, entity->getNormalMap(partID)->getTexture());
			}

			glBindVertexArray(buffer->getVAO());

			glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
			_renderBus.increaseTriangleCount(buffer->getVertexCount() / 3);

			glBindVertexArray(0);

			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if(entity->hasEmissionMap(partID))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if(entity->hasSpecularMap(partID))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if(entity->hasReflectionMap(partID))
			{
				glActiveTexture(GL_TEXTURE6);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if(entity->hasNormalMap(partID))
			{
				glActiveTexture(GL_TEXTURE7);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if(entity->isWireframed(partID))
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}

		if(entity->getPreviousReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
		if(entity->getCurrentReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

		if(entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}