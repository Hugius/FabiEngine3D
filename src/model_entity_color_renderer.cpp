#include "model_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void ModelEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_projectionMatrix", _renderBus->getProjectionMatrix());
	_shader->uploadUniform("u_shadowMatrix", _renderBus->getShadowMatrix());
	_shader->uploadUniform("u_clippingPlane", _renderBus->getClippingPlane());
	_shader->uploadUniform("u_cameraPosition", _renderBus->getCameraPosition());
	_shader->uploadUniform("u_ambientLightingColor", _renderBus->getAmbientLightingColor());
	_shader->uploadUniform("u_ambientLightingIntensity", _renderBus->getAmbientLightingIntensity());
	_shader->uploadUniform("u_directionalLightingColor", _renderBus->getDirectionalLightingColor());
	_shader->uploadUniform("u_directionalLightPosition", _renderBus->getDirectionalLightingPosition());
	_shader->uploadUniform("u_directionalLightingIntensity", _renderBus->getDirectionalLightingIntensity());
	_shader->uploadUniform("u_fogMinDistance", _renderBus->getFogMinDistance());
	_shader->uploadUniform("u_fogMaxDistance", _renderBus->getFogMaxDistance());
	_shader->uploadUniform("u_fogThickness", _renderBus->getFogThickness());
	_shader->uploadUniform("u_fogColor", _renderBus->getFogColor());
	_shader->uploadUniform("u_isFogEnabled", _renderBus->isFogEnabled());
	_shader->uploadUniform("u_isAmbientLightingEnabled", _renderBus->isAmbientLightingEnabled());
	_shader->uploadUniform("u_isDirectionalLightingEnabled", _renderBus->isDirectionalLightingEnabled());
	_shader->uploadUniform("u_isReflectionsEnabled", _renderBus->isReflectionsEnabled());
	_shader->uploadUniform("u_shadowSize", _renderBus->getShadowSize());
	_shader->uploadUniform("u_shadowCenter", _renderBus->getShadowCenterPosition());
	_shader->uploadUniform("u_shadowLightness", _renderBus->getShadowLightness());
	_shader->uploadUniform("u_isShadowsEnabled", _renderBus->isShadowsEnabled());
	_shader->uploadUniform("u_isShadowFrameRenderEnabled", _renderBus->isShadowFrameRenderingEnabled());
	_shader->uploadUniform("u_previousCubeReflectionMap", 0);
	_shader->uploadUniform("u_currentCubeReflectionMap", 1);
	_shader->uploadUniform("u_planarReflectionMap", 2);
	_shader->uploadUniform("u_shadowMap", 3);
	_shader->uploadUniform("u_diffuseMap", 4);
	_shader->uploadUniform("u_emissionMap", 5);
	_shader->uploadUniform("u_specularMap", 6);
	_shader->uploadUniform("u_reflectionMap", 7);
	_shader->uploadUniform("u_normalMap", 8);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if(_renderBus->getPlanarReflectionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getPlanarReflectionMap()->getId());
	}
	if(_renderBus->getShadowMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getShadowMap()->getId());
	}
}

