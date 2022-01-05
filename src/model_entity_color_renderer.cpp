#include "model_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void ModelEntityColorRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_projectionMatrix", renderBus->getProjectionMatrix());
	shader->uploadUniform("u_shadowMatrix", renderBus->getShadowMatrix());
	shader->uploadUniform("u_clippingPlane", renderBus->getClippingPlane());
	shader->uploadUniform("u_cameraPosition", renderBus->getCameraPosition());
	shader->uploadUniform("u_ambientLightingColor", renderBus->getAmbientLightingColor());
	shader->uploadUniform("u_ambientLightingIntensity", renderBus->getAmbientLightingIntensity());
	shader->uploadUniform("u_directionalLightingColor", renderBus->getDirectionalLightingColor());
	shader->uploadUniform("u_directionalLightPosition", renderBus->getDirectionalLightingPosition());
	shader->uploadUniform("u_directionalLightingIntensity", renderBus->getDirectionalLightingIntensity());
	shader->uploadUniform("u_fogMinDistance", renderBus->getFogMinDistance());
	shader->uploadUniform("u_fogMaxDistance", renderBus->getFogMaxDistance());
	shader->uploadUniform("u_fogThickness", renderBus->getFogThickness());
	shader->uploadUniform("u_fogColor", renderBus->getFogColor());
	shader->uploadUniform("u_isFogEnabled", renderBus->isFogEnabled());
	shader->uploadUniform("u_isAmbientLightingEnabled", renderBus->isAmbientLightingEnabled());
	shader->uploadUniform("u_isDirectionalLightingEnabled", renderBus->isDirectionalLightingEnabled());
	shader->uploadUniform("u_isReflectionsEnabled", renderBus->isReflectionsEnabled());
	shader->uploadUniform("u_shadowSize", renderBus->getShadowSize());
	shader->uploadUniform("u_shadowCenter", renderBus->getShadowCenterPosition());
	shader->uploadUniform("u_shadowLightness", renderBus->getShadowLightness());
	shader->uploadUniform("u_isShadowsEnabled", renderBus->isShadowsEnabled());
	shader->uploadUniform("u_isShadowFrameRenderEnabled", renderBus->isShadowFrameRenderingEnabled());
	shader->uploadUniform("u_previousCubeReflectionMap", 0);
	shader->uploadUniform("u_currentCubeReflectionMap", 1);
	shader->uploadUniform("u_planarReflectionMap", 2);
	shader->uploadUniform("u_shadowMap", 3);
	shader->uploadUniform("u_diffuseMap", 4);
	shader->uploadUniform("u_emissionMap", 5);
	shader->uploadUniform("u_specularMap", 6);
	shader->uploadUniform("u_reflectionMap", 7);
	shader->uploadUniform("u_normalMap", 8);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, renderBus->getPlanarReflectionMap()->getID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, renderBus->getShadowMap()->getID());
}

void ModelEntityColorRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	shader->unbind();
}

void ModelEntityColorRenderer::processPointlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<PointlightEntity>>& entities)
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
		shader->uploadUniform("u_pointlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		shader->uploadUniform("u_pointlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		shader->uploadUniform("u_pointlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		shader->uploadUniform("u_pointlightRadiuses[" + to_string(i) + "]", visibleEntities[i]->getRadius());
		shader->uploadUniform("u_pointlightShapes[" + to_string(i) + "]", static_cast<int>(visibleEntities[i]->getShape()));
	}

	shader->uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
}

void ModelEntityColorRenderer::processSpotlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<SpotlightEntity>>& entities)
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
		shader->uploadUniform("u_spotlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		shader->uploadUniform("u_spotlightFrontVectors[" + to_string(i) + "]", visibleEntities[i]->getFrontVector());
		shader->uploadUniform("u_spotlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		shader->uploadUniform("u_spotlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		shader->uploadUniform("u_spotlightAngles[" + to_string(i) + "]", cosf(Math::convertToRadians(visibleEntities[i]->getAngle())));
		shader->uploadUniform("u_spotlightDistances[" + to_string(i) + "]", visibleEntities[i]->getDistance());
	}

	shader->uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
}

