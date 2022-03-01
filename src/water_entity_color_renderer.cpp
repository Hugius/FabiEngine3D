#include "water_entity_color_renderer.hpp"
#include "configuration.hpp"

using std::to_string;
using std::min;
using std::max;

void WaterEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_cameraView", _camera->getView());
	_shader->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shader->uploadUniform("u_directionalLightingColor", _renderStorage->getDirectionalLightingColor());
	_shader->uploadUniform("u_directionalLightingPosition", _renderStorage->getDirectionalLightingPosition());
	_shader->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shader->uploadUniform("u_minFogDistance", _renderStorage->getMinFogDistance());
	_shader->uploadUniform("u_maxFogDistance", _renderStorage->getMaxFogDistance());
	_shader->uploadUniform("u_fogThickness", _renderStorage->getFogThickness());
	_shader->uploadUniform("u_fogColor", _renderStorage->getFogColor());
	_shader->uploadUniform("u_isFogEnabled", _renderStorage->isFogEnabled());
	_shader->uploadUniform("u_cameraNear", _camera->getNear());
	_shader->uploadUniform("u_cameraFar", _camera->getFar());
	_shader->uploadUniform("u_isDirectionalLightingEnabled", _renderStorage->isDirectionalLightingEnabled());
	_shader->uploadUniform("u_directionalLightingIntensity", _renderStorage->getDirectionalLightingIntensity());
	_shader->uploadUniform("u_isReflectionsEnabled", _renderStorage->isReflectionsEnabled());
	_shader->uploadUniform("u_isRefractionsEnabled", _renderStorage->isRefractionsEnabled());
	_shader->uploadUniform("u_reflectionMap", 0);
	_shader->uploadUniform("u_refractionMap", 1);
	_shader->uploadUniform("u_edgeMap", 2);
	_shader->uploadUniform("u_dudvMap", 3);
	_shader->uploadUniform("u_normalMap", 4);
	_shader->uploadUniform("u_displacementMap", 5);
	_shader->uploadUniform("u_hasReflectionMap", (_renderStorage->getWaterReflectionMap() != nullptr));
	_shader->uploadUniform("u_hasRefractionMap", (_renderStorage->getWaterRefractionMap() != nullptr));

	if(_renderStorage->getWaterReflectionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getWaterReflectionMap()->getId());
	}
	if(_renderStorage->getWaterRefractionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getWaterRefractionMap()->getId());
	}
	if(_renderStorage->getWaterEdgeMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getWaterEdgeMap()->getId());
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

	if(_renderStorage->getWaterReflectionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getWaterRefractionMap() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getWaterEdgeMap() != nullptr)
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

	for(unsigned int index = 0; index < visibleEntities.size(); index++)
	{
		//_shader->uploadUniform("u_pointlightPositions[" + to_string(index) + "]", visibleEntities[index]->getPosition());
		//_shader->uploadUniform("u_pointlightColors[" + to_string(index) + "]", visibleEntities[index]->getColor());
		//_shader->uploadUniform("u_pointlightIntensities[" + to_string(index) + "]", visibleEntities[index]->getIntensity());
		//_shader->uploadUniform("u_pointlightRadiuses[" + to_string(index) + "]", visibleEntities[index]->getRadius());
		//_shader->uploadUniform("u_pointlightShapes[" + to_string(index) + "]", static_cast<int>(visibleEntities[index]->getShape()));
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

	for(unsigned int index = 0; index < visibleEntities.size(); index++)
	{
		//_shader->uploadUniform("u_spotlightPositions[" + to_string(index) + "]", visibleEntities[index]->getPosition());
		//_shader->uploadUniform("u_spotlightFronts[" + to_string(index) + "]", visibleEntities[index]->getFront());
		//_shader->uploadUniform("u_spotlightColors[" + to_string(index) + "]", visibleEntities[index]->getColor());
		//_shader->uploadUniform("u_spotlightIntensities[" + to_string(index) + "]", visibleEntities[index]->getIntensity());
		//_shader->uploadUniform("u_spotlightAngles[" + to_string(index) + "]", cosf(Math::convertToRadians(visibleEntities[index]->getAngle())));
		//_shader->uploadUniform("u_spotlightDistances[" + to_string(index) + "]", visibleEntities[index]->getDistance());
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
	_shader->uploadUniform("u_minX", _renderStorage->getMinPosition().x);
	_shader->uploadUniform("u_maxX", _renderStorage->getMaxPosition().x);
	_shader->uploadUniform("u_minY", _renderStorage->getMinPosition().y);
	_shader->uploadUniform("u_maxY", _renderStorage->getMaxPosition().y);
	_shader->uploadUniform("u_minZ", _renderStorage->getMinPosition().z);
	_shader->uploadUniform("u_maxZ", _renderStorage->getMaxPosition().z);
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
		glBindVertexArray(entity->getHighQualityVertexBuffer()->getVaoId());
	}
	else
	{
		glBindVertexArray(entity->getLowQualityVertexBuffer()->getVaoId());
	}

	if(entity->getDisplacementMap() != nullptr)
	{
		glDrawArrays(GL_TRIANGLES, 0, entity->getHighQualityVertexBuffer()->getVertexCount());
		_renderStorage->increaseTriangleCount(entity->getHighQualityVertexBuffer()->getVertexCount() / 3);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, entity->getLowQualityVertexBuffer()->getVertexCount());
		_renderStorage->increaseTriangleCount(entity->getLowQualityVertexBuffer()->getVertexCount() / 3);
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