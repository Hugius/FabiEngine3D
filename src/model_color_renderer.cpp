#include "model_color_renderer.hpp"
#include "tools.hpp"

using std::to_string;

void ModelColorRenderer::bind()
{
	_shaderBuffer->bind();
	_shaderBuffer->uploadUniform("u_cameraView", _camera->getView());
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
	_shaderBuffer->uploadUniform("u_isRefractionsEnabled", _renderStorage->isRefractionsEnabled());
	_shaderBuffer->uploadUniform("u_shadowSize", _renderStorage->getShadowSize());
	_shaderBuffer->uploadUniform("u_shadowLookat", _renderStorage->getShadowLookat());
	_shaderBuffer->uploadUniform("u_shadowLightness", _renderStorage->getShadowLightness());
	_shaderBuffer->uploadUniform("u_shadowBias", _renderStorage->getShadowBias());
	_shaderBuffer->uploadUniform("u_shadowPcfCount", _renderStorage->getShadowPcfCount());
	_shaderBuffer->uploadUniform("u_isShadowsEnabled", _renderStorage->isShadowsEnabled());
	_shaderBuffer->uploadUniform("u_isShadowCircleEnabled", _renderStorage->isShadowCircleEnabled());
	_shaderBuffer->uploadUniform("u_previousReflectionCubeMap", 0);
	_shaderBuffer->uploadUniform("u_previousRefractionCubeMap", 1);
	_shaderBuffer->uploadUniform("u_currentReflectionCubeMap", 2);
	_shaderBuffer->uploadUniform("u_currentRefractionCubeMap", 3);
	_shaderBuffer->uploadUniform("u_planarReflectionMap", 4);
	_shaderBuffer->uploadUniform("u_planarRefractionMap", 5);
	_shaderBuffer->uploadUniform("u_shadowMap", 6);
	_shaderBuffer->uploadUniform("u_diffuseMap", 7);
	_shaderBuffer->uploadUniform("u_emissionMap", 8);
	_shaderBuffer->uploadUniform("u_specularMap", 9);
	_shaderBuffer->uploadUniform("u_reflectionMap", 10);
	_shaderBuffer->uploadUniform("u_refractionMap", 11);
	_shaderBuffer->uploadUniform("u_normalMap", 12);

	if(_renderStorage->getPlanarReflectionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getPlanarReflectionTextureBuffer()->getTboId());
	}

	if(_renderStorage->getPlanarRefractionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, _renderStorage->getPlanarRefractionTextureBuffer()->getTboId());
	}

	if(_renderStorage->getShadowTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
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
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(_renderStorage->getPlanarRefractionTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if(_renderStorage->getShadowTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	_shaderBuffer->unbind();
}

void ModelColorRenderer::processPointlights(const unordered_map<string, shared_ptr<Pointlight>> & pointlights)
{
	vector<shared_ptr<Pointlight>> visiblePointlights = {};

	for(const auto & [pointlightId, pointlight] : pointlights)
	{
		if(pointlight->isVisible())
		{
			visiblePointlights.push_back(pointlight);
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
	vector<shared_ptr<Spotlight>> visibleSpotlights = {};

	for(const auto & [spotlightId, spotlight] : spotlights)
	{
		if(spotlight->isVisible())
		{
			visibleSpotlights.push_back(spotlight);
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

void ModelColorRenderer::render(const shared_ptr<Model> model, const unordered_map<string, shared_ptr<Captor>> & captors)
{
	if(!model->isVisible())
	{
		return;
	}

	_shaderBuffer->uploadUniform("u_minX", max(_renderStorage->getMinClipPosition().x, model->getMinClipPosition().x));
	_shaderBuffer->uploadUniform("u_minY", max(_renderStorage->getMinClipPosition().y, model->getMinClipPosition().y));
	_shaderBuffer->uploadUniform("u_minZ", max(_renderStorage->getMinClipPosition().z, model->getMinClipPosition().z));
	_shaderBuffer->uploadUniform("u_maxX", min(_renderStorage->getMaxClipPosition().x, model->getMaxClipPosition().x));
	_shaderBuffer->uploadUniform("u_maxY", min(_renderStorage->getMaxClipPosition().y, model->getMaxClipPosition().y));
	_shaderBuffer->uploadUniform("u_maxZ", min(_renderStorage->getMaxClipPosition().z, model->getMaxClipPosition().z));
	_shaderBuffer->uploadUniform("u_cubeReflectionMixValue", model->getCubeReflectionMixValue());
	_shaderBuffer->uploadUniform("u_cubeRefractionMixValue", model->getCubeRefractionMixValue());

	if(!model->getPreviousCaptorId().empty())
	{
		if(captors.at(model->getPreviousCaptorId())->getReflectionTextureBuffer() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, captors.at(model->getPreviousCaptorId())->getReflectionTextureBuffer()->getTboId());
		}

		if(captors.at(model->getPreviousCaptorId())->getRefractionTextureBuffer() != nullptr)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, captors.at(model->getPreviousCaptorId())->getRefractionTextureBuffer()->getTboId());
		}
	}

	if(!model->getCurrentCaptorId().empty())
	{
		if(captors.at(model->getCurrentCaptorId())->getReflectionTextureBuffer() != nullptr)
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_CUBE_MAP, captors.at(model->getCurrentCaptorId())->getReflectionTextureBuffer()->getTboId());
		}

		if(captors.at(model->getCurrentCaptorId())->getRefractionTextureBuffer() != nullptr)
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_CUBE_MAP, captors.at(model->getCurrentCaptorId())->getRefractionTextureBuffer()->getTboId());
		}
	}

	for(const auto & partId : model->getPartIds())
	{
		_shaderBuffer->uploadUniform("u_minAlpha", model->getMinAlpha(partId));
		_shaderBuffer->uploadUniform("u_isReflective", model->isReflective(partId));
		_shaderBuffer->uploadUniform("u_isRefractive", model->isRefractive(partId));
		_shaderBuffer->uploadUniform("u_emissionIntensity", model->getEmissionIntensity(partId));
		_shaderBuffer->uploadUniform("u_textureRepeat", model->getTextureRepeat(partId));
		_shaderBuffer->uploadUniform("u_opacity", model->getOpacity(partId));
		_shaderBuffer->uploadUniform("u_isSpecular", model->isSpecular(partId));
		_shaderBuffer->uploadUniform("u_reflectivity", model->getReflectivity(partId));
		_shaderBuffer->uploadUniform("u_refractivity", model->getRefractivity(partId));
		_shaderBuffer->uploadUniform("u_lightness", model->getLightness(partId));
		_shaderBuffer->uploadUniform("u_specularShininess", model->getSpecularShininess(partId));
		_shaderBuffer->uploadUniform("u_specularIntensity", model->getSpecularIntensity(partId));
		_shaderBuffer->uploadUniform("u_color", model->getColor(partId));
		_shaderBuffer->uploadUniform("u_wireframeColor", model->getWireframeColor(partId));
		_shaderBuffer->uploadUniform("u_hasDiffuseMap", (model->getDiffuseTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_hasEmissionMap", (model->getEmissionTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_hasSpecularMap", (model->getSpecularTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_hasReflectionMap", (model->getReflectionTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_hasRefractionMap", (model->getRefractionTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_hasNormalMap", (model->getNormalTextureBuffer(partId) != nullptr));
		_shaderBuffer->uploadUniform("u_transformation", model->getTransformation(partId));
		_shaderBuffer->uploadUniform("u_normalTransformation", Mathematics::transposeMatrix(Mathematics::invertMatrix(mat33(model->getTransformation(partId)))));
		_shaderBuffer->uploadUniform("u_reflectionType", static_cast<int>(model->getReflectionType(partId)));
		_shaderBuffer->uploadUniform("u_refractionType", static_cast<int>(model->getRefractionType(partId)));
		_shaderBuffer->uploadUniform("u_isWireframed", model->isWireframed(partId));
		_shaderBuffer->uploadUniform("u_isBright", model->isBright(partId));

		if(model->isFaceCulled(partId))
		{
			glEnable(GL_CULL_FACE);
		}

		if(model->isWireframed(partId))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if(model->getDiffuseTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, model->getDiffuseTextureBuffer(partId)->getTboId());
		}

		if(model->getEmissionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, model->getEmissionTextureBuffer(partId)->getTboId());
		}

		if(model->getSpecularTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE9);
			glBindTexture(GL_TEXTURE_2D, model->getSpecularTextureBuffer(partId)->getTboId());
		}

		if(model->getReflectionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE10);
			glBindTexture(GL_TEXTURE_2D, model->getReflectionTextureBuffer(partId)->getTboId());
		}

		if(model->getRefractionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE11);
			glBindTexture(GL_TEXTURE_2D, model->getRefractionTextureBuffer(partId)->getTboId());
		}

		if(model->getNormalTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE12);
			glBindTexture(GL_TEXTURE_2D, model->getNormalTextureBuffer(partId)->getTboId());
		}

		glBindVertexArray(model->getVertexBuffer(partId)->getVaoId());
		glDrawArrays(GL_TRIANGLES, 0, model->getVertexBuffer(partId)->getVertexCount());
		glBindVertexArray(0);

		if(model->getDiffuseTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(model->getEmissionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(model->getSpecularTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE9);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(model->getReflectionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE10);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(model->getRefractionTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE11);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(model->getNormalTextureBuffer(partId) != nullptr)
		{
			glActiveTexture(GL_TEXTURE12);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(model->isWireframed(partId))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if(model->isFaceCulled(partId))
		{
			glDisable(GL_CULL_FACE);
		}

		_renderStorage->increaseTriangleCount(model->getVertexBuffer(partId)->getVertexCount() / 3);
	}

	if(model->getPreviousCaptorId().empty())
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	if(model->getCurrentCaptorId().empty())
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}