void ModelEntityColorRenderer::unbind()
{
	if(_renderBus->getPlanarReflectionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderBus->getShadowMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glDisable(GL_BLEND);

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	_shader->unbind();
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
		_shader->uploadUniform("u_pointlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		_shader->uploadUniform("u_pointlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader->uploadUniform("u_pointlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader->uploadUniform("u_pointlightRadiuses[" + to_string(i) + "]", visibleEntities[i]->getRadius());
		_shader->uploadUniform("u_pointlightShapes[" + to_string(i) + "]", static_cast<int>(visibleEntities[i]->getShape()));
	}

	_shader->uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
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
		_shader->uploadUniform("u_spotlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		_shader->uploadUniform("u_spotlightFrontVectors[" + to_string(i) + "]", visibleEntities[i]->getFrontVector());
		_shader->uploadUniform("u_spotlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		_shader->uploadUniform("u_spotlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		_shader->uploadUniform("u_spotlightAngles[" + to_string(i) + "]", cosf(Math::convertToRadians(visibleEntities[i]->getAngle())));
		_shader->uploadUniform("u_spotlightDistances[" + to_string(i) + "]", visibleEntities[i]->getDistance());
	}

	_shader->uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
}

void ModelEntityColorRenderer::render(const shared_ptr<ModelEntity> entity, const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities)
{
	if(entity->isVisible())
	{
		_shader->uploadUniform("u_minHeight", entity->getMinHeight());
		_shader->uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader->uploadUniform("u_cubeReflectionMixValue", entity->getCubeReflectionMixValue());
		_shader->uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(_renderBus->getViewMatrix())) : _renderBus->getViewMatrix()));
		_shader->uploadUniform("u_minTextureOpacity", MIN_TEXTURE_OPACITY);

		if(!entity->getPreviousReflectionEntityId().empty())
		{
			const auto reflectionEntity = reflectionEntities.at(entity->getPreviousReflectionEntityId());

			if(reflectionEntity->getCubeMap() != nullptr)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionEntity->getCubeMap()->getId());
			}
		}
		if(!entity->getCurrentReflectionEntityId().empty())
		{
			const auto reflectionEntity = reflectionEntities.at(entity->getCurrentReflectionEntityId());

			if(reflectionEntity->getCubeMap() != nullptr)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionEntity->getCubeMap()->getId());
			}
		}

		for(const auto& partId : entity->getPartIds())
		{
			_shader->uploadUniform("u_isReflective", entity->isReflective(partId));
			_shader->uploadUniform("u_emissionIntensity", entity->getEmissionIntensity(partId));
			_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat(partId));
			_shader->uploadUniform("u_opacity", entity->getOpacity(partId));
			_shader->uploadUniform("u_isSpecular", entity->isSpecular(partId));
			_shader->uploadUniform("u_reflectivity", entity->getReflectivity(partId));
			_shader->uploadUniform("u_lightness", entity->getLightness(partId));
			_shader->uploadUniform("u_specularShininess", entity->getSpecularShininess(partId));
			_shader->uploadUniform("u_specularIntensity", entity->getSpecularIntensity(partId));
			_shader->uploadUniform("u_color", entity->getColor(partId));
			_shader->uploadUniform("u_wireframeColor", entity->getWireframeColor(partId));
			_shader->uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap(partId));
			_shader->uploadUniform("u_hasEmissionMap", entity->hasEmissionMap(partId));
			_shader->uploadUniform("u_hasSpecularMap", entity->hasSpecularMap(partId));
			_shader->uploadUniform("u_hasReflectionMap", entity->hasReflectionMap(partId));
			_shader->uploadUniform("u_hasNormalMap", entity->hasNormalMap(partId));
			_shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix(partId));
			_shader->uploadUniform("u_normalTransformationMatrix", Math::transposeMatrix(Math::invertMatrix(mat33(entity->getTransformationMatrix(partId)))));
			_shader->uploadUniform("u_reflectionType", static_cast<int>(entity->getReflectionType(partId)));
			_shader->uploadUniform("u_isWireframed", (entity->isWireframed(partId) || _renderBus->isWireframeRenderingEnabled()));
			_shader->uploadUniform("u_isBright", entity->isBright(partId));

			if(entity->isFaceCulled(partId))
			{
				glEnable(GL_CULL_FACE);
			}

			if(entity->isWireframed(partId))
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}

			if(entity->hasDiffuseMap(partId))
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partId)->getId());
			}
			if(entity->hasEmissionMap(partId))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, entity->getEmissionMap(partId)->getId());
			}
			if(entity->hasSpecularMap(partId))
			{
				glActiveTexture(GL_TEXTURE6);
				glBindTexture(GL_TEXTURE_2D, entity->getSpecularMap(partId)->getId());
			}
			if(entity->hasReflectionMap(partId))
			{
				glActiveTexture(GL_TEXTURE7);
				glBindTexture(GL_TEXTURE_2D, entity->getReflectionMap(partId)->getId());
			}
			if(entity->hasNormalMap(partId))
			{
				glActiveTexture(GL_TEXTURE8);
				glBindTexture(GL_TEXTURE_2D, entity->getNormalMap(partId)->getId());
			}

			glBindVertexArray(entity->getMesh(partId)->getVaoId());

			glDrawArrays(GL_TRIANGLES, 0, entity->getMesh(partId)->getVertexCount());
			_renderBus->increaseTriangleCount(entity->getMesh(partId)->getVertexCount() / 3);

			glBindVertexArray(0);

			if(entity->hasDiffuseMap(partId))
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if(entity->hasEmissionMap(partId))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if(entity->hasSpecularMap(partId))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if(entity->hasReflectionMap(partId))
			{
				glActiveTexture(GL_TEXTURE6);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			if(entity->hasNormalMap(partId))
			{
				glActiveTexture(GL_TEXTURE7);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if(entity->isWireframed(partId))
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			if(entity->isFaceCulled(partId))
			{
				glDisable(GL_CULL_FACE);
			}
		}

		if(entity->getPreviousReflectionEntityId().empty())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
		if(entity->getCurrentReflectionEntityId().empty())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
	}
}