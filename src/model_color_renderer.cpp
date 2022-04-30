#include "model_color_renderer.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using std::to_string;
using std::min;
using std::max;

void ModelColorRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shaderBuffer->uploadUniform("u_shadowView", _renderStorage->getShadowView());
	_shaderBuffer->uploadUniform("u_shadowProjection", _renderStorage->getShadowProjection());
	_shaderBuffer->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shaderBuffer->uploadUniform("u_ambientLightingColor", _renderStorage->getAmbientLightingColor());
	_shaderBuffer->uploadUniform("u_ambientLightingIntensity", _renderStorage->getAmbientLightingIntensity());
	_shaderBuffer->uploadUniform("u_directionalLightingColor", _renderStorage->getDirectionalLightingColor());
	_shaderBuffer->uploadUniform("u_directionalLightingPosition", _renderStorage->getDirectionalLightingPosition());
	_shaderBuffer->uploadUniform("u_directionalLightingIntensity", _renderStorage->getDirectionalLightingIntensity());
	_shaderBuffer->uploadUniform("u_minFogDistance", _renderStorage->getMinFogDistance());
	_shaderBuffer->uploadUniform("u_maxFogDistance", _renderStorage->getMaxFogDistance());
	_shaderBuffer->uploadUniform("u_fogThickness", _renderStorage->getFogThickness());
	_shaderBuffer->uploadUniform("u_fogColor", _renderStorage->getFogColor());
	_shaderBuffer->uploadUniform("u_isFogEnabled", _renderStorage->isFogEnabled());
	_shaderBuffer->uploadUniform("u_isAmbientLightingEnabled", _renderStorage->isAmbientLightingEnabled());
	_shaderBuffer->uploadUniform("u_isDirectionalLightingEnabled", _renderStorage->isDirectionalLightingEnabled());
	_shaderBuffer->uploadUniform("u_isReflectionsEnabled", _renderStorage->isReflectionsEnabled());
	//_shader->uploadUniform("u_isRefractionsEnabled", _renderStorage->isRefractionsEnabled());
	_shaderBuffer->uploadUniform("u_shadowSize", _renderStorage->getShadowSize());
	_shaderBuffer->uploadUniform("u_shadowLookat", _renderStorage->getShadowLookat());
	_shaderBuffer->uploadUniform("u_shadowLightness", _renderStorage->getShadowLightness());
	_shaderBuffer->uploadUniform("u_isShadowsEnabled", _renderStorage->isShadowsEnabled());
	_shaderBuffer->uploadUniform("u_isShadowCircleEnabled", _renderStorage->isShadowCircleEnabled());
	_shaderBuffer->uploadUniform("u_previousCubeReflectionMap", 0);
	_shaderBuffer->uploadUniform("u_currentCubeReflectionMap", 1);
	_shaderBuffer->uploadUniform("u_planarReflectionMap", 2);
	_shaderBuffer->uploadUniform("u_shadowMap", 3);
	_shaderBuffer->uploadUniform("u_diffuseMap", 4);
	_shaderBuffer->uploadUniform("u_emissionMap", 5);
	_shaderBuffer->uploadUniform("u_specularMap", 6);
	_shaderBuffer->uploadUniform("u_reflectionMap", 7);
	_shaderBuffer->uploadUniform("u_normalMap", 8);

	if(_renderStorage->getPlanarReflectionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getPlanarReflectionTextureBuffer()->getTboId());
	}
	if(_renderStorage->getShadowTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getShadowTextureBuffer()->getTboId());
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

