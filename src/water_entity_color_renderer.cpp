#include "water_entity_color_renderer.hpp"
#include "configuration.hpp"

using std::to_string;
using std::min;
using std::max;

void WaterEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_cameraView", _renderBus->getCameraView());
	_shader->uploadUniform("u_cameraProjection", _renderBus->getCameraProjection());
	_shader->uploadUniform("u_directionalLightingColor", _renderBus->getDirectionalLightingColor());
	_shader->uploadUniform("u_directionalLightingPosition", _renderBus->getDirectionalLightingPosition());
	_shader->uploadUniform("u_cameraPosition", _renderBus->getCameraPosition());
	_shader->uploadUniform("u_minFogDistance", _renderBus->getMinFogDistance());
	_shader->uploadUniform("u_maxFogDistance", _renderBus->getMaxFogDistance());
	_shader->uploadUniform("u_fogThickness", _renderBus->getFogThickness());
	_shader->uploadUniform("u_fogColor", _renderBus->getFogColor());
	_shader->uploadUniform("u_isFogEnabled", _renderBus->isFogEnabled());
	_shader->uploadUniform("u_cameraNear", _renderBus->getCameraNear());
	_shader->uploadUniform("u_cameraFar", _renderBus->getCameraFar());
	_shader->uploadUniform("u_isDirectionalLightingEnabled", _renderBus->isDirectionalLightingEnabled());
	_shader->uploadUniform("u_directionalLightingIntensity", _renderBus->getDirectionalLightingIntensity());
	_shader->uploadUniform("u_isReflectionsEnabled", _renderBus->isReflectionsEnabled());
	_shader->uploadUniform("u_isRefractionsEnabled", _renderBus->isRefractionsEnabled());
	_shader->uploadUniform("u_reflectionMap", 0);
	_shader->uploadUniform("u_refractionMap", 1);
	_shader->uploadUniform("u_edgeMap", 2);
	_shader->uploadUniform("u_dudvMap", 3);
	_shader->uploadUniform("u_normalMap", 4);
	_shader->uploadUniform("u_displacementMap", 5);
	_shader->uploadUniform("u_hasReflectionMap", (_renderBus->getWaterReflectionMap() != nullptr));
	_shader->uploadUniform("u_hasRefractionMap", (_renderBus->getWaterRefractionMap() != nullptr));

	if(_renderBus->getWaterReflectionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getWaterReflectionMap()->getId());
	}
	if(_renderBus->getWaterRefractionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getWaterRefractionMap()->getId());
	}
	if(_renderBus->getWaterEdgeMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderBus->getWaterEdgeMap()->getId());
	}

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void WaterEntityColorRenderer::unbind()
{
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);
	glDisable(GL_CLIP_DISTANCE4);
	glDisable(GL_CLIP_DISTANCE5);

	if(_renderBus->getWaterReflectionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderBus->getWaterRefractionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderBus->getWaterEdgeMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shader->unbind();
}

void WaterEntityColorRenderer::processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>>& entities)
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
		//_shader->uploadUniform("u_pointlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		//_shader->uploadUniform("u_pointlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		//_shader->uploadUniform("u_pointlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		//_shader->uploadUniform("u_pointlightRadiuses[" + to_string(i) + "]", visibleEntities[i]->getRadius());
		//_shader->uploadUniform("u_pointlightShapes[" + to_string(i) + "]", static_cast<int>(visibleEntities[i]->getShape()));
	}

	//_shader->uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
}

void WaterEntityColorRenderer::processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>>& entities)
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
		//_shader->uploadUniform("u_spotlightPositions[" + to_string(i) + "]", visibleEntities[i]->getPosition());
		//_shader->uploadUniform("u_spotlightFronts[" + to_string(i) + "]", visibleEntities[i]->getFront());
		//_shader->uploadUniform("u_spotlightColors[" + to_string(i) + "]", visibleEntities[i]->getColor());
		//_shader->uploadUniform("u_spotlightIntensities[" + to_string(i) + "]", visibleEntities[i]->getIntensity());
		//_shader->uploadUniform("u_spotlightAngles[" + to_string(i) + "]", cosf(Math::convertToRadians(visibleEntities[i]->getAngle())));
		//_shader->uploadUniform("u_spotlightDistances[" + to_string(i) + "]", visibleEntities[i]->getDistance());
	}

	//_shader->uploadUniform("u_spotlightCount", static_cast<int>(visibleEntities.size()));
}

void WaterEntityColorRenderer::render(const shared_ptr<WaterEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	_shader->uploadUniform("u_isWireframed", entity->isWireframed());
	_shader->uploadUniform("u_rippleOffset", entity->getRippleOffset());
	_shader->uploadUniform("u_waveOffset", entity->getWaveOffset());
	_shader->uploadUniform("u_waveHeight", entity->getWaveHeight());
	_shader->uploadUniform("u_maxDepth", entity->getMaxDepth());
	_shader->uploadUniform("u_height", entity->getHeight());
	_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
	_shader->uploadUniform("u_specularShininess", entity->getSpecularShininess());
	_shader->uploadUniform("u_specularIntensity", entity->getSpecularIntensity());
	_shader->uploadUniform("u_isEdged", entity->isEdged());
	_shader->uploadUniform("u_isSpecular", entity->isSpecular());
	_shader->uploadUniform("u_isReflective", entity->isReflective());
	_shader->uploadUniform("u_isRefractive", entity->isRefractive());
	_shader->uploadUniform("u_color", entity->getColor());
	_shader->uploadUniform("u_minX", _renderBus->getMinPosition().x);
	_shader->uploadUniform("u_maxX", _renderBus->getMaxPosition().x);
	_shader->uploadUniform("u_minY", _renderBus->getMinPosition().y);
	_shader->uploadUniform("u_maxY", _renderBus->getMaxPosition().y);
	_shader->uploadUniform("u_minZ", _renderBus->getMinPosition().z);
	_shader->uploadUniform("u_maxZ", _renderBus->getMaxPosition().z);
	_shader->uploadUniform("u_hasDisplacementMap", (entity->getDisplacementMap() != nullptr));
	_shader->uploadUniform("u_hasDudvMap", (entity->getDudvMap() != nullptr));
	_shader->uploadUniform("u_hasNormalMap", (entity->getNormalMap() != nullptr));
	_shader->uploadUniform("u_wireframeColor", entity->getWireframeColor());

	if(entity->getDudvMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, entity->getDudvMap()->getId());
	}
	if(entity->getNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalMap()->getId());
	}
	if(entity->getDisplacementMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, entity->getDisplacementMap()->getId());
	}

	if(entity->getDisplacementMap() != nullptr)
	{
		glBindVertexArray(entity->getHighQualityMesh()->getVaoId());
	}
	else
	{
		glBindVertexArray(entity->getLowQualityMesh()->getVaoId());
	}

	if(entity->getDisplacementMap() != nullptr)
	{
		glDrawArrays(GL_TRIANGLES, 0, entity->getHighQualityMesh()->getVertexCount());
		_renderBus->increaseTriangleCount(entity->getHighQualityMesh()->getVertexCount() / 3);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, entity->getLowQualityMesh()->getVertexCount());
		_renderBus->increaseTriangleCount(entity->getLowQualityMesh()->getVertexCount() / 3);
	}

	glBindVertexArray(0);

	if(entity->getDudvMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getNormalMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getDisplacementMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}