void ModelEntityColorRenderer::render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<ModelEntity> entity,
									  const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities)
{
	if(entity->isVisible())
	{
		shader->uploadUniform("u_minHeight", entity->getMinHeight());
		shader->uploadUniform("u_maxHeight", entity->getMaxHeight());
		shader->uploadUniform("u_isBright", entity->isBright());
		shader->uploadUniform("u_cubeReflectionMixValue", entity->getCubeReflectionMixValue());
		shader->uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(renderBus->getViewMatrix())) : renderBus->getViewMatrix()));
		shader->uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		if(entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		if(!entity->getPreviousReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionEntities.at(entity->getPreviousReflectionEntityID())->getCubeMap()->getID());
		}
		if(!entity->getCurrentReflectionEntityID().empty())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionEntities.at(entity->getCurrentReflectionEntityID())->getCubeMap()->getID());
		}

		for(const auto& partID : entity->getPartIDs())
		{
			const auto buffer = entity->getMesh(partID);

			const auto& transformationMatrix = entity->getTransformationMatrix(partID);
			mat33 normalTransformationMatrix = Math::transposeMatrix(Math::invertMatrix(mat33(transformationMatrix)));

			shader->uploadUniform("u_isReflective", entity->isReflective(partID));
			shader->uploadUniform("u_emissionIntensity", entity->getEmissionIntensity(partID));
			shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat(partID));
			shader->uploadUniform("u_transparency", entity->getTransparency(partID));
			shader->uploadUniform("u_isSpecular", entity->isSpecular(partID));
			shader->uploadUniform("u_reflectivity", entity->getReflectivity(partID));
			shader->uploadUniform("u_lightness", entity->getLightness(partID));
			shader->uploadUniform("u_specularShininess", entity->getSpecularShininess(partID));
			shader->uploadUniform("u_specularIntensity", entity->getSpecularIntensity(partID));
			shader->uploadUniform("u_color", entity->getColor(partID));
			shader->uploadUniform("u_wireframeColor", entity->getWireframeColor(partID));
			shader->uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap(partID));
			shader->uploadUniform("u_hasEmissionMap", entity->hasEmissionMap(partID));
			shader->uploadUniform("u_hasSpecularMap", entity->hasSpecularMap(partID));
			shader->uploadUniform("u_hasReflectionMap", entity->hasReflectionMap(partID));
			shader->uploadUniform("u_hasNormalMap", entity->hasNormalMap(partID));
			shader->uploadUniform("u_transformationMatrix", transformationMatrix);
			shader->uploadUniform("u_normalTransformationMatrix", normalTransformationMatrix);
			shader->uploadUniform("u_reflectionType", static_cast<int>(entity->getReflectionType(partID)));
			shader->uploadUniform("u_isWireframed", (entity->isWireframed(partID) || renderBus->isWireframeRenderingEnabled()));

			if(entity->isWireframed(partID))
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}

			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID)->getID());
			}
			if(entity->hasEmissionMap(partID))
			{
				glActiveTexture(GL_TEXTURE5);
				glBindTexture(GL_TEXTURE_2D, entity->getEmissionMap(partID)->getID());
			}
			if(entity->hasSpecularMap(partID))
			{
				glActiveTexture(GL_TEXTURE6);
				glBindTexture(GL_TEXTURE_2D, entity->getSpecularMap(partID)->getID());
			}
			if(entity->hasReflectionMap(partID))
			{
				glActiveTexture(GL_TEXTURE7);
				glBindTexture(GL_TEXTURE_2D, entity->getReflectionMap(partID)->getID());
			}
			if(entity->hasNormalMap(partID))
			{
				glActiveTexture(GL_TEXTURE8);
				glBindTexture(GL_TEXTURE_2D, entity->getNormalMap(partID)->getID());
			}

			glBindVertexArray(buffer->getVaoID());

			glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
			renderBus->increaseTriangleCount(buffer->getVertexCount() / 3);

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