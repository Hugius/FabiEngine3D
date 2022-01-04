#include "terrain_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;

void TerrainEntityColorRenderer::bind(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus)
{
	shader->bind();

	shader->uploadUniform("u_viewMatrix", renderBus.getViewMatrix());
	shader->uploadUniform("u_projectionMatrix", renderBus.getProjectionMatrix());
	shader->uploadUniform("u_shadowMatrix", renderBus.getShadowMatrix());
	shader->uploadUniform("u_clippingPlane", renderBus.getClippingPlane());
	shader->uploadUniform("u_cameraPosition", renderBus.getCameraPosition());
	shader->uploadUniform("u_ambientLightingColor", renderBus.getAmbientLightingColor());
	shader->uploadUniform("u_ambientLightingIntensity", renderBus.getAmbientLightingIntensity());
	shader->uploadUniform("u_directionalLightingColor", renderBus.getDirectionalLightingColor());
	shader->uploadUniform("u_directionalLightPosition", renderBus.getDirectionalLightingPosition());
	shader->uploadUniform("u_directionalLightingIntensity", renderBus.getDirectionalLightingIntensity());
	shader->uploadUniform("u_fogMinDistance", renderBus.getFogMinDistance());
	shader->uploadUniform("u_fogMaxDistance", renderBus.getFogMaxDistance());
	shader->uploadUniform("u_fogThickness", renderBus.getFogThickness());
	shader->uploadUniform("u_fogColor", renderBus.getFogColor());
	shader->uploadUniform("u_isFogEnabled", renderBus.isFogEnabled());
	shader->uploadUniform("u_isAmbientLightingEnabled", renderBus.isAmbientLightingEnabled());
	shader->uploadUniform("u_isDirectionalLightingEnabled", renderBus.isDirectionalLightingEnabled());
	shader->uploadUniform("u_shadowSize", renderBus.getShadowSize());
	shader->uploadUniform("u_shadowCenter", renderBus.getShadowCenterPosition());
	shader->uploadUniform("u_shadowLightness", renderBus.getShadowLightness());
	shader->uploadUniform("u_isShadowsEnabled", renderBus.isShadowsEnabled());
	shader->uploadUniform("u_isShadowFrameRenderEnabled", renderBus.isShadowFrameRenderingEnabled());
	shader->uploadUniform("u_shadowMap", 0);
	shader->uploadUniform("u_diffuseMap", 1);
	shader->uploadUniform("u_normalMap", 2);
	shader->uploadUniform("u_blendMap", 3);
	shader->uploadUniform("u_redDiffuseMap", 4);
	shader->uploadUniform("u_greenDiffuseMap", 5);
	shader->uploadUniform("u_blueDiffuseMap", 6);
	shader->uploadUniform("u_redNormalMap", 7);
	shader->uploadUniform("u_greenNormalMap", 8);
	shader->uploadUniform("u_blueNormalMap", 9);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderBus.getShadowMap()->getID());

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void TerrainEntityColorRenderer::unbind(shared_ptr<ShaderBuffer> shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_DEPTH_TEST);

	shader->unbind();
}

void TerrainEntityColorRenderer::processPointlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<PointlightEntity>>& entities)
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

void TerrainEntityColorRenderer::processSpotlightEntities(shared_ptr<ShaderBuffer> shader, const unordered_map<string, shared_ptr<SpotlightEntity>>& entities)
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

void TerrainEntityColorRenderer::render(shared_ptr<ShaderBuffer> shader, RenderBus& renderBus, const shared_ptr<TerrainEntity> entity)
{
	if(entity->isVisible())
	{
		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		glEnable(GL_CULL_FACE);

		shader->uploadUniform("u_isWireframed", (entity->isWireframed() || renderBus.isWireframeRenderingEnabled()));
		shader->uploadUniform("u_isSpecular", entity->isSpecular());
		shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
		shader->uploadUniform("u_redTextureRepeat", entity->getRedTextureRepeat());
		shader->uploadUniform("u_greenTextureRepeat", entity->getGreenTextureRepeat());
		shader->uploadUniform("u_blueTextureRepeat", entity->getBlueTextureRepeat());
		shader->uploadUniform("u_lightness", entity->getLightness());
		shader->uploadUniform("u_specularShininess", entity->getSpecularShininess());
		shader->uploadUniform("u_specularIntensity", entity->getSpecularIntensity());
		shader->uploadUniform("u_hasDiffuseMap", entity->hasDiffuseMap());
		shader->uploadUniform("u_hasNormalMap", entity->hasNormalMap());
		shader->uploadUniform("u_hasBlendMap", entity->hasBlendMap());
		shader->uploadUniform("u_hasRedDiffuseMap", entity->hasRedDiffuseMap());
		shader->uploadUniform("u_hasGreenDiffuseMap", entity->hasGreenDiffuseMap());
		shader->uploadUniform("u_hasBlueDiffuseMap", entity->hasBlueDiffuseMap());
		shader->uploadUniform("u_hasRedNormalMap", entity->hasRedNormalMap());
		shader->uploadUniform("u_hasGreenNormalMap", entity->hasGreenNormalMap());
		shader->uploadUniform("u_hasBlueNormalMap", entity->hasBlueNormalMap());
		shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap()->getID());
		}
		if(entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalMap()->getID());
		}
		if(entity->hasBlendMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, entity->getBlendMap()->getID());
		}
		if(entity->hasRedDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getRedDiffuseMap()->getID());
		}
		if(entity->hasGreenDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, entity->getGreenDiffuseMap()->getID());
		}
		if(entity->hasBlueDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, entity->getBlueDiffuseMap()->getID());
		}
		if(entity->hasRedNormalMap())
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, entity->getRedNormalMap()->getID());
		}
		if(entity->hasGreenNormalMap())
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, entity->getGreenNormalMap()->getID());
		}
		if(entity->hasBlueNormalMap())
		{
			glActiveTexture(GL_TEXTURE9);
			glBindTexture(GL_TEXTURE_2D, entity->getBlueNormalMap()->getID());
		}

		glBindVertexArray(entity->getMesh()->getVaoID());

		glDrawArrays(GL_TRIANGLES, 0, entity->getMesh()->getVertexCount());
		renderBus.increaseTriangleCount(entity->getMesh()->getVertexCount() / 3);

		glBindVertexArray(0);

		if(entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasNormalMap())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasBlendMap())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasRedDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasGreenDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasBlueDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasRedNormalMap())
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasGreenNormalMap())
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->hasBlueNormalMap())
		{
			glActiveTexture(GL_TEXTURE9);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glDisable(GL_CULL_FACE);

		if(entity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}