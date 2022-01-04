#include "water_entity_color_renderer.hpp"
#include "configuration.hpp"

using std::to_string;

void WaterEntityColorRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_viewMatrix", renderBus.getViewMatrix());
	shader->uploadUniform("u_projectionMatrix", renderBus.getProjectionMatrix());
	shader->uploadUniform("u_directionalLightingColor", renderBus.getDirectionalLightingColor());
	shader->uploadUniform("u_directionalLightPosition", renderBus.getDirectionalLightingPosition());
	shader->uploadUniform("u_cameraPosition", renderBus.getCameraPosition());
	shader->uploadUniform("u_fogMinDistance", renderBus.getFogMinDistance());
	shader->uploadUniform("u_fogMaxDistance", renderBus.getFogMaxDistance());
	shader->uploadUniform("u_fogThickness", renderBus.getFogThickness());
	shader->uploadUniform("u_fogColor", renderBus.getFogColor());
	shader->uploadUniform("u_isFogEnabled", renderBus.isFogEnabled());
	shader->uploadUniform("u_nearDistance", renderBus.getNearDistance());
	shader->uploadUniform("u_farDistance", renderBus.getFarDistance());
	shader->uploadUniform("u_isDirectionalLightingEnabled", renderBus.isDirectionalLightingEnabled());
	shader->uploadUniform("u_directionalLightingIntensity", renderBus.getDirectionalLightingIntensity());
	shader->uploadUniform("u_reflectionMap", 0);
	shader->uploadUniform("u_refractionMap", 1);
	shader->uploadUniform("u_depthMap", 2);
	shader->uploadUniform("u_dudvMap", 3);
	shader->uploadUniform("u_normalMap", 4);
	shader->uploadUniform("u_displacementMap", 5);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderBus.getWaterReflectionMap()->getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, renderBus.getWaterRefractionMap()->getID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, renderBus.getDepthMap()->getID());

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void WaterEntityColorRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glDisable(GL_BLEND);

	glDisable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->unbind();
}

void WaterEntityColorRenderer::processPointlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<PointlightEntity>>& entities)
{
	vector<shared_ptr<PointlightEntity>> visibleEntities;
	for(const auto& [key, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	unsigned int index = 0;
	for(size_t i = 0; i < visibleEntities.size(); i++)
	{
		//shader->uploadUniform("u_pointlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		//shader->uploadUniform("u_pointlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		//shader->uploadUniform("u_pointlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		//shader->uploadUniform("u_pointlightRadiuses[" + to_string(i) + "]", visibleEntities[i]->getRadius());
		//shader->uploadUniform("u_pointlightShapes[" + to_string(i) + "]", static_cast<int>(visibleEntities[i]->getShape()));
	}

	//shader->uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
}

void WaterEntityColorRenderer::processSpotlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<SpotlightEntity>>& entities)
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
		//shader->uploadUniform("u_spotlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		//shader->uploadUniform("u_spotlightFrontVectors[" + to_string(i) + "]", visibleEntities[i]->getFrontVector());
		//shader->uploadUniform("u_spotlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		//shader->uploadUniform("u_spotlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		//shader->uploadUniform("u_spotlightAngles[" + to_string(i) + "]", cosf(Math::convertToRadians(visibleEntities[i]->getAngle())));
		//shader->uploadUniform("u_spotlightDistances[" + to_string(i) + "]", visibleEntities[i]->getDistance());
	}

	//shader->uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
}

void WaterEntityColorRenderer::render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<WaterEntity> entity)
{
	if(entity->isVisible())
	{
		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		bool isUnderWater = (renderBus.getCameraPosition().y < (entity->getHeight() + entity->getWaveHeight()));
		isUnderWater = isUnderWater && (renderBus.getCameraPosition().x > (entity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (renderBus.getCameraPosition().x < (entity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (renderBus.getCameraPosition().z > (entity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (renderBus.getCameraPosition().z < (entity->getSize() / 2.0f));

		shader->uploadUniform("u_isUnderWater", isUnderWater);
		shader->uploadUniform("u_isWireframed", (entity->isWireframed() || renderBus.isWireframeRenderingEnabled()));
		shader->uploadUniform("u_rippleOffset", entity->getRippleOffset());
		shader->uploadUniform("u_waveOffset", entity->getWaveOffset());
		shader->uploadUniform("u_waveHeight", entity->getWaveHeight());
		shader->uploadUniform("u_height", entity->getHeight());
		shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		shader->uploadUniform("u_specularShininess", entity->getSpecularShininess());
		shader->uploadUniform("u_specularIntensity", entity->getSpecularIntensity());
		shader->uploadUniform("u_transparency", entity->getTransparency());
		shader->uploadUniform("u_isSpecular", entity->isSpecular());
		shader->uploadUniform("u_isReflective", entity->isReflective());
		shader->uploadUniform("u_isRefractive", entity->isRefractive());
		shader->uploadUniform("u_color", entity->getColor());
		shader->uploadUniform("u_hasDisplacementMap", entity->hasDisplacementMap());
		shader->uploadUniform("u_hasDudvMap", entity->hasDudvMap());
		shader->uploadUniform("u_hasNormalMap", entity->hasNormalMap());
		shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());

		if(entity->hasDudvMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, entity->getDudvMap()->getID());
		}
		if(entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMap()->getID());
		}
		if(entity->hasDisplacementMap())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, entity->getDisplacementMap()->getID());
		}

		if(entity->hasDisplacementMap())
		{
			glBindVertexArray(entity->getHighQualityVertexBuffer()->getVaoID());
		}
		else
		{
			glBindVertexArray(entity->getLowQualityVertexBuffer()->getVaoID());
		}

		if(entity->hasDisplacementMap())
		{
			glDrawArrays(GL_TRIANGLES, 0, entity->getHighQualityVertexBuffer()->getVertexCount());
			renderBus.increaseTriangleCount(entity->getHighQualityVertexBuffer()->getVertexCount() / 3);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, entity->getLowQualityVertexBuffer()->getVertexCount());
			renderBus.increaseTriangleCount(entity->getLowQualityVertexBuffer()->getVertexCount() / 3);
		}

		glBindVertexArray(0);

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

		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}