void ModelColorRenderer::unbind()
{
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);
	glDisable(GL_CLIP_DISTANCE4);
	glDisable(GL_CLIP_DISTANCE5);

	if(_renderStorage->getPlanarReflectionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if(_renderStorage->getShadowTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void ModelColorRenderer::processPointlights(const unordered_map<string, shared_ptr<Pointlight>> & pointlights)
{
	vector<shared_ptr<Pointlight>> visiblePointlights;
	for(const auto & [entityId, entity] : pointlights)
	{
		if(entity->isVisible())
		{
			visiblePointlights.push_back(entity);
		}
	}

	for(int index = 0; index < static_cast<int>(visiblePointlights.size()); index++)
	{
		_shaderBuffer->uploadUniform("u_pointlightPositions[" + to_string(index) + "]", visiblePointlights[index]->getPosition());
		_shaderBuffer->uploadUniform("u_pointlightColors[" + to_string(index) + "]", visiblePointlights[index]->getColor());
		_shaderBuffer->uploadUniform("u_pointlightIntensities[" + to_string(index) + "]", visiblePointlights[index]->getIntensity());
		_shaderBuffer->uploadUniform("u_pointlightRadiuses[" + to_string(index) + "]", visiblePointlights[index]->getRadius());
		_shaderBuffer->uploadUniform("u_pointlightShapes[" + to_string(index) + "]", static_cast<int>(visiblePointlights[index]->getShape()));
	}

	_shaderBuffer->uploadUniform("u_pointlightCount", static_cast<int>(visiblePointlights.size()));
}

void ModelColorRenderer::processSpotlights(const unordered_map<string, shared_ptr<Spotlight>> & spotlights)
{
	vector<shared_ptr<Spotlight>> visibleSpotlights;
	for(const auto & [entityId, entity] : spotlights)
	{
		if(entity->isVisible())
		{
			visibleSpotlights.push_back(entity);
		}
	}

	for(int index = 0; index < static_cast<int>(visibleSpotlights.size()); index++)
	{
		_shaderBuffer->uploadUniform("u_spotlightPositions[" + to_string(index) + "]", visibleSpotlights[index]->getPosition());
		_shaderBuffer->uploadUniform("u_spotlightFronts[" + to_string(index) + "]", visibleSpotlights[index]->getFront());
		_shaderBuffer->uploadUniform("u_spotlightColors[" + to_string(index) + "]", visibleSpotlights[index]->getColor());
		_shaderBuffer->uploadUniform("u_spotlightIntensities[" + to_string(index) + "]", visibleSpotlights[index]->getIntensity());
		_shaderBuffer->uploadUniform("u_spotlightAngles[" + to_string(index) + "]", cosf(Mathematics::convertToRadians(visibleSpotlights[index]->getAngle())));
		_shaderBuffer->uploadUniform("u_spotlightDistances[" + to_string(index) + "]", visibleSpotlights[index]->getDistance());
	}

	_shaderBuffer->uploadUniform("u_spotlightCount", static_cast<int>(visibleSpotlights.size()));
}

void ModelColorRenderer::render(const shared_ptr<Model> entity, const unordered_map<string, shared_ptr<Captor>> & captors)
{
	if(!entity->isVisible())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, entity->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, entity->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, entity->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, entity->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, entity->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, entity->getMaxClipPosition().z));
	_shaderBuffer->uploadUniform("u_cubeReflectionMixValue", entity->getCubeReflectionMixValue());
	_shaderBuffer->uploadUniform("u_cameraView", (entity->isFrozen() ? mat44(mat33(_camera->getView())) : _camera->getView()));

	if(!entity->getPreviousCaptorEntityId().empty())
	{
		if(captors.at(entity->getPreviousCaptorEntityId())->getCubeTextureBuffer() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, captors.at(entity->getPreviousCaptorEntityId())->getCubeTextureBuffer()->getTboId());
		}
	}
	if(!entity->getCurrentCaptorEntityId().empty())
	{
		if(captors.at(entity->getCurrentCaptorEntityId())->getCubeTextureBuffer() != nullptr)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, captors.at(entity->getCurrentCaptorEntityId())->getCubeTextureBuffer()->getTboId());
		}
	}

	for(const auto & partId : entity->getPartIds())
	{
		_shaderBuffer->uploadUniform("u_minTextureAlpha", entity->getMinTextureAlpha(partId));
		_shaderBuffer->uploadUniform("u_isReflective", entity->isReflective(partId));
		_shaderBuffer->uploadUniform("u_emissionIntensity", entity->getEmissionIntensity(partId));
		_shaderBuffer->uploadUniform("u_textureRepeat", entity->getTextureRepeat(partId));
		_shaderBuffer->uploadUniform("u_opacity", entity->getOpacity(partId));
		_shaderBuffer->uploadUniform("u_isSpecular", entity->isSpecular(partId));
		_shaderBuffer->uploadUniform("u_reflectivity", entity->getReflectivity(partId));
		_shaderBuffer->uploadUniform("u_lightness", entity->getLightness(partId));
		_shaderBuffer->uploadUniform("u_specularShininess", entity->getSpecularShininess(partId));
		_shaderBuffer->uploadUniform("u_specularIntensity", entity->getSpecularIntensity(partId));
		_shaderBuffer->uploadUniform("u_color", entity->getColor(partId));
		_shaderBuffer->uploadUniform("u_wireframeColor", entity->getWireframeColor(partId));
		_shaderBuffer->uploadUniform("u_hasDiffuseMap", (entity->getDiffuseTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_hasEmissionMap", (entity->getEmissionTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_hasSpecularMap", (entity->getSpecularTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_hasReflectionMap", (entity->getReflectionTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_hasNormalMap", (entity->getNormalTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_transformation", entity->getTransformation(partId));
		_shaderBuffer->uploadUniform("u_normalTransformation", Mathematics::transposeMatrix(Mathematics::invertMatrix(mat33(entity->getTransformation(partId)))));
		_shaderBuffer->uploadUniform("u_reflectionType", static_cast<int>(entity->getReflectionType(partId)));
		_shaderBuffer->uploadUniform("u_isWireframed", entity->isWireframed(partId));
		_shaderBuffer->uploadUniform("u_isBright", entity->isBright(partId));

		if(entity->isFaceCulled(partId))
		{
			glEnable(GL_CULL_FACE);
		}

		if(entity->isWireframed(partId))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if(entity->getDiffuseTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseTextureBuffer(partId)->getTboId());
		}
		if(entity->getEmissionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, entity->getEmissionTextureBuffer(partId)->getTboId());
		}
		if(entity->getSpecularTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, entity->getSpecularTextureBuffer(partId)->getTboId());
		}
		if(entity->getReflectionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, entity->getReflectionTextureBuffer(partId)->getTboId());
		}
		if(entity->getNormalTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, entity->getNormalTextureBuffer(partId)->getTboId());
		}

		glBindVertexArray(entity->getVertexBuffer(partId)->getVaoId());

		glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer(partId)->getVertexCount());
		_renderStorage->increaseTriangleCount(entity->getVertexBuffer(partId)->getVertexCount() / 3);

		glBindVertexArray(0);

		if(entity->getDiffuseTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->getEmissionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->getSpecularTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->getReflectionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if(entity->getNormalTextureBuffer(partId) != nullptr)
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

	if(entity->getPreviousCaptorEntityId().empty())
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	if(entity->getCurrentCaptorEntityId().empty())
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}