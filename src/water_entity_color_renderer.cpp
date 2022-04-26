#include "water_entity_color_renderer.hpp"
#include "configuration.hpp"

using std::to_string;
using std::min;
using std::max;

void WaterEntityColorRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_cameraView", _camera->getView());
	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shaderBuffer->uploadUniform("u_directionalLightingColor", _renderStorage->getDirectionalLightingColor());
	_shaderBuffer->uploadUniform("u_directionalLightingPosition", _renderStorage->getDirectionalLightingPosition());
	_shaderBuffer->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shaderBuffer->uploadUniform("u_minFogDistance", _renderStorage->getMinFogDistance());
	_shaderBuffer->uploadUniform("u_maxFogDistance", _renderStorage->getMaxFogDistance());
	_shaderBuffer->uploadUniform("u_fogThickness", _renderStorage->getFogThickness());
	_shaderBuffer->uploadUniform("u_fogColor", _renderStorage->getFogColor());
	_shaderBuffer->uploadUniform("u_isFogEnabled", _renderStorage->isFogEnabled());
	_shaderBuffer->uploadUniform("u_cameraNear", _camera->getNear());
	_shaderBuffer->uploadUniform("u_cameraFar", _camera->getFar());
	_shaderBuffer->uploadUniform("u_isDirectionalLightingEnabled", _renderStorage->isDirectionalLightingEnabled());
	_shaderBuffer->uploadUniform("u_directionalLightingIntensity", _renderStorage->getDirectionalLightingIntensity());
	_shaderBuffer->uploadUniform("u_isReflectionsEnabled", _renderStorage->isReflectionsEnabled());
	_shaderBuffer->uploadUniform("u_isRefractionsEnabled", _renderStorage->isRefractionsEnabled());
	_shaderBuffer->uploadUniform("u_reflectionMap", 0);
	_shaderBuffer->uploadUniform("u_refractionMap", 1);
	_shaderBuffer->uploadUniform("u_edgeMap", 2);
	_shaderBuffer->uploadUniform("u_dudvMap", 3);
	_shaderBuffer->uploadUniform("u_normalMap", 4);
	_shaderBuffer->uploadUniform("u_displacementMap", 5);
	_shaderBuffer->uploadUniform("u_hasReflectionMap", (_renderStorage->getWaterReflectionTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasRefractionMap", (_renderStorage->getWaterRefractionTextureBuffer() != nullptr));

	if(_renderStorage->getWaterReflectionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getWaterReflectionTextureBuffer()->getTboId());
	}
	if(_renderStorage->getWaterRefractionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getWaterRefractionTextureBuffer()->getTboId());
	}
	if(_renderStorage->getWaterEdgeTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getWaterEdgeTextureBuffer()->getTboId());
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

	if(_renderStorage->getWaterReflectionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getWaterRefractionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getWaterEdgeTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void WaterEntityColorRenderer::processPointlightEntities(const unordered_map<string, shared_ptr<PointlightEntity>> & entities)
{
	vector<shared_ptr<PointlightEntity>> visibleEntities;
	for(const auto & [entityId, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	for(unsigned int index = 0; index < static_cast<int>(visibleEntities.size()); index++)
	{
		//_shader->uploadUniform("u_pointlightPositions[" + to_string(index) + "]", visibleEntities[index]->getPosition());
		//_shader->uploadUniform("u_pointlightColors[" + to_string(index) + "]", visibleEntities[index]->getColor());
		//_shader->uploadUniform("u_pointlightIntensities[" + to_string(index) + "]", visibleEntities[index]->getIntensity());
		//_shader->uploadUniform("u_pointlightRadiuses[" + to_string(index) + "]", visibleEntities[index]->getRadius());
		//_shader->uploadUniform("u_pointlightShapes[" + to_string(index) + "]", static_cast<int>(visibleEntities[index]->getShape()));
	}

	//_shader->uploadUniform("u_pointlightCount", static_cast<int>(visibleEntities.size()));
}

void WaterEntityColorRenderer::processSpotlightEntities(const unordered_map<string, shared_ptr<SpotlightEntity>> & entities)
{
	vector<shared_ptr<SpotlightEntity>> visibleEntities;
	for(const auto & [entityId, entity] : entities)
	{
		if(entity->isVisible())
		{
			visibleEntities.push_back(entity);
		}
	}

	for(unsigned int index = 0; index < static_cast<int>(visibleEntities.size()); index++)
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

	_shaderBuffer->uploadUniform("u_isWireframed", entity->isWireframed());
	_shaderBuffer->uploadUniform("u_rippleOffset", entity->getRippleOffset());
	_shaderBuffer->uploadUniform("u_waveOffset", entity->getWaveOffset());
	_shaderBuffer->uploadUniform("u_waveHeight", entity->getWaveHeight());
	_shaderBuffer->uploadUniform("u_maxDepth", entity->getMaxDepth());
	_shaderBuffer->uploadUniform("u_height", entity->getHeight());
	_shaderBuffer->uploadUniform("u_textureRepeat", entity->getTextureRepeat());
	_shaderBuffer->uploadUniform("u_specularShininess", entity->getSpecularShininess());
	_shaderBuffer->uploadUniform("u_specularIntensity", entity->getSpecularIntensity());
	_shaderBuffer->uploadUniform("u_isEdged", entity->isEdged());
	_shaderBuffer->uploadUniform("u_isSpecular", entity->isSpecular());
	_shaderBuffer->uploadUniform("u_isReflective", entity->isReflective());
	_shaderBuffer->uploadUniform("u_isRefractive", entity->isRefractive());
	_shaderBuffer->uploadUniform("u_color", entity->getColor());
	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, entity->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, entity->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, entity->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, entity->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, entity->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, entity->getMaxClipPosition().z));
	_shaderBuffer->uploadUniform("u_hasDisplacementMap", (entity->getDisplacementTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasDudvMap", (entity->getDudvTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_hasNormalMap", (entity->getNormalTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_wireframeColor", entity->getWireframeColor());

	if(entity->getDudvTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, entity->getDudvTextureBuffer()->getTboId());
	}
	if(entity->getNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, entity->getNormalTextureBuffer()->getTboId());
	}
	if(entity->getDisplacementTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, entity->getDisplacementTextureBuffer()->getTboId());
	}

	if(entity->getDisplacementTextureBuffer() != nullptr)
	{
		glBindVertexArray(entity->getHighQualityVertexBuffer()->getVaoId());
	}
	else
	{
		glBindVertexArray(entity->getLowQualityVertexBuffer()->getVaoId());
	}

	if(entity->getDisplacementTextureBuffer() != nullptr)
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

	if(entity->getDudvTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getNormalTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(entity->getDisplacementTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(entity->isWireframed())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}